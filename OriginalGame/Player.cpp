#include "Player.h"
#include "Pad.h"
#include "ObjectManager.h"
#include <tuple>
#include "Controller.h"
#include "GameData.h"
#include <string>
#include "Sound.h"

namespace
{
	// �ʏ�ړ��X�s�[�h
	constexpr float kMoveNormalSpeed = 5.0f;
	// �����ړ��X�s�[�h
	constexpr float kMoveFastSpeed = kMoveNormalSpeed * 1.8f;
	// �x���ړ��X�s�[�h
	constexpr float kMoveSlowSpeed = kMoveNormalSpeed * 0.7f;

	// �T�C�Y
	const Vec2 kSize(20.0f, 30.0f);
	// ����T�C�Y
	const Vec2 kCollisionSize(19.0f, 29.0f);


	// �X�̖��C��
	constexpr float kFrictionIce = 0.98f;

	// �R���x�A�̑��x
	constexpr float kConveyorSpeed = kMoveNormalSpeed * 0.8f;
}

namespace
{
	// �ʏ�W�����v��
	constexpr float kJumpNormalPower = 15.0f;
	// ���W�����v��
	constexpr float kJumpStrongPower = kJumpNormalPower * 1.6f;
	// ��W�����v��
	constexpr float kJumpWeakPower = kJumpNormalPower * 0.7;



	// �W�����v��
	constexpr int kJumpCountMax = 2;

	// �d�͑�
	constexpr float kGravity = 1.5f;
	// �d�͏�
	constexpr float kSmallGravity = 0.8f;

	// �ő�ړ���
	constexpr float kMaxDir = 20.0f;
}


namespace Graph
{
	// �g�嗦
	const double kScale = 1.5;
	// �c�������l
	const float kAdjustmentValue = (5.0f);
	
	// �L�����N�^�[�`��̒����l��\���\����
	struct CharacterDrawAdjustment
	{
		// ���W�����l
		Vec2 adjustmentPos = Vec2();

		// �p�x
		float angle = 0.0f;
	};

	// �L�����N�^�[�`��̒����l�̔z��
	const CharacterDrawAdjustment kCharacterDrawAdjustment[4] =
	{
		// ��
		{Vec2(0.0f, kAdjustmentValue), 180.0f},
		// ��
		{Vec2(0.0f, -kAdjustmentValue), 0.0f},
		// ��
		{Vec2(kAdjustmentValue, 0.0f), 90.0f},
		// �E
		{Vec2(-kAdjustmentValue, 0.0f), 270.0f},
	};
}


namespace Anime
{
	const ObjectBase::AnimationRange kAnimationRange[4] =
	{
		{ 0, 2, 1,1 },// ��
		{ 6, 8, 7 ,7},	// ��
		{ 9, 11, 10 ,10},	// ��
		{ 3, 5, 4 ,4},	// �E
	};

	// �A�j���[�V�������x
	constexpr int kAnimeSpeed = 5;
}

namespace Shot
{
	// �V���b�g�̃X�s�[�h
	constexpr float kSpeed = 10.0f;
}


Player::Player() :
	m_moveRect(),
	m_rect(),
	m_size(),
	m_isGround(),
	m_isIceBlock(),
	m_conveyor(),
	m_playerStatus(),
	m_pStateMachine(),
	m_jumpInfo(),
	m_isInvincible(false)
{
}

Player::~Player()
{
}

void Player::Init()
{
	// ���W���Q�[���f�[�^�ɑ��
	GameData::GetInstance()->SetPlayerPos(m_pos);

	// �I�u�W�F�N�gID�ݒ�
	m_objectID = ObjectID::Player;

	// �X�e�[�g�}�V���̏�����
	StateInit();
}

void Player::Update()
{
	// �X�e�[�g�}�V���̍X�V
	m_pStateMachine.Update();

	// ���X�|�[��
	Respawn();
}

void Player::Draw()
{
	// �X�e�[�g�}�V���̕`��
	m_pStateMachine.Draw();
}


void Player::StateInit()
{
	// �X�e�[�g�}�V���̏������AEntry
	auto dummy = []() {};

	// �ʏ�X�e�[�g
	{
		auto enter = [this]() { StateNormalEnter(); };
		auto update = [this]() { StateNormalUpdate(); };
		auto draw = [this]() { StateNormalDraw(); };
		auto exit = [this]() { StateNormalExit(); };

		m_pStateMachine.AddState(State::Normal, enter, update, draw, exit);
	}
	// ���S�X�e�[�g
	{
		m_pStateMachine.AddState(State::Dead, dummy, dummy, dummy, dummy);
	}

	// �����X�e�[�g��ݒ�
	m_pStateMachine.SetState(State::Normal);
}

