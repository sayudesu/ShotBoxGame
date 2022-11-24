#include "ObjectPlayer.h"
#include "game.h"
#include "DxLib.h"

namespace
{
	//�X�e�B�b�N�̊p�x
	constexpr float kStickAngle = 10.0f;
	//��������
	constexpr float kMoveSpeed = 3.0f;
	//�p�x�̑���
	constexpr float kAngleSpeed = 0.3f;
	//�{�b�N�X�̑傫��
	constexpr float kBoxSize = 71.0f;
	//�摜�̊p�x
	constexpr float kAngle = 1.5708f;//90�x�̃��W�A��
	constexpr float kAnglesita = kAngle + kAngle;
	//�摜�f�[�^
	const char* const kPlayerImage = "data/square01a.png";
}

ObjectPlayer::ObjectPlayer() :
	m_hPlayer(-1),//�O���t�B�b�N�n���h��
	m_sizeCount(0),
	m_playerAngle(0.0f),//�v���C���[�̊p�x
	m_playerAngleSave(0.0f),
	m_PlayerGraphSize(0.0f),//�v���C���[�̃T�C�Y
	m_isSize(true),
	m_isMoveCheck(false),
	m_isCheckAngle(false),
	m_pos(0.0f,0.0f),//�v���C���[�̈ʒu
	m_vec(0.0f, 0.0f)//�v���C���[�̉^����
{
}
ObjectPlayer::~ObjectPlayer()
{

}

void ObjectPlayer::init()
{
	m_PlayerGraphSize = 0.3f; //�T�C�Y���w��
}

void ObjectPlayer::end()
{

}

void ObjectPlayer::update()
{
	//�R���g���[���[����
	DINPUT_JOYSTATE input;
	int padState = GetJoypadDirectInputState(DX_INPUT_PAD1, &input);
	m_isMoveCheck = false;

	if (input.X <= -kStickAngle) {//�E
		m_vec.x -= kMoveSpeed;
		m_isMoveCheck = true;
	}
	if (input.X >= kStickAngle) {//��
		m_vec.x += kMoveSpeed;
		m_isMoveCheck = true;
	}
	if (input.Y <= -kStickAngle) {//��
		m_vec.y -= kMoveSpeed;
		m_isMoveCheck = true;
	}
	if (input.Y >= kStickAngle) {//��
		m_vec.y += kMoveSpeed;
		m_isMoveCheck = true;
	}
	if (input.X >= kStickAngle || input.Y <= -kStickAngle) {//�E��
		m_vec.x += kMoveSpeed;
		m_vec.y -= kMoveSpeed;
		m_isMoveCheck = true;
	}
	if (input.X >= kStickAngle || input.Y >= kStickAngle) {//�E��
		m_vec.x += kMoveSpeed;
		m_vec.y += kMoveSpeed;
		m_isMoveCheck = true;
	}
	if (input.X <= -kStickAngle || input.Y >= kStickAngle) {//����
		m_vec.x -= kMoveSpeed;
		m_vec.y += kMoveSpeed;
		m_isMoveCheck = true;
	}
	if (input.X <= -kStickAngle || input.Y <= -kStickAngle) {//����
		m_vec.x -= kMoveSpeed;
		m_vec.y -= kMoveSpeed;
		m_isMoveCheck = true;
	}

	if (!m_isMoveCheck){
		if(m_isSize){//�v���C���[������������
			m_PlayerGraphSize -= 0.005f;
			if(m_PlayerGraphSize <= 0.2f){
				m_isSize = false;
			}
		}
		else if (!m_isSize){//�v���C���[��傫������
			m_PlayerGraphSize += 0.005f;
			if (m_PlayerGraphSize >= 0.3f){
				m_PlayerGraphSize = 0.3f;
				m_sizeCount += 1;
				if (m_sizeCount == 20){//�}�b�N�X�܂ő傫���Ȃ�����20�t���[���~�߂�
					m_isSize = true;
					m_sizeCount = 0;
				}
			}
		}
	}
	else if (m_isMoveCheck){//�v���C���[�𓮂�������傫�����Œ肷��
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
