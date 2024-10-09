#pragma once
#include "Vec2.h"
#include <memory>


class ObjectManager;

class Camera
{
public:
	Camera();
	virtual ~Camera();


	/// <summary>
	/// �I�u�W�F�N�g�t�@�N�g���[�N���X�|�C���^���擾
	/// </summary>
	/// <param name="objectFactory">�I�u�W�F�N�g�t�@�N�g���[�|�C���^</param>
	void SetObjectFactoryPointer(const std::shared_ptr<ObjectManager>& objectFactory) { m_pObjectFactory = objectFactory; }

	/// <summary>
	/// �I�t�Z�b�g�l�v�Z
	/// </summary>
	void OffsetCalculation(const Vec2& targetPos);

	/// <summary>
	/// �J�������W����Ԃ�
	/// </summary>
	Vec2 GetCameraPos() { return m_cameraPos; }

private:

	// �J�������W
	Vec2 m_cameraPos;

	// �I�u�W�F�N�g�t�@�N�g���[�N���X
	std::shared_ptr<ObjectManager> m_pObjectFactory;
};

