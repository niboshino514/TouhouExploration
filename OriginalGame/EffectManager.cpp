#include "EffectManager.h"
#include "Effect.h"
#include <DxLib.h>

namespace
{
	// �G�t�F�N�g�O���t�B�b�N�t�@�C���p�X
	const char* const kEffectGraphicFilePath = "Data/Graphic/Ending/Paper.png";

	// �G�t�F�N�g�C���^�[�o��
	constexpr int kEffectInterval = 1;

	// �G�t�F�N�g�ő吔
	constexpr int kEffectMax = 100;
}


EffectManager::EffectManager():
	m_effectHandle(-1), 
	m_frameCount(0)
{
}

EffectManager::~EffectManager()
{
	// �G�t�F�N�g�O���t�B�b�N���폜
	DeleteGraph(m_effectHandle);
}

void EffectManager::Init()
{
	// �G�t�F�N�g�O���t�B�b�N��ǂݍ���
	m_effectHandle = LoadGraph(kEffectGraphicFilePath);

}

void EffectManager::Update()
{
	// �t���[���J�E���g���X�V
	m_frameCount++;


	// �G�t�F�N�g�𐶐�
	if(m_frameCount >= kEffectInterval)
	{
		if (static_cast<int>(m_pEffectList.size() < kEffectMax))
		{
			CreateEffect();
		}
		m_frameCount = 0;
	}

	// �G�t�F�N�g���X�V
	for (auto& effect : m_pEffectList)
	{
		effect->Update();
	}


	// �G�t�F�N�g���폜
	m_pEffectList.erase(std::remove_if(m_pEffectList.begin(), m_pEffectList.end(), [](const std::shared_ptr<Effect>& effect)
	{
		return !effect->GetIsExist();
	}), m_pEffectList.end());
}

void EffectManager::Draw()
{
	// �G�t�F�N�g��`��
	for (auto& effect : m_pEffectList)
	{
		effect->Draw();
	}
}

void EffectManager::CreateEffect()
{
	// �G�t�F�N�g�𐶐�
	m_pEffectList.push_back(std::make_shared<Effect>());
	m_pEffectList.back()->Init();
	m_pEffectList.back()->SetEffectHandle(m_effectHandle);
}
