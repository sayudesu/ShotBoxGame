#include "SceneTitle.h"
#include "SceneMain.h"
#include "ObjectImage.h"
#include "DxLib.h"
#include "game.h"

namespace
{
	//スティックの角度
	constexpr int kStickAngle = 10;
	//動く速さ
	constexpr float kMoveSpeed = 5.0f;
	//ボックスの大きさ
	constexpr float kBoxSize = 71.0f;

	const char* const kPlayerImage = "data/square02.png";
}

SceneMain::SceneMain() :
	m_isEnd(false),
	m_hPlayer(-1),//プレイヤーのグラフィックハンドル
	m_playerAngle(0.0f),
	m_pos(0, 0),//プレイヤーの位置
	m_pObjectImage(nullptr)//ポインタ
{
	if (m_pObjectImage != nullptr) {
		delete m_pObjectImage;
	}
	m_pObjectImage = nullptr;

	m_pObjectImage = new ObjectImage;
}

SceneMain::~SceneMain() {
	delete m_pObjectImage;
}

void SceneMain::init() {

	m_hPlayer = LoadGraph(kPlayerImage);

	m_pObjectImage->init();
	//m_pObjectImage->setPos(m_pos);
	m_pObjectImage->setHandle(m_hPlayer);

}
void SceneMain::end() {
	DeleteGraph(m_hPlayer);
}

SceneBase* SceneMain::update() {
	//コントローラー操作
	DINPUT_JOYSTATE input;
	int padState = GetJoypadDirectInputState(DX_INPUT_PAD1, &input);

	if (input.X >= kStickAngle) {	//左
		m_pos.x += kMoveSpeed;
	}
	if (input.X <= -kStickAngle) {	//右
		m_pos.x -= kMoveSpeed;
	}
	if (input.Y >= kStickAngle) {	//下
		m_pos.y += kMoveSpeed;
	}
	if (input.Y <= -kStickAngle) {	//上
		m_pos.y -= kMoveSpeed;
	}
	if (input.X >= kStickAngle || input.Y >= kStickAngle) { //右下
		m_pos.x += kMoveSpeed;
		m_pos.y += kMoveSpeed;
	}
	if (input.X <= -kStickAngle || input.Y <= -kStickAngle) { //左上
		m_pos.x -= kMoveSpeed;
		m_pos.y -= kMoveSpeed;
	}
	if (input.X >= kStickAngle || input.Y <= -kStickAngle) {	//右上
		m_pos.x += kMoveSpeed;
		m_pos.y -= kMoveSpeed;
	}
	if (input.X <= -kStickAngle || input.Y >= kStickAngle) {	//左下
		m_pos.x -= kMoveSpeed;
		m_pos.y += kMoveSpeed;
	}


	if (input.Rx >= 10)
	{
		m_playerAngle +=0.3f; //振り向く速度
		if (m_playerAngle >= 3.18f)
		{
			m_playerAngle = 3.1f;
		}
	}

	m_pObjectImage->getPos(m_pos);
	m_pObjectImage->getAngle(m_playerAngle);
	return this;
}

void SceneMain::draw() {

	DrawBox(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y), static_cast<int>(m_pos.x + kBoxSize), static_cast<int>(m_pos.y + kBoxSize), 0xffffff, false);
	m_pObjectImage->draw();
}