void Player::StateNormalEnter()
{

	// �v���C���[�������Ă��邩�ǂ�����ݒ�
	GameData::GetInstance()->SetIsPlayerAlive(true);

	// �v���C���[�X�e�[�^�X���擾
	m_playerStatus = GameData::GetInstance()->GetPlayerStatus();

	// �d�͕����ύX
	ChangeGravityDirection(m_playerStatus.gravityDirection);

	// �A�C�X�u���b�N�t���O��false�ɂ���
	m_isIceBlock = false;


	// �R���x�A��񏉊���
	{
		// �R���x�A�ɏ���Ă��邩�ǂ���
		m_conveyor.isFrag = false;

		// �R���x�A�̑��x
		m_conveyor.speed = kConveyorSpeed;
	}

	// �A�j���[�V����
	{
		// �A�j���[�V�����f�[�^������
		m_animationDetails.frameSpeed = Anime::kAnimeSpeed;

		// ����������
		m_animationDetails.direction[0] = Direction::Left;

		// �A�j���[�V�����ԍ�������
		m_animationDetails.number = Anime::kAnimationRange[static_cast<int>(m_animationDetails.direction[0])].stopNo;

		// �A�j���[�V�����^�C�v������
		m_animationDetails.type = AnimationType::Idle;
	}

}

void Player::StateNormalUpdate()
{
	// �ړ�����
	Move();

	// �W�����v����
	Jump();

	// �����蔻��
	Collision();

	// �A�j���[�V��������
	Animation();

	if (Controller::GetInstance()->IsTriggerKey(KEY_INPUT_M))
	{
		if (m_isInvincible)
		{
			m_isInvincible = false;
		}
		else
		{
			m_isInvincible = true;
		}
	}

}

void Player::StateNormalDraw()
{
	// ���G�Ȃ�v���C���[�𔼓����ɂ���
	if (m_isInvincible)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	}




	// �I�t�Z�b�g�l���擾
	const Vec2 offset = GameData::GetInstance()->GetCameraPos();

	Vec2 pos = m_pos + offset;
	pos += Graph::kCharacterDrawAdjustment[static_cast<int>(m_playerStatus.gravityDirection)].adjustmentPos;

	// ��]�p�x
	const float rota = EvoLib::Convert::ConvertAngleToRadian(Graph::kCharacterDrawAdjustment[static_cast<int>(m_playerStatus.gravityDirection)].angle);

	// ���]�t���O
	const bool isReverse =
		m_playerStatus.gravityDirection == Direction::Right ||
		m_playerStatus.gravityDirection == Direction::Top;

	// �v���C���[�`��
	DrawRotaGraphF(
		pos.x,
		pos.y,
		Graph::kScale, rota,
		m_graphicHandle[m_animationDetails.number], true, isReverse);


	// �����x�����ɖ߂�
	if (m_isInvincible)
	{
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}



	// �f�o�b�O�`��
#if(false)
		// �v���C���[�̓����蔻�蔼�a��`��
	DrawCircle(pos.x, pos.y, kCollisionRadius, 0xff0000, false);



	// �v���C���[���W
	DrawFormatString(0, 15 * 1, 0xffffff, "���WX:%f,���WY:%f,", m_pos.x, m_pos.y);

	// �`����W���v�Z
	const Rect drawRect = EvoLib::Convert::PosToRect(m_pos + offset, m_size);

	// �ړ��\�͈͂̋�`���擾
	Rect drawMoveRect = Rect();

	drawMoveRect.left = m_moveRect.left + offset.x;
	drawMoveRect.right = m_moveRect.right + offset.x;
	drawMoveRect.bottom = m_moveRect.bottom + offset.y;
	drawMoveRect.top = m_moveRect.top + offset.y;


	// �v���C���[�`��
	DrawBoxAA(drawRect.left, drawRect.top, drawRect.right, drawRect.bottom,
		0xff0000, true);

	// �ړ��ł���ꏊ��`��
	DrawBoxAA(drawMoveRect.left, drawMoveRect.top, drawMoveRect.right, drawMoveRect.bottom,
		0x0000ff, false);
#endif
}

void Player::StateNormalExit()
{
	// ���S�����Đ�
	Sound::GetInstance()->Play(kSoundFileName[static_cast<int>(SoundName::Dead)]);

	// �v���C���[�������Ă��邩�ǂ�����ݒ�
	GameData::GetInstance()->SetIsPlayerAlive(false);

	// �v���C���[�̎��S�񐔂��J�E���g�A�b�v
	{
		// ���S�񐔃J�E���g�A�b�v
		m_playerStatus.deathCount++;

		// �v���C���[�̎��S�񐔂�9999�𒴂�����999�ɂ���
		if (m_playerStatus.deathCount > 9999)
		{
			m_playerStatus.deathCount = 9999;
		}

		// ���S�񐔂�ݒ�
		GameData::GetInstance()->SetDeathCount(m_playerStatus.deathCount);
	}
}


