#pragma once
#include "MapChipBase.h"

class NoneMapChip : public MapChipBase
{
public:
	NoneMapChip();
	virtual ~NoneMapChip();

	void Init()override;
	void Update()override;
};

