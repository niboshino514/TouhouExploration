#pragma once

class SceneSaveDataSelect;

class SaveDataSelectScreen
{
public:
	SaveDataSelectScreen();
	~SaveDataSelectScreen();

	/// <summary>
	/// �V�[���Z�[�u�f�[�^�I���̃|�C���^���擾
	/// </summary>
	/// <param name="sceneSaveDataSelect">�V�[���Z�[�u�f�[�^�I���|�C���^</param>
	void SetSceneSaveDataSelect(SceneSaveDataSelect* sceneSaveDataSelect) { m_pSceneSaveDataSelect = sceneSaveDataSelect; }

	void Init();
	void Update();
	void Draw();

private:

	// �V�[���Z�[�u�f�[�^�I���|�C���^
	SceneSaveDataSelect* m_pSceneSaveDataSelect;

};