void Player::Respawn()
{
	// �Z�[�u�|�C���g�Z�����擾����
	if (Controller::GetInstance()->IsTrigger(Controller::ControllerButton::RESPAWN))
	{
		// �X�e�[�W��ύX���邩�ǂ���
		bool isChangeStage = false;

		// �Z�[�u�|�C���g���W���擾����
		std::tie(isChangeStage, m_pos) = m_pObjectManager->GetSavePointPos();

		// ���W���l�p�`���ɕϊ�
		m_square = EvoLib::Convert::RectToSquare(EvoLib::Convert::PosToRect(m_pos, m_size));


		// �X�e�[�W��ύX���Ȃ��ꍇ�A�X�e�[�g���m�[�}���ɂ���
		if (!isChangeStage)
		{
			m_pStateMachine.SetState(State::Normal);

			// �Z�[�u����v���C���[�̃X�e�[�^�X���擾
			m_playerStatus = GameData::GetInstance()->GetPlayerStatus();
		}

		// ���X�^�[�g�����Đ�
		Sound::GetInstance()->Play(kSoundFileName[static_cast<int>(SoundName::Restart)]);

		// �W�����v�͂�������
		m_jumpInfo.fallSpeed = 0.0f;
	}
}

void Player::Move()
{

	// �O�̃t���[���̃v���C���[�̌�����ۑ�
	for (int i = 1; i > 0; i--)
	{
		m_animationDetails.direction[i] = m_animationDetails.direction[i - 1];
	}


	// �ړ���
	Vec2 inputVec = Vec2();

	// �ړ��X�s�[�h
	float moveSpeed = 0.0f;

	if(m_playerStatus.moveSpeed == GameData::MoveSpeed::Normal)
	{
		moveSpeed = kMoveNormalSpeed;
	}
	else if (m_playerStatus.moveSpeed == GameData::MoveSpeed::Fast)
	{
		moveSpeed = kMoveFastSpeed;
	}
	else if (m_playerStatus.moveSpeed == GameData::MoveSpeed::Slow)
	{
		moveSpeed = kMoveSlowSpeed;
	}


	if (m_playerStatus.gravityDirection == Direction::Top ||
		m_playerStatus.gravityDirection == Direction::Bottom)
	{
		// �p�b�h���g�p�����ړ�
		if (Controller::GetInstance()->IsPress(Controller::ControllerButton::RIGHT))
		{
			inputVec.x += moveSpeed;

			// �����Ă���������E�ɂ���
			m_animationDetails.direction[0] = Direction::Right;
		}
		if (Controller::GetInstance()->IsPress(Controller::ControllerButton::LEFT))
		{
			inputVec.x -= moveSpeed;

			// �����Ă�����������ɂ���
			m_animationDetails.direction[0] = Direction::Left;
		}

		// �ړ��ʂ�0.0f�̏ꍇ�A�A�j���[�V�������A�C�h���ɂ���
		if (inputVec.x == 0.0f)
		{
			m_animationDetails.type = AnimationType::Idle;
			m_animationDetails.number = 
				Anime::kAnimationRange[static_cast<int>(m_animationDetails.direction[0])].stopNo;
		}
		else
		{
			m_animationDetails.type = AnimationType::Move;
		}

	}
	else
	{
		// �p�b�h���g�p�����ړ�
		if (Controller::GetInstance()->IsPress(Controller::ControllerButton::DOWN))
		{
			inputVec.y += moveSpeed;

			// �����Ă���������E�ɂ���
			m_animationDetails.direction[0] = Direction::Right;
		}
		if (Controller::GetInstance()->IsPress(Controller::ControllerButton::UP))
		{
			inputVec.y -= moveSpeed;

			// �����Ă�����������ɂ���
			m_animationDetails.direction[0] = Direction::Left;
		}

		// �ړ��ʂ�0.0f�̏ꍇ�A�A�j���[�V�������A�C�h���ɂ���
		if (inputVec.y == 0.0f)
		{
			m_animationDetails.type = AnimationType::Idle;
			m_animationDetails.number = 
				Anime::kAnimationRange[static_cast<int>(m_animationDetails.direction[0])].stopNo;
		}
		else
		{
			m_animationDetails.type = AnimationType::Move;
		}

	}


	// �R���x�A�ɏ���Ă���ꍇ�A�ړ��ʂ�ύX����
	if (m_isGround &&
		m_conveyor.isFrag)
	{
		if (m_playerStatus.gravityDirection == Direction::Top ||
			m_playerStatus.gravityDirection == Direction::Bottom)
		{
			if (m_conveyor.direction == Direction::Right)
			{
				inputVec.x += m_conveyor.speed;
			}
			else if (m_conveyor.direction == Direction::Left)
			{
				inputVec.x += -m_conveyor.speed;
			}
		}
		else
		{
			if (m_conveyor.direction == Direction::Top)
			{
				inputVec.y += -m_conveyor.speed;
			}
			else if (m_conveyor.direction == Direction::Bottom)
			{
				inputVec.y += m_conveyor.speed;
			}
		}

		// �R���x�A�ɏ���Ă���ꍇ�A�ړ��ʂ�ύX����
		m_vec = inputVec;
	}

	// �A�C�X�u���b�N�̏ꍇ�A�ړ��ʂ�ύX����
	if(m_isIceBlock)
	{
		m_vec += inputVec;

		m_vec.x = EvoLib::Calculation::Clamp(m_vec.x, -kMoveNormalSpeed, kMoveNormalSpeed);
		m_vec.y = EvoLib::Calculation::Clamp(m_vec.y, -kMoveNormalSpeed, kMoveNormalSpeed);

		m_vec *= kFrictionIce;

		return;
	}

	// �ړ��ʂ���
	m_vec = inputVec;
}

