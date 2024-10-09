#include "ObjectManager.h"
#include "Player.h"
#include "Camera.h"
#include "game.h"
#include "TransparentBlockChip.h"
#include "Pause.h"
#include "MainScreen.h"
#include "Sound.h"
#include "MessageWindow.h"
#include "Controller.h"
#include "GameOver.h"

#include <cassert>
#include <string>
#include <filesystem>
#include <DxLib.h>



namespace
{
	// �}�b�v�f�[�^�t�@�C���p�X
	const std::string kFieldDataFilePath = "Data/MapData/mapData_";

	// �t�@�C���p�X�g���q
	const std::string kFilePathExtension = ".fmf";
}


namespace
{
	// �摜�f�[�^
	struct GraphData
	{
		// �O���t�B�b�N�t�@�C���p�X
		const char* const kFilePath;
		// ������
		const EvoLib::Load::DivNum kDivNum;
	};
}


namespace PlayerGraph
{
	// �v���C���[�O���t�B�b�N�f�[�^
	const GraphData kPlayerGraphData[] =
	{
		{ "Data/Graphic/Character/GameMain/Marisa.png", EvoLib::Load::DivNum(3, 4) },
	};
}

namespace TalkData
{
	const std::string kDataFilePath = "Data/Csv/Talk/TalkData_1.csv";
}

namespace ScoreGraph_GameMain
{
	// �ԍ��O���t�B�b�N�̃t�@�C����
	const char* kNumberGraphFileName = "Data/Graphic/Number/Number.png";
	// �X�R�A�O���t�B�b�N�̕�����
	const EvoLib::Load::DivNum kNumberGraphDivNum = EvoLib::Load::DivNum(10, 1);

	// �d�؂�O���t�B�b�N�̃t�@�C����
	const char* const kSeparateGraphFileName = "Data/Graphic/Number/Separate.png";
	// �J�E���g�O���t�B�b�N�̃t�@�C����
	const char* const kCountGraphFileName = "Data/Graphic/Number/Count.png";

	// �N���A���g���C�񐔃e�L�X�g�O���t�B�b�N�̃t�@�C����
	const char* const kClearRetryTextGraphFileName = "Data/Graphic/GameMain/CountText.png";


	// �^�C���X�R�A�̈ʒu
	const Vec2 kTimeScorePos = Vec2(150.0f, 20.0f);
	// �f�X�J�E���g�̈ʒu
	const Vec2 kDeathCountPos = Vec2(kTimeScorePos.x, kTimeScorePos.y + 30.0f);

	// �O���t�B�b�N���m�̊Ԋu
	const float kTextGraphInterval = -80.0f;

	// �N���A���g���C�񐔃e�L�X�g�̈ʒu
	const Vec2 kClearTextPos = Vec2(kTimeScorePos.x + kTextGraphInterval, kTimeScorePos.y);
	const Vec2 kRetryTextPos = Vec2(kDeathCountPos.x + kTextGraphInterval, kDeathCountPos.y);


	// �e�L�X�g�O���t�B�b�N�T�C�Y
	constexpr double kTextGraphSize = 0.4;

	// �O���t�B�b�N���m�̊Ԋu
	static float kGraphInterval = 0.0f;
	// �O���t�B�b�N���m�̊Ԋu�̐ݒ�
	const float kGraphIntervalSetting = -15.0f;

	// �O���t�B�b�N�T�C�Y
	constexpr double kGraphSize = 0.4;

	// �X�R�A�O���t�B�b�N�̔��a�T�C�Y
	const float kScoreGraphRadius = 120.0f;

	// �v���C���[���a�T�C�Y
	const float kPlayerRadius = 180.0f;
}

ObjectManager::ObjectManager() :
	m_object(),
	m_mapInfoData(),
	m_screenCircle(),
	m_testMapGraph(),
	m_pStateMachine(),
	m_playerGraphHandle(),
	m_scoreGraphData(),
	m_pPlatinumLoader(std::make_shared<PlatinumLoader>()),
	m_pCamera(std::make_shared<Camera>()),
	m_pPause(std::make_shared<Pause>()),
	m_pOpeningMessageWindow(std::make_shared<MessageWindow>()),
	m_pEndTalkMessageWindow(std::make_shared<MessageWindow>()),
	m_pGameOver(std::make_shared<GameOver>())
{
}

ObjectManager::~ObjectManager()
{
	for (auto& graph : m_testMapGraph)
	{
		DeleteGraph(graph);
	}

	for (auto& graph : m_playerGraphHandle)
	{
		DeleteGraph(graph);
	}
	m_mapInfoData.mapCollisionData.clear();

	m_object.clear();

	m_pPlatinumLoader.reset();

	m_pCamera.reset();

	m_pPause.reset();

	m_pOpeningMessageWindow.reset();

	m_pEndTalkMessageWindow.reset();

	m_pGameOver.reset();

	m_pMainScreen.reset();

	DeleteGraph(m_scoreGraphData.countGraphHandle);
	DeleteGraph(m_scoreGraphData.separateGraphHandle);
	for(auto& graph : m_scoreGraphData.clearRetryTextGraphHandle)
	{
		DeleteGraph(graph);
	}
}

void ObjectManager::Init()
{
	// �X�e�[�g������
	StateInit();
}

void ObjectManager::Update()
{
	// �J�����X�V
	m_pCamera->OffsetCalculation(GameData::GetInstance()->GetPlayerPos());

	// �|�[�Y�N���X�X�V
	m_pPause->Update();

	// �X�e�[�g�}�V���̍X�V
	m_pStateMachine.Update();

}

void ObjectManager::Draw()
{
	// �I�u�W�F�N�g�`��
	ObjectDraw();
	
	// �}�b�v�`��
	TestMapDraw();

	// �X�e�[�g�}�V���̕`��
	m_pStateMachine.Draw();

	// �Z�[�u�X�R�A�`��
	DrawSaveScore();
}

