#include <unordered_map>
#include <DxLib.h>

namespace
{
    // �R���g���[���^�C�v
    enum class ControllerType
    {
        // �L�[�{�[�h
        KEYBOARD,
        // �R���g���[��
        CONTROLLER,
    };

    constexpr int kLogNum = 16;
    // ���̓��O 0���ŐV�̏��
    int padLog[kLogNum];

    // ���݂̓��̓f�o�C�X
    ControllerType currentInputDevice = ControllerType::KEYBOARD;

    // �{�^���̎��
    enum class Button
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

    // �{�^���̃}�b�s���O
    const std::unordered_map<Button, int> keyboardMapping =
    {
        {Button::DECIDE, KEY_INPUT_Z},
        {Button::CANCEL, KEY_INPUT_X},

        {Button::JUMP, KEY_INPUT_SPACE},
        {Button::RESPAWN, KEY_INPUT_R},

        {Button::PAUSE, KEY_INPUT_Q},

        {Button::UP, KEY_INPUT_UP},
        {Button::DOWN, KEY_INPUT_DOWN},
        {Button::LEFT, KEY_INPUT_LEFT},
        {Button::RIGHT, KEY_INPUT_RIGHT},
    };

    const std::unordered_map<Button, int> controllerMapping =
    {
        {Button::DECIDE, PAD_INPUT_1},
        {Button::CANCEL, PAD_INPUT_2},

        {Button::JUMP, PAD_INPUT_3},
        {Button::RESPAWN, PAD_INPUT_4},

        {Button::PAUSE, PAD_INPUT_4},

        {Button::UP, PAD_INPUT_UP},
        {Button::DOWN, PAD_INPUT_DOWN},
        {Button::LEFT, PAD_INPUT_LEFT},
        {Button::RIGHT, PAD_INPUT_RIGHT},
    };
}

namespace Pad
{
    // �p�b�h�̓��͏�Ԏ擾
    void Update()
    {
        // ���݂̃p�b�h�̏�Ԃ��擾
        int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);
        // ���݂̃L�[�{�[�h�̏�Ԃ��擾
        char keyState[256];
        GetHitKeyStateAll(keyState);

        // ���O�̍X�V
        for (int i = kLogNum - 1; i >= 1; i--)
        {
            padLog[i] = padLog[i - 1];
        }
        // �ŐV�̏��
        padLog[0] = padState;

        // ���̓f�o�C�X�̔���
        bool isKeyboardInput = false;
        for (const auto& key : keyboardMapping)
        {
            if (keyState[key.second])
            {
                isKeyboardInput = true;
                break;
            }
        }

        if (isKeyboardInput)
        {
            currentInputDevice = ControllerType::KEYBOARD;
        }
        else if (padState != 0)
        {
            currentInputDevice = ControllerType::CONTROLLER;
        }
    }

    // ������������
    bool IsPress(int button)
    {
        return (padLog[0] & button);
    }

    // �g���K�[����
    bool IsTrigger(int button)
    {
        bool isNow = (padLog[0] & button);   // ���݂̏��
        bool isLast = (padLog[1] & button);  // �P�t���[���O�̏��
        return (isNow && !isLast);
    }

    // ����������
    bool IsRelase(int button)
    {
        bool isNow = (padLog[0] & button);   // ���݂̏��
        bool isLast = (padLog[1] & button);  // �P�t���[���O�̏��
        return (!isNow && isLast);
    }

    // �R���g���[���̎�ނɑ΂���{�^����Ԃ�
    int GetButton(const Button& type)
    {
        switch (currentInputDevice)
        {
        case ControllerType::KEYBOARD:

            return keyboardMapping.at(type);

            break;
        case ControllerType::CONTROLLER:

            return controllerMapping.at(type);

            break;
        default:

            return keyboardMapping.at(type);

            break;
        }

        return 0; // �f�t�H���g�̖߂�l
    }

    // ���݂̓��̓f�o�C�X���擾����
    ControllerType GetCurrentInputDevice()
    {
        return currentInputDevice;
    }
}