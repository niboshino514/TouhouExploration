#include "EvoLib.h"
#include <cassert>


void EvoLib::Assert::ErrorMessage(const std::string& errorMessage)
{
#if _DEBUG

	// read me�g
	std::string startFrame = "\n///////// README /////////\n\n";
	// read me�g	
	std::string endFrame = "\n\n//////////////////////////////\n";

	// �G���[���b�Z�[�W
	const std::string errorMsg = startFrame + errorMessage + endFrame;

	//���C�h������ɕϊ�
	WCHAR* _wtext = new WCHAR[strlen(errorMsg.c_str()) + 1];
	mbstowcs_s(nullptr, _wtext, strlen(errorMsg.c_str()) + 1, errorMsg.c_str(), _TRUNCATE);


	_wassert(_wtext, _CRT_WIDE(__FILE__), (unsigned)(__LINE__));
#endif
}

void EvoLib::Assert::ErrorMessageBox(const std::string& errorMessage)
{
#if _DEBUG
	// �I�����b�Z�[�W
	const std::string endMsg = "\n\n\n�v���O�����̎��s�𑱂��܂����H";

	// �G���[���b�Z�[�W
	const std::string errorMsg = errorMessage + endMsg;

	// �G���[����
	int result = MessageBox(NULL, errorMsg.c_str(), "�G���[���b�Z�[�W", MB_YESNO);

	// ���b�Z�[�W�{�b�N�X�̌��ʂ�IDNO�������ꍇ�v���O�������I������
	if (result == IDNO)
	{
		// �v���O�����I��
		DxLib_End();
	}
#endif
}
