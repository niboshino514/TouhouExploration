#pragma once
#include <vector>
#include <Vec2.h>



class SoundOption
{
public:
	SoundOption();
	virtual ~SoundOption();


	void Init();
	void Update();
	void Draw();


	// �O���t�B�b�N���
	struct GraphInfo
	{
		// �n���h��
		std::vector<int> handle;

		// ���W
		std::vector<Vec2> pos;
	};

	void InitSettingItem();// �ݒ荀�ڂ̏�����


	// �E�B���h�E����邩�ǂ���
	bool GetIsCloseWindow() { return m_isCloseWindow; }
private:

	// �O���t�B�b�N�̃��[�h
	void Load();


	// �I�����ڂ̍X�V
	void UpdateSettingItem();
	// �T�E���hBGM�{�����[���̍X�V
	void UpdateSoundBgmVolume();
	// �T�E���hSE�{�����[���̍X�V
	void UpdateSoundSeVolume();

	// �E�B���h�E�̕`��
	void DrawWindow();

	// �ݒ荀�ڂ̕`��
	void DrawSettingItem();
	// �T�E���hBGM�{�����[���̕`��
	void DrawSoundBgmVolume();
	// �T�E���hSE�{�����[���̕`��
	void DrawSoundSeVolume();




private:

	// �ݒ荀��
	enum class SettingItemSenect
	{
		// BGM����
		BGM,
		// SE����
		SE,
		// �Z���N�g��
		SELECT_NUM,
	};





	struct SoundVolume
	{
		// BGM�̃{�����[��
		int bgmVolume;
		// SE�̃{�����[��
		int seVolume;
	};

private:

	//////////////////////
	// �O���t�B�b�N�֘A //
	//////////////////////

	// �E�B���h�E��
	GraphInfo m_windowNameGraph;

	// �ݒ荀�ڃO���t�B�b�N
	GraphInfo m_settingItemGraph;

	// �T�E���h�{�����[���O���t�B�b�N
	GraphInfo m_soundVolumeGraph;

	// �߂�O���t�B�b�N
	GraphInfo m_backGraph;

	// �I���O�p�`�O���t�B�b�N
	int m_selectTriangleGraph;

	//////////////
	// �I���֘A //
	//////////////

	// �I������
	SettingItemSenect m_settingItemSelect;

	// �T�E���h�{�����[��
	SoundVolume m_soundVolume;

	// �E�B���h�E����邩�ǂ���
	bool m_isCloseWindow;
};