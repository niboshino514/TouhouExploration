#pragma once
#include "SceneBase.h"
#include <memory>


class MainScreen;

class SceneMain : public SceneBase
{
public:
	SceneMain();

	virtual ~SceneMain();


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
		// �G���f�B���O�V�[��
		Ending,
	};

	/// <summary>
	/// �V�[���ύX
	/// </summary>
	void ChangeScene(const Scene& nextScene);


private:

	////////////////////
	// �N���X�|�C���^ //
	////////////////////

	// ���C���X�N���[��
	std::shared_ptr<MainScreen>m_pMainScreen;




};