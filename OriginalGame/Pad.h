// �R���g���[���[
#pragma once

// �R���g���[���[����̓��͏�Ԃ��擾����
namespace Pad
{
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



	void Update();					// �p�b�h�̓��͏�Ԏ擾
	bool IsPress(int button);		// ������������
	bool IsTrigger(int button);		// �g���K�[����
	bool IsRelase(int button);		// ����������

}
