#pragma once
#include "EvoLib.h"

namespace EvoLib
{
	// �Փ˃N���X
	class Collision
	{
	public:

		/// <summary>
		/// ���̏Փ˔���
		/// </summary>
		/// <param name="sphere1">�����1</param>
		/// <param name="sphere2">�����2</param>
		/// <returns>�Փ˂������ǂ�����Ԃ�</returns>
		static bool SphereCollision(const Sphere& sphere1, const Sphere& sphere2);


		/// <summary>
		/// �~�Ǝl�p�`�Ƃ̓����蔻��
		/// </summary>
		/// <param name="circle">�~���</param>
		/// <param name="square">�l�p�`���</param>
		/// <returns>�~�Ǝl�p�`�������������ǂ�����Ԃ�</returns>
		static bool IsAABBCollisionDetection(const Circle& circle, const Square& square);

		/// <summary>
		/// �~���m�̓����蔻��
		/// </summary>
		/// <param name="circle1">�~���1</param>
		/// <param name="circle2">�~���2</param>
		/// <returns>�~���m�̏Փ˔���t���O</returns>
		static bool IsCircleToCircle(const Circle& circle1, const Circle& circle2);

		/// <summary>
		/// �O�p�`�Ǝl�p�`�̓����蔻��
		/// </summary>
		/// <param name="triangle">�O�p�`���</param>
		/// <param name="square">�l�p�`���</param>
		/// <returns>�O�p�`�Ǝl�p�`�̏Փ˔���t���O</returns>
		static bool IsTriangleToSquare(const Triangle& triangle, const Square& square);

		/// <summary>
		/// �l�p�`���m�̓����蔻��
		/// </summary>
		/// <param name="square1">�l�p�`1</param>
		/// <param name="square2">�l�p�`2</param>
		/// <returns>�l�p�`���m�̏Փ˔���t���O</returns>
		static bool IsSquareToSquare(const Square& square1, const Square& square2);

		/// <summary>
		/// �������m���������Ă��邩�ǂ����𒲂ׂ�
		/// </summary>
		/// <param name="line1">����1</param>
		/// <param name="line2">�����Q</param>
		/// <returns>�������m�̏Փ˔���t���O</returns>
		static bool IsLineToLine(const Line& line1, const Line& line2);

		/// <summary>
		/// �|���S���̒��Ƀ|�C���g���W�������Ă��邩�ǂ����𒲂ׂ�
		/// </summary>
		/// <param name="point">���W</param>
		/// <param name="polygon">�|���S��</param>
		/// <returns>�|���S���̒��Ƀ|�C���g���W�������Ă��邩�ǂ���</returns>
		static bool PointInPolygon(const Vec2& point, const std::vector<Vec2>& polygon);


	};
}