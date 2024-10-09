#pragma once
#include "StateMachine.h"
#include <memory>
#include <vector>
#include "Vec2.h"

template <class TState> class StateMachine;

class ObjectManager;
class ControllerOption;
class SoundOption;

class Pause
{
public:

	// ���
	enum class State
	{
		// �ʏ���
		Normal,
		// �|�[�Y
		Pause,
		// ���͐ؑ�
		ChangeInput,

		// ���ʒ���
		SoundOption,

		// �o�b�N�^�C�g��
		BackTitle,
	};

	// �|�[�Y�I��
	enum class PauseSelect
	{
		// �Q�[���ĊJ
		Resume,

		// ���ʒ���
		Volume,

		// ���͐ؑ�
		ChangeInput,

		// �^�C�g����
		Title,

		// �Z���N�g��
		SelectNum,
	};

	// �o�b�N�^�C�g���I��
	enum class BackTitleSelect
	{
		// �͂�
		Yes,

		// ������
		No,

		// �Z���N�g��
		SelectNum
	};


public:
	Pause();
	virtual ~Pause();

	/// <summary>
	/// �I�u�W�F�N�g�t�@�N�g���[�N���X�|�C���^���擾
	/// </summary>
	/// <param name="objectFactory">�I�u�W�F�N�g�t�@�N�g���[�|�C���^</param>
	void SetObjectFactoryPointer(const std::shared_ptr<ObjectManager>& objectFactory) { m_pObjectFactory = objectFactory; }

	void Init();
	void Update();
	void Draw();

private:

	/// <summary>
	/// �X�e�[�g������
	/// </summary>
	void StateInit();

	// �m�[�}���X�e�[�g����
	void StateNormalEnter();
	void StateNormalUpdate();

	// �|�[�Y�X�e�[�g����
	void StatePauseEnter();
	void StatePauseUpdate();
	void StatePauseDraw();
	void StatePauseExit();

	// ���͐ؑփX�e�[�g����
	void StateChangeInputEnter();
	void StateChangeInputUpdate();
	void StateChangeInputDraw();

	// ���ʒ����X�e�[�g����
	void StateSoundOptionEnter();
	void StateSoundOptionUpdate();
	void StateSoundOptionDraw();


	// �o�b�N�^�C�g���X�e�[�g����
	void StateBackTitleEnter();
	void StateBackTitleUpdate();
	void StateBackTitleDraw();

private:


	/// <summary>
	/// �O���t�B�b�N�̃��[�h
	/// </summary>
	void Load();



	/// <summary>
	/// �|�[�Y�I���X�V
	/// </summary>
	void PauseSelectUpdate();
	/// <summary>
	/// �|�[�Y���菈��
	/// </summary>
	void PauseSelectDecision();

	/// <summary>
	/// �o�b�N�^�C�g���I���X�V
	/// </summary>
	void BackTitleSelectUpdate();
	/// <summary>
	/// �o�b�N�^�C�g�����菈��
	/// </summary>
	void BackTitleSelectDecision();

	// �Q�[���ĊJ����
	void ResumeProcess();

	/// <summary>
	/// �|�[�Y�E�B���h�E�`��
	/// </summary>
	void DrawPauseWindow();

	/// <summary>
	/// �|�[�Y�I��`��
	/// </summary>
	void DrawPauseSelect();

	// �^�C�g���ɖ߂�E�B���h�E�`��
	void DrawBackTitleWindow();

	/// <summary>
	/// �o�b�N�^�C�g���I��`��
	/// </summary>
	void DrawBackTitleSelect();
	







	// �O���t�B�b�N���
	struct GraphInfo
	{
		// �n���h��
		std::vector<int> handle;

		// ���W
		std::vector<Vec2> pos;
	};



private:

	//////////////
	// �I���֘A //
	//////////////

	// �|�[�Y�I��
	PauseSelect m_pauseSelect;

	// �o�b�N�^�C�g���I��
	BackTitleSelect m_backTitleSelect;


	//////////////////////
	// �O���t�B�b�N�֘A //
	//////////////////////

	// �|�[�Y�E�B���h�E���O���t�B�b�N
	GraphInfo m_windowNameGraph;

	// �|�[�Y�I���O���t�B�b�N
	GraphInfo m_pauseSelectGprah;

	// �o�b�N�^�C�g���O���t�B�b�N
	GraphInfo m_backTitleGraph;

	// �o�b�N�^�C�g���I���O���t�B�b�N
	GraphInfo m_backTitleSelectGraph;

	// �Z���N�g�O�p�`�O���t�B�b�N
	int m_selectTriangleGraph;

	//////////////////
	// �X�e�[�g�֘A //
	//////////////////

	// �X�e�[�g�}�V��
	StateMachine<State>m_pStateMachine;

	////////////////////////
	// �N���X�|�C���^�֘A //
	////////////////////////

	// �I�u�W�F�N�g�t�@�N�g���[�N���X
	std::shared_ptr<ObjectManager> m_pObjectFactory;

	// �R���g���[���[�I�v�V�����N���X
	std::shared_ptr<ControllerOption> m_pControllerOption;

	// �T�E���h�I�v�V�����N���X
	std::shared_ptr<SoundOption> m_pSoundOption;
};

