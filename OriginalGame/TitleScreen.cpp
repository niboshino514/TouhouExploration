#include "TitleScreen.h"
#include <DxLib.h>
#include "Game.h"
#include "SceneTitle.h"
#include "Controller.h"
#include "EvoLib.h"
#include "Sound.h"
#include "GameData.h"


namespace GraphData
{

	// �I������Ă��Ȃ��O���t�B�b�N�̓����x
	constexpr int kAlpha = 100;

	// �I������Ă���O���t�B�b�N�����ɂ��炷
	constexpr float kSelectMoveX = -10.0f;

	// �I�𒆂̃O���t�B�b�N�f�[�^
	static const EvoLib::Load::GraphicInfo kSelectGraphInfo =
	{
		// �t�@�C���p�X
		"Data/Graphic/Title/Select/Select.png",

		// ���S���W
		Vec2(Game::kWindowCenterX_F + 20.0f, Game::kWindowCenterY_F+80.0f),

		// �O���t�B�b�N�X�P�[��
		0.7,

		// �O���t�B�b�N�̕�����
		EvoLib::Load::DivNum(1,3),
	};

	// �I�𒆂̃O���t�B�b�N�̋���
	const Vec2 kSelectGraphDistance = Vec2(0.0f, 20.0f);


	// �^�C�g���O���t�B�b�N�̃t�@�C����
	const char* const kGameTitleGraphFileName = "Data/Graphic/Title/GameTitle.png";
	// �^�C�g���O���t�B�b�N�̈ʒu
	const Vec2 kGameTitleGraphPos = Vec2(Game::kWindowCenterX_F, Game::kWindowCenterY_F - 230.0f);
	// �^�C�g���O���t�B�b�N�̊g�嗦
	constexpr double kGameTitleGraphScale = 1.0;

	// �w�i�O���t�B�b�N�̃t�@�C����
	const char* const kBackgroundGraphFileName = "Data/Graphic/Title/Background.png";
	// �w�i�̈ړ����x
	constexpr float kBackgroundMoveSpeed = 2.0f;

}

namespace SelectTriangleGraph
{
	// �O���t�B�b�N�t�@�C���p�X
	const char* const kFilePath = "Data/Graphic/Selection/SelectTriangle.png";

	// �g�嗦
	const float kScale = 0.6f;
	// �t���[�����x
	const int kFrameSpeed = 1;

	// ����
	const Vec2 kSelectDistanceValue = Vec2(-250, 0);
}

namespace
{
	// �T�E���h�t�@�C����
	static std::vector<std::string> kSoundFileName =
	{
		"Bgm_0",		// BGM

		"Determination",// ���艹
		"Cancel",		// �L�����Z����
		"Select",		// �I����
	};

	// �T�E���h��
	enum class SoundName
	{
		BGM,			// BGM

		Decision,		// ���艹
		Cancel,			// �L�����Z����
		Select,			// �I����
	};

}

namespace ScoreGraph_Title
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
	const char* const kClearRetryTextGraphFileName = "Data/Graphic/Ending/ClearRetryText.png";


	// �^�C���X�R�A�̈ʒu
	const Vec2 kTimeScorePos = Vec2(Game::kWindowCenterX_F , Game::kWindowCenterY_F + 300.0f);
	// �f�X�J�E���g�̈ʒu
	const Vec2 kDeathCountPos = Vec2(Game::kWindowCenterX_F, kTimeScorePos.y +30.0f);

	// �O���t�B�b�N���m�̊Ԋu
	const float kTextGraphInterval = -100.0f;

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
}

TitleScreen::TitleScreen():
	m_selectGraphInfo(),
	m_selectTriangleGraph(0),
	m_select(Select()),
	m_isContinue(false),
	m_gameTitleGraph(-1),
	m_score(),
	m_isClear(false),
	m_scoreGraphData(),
	m_backgroundGraph(-1),
	m_currentMoveValue(0.0f),
	m_pStateMachine(),
	m_pSceneTitle(nullptr)
{
}

