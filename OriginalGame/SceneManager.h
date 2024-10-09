#pragma once

#include "SceneBase.h"

class SceneManager
{


public:
	SceneManager();
	virtual ~SceneManager();

	void Init();
	void End();

	void Update();
	void Draw();

private:

	// �X�N���[���^�C�v�̕ύX
	void ScreenTypeChange();


private:
	// �V�[��
	SceneBase* m_pScene;

	// �X�V�������x
	int m_updateTime = 0;
	// �`�揈�����x
	int m_drawTime = 0;
};