#pragma once
#include "EvoLib.h"

namespace EvoLib
{
	class Draw
	{
	public:

		// ���[�v�̕���
		enum class LoopDirection
		{
			Up,		// ������Ƀ��[�v����
			Down,	// �������Ƀ��[�v����
			Left,	// �������Ƀ��[�v����
			Right,	// �E�����Ƀ��[�v����
		};


		struct Color
		{
			float r = 0.0f;
			float g = 0.0f;
			float b = 0.0f;
		};


	public:

		/// <summary>
		/// �ȈՔw�i�`��
		/// </summary>
		/// <param name="graphHandle">�摜�n���h��</param>
		/// <param name="screenSize">��ʃT�C�Y</param>
		/// <param name="isFlipImage">�摜�𔽓]���邩�ǂ���</param>
		static void DrawSimpleBackground(const int& graphHandle, const Vec2& screenSize, bool isFlipImage = false);

		/// <summary>
		/// �ȈՔw�i���[�v
		/// </summary>
		/// <param name="graphHandle">�O���t�B�b�N�̃n���h��</param>
		/// <param name="currentFrame">���݂̈ړ���</param>
		/// <param name="moveSpeed">�w�i�̈ړ��X�s�[�h</param>
		/// <param name="screenSize">��ʃT�C�Y</param>
		/// <param name="isSupportedImageInLoop">�g�p����摜�����[�v�ɑΉ����Ă��邩�ǂ���</param>
		/// <param name="loopDirection">���[�v�������</param>
		/// <returns>���݂̈ړ��ʂ�Ԃ�</returns>
		static float SimpleLoopBackground(const int& graphHandle, const float currentMoveValue, float moveSpeed, const Vec2 screenSize, bool isSupportedImageInLoop = false, LoopDirection loopDirection = LoopDirection::Left);

		/// <summary>
		/// 2D�O���t�B�b�N��3D��Ԃɕ`�悷��@��graphHandle �Ŏw�肷��摜�͂W�ȏ�̂Q�̂���̃s�N�Z���T�C�Y�ł���K�v������܂�
		/// </summary>
		/// <param name="graphHandle">�O���t�B�b�N�̃n���h��</param>
		/// <param name="graphScale">�O���t�B�b�N�̃X�P�[��</param>
		/// <param name="angle">�p�x</param>
		/// <param name="pos">���W</param>
		/// <param name="color">�J���[�̒l(�ő�l:1.0f)</param>
		static void DrawGprah3D_EvoLib(const int& graphHandle, const float& graphScale, const VECTOR& angle, const VECTOR& pos, Color color = { 1.0f,1.0f,1.0f });

		/// <summary>
		/// 3D��ԂɃL���[�u��`�悷��
		/// </summary>
		/// <param name="centerPos">���S���W</param>
		/// <param name="cubeScale">��ӂ̒���</param>
		/// <param name="alphaValue">�����x</param>
		/// <param name="lineThickness">���̑���</param>
		/// <param name="color">�J���[�̒l(�ő�l:1.0f)</param>
		static void DrawCube3D_EvoLib(const VECTOR& centerPos, const VECTOR& oneSideLength, int alphaValue = 255, int lineThickness = 1, Color color = { 0.0f,1.0f, 0.0f });


		/// <summary>
		/// �c�Ɖ��ɉ�]����O���t�B�b�N��`�悷��
		/// </summary>
		/// <param name="handle">�O���t�B�b�N�n���h��</param>
		/// <param name="pos">���S���W</param>
		/// <param name="frameSpeed">�t���[���X�s�[�h</param>
		/// <param name="isHorizontalRot">����]</param>
		/// <param name="graphRota">�摜�g�嗦(�f�t�H���g 1.0f)</param>
		/// <param name="isRotateOne">���]�����邩�ǂ���</param>
		/// <param name="isReverseGraph">�摜�𔽓]������</param>
		/// <param name="isTrans">�摜�𓧉߂�����</param>
		/// <param name="isUpdate">�X�V���邩�ǂ���</param>
		static void DrawRotatingImage(const int& handle, const Vec2& pos, const int& frameSpeed, const bool& isHorizontalRot, const float& graphRota = 1.0f, const bool& isRotateOne = true, const bool& isReverseGraph = false, const bool& isTrans = true, const bool& isUpdate = true);

	};
}
