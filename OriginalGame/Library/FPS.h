#pragma once
#include "EvoLib.h"

namespace EvoLib
{
	class FPS
	{
	public:

		// DXLib��60FPS�œ�����
		static constexpr int Dxlib_60FPS = 16667;
		// FPS
		static constexpr int Fps = 60;


		// FPS�̎擾
		static int GetFPS_EvoLib();
	};
}