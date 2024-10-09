#include "Convert.h"
#include "Sort.h"

VECTOR EvoLib::Convert::ConvertColorInto255(const VECTOR& color)
{
    // �J���[�ϐ�
    VECTOR rgb_255 = {};

    // �p�[�Z���e�[�W�ϐ�
    float percentage = 0.0f;

    // ��
    {
        percentage = static_cast<float>(PercentageRate(1.0f, color.x));

        rgb_255.x = static_cast<float>(ConvertValueToPercent(255, percentage));
    }
    // ��
    {
        percentage = static_cast<float>(PercentageRate(1.0f, color.y));


        rgb_255.y = static_cast<float>(ConvertValueToPercent(255, percentage));
    }
    // ��
    {
        percentage = static_cast<float>(PercentageRate(1.0f, color.z));


        rgb_255.z = static_cast<float>(ConvertValueToPercent(255, percentage));
    }

    // �J���[�ϐ���Ԃ�
    return rgb_255;
}

int EvoLib::Convert::PercentageRate(const float& maxValue, const float& convertValue)
{
    // �p�[�Z���g�̏����l�����߂�
    const float decimal = convertValue / maxValue;

    // �p�[�Z���g�ɕϊ�
    const int percentage = static_cast<int>(decimal * 100);

    // �p�[�Z���g��Ԃ�
    return percentage;
}

int EvoLib::Convert::ConvertValueToPercent(const int& maxValue, const float& percentage)
{
    // �p�[�Z���e�[�W�ɑ΂���l�v�Z
    const int convertValue = static_cast<int>(maxValue * percentage * 0.01);

    // �ϊ��l��Ԃ�
    return convertValue;
}

int EvoLib::Convert::ConvertFromPercentToValue(const int& maxValue, const float& percentage)
{
    // �p�[�Z���g�������ɕϊ�
    const float decimal = percentage * 0.01f;

    // �l�����߂�
    const int value = static_cast<int>(maxValue * decimal);

    // �l��Ԃ�
    return value;
}

float EvoLib::Convert::ConvertAngleToRadian(const float& angle)
{
    // �p�x�����W�A���ɕϊ�
    const float radian = angle * (DX_PI_F / 180.0f);

    // ���W�A����Ԃ�
    return radian;
}

float EvoLib::Convert::ConvertRadianToAngle(const float& radian)
{
    // ���W�A������p�x�ɕϊ�
    const float angle = radian * (180.0f / DX_PI_F);

    // �p�x��Ԃ�
    return angle;
}

float EvoLib::Convert::ConvertDirectionToAngle(const Direction& direction)
{
    // �����p�x
    float directionAngle = 0.0f;

    // �����ɂ���đ������p�x��ύX����
    switch (direction)
    {
    case Direction::Top:

        directionAngle = TopAngle;
        break;
    case Direction::Bottom:

        directionAngle = BottomAngle;
        break;
    case Direction::Left:

        directionAngle = LeftAngle;
        break;
    case Direction::Right:

        directionAngle = RightAngle;
        break;
    default:
        break;
    }

    // �����p�x��Ԃ�
    return directionAngle;
}

Direction EvoLib::Convert::ConvertAngleToDirection(const float& angle, const float addSubValue)
{
    // �p�x���
    float directionAngle[5];

    directionAngle[0] = RightAngle;
    directionAngle[1] = BottomAngle;
    directionAngle[2] = LeftAngle;
    directionAngle[3] = TopAngle;
    directionAngle[4] = 360.0f;


    // �������
    Direction direction;

    for (int i = 0; i < 5; i++)
    {
        if (EvoLib::Calculation::IsTargetRangeValue(angle, directionAngle[i], addSubValue))
        {
            switch (i)
            {
            case 0:
                direction = Direction::Right;
                break;
            case 1:
                direction = Direction::Bottom;
                break;
            case 2:
                direction = Direction::Left;
                break;
            case 3:
                direction = Direction::Top;
                break;
            case 4:
                direction = Direction::Right;
                break;
            default:
                break;
            }

            break;
        }
    }

    // ��������Ԃ�
    return direction;
}

int EvoLib::Convert::ConvertFrameToSeconds(const int& frame, const int& fps)
{
    // �b
    int second = 0;

    if (fps == 0)
    {
        second = frame / EvoLib::FPS::Fps;
    }
    else
    {
        second = frame / fps;
    }

    // �b����Ԃ�
    return second;
}

