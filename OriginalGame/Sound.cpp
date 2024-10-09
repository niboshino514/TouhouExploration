#include "Sound.h"
#include "EvoLib.h"
#include <sstream>
Sound* Sound::m_pInstance = nullptr;

namespace 
{
	// �T�E���h�̃t�@�C���p�X
	const std::string  kDataFilePaht = "Data/Sound/";

	// �T�E���h�f�[�^�̃t�@�C���p�X
	const std::string kSoundDataFilePath = "Data/Csv/Sound.csv";

	// �T�E���h�̍ő�l
	const int kSoundMaxValue = 255;

}

void Sound::Init()
{

	// �T�E���h�̏�����
	m_soundPercentVolume = SoundVolume();

	// �T�E���h�f�[�^�̓ǂݍ���
	const std::vector<std::vector<std::string>> loadData = 
		EvoLib::File::CsvFileLoading(kSoundDataFilePath, EvoLib::File::LoadType::SkipFirstLine);
	

	// �f�t�H���g�f�[�^
	SoundData defoultData;

	// �f�t�H���g�g���q��
	std::string defoultExtension;;


	// �T�E���h�f�[�^�̃f�t�H���g�ǂݍ���
	{
		// �t�@�C����
		const std::string fileName = loadData[0][0];

		// �g���q��
		defoultExtension = loadData[0][1];


			// �t�@�C�����Ɗg���q������
		defoultData.filePath = kDataFilePaht + fileName + defoultExtension;
		

		// �T�E���h�^�C�v
		if(loadData[0][2] == "BGM")
		{
			defoultData.soundType = SoundType::BGM;
		}
		else
		{
			defoultData.soundType = SoundType::SE;
		}

		// �{�����[������
		defoultData.volRate = std::stof(loadData[0][3]);

		// �ő�{�����[��
		defoultData.maxVolume = EvoLib::Convert::ConvertValueToPercent(kSoundMaxValue, defoultData.volRate);

		// �ő�{�����[�����{�����[���ɑ��
		defoultData.soundVolume = defoultData.maxVolume;

		// �{�����[����ݒ�{�����[���ɑ��
		defoultData.settingSoundVolume = defoultData.soundVolume;

		// �n���h���̏�����
		defoultData.handle = -1;
	}



	// �T�E���h�f�[�^�̓ǂݍ���
	{
		// �T�E���h�f�[�^�̃T�C�Y
		const int soundDataSize = static_cast<int>(loadData.size());


		for (int i = 1; i < soundDataSize; i++)
		{
			// �ꎞ�ۑ��f�[�^
			SoundData tempData;


			
			// �t�@�C����
			const std::string fileName = loadData[i][0];


			// �g���q��
			std::string extension = loadData[i][1];

			// �g���q������̏ꍇ�A�f�t�H���g�̊g���q������
			if (IsEmpty(loadData[i][1]))
			{
				extension = defoultExtension;
			}


			// �t�@�C�����Ɗg���q������
			tempData.filePath = kDataFilePaht + fileName + extension;
			
			// �T�E���h�^�C�v
			if(!IsEmpty(loadData[i][2]))
			{
				if (loadData[i][2] == "BGM")
				{
					tempData.soundType = SoundType::BGM;
				}
				else
				{
					tempData.soundType = SoundType::SE;
				}
			}
			else
			{
				// �f�t�H���g�̃T�E���h�^�C�v����
				tempData.soundType = defoultData.soundType;
			}
			


			// �{�����[������
			if (loadData[i].size() != 4)
			{
				// �f�t�H���g�̃{�����[����������
				tempData.volRate = defoultData.volRate;

			}
			else
			{
				if (!IsEmpty(loadData[i][3]))
				{
					tempData.volRate = std::stof(loadData[i][3]);
				}
				else
				{
					// �f�t�H���g�̃{�����[����������
					tempData.volRate = defoultData.volRate;
				}
			}

	
			
		

			// �ő�{�����[��
			tempData.maxVolume = EvoLib::Convert::ConvertValueToPercent(kSoundMaxValue, tempData.volRate);

			// �ő�{�����[�����{�����[���ɑ��
			tempData.soundVolume = tempData.maxVolume;

			// �{�����[����ݒ�{�����[���ɑ��
			tempData.settingSoundVolume = tempData.soundVolume;

			// �n���h���̏�����
			tempData.handle = -1;


			// �T�E���h�f�[�^�̒ǉ�
			m_soundData[fileName] = tempData;
		}

	}
}

