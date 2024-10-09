#pragma once
#include "EvoLib.h"


namespace EvoLib
{
	// �ϊ��N���X
	class Convert
	{
	public:

		// �����ɑΉ������p�x
		static constexpr float TopAngle = 270.0f;	// ��
		static constexpr float BottomAngle = 90.0f;	// ��
		static constexpr float LeftAngle = 180.0f;	// ��
		static constexpr float RightAngle = 0.0f;	// �E

	public:

		/// <summary>
		/// �J���[��255�ɕϊ�
		/// </summary>
		/// <param name="color"></param>
		/// <returns>255�ϊ����ꂽ�J���[�l��Ԃ�</returns>
		static VECTOR ConvertColorInto255(const VECTOR& color);

		/// <summary>
		/// �ő�l�ƕϊ��l���g���A�p�[�Z���g�����߂�
		/// </summary>
		/// <param name="maxValue">�ő�l</param>
		/// <param name="convertValue">�ϊ��l</param>
		/// <returns>�p�[�Z���e�[�W</returns>
		static int PercentageRate(const float& maxValue, const float& convertValue);


		/// <summary>
		/// �l���p�[�Z���g�ϊ�
		/// </summary>
		/// <param name="maxValue">�ő�l</param>
		/// <param name="percentage">�p�[�Z���g</param>
		/// <returns>�p�[�Z���e�[�W</returns>
		static int ConvertValueToPercent(const int& maxValue, const float& percentage);


		/// <summary>
		/// �p�[�Z���g����l�ɕϊ�
		/// </summary>
		/// <param name="maxValue">�ő�l</param>
		/// <param name="percentage">�p�[�Z���g</param>
		/// <returns>�ϊ����ꂽ�l</returns>
		static int ConvertFromPercentToValue(const int& maxValue, const float& percentage);


		/// <summary>
		/// �p�x�����W�A���ɕϊ�
		/// </summary>
		/// <param name="angle">�p�x</param>
		/// <returns>�ϊ��������W�A����Ԃ�</returns>
		static float ConvertAngleToRadian(const float& angle);


		/// <summary>
		/// ���W�A�����p�x�ɕϊ�
		/// </summary>
		/// <param name="radian">���W�A��</param>
		/// <returns>�ϊ������p�x��Ԃ�</returns>
		static float ConvertRadianToAngle(const float& radian);


		/// <summary>
		/// ���������p�x�ɕϊ�
		/// </summary>
		/// <param name="direction">����</param>
		/// <returns>�p�x</returns>
		static float ConvertDirectionToAngle(const Direction& direction);


		/// <summary>
		/// �p�x����������ɕϊ�
		/// </summary>
		/// <param name="angle">�p�x</param>
		/// <param name="addSubValue">�����l</param>
		/// <returns>�������</returns>
		static Direction ConvertAngleToDirection(const float& angle, const float addSubValue = 0.0f);


		/// <summary>
		/// �t���[����b�ɕϊ�
		/// </summary>
		/// <param name="frame">�t���[��</param>
		/// <param name="fps">FPS</param>
		/// <returns>�b</returns>
		static int ConvertFrameToSeconds(const int& frame, const int& fps = 0);

		/// <summary>
		/// �t���[����b�ɕϊ�(������)
		/// </summary>
		/// <param name="frame">�t���[��</param>
		/// <param name="isInteger">�����l��Ԃ����ǂ���</param>
		/// <param name="fps">FPS</param>
		/// <returns>�ϊ����ꂽ�b����Ԃ�</returns>
		static float ConvertFrameToSeconds_Revision(const int& frame, bool isInteger = true, int fps = 0);


		/// <summary>
		/// �����֕ϊ�
		/// </summary>
		/// <param name="pos">���W</param>
		/// <param name="radius">���a</param>
		/// <returns>�����</returns>
		static Sphere ConvertSphereInfo(const VECTOR& pos, const float& radius);


