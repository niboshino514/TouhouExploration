#pragma once
#include <vector>
#include <memory>


class PlatinumLoader;

class MapLoader
{
public:
	MapLoader();
	virtual ~MapLoader();

	void Init();
	void Update();
	void Draw();


	/// <summary>
	/// �}�b�v�����[�h����
	/// </summary>
	/// <param name="fmfFilePath">�}�b�v��FMF�f�[�^</param>
	/// <param name="layerType">���C���[�^�C�v</param>
	void LoadMap(const TCHAR* fmfFilePath, int layerType);


private:
	// �`�b�v�ԍ��̕ۑ�
	std::vector<std::vector<int>> m_currentData;

	// �N���X�|�C���^
	std::shared_ptr<PlatinumLoader>m_pPlatinumLoader;
};