#pragma once
#include "ShotBase.h"

class ReflectionShot : public ShotBase
{
public:
	ReflectionShot();
	~ReflectionShot();

	// �V���b�g�̏�����
	void ShotInit() override;

	// �V���b�g�̍X�V
	void ShotUpdate() override;
};