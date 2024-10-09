#pragma once

#include "StateMachine.h"
#include <memory>
#include <vector>
#include <string>
#include "Vec2.h"
#include "PlatinumLoader.h"
#include "SceneMain.h"
#include "GameData.h"

#include "EvoLib.h"

#include <tuple>


template <class TState> class StateMachine;



namespace
{
	// �T�E���h�t�@�C����
	static std::vector<std::string> kSoundFileName =
	{
		"Bgm_0",		// BGM

		"Determination",// ���艹
		"Cancel",		// �L�����Z����
		"Select",		// �I����

		"Pause",		// �|�[�Y��

		"Jump",			// �W�����v��
		"Dead",			// ���S��
		"Restart",		// ���X�^�[�g��
	};

	// �T�E���h��
	enum class SoundName
	{
		BGM,			// BGM

		Decision,		// ���艹
		Cancel,			// �L�����Z����
		Select,			// �I����

		Pause,			// �|�[�Y��

		Jump,			// �W�����v��
		Dead,			// ���S��
		Restart,		// ���X�^�[�g��
	};

}



class MainScreen;
class ObjectBase;
class PlatinumLoader;
class Camera;
class Pause;
class MessageWindow;
class GameOver;

class ObjectManager : public std::enable_shared_from_this<ObjectManager>
{
public:

	// �X�e�[�W�ړ��^�C�v
	enum class MapSwitchType
	{
		Spawn,			// �X�|�[��
		SaveData,		// �Z�[�u�f�[�^
		Respawn,		// ���X�|�[��
		NextStage,		// ���̃X�e�[�W
		PreviouseStage	// �O�̃X�e�[�W
	};


	// �`�b�v�^�C�v
	enum class ChipType
	{
		None,				// �����Ȃ�
		Ground,				// �n��
		NextStage,			// ���̃X�e�[�W
		PreviouseStage,		// �O�̃X�e�[�W
		NextPos,			// ���̃X�e�[�W���W
		PreviousePos,		// �O�̃X�e�[�W���W
		SpawnPos,			// �X�|�[�����W
		Save,				// �Z�[�u

		TopNeedle,			// ��j
		BottomNeedle,		// ���j
		LeftNeedle,			// ���j
		RightNeedle,		// �E�j
		DiedBlock,			// ���S�u���b�N
		
		TopGravity,			// ��d��
		BottomGravity,		// ���d��
		LeftGravity,		// ���d��
		RightGravity,		// �E�d��

		IceBlock,			// �A�C�X�u���b�N
	
		TopConveyor,		// ��R���x�A
		BottomConveyor,		// ���R���x�A
		LeftConveyor,		// ���R���x�A
		RigthConveyor,		// �E�R���x�A

		TransparentBlock,	// �����u���b�N
		
		InfiniteJump,		// �����W�����v
		SecondJump,			// ��i�W�����v

		StrongJumpPower,	// ���W�����v
		WeakJumpPower,		// ��W�����v
		NormalJumpPower,		// �ʏ�W�����v

		Acceleration,		// ����
		Deceleration,		// ����
		NormalSpeed,		// �ʏ푬�x

		EndGame,			// �Q�[���I��

		NotExists			// ���݂��Ȃ�
	};



	// �}�b�v����f�[�^
	struct MapCollisionData
	{
		// �`�b�v�^�C�v
		ChipType chipType = ChipType::None;

		// �}�b�v�l�p�`���
		Square square = Square();

		// �}�b�v�~���
		Circle circle = Circle();

		// ��ʓ��t���O
		bool screenFlag = false;

		// �v���C���[�͈͓��t���O
		bool playerRangeFlag = false;
	};

	// �}�b�v���f�[�^
	struct MapInfoData
	{
		// �}�b�v�f�[�^�̃t�@�C���p�X
		std::vector<std::string> filePath;

		// �}�b�v����f�[�^
		std::vector<std::vector<MapCollisionData>> mapCollisionData;

		// �}�b�v���
		PlatinumLoader::MapChip mapChip;
		
