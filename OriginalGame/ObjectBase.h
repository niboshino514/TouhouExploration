#pragma once
#include "Vec2.h"
#include <DxLib.h>
#include "EvoLib.h"
#include "ObjectManager.h"
#include <memory>
#include "GameData.h"
#include <vector>





class ObjectManager;

class ObjectBase
{
public:
	ObjectBase();
	virtual ~ObjectBase();

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	// �I�u�W�F�N�gID
	enum class ObjectID
	{
		Player,					// �v���C���[

		TransparentBlockChip,	// �����u���b�N�`�b�v
		BossSpawnFlagChip,		// �{�X�X�|�[���t���O�`�b�v
		BossEnemy,				// �{�X�G�l�~�[

		PlayerShot,				// �v���C���[�V���b�g
	};


	// �`�惉���N(�����N�̐��l������������O�ɕ`�悳���)
	enum class DrawRank
	{
		Rank_1 = 1,
		Rank_2,
		Rank_3,
		Rank_4,
		Rank_5,
		Rank_6,
		RankNum,
	};
	
	// �A�j���[�V�����̎��
	enum class AnimationType
	{
		// ��~���
		Idle,
		// �ړ����
		Move,
	};


	/// <summary>
	/// �A�j���[�V�����̏ڍׂ�\���\����
	/// </summary>
	struct AnimationDetails
	{
		// �A�j���[�V�����ԍ�
		int number = 0;
		// �A�j���[�V�����̑��x
		int frameSpeed = 0;
		// �L�����N�^�[�������Ă��邩�ǂ����̏���
		AnimationType type = AnimationType();
		// ����
		Direction direction[2];
	};

	/// <summary>
	/// �A�j���[�V�����͈̔͂�\���\����
	/// </summary>
	struct AnimationRange
	{
		// �ŏ��C���f�b�N�X
		int minIndex = 0;
		// �ő�C���f�b�N�X
		int maxIndex = 0;
		// �A�j���[�V�������J�n����z��ԍ�
		int dirNo = 0;
		// ��~���̔z��ԍ�
		int stopNo = 0;
	};





public:

	/// <summary>
	/// �I�u�W�F�N�g�t�@�N�g���[�N���X���R�s�[
	/// </summary>
	/// <param name="objectFactory">�I�u�W�F�N�g�t�@�N�g���[</param>
	void SetObjectFactory(std::shared_ptr<ObjectManager>objectFactory) { m_pObjectManager = objectFactory; }

	/// <summary>
	/// ���݃t���O���
	/// </summary>
	/// <param name="isExlist">���݃t���O</param>
	void SetIsExlist(const bool& isExlist) { m_isExlist = isExlist; }

	/// <summary>
	/// ���݃t���O��Ԃ�
	/// </summary>
	/// <returns>���݃t���O</returns>
	bool GetIsExlist() { return m_isExlist; }

	

	/// <summary>
	/// ���W����
	/// </summary>
	/// <param name="pos">���W</param>
	void SetPos(const Vec2& pos) { m_pos = pos; }

	/// <summary>
	/// �~����Ԃ�
	/// </summary>
	/// <returns>�~���</returns>
	Circle GetCircle() { return m_circle; }


	/// <summary>
	/// �l�p�`������
	/// </summary>
	/// <param name="square">�l�p�`���</param>
	void SetSquare(const Square& square) { m_square = square; }

	/// <summary>
	/// �l�p�`����Ԃ�
	/// </summary>
	/// <returns>�l�p�`���</returns>
	Square GetSquare() { return m_square; }


	/// <summary>
	/// �I�u�W�F�N�g
	/// </summary>
	/// <param name="objectID"></param>
	void SetObjectID(const ObjectID& objectID) { m_objectID = objectID; }

	/// <summary>
	/// �I�u�W�F�N�gID��Ԃ�
	/// </summary>
	/// <returns>�I�u�W�F�N�gID</returns>
	ObjectID GetObjectID() { return m_objectID; }


	/// <summary>
	/// �`��D�揇�ʂ�Ԃ�
	/// </summary>
	/// <returns>�`��D�揇��</returns>
	DrawRank GetDrawRank() { return m_drawRank; }

	/// <summary>
	/// �`��D�揇�ʎ擾
	/// </summary>
	/// <param name="drawRank">�`�惉���N</param>
	void SetDrawRank(const DrawRank& drawRank) { m_drawRank = drawRank; }

	/// <summary>
	/// �M�~�b�N�t���O���擾
	/// </summary>
	/// <param name="isGimmick">�M�~�b�N�t���O</param>
	void SetGimiickFlag(const bool& isGimmick) { m_isGimmick = isGimmick; }

	/// <summary>
	/// �O���t�B�b�N�n���h�����Z�b�g
	/// </summary>
	/// <param name="graphicHandle">�O���t�B�b�N�n���h��</param>
	void SetGraphicHandle(const std::vector<int>& graphicHandle) { m_graphicHandle = graphicHandle; }


protected:

	/// <summary>
	///  �A�j���[�V�����ԍ��X�V
	/// </summary>
	/// <param name="animationDetails">�A�j���[�V�����ڍ�</param>
	/// <param name="animationRange">�A�j���[�V�����͈�</param>
	/// <returns>�A�j���[�V�����ԍ�</returns>
	int AnimationNamberUpdate(const AnimationDetails& animationDetails, const AnimationRange& animationRange);


protected:


	// �I�u�W�F�N�g�̎��
	ObjectID m_objectID;

	// �M�~�b�N�t���O
	bool m_isGimmick;

	// ���݃t���O
	bool m_isExlist;

	// �~���
	Circle m_circle;

	// ���W
	Vec2 m_pos;

	// �ړ���
	Vec2 m_vec;

	// �l�p�`���
	Square m_square;

	// �`��̗D�揇��
	DrawRank m_drawRank;


	//////////////////////
	// �O���t�B�b�N�֘A //
	//////////////////////

	// �摜�n���h��
	std::vector<int>m_graphicHandle;

	////////////////////////
	// �A�j���[�V�����֘A //
	////////////////////////

	// �A�j���[�V�����ڍ�
	AnimationDetails m_animationDetails;

	// �A�j���[�V�����͈�
	AnimationRange m_animationRange;
	
	////////////////////
	// �N���X�|�C���^ //
	////////////////////

	std::shared_ptr<ObjectManager>m_pObjectManager;// �I�u�W�F�N�g�}�l�[�W���[
};