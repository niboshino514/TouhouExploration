#include "Calculation.h"


Vec2 EvoLib::Calculation::VibrationValue(int currentFrame, const int& maxFrame, const int& vibrationWidth)
{
    // ���݂̃t���[���ɍő�t���[�����猻�݂̃t���[�����������l��������
    currentFrame = maxFrame - currentFrame;

    // ���݂̃t���[�����O�ȉ��������ꍇ�A0����
    if (currentFrame <= 0)
    {
        currentFrame = 0;
    }


    // x,y���}�C�i�X���邩���Ȃ���
    int x = GetRand(1);
    int y = GetRand(1);

    // �p�[�Z���e�[�W�����߂�
    const float percentage = static_cast<float>(EvoLib::Convert::PercentageRate(static_cast<float>(maxFrame), static_cast<float>(currentFrame)));

    // ������
    const float decimal = percentage * 0.01f;

    // �U����(�v�Z)
    int afterVibrationWidth = static_cast<int>(vibrationWidth * decimal);


    Vec2 vibrationPos = {};


    // �����_���l�ō��W��ϊ�����
    vibrationPos.x = static_cast<float>(GetRand(afterVibrationWidth));
    vibrationPos.y = static_cast<float>(GetRand(afterVibrationWidth));


    // x or y��0�̎��A�ʒu���}�C�i�X����
    if (x == 0)vibrationPos.x *= -1;
    if (y == 0)vibrationPos.y *= -1;

    // �U���l��Ԃ�
    return vibrationPos;
}

int EvoLib::Calculation::SelectLoopNumber(const int& minNumber, const int& maxNumber, const int& currentNumber, bool isInverseLoop)
{
    // ���݂̔ԍ�����
    int number = currentNumber;

    // �t���[�v���邩�ǂ����ŏ�����ύX����
    if (isInverseLoop)
    {
        // ���݂̑I�����ڂ����ɂ��炷(�t���[�v����)
        number = (currentNumber + (maxNumber - 1)) % maxNumber;
    }
    else
    {
        // ���݂̑I�����ڂ�����ɂ��炷(���[�v����)
        number = (currentNumber + 1) % maxNumber;
    }

    // ���߂��ԍ���Ԃ�
    return number;
}

Vec2 EvoLib::Calculation::GetGraphSize_EvoLib(std::vector<int> graphHandle, const double& graphMagnificationRate)
{
    int wide = 0;       // �O���t�B�b�N�̉���
    int height = 0;     // �O���t�B�b�N�̏c��

    // �v���C���[�̃O���t�B�b�N�T�C�Y���擾
    {
        GetGraphSize(graphHandle[0], &wide, &height);
    }
   
    Vec2 graphSize = Vec2();

    graphSize.x = static_cast<float>(wide * graphMagnificationRate);
    graphSize.y = static_cast<float>(height * graphMagnificationRate);

    return graphSize;
}

std::vector<Vec2> EvoLib::Calculation::GraphEqualization(const Vec2& graphSize, const Vec2& basePos, const int& num, const Vec2& graphInterval, const bool& isHorizontalSort)
{
    // ���W���X�g
    std::vector<Vec2> posList;

    Vec2 posWidth = Vec2();
    
    // �����т��ǂ����ŏ�����ύX����
    if(isHorizontalSort)
	{
		// ���W�̕�
        posWidth.x = graphSize.x + graphInterval.x;
	}
	else
	{
		// ���W�̕�
		posWidth.y = graphSize.y + graphInterval.y;
	}

    // ���W�̕�
    const Vec2 posDistance = posWidth * static_cast<float>(num - 1);

    for (int i = 0; i < num; i++)
    {
        Vec2 pos = basePos - (posDistance * 0.5f) + (posWidth * static_cast<float>(i));

        posList.push_back(pos);
    }

    return posList;
}

std::vector<Vec2> EvoLib::Calculation::PosEqualization(const Vec2& basePos, const int& num, const Vec2& interval)
{
    // ���W���X�g
    std::vector<Vec2> posList;

    // ���W�̕�
    const Vec2 posDistance = interval * static_cast<float>(num - 1);


    for (int i = 0; i < num; i++)
    {
        Vec2 pos = basePos - (posDistance * 0.5f) + (interval * static_cast<float>(i));

        posList.push_back(pos);
    }


    return posList;
}

bool EvoLib::Calculation::IsTargetRangeValue(const float& currentValue, const float& targetValue, const float& addSubValue)
{
    // �l��␳
    if (currentValue <= (targetValue + addSubValue) &&
        currentValue >= (targetValue - addSubValue))
    {
        // true�����Ԃ�
        return true;
    }

    // false�����Ԃ�
    return false;
}