void ObjectManager::ChangeScene(const SceneMain::Scene& nextScene)
{
	// �V�[���ύX
	m_pMainScreen->ChangeScene(nextScene);
}

void ObjectManager::StateInit()
{
	// �X�e�[�g�}�V���̏������AEntry
	auto dummy = []() {};


	// �ݒ�X�e�[�g
	{
		auto enter = [this]() { StateSettingInit(); };
		
		m_pStateMachine.AddState(State::Setting, enter, dummy, dummy, dummy);
	}

	// �I�[�v�j���O�X�e�[�g
	{
		auto enter = [this]() { StateOpeningEnter(); };
		auto update = [this]() { StateOpeningUpdate(); };
		auto draw = [this]() { StateOpeningDraw(); };
		auto exit = [this]() { StateOpeningExit(); };
		

		m_pStateMachine.AddState(State::Opening, enter, update, draw, exit);
	}

	// �ʏ�X�e�[�g
	{
		auto update = [this]() { StateNormalUpdate(); };
		auto draw = [this]() { StateNormalDraw(); };
		

		m_pStateMachine.AddState(State::Normal, dummy, update, draw, dummy);
	}

	// �I����b�X�e�[�g
	{
		auto enter = [this]() { StateEndTalkEnter(); };
		auto update = [this]() { StateEndTalkUpdate(); };
		auto draw = [this]() { StateEndTalkDraw(); };
		auto exit = [this]() { StateEndTalkExit(); };
		
		m_pStateMachine.AddState(State::EndTalk, enter, update, draw, exit);
	}

	// �|�[�Y�X�e�[�g
	{	
		auto update = [this]() { StatePauseUpdate(); };
		auto draw = [this]() { StatePauseDraw(); };
		

		m_pStateMachine.AddState(State::Pause, dummy, update, draw, dummy);
	}

	// �G���f�B���O�X�e�[�g
	{
		auto enter = [this]() { StateEndingEnter(); };


		m_pStateMachine.AddState(State::Ending, enter, dummy, dummy, dummy);
	}

	// �����X�e�[�g��ݒ�
	SetState(State::Setting);
}

void ObjectManager::StateSettingInit()
{
	// �X�e�[�g
	State state = State::Opening;

	// �Q�[���f�[�^������������Ă��Ȃ���΁A�m�[�}���X�e�[�g�ɕύX
	if (!GameData::GetInstance()->GetSaveData().isInit)
	{
		state = State::Normal;
	}



	// ���[�h
	Load();

	// �}�b�v�֘A�����ݒ�
	InitMap();

	// �X�N���[���T�[�N��������
	InitScreenCircle();


	// �J�����N���X�ɃI�u�W�F�N�g�t�@�N�g���[�N���X�|�C���^�𑗂�
	m_pCamera->SetObjectFactoryPointer(shared_from_this());

	// �|�[�Y�N���X�ɃI�u�W�F�N�g�t�@�N�g���[�N���X�|�C���^�𑗂�
	m_pPause->SetObjectFactoryPointer(shared_from_this());

	// �|�[�Y�N���X������
	m_pPause->Init();

	// �Q�[���I�[�o�[�N���X������
	m_pGameOver->Init();

	// �}�b�v�O���t�B�b�N���
	{
		EvoLib::Load::DivNum divNum = EvoLib::Load::DivNum(16, 16);

		m_testMapGraph = EvoLib::Load::LoadDivGraph_EvoLib_Revision("Data/MapData/mapSetting.png", divNum);
	}


	// ���b�Z�[�W�E�B���h�E�f�[�^���[�h
	m_pEndTalkMessageWindow->LoadData(TalkData::kDataFilePath);

	// BGM�Đ�
	Sound::GetInstance()->Play(kSoundFileName[static_cast<int>(SoundName::BGM)]);

	// �X�e�[�g��ύX
	SetState(state);
}

void ObjectManager::StateOpeningEnter()
{
	// ���b�Z�[�W�E�B���h�E�f�[�^���[�h
	m_pOpeningMessageWindow->LoadData(TalkData::kDataFilePath);
}

void ObjectManager::StateOpeningUpdate()
{

	// �I�u�W�F�N�g�X�V
	ObjectUpdate(true);

	// �X�N���[�������ǂ����𒲂ׂ�
	FieldCheck();

	// ���b�Z�[�W�E�B���h�E�X�V
	m_pOpeningMessageWindow->Update();

	// ���b�Z�[�W�E�B���h�E���I�������玟�̃X�e�[�g�ɕύX
	if (m_pOpeningMessageWindow->IsAllTextEnd())
	{
		SetState(State::Normal);
	}
}

void ObjectManager::StateOpeningDraw()
{
	// ���b�Z�[�W�E�B���h�E�`��
	m_pOpeningMessageWindow->Draw();
}

void ObjectManager::StateOpeningExit()
{
	// ���b�Z�[�W�E�B���h�E������
	m_pOpeningMessageWindow->InitData();
}

void ObjectManager::StateNormalUpdate()
{
	// �I�u�W�F�N�g�X�V
	ObjectUpdate();

	// �X�N���[�������ǂ����𒲂ׂ�
	FieldCheck();

	// �I�u�W�F�N�g�폜
	ObjectErase();
	
	// ���Ԍv��
	GameData::GetInstance()->TimeCount();
}

void ObjectManager::StateNormalDraw()
{
	// �Q�[���I�[�o�[�N���X�`��
	m_pGameOver->Draw();
}

void ObjectManager::StateEndTalkEnter()
{

	//m_pEndTalkMessageWindow->ResetData();
}

