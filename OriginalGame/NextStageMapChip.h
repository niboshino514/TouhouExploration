#pragma once
#include "MapChipBase.h"

class NextStageMapChip : public MapChipBase
{
public:
	NextStageMapChip();
	virtual ~NextStageMapChip();

	void Init()override;
	void Update()override;

private:


	/// <summary>
	/// �����蔻��
	/// </summary>
	void Collision();

};

