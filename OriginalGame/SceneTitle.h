#pragma once
#include "SceneBase.h"
#include <memory>

class TitleScreen;

class SceneTitle : public SceneBase
{
public:
	SceneTitle();
	virtual ~SceneTitle();

	virtual void Init()override;
	virtual SceneBase* Update()override;
	virtual void Draw()override;


public:

	// �V�[��
	enum class Scene
	{
		// �Q�[�����C���V�[��
		GameMain,
	};



	/// <summary>
	/// �V�[���ύX
	/// </summary>
	void ChangeScene(const Scene& nextScene);


	

private:

	// �^�C�g���X�N���[���|�C���^
	std::shared_ptr<TitleScreen> m_pTitleScreen;
};