void Player::Jump()
{
	// �{�^�����������Ƃ��A�W�����v�J�E���g��0�ȏ�Ȃ�΃W�����v�͂�^����
	if (Controller::GetInstance()->IsTrigger(Controller::ControllerButton::JUMP))
	{

		// �W�����v�J�E���g��0�ȏ�Ȃ�΃W�����v�͂�^����
		if (m_jumpInfo.jumpCount > 0 ||
			m_playerStatus.jumpType == GameData::JumpType::Infinite)
		{
			// �W�����v�t���O��true�ɂ���
			m_jumpInfo.isJump = true;

			// �W�����v��
			float jumpPower = 0.0f;

			if(m_playerStatus.jumpPower == GameData::JumpPower::Normal)
			{
				jumpPower = kJumpNormalPower;
			}
			else if (m_playerStatus.jumpPower == GameData::JumpPower::Strong)
			{
				jumpPower = kJumpStrongPower;
			}
			else if (m_playerStatus.jumpPower == GameData::JumpPower::Weak)
			{
				jumpPower = kJumpWeakPower;
			}

			// �W�����v�͂�^����
			m_jumpInfo.fallSpeed = -jumpPower;


			// �W�����v�^�C�v��Second�Ȃ�΁A�W�����v�J�E���g�����炷
			if (m_playerStatus.jumpType == GameData::JumpType::Second)
			{
				// �W�����v�J�E���g�����炷
				m_jumpInfo.jumpCount--;
			}
			
			// �W�����v�����Đ�
			Sound::GetInstance()->Play(kSoundFileName[static_cast<int>(SoundName::Jump)]);
		}
	}

	// ���ł����ꍇ�̓{�^���������Ă��邩�ǂ����ŗ����X�s�[�h���ς��
	if (m_jumpInfo.isJump)
	{
		// �{�^���������Ă��邩�ǂ����ŁA�W�����v�͂��ς��
		if (Controller::GetInstance()->IsPress(Controller::ControllerButton::JUMP))
		{
			// �������d�͂�^����
			m_jumpInfo.fallSpeed += kSmallGravity;
		}
		else
		{
			// �傫���d�͂�^����
			m_jumpInfo.fallSpeed += kGravity;
		}
	}
	else
	{
		// �W�����v���Ă��Ȃ�������ʏ�̏d�͂�^����
		m_jumpInfo.fallSpeed += kGravity;
	}

	
	if (m_playerStatus.gravityDirection == Direction::Top ||
		m_playerStatus.gravityDirection == Direction::Bottom)
	{
		// �ړ��ʂɗ����X�s�[�h��������
		m_vec.y = m_jumpInfo.fallSpeed;


		if (m_playerStatus.gravityDirection == Direction::Top)
		{
			// �ړ��ʂɗ����X�s�[�h��������
			m_vec.y = -m_jumpInfo.fallSpeed;
		}
		else
		{
			// �ړ��ʂɗ����X�s�[�h��������
			m_vec.y = m_jumpInfo.fallSpeed;
		}

		// ���ȏ�̑��x�ɂȂ����瑬�x��}����
		if (m_vec.y > kMaxDir)
		{
			m_vec.y = kMaxDir;
		}
	}
	else
	{
		// �ړ��ʂɗ����X�s�[�h��������
		m_vec.x = m_jumpInfo.fallSpeed;


		if (m_playerStatus.gravityDirection == Direction::Left)
		{
			// �ړ��ʂɗ����X�s�[�h��������
			m_vec.x = -m_jumpInfo.fallSpeed;
		}
		else
		{
			// �ړ��ʂɗ����X�s�[�h��������
			m_vec.x = m_jumpInfo.fallSpeed;
		}

		// ���ȏ�̑��x�ɂȂ����瑬�x��}����
		if (m_vec.x > kMaxDir)
		{
			m_vec.x = kMaxDir;
		}
	}

}

void Player::Collision()
{

	// ���W���l�p�`���ɕϊ�
	m_square = EvoLib::Convert::RectToSquare(EvoLib::Convert::PosToRect(m_pos, m_size));


	// �n�ʂ̓����蔻��
	GroundCollision();

	// ���`���
	PosLinearInterpolation();
}

void Player::Animation()
{
	if (m_animationDetails.direction[0] != m_animationDetails.direction[1])
	{
		m_animationDetails.number = Anime::kAnimationRange[static_cast<int>(m_animationDetails.direction[0])].dirNo;
	}

	// �ړ��ȊO�̏ꍇ�A�A�j���[�V�������s��Ȃ�
	if (m_animationDetails.type != AnimationType::Move)
	{
		return;
	}

	
	// �A�j���[�V�����ԍ����X�V
	m_animationDetails.number = AnimationNamberUpdate(m_animationDetails, Anime::kAnimationRange[static_cast<int>(m_animationDetails.direction[0])]);
}