float EvoLib::Calculation::AngleLimitValueNotExceedToCalculate(const float& currentAngle, const float& addSubValue, EvoLib::Calculation::CalculationType calculation, bool isInteger, bool isAdjustment)
{
    // ���݂̊p�x����
    float angle = currentAngle;

    // �����l
    float adjustmentValue = 0.0f;

    // ���Z�̏ꍇ�A360�x�𒴂��Ȃ��悤�ɂ���
    if (calculation == CalculationType::Addition)
    {
        // �p�x�ɉ����Z�l��������
        angle += addSubValue;

        if (angle >= 360.0f)
        {
            // �A���O����0�x�ɂ���
            angle = 0.0f;

            // �����l�Ɍ��݂̃A���O������360.0f�������������߂�
            adjustmentValue = angle - 360.0f;
        }
    }
    // ���Z�̏ꍇ�A0�x�������Ȃ��悤�ɂ���
    else
    {
        // �p�x�������Z�l�����炷
        angle -= addSubValue;

        if (angle <= 0.0f)
        {
            // �����l�Ɍ��݂̃A���O����������
            adjustmentValue = angle;

            // �A���O����360�x�ɂ���
            angle = 360.0f;
        }
    }

    // �����l���g�p����ꍇ�A�����l�����Z���s��
    if (isAdjustment)
    {
        // �A���O���𒲐��l���A���Z����
        angle += adjustmentValue;
    }

    // �����l�t���O��true�Ȃ�ΐ����l��Ԃ�
    if (isInteger)
    {
        // �����l�֕ϊ�
        const int integerNum = static_cast<int>(angle);

        // ���߂��p�x��Ԃ�
        return static_cast<float>(integerNum);
    }


    // ���߂��p�x��Ԃ�
    return angle;
}

float EvoLib::Calculation::ThreeSquareTheorem(const Vec2& poa1, const Vec2& pos2)
{
    // ��ӂ̒���
    float length = 0.0f;

    // 2�悳�ꂽ�A��ӂ̒��������߂�
    length = std::powf(poa1.x - pos2.x, 2.0f)
        + std::powf(poa1.y - pos2.y, 2.0f);

    // ���������v�Z
    length = std::sqrtf(length);

    // ��ӂ̒�����Ԃ�
    return length;
}

int EvoLib::Calculation::InearInterpolationCount(const Vec2& pos, const Vec2& vec, const Vec2& size)
{
    // �ړ��ʂ�0�Ȃ�΁A�����ŏ������I������
    if (vec.x == 0.0f &&
        vec.y == 0.0f)
    {
        return 0;
    }

    // �ŏ��T�C�Y�𒲂ׂ�
    float minSize = size.x;

    if (minSize > size.x)
    {
        minSize = size.y;
    }

    // �ő�̈ړ��ʂ����߂�
    float maxVec = std::abs(vec.x);

    if (maxVec < std::abs(vec.y))
    {
        maxVec = std::abs(vec.y);
    }


    const int iinearInterpolationCount =
        static_cast<int>(maxVec / minSize);

    return iinearInterpolationCount;
}

std::vector<Vec2> EvoLib::Calculation::InearInterpolationPos(const Vec2& pos, const Vec2& vec, const int& inearInterpolationCount)
{
    // ���`��ԍ��W
    std::vector<Vec2>inearInterpolationPos;

    // ���Z���W�v�Z
    Vec2 addVec = Vec2();
    addVec.x = (vec.x / inearInterpolationCount);
    addVec.y = (vec.y / inearInterpolationCount);


    // ���`��ԍ��W���v�Z
    for (int i = 1; i < inearInterpolationCount + 1; i++)
    {
        inearInterpolationPos.push_back(pos + (addVec * static_cast<float>(i)));
    }

    // ���`��ԍ��W��Ԃ�
    return inearInterpolationPos;
}

