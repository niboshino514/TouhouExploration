#include "GameData.h"

// �V���O���g��
GameData* GameData::m_pInstance = nullptr;

namespace
{
	// �Z�[�u�f�[�^�t�@�C����
	static const std::string kSaveDataFileName = "Data/Save/SaveData.dat";

	// �X�R�A�f�[�^�t�@�C����
	static const std::string kScoreDataFileName = "Data/Save/ScoreData.dat";
}

void GameData::LoadSaveData()
{
	// �t�@�C�������݂��邩�ǂ������m�F���A���݂��Ȃ��ꍇ�͐V�K�쐬
	if (!EvoLib::File::IsFileExist(kSaveDataFileName))
	{
		// �Z�[�u�f�[�^����������
		EvoLib::File::WriteBinaryFile<SaveData>(kSaveDataFileName, SaveData());

		return;
	}
	
	// dat�t�@�C���̓ǂݍ���
	EvoLib::File::ReadBinaryFile<SaveData>(kSaveDataFileName, m_saveData);
}

void GameData::WriteSaveData()
{
	// �Z�[�u�f�[�^����������
	EvoLib::File::WriteBinaryFile<SaveData>(kSaveDataFileName, m_saveData);
}

void GameData::InitSaveData()
{
	// �Z�[�u�f�[�^�̏�����
	m_saveData = SaveData();

}

void GameData::LoadScoreData()
{
	// �t�@�C�������݂��邩�ǂ������m�F���A���݂��Ȃ��ꍇ�͐V�K�쐬
	if (!EvoLib::File::IsFileExist(kScoreDataFileName))
	{
		// �X�R�A�f�[�^����������
		EvoLib::File::WriteBinaryFile<ScoreData>(kScoreDataFileName, ScoreData());

		return;
	}

	// dat�t�@�C���̓ǂݍ���
	EvoLib::File::ReadBinaryFile<ScoreData>(kScoreDataFileName, m_scoreData);
}

void GameData::WriteScoreData()
{
	// �X�R�A�f�[�^����������
	EvoLib::File::WriteBinaryFile<ScoreData>(kScoreDataFileName, m_scoreData);
}

void GameData::SetScoreData()
{
	// �X�R�A�f�[�^��ݒ�
	m_scoreData.isClear = true;
	m_scoreData.clearTime = m_saveData.time;
	m_scoreData.deathCount = m_saveData.playerStatus.deathCount;
}

void GameData::SetSavePointData(const int& stageNumber, const Cell& cell, const PlayerStatus& playerStatus)
{
	// �Z�[�u�|�C���g�f�[�^��ݒ�
	m_saveData.stageNumber = stageNumber;
	m_saveData.cell = cell;
	m_saveData.playerStatus = playerStatus;
}

bool GameData::IsNewRecord()
{
	// �������^�C��
	Time initTime = Time();

	// �X�R�A�f�[�^�������l�̏ꍇ�A�V�L�^�Ƃ���
	if (m_scoreData.clearTime.hour == initTime.hour&&
		m_scoreData.clearTime.minute== initTime.minute&&
		m_scoreData.clearTime.second == initTime.second&&
		m_scoreData.clearTime.millisecond == initTime.millisecond)
	{
		return true;
	}
	
	bool isTime = false;

	// ���Ԃ̔�r
	if (m_saveData.time.hour < m_scoreData.clearTime.hour ||
		(m_saveData.time.hour == m_scoreData.clearTime.hour && m_saveData.time.minute < m_scoreData.clearTime.minute) ||
		(m_saveData.time.hour == m_scoreData.clearTime.hour && m_saveData.time.minute == m_scoreData.clearTime.minute && m_saveData.time.second < m_scoreData.clearTime.second) ||
		(m_saveData.time.hour == m_scoreData.clearTime.hour && m_saveData.time.minute == m_scoreData.clearTime.minute && m_saveData.time.second == m_scoreData.clearTime.second && m_saveData.time.millisecond <= m_scoreData.clearTime.millisecond))
	{
		isTime = true;
	}




	bool isDeathCount = false;

	// �Z�[�u�f�[�^�̃f�X�J�E���g���X�R�A�f�[�^�̃f�X�J�E���g�������Ȃ��ꍇ�A�V�L�^�Ƃ���
	if(m_saveData.playerStatus.deathCount <= m_scoreData.deathCount)
	{
		isDeathCount = true;
	}


	if(isTime && isDeathCount)
	{
		return true;
	}


	return false;
}

void GameData::TimeCount()
{
	// �~���b
	{
		// �~���b�����Z
		m_saveData.time.millisecond++;

		// 60�J�E���g�ȏ�Ȃ�Εb�����Z���A�~���b�����Z�b�g
		if (IsTimeCount60(m_saveData.time.millisecond))
		{
			// �b�����Z
			m_saveData.time.second++;

			// �~���b�����Z�b�g
			m_saveData.time.millisecond = 0;
		}
	}

	// �b
	{
		// 60�J�E���g�ȏ�Ȃ�Ε������Z���A�b�����Z�b�g
		if (IsTimeCount60(m_saveData.time.second))
		{
			// �������Z
			m_saveData.time.minute++;

			// �b�����Z�b�g
			m_saveData.time.second = 0;
		}
	}

	// ��
	{
		// 60�J�E���g�ȏ�Ȃ�Ύ��Ԃ����Z���A�������Z�b�g
		if (IsTimeCount60(m_saveData.time.minute))
		{
			// ���Ԃ����Z
			m_saveData.time.hour++;

			// ���Ԃ�99�ȏ�Ȃ��99�ɐݒ�
			if(m_saveData.time.hour >= 99)
			{
				m_saveData.time.hour = 99;
			}


			// �������Z�b�g
			m_saveData.time.minute = 0;
		}
	}

}

bool GameData::IsTimeCount60(const int& count)
{
	// 60�J�E���g�ȏ�Ȃ�΁Atrue��Ԃ�
	if (count >= 60)
	{
		return true;
	}

	return false;
}

GameData::Score GameData::CalcScore(const Time& time, const int& deathCount)
{
	// �X�R�A�f�[�^
	GameData::Score score = Score();

	// �X�R�A�^�C���v�Z
	{
		
		// �����_�ȉ�
		{
			score.time[7] = time.millisecond % 10;
			score.time[6] = (time.millisecond / 10) % 10;
		}
		
		// �b
		{
			score.time[5] = time.second % 10;
			score.time[4] = (time.second / 10) % 10;
		}

		// ��
		{
			score.time[3] = time.minute % 10;
			score.time[2] = (time.minute / 10) % 10;
		}

		// ����
		{
			score.time[1] = time.hour % 10;
			score.time[0] = (time.hour / 10) % 10;
		}
	}

	// �X�R�A�f�X�J�E���g�v�Z
	{
		// ��̈�
		{
			score.deathCount[3] = deathCount % 10;
		}

		// �\�̈�
		{
			score.deathCount[2] = (deathCount / 10) % 10;
		}

		// �S�̈�
		{
			score.deathCount[1] = (deathCount / 100) % 10;
		}

		// ��̈�
		{
			score.deathCount[0] = (deathCount / 1000) % 10;
		}

	}


	// �X�R�A��Ԃ�
	return score;
}

