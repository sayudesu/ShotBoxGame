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

	void setHandle(int handle) { m_hPlayer = handle; }

private:
	// グラフィックハンドル
	int m_hPlayer;
	int m_sizeCount;

	float m_playerAngle;
	float m_playerAngleSave;
	float m_PlayerGraphSize;

	bool m_isSize;
	bool m_isMoveCheck;
	bool m_isCheckAngle;

	// 左上座標
	Vec2 m_pos;
	Vec2 m_vec;
};