TitleScreen::~TitleScreen()
{
	// �O���t�B�b�N�̉��
	for(auto& handle : m_selectGraphInfo.handle)
	{
		DeleteGraph(handle);
	}

	// �O���t�B�b�N�̉��
	DeleteGraph(m_selectTriangleGraph);

	// �O���t�B�b�N�̉��
	for (auto& handle : m_scoreGraphData.numberGraphHandle)
	{
		DeleteGraph(handle);
	}

	// �O���t�B�b�N�̉��
	DeleteGraph(m_scoreGraphData.separateGraphHandle);

	// �O���t�B�b�N�̉��
	DeleteGraph(m_scoreGraphData.countGraphHandle);

	// �O���t�B�b�N�̉��
	for (auto& handle : m_scoreGraphData.clearRetryTextGraphHandle)
	{
		DeleteGraph(handle);
	}

	// �O���t�B�b�N�̉��
	DeleteGraph(m_backgroundGraph);


}

void TitleScreen::Init()
{
	// �O���t�B�b�N�̓ǂݍ���
	Load();

	// �Z�[�u�f�[�^�m�F
	CheckSaveData();

	// �X�R�A�f�[�^�m�F
	CheckScoreData();

	// �X�e�[�g�̏�����
	StateInit();

	// BGM�Đ�
	Sound::GetInstance()->Play(kSoundFileName[static_cast<int>(SoundName::BGM)]);
}

void TitleScreen::Update()
{
	// �X�e�[�g�}�V���̍X�V
	m_pStateMachine.Update();
}

void TitleScreen::Draw()
{
	// �w�i
	DrawBackground();

	// �^�C�g���O���t�B�b�N�̕`��
	DrawRotaGraphF(
		GraphData::kGameTitleGraphPos.x,
		GraphData::kGameTitleGraphPos.y,
		GraphData::kGameTitleGraphScale,
		0.0,
		m_gameTitleGraph,
		TRUE);


	// �X�e�[�g�}�V���̕`��
	m_pStateMachine.Draw();
	
	// �X�R�A�̕`��
	DrawScore();
}

void TitleScreen::Load()
{
	// �T�E���h�̓ǂݍ���
	{
		Sound::GetInstance()->Load(kSoundFileName);	
	}


	// �I�𒆂̃O���t�B�b�N�ǂݍ���
	{
		// �O���t�B�b�N�̓ǂݍ���
		m_selectGraphInfo.handle = 
			EvoLib::Load::LoadDivGraph_EvoLib_Revision(
				GraphData::kSelectGraphInfo.filePath,
				GraphData::kSelectGraphInfo.div);

		// �O���t�B�b�N�̃T�C�Y���擾
		const Vec2 size = 
			EvoLib::Calculation::GetGraphSize_EvoLib(
				m_selectGraphInfo.handle,
				GraphData::kSelectGraphInfo.scale);

		// �T�C�Y����
		for(int i = 0; i < m_selectGraphInfo.handle.size(); i++)
		{
			m_selectGraphInfo.scale.push_back(GraphData::kSelectGraphInfo.scale);
		}

		// �O���t�B�b�N���ϓ��ɔz�u����
		m_selectGraphInfo.pos =
			EvoLib::Calculation::GraphEqualization(
				size,
				GraphData::kSelectGraphInfo.pos,
				GraphData::kSelectGraphInfo.div.y,
				GraphData::kSelectGraphDistance,
				false);
	}


	// �Z���N�g�O�p�`�O���t�B�b�N
	{
		// �O���t�B�b�N���[�h
		m_selectTriangleGraph = LoadGraph(SelectTriangleGraph::kFilePath);
	}

	// �X�R�A�O���t�B�b�N���[�h
	{
		m_scoreGraphData.numberGraphHandle =
			EvoLib::Load::LoadDivGraph_EvoLib_Revision(ScoreGraph_Title::kNumberGraphFileName, ScoreGraph_Title::kNumberGraphDivNum);

		m_scoreGraphData.separateGraphHandle = LoadGraph(ScoreGraph_Title::kSeparateGraphFileName);
		m_scoreGraphData.countGraphHandle = LoadGraph(ScoreGraph_Title::kCountGraphFileName);

		// �N���A���g���C�񐔃e�L�X�g�O���t�B�b�N���[�h
		m_scoreGraphData.clearRetryTextGraphHandle =
			EvoLib::Load::LoadDivGraph_EvoLib_Revision(ScoreGraph_Title::kClearRetryTextGraphFileName, EvoLib::Load::DivNum(1, 2));

		{
			// �O���t�B�b�N�̃T�C�Y���擾
			const Vec2 size = EvoLib::Calculation::GetGraphSize_EvoLib(m_scoreGraphData.numberGraphHandle, ScoreGraph_Title::kGraphSize);

			// �O���t�B�b�N�̊Ԋu��ݒ�
			ScoreGraph_Title::kGraphInterval = size.x + ScoreGraph_Title::kGraphIntervalSetting;
		}
	}

	// �Q�[���^�C�g���O���t�B�b�N
	{
		// �O���t�B�b�N�̓ǂݍ���
		m_gameTitleGraph = LoadGraph(GraphData::kGameTitleGraphFileName);
	}

	// �w�i�O���t�B�b�N
	{
		// �O���t�B�b�N�̓ǂݍ���
		m_backgroundGraph = LoadGraph(GraphData::kBackgroundGraphFileName);
	}
}

