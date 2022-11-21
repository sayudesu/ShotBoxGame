#pragma once
#include "SceneBase.h"
#include "Vec2.h"

class ObjectImage;

class SceneMain : public SceneBase
{
public:
	SceneMain();
	virtual ~SceneMain();


	virtual void init();
	virtual void end();

	virtual SceneBase* update() override;
	virtual void draw();

	virtual bool isEnd() { return m_isEnd; }
private:

	bool m_isEnd;

	int m_hPlayer;
	float m_playerAngle;

	Vec2 m_pos;

	ObjectImage* m_pObjectImage;
};