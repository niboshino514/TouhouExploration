#include "EndingScreen.h"
#include "SceneEnding.h"
#include "Controller.h"
#include "game.h"
#include "GameData.h"
#include "EffectManager.h"

namespace Graph
{
	// �Q�[���N���A�摜
	const char* const kGameClearGraphFileName = "Data/Graphic/Ending/GameClear.png";
	// �Q�[���N���A�摜�̈ʒu
	const Vec2 kGameClearGraphPos = Vec2(Game::kWindowCenterX_F, Game::kWindowCenterY_F - 290.0f);

	// �L�����N�^�[�O���t�B�b�N�̃t�@�C����
	const char* const kCharaGraphFileName = "Data/Graphic/Ending/Marisa.png";
	// �L�����N�^�[�O���t�B�b�N�̈ʒu
	const Vec2 kCharaGraphPos = Vec2(1180.0f, 500.0f);

}

namespace SineCurve
{
	// �ő�t���[��
	constexpr int kMaxFrame = 100;

	constexpr int kSineCurveSpeed = 1;

	constexpr float kMaxSineCurveValue = 10.0f;
}

namespace ScoreGraph
{
	// �ԍ��O���t�B�b�N�̃t�@�C����
	const char* kNumberGraphFileName = "Data/Graphic/Number/Number.png";
	// �X�R�A�O���t�B�b�N�̕�����
	const EvoLib::Load::DivNum kNumberGraphDivNum = EvoLib::Load::DivNum(10, 1);

	// �d�؂�O���t�B�b�N�̃t�@�C����
	const char* kSeparateGraphFileName = "Data/Graphic/Number/Separate.png";
	// �J�E���g�O���t�B�b�N�̃t�@�C����
	const char* kCountGraphFileName = "Data/Graphic/Number/Count.png";

	// �N���A���g���C�񐔃e�L�X�g�O���t�B�b�N�̃t�@�C����
	const char* kClearRetryTextGraphFileName = "Data/Graphic/Ending/ClearRetryText.png";

	// �T���N�X�O���t�B�b�N�̃t�@�C����
	const char* kThanksGraphFileName = "Data/Graphic/Ending/Thanks.png";

	// �V�L�^�O���t�B�b�N�̃t�@�C����
	const char* kNewRecordGraphFileName = "Data/Graphic/Ending/NewRecord.png";


	// �^�C���X�R�A�̈ʒu
	const Vec2 kTimeScorePos = Vec2(530, Game::kWindowCenterY_F - 70.0f);
	// �f�X�J�E���g�̈ʒu
	const Vec2 kDeathCountPos = Vec2(kTimeScorePos.x, Game::kWindowCenterY_F + 100.0f);

	// �O���t�B�b�N���m�̊��o
	const float kTextGraphInterval = -250.0f;

	// �N���A���g���C�񐔃e�L�X�g�̈ʒu
	const Vec2 kClearTextPos = Vec2(kTimeScorePos.x + kTextGraphInterval, kTimeScorePos.y);
	const Vec2 kRetryTextPos = Vec2(kDeathCountPos.x + kTextGraphInterval, kDeathCountPos.y);

	// �T���N�X�O���t�B�b�N�̈ʒu
	const Vec2 kThanksGraphPos = Vec2(Game::kWindowCenterX_F, Game::kWindowCenterY_F + 300.0f);
	// �T���N�X�O���t�B�b�N�̃T�C�Y
	constexpr double kThanksGraphSize = 1.0;

	// �V�L�^�̃O���t�B�b�N�̈ʒu
	const Vec2 kNewRecordGraphPos = Vec2(250, Game::kWindowCenterY_F - 150.0f);
	// �V�L�^�̃O���t�B�b�N�̃T�C�Y
	constexpr double kNewRecordGraphSize = 0.5;


	// �e�L�X�g�O���t�B�b�N�T�C�Y
	constexpr double kTextGraphSize = 1.0;

	// �O���t�B�b�N���m�̊Ԋu
	static float kGraphInterval = 0.0f;
	// �O���t�B�b�N���m�̊Ԋu�̐ݒ�
	const float kGraphIntervalSetting = -50.0f;

	// �O���t�B�b�N�T�C�Y
	constexpr double kGraphSize = 1.1;
}