bool Sound::IsEmpty(const std::string& str)
{
	if(str == "")
	{
		return true;
	}

	return false;
}

void Sound::Load(const std::vector<std::string>& fileName, const bool& ASyncLoad)
{
	// �񓯊��������s�����ǂ���
	if (ASyncLoad)
	{
		// ���\�[�X�̓ǂݍ���
		SetUseASyncLoadFlag(true);	// �񓯊��ǂݍ��݂��s������
	}

	// �T�E���h�̓ǂݍ���
	for (auto& file : fileName)
	{

		if(!EvoLib::File::IsFileExist(m_soundData[file].filePath))
		{
			EvoLib::Assert::ErrorMessageBox(m_soundData[file].filePath + "�����݂��Ȃ��悤�ł��B");
		}


		// �n���h����������
		m_soundData[file].handle = LoadSoundMem(m_soundData[file].filePath.c_str());

		// ���ʂ�������
		m_soundData[file].soundVolume = m_soundData[file].settingSoundVolume;

		// ���ʐݒ�
		ChangeVolumeSoundMem(m_soundData[file].soundVolume, m_soundData[file].handle);
	}

	// ���\�[�X�̓ǂݍ���
	SetUseASyncLoadFlag(false);	// �f�t�H���g�ɖ߂��Ă���
}

void Sound::UnLoad()
{
	// ���ׂẴn���h�����폜
	InitSoundMem();
}

void Sound::Play(const std::string& filename)
{
	// �T�E���h�̃v���C�^�C�v
	int playType = 0;

	if (m_soundData[filename].soundType == SoundType::BGM)
	{
		playType = DX_PLAYTYPE_LOOP;
	}
	else
	{
		playType = DX_PLAYTYPE_BACK;
	}

	// ���ʐݒ�
	ChangeVolumeSoundMem(m_soundData[filename].soundVolume, m_soundData[filename].handle);

	// �T�E���h��炷
	PlaySoundMem(m_soundData[filename].handle, playType);
}

void Sound::ScreenFadeBGMStop(const int& fadeValue)
{
	// �t�F�[�h�̍ő�l
	const int fadeMaxValue = 255;

	// �t�F�[�h�l�̌v�Z
	const int fadeValueReverse = fadeMaxValue - fadeValue;

	// �t�F�[�h�l��S�����Ōv�Z
	const int fadePercent = EvoLib::Convert::PercentageRate(static_cast<float>(fadeMaxValue), static_cast<float>(fadeValueReverse));

	// �T�E���h�̓ǂݍ���
	for (auto& data : m_soundData)
	{
		// BGM�łȂ������ꍇ�A�R���e�B�j���[����
		if(data.second.soundType != SoundType::BGM)
		{
			continue;
		}

		// �T�E���h�{�����[�������߂�
		data.second.soundVolume = EvoLib::Convert::ConvertFromPercentToValue(data.second.settingSoundVolume, static_cast<float>(fadePercent));

		// ���ʐݒ�
		ChangeVolumeSoundMem(data.second.soundVolume, data.second.handle);
	}
}

void Sound::SetSoundVolume(const SoundType& soundType, const int& soundPercentVolume)
{
	
	// �T�E���h�̉��ʂ�������
	switch (soundType)
	{
	case Sound::SoundType::BGM:

		// �T�E���h�̉��ʂ�������
		m_soundPercentVolume.bgm = soundPercentVolume;

		break;
	case Sound::SoundType::SE:

		// �T�E���h�̉��ʂ�������
		m_soundPercentVolume.se = soundPercentVolume;

		break;
	default:
		// �T�E���h�̉��ʂ�������
		m_soundPercentVolume.bgm = soundPercentVolume;
		break;
	}


	// �T�E���h�̓ǂݍ���
	for (auto& data : m_soundData)
	{
		// �T�E���h�^�C�v���قȂ�ꍇ�Ac:ontinue����
		if (data.second.soundType != soundType)
		{
			continue;
		}

		// �T�E���h���ʂ𒲂ׂ�
		const int soundVolume = EvoLib::Convert::ConvertFromPercentToValue(data.second.maxVolume, static_cast<float>(soundPercentVolume));

		// �ݒ�{�����[���ɒ��ׂ��T�E���h�{�����[����������
		data.second.settingSoundVolume = soundVolume;

		// �{�����[���ɐݒ�{�����[����������
		data.second.soundVolume = data.second.settingSoundVolume;

		// ���ʐݒ�
		ChangeVolumeSoundMem(data.second.soundVolume, data.second.handle);
	}
}
