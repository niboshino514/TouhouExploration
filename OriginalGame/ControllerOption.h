#pragma once
#include <vector>
#include <Vec2.h>
#include "Controller.h"

class ControllerOption
{
public:
	ControllerOption();
	virtual ~ControllerOption();

	void Init();
	void Update();
	void Draw();


public:
	void InitSettingItem();// �ݒ荀�ڂ̏�����


	// �E�B���h�E����邩�ǂ���
	bool GetIsCloseWindow() { return m_isCloseWindow; }
private:

	// �ݒ荀��
	enum class SettingItemSenect
	{
		// �R���g���[���[�����؊���
		AUTO_SWITCH,
		// �R���g���[���[�^�C�v�I��
		CTRL_TYPE,
		// ���̓f�o�C�X�ؑ�
		INPUT_DEVICE,
		// �Z���N�g��
		SELECT_NUM,
	};





	// �O���t�B�b�N���
	struct GraphInfo
	{
		// �n���h��
		std::vector<int> handle;

		// ���W
		std::vector<Vec2> pos;
	};

	



	// �O���t�B�b�N�̃��[�h
	void Load();

	// �I�����ڂ̍X�V
	void UpdateSettingItem();
	// �R���g���[���[�ݒ�̍X�V
	void UpdateControllerSetting();

	void UpdateAutoSwitch();// �R���g���[���[�����؊���
	void UpdateCtrlType();// �R���g���[���[�^�C�v�I��
	void UpdateInputDevice();// ���̓f�o�C�X�ؑ�



	// �E�B���h�E�̕`��
	void DrawWindow();
	// �ݒ荀�ڂ̕`��
	void DrawSettingItem();
	// �R���g���[���[�ݒ�̕`��
	void DrawControllerSetting();
	// �R���g���[���[�����̕`��
	void DrawControllerExplanation();

private:

	//////////////
	// �I���֘A //
	//////////////

	// �I������
	SettingItemSenect m_settingItemSelect;

	// �R���g���[���[�ݒ�
	Controller::ControllerSetting m_controllerSetting;

	// �E�B���h�E����邩�ǂ���
	bool m_isCloseWindow;

	//////////////////////
	// �O���t�B�b�N�֘A //
	//////////////////////
	
	// �E�B���h�E��
	GraphInfo m_windowNameGraph;

	// �ݒ荀�ڃO���t�B�b�N
	GraphInfo m_settingItemGraph;

	// �R���g���[���ݒ�O���t�B�b�N
	std::vector<GraphInfo> m_controllerSettingGraph;

	// �߂�O���t�B�b�N
	GraphInfo m_backGraph;

	// �Z���N�g�O�p�`�O���t�B�b�N
	int m_selectTriangleGraph;
};

