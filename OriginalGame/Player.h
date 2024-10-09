#pragma once
#include "ObjectBase.h"
#include "GameData.h"


template <class TState> class StateMachine;

class Player : public ObjectBase
{
public:

	// �v���C���[�̓����蔻�蔼�a�T�C�Y
	static constexpr float kCollisionRadius = 120.0f;


	// �W�����v���
	struct JumpInfo
	{
		// �W�����v���Ă��邩�ǂ���
		bool isJump = false;

		// �������x
		float fallSpeed = 0.0f;

		// �W�����v��
		int jumpCount = 0;
	};

	// ���
	enum State
	{
		// �ʏ���
		Normal,
		// ���S
		Dead,
	};

	// �R���x�A
	struct Conveyor
	{
		// �R���x�A�ɏ���Ă��邩�ǂ���
		bool isFrag = false;

		// �R���x�A�̑��x
		float speed = 0.0f;

		// �R���x�A�̕���
		Direction direction = Direction();
	};
	

public:
	Player();
	virtual ~Player();


	void Init()override;
	void Update()override;
	void Draw()override;

private:

	/// <summary>
	/// �X�e�[�g������
	/// </summary>
	void StateInit();

	
	// �m�[�}���X�e�[�g����
	void StateNormalEnter();
	void StateNormalUpdate();
	void StateNormalDraw();
	void StateNormalExit();

	



	/// <summary>
	/// ���X�|�[��
	/// </summary>
	void Respawn();

	/// <summary>
	/// �ړ�
	/// </summary>
	void Move();

	/// <summary>
	/// �W�����v����
	/// </summary>
	void Jump();

	/// <summary>
	/// �Փ�
	/// </summary>
	void Collision();


private:

	/// <summary>
	/// �A�j���[�V����
	/// </summary>
	void Animation();

	/// <summary>
	/// �n�ʂ̏Փ˔���
	/// </summary>
	void GroundCollision();

	/// <summary>
	/// ���W���`���
	/// </summary>
	void PosLinearInterpolation();

	/// <summary>
	/// �}�b�v�`�b�v�̓����蔻��
	/// </summary>
	void MapChipCollision(const Vec2& pos);

	/// <summary>
	/// ��Q���̓����蔻��
	/// </summary>
	/// <param name="mapCollisionData">�}�b�v����f�[�^</param>
	/// <param name="pos">�v���C���[�̎l�p�`���</param>
	void ObstacleCollision(const ObjectManager::MapCollisionData& mapCollisionData, const Square& square);

	/// <summary>
	/// �Z�[�u�|�C���g�̏Փˏ���
	/// </summary>
	void SavePointCollision(const Cell& savePointCell);

	/// <summary>
	/// �}�b�v�ړ�
	/// </summary>
	/// <param name="mapCollisionData">�}�b�v����f�[�^</param>
	void MapMove(const ObjectManager::MapCollisionData& mapCollisionData);

	/// <summary>
	/// �d�͏���
	/// </summary>
	/// <param name="mapCollisionData">�}�b�v����f�[�^</param>
	void Gravity(const ObjectManager::MapCollisionData& mapCollisionData);

	/// <summary>
	/// �d�͕ύX
	/// </summary>
	/// <param name="gravityDirection">�d�͕ύX����</param>
	void ChangeGravityDirection(const Direction& gravityDirection);

	/// <summary>
	/// �A�C�X�u���b�N�̏Փˏ���
	/// </summary>
	void IceBlockCollision();

	/// <summary>
	/// �R���x�A�̏Փˏ���
	/// </summary>
	/// <param name="mapCollisionData">�}�b�v����f�[�^</param>
	void ConveyorCollision(const ObjectManager::MapCollisionData& mapCollisionData);

	/// <summary>
	/// �W�����v�^�C�v�̏Փˏ���
	/// </summary>
	/// <param name="mapCollisionData">�}�b�v����f�[�^</param>
	void JumpTypeCollision(const ObjectManager::MapCollisionData& mapCollisionData);

	/// <summary>
	/// �W�����v�͂̏Փˏ���
	/// </summary>
	/// <param name="mapCollisionData"�}�b�v����f�[�^></param>
	void JumpPowerCollision(const ObjectManager::MapCollisionData& mapCollisionData);

	/// <summary>
	/// �����t���O�̏Փˏ���
	/// </summary>
	/// <param name="mapCollisionData">�}�b�v����f�[�^</param>
	void AccelerationCollision(const ObjectManager::MapCollisionData& mapCollisionData);


private:

	//////////////
	// �ړ��֘A //
	//////////////


	// ��`
	Rect m_rect;

	// �ړ���`
	Rect m_moveRect;

	// �T�C�Y
	Vec2 m_size;

	// �n�ʂɂ��邩�ǂ���
	bool m_isGround;

	// �A�C�X�u���b�N�̏�ɂ��邩�ǂ���
	bool m_isIceBlock;
	
	// �R���x�A
	Conveyor m_conveyor;

	////////////////////
	// �v���C���[��� //
	////////////////////

	// �v���C���[�X�e�[�^�X
	GameData::PlayerStatus m_playerStatus;

	// ���G��Ԃ��ǂ���
	bool m_isInvincible;

	//////////////////
	// �X�e�[�g�֘A //
	//////////////////

	// �X�e�[�g�}�V��
	StateMachine<State>m_pStateMachine;

	////////////////////
	/// �W�����v�֘A ///
	////////////////////
	
	// �W�����v���
	JumpInfo m_jumpInfo;

};