Rect EvoLib::Calculation::CalculateRectangleMovementRange(const Rect& rect, const Cell& maxCell, const float& cellSize, const std::vector<std::vector<int>>& cellData, const std::vector<int> groundCellNumber)
{
    // ���ʂ̋�`
    Rect result = Rect();

	// �}�b�v�S�̂��ړ��\�ȏ�Ԃŏ�����
	result.top = 0.0f;
	result.bottom = (maxCell.y * cellSize) - (rect.bottom - rect.top) / 2.0f;
	result.left = 0.0f;
	result.right = (maxCell.x * cellSize) - (rect.right - rect.left) / 2.0f;


	// ����Ώۂ̈ʒu���}�b�v�`�b�v�̃C���f�b�N�X�ɕύX
	const int indexMinX = static_cast<int>(rect.left / cellSize);
	const int indexMaxX = static_cast<int>((rect.right - 1) / cellSize);
	const int indexMinY = static_cast<int>(rect.top / cellSize);
	const int indexMaxY = static_cast<int>((rect.bottom - 1) / cellSize);

	// ������`�F�b�N
	for (int y = indexMinY; y >= 0; y--)
	{
		for (int x = indexMinX; x <= indexMaxX; x++)
		{
            if (cellData[x][y] == 0)
            {
				continue;
			}

            bool isContinue = true;

            // �n�ʃZ���ԍ�������ꍇ�A���̃Z���ԍ��͖�������
            for (auto& unused : groundCellNumber)
            {
				if (cellData[x][y] == unused)
				{
                    isContinue = false;
				}
            }

            if (isContinue)
            {
                continue;
            }



			// ��ԍŏ��Ɍ��������Ԃ���}�b�v�`�b�v�̈�ԉ�Y���W�����
			float temp = static_cast<float>(y * cellSize + cellSize);
			if (temp > result.top)
			{
				result.top = temp;
			}
		}
	}
	// �������`�F�b�N
	for (int y = indexMaxY; y < maxCell.y; y++)
	{
		for (int x = indexMinX; x <= indexMaxX; x++)
		{

            if (cellData[x][y] == 0)
            {
                continue;
            }

            bool isContinue = true;

            // �n�ʃZ���ԍ�������ꍇ�A���̃Z���ԍ��͖�������
            for (auto& unused : groundCellNumber)
            {
                if (cellData[x][y] == unused)
                {
                    isContinue = false;
                }
            }

            if (isContinue)
            {
                continue;
            }


			// ��ԍŏ��Ɍ��������Ԃ���}�b�v�`�b�v�̈�ԏ�Y���W�����
			float temp = static_cast<float>(y * cellSize);
			if (temp < result.bottom)
			{
				result.bottom = temp;
			}
		}
	}
	// ������
	for (int x = indexMinX; x >= 0; x--)
	{
		for (int y = indexMinY; y <= indexMaxY; y++)
		{

            if (cellData[x][y] == 0)
            {
                continue;
            }

            bool isContinue = true;

            // �n�ʃZ���ԍ�������ꍇ�A���̃Z���ԍ��͖�������
            for (auto& unused : groundCellNumber)
            {
                if (cellData[x][y] == unused)
                {
                    isContinue = false;
                }
            }

            if (isContinue)
            {
                continue;
            }


			// ��ԍŏ��Ɍ��������Ԃ���}�b�v�`�b�v�̈�ԉEX���W�����
			float temp = static_cast<float>(x * cellSize + cellSize);
			if (temp > result.left)
			{
				result.left = temp;
			}
		}
	}
	// �E����
	for (int x = indexMaxX; x < maxCell.x; x++)
	{
		for (int y = indexMinY; y <= indexMaxY; y++)
		{

            if (cellData[x][y] == 0)
            {
                continue;
            }

            bool isContinue = true;

            // �n�ʃZ���ԍ�������ꍇ�A���̃Z���ԍ��͖�������
            for (auto& unused : groundCellNumber)
            {
                if (cellData[x][y] == unused)
                {
                    isContinue = false;
                }
            }

            if (isContinue)
            {
                continue;
            }


			// ��ԍŏ��Ɍ��������Ԃ���}�b�v�`�b�v�̈�ԍ�X���W�����
			float temp = static_cast<float>(x * cellSize);
			if (temp < result.right)
			{
				result.right = temp;
			}
		}
	}

	return result;
}

bool EvoLib::Calculation::IsCellRange(const Cell& cell, const Cell& maxCell, const Cell& minCell)
{
    // �Z�����ő�Z���𒴂��Ă��邩�ǂ������m�F����
    if (cell.x >= maxCell.x ||
        cell.y >= maxCell.y)
    {
        // �����Ă�����false��Ԃ�
        return false;
    }

    // �Z�����ŏ��Z����������Ă��邩�ǂ������m�F����
    if (cell.x < minCell.x ||
        cell.y < minCell.y)
    {
        // ������Ă�����false��Ԃ�
        return false;
    }

    // true��Ԃ�
    return true;
}

