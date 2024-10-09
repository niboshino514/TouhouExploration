#include "Load.h"



int EvoLib::Load::LoadGraph_EvoLib(const char* filePath)
{
    // �t�@�C�������݂��Ȃ��ꍇ�A�G���[���b�Z�[�W��\��
    if (!EvoLib::File::IsFileExist(filePath))
    {
        // �t�@�C�������݂��Ȃ��ꍇ�A�G���[���b�Z�[�W��\��
        std::string errorMsg = "[" + static_cast<std::string>(filePath) + "]" +
            " �̃O���t�B�b�N�t�@�C���͑��݂��Ȃ��悤�ł��B";

        // �t�@�C���Ǎ��G���[����
        EvoLib::Assert::ErrorMessageBox(errorMsg);
    }


    // �O���t�B�b�N�n���h���̃��[�h
    const int graphic = LoadGraph(filePath);

    // �O���t�B�b�N�n���h����Ԃ�
    return graphic;
}

EvoLib::Load::DivGraphInfo_Old_Type EvoLib::Load::LoadDivGraph_EvoLib(const char* filePath, const int& div_x, const int& div_y)
{

    int wide = 0;       // �O���t�B�b�N�̉���
    int height = 0;     // �O���t�B�b�N�̏c��
    int graphic = -1;   // �O���t�B�b�N�̑��


    // �v���C���[�̃O���t�B�b�N�T�C�Y���擾
    {
        graphic = LoadGraph(filePath);
        GetGraphSize(graphic, &wide, &height);

		// �O���t�B�b�N�̍폜
        DeleteGraph(graphic);
    }


    // ���������v
    const int divNum = div_x * div_y;

    // �O���t�B�b�N���
    DivGraphInfo_Old_Type graphInfo;

    // �X�P�[������
    graphInfo.scale.x = static_cast<float>(wide);
    graphInfo.scale.y = static_cast<float>(height);



    // ���������摜���n���h���ɓ����
    {
        // �n���h��
        int* handle = new int[divNum];

        // ���������摜������
        LoadDivGraph(filePath, divNum,
            div_x, div_y,
            wide / div_x, height / div_y, handle);

        for (int i = 0; i < divNum; i++)
        {
            // �O���t�B�b�N����
            graphInfo.handle.push_back(handle[i]);
        }

        // �������̊J��
        delete[] handle;
    }

    return graphInfo;
}

std::vector<int> EvoLib::Load::LoadDivGraph_EvoLib_Revision(const char* filePath, const DivNum& div)
{
    // �t�@�C�������݂��Ȃ��ꍇ�A�G���[���b�Z�[�W��\��
    if(!EvoLib::File::IsFileExist(filePath))
    {
		// �t�@�C�������݂��Ȃ��ꍇ�A�G���[���b�Z�[�W��\��
		std::string errorMsg = "[" + static_cast<std::string>(filePath) + "]" +
			" �̃O���t�B�b�N�t�@�C���͑��݂��Ȃ��悤�ł��B";

		// �t�@�C���Ǎ��G���[����
		EvoLib::Assert::ErrorMessageBox(errorMsg);
	}




    int wide = 0;       // �O���t�B�b�N�̉���
    int height = 0;     // �O���t�B�b�N�̏c��
    int graphic = -1;   // �O���t�B�b�N�̑��


    // �v���C���[�̃O���t�B�b�N�T�C�Y���擾
    {
        graphic = LoadGraph(filePath);
        GetGraphSize(graphic, &wide, &height);

		// �O���t�B�b�N�̍폜
        DeleteGraph(graphic);
    }


    // ���������v
    const int divNum = div.x * div.y;

    // �������ꂽ�O���t�B�b�N�n���h��
    std::vector<int> graphHandle;

    // ���������摜���n���h���ɓ����
    {
        // �n���h��
        int* handle = new int[divNum];

        // ���������摜������
        LoadDivGraph(filePath, divNum,
            div.x, div.y,
            wide / div.x, height / div.y, handle);

        for (int i = 0; i < divNum; i++)
        {
            // �O���t�B�b�N����
            graphHandle.push_back(handle[i]);
        }
        // �������̊J��
        delete[] handle;
    }

    // �O���t�B�b�N���
    return graphHandle;
}

int EvoLib::Load::LoadFont(const char* filePath, const char* fontName, const int& fontSize)
{
    // �ǂݍ��ރt�H���g�t�@�C���̃p�X
    LPCSTR font_path = filePath; 

    // �G���[���b�Z�[�W
    std::string errorMsg = "";

 
    // �t�@�C�������݂��Ȃ��ꍇ�A�G���[���b�Z�[�W��\��
    if (!EvoLib::File::IsFileExist(filePath))
    {
        // �G���[���b�Z�[�W
        errorMsg = "[" + static_cast<std::string>(filePath) + "]" +
			" �͑��݂��Ȃ��悤�ł��B";

        // �t�@�C���Ǎ��G���[����
        EvoLib::Assert::ErrorMessageBox(errorMsg);
    }


    // �t�H���g�Ǎ�
    if (AddFontResource(font_path) > 0) 
    {
        PostMessage(HWND_BROADCAST, WM_FONTCHANGE, 0, 0);
    }
    else 
    {
        // �G���[���b�Z�[�W
        errorMsg = "[" + static_cast<std::string>(filePath) + "]" +
            " �ɂ���t�H���g�̓ǂݍ��݂����s���܂����B";

        // �t�H���g�Ǎ��G���[����
        EvoLib::Assert::ErrorMessageBox(errorMsg);
    }

    // �t�H���g�̕ۑ�
    const int fontData = CreateFontToHandle(fontName, fontSize, 3, DX_FONTTYPE_ANTIALIASING_EDGE_8X8, -1, -1);

    // �t�H���g�f�[�^��-1�̏ꍇ�A�G���[���b�Z�[�W��\��
    if (fontData == -1)
    {
        // �G���[���b�Z�[�W
        errorMsg = "�t�H���g��ۑ�����ۂɃG���[���������܂����B";

        // �t�H���g�Ǎ��G���[����
        EvoLib::Assert::ErrorMessageBox(errorMsg);
    }

    // �t�H���g�f�[�^��Ԃ�
    return fontData;
}


