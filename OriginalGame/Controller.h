#pragma once
#include <unordered_map>
#include <DxLib.h>
#include <vector>

// �R���g���[���[
class Controller
{
private:
	Controller();
	virtual ~Controller() = default;

	static Controller* m_pInstance;

public:

	// �R�s�[�C���X�g���N�^�̋֎~
	Controller(const Controller&) = delete;
	Controller& operator=(const Controller&) = delete;
	Controller(Controller&&) = delete;
	Controller& operator=(Controller&&) = delete;

	static Controller* GetInstance()
	{
		if (m_pInstance == nullptr)
		{
			m_pInstance = new Controller();
		}

		return m_pInstance;
	}

	static void DeleteInstance()
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}

public:

	// �R���g���[���[�̃{�^��
	enum class ControllerButton
	{
		DECIDE, // ����
		CANCEL, // �L�����Z��

		JUMP,   // �W�����v
		RESPAWN,// ���X�|�[��

		PAUSE,  // �|�[�Y

		UP,     // ��
		DOWN,   // ��
		LEFT,   // ��
		RIGHT,  // �E
	};

	// �R���g���[���[�����؊���
	enum class AutoSwitch
	{
		// �I��
		ON,
		// �I�t
		OFF,
		// �Z���N�g��
		AUTO_SWITCH_NUM,
	};

	// �R���g���[���^�C�v
	enum class ControllerType
	{
		// �L�[�{�[�h
		KEYBOARD,
		// �R���g���[��
		CONTROLLER,
		// ���ڐ�
		CONTROLLER_NUM,
	};

	// �p�b�h�̃^�C�v
	enum class PadType
	{
		// XBOX�R���g���[��
		XBOX,
		// �f���A���V���b�N
		DUALSHOCK,
		// SWITCHPRO
		SWITCH_PRO,
		// ���ڐ�
		PAD_TYPE_NUM,
	};

	// �ݒ�
	struct ControllerSetting
	{
		// �����؊���
		AutoSwitch autoSwitch = AutoSwitch::ON;

		// �p�b�h�^�C�v
		PadType padType = PadType::XBOX;

		// �R���g���[���[�^�C�v
		ControllerType controllerType = ControllerType::KEYBOARD;
	};

private:

	// �{�^���̃}�b�s���O
	const std::unordered_map<ControllerButton, int> keyboardMapping =
	{
		{ControllerButton::DECIDE, KEY_INPUT_Z},
		{ControllerButton::CANCEL, KEY_INPUT_X},

		{ControllerButton::JUMP, KEY_INPUT_SPACE},
		{ControllerButton::RESPAWN, KEY_INPUT_R},

		{ControllerButton::PAUSE, KEY_INPUT_Q},

		{ControllerButton::UP, KEY_INPUT_UP},
		{ControllerButton::DOWN, KEY_INPUT_DOWN},
		{ControllerButton::LEFT, KEY_INPUT_LEFT},
		{ControllerButton::RIGHT, KEY_INPUT_RIGHT},
	};

	// xbox�R���g���[���[�̃}�b�s���O
	const std::unordered_map<ControllerButton, int> xboxMapping =
	{
		{ControllerButton::DECIDE, PAD_INPUT_1},
		{ControllerButton::CANCEL, PAD_INPUT_2},

		{ControllerButton::JUMP, PAD_INPUT_1},
		{ControllerButton::RESPAWN, PAD_INPUT_4},

		{ControllerButton::PAUSE, PAD_INPUT_8},

		{ControllerButton::UP, PAD_INPUT_UP},
		{ControllerButton::DOWN, PAD_INPUT_DOWN},
		{ControllerButton::LEFT, PAD_INPUT_LEFT},
		{ControllerButton::RIGHT, PAD_INPUT_RIGHT},
	};

	// dualshock�R���g���[���[�}�b�s���O
	const std::unordered_map<ControllerButton, int> dualShockMapping =
	{
		{ControllerButton::DECIDE, PAD_INPUT_2},
		{ControllerButton::CANCEL, PAD_INPUT_3},

		{ControllerButton::JUMP, PAD_INPUT_2},
		{ControllerButton::RESPAWN, PAD_INPUT_4},

		{ControllerButton::PAUSE, PAD_INPUT_10},

		{ControllerButton::UP, PAD_INPUT_UP},
		{ControllerButton::DOWN, PAD_INPUT_DOWN},
		{ControllerButton::LEFT, PAD_INPUT_LEFT},
		{ControllerButton::RIGHT, PAD_INPUT_RIGHT},
	};

	// switchPro�R���g���[���[�}�b�s���O
	const std::unordered_map<ControllerButton, int> switchProMapping =
	{
		{ControllerButton::DECIDE, PAD_INPUT_2},
		{ControllerButton::CANCEL, PAD_INPUT_3},

		{ControllerButton::JUMP, PAD_INPUT_2},
		{ControllerButton::RESPAWN, PAD_INPUT_4},

		{ControllerButton::PAUSE, PAD_INPUT_10},

		{ControllerButton::UP, PAD_INPUT_UP},
		{ControllerButton::DOWN, PAD_INPUT_DOWN},
		{ControllerButton::LEFT, PAD_INPUT_LEFT},
		{ControllerButton::RIGHT, PAD_INPUT_RIGHT},
	};



public:



	// �R���g���[���[�̓��͏�ԍX�V
	void Update();

	// �L�[�̓��͏�ԍX�V
	void KeyInputUpdate();
	// �p�b�h�̓��͏�ԍX�V
	void PadInputUpdate();


	// �����ꑱ���Ă邩�ǂ���
	bool IsPress(const ControllerButton& button);
	// �����ꂽ�u�Ԃ��ǂ���
	bool IsTrigger(const ControllerButton& button, bool isAllController = false);

	/// <summary>
	/// ������󂯕t���邩�ǂ�����ݒ�
	/// </summary>
	/// <param name="isAcceptInput">��t�t���O</param>
	void SetAcceptInput(const bool& isAcceptInput) { m_isAcceptInput = isAcceptInput; }

	/// <summary>
	/// �R���g���[���[�ݒ��Ԃ�
	/// </summary>
	/// <returns>�R���g���[���[�ݒ�</returns>
	ControllerSetting GetControllerSetting() { return m_controllerSetting; }

	/// <summary>
	/// �R���g���[���[�ݒ���Z�b�g
	/// </summary>
	/// <param name="controllerSetting">�R���g���[���[�ݒ�</param>
	void SetControllerSetting(const ControllerSetting& controllerSetting) { m_controllerSetting = controllerSetting; }

	/// <summary>
	/// �L�[�������ꂽ�u�Ԃ��ǂ���
	/// </summary>
	/// <param name="key">�L�[</param>
	bool IsTriggerKey(const int& key);

private:

	// �R���g���[���[�̎�ނɂ��{�^����
	int GetButton(const ControllerButton& button);

	// �L�[�̓��͏��
	struct KeyInputState
	{
		char key[256];
		int count[256];
	};

private:

	
	// ���̓��O 0���ŐV�̏��
	std::vector<int> m_padLog;

	// �L�[�̏��
	KeyInputState m_keyInputState;

	// �R���g���[���[�̐ݒ�
	ControllerSetting m_controllerSetting;

	// ������󂯕t���邩�ǂ���
	bool m_isAcceptInput;
};