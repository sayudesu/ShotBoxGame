#include "ObjectImage.h"
#include "game.h"
#include "DxLib.h"

ObjectImage::ObjectImage() :
	m_hPlayer(-1),
	m_playerAngle(0.0f),
	m_PlayerPos(0.0f, 0.0f)
{
}

void ObjectImage::draw()
{
	//DrawGraph(static_cast<int>(m_PlayerPos.x), static_cast<int>(m_PlayerPos.y), m_hPlayer, true);
	DrawRotaGraphF(m_PlayerPos.x,m_PlayerPos.y, 1.0f, m_playerAngle/2, m_hPlayer, true);

}
