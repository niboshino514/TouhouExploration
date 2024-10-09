#include "PreviousStageMapChip.h"

PreviousStageMapChip::PreviousStageMapChip()
{
}

PreviousStageMapChip::~PreviousStageMapChip()
{
}

void PreviousStageMapChip::Init()
{
	// �I�u�W�F�N�gID�ݒ�
	m_objectID = ObjectID::PreviousStageMapChip;

	// �J���[���
	m_color = 0x8a2be2;
}

void PreviousStageMapChip::Update()
{
	// �����蔻��
	Collision();
}

void PreviousStageMapChip::Collision()
{
	for (auto& object : m_pObjectFactory->GetObjectInfo())
	{
		switch (object->GetObjectID())
		{
		case ObjectID::Player:

			// �������Ă����ꍇ�A�O�̃X�e�[�W�Ɉڍs����
			if (FunctionConclusion::IsAABBCollisionDetection(object->GetCircle(), m_square))
			{
				m_pObjectFactory->StageMove(ObjectFactory::MapSwitchType::PreviouseStage);
				return;
			}

			break;
		default:
			break;
		}
	}
}