EndingScreen::EndingScreen() :
	m_gameClearGraphHandle(-1),
	m_scoreGraphData(),
	m_thanksGraphHandle(-1),
	m_newRecordGraphHandle(-1),
	m_isNewRecord(false),
	m_score(),
	m_gameClearGraphSineCuve(),
	m_gameClearGraphSineCurveValue(0.0f),
	m_pSceneEnding(nullptr),
	m_pEffectManager(std::make_shared<EffectManager>())
{
}

EndingScreen::~EndingScreen()
{
	// �摜�n���h�����
	DeleteGraph(m_gameClearGraphHandle);
	for (auto& handle : m_scoreGraphData.numberGraphHandle)
	{
		DeleteGraph(handle);
	}
	DeleteGraph(m_scoreGraphData.separateGraphHandle);
	DeleteGraph(m_scoreGraphData.countGraphHandle);
	for (auto& handle : m_scoreGraphData.clearRetryTextGraphHandle)
	{
		DeleteGraph(handle);
	}
	DeleteGraph(m_thanksGraphHandle);
	DeleteGraph(m_newRecordGraphHandle);
	DeleteGraph(m_charaGraphHandle);
}

void EndingScreen::Init()
{
	// �摜���[�h
	Load();


	// �T�C���J�[�u�̃f�[�^�̏�����
	m_gameClearGraphSineCuve.sineCurrentFrame = 0;
	m_gameClearGraphSineCuve.sineMaxFrame = SineCurve::kMaxFrame;
	m_gameClearGraphSineCuve.sineMaxValue = SineCurve::kMaxSineCurveValue;

	// �V�L�^���ǂ����̔���
	{
		// �V�L�^���ǂ����̔���
		m_isNewRecord = GameData::GetInstance()->IsNewRecord();
	}

	if (m_isNewRecord)
	{
		// �V�L�^�̏ꍇ�A�Z�[�u�f�[�^���X�V
		GameData::GetInstance()->SetScoreData();

		GameData::GetInstance()->WriteScoreData();
	}


	m_score = GameData::GetInstance()->
		CalcScore(
			GameData::GetInstance()->GetTime(),
			GameData::GetInstance()->GetDeathCount());

	// �G�t�F�N�g�}�l�[�W���[�̏�����
	m_pEffectManager->Init();
}

void EndingScreen::Update()
{
	// �T�C���J�[�u�̍X�V
	UpdateSineCurve();

	// �{�^���������ꂽ��t�F�[�h�A�E�g��ݒ肷��
	if (Controller::GetInstance()->IsTrigger(Controller::ControllerButton::DECIDE))
	{
		m_pSceneEnding->ChangeScene(SceneEnding::Scene::Title);
	}

	// �G�t�F�N�g�}�l�[�W���[�̍X�V
	m_pEffectManager->Update();
}

void EndingScreen::Draw()
{
	// �w�i
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0xa9a9a9, true);


	// �L�����N�^�[�̕`��
	DrawRotaGraphF(
		Graph::kCharaGraphPos.x,
		Graph::kCharaGraphPos.y,
		1.0,
		0.0,
		m_charaGraphHandle,
		TRUE);


	// �Q�[���N���A�摜
	DrawRotaGraphF(
		Graph::kGameClearGraphPos.x,
		Graph::kGameClearGraphPos.y + m_gameClearGraphSineCurveValue,
		1.0,
		0.0,
		m_gameClearGraphHandle, TRUE);

	// �X�R�A�̕`��
	DrawScore();


	// �T���N�X�摜
	DrawRotaGraphF(
		ScoreGraph::kThanksGraphPos.x,
		ScoreGraph::kThanksGraphPos.y,
		ScoreGraph::kThanksGraphSize,
		0.0,
		m_thanksGraphHandle,
		TRUE);

	// �G�t�F�N�g�}�l�[�W���[�̕`��
	m_pEffectManager->Draw();
}

