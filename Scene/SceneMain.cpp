#include "SceneTitle.h"
#include "SceneMain.h"
#include "ObjectImage.h"
#include "DxLib.h"
#include "game.h"

namespace
{
	//�X�e�B�b�N�̊p�x
	constexpr int kStickAngle = 10;
	//��������
	constexpr float kMoveSpeed = 5.0f;
	//�{�b�N�X�̑傫��
	constexpr float kBoxSize = 71.0f;

	const char* const kPlayerImage = "data/square02.png";
}

SceneMain::SceneMain() :
	m_isEnd(false),
	m_hPlayer(-1),//�v���C���[�̃O���t�B�b�N�n���h��
	m_playerAngle(0.0f),
	m_pos(0, 0),//�v���C���[�̈ʒu
	m_pObjectImage(nullptr)//�|�C���^
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
	//�R���g���[���[����
	DINPUT_JOYSTATE input;
	int padState = GetJoypadDirectInputState(DX_INPUT_PAD1, &input);

	if (input.X >= kStickAngle) {	//��
		m_pos.x += kMoveSpeed;
	}
	if (input.X <= -kStickAngle) {	//�E
		m_pos.x -= kMoveSpeed;
	}
	if (input.Y >= kStickAngle) {	//��
		m_pos.y += kMoveSpeed;
	}
	if (input.Y <= -kStickAngle) {	//��
		m_pos.y -= kMoveSpeed;
	}
	if (input.X >= kStickAngle || input.Y >= kStickAngle) { //�E��
		m_pos.x += kMoveSpeed;
		m_pos.y += kMoveSpeed;
	}
	if (input.X <= -kStickAngle || input.Y <= -kStickAngle) { //����
		m_pos.x -= kMoveSpeed;
		m_pos.y -= kMoveSpeed;
	}
	if (input.X >= kStickAngle || input.Y <= -kStickAngle) {	//�E��
		m_pos.x += kMoveSpeed;
		m_pos.y -= kMoveSpeed;
	}
	if (input.X <= -kStickAngle || input.Y >= kStickAngle) {	//����
		m_pos.x -= kMoveSpeed;
		m_pos.y += kMoveSpeed;
	}


	if (input.Rx >= 10)
	{
		m_playerAngle +=0.3f; //�U��������x
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