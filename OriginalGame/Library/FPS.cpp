#include "FPS.h"

int EvoLib::FPS::GetFPS_EvoLib()
{
    // ���݂�FPS���擾����
    const float fps = GetFPS();

    // �擾����FPS��Ԃ�
    return static_cast<int>(fps);
}