void ObjectManager::StateEndTalkUpdate()
{
	// �X�N���[�������ǂ����𒲂ׂ�
	FieldCheck();

	// �J�����X�V
	m_pCamera->OffsetCalculation(GameData::GetInstance()->GetPlayerPos());

	// ���b�Z�[�W�E�B���h�E�X�V
	m_pEndTalkMessageWindow->Update();

	// ���b�Z�[�W�E�B���h�E���I�������玟�̃X�e�[�g�ɕύX
	if (m_pEndTalkMessageWindow->IsAllTextEnd())
	{
		SetState(State::Ending);
	}
}

void ObjectManager::StateEndTalkDraw()
{
	// ���b�Z�[�W�E�B���h�E�`��
	m_pEndTalkMessageWindow->Draw();
}

void ObjectManager::StateEndTalkExit()
{
}

void ObjectManager::StatePauseUpdate()
{
}

void ObjectManager::StatePauseDraw()
{
	// �|�[�Y�N���X�`��
	m_pPause->Draw();
}

void ObjectManager::StateEndingEnter()
{
	// �G���f�B���O�V�[���ɕύX
	m_pMainScreen->ChangeScene(SceneMain::Scene::Ending);
}

void ObjectManager::SetSavePoint(const Cell& cell, const GameData::PlayerStatus& playerStatus)
{
	// �Z�[�u�|�C���g�f�[�^��ݒ�
	GameData::GetInstance()->SetSavePointData(m_mapInfoData.mapNumber, cell, playerStatus);
}

void ObjectManager::SetState(const State& state)
{
	// �X�e�[�g��ݒ�
	m_pStateMachine.SetState(state);
}

void ObjectManager::Load()
{
	// �v���C���[�O���t�B�b�N���[�h
	{
		for (const auto& graphData : PlayerGraph::kPlayerGraphData)
		{
			m_playerGraphHandle = 
				(EvoLib::Load::LoadDivGraph_EvoLib_Revision(graphData.kFilePath, graphData.kDivNum));
		}
	}

	// �T�E���h���[�h
	{
		Sound::GetInstance()->Load(kSoundFileName,false);
	}

	// �X�R�A�O���t�B�b�N���[�h
	{
		m_scoreGraphData.numberGraphHandle =
			EvoLib::Load::LoadDivGraph_EvoLib_Revision(ScoreGraph_GameMain::kNumberGraphFileName, ScoreGraph_GameMain::kNumberGraphDivNum);

		m_scoreGraphData.separateGraphHandle = LoadGraph(ScoreGraph_GameMain::kSeparateGraphFileName);
		m_scoreGraphData.countGraphHandle = LoadGraph(ScoreGraph_GameMain::kCountGraphFileName);

		// �N���A���g���C�񐔃e�L�X�g�O���t�B�b�N���[�h
		m_scoreGraphData.clearRetryTextGraphHandle =
			EvoLib::Load::LoadDivGraph_EvoLib_Revision(ScoreGraph_GameMain::kClearRetryTextGraphFileName, EvoLib::Load::DivNum(1, 2));

		{
			// �O���t�B�b�N�̃T�C�Y���擾
			const Vec2 size = EvoLib::Calculation::GetGraphSize_EvoLib(m_scoreGraphData.numberGraphHandle, ScoreGraph_GameMain::kGraphSize);

			// �O���t�B�b�N�̊Ԋu��ݒ�
			ScoreGraph_GameMain::kGraphInterval = size.x + ScoreGraph_GameMain::kGraphIntervalSetting;
		}
	}
}

void ObjectManager::PlayerCreate(const Vec2& pos)
{
	// �v���C���[����
	m_object.push_back(std::make_shared<Player>());

	// �|�C���^�𑗂�
	m_object.back()->SetObjectFactory(shared_from_this());

	// �`�惉���N����
	m_object.back()->SetDrawRank(ObjectBase::DrawRank::Rank_1);

	// ���W����
	m_object.back()->SetPos(pos);

	// �O���t�B�b�N�n���h������
	m_object.back()->SetGraphicHandle(m_playerGraphHandle);

	// ����������
	m_object.back()->Init();
}

