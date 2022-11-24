#pragma once
#include "Vec2.h"

class ObjectImage
{
public:
	ObjectImage();
	virtual ~ObjectImage() {};

	virtual void init() {};
	virtual void end() {};

	virtual void update() {};

	void setHandle(int Player) { m_hPlayer = Player; }
	//void getPos(Vec2 pos) { m_PlayerPos = pos; }
	void getAngle(float handleAngle) {m_playerAngle = handleAngle; }

	virtual void draw(int GraphSize);

protected:
	// グラフィックハンドル
	int	m_hPlayer;
	float m_playerAngle;
	Vec2 m_PlayerPos;

};