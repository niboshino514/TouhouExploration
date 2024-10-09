#pragma once
#include <string>
#include "Vec2.h"
#include <vector>
#include <memory>

class MessageTextLoader;

class MessageWindow
{
public:

	// �t�H���g�T�C�Y
	enum FontSize
	{
		Normal,			// �ʏ�
		Small,			// ������
		Big,			// �傫��
		FontSizeCount,	// �t�H���g�T�C�Y�̐�
	};


	// ���b�Z�[�W�v�f
	struct MessageElement
	{
		// �b������
		std::string talkText = "";

		// �b���L�����N�^�[�ԍ�
		int talkCharacterNo = 0;

		// �L�����N�^�[�̕\��ԍ�
		int talkFaceNo = 0;

		// �E�[�ɕ\�����邩�ǂ���
		bool isRight = false;

		// ���]�`�悷�邩�ǂ���
		bool isFlip = false;

		// �e�L�X�g�̃t�H���g�J���[
		int fontColor = 0xffffff;

		// �t�H���g�̓����x
		int fontAlpha = 0;

		// �t�H���g�̕����T�C�Y�^�C�v
		FontSize fontSizeType = FontSize();

		// ������k�킹�邩�ǂ���
		bool isShake = false;

		// �e�L�X�g�X�s�[�h
		int drawCharFrame = 0;

		// �t�H���g�^�C�v
		int fontType = 0;

		// �e�L�X�g�̕�����
		int charInterval = 0;

		// �e�L�X�g�T�C�Y����̍s��
		float lineInterval = 0.4f;

		// �L�����N�^�[���J���[
		int characterNameColor = 0;

		// �L�����N�^�[��
		std::string characterName = "";
	};

public:
	MessageWindow();
	virtual ~MessageWindow();


	void Update();
	void Draw();


	// �e�L�X�g�\�����
	struct TextDisplayInfo
	{
		// �e�L�X�g�̍��W
		Vec2 textPos = Vec2(0, 0);

		// �e�L�X�g�ԍ�
		int currentNumber = 0;

		// ���͂̕\�����I��������ǂ���
		bool isEndText = false;

		// ������𑁂��`�悷�邩�ǂ���
		bool isFastDraw = false;

		// ������i�[
		std::string m_temp = "";

		// �i���؂�ւ��t���O
		bool isParagraph = false;

		// �t���[�����J�E���g
		int frameCount = 0;

		// �\�����镶����
		int dispCharCount = 0;

		// �ʏ�t�H���g�T�C�Y
		int normalFontSize = 0;
		// �������t�H���g�T�C�Y
		int smallFontSize = 0;
		// �傫���t�H���g�T�C�Y
		int bigFontSize = 0;



		// �t�H���g�n���h��
		std::vector<std::vector<int>> fontHandle;

	

		// �L�����N�^�[���̃t�H���g�n���h��
		int nameFontHandle = 0;

		// �L�����N�^�[���̕������Ԋu
		int characterNameCharInterval = 0;

	};

	// ���b�Z�[�W�E�B���h�E���
	struct MessageWindowInfo
	{
		// �E�B���h�E�̍�����W
		Vec2 leftTop = Vec2();

		// �E�B���h�E�̉E�����W
		Vec2 rightBottom = Vec2();

		// �L�����N�^�[����\������E�B���h�E�̍�����W
		Vec2 nameLeftTop = Vec2();

		// �L�����N�^�[����\������E�B���h�E�̉E�����W
		Vec2 nameRightBottom = Vec2();

		// �L�����N�^�[����\������E�B���h�E�̉���
		float nameWindowWidth = 0.0f;
	};

	// �L�����N�^�[�\�����
	struct CharacterDisplayInfo
	{
		// �L�����N�^�[�O���t�B�b�N�n���h��
		std::vector<int> graphicHandle;

		// �L�����N�^�[��
		std::string name = "";

		// �L�����N�^�[�g�嗦
		double scale = 1.0f;

		// �摜���E�����ɂ��邩�ǂ���
		bool isGraphRight = false;


		// �E���ɕ\������Ă��邩�ǂ���
		bool isRightDraw = false;

		// �L�����N�^�[�̍��W
		Vec2 pos = Vec2();

		// �L�����N�^�[�̃I�t�Z�b�g�l
		Vec2 centerPosOffset = Vec2();

		// �^�[�Q�b�g���W
		Vec2 targetPos = Vec2();

		// �ړ���
		Vec2 vec = Vec2();
	};


public:

