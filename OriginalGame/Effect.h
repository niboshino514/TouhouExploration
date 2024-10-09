#pragma once
#include "Vec2.h"
#include <EvoLib.h>


class Effect
{
public:
	Effect();
	virtual ~Effect();

	
	void Init();
	void Update();
	void Draw();

	// �G�t�F�N�g�n���h�����擾
	void SetEffectHandle(int effectHandle){ m_effectHandle = effectHandle; }

	bool GetIsExist(){ return m_isExist; }
public:

	struct Color
	{
		// ��
		int r = 0;
		// ��
		int g = 0;
		// ��
		int b = 0;
	};


	// �G�t�F�N�g�f�[�^
	struct EffectData
	{
		// ���W
		Vec2 pos = Vec2();
		// ���x
		float speed = 0.0f;
		// �ړ����W�A��
		float moveRad = 0.0f;


		// �摜�̃T�C�Y
		double graphSize = 0.0;
		// �摜�̃��W�A��
		float graphRad = 0.0f;
		// �摜�̓����x
		int alpha = 255;

		// �摜�̐F
		Color color = Color();
	};


private:

	// �G�t�F�N�g�f�[�^
	EffectData m_effectData;

	// �G�t�F�N�g�n���h��
	int m_effectHandle;

	// ���݂��邩�̃t���O
	bool m_isExist = false;

};