		/// <summary>
		/// string�^����float�^�ɕϊ�
		/// </summary>
		/// <param name="num">string�^�̐���</param>
		/// <returns>float�^�̐���</returns>
		static float ConvertingStringToFloat(const std::string& stringNum);

		/// <summary>
		/// float�^����string�^�ɕϊ�
		/// </summary>
		/// <param name="num">float�^�̐���</param>
		/// <returns>string�^�̐���</returns>
		static std::string ConvertingFloatToString(const float& num);

		/// <summary>
		/// �t���[�����~���b�P�ʂɕϊ�
		/// </summary>
		/// <param name="frame">�t���[��</param>
		/// <returns>�~���b�P�ʂ�Ԃ�</returns>
		static int ConvertFrameCountToMillisecondUnit(const int& frame);


		/// <summary>
		/// ���W���Z���ɕϊ�
		/// </summary>
		/// <param name="pos">���W</param>
		/// <param name="cellSize">�Z���T�C�Y</param>
		/// <returns>�Z�����</returns>
		static Cell PosToCell(const Vec2& pos, const float& cellSize);

		/// <summary>
		/// �Z�������W�ɕϊ�
		/// </summary>
		/// <param name="cell">�Z��</param>
		/// <param name="cellSize">�Z���T�C�Y</param>
		/// <returns></returns>
		static Vec2 CellToPos(const Cell& cell, const float& cellSize);

		/// <summary>
		/// 2�_�̍��W���璼���̌X����Y���̌�_�����߂�
		/// </summary>
		/// <param name="pos1">���W1</param>
		/// <param name="pos2">���W2</param>
		/// <returns>�������</returns>
		static Line CalculateLine(const Vec2& pos1, const Vec2& pos2);

		/// <summary>
		/// 2�̒�����_���v�Z����
		/// </summary>
		/// <param name="line1">����1</param>
		/// <param name="line2">����2</param>
		/// <returns>�������(�d�Ȃ��Ă��邩�ǂ����̃t���O,�d�Ȃ��Ă�����W)</returns>
		static Intersection CalculateIntersection(const Line& line1, const Line& line2);

		/// <summary>
		/// �l�p�`��񂩂璆�S���W�����߂�
		/// </summary>
		/// <param name="square">�l�p�`���W</param>
		/// <returns>�l�p�`���</returns>
		static Vec2 QuadrangularCenter(const Square& square);

		/// <summary>
		/// �l�p�`�̒��S�_����сA���S�_����̊e���_�����̍ő�l�𔼌a�Ƃ����~�̏���Ԃ�
		/// </summary>
		/// <param name="square">�l�p�`���</param>
		/// <returns>�~���</returns>
		static Circle SquareToCircle(const Square& square);

		/// <summary>
		/// ��`�����l�p�`���ɕϊ�����
		/// </summary>
		/// <param name="rect">��`���</param>
		/// <returns>�l�p�`���</returns>
		static Square RectToSquare(const Rect& rect);


		/// <summary>
		/// ���W�𒆐S�Ƃ�����`���ɕϊ�
		/// </summary>
		/// <param name="pos">���S���W</param>
		/// <param name="size">�T�C�Y</param>
		/// <returns>��`���</returns>
		static Rect PosToRect(const Vec2& pos, const Vec2& size);

		/// <summary>
		/// string�^�̐^���l��bool�^�ɕϊ�
		/// </summary>
		/// <param name="str">string�^�̐^���l</param>
		/// <returns>bool�^�̐^���l</returns>
		static bool ConvertStringToBool(const std::string& str);

		/// <summary>
		/// wstring�^��string�^�ɕϊ�
		/// </summary>
		/// <param name="wstr">wstring�^�̕���</param>
		/// <returns>string�^�ɕϊ����ꂽ����</returns>
		static std::string WStringToString(const std::wstring& wstr);

		/// <summary>
		/// string�^��wstring�^�ɕϊ�
		/// </summary>
		/// <param name="str">string�^�̕���</param>
		/// <returns>wstring�^�ɕϊ����ꂽ����</returns>
		static std::wstring StringToWString(const std::string& str);

	};
}