	/// <summary>
	/// �f�[�^�̓ǂݍ���
	/// </summary>
	void LoadData(const std::string& talkCsvFilePath);

	/// <summary>
	/// ���ׂẴe�L�X�g���I���������ǂ���
	/// </summary>
	/// <returns>�e�L�X�g���I���t���O��Ԃ�</returns>
	bool IsAllTextEnd() { return m_isAllTextEnd; }

	// �f�[�^�̏�����
	void InitData();

	// �f�[�^�̃��Z�b�g
	void ResetData();

private:

	/// <summary>
	/// �f�[�^�̉��
	/// </summary>
	void UnloadData();



	/// <summary>
	/// �e�L�X�g�\���i�s
	/// </summary>
	void UpdateTextDisplay();

	/// <summary>
	/// ���͎��Ƀe�L�X�g�̍X�V
	/// </summary>
	void UpdateTextOnInput();


	/// <summary>
	/// �e�L�X�g�`��
	/// </summary>
	void DrawMessageText();

	/// <summary>
	/// �L�����N�^�[���̕`��
	/// </summary>
	void DrawCharacterNameText();



	/// <summary>
	/// ������̃T�C�Y���擾
	/// </summary>
	/// <param name="str">������</param>
	/// <param name="length">���ׂ镶��</param>
	/// <param name="fontHandle">�t�H���g�n���h��</param>
	/// <returns>������̃T�C�Y</returns>
	int GetDrawStringWidth(const char* str, const int& length, const int& fontHandle);

	/// <summary>
	/// �����񂪃��b�Z�[�W�E�B���h�E�Ɏ��܂邩�ǂ���
	/// </summary>
	/// <param name="textPos">�e�L�X�g�̍��W</param>
	/// <param name="fontHandle">�t�H���g�̃n���h��</param>
	/// <returns>�����񂪃��b�Z�[�W�E�B���h�E�Ɏ��܂邩�ǂ����̃t���O</returns>
	bool IsTextInWindow(const Vec2 textPos, const int fontHandle);




	/// <summary>
	/// ���b�Z�[�W�E�B���h�E�̕`��
	/// </summary>
	void DrawMessageWindow();
	

	/// <summary>
	/// �L�����N�^�[�̏����ʒu�ݒ�
	/// </summary>
	/// <param name="isRightDraw">�E�ɕ\�����邩�ǂ���</param>
	void InitCharacterPos(const bool& isRightDraw);

	/// <summary>
	/// �L�����N�^�[�̈ʒu�ݒ�
	/// </summary>
	/// <param name="isRightDraw">�E�ɕ\�����邩�ǂ���</param>
	/// <param name="characterNumber">�L�����N�^�[�ԍ�</param>
	/// <param name="isBeforeNumber">�O�̃L�����N�^�[�ԍ����ǂ���</param>
	void SetUpCharacterPos(const bool& isRightDraw, const int& characterNumber, const bool isBeforeNumber);

	/// <summary>
	/// �L�����N�^�[���W�X�V
	/// </summary>
	void UpdateCharacterPos();

	/// <summary>
	/// �L�����N�^�[�`��
	/// </summary>
	void DrawCharacter();

	/// <summary>
	/// �L�����N�^�[�𔽓]�����邩�ǂ���
	/// </summary>
	/// <param name="characterNumber">�L�����N�^�[�i���o�[</param>
	/// <param name="textNumber">�e�L�X�g�i���o�[</param>
	/// <returns>���]�t���O��Ԃ�</returns>
	bool IsFlipCharacter(const int& characterNumber, const int& textNumber);


private:

	// �e�L�X�g���
	TextDisplayInfo m_textInfo;

	// �E�B���h�E���
	MessageWindowInfo m_windowInfo;

	// �L�����N�^�[���
	std::vector<CharacterDisplayInfo> m_characterInfo;

	// �L�����N�^�[�̈ړ����x
	float m_moveSpeed;

	// �L�����N�^�[���b���Ă��Ȃ����̓����x
	int m_graphNotSpeakAlpha;

	// ���b�Z�[�W�v�f
	std::vector<MessageElement> m_messageElement;

	// ���ׂẴe�L�X�g���I���������ǂ���
	bool m_isAllTextEnd;

	////////////////////////
	// �N���X�|�C���^�֘A //
	////////////////////////

	// ���b�Z�[�W�e�L�X�g���[�_�[�|�C���^
	std::shared_ptr<MessageTextLoader> m_pMessageTextLoader;
};

