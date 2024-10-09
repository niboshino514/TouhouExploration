#pragma once
#include "EvoLib.h"


namespace EvoLib
{
	class Load
	{

	public:
		// ������
		struct DivNum
		{
			// ���̕�����
			const int x = 1;
			// �c�̕�����
			const int y = 1;
		};


		// �O���t�B�b�N���
		struct GraphicInfo
		{
			// �t�@�C���p�X
			const char* filePath = "";

			// ���W
			Vec2 pos = Vec2(0.0f, 0.0f);

			// �O���t�B�b�N�X�P�[��
			double scale = 1.0;

			// �O���t�B�b�N�̕�����
			DivNum div = DivNum();
		};


		// �O���t�B�b�N�������(���o�[�W����)
		struct DivGraphInfo_Old_Type
		{
			// �n���h��
			std::vector<int>handle;

			// �O���t�B�b�N�̃X�P�[��
			Vec2 scale = Vec2(0.0f, 0.0f);
		};

		// �O���t�B�b�N�������
		struct DivGraphInfo
		{
			// �n���h��
			std::vector<int> handle;

			// ���W
			std::vector<Vec2> pos;

			// �X�P�[��
			std::vector<double> scale;
		};

	public:

		/// <summary>
		/// �O���t�B�b�N�̓ǂݍ���
		/// </summary>
		/// <param name="filePath">�O���t�B�b�N�̃t�@�C���p�X</param>
		/// <returns>���[�h�����O���t�B�b�N�n���h��</returns>
		static int LoadGraph_EvoLib(const char* filePath);

		/// <summary>
		/// �O���t�B�b�N�̕���
		/// </summary>
		/// <param name="filePath">�O���t�B�b�N�̃t�@�C���p�X</param>
		/// <param name="div_x">�������ɑ΂��镪����</param>
		/// <param name="div_y">�c�����ɑ΂��镪����</param>
		/// <returns></returns>
		static DivGraphInfo_Old_Type LoadDivGraph_EvoLib(const char* filePath, const int& div_x, const int& div_y);

		/// <summary>
		/// �O���t�B�b�N�̕����@�����
		/// </summary>
		/// <param name="filePath">�O���t�B�b�N�̃t�@�C���p�X</param>
		/// <param name="div">�c���̕�����</param>
		/// <returns>�������ꂽ�O���t�B�b�N�n���h����Ԃ�</returns>
		static std::vector<int> LoadDivGraph_EvoLib_Revision(const char* filePath, const DivNum& div);


		/// <summary>
		/// �t�H���g�̓ǂݍ���
		/// </summary>
		/// <param name="filePath">�t�H���g�t�@�C���p�X</param>
		/// <param name="fontName">�t�H���g��</param>
		/// <param name="fontSize">�t�H���g�T�C�Y</param>
		/// <returns>�t�H���g���</returns>
		static int LoadFont(const char* filePath, const char* fontName, const int& fontSize);


	};
}