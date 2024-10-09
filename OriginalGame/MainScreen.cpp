#include "MainScreen.h"
#include "ObjectManager.h"





MainScreen::MainScreen():
	m_pSceneMain(nullptr),
	m_pObjectFactory(std::make_shared<ObjectManager>())
{
}

MainScreen::~MainScreen()
{
}

void MainScreen::Init()
{
	// �I�u�W�F�N�g�t�@�N�g���[�N���X�Ɏ��g�̃|�C���^��n��
	m_pObjectFactory->SetMainScreenPointer(shared_from_this());

	// ����������
	m_pObjectFactory->Init();
}

void MainScreen::Update()
{
	// �X�V����
	m_pObjectFactory->Update();

	
}

void MainScreen::Draw()
{
	// �`�揈��
	m_pObjectFactory->Draw();
}

void MainScreen::ChangeScene(const SceneMain::Scene& nextScene)
{
	// �V�[���ύX
	m_pSceneMain->ChangeScene(nextScene);
}
