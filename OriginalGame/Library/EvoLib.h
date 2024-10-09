#pragma once
#include <DxLib.h>
#include <vector>
#include <string>
#include "Vec2.h"
#include "Easing.h"
#include <iostream>
#include <fstream>
#include <typeinfo>  // typeid���g�����߂ɕK�v

/// <summary>
/// ����
/// </summary>
struct Time
{
	int hour = 0;		// ����
	int minute = 0;		// ��
	int second = 0;		// �b
	int millisecond = 0;// �~���b
};



/// <summary>
/// ����
/// </summary>
enum class Direction
{
	Top,	// ��
	Bottom,	// ��
	Left,	// ��
	Right,	// �E
	DirectionNum,// ������
};

/// <summary>
/// ���̏��
/// </summary>
struct Sphere
{
	// ���W
	VECTOR pos = { 0.0f,0.0f,0.0f };
	// ���a
	float radius = 0.0f;
};

/// <summary>
/// �Z�����
/// </summary>
struct Cell
{
	int x = 0;	// �Z��X
	int y = 0;	// �Z��Y
};

// �~�\����
struct Circle
{
	// ���S���W
	Vec2 centerPos = Vec2();

	// �~�̔��a
	float radius = 0.0f;
};

/// <summary>
/// ��`���
/// </summary>
struct Rect
{
	float top = 0.0f;	// ��
	float bottom = 0.0f;// ��
	float left = 0.0f;	// ��
	float right = 0.0f;	// �E
};

/// <summary>
/// �l�p�`���
/// </summary>
struct Square
{
	// ������W
	Vec2 A = Vec2();

	// �E����W
	Vec2 B = Vec2();

	// �E�����W
	Vec2 C = Vec2();

	// �������W
	Vec2 D = Vec2();
};


/// <summary>
/// �����̍\����
/// </summary>
struct Intersection
{
	// �����������ǂ����̃t���O
	bool isFrag = false;

	// �������W
	Vec2 pos = Vec2(0.0f, 0.0f);
};

/// <summary>
/// �������
/// </summary>
struct Line
{
	// �X��
	float a = 0.0f; 
	// y���Ƃ̌�_
	float b = 0.0f; 

	// �n�_
	Vec2 start = Vec2();
	// �I�_
	Vec2 end = Vec2();
};

/// <summary>
/// �O�p�`���
/// </summary>
struct Triangle
{
	// ���W1
	Vec2 pos_1 = Vec2();

	// ���W2
	Vec2 pos_2 = Vec2();

	// ���W3
	Vec2 pos_3 = Vec2();
};

namespace EvoLib
{

	// �A�T�[�g�N���X
	class Assert
	{
	public:

		/// <summary>
		/// �G���[���b�Z�[�W
		/// </summary>
		/// <param name="errorMessage">�G���[���b�Z�[�W</param>
		static void ErrorMessage(const std::string& errorMessage);



		
		/// <summary>
		/// ���b�Z�[�W�{�b�N�X
		/// </summary>
		/// <param name="errorMessage">�G���[���b�Z�[�W</param>
		static void ErrorMessageBox(const std::string& errorMessage);
	};

	


	

}



#include "FPS.h"
#include "Convert.h"
#include "Collision.h"
#include "Calculation.h"
#include "Load.h"
#include "Draw.h"
#include "File.h"