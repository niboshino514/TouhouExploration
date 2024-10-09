#include "SaveDataSelectScreen.h"
#include <DxLib.h>
#include "Game.h"
#include "SceneSaveDataSelect.h"
#include "Controller.h"


SaveDataSelectScreen::SaveDataSelectScreen():
	m_pSceneSaveDataSelect(nullptr)
{
}

SaveDataSelectScreen::~SaveDataSelectScreen()
{
}

void SaveDataSelectScreen::Init()
{
}

void SaveDataSelectScreen::Update()
{
	// �{�^���������ꂽ��t�F�[�h�A�E�g��ݒ肷��
	if (Controller::GetInstance()->IsTrigger(Controller::ControllerButton::DECIDE))
	{
		// �Q�[�����C���V�[���ɑJ��
		m_pSceneSaveDataSelect->ChangeScene(SceneSaveDataSelect::NextScene::GameMain);
	}

	// �{�^���������ꂽ��t�F�[�h�A�E�g��ݒ肷��
	if (Controller::GetInstance()->IsTrigger(Controller::ControllerButton::CANCEL))
	{
		// �^�C�g���V�[���ɑJ��
		m_pSceneSaveDataSelect->ChangeScene(SceneSaveDataSelect::NextScene::Title);
	}
}

void SaveDataSelectScreen::Draw()
{
	// �w�i
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x4682b4, true);
}