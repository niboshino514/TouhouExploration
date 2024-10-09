#include "Effect.h"
#include <vector>
#include "game.h"

namespace ColorData
{
	std::vector<Effect::Color>data =
	{
		Effect::Color{255, 0, 0},
		Effect::Color{0, 255, 0},
		Effect::Color{0, 0, 255},
		Effect::Color{255, 255, 0},
		Effect::Color{0, 255, 255},
		Effect::Color{255, 0, 255},
	};
}

namespace
{
	// ���x�̍ő�l
	constexpr float kSpeedMax = 5.0f;
}


Effect::Effect(): 
	m_effectHandle(0),
	m_isExist(true)
{
}

Effect::~Effect()
{
}

void Effect::Init()
{
	// �J���[�f�[�^�������_���Ŏ擾
	{
		int maxColorIndex = static_cast<int>(ColorData::data.size());
		maxColorIndex-= 1;

		int colorIndex = GetRand(maxColorIndex);
		m_effectData.color = ColorData::data[colorIndex];
	}

	// ���W�������_���Ŏ擾
	{
		m_effectData.pos.x = GetRand(Game::kScreenWidth_F);
		m_effectData.pos.y = GetRand(Game::kScreenHeight_F);
	}

	// ���x�������_���Ŏ擾
	{
		m_effectData.speed = GetRand(kSpeedMax);

		if (m_effectData.speed < 1.0f)
		{
			m_effectData.speed = 1.0f;
		}
	}

	// �ړ����W�A���������_���Ŏ擾
	{
		m_effectData.moveRad = 
			EvoLib::Convert::ConvertAngleToRadian
			(static_cast<float>(GetRand(360)));
	}

	// �摜�̃T�C�Y�������_���Ŏ擾
	{
		m_effectData.graphSize = static_cast<double>(GetRand(10)*0.1f);
	}

	// �摜�̃��W�A���������_���Ŏ擾
	{
		m_effectData.graphRad = 
			EvoLib::Convert::ConvertAngleToRadian
			(static_cast<float>(GetRand(360)));
	}

	// �摜�̓����x�������_���Ŏ擾
	{
		m_effectData.alpha = GetRand(255);
	}
}

void Effect::Update()
{
	// ���W���ړ�
	{
		m_effectData.pos.x += cosf(m_effectData.moveRad) * m_effectData.speed;
		m_effectData.pos.y += sinf(m_effectData.moveRad) * m_effectData.speed;
	}

	// �摜�̓����x������
	{
		m_effectData.alpha -= 1;

		if (m_effectData.alpha < 0)
		{
			m_effectData.alpha = 0;
		}
	}

	// �����x��0�ɂȂ����瑶�݂��Ȃ��t���O�𗧂Ă�
	{
		if (m_effectData.alpha == 0)
		{
			m_isExist = false;
		}
	}

	// ��ʊO�ɏo���瑶�݂��Ȃ��t���O�𗧂Ă�
	{
		if(m_effectData.pos.y < 0.0f)
		{
			m_isExist = false;
		}

		if (m_effectData.pos.y > Game::kScreenHeight_F)
		{
			m_isExist = false;
		}

		if(m_effectData.pos.x > Game::kScreenWidth_F)
		{
			m_isExist = false;
		}

		if (m_effectData.pos.x < 0.0f)
		{
			m_isExist = false;
		}
	}
}

void Effect::Draw()
{
	// �摜�̓����x��ݒ�
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_effectData.alpha);
	}

	// �F��ݒ�
	{
		SetDrawBright(m_effectData.color.r, m_effectData.color.g, m_effectData.color.b);
	}

	// �摜��`��
	{
		DrawRotaGraphF
		(
			m_effectData.pos.x,
			m_effectData.pos.y,
			m_effectData.graphSize,
			m_effectData.graphRad,
			m_effectHandle,
			TRUE
		);
	}

	// �F�����ɖ߂�
	{
		SetDrawBright(255, 255, 255);
	}

	// �摜�̓����x�����ɖ߂�
	{
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}
