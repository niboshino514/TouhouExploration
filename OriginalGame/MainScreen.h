#pragma once
#include <memory>
#include "SceneMain.h"

class ObjectManager;
class SceneMain;

class MainScreen : public std::enable_shared_from_this<MainScreen>
{
public:
	MainScreen();
	virtual ~MainScreen();

	/// <summary>
	/// �V�[�����C���N���X�|�C���^���擾
	/// </summary>
	/// <param name="sceneMain"></param>
	void SetSceneMain(SceneMain* sceneMain) { m_pSceneMain = sceneMain; }


	void Init();
	void Update();
	void Draw();

public:

	/// <summary>
	/// �V�[���ύX
	/// </summary>
	/// <param name="nextScene">���̃V�[��</param>
	void ChangeScene(const SceneMain::Scene& nextScene);
	


private:




	////////////////////
	// �N���X�|�C���^ //
	////////////////////

	// �V�[�����C���|�C���^
	SceneMain* m_pSceneMain;

	// �I�u�W�F�N�g�t�@�N�g���[�|�C���^
	std::shared_ptr<ObjectManager>m_pObjectFactory;

};