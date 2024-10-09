#include "ObjectBase.h"

ObjectBase::ObjectBase():
	m_objectID(),
	m_isExlist(true),
	m_isGimmick(false),
	m_circle(),
	m_square(),
	m_drawRank(),
	m_graphicHandle(),
	m_animationDetails(),
	m_animationRange()
{
}

ObjectBase::~ObjectBase()
{
}

int ObjectBase::AnimationNamberUpdate(const AnimationDetails& animationDetails, const AnimationRange& animationRange)
{
	// ���Z���Z�̔���
	static bool isAdd = true;
	// �t���[���J�E���g
	static int frameCount = 0;
	// �A�j���[�V�����ԍ�
	int animationNum = animationDetails.number;


	if (animationNum <= animationRange.minIndex)
	{
		isAdd = true;
	}
	else if (animationNum >= animationRange.maxIndex)
	{
		isAdd = false;
	}

	// �t���[�����Z
	frameCount++;

	// �A�j���[�V��������
	if (frameCount >= animationDetails.frameSpeed)
	{
		frameCount = 0;

		// ���Z���Z�̔���
		if (isAdd)
		{
			animationNum++;
		}
		else
		{
			animationNum--;
		}
	}

	// �A�j���[�V�����ԍ���Ԃ�
	return animationNum;
}