		// �}�b�v�i���o�[
		int mapNumber = 0;
	};


public:

	// �X�e�[�g
	enum class State
	{
		// �ݒ�
		Setting,
		// �I�[�v�j���O
		Opening,
		// �ʏ�
		Normal,
		// �I����b
		EndTalk,
		// �|�[�Y���
		Pause,
		// �G���f�B���O
		Ending,
	};


public:
	ObjectManager();
	virtual ~ObjectManager();

	/// <summary>
	/// ���C���X�N���[���|�C���^�擾
	/// </summary>
	/// <param name="pMainScreen">���C���X�N���[���|�C���^</param>
	void SetMainScreenPointer(const std::shared_ptr<MainScreen>& pMainScreen) { m_pMainScreen = pMainScreen; }


	void Init();
	void Update();
	void Draw();

public:

	/// <summary>
	/// �V�[���ύX
	/// </summary>
	/// <param name="nextScene">���̃V�[��</param>
	void ChangeScene(const SceneMain::Scene& nextScene);


public:

	/// <summary>
	/// �Z�[�u�|�C���g�ݒ�
	/// </summary>
	/// <param name="cell">�Z��</param>
	/// <param name="playerStatus">�v���C���[�X�e�[�^�X</param>
	void SetSavePoint(const Cell& cell, const GameData::PlayerStatus& playerStatus);

	/// <summary>
	/// �X�e�[�g�ݒ�
	/// </summary>
	/// <param name="state">�X�e�[�g</param>
	void SetState(const State& state);

	/// <summary>
	/// ���[�h
	/// </summary>
	void Load();

	/// <summary>
	/// �L�����N�^�[����
	/// </summary>
	void PlayerCreate(const Vec2& pos);

	/// <summary>
	/// �}�b�v����
	/// </summary>
	/// <param name="�}�b�v���"></param>
	void MapCollisionDataCreate(const std::vector<std::vector<int>>& mapData, const MapSwitchType& mapSwitchType);

	/// <summary>
	/// �I�u�W�F�N�g�폜
	/// </summary>
	void ObjectErase();

	/// <summary>
	/// �X�e�[�W�ړ�
	/// </summary>
	void StageMove(const MapSwitchType& mapSwitchType);

	/// <summary>
	/// �}�b�v���f�[�^��Ԃ�
	/// </summary>
	/// <returns>�}�b�v���f�[�^</returns>
	MapInfoData GetMapInfoData() { return m_mapInfoData; }
	
	/// <summary>
	/// �}�b�v�`�b�v�ԍ���Ԃ�
	/// </summary>
	/// <returns></returns>
	std::vector<std::vector<int>>GetMapChipNumber();


	/// <summary>
	/// �Z�[�u�|�C���g�̍��W��Ԃ�
	/// </summary>
	/// <returns>bool : �X�e�[�W��ύX���邩�ǂ����@Vec2 : ���W</returns>
	std::tuple<bool, Vec2> GetSavePointPos();

	/// <summary>
	/// �j�[�h������Ԃ�
	/// </summary>
	/// <param name="needleDirection">�j�[�h���̌���</param>
	/// <param name="square">�l�p�`���</param>
	/// <returns>�j�[�h�����</returns>
	Triangle ChipTypeToTriangle(const ChipType& needleDirection, const Square& square);

	/// <summary>
	/// �t�B�[���h���m�F����
	/// </summary>
	void FieldCheck();

	/// <summary>
	/// �}�b�v�����蔻��f�[�^��Ԃ�
	/// </summary>
	std::vector<std::vector<MapCollisionData>> GetMapCollisionData() { return m_mapInfoData.mapCollisionData; }

	/// <summary>
	/// �I�u�W�F�N�g����Ԃ�
	/// </summary>
	/// <returns>�I�u�W�F�N�g���</returns>
	std::vector<std::shared_ptr<ObjectBase>> GetObjectInfo() { return m_object; }
	

private:

	/// <summary>
	/// �X�e�[�g������
	/// </summary>
	void StateInit();