void ObjectManager::MapCollisionDataCreate(const std::vector<std::vector<int>>& mapData, const MapSwitchType& mapSwitchType)
{
	// �}�b�v�f�[�^
	std::vector<std::vector<MapCollisionData>>mapCollisionData(
		m_mapInfoData.mapChip.mapWidth, 
		std::vector<MapCollisionData>(m_mapInfoData.mapChip.mapHeight));

	// ���̃X�e�[�W�Z��
	Cell nextStageCell = Cell();

	// �O�̃X�e�[�W�Z��
	Cell previouseStageCell = Cell();

	// �v���C���[���������ꂽ���ǂ���
	bool isPlayerCreate = false;

	// �X�|�[���`�b�v��
	int spawnChip = 0;

	// ���̃X�e�[�W���W�`�b�v��
	int nextPosChip = 0;

	// �O�̃X�e�[�W���W�`�b�v��
	int previousePosChip = 0;

	// �{�X�X�|�[���t���O�`�b�v��
	int bossSpawnFragChip = 0;

	// �{�X�X�|�[�����W�`�b�v��
	int bossSpawnPosChip = 0;



	// ���ׂẴZ��������
	for (int y = 0; y < m_mapInfoData.mapChip.mapHeight; y++)
	{
		for (int x = 0; x < m_mapInfoData.mapChip.mapWidth; x++)
		{
			// �}�b�v�`�b�v�^�C�v�ɕϊ�
			const ChipType mapChipType = ChipType(mapData[x][y]);

			// �`�b�v�̐����J�E���g����
			{
				switch (mapChipType)
				{
				case ObjectManager::ChipType::NextStage:

				
					// ���̃X�e�[�W���W�Z������
					nextStageCell = Cell(x, y);
					break;
				case ObjectManager::ChipType::PreviouseStage:

					// �O�̃X�e�[�W���W�Z������
					previouseStageCell = Cell(x, y);
					break;
				case ObjectManager::ChipType::NextPos:

					// ���̃X�e�[�W���W�`�b�v���𑝂₷
					nextPosChip++;
					break;
				case ObjectManager::ChipType::PreviousePos:

					// �O�̃X�e�[�W���W�`�b�v���𑝂₷
					previousePosChip++;
					break;
				case ObjectManager::ChipType::SpawnPos:

					// �X�|�[���`�b�v���𑝂₷
					spawnChip++;
					break;
				default:
					break;
				}
			}


			// �}�b�v����f�[�^�ݒ�
			{
				// �`�b�v�^�C�v������
				mapCollisionData[x][y].chipType = ChipType(mapData[x][y]);

				// �l�p�`���v�Z
				mapCollisionData[x][y].square.A = Vec2((m_mapInfoData.mapChip.chipSize * x), (m_mapInfoData.mapChip.chipSize * y));
				mapCollisionData[x][y].square.B = Vec2((mapCollisionData[x][y].square.A.x + m_mapInfoData.mapChip.chipSize), mapCollisionData[x][y].square.A.y);
				mapCollisionData[x][y].square.C = Vec2(mapCollisionData[x][y].square.B.x, (mapCollisionData[x][y].square.B.y + m_mapInfoData.mapChip.chipSize));
				mapCollisionData[x][y].square.D = Vec2(mapCollisionData[x][y].square.A.x, mapCollisionData[x][y].square.C.y);

				// �~���v�Z
				mapCollisionData[x][y].circle =
					EvoLib::Convert::SquareToCircle(mapCollisionData[x][y].square);
			}

			// �v���C���[����
			{
				// �X�|�[�����邩�ǂ���
				const bool isSpwan =
					mapChipType == ChipType::SpawnPos &&
					mapSwitchType == MapSwitchType::Spawn;

				// ���̃X�e�[�W���W�Ɉړ����邩�ǂ���
				const bool isNextStagePos =
					mapChipType == ChipType::NextPos &&
					mapSwitchType == MapSwitchType::NextStage;

				// �O�̃X�e�[�W���W�Ɉړ����邩�ǂ���
				const bool isPreviouseStagePos =
					mapChipType == ChipType::PreviousePos &&
					mapSwitchType == MapSwitchType::PreviouseStage;

				// �X�|�[��
				if (isSpwan)
				{
					// �Z�[�u���𑗂�
					GameData::GetInstance()->SetSaveData(GameData::SaveData(false, Time(), m_mapInfoData.mapNumber, Cell(x, y)));
				}

				// �v���C���[����
				if (isSpwan ||
					isNextStagePos ||
					isPreviouseStagePos)
				{
					// �L�����N�^�[����
					PlayerCreate(EvoLib::Convert::CellToPos(Cell(x, y), m_mapInfoData.mapChip.chipSize));

					// �v���C���[�����t���O
					isPlayerCreate = true;
				}
			}

			// �}�b�v�`�b�v����
			{
				// �`�b�v�����t���O
				const bool isCreateChip =
					mapCollisionData[x][y].chipType == ChipType::TransparentBlock;

				// �`�b�v����
				if (isCreateChip)
				{
					// �}�b�v�`�b�v����
					MapChipCreate(mapCollisionData[x][y]);
				}
			}
		}
	}

	if (mapSwitchType == MapSwitchType::SaveData)
	{
		// �L�����N�^�[����
		PlayerCreate(EvoLib::Convert::CellToPos(GameData::GetInstance()->GetSaveData().cell, m_mapInfoData.mapChip.chipSize));

		// �v���C���[�����t���O
		isPlayerCreate = true;
	}


	// ���X�|�[��
	if (mapSwitchType == MapSwitchType::Respawn)
	{
		// �L�����N�^�[����
		PlayerCreate(EvoLib::Convert::CellToPos(GameData::GetInstance()->GetSaveData().cell, m_mapInfoData.mapChip.chipSize));

		// �v���C���[�����t���O
		isPlayerCreate = true;
	}

	// �v���C���[����������Ă��Ȃ������ꍇ�A���̃X�e�[�W���O�̃X�e�[�W�Ɉړ�����
	if (!isPlayerCreate)
	{
		// �X�e�[�W�ύX�^�C�v�����̃X�e�[�W�̏ꍇ�A�O�̃X�e�[�W�Z�����W�������ăL�����N�^�[����
		if (mapSwitchType == MapSwitchType::NextStage)
		{
			// �L�����N�^�[����
			PlayerCreate(EvoLib::Convert::CellToPos(previouseStageCell, m_mapInfoData.mapChip.chipSize));
		}

		// �X�e�[�W�ύX�^�C�v���O�̃X�e�[�W�̏ꍇ�A���̃X�e�[�W�Z�����W�������ăL�����N�^�[����
		if (mapSwitchType == MapSwitchType::PreviouseStage)
		{
			// �L�����N�^�[����
			PlayerCreate(EvoLib::Convert::CellToPos(nextStageCell, m_mapInfoData.mapChip.chipSize));
		}
	}


	// �X�e�[�W�̃}�b�v�f�[�^��������
	m_mapInfoData.mapCollisionData = mapCollisionData;


	// �G���[���b�Z�[�W����
	{
		// �`�b�v�������������ꍇ�̃G���[���b�Z�[�W
		const std::string overChip = "����������悤�ł�";

		// �`�b�v���������ꍇ�̃G���[���b�Z�[�W
		const std::string noChip = "������Ȃ��悤�ł�";


		// �`�b�v��
		std::string chipName = "";


		// ���݂�fmf�t�@�C����
		std::string fmfFileName = "[ " + m_mapInfoData.filePath[m_mapInfoData.mapNumber] + " ]��";


		// �G���[���b�Z�[�W
		std::string errorMessage = "";

		// �G���[���b�Z�[�W�t���O
		bool isErrorMessage = false;


		// �X�|�[��
		if (mapSwitchType == MapSwitchType::Spawn)
		{
			// �`�b�v����SpawnChip�ɂ���
			chipName = "[ SpawnChip ]";

			if (spawnChip <= 0)
			{
				// �G���[���b�Z�[�W����
				errorMessage = fmfFileName + chipName + noChip;

				// �G���[���b�Z�[�W�t���O
				isErrorMessage = true;
			}
			else if (spawnChip > 1)
			{
				// �G���[���b�Z�[�W����
				errorMessage = fmfFileName + chipName + overChip;

				// �G���[���b�Z�[�W�t���O
				isErrorMessage = true;
			}
		}

		// ���̃X�e�[�W
		if (mapSwitchType == MapSwitchType::NextStage)
		{
			// �`�b�v����NextPosChip�ɂ���
			chipName = "[ NextPosChip ]";

			if (nextPosChip <= 0)
			{
				// �G���[���b�Z�[�W����
				errorMessage = fmfFileName + chipName + noChip;

				// �G���[���b�Z�[�W�t���O
				isErrorMessage = true;
			}
			else if (nextPosChip > 1)
			{
				// �G���[���b�Z�[�W����
				errorMessage = fmfFileName + chipName + overChip;

				// �G���[���b�Z�[�W�t���O
				isErrorMessage = true;
			}
		}

		// �O�̃X�e�[�W
		if (mapSwitchType == MapSwitchType::PreviouseStage)
		{
			// �`�b�v����PreviousePosChip�ɂ���
			chipName = "[ PreviousePosChip ]";

			if (previousePosChip <= 0)
			{
				// �G���[���b�Z�[�W����
				errorMessage = fmfFileName + chipName + noChip;

				// �G���[���b�Z�[�W�t���O
				isErrorMessage = true;
			}
			else if (previousePosChip > 1)
			{
				// �G���[���b�Z�[�W����
				errorMessage = fmfFileName + chipName + overChip;

				// �G���[���b�Z�[�W�t���O
				isErrorMessage = true;
			}
		}


	
		if (bossSpawnFragChip > 0)
		{
			if(bossSpawnPosChip <=0)
			{
				// �G���[���b�Z�[�W����
				errorMessage = fmfFileName + chipName + noChip;

				// �G���[���b�Z�[�W�t���O
				isErrorMessage = true;
			}
			else if (bossSpawnPosChip > 1)
			{
				// �G���[���b�Z�[�W����
				errorMessage = fmfFileName + chipName + overChip;

				// �G���[���b�Z�[�W�t���O
				isErrorMessage = true;
			}
		}



		// �G���[���b�Z�[�W���o�����ǂ���
		if (isErrorMessage)
		{
			// �G���[���b�Z�[�W���o��
			EvoLib::Assert::ErrorMessageBox(errorMessage);
		}
	}
}

