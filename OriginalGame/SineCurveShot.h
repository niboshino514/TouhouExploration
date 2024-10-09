#pragma once
#include "ShotBase.h"

class SineCurveShot : public ShotBase
{
public:
	SineCurveShot();
	virtual ~SineCurveShot();
	
	void ShotInit() override;
	void ShotUpdate() override;

private:

	void SineCurveMove();

private:

	// �T�C���J�[�u�̃f�[�^
	EvoLib::Calculation::SineCurveData<float> m_sineCurveData;
};