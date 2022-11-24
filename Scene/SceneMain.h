#pragma once
#include "SceneBase.h"
#include "Vec2.h"

class ObjectPlayer;
class ObjectEnemy;

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

	Vec2 m_EnemyPos;

	Vec2 m_target;
	ObjectPlayer* m_pObjectPlayer;
	ObjectEnemy* m_pObjectEnemy;
};