void Player::GroundCollision()
{
	// ���S���W�����`�����߂�
	m_rect = EvoLib::Convert::PosToRect(m_pos, m_size);

	// �}�b�v�`�b�v�̃T�C�Y���擾
	const float mapChipSize = m_pObjectManager->GetMapInfoData().mapChip.chipSize;

	// �}�b�v�`�b�v�̍ő�Z�����擾
	const Cell maxCell = Cell(m_pObjectManager->GetMapInfoData().mapChip.mapWidth, m_pObjectManager->GetMapInfoData().mapChip.mapHeight);

	// �n�ʃZ���ԍ�
	std::vector<int>groundCellNumber;
	groundCellNumber.push_back(static_cast<int>(ObjectManager::ChipType::Ground));
	groundCellNumber.push_back(static_cast<int>(ObjectManager::ChipType::IceBlock));
	groundCellNumber.push_back(static_cast<int>(ObjectManager::ChipType::TopConveyor));
	groundCellNumber.push_back(static_cast<int>(ObjectManager::ChipType::BottomConveyor));
	groundCellNumber.push_back(static_cast<int>(ObjectManager::ChipType::LeftConveyor));
	groundCellNumber.push_back(static_cast<int>(ObjectManager::ChipType::RigthConveyor));
	groundCellNumber.push_back(static_cast<int>(ObjectManager::ChipType::TransparentBlock));


	// �ړ��\�͈͂̋�`���擾
	m_moveRect = EvoLib::Calculation::CalculateRectangleMovementRange
	(m_rect, maxCell, mapChipSize, m_pObjectManager->GetMapChipNumber(), groundCellNumber);



	// �擾������`��m_pos�̈ړ��\�͈͂ɕϊ�
	m_moveRect.left += m_size.x * 0.5f;
	m_moveRect.right -= m_size.x * 0.5f;
	m_moveRect.top += m_size.y * 0.5f;
	m_moveRect.bottom -= m_size.y * 0.5f;


	// �ړ��ʂ����W�ɑ��
	m_pos += m_vec;



	// �n�ʔ��菉����
	m_isGround = false;


	if (m_playerStatus.gravityDirection == Direction::Top ||
		m_playerStatus.gravityDirection == Direction::Bottom)
	{
		if (m_pos.x < m_moveRect.left)
		{
			m_pos.x = m_moveRect.left;
			m_vec.x = 0.0f;
		}
		if (m_pos.x > m_moveRect.right)
		{
			m_pos.x = m_moveRect.right;
			m_vec.x = 0.0f;
		}

		if (m_playerStatus.gravityDirection == Direction::Bottom)
		{

			if (m_pos.y < m_moveRect.top)
			{
				m_pos.y = m_moveRect.top;

				// �������x��0.0f�ɂ���
				m_jumpInfo.fallSpeed = 0.0f;

				m_vec.y = 0.0f;
			}
			if (m_pos.y > m_moveRect.bottom)
			{
				// �������x��0.0f�ɂ���
				m_jumpInfo.fallSpeed = 0.0f;

				// �n�ʃt���O��true�ɂ���
				m_isGround = true;

				m_pos.y = m_moveRect.bottom;
				m_vec.y = 0.0f;
			}
		}
		else
		{
			if (m_pos.y < m_moveRect.top)
			{
				// �n�ʃt���O��true�ɂ���
				m_isGround = true;

				// �������x��0.0f�ɂ���
				m_jumpInfo.fallSpeed = 0.0f;

				m_pos.y = m_moveRect.top;
				m_vec.y = 0.0f;
			}
			if (m_pos.y > m_moveRect.bottom)
			{
				// �������x��0.0f�ɂ���
				m_jumpInfo.fallSpeed = 0.0f;

				m_pos.y = m_moveRect.bottom;
				m_vec.y = 0.0f;
			}
		}
	}
	else
	{
	
		if (m_pos.y < m_moveRect.top)
		{
			m_pos.y = m_moveRect.top;
			m_vec.y = 0.0f;
		}
		if (m_pos.y > m_moveRect.bottom)
		{
			m_pos.y = m_moveRect.bottom;
			m_vec.y = 0.0f;
		}

		if (m_playerStatus.gravityDirection == Direction::Left)
		{

			if (m_pos.x < m_moveRect.left)
			{
				// �������x��0.0f�ɂ���
				m_jumpInfo.fallSpeed = 0.0f;

				// �n�ʃt���O��true�ɂ���
				m_isGround = true;

				m_pos.x = m_moveRect.left;
				m_vec.x = 0.0f;
			}
			if (m_pos.x > m_moveRect.right)
			{
				// �������x��0.0f�ɂ���
				m_jumpInfo.fallSpeed = 0.0f;

				m_pos.x = m_moveRect.right;
				m_vec.x = 0.0f;
			}
		}
		else
		{
			if (m_pos.x < m_moveRect.left)
			{
				// �������x��0.0f�ɂ���
				m_jumpInfo.fallSpeed = 0.0f;

				m_pos.x = m_moveRect.left;
				m_vec.x = 0.0f;
			}
			if (m_pos.x > m_moveRect.right)
			{
		
				// �������x��0.0f�ɂ���
				m_jumpInfo.fallSpeed = 0.0f;

				// �n�ʃt���O��true�ɂ���
				m_isGround = true;

				m_pos.x = m_moveRect.right;
				m_vec.x = 0.0f;
			}
		}
	}


	if(m_isGround)
	{
		// �n�ʂɒ����Ă���̂ŁA�W�����v�t���O��false�ɂ���
		m_jumpInfo.isJump = false;

		// �W�����v�J�E���g�̍ő�l��������
		m_jumpInfo.jumpCount = kJumpCountMax;

		// �A�C�X�u���b�N�t���O��false�ɂ���
		m_isIceBlock = false;
	}



	// ���W���Q�[���f�[�^�ɑ��
	GameData::GetInstance()->SetPlayerPos(m_pos);
}

