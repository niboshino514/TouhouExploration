#include "SceneTitle.h"

#include "TitleScreen.h"

#include "SceneMain.h"
#include "Controller.h"
namespace
{
	// �t�F�[�h�C���A�E�g�̃X�s�[�h
	constexpr int kFadeSpeed = 5;

	// �t�F�[�h�̃J���[
	constexpr int kFadeColor = 0x000000;
}

SceneTitle::SceneTitle():
	m_pTitleScreen(std::make_shared<TitleScreen>())
{
}

SceneTitle::~SceneTitle()
{
}

void SceneTitle::Init()
{
	// �t�F�[�h�C���ݒ�
	SetFadeIn(kFadeSpeed, kFadeColor);

	// �^�C�g���X�N���[���Ɏ��g�̃|�C���^��n��
	m_pTitleScreen->SetSceneTitle(this);
	// ����������
	m_pTitleScreen->Init();

	// �����t��L���ɂ���
	Controller::GetInstance()->SetAcceptInput(true);
}

SceneBase* SceneTitle::Update()
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
	m_pTitleScreen->Update();	



	return this;
}

void SceneTitle::Draw()
{
	// �`�揈��
	m_pTitleScreen->Draw();

	// �t�F�[�h�`��(��ԉ��ɗ���悤�ɂ���)
	DrawFade();
}

void SceneTitle::ChangeScene(const Scene& nextScene)
{
	// ���̃V�[����ݒ�
	switch (nextScene)
	{
	case SceneTitle::Scene::GameMain:

		// �Z�[�u�f�[�^�I���V�[��
		m_nextScene = new SceneMain();

		break;
	default:
		break;
	}

	// �����t�𖳌��ɂ���
	Controller::GetInstance()->SetAcceptInput(false);

	// �t�F�[�h�A�E�g�ݒ�
	SetFadeOut(kFadeSpeed, kFadeColor);
}