void TitleScreen::StateInit()
{
	// �X�e�[�g�}�V���̏�����
	auto dummy = []() {};

	// ���͑҂��X�e�[�g
	{
		auto enter = [this]() {this->StateWaitEnter(); };
		auto update = [this]() {this->StateWaitUpdate(); };
		auto draw = [this]() {this->StateWaitDraw(); };
		auto exit = [this]() {this->StateWaitExit(); };

		m_pStateMachine.AddState(State::WaitInput, enter, update, draw, exit);
	}

	// �I�𒆃X�e�[�g
	{
		auto enter = [this]() {this->StateSelectEnter(); };
		auto update = [this]() {this->StateSelectUpdate(); };
		auto draw = [this]() {this->StateSelectDraw(); };
		auto exit = [this]() {this->StateSelectExit(); };

		m_pStateMachine.AddState(State::Selecting, enter, update, draw, exit);
	}

	// �����X�e�[�g�ݒ�
	m_pStateMachine.SetState(State::Selecting);
}

void TitleScreen::StateWaitEnter()
{
}

void TitleScreen::StateWaitUpdate()
{
	// ����{�^���������ꂽ��A�I�𒆃X�e�[�g�ɑJ�ڂ���
	if (Controller::GetInstance()->IsTrigger(Controller::ControllerButton::DECIDE))
	{
		// �I�𒆃X�e�[�g�ɑJ��
		m_pStateMachine.SetState(State::Selecting);
	}
}

void TitleScreen::StateWaitDraw()
{
}

void TitleScreen::StateWaitExit()
{
}

void TitleScreen::StateSelectEnter()
{
}

void TitleScreen::StateSelectUpdate()
{
	// �I������
	SelectProcess();

	// ���菈��
	DecideProcess();
}

void TitleScreen::StateSelectDraw()
{
	// �I������Ă��Ȃ��O���t�B�b�N�`��
	{
		// �����x�ݒ�
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, GraphData::kAlpha);

		// �O���t�B�b�N�`��
		for (int i = 0; i < m_selectGraphInfo.handle.size(); i++)
		{
			// �I�𒆂Ȃ�΁Acontinue����
			if (i == static_cast<int>(m_select))
			{
				continue;
			}

			if (!m_isContinue &&
				i == static_cast<int>(Select::Continue))
			{
				continue;
			}


			DrawRotaGraphF(
				m_selectGraphInfo.pos[i].x,
				m_selectGraphInfo.pos[i].y,
				m_selectGraphInfo.scale[i],
				0.0f,
				m_selectGraphInfo.handle[i],
				true);
		}
		// �����x����
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	// �I�΂�Ă���I�����͐ԐF�ŕ`��
	SetDrawBright(255, 0, 0);

	// �I�𒆂̃O���t�B�b�N�`��
	{
		// �O���t�B�b�N�`��
		DrawRotaGraphF(
			m_selectGraphInfo.pos[static_cast<int>(m_select)].x + GraphData::kSelectMoveX,
			m_selectGraphInfo.pos[static_cast<int>(m_select)].y,
			m_selectGraphInfo.scale[static_cast<int>(m_select)],
			0.0f,
			m_selectGraphInfo.handle[static_cast<int>(m_select)],
			true);
	}


	// �I������Ă���O�p�`�`��
	{
		Vec2 pos = Vec2();
		pos.x = (m_selectGraphInfo.pos[static_cast<int>(m_select)].x + GraphData::kSelectMoveX);
		pos.y = m_selectGraphInfo.pos[static_cast<int>(m_select)].y;

		pos += SelectTriangleGraph::kSelectDistanceValue;

		// ��]�`��
		EvoLib::Draw::DrawRotatingImage(
			m_selectTriangleGraph,
			pos,
			SelectTriangleGraph::kFrameSpeed,
			false,
			SelectTriangleGraph::kScale);
	}

	// �F�����ɖ߂�
	SetDrawBright(255, 255, 255);
}

