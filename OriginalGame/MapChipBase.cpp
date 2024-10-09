#include "MapChipBase.h"

MapChipBase::MapChipBase()
{
}

MapChipBase::~MapChipBase()
{
}


void MapChipBase::Collision()
{
	const auto& objectData = m_pObjectManager->GetObjectInfo();

	for (auto& object : objectData)
	{

		ObjectID objectID = object->GetObjectID();

		if (object->GetObjectID() != ObjectID::Player)
		{
			continue;
		}

		// �v���C���[�Ƃ̓����蔻��
		if (EvoLib::Collision::IsSquareToSquare(m_square, object->GetSquare()))
		{
			m_isGimmick = true;

			return;
		}
	}
}
