#include "SceneManager.h"
#include <cassert>

#include "SceneTitle.h"
#include "SceneMain.h"
#include "SceneEnding.h"

#include "Pad.h"
#include <DxLib.h>
#include "game.h"
#include "Controller.h"
#include "Sound.h"


SceneManager::SceneManager()
{
	m_pScene = nullptr;
}
SceneManager::~SceneManager()
{
}

void SceneManager::Init()
{
	m_pScene = new SceneEnding;
	m_pScene->Init();
}

void SceneManager::End()
{
	assert(m_pScene);
	if (!m_pScene)	return;

	m_pScene->End();
	delete m_pScene;
	m_pScene = nullptr;
}

void SceneManager::Update()
{
	assert(m_pScene);
	if (!m_pScene)	return;

	// �X�V�������x���͂���
	LONGLONG start = GetNowHiPerformanceCount();

	// �p�b�h�̃A�b�v�f�[�g����
	Pad::Update();

	// �R���g���[���[�̃A�b�v�f�[�g����
	Controller::GetInstance()->Update();


	// �X�N���[���^�C�v��ύX
	ScreenTypeChange();

	SceneBase* pScene = m_pScene->Update();
	if (pScene != m_pScene)
	{
		// �O�̃V�[���̏I������
		m_pScene->End();
		delete m_pScene;

		// �T�E���h�̍폜
		Sound::GetInstance()->UnLoad();


		m_pScene = pScene;
		m_pScene->Init();
	}

	// �X�V�������x�v�Z
	m_updateTime = static_cast<int>(GetNowHiPerformanceCount() - start);
}

void SceneManager::Draw()
{
	assert(m_pScene);
	if (!m_pScene)	return;

	// �`�揈�����x���͂���
	LONGLONG start = GetNowHiPerformanceCount();

	m_pScene->Draw();

	// �`�揈�����x�v�Z
	m_drawTime = static_cast<int>(GetNowHiPerformanceCount() - start);


#if _DEBUG

	DrawString(0, Game::kScreenHeight - 48, "�`��", 0xffffff, 0x000000);
	DrawBox(32 + 2, Game::kScreenHeight - 48 + 2, 48 + 16 - 2, Game::kScreenHeight - 32 - 2, 0x0000ff, true);

	DrawString(0, Game::kScreenHeight - 32, "����", 0xffffff, 0x000000);
	DrawBox(32 + 2, Game::kScreenHeight - 32 + 2, 48 + 16 - 2, Game::kScreenHeight - 16 - 2, 0xff0000, true);

	float rate = static_cast<float>(m_updateTime + m_drawTime) / 16666.6f;
	int width = static_cast<int>(Game::kScreenWidth * rate);
	DrawBox(0, Game::kScreenHeight - 16, width, Game::kScreenHeight, 0x0000ff, true);

	rate = static_cast<float>(m_updateTime) / 16666.6f;
	width = static_cast<int>(Game::kScreenWidth * rate);
	DrawBox(0, Game::kScreenHeight - 16, width, Game::kScreenHeight, 0xff0000, true);
#endif
}

void SceneManager::ScreenTypeChange()
{
	// Enter�ŃX�N���[���؂�ւ�
	if (Controller::GetInstance()->IsTriggerKey(KEY_INPUT_RETURN))
	{
		// ���݂̃E�B���h�E���[�h�i�E�B���h�E���[�h�Ȃ�TRUE�A�t���X�N���[���Ȃ�FALSE�j
		bool isWindowMode = GetWindowModeFlag();

		ChangeWindowMode(!isWindowMode);
	}
}