void EndingScreen::Load()
{
	// �Q�[���N���A�摜���[�h
	m_gameClearGraphHandle = LoadGraph(Graph::kGameClearGraphFileName);

	// �X�R�A�O���t�B�b�N���[�h
	{
		m_scoreGraphData.numberGraphHandle =
			EvoLib::Load::LoadDivGraph_EvoLib_Revision(ScoreGraph::kNumberGraphFileName, ScoreGraph::kNumberGraphDivNum);

		m_scoreGraphData.separateGraphHandle = LoadGraph(ScoreGraph::kSeparateGraphFileName);
		m_scoreGraphData.countGraphHandle = LoadGraph(ScoreGraph::kCountGraphFileName);

		// �N���A���g���C�񐔃e�L�X�g�O���t�B�b�N���[�h
		m_scoreGraphData.clearRetryTextGraphHandle =
			EvoLib::Load::LoadDivGraph_EvoLib_Revision(ScoreGraph::kClearRetryTextGraphFileName, EvoLib::Load::DivNum(1, 2));

		// �T���N�X�O���t�B�b�N�̃��[�h
		m_thanksGraphHandle = LoadGraph(ScoreGraph::kThanksGraphFileName);

		{
			// �O���t�B�b�N�̃T�C�Y���擾
			const Vec2 size = EvoLib::Calculation::GetGraphSize_EvoLib(m_scoreGraphData.numberGraphHandle, ScoreGraph::kGraphSize);

			// �O���t�B�b�N�̊Ԋu��ݒ�
			ScoreGraph::kGraphInterval = size.x + ScoreGraph::kGraphIntervalSetting;
		}

		// �V�L�^�̃O���t�B�b�N�̃��[�h
		m_newRecordGraphHandle = LoadGraph(ScoreGraph::kNewRecordGraphFileName);
	}

	// �L�����N�^�[�O���t�B�b�N���[�h
	m_charaGraphHandle = LoadGraph(Graph::kCharaGraphFileName);
}

void EndingScreen::UpdateSineCurve()
{
	// �T�C���J�[�u�̍X�V
	m_gameClearGraphSineCurveValue =
		EvoLib::Calculation::SineCurve<float>(m_gameClearGraphSineCuve);
}

void EndingScreen::DrawScore()
{


	// �N���A���g���C�񐔃e�L�X�g�̕`��
	DrawRotaGraphF(
		ScoreGraph::kClearTextPos.x,
		ScoreGraph::kClearTextPos.y,
		ScoreGraph::kTextGraphSize,
		0.0,
		m_scoreGraphData.clearRetryTextGraphHandle[0],
		TRUE);


	// �N���A���g���C�񐔃e�L�X�g�̕`��
	DrawRotaGraphF(
		ScoreGraph::kRetryTextPos.x,
		ScoreGraph::kRetryTextPos.y,
		ScoreGraph::kTextGraphSize,
		0.0,
		m_scoreGraphData.clearRetryTextGraphHandle[1],
		TRUE);

	// �V�L�^���o�Ă����ꍇ�A�ԐF�ŕ`��
	if (m_isNewRecord)
	{
		// �V�L�^�̕`��
		DrawRotaGraphF(
			ScoreGraph::kNewRecordGraphPos.x,
			ScoreGraph::kNewRecordGraphPos.y,
			ScoreGraph::kNewRecordGraphSize,
			0.0,
			m_newRecordGraphHandle,
			TRUE);

		// �ԐF�ɕύX
		SetDrawBright(255, 0, 0);
	}



	// ���ԃX�R�A
	{
		// ���ԃX�R�A�̕`��
		const int loopNum = static_cast<int>(m_score.time.size());

		int count = 0;

		for (int i = 0; i < loopNum; i++)
		{
			if (i != 0 && i % 2 == 0)
			{
				const float x = ScoreGraph::kTimeScorePos.x + ((i + count) * ScoreGraph::kGraphInterval);

				DrawRotaGraphF(
					x,
					ScoreGraph::kTimeScorePos.y,
					ScoreGraph::kGraphSize,
					0.0,
					m_scoreGraphData.separateGraphHandle,
					TRUE);

				count++;
			}

			const float x = ScoreGraph::kTimeScorePos.x + ((i + count) * ScoreGraph::kGraphInterval);

			DrawRotaGraphF(
				x,
				ScoreGraph::kTimeScorePos.y,
				ScoreGraph::kGraphSize,
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


			const float x = ScoreGraph::kDeathCountPos.x + (i * ScoreGraph::kGraphInterval);

			DrawRotaGraphF(
				x,
				ScoreGraph::kDeathCountPos.y,
				ScoreGraph::kGraphSize,
				0.0,
				m_scoreGraphData.numberGraphHandle[m_score.deathCount[i]],
				TRUE);
		}

		float x = ScoreGraph::kDeathCountPos.x + (loopNum * ScoreGraph::kGraphInterval);
		x += 20.0f;

		DrawRotaGraphF(
			x,
			ScoreGraph::kDeathCountPos.y,
			ScoreGraph::kGraphSize,
			0.0,
			m_scoreGraphData.countGraphHandle,
			TRUE);
	}

	// �F�����ɖ߂�
	SetDrawBright(255, 255, 255);
}