void ObjectManager::ObjectErase()
{	
	// ���ׂẴI�u�W�F�N�g�����āA�폜����
	auto rmIt = std::remove_if
	(m_object.begin(), m_object.end(), [](const std::shared_ptr<ObjectBase>& object)
		{
			return !object->GetIsExlist();
		}
	);

	// �폜
	m_object.erase(rmIt, m_object.end());
}

void ObjectManager::StageMove(const MapSwitchType& mapSwitchType)
{
	// ���̃X�e�[�W�Ɉړ����邩�ǂ����̃t���O����X�e�[�W�i���o�[�𑝂₷�����߂�
	if (mapSwitchType == MapSwitchType::NextStage)
	{
		// �X�e�[�W�i���o�[�̐����𑝂₷
		m_mapInfoData.mapNumber++;
	}
	else if(mapSwitchType == MapSwitchType::PreviouseStage)
	{
		// �X�e�[�W�i���o�[�̐��������炷;
 		m_mapInfoData.mapNumber--;
	}
	else if (mapSwitchType == MapSwitchType::Respawn)
	{
		// �Z�[�u�|�C���g�f�[�^�̃X�e�[�W�i���o�[���X�e�[�W�i���o�[�̐����ɑ��
		m_mapInfoData.mapNumber = GameData::GetInstance()->GetSaveData().stageNumber;
	}


	// �v�f�폜
	for (auto& object : m_object)
	{
		object->SetIsExlist(false);
	}

	// �v���`�i���f�[�^���[�h
	m_pPlatinumLoader->Load(m_mapInfoData.filePath[m_mapInfoData.mapNumber].c_str());
	
	// �v���`�i���f�[�^�擾
	const std::vector<PlatinumLoader::MapData>mapData = m_pPlatinumLoader->GetMapAllData();

	// �}�b�v�̃��C���[
	const int mapLayer = 0;
	
	// �}�b�v���擾
	m_mapInfoData.mapChip = m_pPlatinumLoader->GetMapChip();

	// �}�b�v����
	MapCollisionDataCreate(mapData[mapLayer].mapData, mapSwitchType);
}


std::vector<std::vector<int>> ObjectManager::GetMapChipNumber()
{
	// �񎟌��̗v�f�����������ϒ��z��
	std::vector<std::vector<int>>mapChipNumber(m_mapInfoData.mapChip.mapWidth, std::vector<int>(m_mapInfoData.mapChip.mapHeight));

	
	for (int y = 0; y < m_mapInfoData.mapChip.mapHeight; y++)
	{
		for (int x = 0; x < m_mapInfoData.mapChip.mapWidth; x++)
		{
			mapChipNumber[x][y] = static_cast<int>(m_mapInfoData.mapCollisionData[x][y].chipType);
		}
	}

	return mapChipNumber;
}

