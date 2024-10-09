#include "PlatinumLoader.h"
#include <string>
#include <cassert>
#include <filesystem>

PlatinumLoader::PlatinumLoader() :
	m_platinumData(),
	m_mapChip(),
	m_layerMaxNum(0)
{
}

PlatinumLoader::~PlatinumLoader()
{
}

void PlatinumLoader::Load(const TCHAR* filePath)
{
	// �t�@�C�������݂��邩�ǂ������m�F����
	FileExistsConfirmation(filePath);


	// FMF�w�b�_�[(Platinum�̃h�L�������g�ɏ����Ă���)
	struct Header {
		int8_t id[4];			// ���ʎq(FMF_)								1*4�o�C�g
		uint32_t size;			// �f�[�^�T�C�Y�@							4�o�C�g
		uint32_t mapWidth;		// �}�b�v�̕�								4�o�C�g
		uint32_t mapHeight;		// �}�b�v�̍����@							4�o�C�g
		uint8_t chiphWidth;		// �`�b�v(�Z�����)�̕�						1�o�C�g
		uint8_t chpHeight;		// �`�b�v(�Z�����)�̍���					1�o�C�g
		uint8_t layerCount;		// ���C���[�̐�								1�o�C�g
		uint8_t bitCount;		// �P�Z��������̃r�b�g��(��8�Ńo�C�g��)	1�o�C�g
	};// 20�o�C�g

	// �w�b�_�[�ϐ�
	Header header;

	const int handle = FileRead_open(filePath);
	FileRead_read(&header, sizeof(header), handle);

	std::string strId;
	strId.resize(4);
	std::copy_n(header.id, 4, strId.begin());



	// ���C���[������
	m_layerMaxNum = header.layerCount;

	// �}�b�v�̏c���Ɖ�������
	m_mapChip.mapHeight = header.mapHeight;
	m_mapChip.mapWidth = header.mapWidth;

	//���C���[1������̃T�C�Y���v�Z����
	//�}�b�v�̕����}�b�v�̍���*(�`�b�v1������̃o�C�g��)
	int layerDataSize = header.mapWidth * header.mapHeight * (header.bitCount / 8);

	// �`�b�v�T�C�Y����(�`�b�v�T�C�Y�͏c�������T�C�Y�Ȃ̂�Width�ł�Height�ł��ǂ���ł��悢)
	m_mapChip.chipSize = header.chiphWidth;


	m_platinumData.resize(m_layerMaxNum);
	for (auto& layer : m_platinumData) {
		layer.resize(layerDataSize);
		FileRead_read(layer.data(), layerDataSize, handle);
	}

	FileRead_close(handle);
}



std::vector<std::vector<int>> PlatinumLoader::GetMapLayerData(const int& layerNum)
{
	// ���C���[�����݂��邩���m�F����
	LayerCheck(layerNum);


	// �񎟌��̗v�f�����������񎟌��z��
	std::vector<std::vector<int>>mapData(m_mapChip.mapWidth, std::vector<int>(m_mapChip.mapHeight));

	for (int y = 0; y < m_mapChip.mapHeight; y++)
	{
		for (int x = 0; x < m_mapChip.mapWidth; x++)
		{
			auto index = x + y * m_mapChip.mapWidth;

			mapData[x][y] = m_platinumData[layerNum][index];
		}
	}

	// �}�b�v�f�[�^��Ԃ�
	return mapData;
}

std::vector<PlatinumLoader::MapData> PlatinumLoader::GetMapAllData()
{
	// �}�b�v�f�[�^�i�[�ϐ�
	std::vector<MapData> mapData;

	// ���ׂẴ��C���[�̃f�[�^���i�[����
	for (int i = 0; i < m_layerMaxNum; i++)
	{
		mapData.push_back(MapData(GetMapLayerData(i)));
	}

	// �}�b�v�f�[�^��Ԃ�
	return mapData;
}

void PlatinumLoader::FileExistsConfirmation(const TCHAR* filePath)
{
#if _DEBUG

	if (!std::filesystem::is_regular_file(filePath))
	{

		// �t�@�C�������e�L�X�g��
		std::string fileName = filePath;

		// �G���[���b�Z�[�W
		std::string errorMsg =
			"\n///////// README /////////\n\n" +
			fileName + " <-This file isn't here.\n\n" +
			"-END-";

		// ���C�h������ɕϊ�
		WCHAR* _wtext = new WCHAR[strlen(errorMsg.c_str()) + 1];
		mbstowcs_s(nullptr, _wtext, strlen(errorMsg.c_str()) + 1, errorMsg.c_str(), _TRUNCATE);


		_wassert(_wtext, _CRT_WIDE(__FILE__), (unsigned)(__LINE__));
	}
#endif
}

void PlatinumLoader::LayerCheck(const int& layerNum)
{
#if _DEBUG

	// ���C���[�����݂��Ȃ��ꍇ�G���[���b�Z�[�W���o��
	if (m_layerMaxNum == layerNum)
	{
		// �G���[���b�Z�[�W
		std::string errorMsg =
			"\n///////// README /////////\n\n"
			" This fmf file does not have that layer..\n\n"
			"-END-";

		//���C�h������ɕϊ�
		WCHAR* _wtext = new WCHAR[strlen(errorMsg.c_str()) + 1];
		mbstowcs_s(nullptr, _wtext, strlen(errorMsg.c_str()) + 1, errorMsg.c_str(), _TRUNCATE);


		_wassert(_wtext, _CRT_WIDE(__FILE__), (unsigned)(__LINE__));
	}
#endif
}