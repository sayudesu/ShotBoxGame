#pragma once

#include "Vec2.h"

class ObjectPlayer
{
public:
	ObjectPlayer();
	virtual ~ObjectPlayer();

	virtual void init();
	virtual void end();

	virtual void update();
	virtual void draw();

	Vec2 getPos() const { return m_pos; }

	void setHandle(int handle) { m_hGraph = handle; }

private:
	// �O���t�B�b�N�n���h��
	int 	m_hGraph;
	// ������W
	Vec2	m_pos;
};