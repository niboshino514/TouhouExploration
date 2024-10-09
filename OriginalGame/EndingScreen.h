#pragma once
#include <memory>
#include "EvoLib.h"
#include "GameData.h"

class SceneEnding;
class EffectManager;

class EndingScreen
{
public:
	EndingScreen();
	virtual ~EndingScreen();

	/// <summary>
	/// �V�[���G���f�B���O�̃|�C���^���擾
	/// </summary>
	/// <param name="sceneEnding">�V�[���G���f�B���O�|�C���^�[</param>
	void SetSceneEndingPointer(SceneEnding* sceneEnding) { m_pSceneEnding = sceneEnding; }

	void Init();
	void Update();
	void Draw();

private:

	// �摜���[�h
	void Load();

	// �T�C���J�[�u�̍X�V
	void UpdateSineCurve();

	// �X�R�A�̕`��
	void DrawScore();


private:

	// �X�R�A�O���t�B�b�N�f�[�^
	struct ScoreGraphData
	{
		// �ԍ��O���t
		std::vector<int> numberGraphHandle;

		// �d�؂�O���t
		int separateGraphHandle = -1;

		// �񐔂̃O���t�B�b�N
		int countGraphHandle = -1;

		// �N���A���g���C�񐔃e�L�X�g�O���t�B�b�N
		std::vector<int> clearRetryTextGraphHandle;
	};


private:


	//////////////////////
	// �O���t�B�b�N�֌W //
	//////////////////////

	int m_gameClearGraphHandle;	// �Q�[���N���A�摜�n���h��

	ScoreGraphData m_scoreGraphData;	// �X�R�A�O���t�B�b�N�f�[�^

	int m_thanksGraphHandle;	// �T���N�X�摜�n���h��

	int m_newRecordGraphHandle;	// �j���[���R�[�h�摜�n���h��

	int m_charaGraphHandle;	// �L�����N�^�[�摜�n���h��

	////////////////
	// �X�R�A�֘A //
	////////////////


	GameData::Score m_score;	// �X�R�A

	bool m_isNewRecord;	// �j���[���R�[�h���ǂ���

	//////////////////////
	// �T�C���J�[�u�֘A //
	//////////////////////

	EvoLib::Calculation::SineCurveData<float> m_gameClearGraphSineCuve;	// �Q�[���N���A�摜�̃T�C���J�[�u�f�[�^
	float m_gameClearGraphSineCurveValue;	// �Q�[���N���A�摜�̃T�C���J�[�u�̒l

	// �V�[���G���f�B���O�|�C���^
	SceneEnding* m_pSceneEnding;

	// �G�t�F�N�g�}�l�[�W���[
	std::shared_ptr<EffectManager> m_pEffectManager;

};