std::tuple<bool, Vec2>  ObjectManager::GetSavePointPos()
{
	// �Z�[�u�|�C���g�f�[�^���擾
	const GameData::SaveData savePointData = GameData::GetInstance()->GetSaveData();

	// �{�X���폜����
	for (auto& object : m_object)
	{
		if (object->GetObjectID() == ObjectBase::ObjectID::BossEnemy)
		{
			object->SetIsExlist(false);
		}
	}

	// �Z�[�u�|�C���g�f�[�^�̃X�e�[�W�i���o�[�ƌ��݂̃X�e�[�W�i���o�[���قȂ�ꍇ�A�}�b�v�������s��
	if (savePointData.stageNumber != m_mapInfoData.mapNumber)
	{
		// �}�b�v�ړ�����
		StageMove(MapSwitchType::Respawn);

		return std::tuple<bool, Vec2>(true, Vec2());
	}


	// �M�~�b�N���Z�b�g
	GimmickReset();

	
	// �Z������ϊ��������W��Ԃ�
	return std::tuple<bool, Vec2>(false, EvoLib::Convert::CellToPos(savePointData.cell, m_mapInfoData.mapChip.chipSize));
}

void ObjectManager::InitMap()
{
	// �}�b�v�f�[�^�����ݒ�
	InitMapDataFilePath();

	// �}�b�v�i���o�[��������
	m_mapInfoData.mapNumber = 0;

	// �X�e�[�W�ړ��^�C�v��������
	MapSwitchType mapSwitchType = MapSwitchType::Spawn;

	

	//// �Z�[�u�f�[�^������������Ă��Ȃ��ꍇ
	//if(!GameData::GetInstance()->GetSaveData().isInit)
	//{
	//	// �X�e�[�W�ړ��^�C�v���Z�[�u�f�[�^�ɂ���
	//	mapSwitchType = MapSwitchType::SaveData;

	//	// �X�e�[�W�i���o�[���Z�[�u�f�[�^�ɂ��鐔�l�ɂ���
	//	m_mapInfoData.mapNumber = GameData::GetInstance()->GetSaveData().stageNumber;
	//}

	// �X�e�[�W�i���o�[���Z�[�u�f�[�^�ɂ��鐔�l�ɂ���
	m_mapInfoData.mapNumber = 0;

	// �}�b�v����
	StageMove(mapSwitchType);
}

void ObjectManager::InitScreenCircle()
{
	// ��ʂ̎l�p�`���
	Square screenSquare = Square();

	// ��ʂ̎l�p�`������
	screenSquare.A = Vec2(0, 0);
	screenSquare.B = Vec2(Game::kScreenWidth, 0);
	screenSquare.C = Vec2(Game::kScreenWidth, Game::kScreenHeight);
	screenSquare.D = Vec2(0, Game::kScreenHeight);

	// ��ʂ̒��S�_����сA��ʂ���̊e���_�����̍ő�l�𔼌a�Ƃ����~�̏���Ԃ�
	m_screenCircle =
		EvoLib::Convert::SquareToCircle(screenSquare);
}

void ObjectManager::InitMapDataFilePath()
{
	// �������J�E���g
	int processCount = 0;

	while (true)
	{
		// �������J�E���g��string�^�ɕϊ�
		std::string numberStr = std::to_string(processCount);

		// �t�@�C���p�X���쐬
		std::string filePath =
			kFieldDataFilePath +
			numberStr +
			kFilePathExtension;


		// ���̃t�@�C���p�X�����݂��邩�ǂ����𒲂ׂ�
		if (!std::filesystem::is_regular_file(filePath))
		{
			break;
		}

		// �t�@�C���p�X����ǉ�����
		m_mapInfoData.filePath.push_back(filePath);


		// �����J�E���g�𑝂₷
		processCount++;
	}	
}

void ObjectManager::MapChipCreate(const MapCollisionData& mapCollisionData)
{
	if (mapCollisionData.chipType == ChipType::TransparentBlock)
	{
		// �}�b�v�`�b�v����
		m_object.push_back(std::make_shared<TransparentBlockChip>());
	}

	// �`�惉���N����
	m_object.back()->SetDrawRank(ObjectBase::DrawRank::Rank_2);

	// �|�C���^�𑗂�
	m_object.back()->SetObjectFactory(shared_from_this());

	// ���W����
	m_object.back()->SetSquare(mapCollisionData.square);

	// ����������
	m_object.back()->Init();
}

void ObjectManager::GimmickReset()
{
	// �M�~�b�N�t���O�����Z�b�g
	for (auto& object : m_object)
	{
		object->SetGimiickFlag(false);
	}
}

bool ObjectManager::IsCellCheckOutOfRange(const Cell& cell)
{
	if (cell.x < 0)return true;
	if (cell.x >= m_mapInfoData.mapChip.mapWidth)return true;
	if (cell.y < 0)return true;
	if (cell.y >= m_mapInfoData.mapChip.mapHeight)return true;

	return false;
}

void ObjectManager::ObjectUpdate(const bool isStopPlayer)
{

	for(auto& object : m_object)
	{
		// �v���C���[�̍X�V���~�߂�
		if (isStopPlayer && object->GetObjectID() == ObjectBase::ObjectID::Player)
		{
			continue;
		}
		object->Update();
	}
}

void ObjectManager::ObjectDraw()
{
	// �`�惉���N�̋t���ɃI�u�W�F�N�g��`�悷�郋�[�v
	for (int i = static_cast<int>(ObjectBase::DrawRank::RankNum) - 1; i >= 0; --i) {
		// �`�惉���N
		const ObjectBase::DrawRank drawRank = static_cast<ObjectBase::DrawRank>(i);

		// �����𖞂������ׂẴI�u�W�F�N�g��`�悷��
		std::for_each(m_object.begin(), m_object.end(),
			[drawRank](const std::shared_ptr<ObjectBase>& object) {
				if (object->GetDrawRank() == drawRank) {
					object->Draw();
				}
			});
	}
}