Vec2 EvoLib::Calculation::TargetMoveValue(const Vec2& pos, const Vec2& targetPos, const float& moveSpeed)
{

    // �^�[�Q�b�g�̍��W���玩�g�̍��W���������l�����߂�
    Vec2 vel = targetPos - pos;

    // ���߂��������m�}���C�Y���邱�Ƃɂ�苗���̒������P�Ƃ݂�
    vel = vel.normalize();

    // �m�[�}���C�Y���ꂽ�����Ɉړ����x��������
    vel *= moveSpeed;

    // �ړ��ʂ�Ԃ�
    return vel;
}

Vec2 EvoLib::Calculation::SatelliteTrajectory(const Vec2& centerPos, const float& radian, const float& circleRadius)
{
    // �ړ���
    Vec2 vec = Vec2();

    // ���S�ʒu���甼�a�����ƂɋO�����v�Z
    vec.x = cos(radian) * circleRadius;
    vec.y = sin(radian) * circleRadius;

    // �x�N�g�����ʒu�ɉ��Z
    const Vec2 pos = centerPos + vec;

    // ���W��Ԃ�
    return pos;
}

std::vector<Vec2> EvoLib::Calculation::VertexCoordinateRotation(const Vec2& rotaCenterPos, const float& radian, const std::vector<Vec2> vertexPos)
{
    // �e���_�̃��W�A��
    float vertexRad;

    // �e���_�̍��W
    std::vector<Vec2>vertexRotaPos;

    for (int i = 0; i < static_cast<int>(vertexPos.size()); i++)
    {
        // ���_�̃��W�A�������߂�
        vertexRad = Atan2_Lib(vertexPos[i], rotaCenterPos) + radian;

        // ���_�̉�]���W�𒲂ׂ�
        vertexRotaPos.push_back(SatelliteTrajectory(rotaCenterPos, vertexRad, ThreeSquareTheorem(vertexPos[i], rotaCenterPos)));
    }

    return vertexRotaPos;
}

float EvoLib::Calculation::Atan2_Lib(const Vec2& targetPos, const Vec2& startPos)
{
    // �^�[�Q�b�g���W�������A���W�A�������߂�
    const float radian = atan2(targetPos.y - startPos.y, targetPos.x - startPos.x);

    // �^�[�Q�b�g���W���������W�A��
    return radian;
}

Vec2 EvoLib::Calculation::NormalVector(const Vec2& p1, const Vec2& p2)
{
    // 2�_�Ԃ̕����x�N�g�����v�Z
    Vec2 directinVec = directinVec.directionVector(p1, p2);

    // �����x�N�g���𐳋K��
    directinVec = directinVec.normalize();

    // �����x�N�g���ɑ΂���E�����̖@���x�N�g�����v�Z
    Vec2 normal = normal.rightNormal(directinVec);

    // �@���x�N�g����Ԃ�
    return normal;
}

Vec2 EvoLib::Calculation::ReflectVector(const Vec2& vec, const Vec2& p1, const Vec2& p2)
{
    // �@���x�N�g�������߂�
    const Vec2 normal = NormalVector(p1, p2);

    // ���˃x�N�g�����v�Z
    Vec2 reflect = reflect.reflect(vec, normal);

    // ���˃x�N�g����Ԃ�
    return reflect;
}

std::vector<float> EvoLib::Calculation::AngleDivision(const int& divisionNumber, const float& baseAngle)
{

    // 1�̊p�x�����߂�
    const float divAngle = 360.0f / static_cast<float>(divisionNumber);

    // �p�x���X�g
    std::vector<float> angleList;


    for(int i = 0; i < divisionNumber; i++)
	{
		// �p�x�����߂�
		const float tempAngle = baseAngle + (divAngle * static_cast<float>(i));

		// �p�x�����X�g�ɒǉ�
		angleList.push_back(tempAngle);
	}

    // �p�x���X�g��Ԃ�
    return angleList;
}

Vec2 EvoLib::Calculation::EasingInOutSine(EasingData& easingData)
{
    // ���݂̃t���[�����𑝂₷
    easingData.currentFrame++;

    // ���݂̃t���[���������t���[�����𒴂�����A���t���[�����ɂ���
    easingData.currentFrame = min(easingData.currentFrame, easingData.totalFrame);

    // ���݂̍��W
    Vec2 pos = Vec2();

    // ���݂̍��W���C�[�W���O�ŋ��߂�
    pos.x = Easing::InOutSine(easingData.currentFrame, easingData.totalFrame, easingData.endPos.x, easingData.startPos.x);
    pos.y = Easing::InOutSine(easingData.currentFrame, easingData.totalFrame, easingData.endPos.y, easingData.startPos.y);

    // ���݂̃t���[������i�߂�
    return pos;
}