void Player::PosLinearInterpolation()
{
	// �O�̍��W
	const Vec2 beforePos = m_pos - m_vec;

	// ���`��Ԑ����v�Z
	const int iinearInterpolationCount =
		EvoLib::Calculation::InearInterpolationCount(beforePos, m_vec, kCollisionSize);

	

	// ���`��ԍ��W���v�Z
	std::vector<Vec2> iinearInterpolationPos =
		EvoLib::Calculation::InearInterpolationPos(beforePos, m_vec, iinearInterpolationCount);

	
	// ���`��Ԑ���0�Ȃ�΁A���W�Ɉړ��ʂ𑫂������̂�z��ɓ����
	if (iinearInterpolationCount == 0)
	{
		// �ړ���̍��W��������
		iinearInterpolationPos.push_back(m_pos);
	}

	// ���`�␳��for������
	for (int i = 0; i < static_cast<int>(iinearInterpolationPos.size()); i++)
	{
		// �}�b�v�`�b�v�̓����蔻��
		MapChipCollision(iinearInterpolationPos[i]);
	}
}

void Player::MapChipCollision(const Vec2& pos)
{
	// �R���x�A�t���O������
	m_conveyor.isFrag = false;

	// �}�b�v����f�[�^���擾
	std::vector<std::vector<ObjectManager::MapCollisionData>> mapCollisionData =
		m_pObjectManager->GetMapInfoData().mapCollisionData;

	// �}�b�v�̕��ƍ������擾
	const int mapWidth = static_cast<int>(mapCollisionData.size());
	const int mapHeight = static_cast<int>(mapCollisionData[0].size());




	// ���W���l�p�`���ɕϊ�
	const Square mapSquare = EvoLib::Convert::RectToSquare(EvoLib::Convert::PosToRect(pos, m_size));


	for (int y = 0; y < mapHeight; y++)
	{
		for (int x = 0; x < mapWidth; x++)
		{
			//�}�b�v����f�[�^���v���C���[�̔���͈͊O�̏ꍇ�A���̃��[�v�Ɉڂ�
			if (!mapCollisionData[x][y].playerRangeFlag)
			{
				continue;
			}

			// �l�p�`���m�̓����蔻��
			if (!EvoLib::Collision::IsSquareToSquare(mapCollisionData[x][y].square, mapSquare))
			{
				continue;
			}

			// �Z�[�u�|�C���g�̓����蔻����s�����ǂ���
			const bool isSavePointCollision =
				mapCollisionData[x][y].chipType == ObjectManager::ChipType::Save;


			// �}�b�v�ړ��t���O���s�����ǂ���
			const bool isMapMove =
				mapCollisionData[x][y].chipType == ObjectManager::ChipType::NextStage ||
				mapCollisionData[x][y].chipType == ObjectManager::ChipType::PreviouseStage;



			// �d�͕�����ύX���邩�ǂ���
			const bool isGravity =
				mapCollisionData[x][y].chipType == ObjectManager::ChipType::TopGravity ||
				mapCollisionData[x][y].chipType == ObjectManager::ChipType::BottomGravity ||
				mapCollisionData[x][y].chipType == ObjectManager::ChipType::LeftGravity ||
				mapCollisionData[x][y].chipType == ObjectManager::ChipType::RightGravity;

			// �A�C�X�u���b�N�̓����蔻����s�����ǂ���
			const bool isIceBlockCollision =
				mapCollisionData[x][y].chipType == ObjectManager::ChipType::IceBlock;

			// �R���x�A�̓����蔻����s�����ǂ���
			const bool isConveyorCollision =
				mapCollisionData[x][y].chipType == ObjectManager::ChipType::TopConveyor ||
				mapCollisionData[x][y].chipType == ObjectManager::ChipType::BottomConveyor ||
				mapCollisionData[x][y].chipType == ObjectManager::ChipType::LeftConveyor ||
				mapCollisionData[x][y].chipType == ObjectManager::ChipType::RigthConveyor;

			// �W�����v�^�C�v�u���b�N�̓����蔻����s�����ǂ���
			const bool isJumpTypeCollision =
				mapCollisionData[x][y].chipType == ObjectManager::ChipType::InfiniteJump ||
				mapCollisionData[x][y].chipType == ObjectManager::ChipType::SecondJump;

			// �W�����v�͂̕ύX�̓����蔻����s�����ǂ���
			const bool isJumpPowerCollision =
				mapCollisionData[x][y].chipType == ObjectManager::ChipType::NormalJumpPower ||
				mapCollisionData[x][y].chipType == ObjectManager::ChipType::StrongJumpPower ||
				mapCollisionData[x][y].chipType == ObjectManager::ChipType::WeakJumpPower;

			// �����x��ύX���邩�ǂ���
			const bool isAcceleration =
				mapCollisionData[x][y].chipType == ObjectManager::ChipType::Acceleration ||
				mapCollisionData[x][y].chipType == ObjectManager::ChipType::Deceleration ||
				mapCollisionData[x][y].chipType == ObjectManager::ChipType::NormalSpeed;

			// �Q�[�����I�����邩�ǂ���
			const bool isEndGame =
				mapCollisionData[x][y].chipType == ObjectManager::ChipType::EndGame;


			// �Z�[�u�|�C���g�̓����蔻����s�����ǂ���
			if (isSavePointCollision)
			{
				// �Z�[�u�|�C���g�̓����蔻��
				SavePointCollision(Cell(x, y));
			}

			// �}�b�v�ړ��̓����蔻����s�����ǂ���
			if (isMapMove)
			{
				// �}�b�v�`�b�v�̓����蔻��
				MapMove(mapCollisionData[x][y]);
			}

			// �d�͕�����ύX���邩�ǂ���
			if (isGravity)
			{
				// �d�͕�����ύX����
				Gravity(mapCollisionData[x][y]);
			}

			// �A�C�X�u���b�N�̓����蔻����s�����ǂ���
			if (isIceBlockCollision)
			{
				// �A�C�X�u���b�N�̓����蔻��
				IceBlockCollision();
			}

			// �R���x�A�̓����蔻����s�����ǂ���
			if (isConveyorCollision)
			{
				// �R���x�A�̓����蔻��
				ConveyorCollision(mapCollisionData[x][y]);
			}

			// �W�����v�^�C�v�u���b�N�̓����蔻����s�����ǂ���
			if (isJumpTypeCollision)
			{
				// �W�����v�^�C�v�u���b�N�̓����蔻��
				JumpTypeCollision(mapCollisionData[x][y]);
			}

			// �W�����v�͂̕ύX�̓����蔻����s�����ǂ���
			if (isJumpPowerCollision)
			{
				// �W�����v�͂̕ύX�̓����蔻��
				JumpPowerCollision(mapCollisionData[x][y]);
			}

			// �����x��ύX���邩�ǂ���
			if (isAcceleration)
			{
				// �����x��ύX����
				AccelerationCollision(mapCollisionData[x][y]);
			}

			// �Q�[�����I�����邩�ǂ���
			if (isEndGame)
			{
				// �I����b�ɃX�e�[�g��ύX
				m_pObjectManager->SetState(ObjectManager::State::EndTalk);
			}

			// ���݂��Ȃ��ꍇ�A���[�v�𔲂���
			if (!m_isExlist)
			{
				return;
			}
		}
	}



	// ���W���l�p�`���ɕϊ�
	const Square square = EvoLib::Convert::RectToSquare(EvoLib::Convert::PosToRect(pos, kCollisionSize));


	for (int y = 0; y < mapHeight; y++)
	{
		for (int x = 0; x < mapWidth; x++)
		{
			//�}�b�v����f�[�^���v���C���[�̔���͈͊O�̏ꍇ�A���̃��[�v�Ɉڂ�
			if (!mapCollisionData[x][y].playerRangeFlag)
			{
				continue;
			}

			// �l�p�`���m�̓����蔻��
			if (!EvoLib::Collision::IsSquareToSquare(mapCollisionData[x][y].square, square))
			{
				continue;
			}

			// ��Q���̓����蔻����s�����ǂ���
			const bool isObstacleCollision =
				mapCollisionData[x][y].chipType == ObjectManager::ChipType::TopNeedle ||
				mapCollisionData[x][y].chipType == ObjectManager::ChipType::BottomNeedle ||
				mapCollisionData[x][y].chipType == ObjectManager::ChipType::LeftNeedle ||
				mapCollisionData[x][y].chipType == ObjectManager::ChipType::RightNeedle ||
				mapCollisionData[x][y].chipType == ObjectManager::ChipType::DiedBlock;

			// ��Q���̓����蔻����s�����ǂ���
			if (isObstacleCollision)
			{
				// ��Q���̓����蔻��
				ObstacleCollision(mapCollisionData[x][y], mapSquare);
			}

			// ���݂��Ȃ��ꍇ�A���[�v�𔲂���
			if (!m_isExlist)
			{
				return;
			}
		}
	}

}