Triangle ObjectManager::ChipTypeToTriangle(const ChipType& needleDirection, const Square& square)
{
	// ����
	const Vec2 leftTopPos = square.A;
	// ��
	const Vec2 topPos = Vec2(leftTopPos.x + (m_mapInfoData.mapChip.chipSize * 0.5f), leftTopPos.y);
	// �E��
	const Vec2 rightTopPos = Vec2(leftTopPos.x + m_mapInfoData.mapChip.chipSize, leftTopPos.y);
	// �E
	const Vec2 rightPos = Vec2(leftTopPos.x + m_mapInfoData.mapChip.chipSize, leftTopPos.y + (m_mapInfoData.mapChip.chipSize * 0.5f));
	// �E��
	const Vec2 rightBottomPos = Vec2(leftTopPos.x + m_mapInfoData.mapChip.chipSize, leftTopPos.y + m_mapInfoData.mapChip.chipSize);
	// ��
	const Vec2 bottomPos = Vec2(leftTopPos.x + (m_mapInfoData.mapChip.chipSize * 0.5f), leftTopPos.y + m_mapInfoData.mapChip.chipSize);
	// ����
	const Vec2 leftBottomPos = Vec2(leftTopPos.x, leftTopPos.y + m_mapInfoData.mapChip.chipSize);
	// ��
	const Vec2 leftPos = Vec2(leftTopPos.x, leftTopPos.y + (m_mapInfoData.mapChip.chipSize * 0.5f));


	// �O�p�`���
	Triangle triangle = Triangle();

	if (needleDirection == ChipType::TopNeedle)
	{
		// ��
		triangle.pos_1 = topPos;
		// ����
		triangle.pos_2 = leftBottomPos;
		// �E��
		triangle.pos_3 = rightBottomPos;
	}

	if (needleDirection == ChipType::BottomNeedle)
	{
		// ��
		triangle.pos_1 = bottomPos;
		// ����
		triangle.pos_2 = leftTopPos;
		// �E��
		triangle.pos_3 = rightTopPos;
	}

	if (needleDirection == ChipType::LeftNeedle)
	{
		// ��
		triangle.pos_1 = leftPos;
		// �E��
		triangle.pos_2 = rightTopPos;
		// �E��
		triangle.pos_3 = rightBottomPos;
	}

	if (needleDirection == ChipType::RightNeedle)
	{
		// �E
		triangle.pos_1 = rightPos;
		// ����
		triangle.pos_2 = leftTopPos;
		// ����
		triangle.pos_3 = leftBottomPos;
	}

	return triangle;
}

void ObjectManager::FieldCheck()
{
	// ����p�̉~���
	Circle collisionMapCircle = Circle();

	// �v���C���[�̍��W���擾
	Vec2 playerPos = GameData::GetInstance()->GetPlayerPos();
	playerPos += GameData::GetInstance()->GetCameraPos();

	// �v���C���[�̔���~���
	const Circle playerCircle = Circle(playerPos, Player::kCollisionRadius);

	// �}�b�v�͈͓̔��ł��邩�ǂ����𒲂ׂ�
	for (int y = 0; y < m_mapInfoData.mapChip.mapHeight; y++)
	{
		for (int x = 0; x < m_mapInfoData.mapChip.mapWidth; x++)
		{

			// �~�����R�s�[
			collisionMapCircle = m_mapInfoData.mapCollisionData[x][y].circle;

			// ���W�ɃI�t�Z�b�g�l��������
			collisionMapCircle.centerPos += GameData::GetInstance()->GetCameraPos();


			// �X�N���[���O�ł��邩�ǂ����𒲂ׂ�
			{
				// �~�̔���
				m_mapInfoData.mapCollisionData[x][y].screenFlag = EvoLib::Collision::IsCircleToCircle(collisionMapCircle, m_screenCircle);
			}

			// �v���C���[�͈͓̔��ł��邩�ǂ����𒲂ׂ�
			{
				// �~�̔���
				m_mapInfoData.mapCollisionData[x][y].playerRangeFlag = EvoLib::Collision::IsCircleToCircle(collisionMapCircle, playerCircle);
			}
		
		}
	}
}

