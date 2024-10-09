#include "Camera.h"
#include "game.h"
#include "ObjectManager.h"
#include "GameData.h"

Camera::Camera():
	m_cameraPos()
{
}

Camera::~Camera()
{
}


void Camera::OffsetCalculation(const Vec2& targetPos)
{
	// �^�[�Q�b�g�I�t�Z�b�g
	Vec2 offset = Vec2();

	
	

	// �}�b�v�̏c��������
	const float mapWidth = (m_pObjectFactory->GetMapInfoData().mapChip.mapWidth * m_pObjectFactory->GetMapInfoData().mapChip.chipSize);
	const float mapHeight = (m_pObjectFactory->GetMapInfoData().mapChip.mapHeight * m_pObjectFactory->GetMapInfoData().mapChip.chipSize);



	// �X�N���[���̌v�Z�A�v���C���[����ʒ����ɕ\�������悤�ɃX�N���[������
	offset.x = (Game::kScreenWidth / 2) - targetPos.x;
	if (offset.x > 0)
	{
		offset.x = 0;
	}
	if (offset.x < -mapWidth + static_cast<float>(Game::kScreenWidth))
	{
		offset.x = -mapWidth + static_cast<float>(Game::kScreenWidth);
	}

	offset.y = (Game::kScreenHeight / 2) - targetPos.y;
	if (offset.y > 0)
	{
		offset.y = 0;
	}
	if (offset.y < -mapHeight + static_cast<float>(Game::kScreenHeight))
	{
		offset.y = -mapHeight + static_cast<float>(Game::kScreenHeight);
	}


	m_cameraPos = offset * 0.2f + m_cameraPos * 0.8f;


	// �X�N���[���̔����̉���
	const float screenWidthCenter = Game::kScreenWidth * 0.5f;
	const float screenHeightCenter = Game::kScreenHeight * 0.5f;



	// �␳�I�t�Z�b�g�l
	Vec2 correctionOffset = m_cameraPos;


	if (Game::kScreenWidth >= mapWidth)
	{
		// ���S�}�b�v�l
		const float centerMapValue = correctionOffset.x - screenWidthCenter;

		// �␳�I�t�Z�b�g�l�v�Z
		correctionOffset.x = (m_cameraPos.x - centerMapValue) - (mapWidth * 0.5f);
	}

	if (Game::kScreenHeight >= mapHeight)
	{
		// ���S�}�b�v�l
		const float centerMapValue = correctionOffset.y - screenHeightCenter;

		// �␳�I�t�Z�b�g�l�v�Z
		correctionOffset.y = (m_cameraPos.y - centerMapValue) - (mapHeight * 0.5f);
	}

	// �Q�[���f�[�^�ɃJ�������W����
	GameData::GetInstance()->SetCameraPos(correctionOffset);
}
