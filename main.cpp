#include "DxLib.h"
#include "game.h"
#include "Scene/SceneManager.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// windowモード設定
	ChangeWindowMode(Game::kWindowMode);
	// ウインドウ名設定
	SetMainWindowText(Game::kTitleText);
	//マウスカーソル表示
	SetMouseDispFlag(Game::kMouseMode);
	// 画面サイズの設定
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game::kColorDepth);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	// ダブルバッファモード
	SetDrawScreen(DX_SCREEN_BACK);

	// 最初のシーンの初期化
	SceneManager scene;
	scene.init();
	DINPUT_JOYSTATE input;

	while (ProcessMessage() == 0)
	{
		LONGLONG  time = GetNowHiPerformanceCount();
		// 画面のクリア
		ClearDrawScreen();

		scene.update();
		scene.draw();



		// 入力状態を取得
		GetJoypadDirectInputState(DX_INPUT_PAD1, &input);

		// 画面に構造体の中身を描画
		int Color = GetColor(255, 255, 255);
		DrawFormatString(0, 0, Color, "X:%d Y:%d Z:%d",
			input.X, input.Y, input.Z);
		DrawFormatString(0, 16, Color, "Rx:%d Ry:%d Rz:%d",
			input.Rx, input.Ry, input.Rz);
		DrawFormatString(0, 32, Color, "Slider 0:%d 1:%d",
			input.Slider[0], input.Slider[1]);
		DrawFormatString(0, 48, Color, "POV 0:%d 1:%d 2:%d 3:%d",
			input.POV[0], input.POV[1],
			input.POV[2], input.POV[3]);
		DrawString(0, 64, "Button", Color);
		for (int i = 0; i < 32; i++)
		{
			DrawFormatString(64 + i % 8 * 64, 64 + i / 8 * 16, Color,
				"%2d:%d", i, input.Buttons[i]);
		}






		//裏画面を表画面を入れ替える
		ScreenFlip();

		// escキーを押したら終了する
		if (CheckHitKey(KEY_INPUT_ESCAPE))	break;

		// fpsを60に固定
		while (GetNowHiPerformanceCount() - time < 16667)
		{
		}
	}
	scene.end();

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}