void ObjectManager::TestMapDraw()
{

	SetDrawBlendMode(DX_BLENDMODE_ALPHA,200);

	Vec2 pos1 = Vec2();
	Vec2 pos2 = Vec2();


	for (int y = 0; y < m_mapInfoData.mapChip.mapHeight; y++)
	{
		for (int x = 0; x < m_mapInfoData.mapChip.mapWidth; x++)
		{
			// ��ʓ��łȂ��ꍇ�͕`�悵�Ȃ�
			if(!m_mapInfoData.mapCollisionData[x][y].screenFlag)
			{
				continue;
			}
			
			// ���W�̑��
			pos1 = Vec2(x * m_mapInfoData.mapChip.chipSize, y * m_mapInfoData.mapChip.chipSize);
			pos2 = Vec2(pos1.x + m_mapInfoData.mapChip.chipSize, pos1.y + m_mapInfoData.mapChip.chipSize);

			// �J�������W�𑫂�
			pos1 += GameData::GetInstance()->GetCameraPos();
			pos2 += GameData::GetInstance()->GetCameraPos();


			int color = 0x00ff00;

			if (m_mapInfoData.mapCollisionData[x][y].chipType == ChipType::Ground)
			{
				color = 0xff0000;
			}
			if (m_mapInfoData.mapCollisionData[x][y].chipType == ChipType::Save)
			{
				color = 0xffffff;
			}

			
			// �����̍��W
			const Vec2 stringPos = Vec2(pos1.x + m_mapInfoData.mapChip.chipSize * 0.5f, pos1.y + m_mapInfoData.mapChip.chipSize * 0.5f);
			// �����`��
			DrawFormatString(static_cast<int>(stringPos.x), static_cast<int>(stringPos.y), 0xffffff, "%d", static_cast<int>(m_mapInfoData.mapCollisionData[x][y].chipType));



			// �j�̕`��
			if (m_mapInfoData.mapCollisionData[x][y].chipType == ChipType::RightNeedle	||
				m_mapInfoData.mapCollisionData[x][y].chipType == ChipType::LeftNeedle	||
				m_mapInfoData.mapCollisionData[x][y].chipType == ChipType::TopNeedle	||
				m_mapInfoData.mapCollisionData[x][y].chipType == ChipType::BottomNeedle)
			{
				Triangle triangle = ChipTypeToTriangle(m_mapInfoData.mapCollisionData[x][y].chipType, m_mapInfoData.mapCollisionData[x][y].square);

				triangle.pos_1 += GameData::GetInstance()->GetCameraPos();
				triangle.pos_2 += GameData::GetInstance()->GetCameraPos();	
				triangle.pos_3 += GameData::GetInstance()->GetCameraPos();

				// �O�p�`�`��
				DrawTriangleAA(
					triangle.pos_1.x, triangle.pos_1.y,
					triangle.pos_2.x, triangle.pos_2.y,
					triangle.pos_3.x, triangle.pos_3.y, 0xff0000, true);

				continue;
			}

			if (m_mapInfoData.mapCollisionData[x][y].chipType == ChipType::TransparentBlock)
			{
				continue;
			}

			// �}�b�v�̕`��
			DrawGraphF(pos1.x, pos1.y, m_testMapGraph[static_cast<int>(m_mapInfoData.mapCollisionData[x][y].chipType)], true);

			// �}�b�v�̕`��
			DrawBoxAA(pos1.x, pos1.y, pos2.x, pos2.y, color, false);
		}
	}

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND,255);

}

void ObjectManager::DrawSaveScore()
{

	const Circle playerCircle = Circle(GameData::GetInstance()->GetPlayerPos(), ScoreGraph_GameMain::kPlayerRadius);
	const Circle scoreCircle = Circle(ScoreGraph_GameMain::kClearTextPos, ScoreGraph_GameMain::kScoreGraphRadius);


	// �v���C���[�̔��a�ƃX�R�A�̔��a�̏Փ˔���
	if (EvoLib::Collision::IsCircleToCircle(playerCircle, scoreCircle))
	{
		// �������`��
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	}




	// ���݂̃^�C�����擾
	const Time currentTime = GameData::GetInstance()->GetTime();

	// ���݂̎��S�񐔂��擾
	const int currentDeathCount = GameData::GetInstance()->GetDeathCount();
	
	const GameData::Score saveScore = GameData::GetInstance()->CalcScore(currentTime, currentDeathCount);

	// �N���A���g���C�񐔃e�L�X�g�̕`��
	DrawRotaGraphF(
		ScoreGraph_GameMain::kClearTextPos.x,
		ScoreGraph_GameMain::kClearTextPos.y,
		ScoreGraph_GameMain::kTextGraphSize,
		0.0,
		m_scoreGraphData.clearRetryTextGraphHandle[0],
		TRUE);


	// �N���A���g���C�񐔃e�L�X�g�̕`��
	DrawRotaGraphF(
		ScoreGraph_GameMain::kRetryTextPos.x,
		ScoreGraph_GameMain::kRetryTextPos.y,
		ScoreGraph_GameMain::kTextGraphSize,
		0.0,
		m_scoreGraphData.clearRetryTextGraphHandle[1],
		TRUE);


	// ���ԃX�R�A
	{
		// ���ԃX�R�A�̕`��
		const int loopNum = static_cast<int>(saveScore.time.size());

		int count = 0;

		for (int i = 0; i < loopNum; i++)
		{
			if (i != 0 && i % 2 == 0)
			{
				const float x = ScoreGraph_GameMain::kTimeScorePos.x + ((i + count) * ScoreGraph_GameMain::kGraphInterval);

				DrawRotaGraphF(
					x,
					ScoreGraph_GameMain::kTimeScorePos.y,
					ScoreGraph_GameMain::kGraphSize,
					0.0,
					m_scoreGraphData.separateGraphHandle,
					TRUE);

				count++;
			}

			const float x = ScoreGraph_GameMain::kTimeScorePos.x + ((i + count) * ScoreGraph_GameMain::kGraphInterval);

			DrawRotaGraphF(
				x,
				ScoreGraph_GameMain::kTimeScorePos.y,
				ScoreGraph_GameMain::kGraphSize,
				0.0,
				m_scoreGraphData.numberGraphHandle[saveScore.time[i]],
				TRUE);
		}
	}

	// �f�X�J�E���g
	{
		// �f�X�J�E���g�̕`��
		const int loopNum = static_cast<int>(saveScore.deathCount.size());

		for (int i = 0; i < loopNum; i++)
		{


			const float x = ScoreGraph_GameMain::kDeathCountPos.x + (i * ScoreGraph_GameMain::kGraphInterval);

			DrawRotaGraphF(
				x,
				ScoreGraph_GameMain::kDeathCountPos.y,
				ScoreGraph_GameMain::kGraphSize,
				0.0,
				m_scoreGraphData.numberGraphHandle[saveScore.deathCount[i]],
				TRUE);
		}

		float x = ScoreGraph_GameMain::kDeathCountPos.x + (loopNum * ScoreGraph_GameMain::kGraphInterval);
		x += 5.0f;

		DrawRotaGraphF(
			x,
			ScoreGraph_GameMain::kDeathCountPos.y,
			ScoreGraph_GameMain::kGraphSize,
			0.0,
			m_scoreGraphData.countGraphHandle,
			TRUE);
	}

	// �����x�����ɖ߂�
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