void Player::ObstacleCollision(const ObjectManager::MapCollisionData& mapCollisionData, const Square& square)
{
	if(m_isInvincible)
	{
		return;
	}



	// �l�p�`�Ǝl�p�`�̓����蔻��
	if (mapCollisionData.chipType == ObjectManager::ChipType::DiedBlock)
	{
		// �X�e�[�g���f�b�h�ɂ���
		m_pStateMachine.SetState(State::Dead);

		return;
	}

	// �O�p�`�̏����擾
	const Triangle needle = m_pObjectManager->ChipTypeToTriangle(mapCollisionData.chipType, mapCollisionData.square);

	// �O�p�`�Ǝl�p�`�̓����蔻��
	if (EvoLib::Collision::IsTriangleToSquare(needle, square))
	{
		// �X�e�[�g���f�b�h�ɂ���
		m_pStateMachine.SetState(State::Dead);
	}
}

void Player::SavePointCollision(const Cell& savePointCell)
{
	// �Z�[�u�|�C���g���Z�b�g����
	m_pObjectManager->SetSavePoint(savePointCell, m_playerStatus);
}

void Player::MapMove(const ObjectManager::MapCollisionData& mapCollisionData)
{

	// �v���C���[�X�e�[�^�X���
	GameData::GetInstance()->SetPlayerStatus(m_playerStatus);

	// ���̃X�e�[�W�ɐi��
	if (mapCollisionData.chipType == ObjectManager::ChipType::NextStage)
	{
		m_pObjectManager->StageMove(ObjectManager::MapSwitchType::NextStage);

		return;
	}

	// �O�̃X�e�[�W�ɖ߂�
	if (mapCollisionData.chipType == ObjectManager::ChipType::PreviouseStage)
	{
		m_pObjectManager->StageMove(ObjectManager::MapSwitchType::PreviouseStage);

		return;
	}
}

