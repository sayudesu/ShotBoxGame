#include "SceneTitle.h"
#include "SceneMain.h"
#include "ObjectPlayer.h"
#include "ObjectImage.h"
#include "ObjectEnemy.h"
#include "DxLib.h"
#include "game.h"

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
	constexpr float kAngle = 3.14f;
	constexpr float kAnglesita = kAngle + kAngle;

	const char* const kPlayerImage = "data/square01a.png";
}

SceneMain::SceneMain() :
	m_isEnd(false),
	m_hPlayer(-1),//�v���C���[�̃O���t�B�b�N�n���h��
	m_EnemyPos(0.0f, 0.0f),
	m_pObjectPlayer(nullptr),//�|�C���^
	m_pObjectEnemy(nullptr)
{
	if (m_pObjectPlayer != nullptr) {
		delete m_pObjectPlayer;
		m_pObjectPlayer = nullptr;
	}
	if (m_pObjectEnemy != nullptr) {
		delete m_pObjectEnemy;
		m_pObjectEnemy = nullptr;
	}

	m_pObjectPlayer = new ObjectPlayer;
	m_pObjectEnemy = new ObjectEnemy;
}

SceneMain::~SceneMain() {
	delete m_pObjectPlayer;
}

void SceneMain::init() {

	m_hPlayer = LoadGraph(kPlayerImage);

	m_pObjectPlayer->init();
	m_pObjectPlayer->setHandle(m_hPlayer);
}
void SceneMain::end() {
	DeleteGraph(m_hPlayer);
}

SceneBase* SceneMain::update() {

	m_pObjectPlayer->update();
	/*
	m_pObjectImage->getPos(m_pos);
	m_pObjectImage->getAngle(m_playerAngle);
	*/
	return this;
}

void SceneMain::draw() {

	//DrawBox(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y), static_cast<int>(m_pos.x + kBoxSize), static_cast<int>(m_pos.y + kBoxSize), 0xffffff, false);
	m_pObjectPlayer->draw();
	m_pObjectEnemy->draw(m_EnemyPos.x, m_EnemyPos.y);
}