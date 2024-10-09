#pragma once
#include "SceneBase.h"
#include <memory>

class EndingScreen;

class SceneEnding : public SceneBase
{
public:
	SceneEnding();

	virtual ~SceneEnding();

	virtual void Init() override;
	virtual void End() override {}

	virtual SceneBase* Update() override;
	virtual void Draw() override;

public:

	// �V�[��
	enum class Scene
	{
		// �^�C�g���V�[��
		Title,

	};

	/// <summary>
	/// �V�[���ύX
	/// </summary>
	void ChangeScene(const Scene& nextScene);

private:

	// �G���f�B���O�X�N���[���|�C���^
	std::shared_ptr<EndingScreen> m_pEndingScreen;
};

