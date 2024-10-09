#include <DxLib.h>
#include "SceneMain.h"
#include "Vec2.h"
#include "game.h"
#include "Pad.h"
#include "MainScreen.h"
#include "SceneTitle.h"
#include "Sound.h"
#include "SceneEnding.h"
#include "Controller.h"

namespace
{
	// �t�F�[�h�C���A�E�g�̃X�s�[�h
	constexpr int kFadeSpeed = 5;

	// �t�F�[�h�̃J���[
	constexpr int kFadeColor = 0x000000;
}

SceneMain::SceneMain():
	m_pMainScreen(std::make_shared<MainScreen>())
{
}

SceneMain::~SceneMain()
{
}

void SceneMain::Init()
{
	// �����t��L���ɂ���
	Controller::GetInstance()->SetAcceptInput(true);

	// �t�F�[�h�C���ݒ�
	SetFadeIn(kFadeSpeed, kFadeColor);

	// ���C���X�N���[���Ɏ��g�̃|�C���^��n��
	m_pMainScreen->SetSceneMain(this);

	// ����������
	m_pMainScreen->Init();
}

SceneBase* SceneMain::Update()
{
	// �t�F�[�h����
	UpdateFade();

	// �t�F�[�h�A�E�g���A���񂾂񉹂��������Ȃ�T�E���h����
	FadeOutSound();

	// �t�F�[�h�C�����I�����Ă�����V�[���J�ڂ���
	if (IsFadeOutEnd())
	{
		// �V�[���J��
		return m_nextScene;
	}

	// �X�V����
	m_pMainScreen->Update();
	

	return this;
}

void SceneMain::Draw()
{
	// �`�揈��
	m_pMainScreen->Draw();

	// �t�F�[�h�`��(��ԉ��ɗ���悤�ɂ���)
	DrawFade();
}

void SceneMain::ChangeScene(const Scene& nextScene)
{
	// ���̃V�[����ݒ�
	switch (nextScene)
	{
	case SceneMain::Scene::Title:

		// �^�C�g���V�[��
		m_nextScene = new SceneTitle();
		break;

	case SceneMain::Scene::Ending:

		// �G���f�B���O�V�[��
		m_nextScene = new SceneEnding();
		break;

	default:
		break;
	}

	// �����t�𖳌��ɂ���
	Controller::GetInstance()->SetAcceptInput(false);

	// �t�F�[�h�A�E�g�ݒ�
	SetFadeOut(kFadeSpeed, kFadeColor);
}
