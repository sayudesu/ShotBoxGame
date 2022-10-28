#include "SceneTitle.h"
#include "SceneMain.h"
#include "DxLib.h"
#include "game.h"

namespace
{

}

void SceneTitle::init()
{

}
void SceneTitle::end()
{

}

SceneBase* SceneTitle::update()
{
	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	//ƒƒjƒ…[‰æ–Ê‚ÉˆÚ“®
	if (padState & PAD_INPUT_1)
	{
		return(new SceneMain);
	}

	return this;
}

void SceneTitle::draw()
{

}