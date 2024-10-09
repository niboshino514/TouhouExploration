#include "MessageTextLoader.h"
#include "EvoLib.h"
#include <iostream>

namespace
{
	// �t�@�C��Path
	const char* const kTextSettingDataFilePath = "Data/Csv/Talk/TextSetting.csv";
}

MessageTextLoader::MessageTextLoader():
	m_loadData()
{
}

MessageTextLoader::~MessageTextLoader()
{
}

MessageTextLoader::LoadData MessageTextLoader::LoadTextData(const std::string& talkDataCsvFilePath)
{
	// �e�L�X�g�ݒ�f�[�^�̓ǂݍ���
	LoadTextSettingData();
	
	// ��b�f�[�^�̓ǂݍ���
	LoadTalkData(talkDataCsvFilePath);

	// �f�[�^��Ԃ�
	return m_loadData;
}

void MessageTextLoader::LoadTextSettingData()
{
	// �e�L�X�g�ݒ�f�[�^�t�@�C���p�X
	const char* textSettingDataFilePath = kTextSettingDataFilePath;


	// �e�L�X�g�ݒ�f�[�^�̓ǂݍ���
	std::vector<std::vector<std::string>> csvFileData =
		EvoLib::File::CsvFileLoading_Revision(textSettingDataFilePath, true, 2, true);


	// �t�H���g�f�[�^�̓ǂݍ���
	CSVFontData fontData = CSVFontData();

	// �t�H���g�f�[�^�֘A
	{
		// �t�H���g�t�@�C���p�X
		fontData.fontFilePath = csvFileData[0];
		// �t�H���g��
		fontData.fontName = csvFileData[1];
		// �ʏ�t�H���g�T�C�Y
		fontData.normalFontSize = std::stoi(csvFileData[2][0]);
		// �������t�H���g�T�C�Y
		fontData.smallFontSize = std::stoi(csvFileData[3][0]);
		// �傫���t�H���g�T�C�Y
		fontData.bigFontSize = std::stoi(csvFileData[4][0]);


		// �L�����N�^�[����`�悷��ۂ̃t�H���g�T�C�Y
		fontData.characterNameFontSize = std::stoi(csvFileData[5][0]);
		// �L�����N�^�[�̍ő啶����
		fontData.characterNameMaxCharCount = std::stoi(csvFileData[6][0]);
		// �L�����N�^�[���̕������Ԋu
		fontData.characterNameCharInterval = std::stoi(csvFileData[7][0]);
		// �L�����N�^�[���̃t�H���g�^�C�v
		fontData.characterNameFontType = std::stoi(csvFileData[8][0]);
	}






	// �L�����N�^�[�f�[�^�̓ǂݍ���
	CSVCharacterData characterData = CSVCharacterData();

	// �L�����N�^�[�f�[�^�֘A
	{
		// �L�����N�^�[�t�@�C���p�X
		characterData.characterFilePath = csvFileData[9];
		// �L�����N�^�[��
		characterData.characterName = csvFileData[10];
		// �摜�g�嗦
		for (int i = 0; i < static_cast<int>(csvFileData[11].size()); i++)
		{
			characterData.characterScale.push_back(std::stod(csvFileData[11][i]));
		}
		// �摜�̏c������
		for (int i = 0; i < static_cast<int>(csvFileData[12].size()); i++)
		{
			characterData.characterSplitY.push_back(std::stoi(csvFileData[12][i]));
		}
		// �摜�̉�������
		for (int i = 0; i < static_cast<int>(csvFileData[13].size()); i++)
		{
			characterData.characterSplitX.push_back(std::stoi(csvFileData[13][i]));
		}
		// �摜���E�������ǂ���
		for (int i = 0; i < static_cast<int>(csvFileData[14].size()); i++)
		{
			characterData.characterIsRight.push_back(EvoLib::Convert::ConvertStringToBool(csvFileData[14][i]));
		}
		// �摜�̏㉺�����l
		for (int i = 0; i < static_cast<int>(csvFileData[15].size()); i++)
		{
			characterData.characterAdjustY.push_back(std::stof(csvFileData[15][i]));
		}
		// �摜�̍��E�����l
		for (int i = 0; i < static_cast<int>(csvFileData[16].size()); i++)
		{
			characterData.characterAdjustX.push_back(std::stof(csvFileData[16][i]));
		}


		// �L�����N�^�[���b�����̃{�C�X�t�@�C���p�X
		characterData.characterVoiceFilePath = csvFileData[17];
		// �L�����N�^�[���b���ۂ̃{�C�X����
		for (int i = 0; i < static_cast<int>(csvFileData[18].size()); i++)
		{
			characterData.characterVoiceVolume.push_back(std::stoi(csvFileData[18][i]));
		}

		// ��ʉ�����摜�̒��S�܂ł̋���
		characterData.characterCenterPosOffsetY = std::stof(csvFileData[19][0]);
		// ��ʒ[����摜�̒��S�܂ł̋���
		characterData.characterCenterPosOffsetX = std::stof(csvFileData[20][0]);

		// �L�����N�^�[���b���Ă��Ȃ����̉摜�̓����x�p�[�Z���e�[�W
		characterData.characterNotSpeakAlphaPercentage = std::stoi(csvFileData[21][0]);
		// �L�����N�^�[���b���Ă��Ȃ����̉摜���S����̋���
		characterData.characterNotSpeakCenterPosOffsetY = std::stof(csvFileData[22][0]);
		// �摜�ړ����x
		characterData.characterMoveSpeed = std::stof(csvFileData[23][0]);

	}

	// ���b�Z�[�W�E�B���h�E�f�[�^�̓ǂݍ���
	CSVMessageWindowData messageWindowData = CSVMessageWindowData();

	// ���b�Z�[�W�E�B���h�E�֘A
	{
		// ���b�Z�[�W�E�B���h�E�̉���
		messageWindowData.messageWindowWidth = std::stof(csvFileData[24][0]);

		// ��ʒ[����̃��b�Z�[�W�E�B���h�E�̋���
		messageWindowData.messageWindowMargin = std::stof(csvFileData[25][0]);

		// ��ʉ�����̃��b�Z�[�W�E�B���h�E�̋���
		messageWindowData.messageWindowPosOffsetY = std::stof(csvFileData[26][0]);
	}


	// �G���[�m�F
	{
		// �t�@�C���p�X
		const std::string filePath = textSettingDataFilePath;
		// �G���[���b�Z�[�W
		std::string errorMsg = "[" + filePath + "] ";


		// �t�H���g�f�[�^
		{
			// �t�H���g�t�@�C���p�X�̃T�C�Y
			const int fontFilePathSize = static_cast<int>(fontData.fontFilePath.size());
			// �t�H���g���̃T�C�Y
			const int fontNameSize = static_cast<int>(fontData.fontName.size());

			// �T�C�Y���Ⴄ�ꍇ�A�G���[���b�Z�[�W��\��
			if (fontFilePathSize != fontNameSize)
			{
				// �G���[���b�Z�[�W��\��
				EvoLib::Assert::ErrorMessageBox(errorMsg + "�e�L�X�g�ݒ�̃t�H���g�֘A�ł̐�����v���Ȃ��悤�ł��B");
			}
		}

		// �L�����N�^�[�f�[�^
		{
			// �L�����N�^�[�f�[�^�̃T�C�Y
			const int characterGraphFilePathSize = 
				static_cast<int>(characterData.characterFilePath.size());
			// �L�����N�^�[�f�[�^�̃T�C�Y
			const int characterNameSize = 
				static_cast<int>(characterData.characterName.size());
			// �摜�g�嗦�̃T�C�Y
			const int characterScaleSize = 
				static_cast<int>(characterData.characterScale.size());
			// �L�����N�^�[�̉��������̃T�C�Y
			const int characterSplitXSize = 
				static_cast<int>(characterData.characterSplitX.size());
			// �L�����N�^�[���E�������ǂ����̃T�C�Y
			const int characterIsRightSize = 
				static_cast<int>(characterData.characterIsRight.size());
			// �摜�̏㉺�����l�̃T�C�Y
			const int characterAdjustYSize = 
				static_cast<int>(characterData.characterAdjustY.size());
			// �摜�̍��E�����l�̃T�C�Y
			const int characterAdjustXSize = 
				static_cast<int>(characterData.characterAdjustX.size());

			// �T�C�Y���Ⴄ�ꍇ�A�G���[���b�Z�[�W��\��
			if (characterGraphFilePathSize != characterNameSize ||
				characterGraphFilePathSize != characterScaleSize ||
				characterGraphFilePathSize != characterSplitXSize ||
				characterGraphFilePathSize != characterIsRightSize ||
				characterGraphFilePathSize != characterAdjustYSize ||
				characterGraphFilePathSize != characterAdjustXSize)
			{
				// �G���[���b�Z�[�W��\��
				EvoLib::Assert::ErrorMessageBox(errorMsg + "�e�L�X�g�ݒ�̃L�����N�^�[�֘A�ł̐�����v���Ȃ��悤�ł��B");	
			}
		}
	}




	// �f�[�^���i�[
	m_loadData.fontData = fontData;
	m_loadData.characterData = characterData;
	m_loadData.messageWindowData = messageWindowData;
}