void TitleScreen::StateSelectExit()
{
}

void TitleScreen::CheckSaveData()
{
	// �Z�[�u�f�[�^������������Ă��邩�ǂ������擾
	const bool isSaveDataInit = GameData::GetInstance()->IsSaveDataInit();

	// �Z�[�u�f�[�^������������Ă���Ȃ�΁A��������v���C�ł��Ȃ�
	if(isSaveDataInit)
	{
		m_isContinue = false;

		// �Z���N�g�̏�����NewGame�ɐݒ�
		m_select = Select::NewGame;
	}
	else
	{
		m_isContinue = true;
	}

}

void TitleScreen::CheckScoreData()
{
	// �X�R�A�f�[�^�̓ǂݍ���
	const GameData::ScoreData scoreData = 
		GameData::GetInstance()->GetScoreData();


	m_score = GameData::GetInstance()->CalcScore
	(scoreData.clearTime, scoreData.deathCount);

	// �N���A���Ă��邩�ǂ���
	m_isClear = scoreData.isClear;

}

void TitleScreen::SelectProcess()
{
	// �Z���N�g��
	const int selectNum = static_cast<int>(Select::SelectNum);




	if (Controller::GetInstance()->IsTrigger(Controller::ControllerButton::UP))
	{
		m_select = static_cast<Select>(((static_cast<int>(m_select) - 1 + selectNum) % selectNum));

		if (!m_isContinue &&
			m_select == Select::Continue)
		{
			m_select = static_cast<Select>((static_cast<int>(m_select) - 1 + selectNum));
		}

		// �I�������Đ�
		Sound::GetInstance()->Play(kSoundFileName[static_cast<int>(SoundName::Select)]);
	}
	else if (Controller::GetInstance()->IsTrigger(Controller::ControllerButton::DOWN))
	{
		m_select = static_cast<Select>(((static_cast<int>(m_select) + 1) % selectNum));

		if(!m_isContinue&&
			m_select == Select::Continue)
		{
			m_select = static_cast<Select>(((static_cast<int>(m_select) + 1)));
		}

		// �I�������Đ�
		Sound::GetInstance()->Play(kSoundFileName[static_cast<int>(SoundName::Select)]);
	}
}

void TitleScreen::DecideProcess()
{
	// �t�F�[�h�C�����I�����Ă��Ȃ���΁Areturn
	if (!m_pSceneTitle->IsFadeInEnd())
	{
		return;
	}

	// ����{�^����������Ă��Ȃ���΁Areturn
	if (!Controller::GetInstance()->IsTrigger(Controller::ControllerButton::DECIDE))
	{
		return;
	}



	// �I�����ꂽ���̂ɂ���ď����𕪊�
	switch (m_select)
	{
	case TitleScreen::Select::Continue:
		// �V�[����ύX����
		m_pSceneTitle->ChangeScene(SceneTitle::Scene::GameMain);

		break;
	case TitleScreen::Select::NewGame:
		// �Z�[�u�f�[�^��������
		GameData::GetInstance()->InitSaveData();
		// �V�[����ύX����
		m_pSceneTitle->ChangeScene(SceneTitle::Scene::GameMain);

	
		break;
	case TitleScreen::Select::GameEnd:
		
		GameData::GetInstance()->WriteSaveData();	// �Z�[�u�f�[�^����������
		GameData::GetInstance()->WriteScoreData();	// �X�R�A�f�[�^�̏�������

		// �Q�[���I��
		DxLib_End();

		break;
	default:
		break;
	}

	// ���艹���Đ�
	Sound::GetInstance()->Play(kSoundFileName[static_cast<int>(SoundName::Decision)]);
}

