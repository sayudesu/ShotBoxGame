#include "ObjectPlayer.h"
#include "game.h"
#include "DxLib.h"

namespace
{
	//スティックの角度
	constexpr float kStickAngle = 10.0f;
	//動く速さ
	constexpr float kMoveSpeed = 3.0f;
	//角度の速さ
	constexpr float kAngleSpeed = 0.3f;
	//ボックスの大きさ
	constexpr float kBoxSize = 71.0f;
	//画像の角度
	constexpr float kAngle = 1.5708f;//90度のラジアン
	constexpr float kAnglesita = kAngle + kAngle;
	//画像データ
	const char* const kPlayerImage = "data/square01a.png";
}

ObjectPlayer::ObjectPlayer() :
	m_hPlayer(-1),//グラフィックハンドル
	m_sizeCount(0),
	m_playerAngle(0.0f),//プレイヤーの角度
	m_playerAngleSave(0.0f),
	m_PlayerGraphSize(0.0f),//プレイヤーのサイズ
	m_isSize(true),
	m_isMoveCheck(false),
	m_isCheckAngle(false),
	m_pos(0.0f,0.0f),//プレイヤーの位置
	m_vec(0.0f, 0.0f)//プレイヤーの運動量
{
}
ObjectPlayer::~ObjectPlayer()
{

}

void ObjectPlayer::init()
{
	m_PlayerGraphSize = 0.3f; //サイズを指定
}

void ObjectPlayer::end()
{

}

void ObjectPlayer::update()
{
	//コントローラー操作
	DINPUT_JOYSTATE input;
	int padState = GetJoypadDirectInputState(DX_INPUT_PAD1, &input);
	m_isMoveCheck = false;

	if (input.X <= -kStickAngle) {//右
		m_vec.x -= kMoveSpeed;
		m_isMoveCheck = true;
	}
	if (input.X >= kStickAngle) {//左
		m_vec.x += kMoveSpeed;
		m_isMoveCheck = true;
	}
	if (input.Y <= -kStickAngle) {//上
		m_vec.y -= kMoveSpeed;
		m_isMoveCheck = true;
	}
	if (input.Y >= kStickAngle) {//下
		m_vec.y += kMoveSpeed;
		m_isMoveCheck = true;
	}
	if (input.X >= kStickAngle || input.Y <= -kStickAngle) {//右上
		m_vec.x += kMoveSpeed;
		m_vec.y -= kMoveSpeed;
		m_isMoveCheck = true;
	}
	if (input.X >= kStickAngle || input.Y >= kStickAngle) {//右下
		m_vec.x += kMoveSpeed;
		m_vec.y += kMoveSpeed;
		m_isMoveCheck = true;
	}
	if (input.X <= -kStickAngle || input.Y >= kStickAngle) {//左下
		m_vec.x -= kMoveSpeed;
		m_vec.y += kMoveSpeed;
		m_isMoveCheck = true;
	}
	if (input.X <= -kStickAngle || input.Y <= -kStickAngle) {//左上
		m_vec.x -= kMoveSpeed;
		m_vec.y -= kMoveSpeed;
		m_isMoveCheck = true;
	}

	if (!m_isMoveCheck){
		if(m_isSize){//プレイヤーを小さくする
			m_PlayerGraphSize -= 0.005f;
			if(m_PlayerGraphSize <= 0.2f){
				m_isSize = false;
			}
		}
		else if (!m_isSize){//プレイヤーを大きくする
			m_PlayerGraphSize += 0.005f;
			if (m_PlayerGraphSize >= 0.3f){
				m_PlayerGraphSize = 0.3f;
				m_sizeCount += 1;
				if (m_sizeCount == 20){//マックスまで大きくなったら20フレーム止める
					m_isSize = true;
					m_sizeCount = 0;
				}
			}
		}
	}
	else if (m_isMoveCheck){//プレイヤーを動かしたら大きさを固定する
		if (m_PlayerGraphSize <= 0.3f) {
			m_PlayerGraphSize += 0.01;
			if (m_PlayerGraphSize >= 0.3f){
				m_PlayerGraphSize = 0.3f;
			}
		}
	}

	if (input.Rx >= 500||input.Ry >= 500||
		 input.Rx <= -500||input.Ry <= -500){
		m_playerAngleSave = atan2(input.Ry, input.Rx) + kAngle;
	}

	m_pos = m_vec;
	m_playerAngle = m_playerAngleSave;
}

void ObjectPlayer::draw()
{
	DrawRotaGraphF(m_pos.x, m_pos.y, m_PlayerGraphSize , m_playerAngle, m_hPlayer, true);
}
