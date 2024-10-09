#include "SceneEnding.h"
#include "Sound.h"
#include "SceneTitle.h"
#include "EndingScreen.h"
#include "Controller.h"

namespace
{
	// �t�F�[�h�C���A�E�g�̃X�s�[�h
	constexpr int kFadeSpeed = 5;

	// �t�F�[�h�̃J���[
	constexpr int kFadeColor = 0x000000;
}

SceneEnding::SceneEnding() :
	m_pEndingScreen(std::make_shared<EndingScreen>())
{
}

SceneEnding::~SceneEnding()
{
}

void SceneEnding::Init()
{
	// �t�F�[�h�C���ݒ�
	SetFadeIn(kFadeSpeed, kFadeColor);

	// �����t��L���ɂ���
	Controller::GetInstance()->SetAcceptInput(true);

	// �G���f�B���O�X�N���[���Ɏ��g�̃|�C���^��n��
	m_pEndingScreen->SetSceneEndingPointer(this);

	// ����������
	m_pEndingScreen->Init();
}

SceneBase* SceneEnding::Update()
{
	// �t�F�[�h����
	UpdateFade();

	// �t�F�[�h�A�E�g���A���񂾂񉹂��������Ȃ�T�E���h����
	FadeOutSound();


	// �t�F�[�h�A�E�g���I�����Ă�����V�[���J�ڂ���
	if (IsFadeOutEnd())
	{
		// �V�[���J��
		return m_nextScene;
	}

	// �X�V����
	m_pEndingScreen->Update();

	return this;
}

void SceneEnding::Draw()
{
	// �`�揈��
	m_pEndingScreen->Draw();

	// �t�F�[�h�`��(��ԉ��ɗ���悤�ɂ���)
	DrawFade();
}

void SceneEnding::ChangeScene(const Scene& nextScene)
{
	// ���̃V�[����ݒ�
	switch (nextScene)
	{
	case SceneEnding::Scene::Title:

		// �^�C�g���V�[��
		m_nextScene = new SceneTitle();

		break;
	default:
		break;
	}

	// �t�F�[�h�A�E�g�ݒ�
	SetFadeOut(kFadeSpeed, kFadeColor);
}

