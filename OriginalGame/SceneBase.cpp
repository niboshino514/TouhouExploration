#include "SceneBase.h"
#include <DxLib.h>
#include "game.h"
#include "Sound.h"

void SceneBase::SetFadeIn(const int& fadeSpeed, const int& fadeColor)
{
	// �t�F�[�h�X�e�[�g���t�F�[�h�C���ɐݒ�
	m_fade.state = Fade::In;

	// �t�F�[�h�X�s�[�h��ݒ�
	m_fade.speed = fadeSpeed;

	// �t�F�[�h�J���[��ݒ�
	m_fade.color = fadeColor;

	// �t�F�[�h�A���t�@�l��ݒ�
	m_fade.alpha = 255;
}

void SceneBase::SetFadeOut(const int& fadeSpeed, const int& fadeColor)
{
	// �t�F�[�h���t�F�[�h�C�����������珈�������Ȃ�
	if (m_fade.state != Fade::InEnd)
	{
		return;
	}

	// �t�F�[�h�X�e�[�g���t�F�[�h�A�E�g�ɐݒ�
	m_fade.state = Fade::Out;

	// �t�F�[�h�X�s�[�h��ݒ�
	m_fade.speed = fadeSpeed;

	// �t�F�[�h�J���[��ݒ�
	m_fade.color = fadeColor;

	// �t�F�[�h�A���t�@�l��ݒ�
	m_fade.alpha = 0;
}


bool SceneBase::IsFadeOutEnd()
{
	// �t�F�[�h�A�E�g���������Ă�����true��Ԃ�
	return m_fade.state == Fade::OutEnd;
}

void SceneBase::UpdateFade()
{
	// �t�F�[�h���������Ă����珈�������Ȃ�
	if (m_fade.state == Fade::State::InEnd ||
		m_fade.state == Fade::State::OutEnd)
	{
		return;
	}


	if (m_fade.state == Fade::State::In)
	{
		// �t�F�[�h�C������
		m_fade.alpha -= m_fade.speed;
		if (m_fade.alpha <= 0)
		{
			m_fade.alpha = 0;
			m_fade.state = Fade::State::InEnd;
		}
	}
	else if (m_fade.state == Fade::State::Out)
	{
		// �t�F�[�h�A�E�g����
		m_fade.alpha += m_fade.speed;
		if (m_fade.alpha >= 255)
		{
			m_fade.alpha = 255;
			m_fade.state = Fade::State::OutEnd;
		}
	}
}

void SceneBase::DrawFade()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fade.alpha);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, m_fade.color, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void SceneBase::FadeOutSound()
{
	// �t�F�[�h�A�E�g���Ŗ�����Ώ��������Ȃ�
	if (m_fade.state != Fade::Out)
	{
		return;
	}

	// �t�F�[�h�ɍ��킹��BGM�̉��ʂ�������
	Sound::GetInstance()->ScreenFadeBGMStop(GetFadeAlpha());
}