#include "DxLib.h"
#include "game.h"
#include "Scene/SceneManager.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// window���[�h�ݒ�
	ChangeWindowMode(Game::kWindowMode);
	// �E�C���h�E���ݒ�
	SetMainWindowText(Game::kTitleText);
	//�}�E�X�J�[�\���\��
	SetMouseDispFlag(Game::kMouseMode);
	// ��ʃT�C�Y�̐ݒ�
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game::kColorDepth);

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	// �_�u���o�b�t�@���[�h
	SetDrawScreen(DX_SCREEN_BACK);

	// �ŏ��̃V�[���̏�����
	SceneManager scene;
	scene.init();
	DINPUT_JOYSTATE input;

	while (ProcessMessage() == 0)
	{
		LONGLONG  time = GetNowHiPerformanceCount();
		// ��ʂ̃N���A
		ClearDrawScreen();

		scene.update();
		scene.draw();



		// ���͏�Ԃ��擾
		GetJoypadDirectInputState(DX_INPUT_PAD1, &input);

		// ��ʂɍ\���̂̒��g��`��
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






		//����ʂ�\��ʂ����ւ���
		ScreenFlip();

		// esc�L�[����������I������
		if (CheckHitKey(KEY_INPUT_ESCAPE))	break;

		// fps��60�ɌŒ�
		while (GetNowHiPerformanceCount() - time < 16667)
		{
		}
	}
	scene.end();

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}