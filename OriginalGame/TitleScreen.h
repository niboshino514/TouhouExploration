#pragma once
#include "StateMachine.h"
#include <vector>
#include "Vec2.h"
#include "EvoLib.h"
#include "GameData.h"

template <class TState> class StateMachine;

class SceneTitle;

class TitleScreen
{
public:
	TitleScreen();
	~TitleScreen();

	/// <summary>
	/// �V�[���^�C�g���̃|�C���^���擾
	/// </summary>
	/// <param name="sceneTitle">�V�[���^�C�g���|�C���^</param>
	void SetSceneTitle(SceneTitle* sceneTitle) { m_pSceneTitle = sceneTitle; }

	void Init();
	void Update();
	void Draw();

public:

	// ���
	enum State
	{
		// ���͑҂�
		WaitInput,
		// �I��
		Selecting,
	};

	// �I��
	enum class Select
	{
		// ��������
		Continue,
		// �V�K�Q�[��
		NewGame,
		// �Q�[���I��
		GameEnd,
		// �Z���N�g��
		SelectNum,
	};

private:

	/// <summary>
	/// �O���t�B�b�N�̓ǂݍ���
	/// </summary>
	void Load();


	/// <summary>
	/// �X�e�[�g�̏�����
	/// </summary>
	void StateInit();

	// ���͑҂��X�e�[�g����
	void StateWaitEnter();
	void StateWaitUpdate();
	void StateWaitDraw();
	void StateWaitExit();

	// �I�𒆃X�e�[�g����
	void StateSelectEnter();
	void StateSelectUpdate();
	void StateSelectDraw();
	void StateSelectExit();

	// �Z�[�u�f�[�^�m�F
	void CheckSaveData();

	// �X�R�A�f�[�^�m�F
	void CheckScoreData();


	// �I������
	void SelectProcess();
	
	// ���菈��
	void DecideProcess();

	// �X�R�A�̕`��
	void DrawScore();

	// �w�i�̕`��
	void DrawBackground();

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




	////////////////
	// �X�R�A�֘A //
	////////////////

	GameData::Score m_score;	// �X�R�A

	bool m_isClear;				// �N���A���Ă��邩�ǂ���

	//////////////////////
	// �O���t�B�b�N�֘A //
	//////////////////////

	ScoreGraphData m_scoreGraphData;	// �X�R�A�O���t�B�b�N�f�[�^

	// �I���O���t�B�b�N�n���h��
	EvoLib::Load::DivGraphInfo m_selectGraphInfo;

	// �Z���N�g�O�p�`�O���t�B�b�N
	int m_selectTriangleGraph;

	int m_gameTitleGraph;	// �Q�[���^�C�g���O���t�B�b�N

	int m_backgroundGraph;	// �w�i�O���t�B�b�N
	float m_currentMoveValue;	// ���݂̈ړ���

	//////////////
	// �I���֘A //
	//////////////

	// ��������v���C�\���ǂ���
	bool m_isContinue;

	// �I��
	Select m_select;

	//////////////////
	// �X�e�[�g�֘A //
	//////////////////

	// �X�e�[�g�}�V��
	StateMachine<State>m_pStateMachine;


	// �V�[���^�C�g���|�C���^
	SceneTitle* m_pSceneTitle;
};