void TitleScreen::DrawScore()
{
	// �N���A���Ă��Ȃ��Ȃ�΁Areturn
	if (!m_isClear)
	{
		return;
	}


	// �N���A���g���C�񐔃e�L�X�g�̕`��
	DrawRotaGraphF(
		ScoreGraph_Title::kClearTextPos.x,
		ScoreGraph_Title::kClearTextPos.y,
		ScoreGraph_Title::kTextGraphSize,
		0.0,
		m_scoreGraphData.clearRetryTextGraphHandle[0],
		TRUE);


	// �N���A���g���C�񐔃e�L�X�g�̕`��
	DrawRotaGraphF(
		ScoreGraph_Title::kRetryTextPos.x,
		ScoreGraph_Title::kRetryTextPos.y,
		ScoreGraph_Title::kTextGraphSize,
		0.0,
		m_scoreGraphData.clearRetryTextGraphHandle[1],
		TRUE);


	// ���ԃX�R�A
	{
		// ���ԃX�R�A�̕`��
		const int loopNum = static_cast<int>(m_score.time.size());

		int count = 0;

		for (int i = 0; i < loopNum; i++)
		{
			if (i != 0 && i % 2 == 0)
			{
				const float x = ScoreGraph_Title::kTimeScorePos.x + ((i + count) * ScoreGraph_Title::kGraphInterval);

				DrawRotaGraphF(
					x,
					ScoreGraph_Title::kTimeScorePos.y,
					ScoreGraph_Title::kGraphSize,
					0.0,
					m_scoreGraphData.separateGraphHandle,
					TRUE);

				count++;
			}

			const float x = ScoreGraph_Title::kTimeScorePos.x + ((i + count) * ScoreGraph_Title::kGraphInterval);

			DrawRotaGraphF(
				x,
				ScoreGraph_Title::kTimeScorePos.y,
				ScoreGraph_Title::kGraphSize,
				0.0,
				m_scoreGraphData.numberGraphHandle[m_score.time[i]],
				TRUE);
		}
	}

	// �f�X�J�E���g
	{
		// �f�X�J�E���g�̕`��
		const int loopNum = static_cast<int>(m_score.deathCount.size());

		for (int i = 0; i < loopNum; i++)
		{


			const float x = ScoreGraph_Title::kDeathCountPos.x + (i * ScoreGraph_Title::kGraphInterval);

			DrawRotaGraphF(
				x,
				ScoreGraph_Title::kDeathCountPos.y,
				ScoreGraph_Title::kGraphSize,
				0.0,
				m_scoreGraphData.numberGraphHandle[m_score.deathCount[i]],
				TRUE);
		}

		float x = ScoreGraph_Title::kDeathCountPos.x + (loopNum * ScoreGraph_Title::kGraphInterval);
		x += 5.0f;

		DrawRotaGraphF(
			x,
			ScoreGraph_Title::kDeathCountPos.y,
			ScoreGraph_Title::kGraphSize,
			0.0,
			m_scoreGraphData.countGraphHandle,
			TRUE);
	}
}

void TitleScreen::DrawBackground()
{
	m_currentMoveValue += GraphData::kBackgroundMoveSpeed;

	if (m_currentMoveValue >= Game::kScreenWidth)
	{
		m_currentMoveValue = 0.0f;
	}

	EvoLib::Draw::SimpleLoopBackground(
		m_backgroundGraph,
		m_currentMoveValue,
		GraphData::kBackgroundMoveSpeed,
		Vec2(Game::kScreenWidth, Game::kScreenHeight),
		true,
		EvoLib::Draw::LoopDirection::Right);
}
