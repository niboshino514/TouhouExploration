#pragma once
#include <string>
#include <vector>
#include <string>
#include <map>

// �V���O���g�����g�p�����T�E���h�N���X
class Sound
{

private:
	Sound() = default;
	virtual ~Sound() = default;

	static Sound* m_pInstance;

public:
	// �R�s�[�R���X�g���N�^�̋֎~
	Sound(const Sound&) = delete;
	Sound& operator=(const Sound&) = delete;
	Sound(Sound&&) = delete;
	Sound& operator=(Sound&&) = delete;

	static Sound* GetInstance()
	{
		if (m_pInstance == nullptr)
		{
			m_pInstance = new Sound();
		}
		return m_pInstance;
	}
	static void DeleteInstance()
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}

public:

	// �T�E���h�^�C�v���
	enum class SoundType
	{
		BGM,// BGM
		SE,	// SE
	};

private:

	// �t�@�C��
	enum class File
	{
		FileName,		// �t�@�C����
		FileExtension,	// �g���q
		SoundType,		// �T�E���h�̃^�C�v
		SoundVolume,	// �T�E���h�̉���
	};

	// �T�E���h�f�[�^
	struct SoundData
	{
		SoundType soundType = SoundType();	// �T�E���h�^�C�v
		float volRate = 0.0f;				// �{�����[������
		int maxVolume = 0;					// �ő�{�����[��
		int soundVolume = 0;				// �T�E���h�{�����[��
		int settingSoundVolume = 0;			// �ݒ肵���T�E���h�{�����[��
		int handle = -1;					// �T�E���h�n���h��
		std::string filePath;				// �t�@�C���p�X
	};

	// �T�E���h�{�����[��
	struct SoundVolume
	{
		int bgm = 100;// BGM�{�����[��
		int se = 100;	// SE�{�����[��
	};

public:
	// ��������
	void Init();

	// sting�ɉ���������Ă��Ȃ����ǂ����̔���
	bool IsEmpty(const std::string& str);


	/// <summary>
	/// �T�E���h���[�h
	/// </summary>
	/// <param name="fileName">�t�@�C����</param>
	/// <param name="ASyncLoad">�񓯊��������s�����ǂ���</param>
	void Load(const std::vector<std::string>& fileName, const bool& ASyncLoad = false);

	/// <summary>
	/// �T�E���h�A�����[�h
	/// </summary>
	void UnLoad();

	/// <summary>
	/// �Đ�
	/// </summary>
	/// <param name="filename">�t�@�C����</param>
	void Play(const std::string& filename);

	/// <summary>
	/// ��ʂ̃t�F�[�h�ɍ��킹��BGM������
	/// </summary>
	/// <param name="fadeValue">�����������FadeBrightValue()</param>
	void ScreenFadeBGMStop(const int& fadeValue);

	/// <summary>
	/// �T�E���h���ʐݒ�
	/// </summary>
	/// <param name="soundType">�T�E���h�^�C�v</param>
	/// <param name="soundPercentVolume">�T�E���h�p�[�Z���g�{�����[��</param>
	void SetSoundVolume(const SoundType& soundType, const int& soundPercentVolume);

	/// <summary>
	/// �T�E���h���ʎ擾
	/// </summary>
	/// <returns>�T�E���h���ʂ�Ԃ�</returns>
	SoundVolume GetSoundVolume() const { return m_soundPercentVolume; }

private:

	// �����f�[�^
	std::map<std::string, SoundData> m_soundData;

	// �T�E���h�p�[�Z���g�{�����[��
	SoundVolume m_soundPercentVolume;
};