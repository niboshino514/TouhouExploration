#pragma once
#include "EvoLib.h"

namespace EvoLib
{
	class File
	{

	public:

		// �ǂݎ��^�C�v
		enum class LoadType
		{
			Noramal,// �ʏ�
			SkipFirstLine,	// ��s�ڂ��X�L�b�v����
			SkipOneColumn,	// �e���ڂ��X�L�b�v����
			DoubleSkip,		// ��s�ڂƊe���ڂ��X�L�b�v����
		};


	private:

		/// <summary>
		/// ������𕪊����ĕԂ�
		static std::vector<std::string> Split(const std::string& input, const char& delimiter);

		/// ������𕪊����ĕԂ�
		static std::vector<std::wstring> SplitWString(const std::wstring& input, const wchar_t& delimiter);
		
	public:

		/// <summary>
		/// �t�@�C�������݂��邩�ǂ������m�F
		/// </summary>
		/// <param name="name">�t�@�C����</param>
		/// <returns>���̃t�@�C�������݂��邩�ǂ�����Ԃ�</returns>
		static bool IsFileExist(const std::string& name);

		/// <summary>
		/// CSV�t�@�C����ǂݍ���
		/// </summary>
		/// <param name="filePath">�t�@�C���p�X</param>
		/// <param name="isLoadFirstLine">�ŏ��̈�s��ǂݍ��ނ��ǂ���</param>
		/// <param name="isLoadOneColumn">�ŏ��̈���ǂݍ��ނ��ǂ���</param>
		/// <returns>�ǂݍ��񂾕������Ԃ�</returns>
		static std::vector<std::vector<std::string>> CsvFileLoading(const std::string& filePath, LoadType loadType = LoadType::Noramal);

		/// <summary>
		/// CSV�t�@�C����ǂݍ���(������)
		/// </summary>
		/// <param name="filePath">�t�@�C���p�X</param>
		/// <param name="isSkipOneArray">�ŏ��̈����΂����ǂ���</param>
		/// <param name="skipColumnNum">�e�񉽌܂Ŕ�΂����̐�</param>
		/// <param name="isDeleteEmptyCell">��̃Z�����폜���邩�ǂ���</param>
		/// <returns>�ǂݍ��񂾕������Ԃ�</returns>
		static std::vector<std::vector<std::string>> CsvFileLoading_Revision(const std::string& filePath, const bool& isSkipOneArray = false, const int& skipColumnNum = 0, const bool& isDeleteEmptyCell = false);

		/// <summary>
		/// �Ȉ�CSV�t�@�C����������
		/// </summary>
		/// <param name="fileName">�t�@�C����</param>
		/// <param name="writingText">�������ރe�L�X�g</param>
		static void SimpleCsvFileWriting(const std::string& fileName, const std::string& writingText);

		/// <summary>
		/// �o�C�i���t�@�C������������(�������\)���e�L�X�g�̏ꍇ�Achar[]�^�ɕϊ����Ă�������
		/// </summary>
		/// <typeparam name="T">struct</typeparam>
		/// <param name="filename">�������ރt�@�C����</param>
		/// <param name="data">�������ރf�[�^</param>
		template<typename T>
		static void WriteBinaryFile(const std::string& filename, const T& data);

		/// <summary>
		/// �o�C�i���t�@�C����ǂݍ��ށ��e�L�X�g�̏ꍇ�Achar[]�^�ł����ǂݍ��ގ����ł��܂���
		/// </summary>
		/// <typeparam name="T">struct</typeparam>
		/// <param name="filename">�ǂݍ��ރt�@�C����</param>
		/// <param name="data">�ǂݍ��ރf�[�^�֐�</param>
		template<typename T>
		static void ReadBinaryFile(const std::string& filename, T& data);
	};

	template<typename T>
	inline void File::WriteBinaryFile(const std::string& filename, const T& data)
	{
		std::ofstream outFile(filename, std::ios::binary);
		if (!outFile) {
			std::cerr << "�t�@�C�����J���܂���ł���: " << filename << std::endl;
			return;
		}
		outFile.write(reinterpret_cast<const char*>(&data), sizeof(T));
		outFile.close();
	}

	template<typename T>
	inline void File::ReadBinaryFile(const std::string& filename, T& data)
	{
		std::ifstream inFile(filename, std::ios::binary);
		if (!inFile) {
			std::cerr << "�t�@�C�����J���܂���ł���: " << filename << std::endl;
			return;
		}
		inFile.read(reinterpret_cast<char*>(&data), sizeof(T));
		inFile.close();
	}

}