float EvoLib::Convert::ConvertFrameToSeconds_Revision(const int& frame, bool isInteger, int fps)
{
    // �b
    float second = 0;

    // FPS���l�����Čv�Z����
    if (fps == 0)
    {
        second = static_cast<float>(frame / EvoLib::FPS::Fps);
    }
    else
    {
        second = static_cast<float>(frame / fps);
    }

    // �����l�t���O��true�̏ꍇ�A�����l��Ԃ�
    if (isInteger)
    {
        // �����l�֕ϊ�
        const int integerNum = static_cast<int> (second);

        return static_cast<float> (integerNum);
    }

    // �b����Ԃ�
    return second;
}

Sphere EvoLib::Convert::ConvertSphereInfo(const VECTOR& pos, const float& radius)
{
    // �����
    const Sphere sphere = { pos, radius };

    // ������Ԃ�
    return sphere;
}

float EvoLib::Convert::ConvertingStringToFloat(const std::string& stringNum)
{
    // string�^�̐�����float�^�ɕϊ�����
    const float num = std::stof(stringNum);

    // �l��Ԃ�
    return num;
}

std::string EvoLib::Convert::ConvertingFloatToString(const float& num)
{
    // float�^��string�^�ɕϊ�
    const std::string stringNum = std::to_string(num);

    // �ϊ�����string�^�̐�����Ԃ�
    return stringNum;
}

int EvoLib::Convert::ConvertFrameCountToMillisecondUnit(const int& frame)
{
    // �t���[��������b�������߂�
    const float seconds = ConvertFrameToSeconds_Revision(frame);

    // �b������~���b�P�ʂ����߂�
    int millisecondUnit = static_cast<int>(seconds * 1000.0f);

    // �~���b�P�ʂ�Ԃ�
    return millisecondUnit;
}

Cell EvoLib::Convert::PosToCell(const Vec2& pos, const float& cellSize)
{
    // ���W�ϐ�
    Cell cell = Cell();

    // �Z�������߂�
    cell.x = static_cast<int>(pos.x / cellSize);
    cell.y = static_cast<int>(pos.y / cellSize);

    // �Z����Ԃ�
    return cell;
}

Vec2 EvoLib::Convert::CellToPos(const Cell& cell, const float& cellSize)
{
    // ���W�ϐ�
    Vec2 pos = Vec2();

    // ���W�����߂�
    pos.x = (cell.x * cellSize) + (cellSize * 0.5f);
    pos.y = (cell.y * cellSize) + (cellSize * 0.5f);

    // ���W��Ԃ�
    return pos;
}

Line EvoLib::Convert::CalculateLine(const Vec2& pos1, const Vec2& pos2)
{
    // �����ϐ�
    Line line = Line();

    
    // �X�������߂�
    line.a = (pos2.y - pos1.y) / (pos2.x - pos1.x);
    // Y���Ƃ���_�����߂�
    line.b = pos1.y - line.a * pos1.x;
    
  
    // ��������Ԃ�
    return line;
}

Intersection EvoLib::Convert::CalculateIntersection(const Line& line1, const Line& line2)
{
    // �����̍\���̕ϐ�
    Intersection intersection = Intersection();


    // �X���������ꍇ�A��_�͑��݂��Ȃ�
    if (line1.a == line2.a)
    {
        return intersection;
    }

    // ��_�����݂���̂ŁA�t���O��true�ɂ���
    intersection.isFrag = true;

    // ��_��x���W���v�Z
    intersection.pos.x = (line2.b - line1.b) / (line1.a - line2.a);

    // ��_��y���W���v�Z
    intersection.pos.y = line1.a * intersection.pos.x + line1.b;


    // ��������Ԃ�
    return intersection;
}

Vec2 EvoLib::Convert::QuadrangularCenter(const Square& square)
{
    // ������2�_����v�Z
    const Line line1 = CalculateLine(square.A, square.C);
    const Line line2 = CalculateLine(square.B, square.D);

    // 2�̒�����_�����擾
    const Intersection intersection = CalculateIntersection(line1, line2);

    // ���S�_
    Vec2 centerPos = Vec2();

    // �������������ĂȂ���΁A�����ŏ������I������
    if (!intersection.isFrag)
    {
        return centerPos;
    }

    // ���S�_����
    centerPos = intersection.pos;

    // ���S���W��Ԃ�
    return centerPos;
}

