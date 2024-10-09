#pragma once
#include <string>
#include <vector>


class MessageTextLoader
{
public:

	// ���[�h�����t�H���g�f�[�^
	struct CSVFontData
	{
		// �t�H���g�t�@�C���p�X
		std::vector<std::string> fontFilePath;
		// �t�H���g��
		std::vector<std::string> fontName;
		// �ʏ�t�H���g�T�C�Y
		int normalFontSize = 0;
		// �������t�H���g�T�C�Y
		int smallFontSize = 0;
		// �傫���t�H���g�T�C�Y
		int bigFontSize = 0;



		// �L�����N�^�[����`�悷��ۂ̃t�H���g�T�C�Y
		int characterNameFontSize = 0;
		// �L�����N�^�[�̍ő啶����
		int characterNameMaxCharCount = 0;
		// �L�����N�^�[���̕������Ԋu
		int characterNameCharInterval = 0;
		// �L�����N�^�[���̃t�H���g�^�C�v
		int characterNameFontType = 0;
	};


	// ���[�h�����L�����N�^�[�f�[�^
	struct CSVCharacterData
	{
		// �L�����N�^�[�t�@�C���p�X
		std::vector<std::string> characterFilePath;
		// �L�����N�^�[��
		std::vector<std::string> characterName;
		// �摜�g�嗦
		std::vector<double> characterScale;
		// �摜�̏c������
		std::vector<int> characterSplitY;
		// �摜�̉�������
		std::vector<int> characterSplitX;
		

		// �摜���E�������ǂ���
		std::vector<bool> characterIsRight;
		// �摜�̏㉺�����l
		std::vector<float> characterAdjustY;
		// �摜�̍��E�����l
		std::vector<float> characterAdjustX;


		// �L�����N�^�[���b�����̃{�C�X�t�@�C���p�X
		std::vector<std::string> characterVoiceFilePath;
		// �L�����N�^�[���b���ۂ̃{�C�X����
		std::vector<int> characterVoiceVolume;

		// ��ʉ�����摜�̒��S�܂ł̋���
		float characterCenterPosOffsetY = 0.0f;
		// ��ʒ[����摜�̒��S�܂ł̋���
		float characterCenterPosOffsetX = 0.0f;

		// �L�����N�^�[���b���Ă��Ȃ����̉摜�̓����x�p�[�Z���e�[�W
		int characterNotSpeakAlphaPercentage = 0;
		// �L�����N�^�[���b���Ă��Ȃ����̉摜���S����̋���
		float characterNotSpeakCenterPosOffsetY = 0.0f;
		// �摜�ړ����x
		float characterMoveSpeed = 0.0f;
	};

	// ���[�h�������b�Z�[�W�E�B���h�E�f�[�^
	struct CSVMessageWindowData
	{
		// ���b�Z�[�W�E�B���h�E�̉���
		float messageWindowWidth = 0.0f;

		// ��ʒ[���烁�b�Z�[�W�E�B���h�E�܂ł̋���
		float messageWindowMargin = 0.0f;

		// ��ʉ����烁�b�Z�[�W�E�B���h�E�܂ł̋���
		float messageWindowPosOffsetY = 0.0f;
	};

	// ���[�h�����g�[�N�f�[�^
	struct CSVTakeData
	{
		// �b������
		std::string talkText;

		// �b���L�����N�^�[�ԍ�
		int talkCharacterNo = 0;

		// �L�����N�^�[�\��ԍ�
		int talkFaceNo = 0;

		// �E�[�ɕ\�����邩�ǂ���
		bool isRight = false;

		// ���]�`�悷�邩�ǂ���
		bool isFlip = false;

		// �t�H���g�J���[
		int fontColor = 0xffffff;

		// �t�H���g�̓����x
		int fontAlpha = 0;

		// �t�H���g�̕����T�C�Y�^�C�v
		int fontSizeType = 0;

		// ������k�킹�邩�ǂ���
		bool isShake = false;

		// �ꕶ����\������̂ɂ�����t���[����
		int drawCharFrame = 0;

		// �t�H���g�^�C�v
		int fontType = 0;

		// �������Ԋu
		int charInterval = 0;

		// �����c�Ԋu
		float lineInterval = 0.0f;

		// �L�����N�^�[���J���[
		int characterNameColor = 0;

		// �L�����N�^�[��
		std::string characterName = "";
	}; 

	// ���[�h�����f�[�^
	struct LoadData
	{
		CSVFontData fontData = CSVFontData();
		CSVCharacterData characterData = CSVCharacterData();
		CSVMessageWindowData messageWindowData = CSVMessageWindowData();
		std::vector<CSVTakeData> talkData;
	};


public:

	MessageTextLoader();
	virtual ~MessageTextLoader();



	/// <summary>
	/// �f�[�^�����[�h����
	/// </summary>
	/// <returns></returns>
	LoadData LoadTextData(const std::string& talkDataCsvFilePath);




private:

	/// <summary>
	/// �e�L�X�g�ݒ�f�[�^�����[�h
	/// </summary>
	void LoadTextSettingData();

	/// <summary>
	/// ��b�f�[�^�����[�h
	/// </summary>
	void LoadTalkData(const std::string& talkDataCsvFilePath);

	/// <summary>
	/// �f�[�^���󂩂ǂ���
	/// </summary>
	/// <param name="str">string�^�̕���</param>
	/// <returns>�f�[�^���󂩂ǂ����̃t���O</returns>
	bool IsEmptyData(const std::string& str);

private:

	// ���[�h�����f�[�^
	LoadData m_loadData;

};