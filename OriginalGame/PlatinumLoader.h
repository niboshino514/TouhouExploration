#pragma once
#include <DxLib.h>
#include <vector>


//�}�b�v�̍L�� * ���C���[���Ȃ̂ŁA2�̃x�N�^�[�����q�ɂ��Ă�
using MapData_t = std::vector < std::vector<unsigned char>>;


/// <summary>
/// Platinum�̃f�[�^�����[�h����
/// </summary>
class PlatinumLoader
{
public:
	// �}�b�v�`�b�v���
	struct MapChip
	{
		// �}�b�v�̉���
		int mapWidth = 0;
		// �}�b�v�̏c��
		int mapHeight = 0;
		// �`�b�v�T�C�Y
		float chipSize = 0;
	};

	// �}�b�v�f�[�^
	struct MapData
	{
		// �}�b�v�f�[�^
		std::vector<std::vector<int>> mapData;
	};

public:
	PlatinumLoader();
	virtual ~PlatinumLoader();

public:

	/// <summary>
	/// fmf�t�@�C����ǂݍ����mapData_�ɒ��g������
	/// </summary>
	/// <param name="filePath">fmf�t�@�C���̃t�@�C���p�X</param>
	void Load(const TCHAR* filePath);
	

	/// <summary>
	/// ���C���[���Ƃ̃}�b�v�f�[�^���擾����
	/// </summary>
	/// <param name="layerNum">���C���[�ԍ�</param>
	/// <returns>�}�b�v�f�[�^��Ԃ�</returns>
	std::vector<std::vector<int>> GetMapLayerData(const int& layerNum);

	/// <summary>
	/// ���ׂẴ}�b�v�f�[�^���擾����
	/// </summary>
	/// <returns></returns>
	std::vector<MapData> GetMapAllData();

	/// <summary>
	/// �}�b�v�`�b�v����Ԃ�
	/// </summary>
	/// <returns>�}�b�v���(�}�b�v�̉���,�@�}�b�v�̏c��,�@�}�b�v�`�b�v�̃T�C�Y)</returns>
	MapChip GetMapChip() { return m_mapChip; }



private:

	/// <summary>
	/// �t�@�C�������݂��邩�ǂ������m�F(�A�T�[�g)
	/// </summary>
	/// <param name="filePath">�t�@�C���p�X</param>
	void FileExistsConfirmation(const TCHAR* filePath);


	/// <summary>
	/// ���̃��C���[�����݂���̂��m�F
	/// </summary>
	/// <param name="layerNum">���C���[</param>
	void LayerCheck(const int& layerNum);


private:

	// �v���`�i���f�[�^
	MapData_t m_platinumData;

	// �}�b�v�`�b�v���
	MapChip m_mapChip;

	// ���C���[��
	int m_layerMaxNum = 0;
};

