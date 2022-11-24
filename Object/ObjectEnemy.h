#pragma once

#include "Vec2.h"

class ObjectEnemy
{
public:
	ObjectEnemy();
	virtual ~ObjectEnemy();

	virtual void init();
	virtual void end();

	virtual void update();
	virtual void draw(int posX, int posY);

private:
	Vec2 m_pos;
};