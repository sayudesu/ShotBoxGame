#include "ObjectEnemy.h"
#include "game.h"
#include "DxLib.h"

namespace
{
}

ObjectEnemy::ObjectEnemy():
	m_pos(0.0f,0.0f)
{

}
ObjectEnemy::~ObjectEnemy()
{

}

void ObjectEnemy::init()
{

}

void ObjectEnemy::end()
{

}

void ObjectEnemy::update()
{

}

void ObjectEnemy::draw(int posX, int posY)
{
	DrawBox(posX,posY,posX + 101,posY + 101, 0xffffff, false);
}

