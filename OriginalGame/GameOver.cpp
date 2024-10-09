#include "GameOver.h"
#include "EvoLib.h"
#include "GameData.h"
#include "Vec2.h"
#include "game.h"

namespace
{
	// �Q�[���I�[�o�[�O���t�B�b�N�t�@�C����
	static const char* const kGameOverFileName = "Data/Graphic/GameMain/GameOver.png";

}


GameOver::GameOver():
	m_gameOverGraphHandle(-1)
{
}

GameOver::~GameOver()
{
	// �O���t�B�b�N�n���h�����
	DeleteGraph(m_gameOverGraphHandle);
}

void GameOver::Init()
{
	// �Q�[���I�[�o�[�O���t�B�b�N�ǂݍ���
	m_gameOverGraphHandle = EvoLib::Load::LoadGraph_EvoLib(kGameOverFileName);

}

void GameOver::Draw()
{
	// �v���C���[�����S���Ă��Ȃ��ꍇ�A�������s��Ȃ�
	if(GameData::GetInstance()->GetIsPlayerAlive())
	{
		return;
	}


	// ��ʑS�̂𔖂��h��Ԃ�
	{
		// �����x�𔼕��ɐݒ�
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);

		// ��ʑS�̂����œh��Ԃ�
		DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, TRUE);

		// �����x�����ɖ߂�
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	
	// ��ʒ����ɃQ�[���I�[�o�[�O���t�B�b�N��`��
	{
		// �Q�[���I�[�o�[�O���t�B�b�N�̃T�C�Y���擾
		int w, h;
		GetGraphSize(m_gameOverGraphHandle, &w, &h);

		// �Q�[���I�[�o�[�O���t�B�b�N����ʒ����ɕ`��
		DrawGraph(Game::kScreenWidth / 2 - w / 2, Game::kScreenHeight / 2 - h / 2, m_gameOverGraphHandle, TRUE);
	}
}