void MessageTextLoader::LoadTalkData(const std::string& talkDataCsvFilePath)
{
	


	// �e�L�X�g�ݒ�f�[�^�̓ǂݍ���
	std::vector<std::vector<std::string>> csvFileData =
		EvoLib::File::CsvFileLoading_Revision(talkDataCsvFilePath, true, 0);



	// �t�@�C���T�C�Y��1�ȉ��̏ꍇ�A�G���[���b�Z�[�W��\��
	if (static_cast<int>(csvFileData.size()) <= 1)
	{
		EvoLib::Assert::ErrorMessageBox("[" + talkDataCsvFilePath + "] " + "�ɂ̓f�[�^���Ȃ����A�f�t�H���g�̃f�[�^�������݂��Ȃ��悤�ł��B");
	}


	// �f�t�H���g�̃e�L�X�g�f�[�^
	CSVTakeData defaultTakeData = CSVTakeData();
	{
		// �b������
		defaultTakeData.talkText = csvFileData[0][0];

		// �b���L�����N�^�[�ԍ�
		defaultTakeData.talkCharacterNo = std::stoi(csvFileData[0][1]);

		// �L�����N�^�[�̕\��ԍ�
		defaultTakeData.talkFaceNo = std::stoi(csvFileData[0][2]);

		// �E�[�ɕ\�����邩�ǂ���
		defaultTakeData.isRight = EvoLib::Convert::ConvertStringToBool(csvFileData[0][3]);

		// ���]�`�悷�邩�ǂ���
		defaultTakeData.isFlip = EvoLib::Convert::ConvertStringToBool(csvFileData[0][4]);

		// �t�H���g�J���[
		{
			// �J���[�R�[�h�ɕϊ�
			const std::string color = "0x" + csvFileData[0][5];
			// �t�H���g�J���[
			defaultTakeData.fontColor = std::stoi(color, nullptr, 16);
		}

		// �t�H���g�̓����x
		defaultTakeData.fontAlpha = std::stoi(csvFileData[0][6]);

		// �t�H���g�̕����T�C�Y�^�C�v
		defaultTakeData.fontSizeType = std::stoi(csvFileData[0][7]);

		// ������k�킹�邩�ǂ���
		defaultTakeData.isShake = EvoLib::Convert::ConvertStringToBool(csvFileData[0][8]);

		// �ꕶ����\������̂ɂ�����t���[����
		defaultTakeData.drawCharFrame = std::stoi(csvFileData[0][9]);

		// �t�H���g�^�C�v
		defaultTakeData.fontType = std::stoi(csvFileData[0][10]);

		// �������Ԋu
		defaultTakeData.charInterval = std::stoi(csvFileData[0][11]);

		// �����c�Ԋu
		defaultTakeData.lineInterval = std::stof(csvFileData[0][12]);

		// �L�����N�^�[���J���[
		{
			// �J���[�R�[�h�ɕϊ�
			const std::string color = "0x" + csvFileData[0][13];

			// �L�����N�^�[���J���[
			defaultTakeData.characterNameColor = std::stoi(color, nullptr, 16);
		}
		// �L�����N�^�[��
		defaultTakeData.characterName = csvFileData[0][14].c_str();
	}

	std::vector<CSVTakeData> talkData;

	for (int i = 1; i < static_cast<int>(csvFileData.size()); i++)
	{
		// �e�L�X�g�f�[�^
		CSVTakeData tempTakeData = CSVTakeData();

		tempTakeData = defaultTakeData;

		// �t�@�C���T�C�Y�𒲂ׂ�
		const int size = static_cast<int>(csvFileData[i].size());

		
		// �b������
		if (!IsEmptyData(csvFileData[i][0]))
		{
			tempTakeData.talkText = csvFileData[i][0];
		}

		// �b���L�����N�^�[�ԍ�
		if (!IsEmptyData(csvFileData[i][1]))
		{
			tempTakeData.talkCharacterNo = std::stoi(csvFileData[i][1]);
		}

		// �L�����N�^�[�̕\��ԍ�
		if (!IsEmptyData(csvFileData[i][2]))
		{
			tempTakeData.talkFaceNo = std::stoi(csvFileData[i][2]);
		}

		// �E�[�ɕ\�����邩�ǂ���
		if (!IsEmptyData(csvFileData[i][3]))
		{
			tempTakeData.isRight = EvoLib::Convert::ConvertStringToBool(csvFileData[i][3]);
		}

		// ���]�`�悷�邩�ǂ���
		if (!IsEmptyData(csvFileData[i][4]))
		{
			tempTakeData.isFlip = EvoLib::Convert::ConvertStringToBool(csvFileData[i][4]);
		}

		// �t�H���g�J���[
		if (!IsEmptyData(csvFileData[i][5]))
		{
			// �J���[�R�[�h�ɕϊ�
			const std::string color = "0x" + csvFileData[i][5];

			tempTakeData.fontColor = std::stoi(color, nullptr, 16);
		}

		// �t�H���g�̓����x
		if (!IsEmptyData(csvFileData[i][6]))
		{
			tempTakeData.fontAlpha = std::stoi(csvFileData[i][6]);
		}

		// �t�H���g�̕����T�C�Y�^�C�v
		if (!IsEmptyData(csvFileData[i][7]))
		{
			tempTakeData.fontSizeType = std::stoi(csvFileData[i][7]);
		}

		// ������k�킹�邩�ǂ���
		if (!IsEmptyData(csvFileData[i][8]))
		{
			tempTakeData.isShake = EvoLib::Convert::ConvertStringToBool(csvFileData[i][8]);
		}

		// �ꕶ����\������̂ɂ�����t���[����
		if (!IsEmptyData(csvFileData[i][9]))
		{
			tempTakeData.drawCharFrame = std::stoi(csvFileData[i][9]);
		}

		// �t�H���g�^�C�v
		if (!IsEmptyData(csvFileData[i][10]))
		{
			tempTakeData.fontType = std::stoi(csvFileData[i][10]);
		}

		// �������Ԋu
		if (!IsEmptyData(csvFileData[i][11]))
		{
			tempTakeData.charInterval = std::stoi(csvFileData[i][11]);
		}

		// �����c�Ԋu
		if (!IsEmptyData(csvFileData[i][12]))
		{
			tempTakeData.lineInterval = std::stof(csvFileData[i][12]);
		}

		// �L�����N�^�[���J���[
		if (!IsEmptyData(csvFileData[i][13]))
		{
			// �J���[�R�[�h�ɕϊ�
			const std::string color = "0x" + csvFileData[i][13];

			tempTakeData.characterNameColor = std::stoi(color, nullptr, 16);
		}

		if (14 >= size)
		{
			// �L�����N�^�[��
			tempTakeData.characterName = m_loadData.characterData.characterName[tempTakeData.talkCharacterNo];
		}
		else
		{
			// �L�����N�^�[��
			if (!IsEmptyData(csvFileData[i][14]))
			{
				tempTakeData.characterName = csvFileData[i][14].c_str();
			}
			else
			{
				tempTakeData.characterName = m_loadData.characterData.characterName[tempTakeData.talkCharacterNo];
			}
		}

		// �f�[�^���i�[
		talkData.push_back(tempTakeData);
	}


	// �f�[�^���i�[
	m_loadData.talkData = talkData;
}

bool MessageTextLoader::IsEmptyData(const std::string& str)
{
	// �����񂪋󕶎��̏ꍇ�Atrue��Ԃ�
	if (str == "")
	{
		return true;
	}

	// �����񂪋󕶎��łȂ��ꍇ�Afalse��Ԃ�
	return false;
}
