#include "NextStageMapChip.h"



NextStageMapChip::NextStageMapChip()
{
}

NextStageMapChip::~NextStageMapChip()
{
}

void NextStageMapChip::Init()
{
	// �I�u�W�F�N�gID�ݒ�
	m_objectID = ObjectID::NextStageMapChip;

	// �J���[���
	m_color = 0xe0ffff;
}

void NextStageMapChip::Update()
{
	// �����蔻��
	Collision();
}

void NextStageMapChip::Collision()
{
	for (auto& object : m_pObjectFactory->GetObjectInfo())
	{
		switch (object->GetObjectID())
		{
		case ObjectID::Player:

			// �������Ă����ꍇ�A���̃X�e�[�W�Ɉڍs����
			if (FunctionConclusion::IsAABBCollisionDetection(object->GetCircle(), m_square))
			{
				m_pObjectFactory->StageMove(ObjectFactory::MapSwitchType::NextStage);
			
				return;
			}

			break;
		default:
			break;
		}
	}
}
