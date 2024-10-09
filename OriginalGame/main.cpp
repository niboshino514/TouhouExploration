#include "DxLib.h"
#include "game.h"
#include "SceneManager.h"
#include <crtdbg.h>
#include "Sound.h"
#include "crtdbg.h"
#include "Controller.h"
#include "GameData.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// �����������ׂĉ�����Ă��邩�ǂ����𒲂ׂ�
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// ���[�N���������Ă��郁�����m�ۉ񐔂������ɂ��邱�ƂŁA
    // ���̌��Ƀf�o�b�O�u���[�N�������Ă����
//	_CrtSetBreakAlloc(756);

	// ��ʃ��[�h�̐ݒ�
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	// �o�̓��Otxt���o���Ȃ��悤�ɂ���
	SetOutApplicationLogValidFlag(false);

	// window���[�h�ݒ�
	ChangeWindowMode(Game::kWindowMode);
	// �E�C���h�E���ݒ�
	SetMainWindowText(Game::kTitleText);
	// ��ʃT�C�Y�̐ݒ�
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game::kColorDepth);

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	// �_�u���o�b�t�@���[�h
	SetDrawScreen(DX_SCREEN_BACK);


	// �T�E���h���[�h
	Sound::GetInstance()->Init();

	// �Z�[�u���[�h
	GameData::GetInstance()->LoadSaveData();	// �Z�[�u�f�[�^�̓ǂݍ���
	GameData::GetInstance()->LoadScoreData();	// �X�R�A�f�[�^�̓ǂݍ���


	// �ŏ��̃V�[���̏�����
	SceneManager scene;
	scene.Init();





	while (ProcessMessage() == 0)
	{
		LONGLONG  time = GetNowHiPerformanceCount();
		// ��ʂ̃N���A
		ClearDrawScreen();

		scene.Update();
		scene.Draw();


		//����ʂ�\��ʂ����ւ���
		ScreenFlip();

		// esc�L�[����������I������
		if (CheckHitKey(KEY_INPUT_ESCAPE))	break;

		// fps��60�ɌŒ�
		while (GetNowHiPerformanceCount() - time < 16667)
		{
		}
	}

	// �V�[���I��
	scene.End();

	// �Z�[�u��������
	GameData::GetInstance()->WriteSaveData();	// �Z�[�u�f�[�^�̏�������

	// �V���O���g�����
	{
		// �T�E���h�V���O���g�����
		Sound::GetInstance()->DeleteInstance();

		// �R���g���[���[���
		Controller::GetInstance()->DeleteInstance();

		// �Q�[���f�[�^���
		GameData::GetInstance()->DeleteInstance();
	}

	
	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}