Circle EvoLib::Convert::SquareToCircle(const Square& square)
{
    // ������2�_����v�Z
    const Line line1 = EvoLib::Convert::CalculateLine(square.A, square.C);
    const Line line2 = EvoLib::Convert::CalculateLine(square.B, square.D);

    // 2�̒�����_�����擾
    const Intersection intersection = CalculateIntersection(line1, line2);

    // �~���
    Circle circle;

    // �������������ĂȂ���΁A�����ŏ������I������
    if (!intersection.isFrag)
    {
        return circle;
    }

    // ����
    std::vector<float>range;

    // �l����
    range.push_back(EvoLib::Calculation::ThreeSquareTheorem(square.A, intersection.pos));
    range.push_back(EvoLib::Calculation::ThreeSquareTheorem(square.B, intersection.pos));
    range.push_back(EvoLib::Calculation::ThreeSquareTheorem(square.C, intersection.pos));
    range.push_back(EvoLib::Calculation::ThreeSquareTheorem(square.D, intersection.pos));

    // ���l�����������ɂȂ�悤�A�\�[�g���s��
    Sort::SelectionSort(range, static_cast<int>(range.size()));



    // �~�̒��S�_����
    circle.centerPos = intersection.pos;
    // ���a����
    circle.radius = range.back();

    // �~����Ԃ�
    return circle;
}

Square EvoLib::Convert::RectToSquare(const Rect& rect)
{
    // �l�p�`���
    Square square = Square();

    // �l�p�`�����v�Z
    {
        square.A = Vec2(rect.left, rect.top);
        square.B = Vec2(rect.right, rect.top);
        square.C = Vec2(rect.right, rect.bottom);
        square.D = Vec2(rect.left, rect.bottom);
    }

    // �l�p�`����Ԃ�
    return square;
}

Rect EvoLib::Convert::PosToRect(const Vec2& pos, const Vec2& size)
{
    // ��`�ϐ�
    Rect rect = Rect();

    // ��`�����v�Z
    rect.top = pos.y - (size.y * 0.5f);
    rect.bottom = pos.y + (size.y * 0.5f);
    rect.left = pos.x - (size.x * 0.5f);
    rect.right = pos.x + (size.x * 0.5f);

    // �v�Z������`��Ԃ�
    return rect;
}

bool EvoLib::Convert::ConvertStringToBool(const std::string& str)
{
    bool isFlag = false;

    if (str == "FALSE" ||
        str == "false")
    {
        isFlag = false;
    }
    else if (
        str == "TRUE" ||
        str == "true")
    {
        isFlag = true;
    }
    else
    {

        EvoLib::Assert::ErrorMessageBox("ConvertStringToBool�ŕϊ�����ہA�X�y���~�X���������悤�ł��B");
    }

    return isFlag;
}

std::string EvoLib::Convert::WStringToString(const std::wstring& wstr)
{
    // wstring �� SJIS
    int iBufferSize = WideCharToMultiByte(CP_OEMCP, 0, wstr.c_str()
        , -1, (char*)NULL, 0, NULL, NULL);

    // �o�b�t�@�̎擾
    CHAR* cpMultiByte = new CHAR[iBufferSize];

    // wstring �� SJIS
    WideCharToMultiByte(CP_OEMCP, 0, wstr.c_str(), -1, cpMultiByte
        , iBufferSize, NULL, NULL);

    // string�̐���
    std::string oRet(cpMultiByte, cpMultiByte + iBufferSize - 1);

    // �o�b�t�@�̔j��
    delete[] cpMultiByte;

    // �ϊ����ʂ�Ԃ�
    return(oRet);
}

std::wstring EvoLib::Convert::StringToWString(const std::string& str)
{
    // string �� wstring
    int iBufferSize = MultiByteToWideChar(CP_OEMCP, 0, str.c_str(), -1, nullptr, 0);

    // �o�b�t�@�̎擾
    WCHAR* wpWideChar = new WCHAR[iBufferSize];

    // string �� wstring
    MultiByteToWideChar(CP_OEMCP, 0, str.c_str(), -1, wpWideChar, iBufferSize);

    // wstring�̐���
    std::wstring oRet(wpWideChar, wpWideChar + iBufferSize - 1);

    // �o�b�t�@�̔j��
    delete[] wpWideChar;

    // �ϊ����ʂ�Ԃ�
    return oRet;
}