	// �ݒ�X�e�[�g����
	void StateSettingInit();

	// �I�[�v�j���O�X�e�[�g����
	void StateOpeningEnter();
	void StateOpeningUpdate();
	void StateOpeningDraw();
	void StateOpeningExit();

	// �m�[�}���X�e�[�g����
	void StateNormalUpdate();
	void StateNormalDraw();

	// �I����b�X�e�[�g����
	void StateEndTalkEnter();
	void StateEndTalkUpdate();
	void StateEndTalkDraw();
	void StateEndTalkExit();

	// �|�[�Y�X�e�[�g����
	void StatePauseUpdate();
	void StatePauseDraw();

	// �G���f�B���O�X�e�[�g����
	void StateEndingEnter();


private:

	/// <summary>
	/// �}�b�v�֘A�����ݒ�
	/// </summary>
	void InitMap();
	
	/// <summary>
	/// �X�N���[���T�[�N��������
	/// </summary>
	void InitScreenCircle();

	/// <summary>
	/// �}�b�v�f�[�^�t�@�C���p�X�̏����ݒ�
	/// </summary>
	void InitMapDataFilePath();

	/// <summary>
	/// �}�b�v�`�b�v����
	/// </summary>
	/// <param name="mapCollisionData">�}�b�v����f�[�^</param>
	void MapChipCreate(const MapCollisionData& mapCollisionData);

	/// <summary>
	/// �M�~�b�N���Z�b�g����
	/// </summary>
	void GimmickReset();

	/// <summary>
	/// �Z�����͈͊O���ǂ������m�F����
	/// </summary>
	/// <param name="cell">�Z��</param>
	/// <returns>�Z�����͈͊O���ǂ����̃t���O</returns>
	bool IsCellCheckOutOfRange(const Cell& cell);


	/// <summary>d
	/// �I�u�W�F�N�g�X�V
	/// </summary>
	/// <param name="isStopPlayer">�v���C���[���~�߂邩�ǂ���</param>
	void ObjectUpdate(const bool isStopPlayer = false);

	/// <summary>
	/// �I�u�W�F�N�g�`��
	/// </summary>
	void ObjectDraw();


	/// <summary>
	/// �}�b�v�`��
	/// </summary>
	void TestMapDraw();

	/// <summary>
	/// �Z�[�u�X�R�A�`��
	/// </summary>
	void DrawSaveScore();


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

	// �I�u�W�F�N�g
	std::vector<std::shared_ptr<ObjectBase>>m_object;

	// �}�b�v���f�[�^
	MapInfoData m_mapInfoData;

	// �X�N���[���T�[�N��
	Circle m_screenCircle;

	// �}�b�v�O���t�B�b�N
	std::vector<int>m_testMapGraph;

	//////////////////////
	// �O���t�B�b�N�֘A //
	//////////////////////

	// �v���C���[�O���t�B�b�N�n���h��
	std::vector<int>m_playerGraphHandle;

	// �X�R�A�O���t�B�b�N�f�[�^
	ScoreGraphData m_scoreGraphData;	

	//////////////////
	// �X�e�[�g�֘A //
	//////////////////

	// �X�e�[�g�}�V��
	StateMachine<State>m_pStateMachine;

	////////////////////
	// �N���X�|�C���^ //
	////////////////////

	// ���C���X�N���[��
	std::shared_ptr<MainScreen>m_pMainScreen;

	// �v���`�i�����[�_�[
	std::shared_ptr<PlatinumLoader>m_pPlatinumLoader;

	// �J����
	std::shared_ptr<Camera>m_pCamera;

	// �|�[�Y
	std::shared_ptr<Pause>m_pPause;

	// �I�[�v�j���O���b�Z�[�W�E�B���h�E
	std::shared_ptr<MessageWindow>m_pOpeningMessageWindow;

	// �I����b���b�Z�[�W�E�B���h�E
	std::shared_ptr<MessageWindow>m_pEndTalkMessageWindow;

	// �Q�[���I�[�o�[
	std::shared_ptr<GameOver>m_pGameOver;
};