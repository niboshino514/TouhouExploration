#include "Controller.h"
// �V���O���g��
Controller* Controller::m_pInstance = nullptr;

namespace
{
    // ���O�̃T�C�Y
    const int kLogSize = 16;
}

Controller::Controller()
{
    // ���O�̏�����
    m_padLog.resize(kLogSize);

    // �ݒ�̏�����
    {
        // �����؊���
        m_controllerSetting.autoSwitch = Controller::AutoSwitch::ON;

        // �p�b�h�^�C�v
        m_controllerSetting.padType = Controller::PadType::XBOX;

        // �R���g���[���[�^�C�v
        m_controllerSetting.controllerType = Controller::ControllerType::CONTROLLER;
    }

    // �L�[��Ԃ̏�����
    m_keyInputState = {};

    // ���͎�t�t���O
    m_isAcceptInput = true;
}

void Controller::Update()
{
    // �L�[�{�[�h�̓��͏�Ԃ��X�V
	KeyInputUpdate();

	// �p�b�h�̓��͏�Ԃ��X�V
	PadInputUpdate();
}

void Controller::KeyInputUpdate()
{
    // �S�ẴL�[�̓��͏�Ԃ𓾂�
    GetHitKeyStateAll(m_keyInputState.key);

    for (int i = 0; i < 256; i++)
    {
        // i�Ԃ̃L�[�R�[�h�ɑΉ�����L�[��������Ă�����
        if (m_keyInputState.key[i] != 0)
        {
            m_keyInputState.count[i]++;     // ���Z

            // 10000�ȏ�ɂȂ�����I�[�o�[�t���[���Ȃ��悤�ɂ���
            if (m_keyInputState.count[i] >= 10000)
            {
                m_keyInputState.count[i] = 10000;
            }

            // �I�[�g�X�C�b�`��ON�̏ꍇ
            if(m_controllerSetting.autoSwitch == AutoSwitch::ON)
			{
				// �L�[�{�[�h���͂��������ꍇ�A���̓f�o�C�X���L�[�{�[�h�ɐݒ�
				m_controllerSetting.controllerType = ControllerType::KEYBOARD;
			}

        }
        else
        {              // ������Ă��Ȃ����
            m_keyInputState.count[i] = 0;   // 0�ɂ���
        }
    }
}

void Controller::PadInputUpdate()
{
    // ���݂̃p�b�h�̏�Ԃ��擾
    int padState = GetJoypadInputState(DX_INPUT_PAD1);

    // �p�b�h���͂��������ꍇ�A���̓f�o�C�X���L�[�{�[�h�ɐݒ�
    if (padState != 0)
    {
        // �I�[�g�X�C�b�`��ON�̏ꍇ
        if (m_controllerSetting.autoSwitch == AutoSwitch::ON)
        {
            m_controllerSetting.controllerType = ControllerType::CONTROLLER;
        }
    }
    // ���O�̍X�V
    for (int i = kLogSize - 1; i >= 1; i--)
    {
        m_padLog[i] = m_padLog[i - 1];
    }

    // �ŐV�̏��
    m_padLog[0] = padState;
}

bool Controller::IsPress(const ControllerButton& button)
{
    // ���͎�t�t���O��false�̏ꍇ�A���͂��󂯕t���Ȃ�
    if (!m_isAcceptInput)
	{
		return false;
	}



    // �{�^���̃R�[�h���擾
    const int buttonCode = GetButton(button);

    if(m_controllerSetting.controllerType == ControllerType::CONTROLLER)
	{
		// �R���g���[���[�̏ꍇ
		return (m_padLog[0] & buttonCode);
	}
    else if (m_controllerSetting.controllerType == ControllerType::KEYBOARD)
    {
        // �L�[�{�[�h�̏ꍇ
        return (m_keyInputState.key[buttonCode] != 0);
    }

    return false;
}

bool Controller::IsTrigger(const ControllerButton& button, bool isAllController)
{

    
    // ���͎�t�t���O��false�̏ꍇ�A���͂��󂯕t���Ȃ�
    if (!m_isAcceptInput)
    {
        return false;
    }

    // �{�^���̃R�[�h���擾
    const int buttonCode = GetButton(button);


    if (isAllController)
    {

        bool isNow = (m_padLog[0] & buttonCode);   // ���݂̏��
        bool isLast = (m_padLog[1] & buttonCode);  // �P�t���[���O�̏��
        return (isNow && !isLast);
    }



	if (m_controllerSetting.controllerType == ControllerType::CONTROLLER)
	{
		// �R���g���[���[�̏ꍇ
		return ((m_padLog[0] & buttonCode) && !(m_padLog[1] & buttonCode));
	}
	else if (m_controllerSetting.controllerType == ControllerType::KEYBOARD)
	{
		// �L�[�{�[�h�̏ꍇ
		return (m_keyInputState.key[buttonCode] != 0 && m_keyInputState.count[buttonCode] == 1);
	}
    
	return false;
}


bool Controller::IsTriggerKey(const int& key)
{
	// �L�[�����͂��ꂽ�u�Ԃ��ǂ���
    if (m_keyInputState.key[key] != 0 && m_keyInputState.count[key] == 1)
    {
		return true;
    }
    return false;
}

int Controller::GetButton(const ControllerButton& button)
{

    
    if (m_controllerSetting.controllerType == ControllerType::KEYBOARD)
    {
        // �L�[�{�[�h�̏ꍇ
		return keyboardMapping.at(button);
    }
    else
    {

        switch (m_controllerSetting.padType)
        {
        case Controller::PadType::XBOX:
            // XBOX�̏ꍇ
            return xboxMapping.at(button);

            break;
        case Controller::PadType::DUALSHOCK:
            // �f���A���V���b�N�̏ꍇ
            return dualShockMapping.at(button);

            break;
        case Controller::PadType::SWITCH_PRO:
            // SWITCHPRO�̏ꍇ
            return switchProMapping.at(button);
            break;
        default:
            // XBOX�̏ꍇ
            return xboxMapping.at(button);

            break;
        }
    }


    // �L�[�{�[�h�̏ꍇ
    return keyboardMapping.at(button);
}