void Player::Gravity(const ObjectManager::MapCollisionData& mapCollisionData)
{

	Direction gravityDirection = Direction();

	// �d�͕�����ύX����
	if (mapCollisionData.chipType == ObjectManager::ChipType::TopGravity)
	{
		gravityDirection = Direction::Top;
	}
	else if (mapCollisionData.chipType == ObjectManager::ChipType::BottomGravity)
	{
		gravityDirection = Direction::Bottom;
	}
	else if(mapCollisionData.chipType == ObjectManager::ChipType::LeftGravity)
	{
		gravityDirection = Direction::Left;
	}
	else if (mapCollisionData.chipType == ObjectManager::ChipType::RightGravity)
	{
		gravityDirection = Direction::Right;
	}

	ChangeGravityDirection(gravityDirection);

}

void Player::ChangeGravityDirection(const Direction& gravityDirection)
{
	if (gravityDirection == Direction::Top ||
		gravityDirection == Direction::Bottom)
	{
		m_size = kSize;
	}
	else
	{
		m_size = Vec2(kSize.y, kSize.x);
	}

	// �d�͕�����ύX����
	m_playerStatus.gravityDirection = gravityDirection;
}

void Player::IceBlockCollision()
{
	m_isIceBlock = true;
}

void Player::ConveyorCollision(const ObjectManager::MapCollisionData& mapCollisionData)
{



	// �R���x�A�̕������擾
	if(mapCollisionData.chipType == ObjectManager::ChipType::TopConveyor)
	{
		m_conveyor.direction = Direction::Top;
	}
	else if(mapCollisionData.chipType == ObjectManager::ChipType::BottomConveyor)
	{
		m_conveyor.direction = Direction::Bottom;
	}
	else if(mapCollisionData.chipType == ObjectManager::ChipType::LeftConveyor)
	{
		m_conveyor.direction = Direction::Left;
	}
	else if(mapCollisionData.chipType == ObjectManager::ChipType::RigthConveyor)
	{
		m_conveyor.direction = Direction::Right;
	}

	// �R���x�A�ɏ���Ă���
	m_conveyor.isFrag = true;
}

void Player::JumpTypeCollision(const ObjectManager::MapCollisionData& mapCollisionData)
{
	if(mapCollisionData.chipType == ObjectManager::ChipType::InfiniteJump)
	{
		m_playerStatus.jumpType = GameData::JumpType::Infinite;
	}
	else if(mapCollisionData.chipType == ObjectManager::ChipType::SecondJump)
	{
		m_playerStatus.jumpType = GameData::JumpType::Second;
	}
}

void Player::JumpPowerCollision(const ObjectManager::MapCollisionData& mapCollisionData)
{
	if (mapCollisionData.chipType == ObjectManager::ChipType::StrongJumpPower)
	{
		m_playerStatus.jumpPower = GameData::JumpPower::Strong;
	}
	else if(mapCollisionData.chipType == ObjectManager::ChipType::WeakJumpPower)
	{
		m_playerStatus.jumpPower = GameData::JumpPower::Weak;
	}
	else if(mapCollisionData.chipType == ObjectManager::ChipType::NormalJumpPower)
	{
		m_playerStatus.jumpPower = GameData::JumpPower::Normal;
	}
}

void Player::AccelerationCollision(const ObjectManager::MapCollisionData& mapCollisionData)
{
	if(mapCollisionData.chipType == ObjectManager::ChipType::NormalSpeed)
	{
		m_playerStatus.moveSpeed = GameData::MoveSpeed::Normal;
	}
	else if(mapCollisionData.chipType == ObjectManager::ChipType::Acceleration)
	{
		m_playerStatus.moveSpeed = GameData::MoveSpeed::Fast;
	}
	else if(mapCollisionData.chipType == ObjectManager::ChipType::Deceleration)
	{
		m_playerStatus.moveSpeed = GameData::MoveSpeed::Slow;
	}
}