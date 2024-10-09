#include "Pause.h"
#include "game.h"
#include <DxLib.h>
#include "Controller.h"
#include "ObjectManager.h"
#include "EvoLib.h"
#include "ControllerOption.h"
#include "Sound.h"
#include "SoundOption.h"

namespace Window
{
	// �|�[�Y�E�B���h�E�̉���
	const int kWidth = 700;

	// �|�[�Y�E�B���h�E�̏c��
	const int kHeight = 450;

	// �����x
	const int kAlpha = 200;
}

namespace WindowNameGraph
{
	// �O���t�B�b�N�t�@�C���p�X
	const char* const kFilePath = "Data/Graphic/Pause/WindowName.png";
	// ������
	const EvoLib::Load::DivNum kDivNum = { 1, 1 };
	// �g�嗦
	const double kScale = 1.0;
}

namespace BackTitleWindow
{
	// �|�[�Y�E�B���h�E�̉���
	const int kWidth = 600;

	// �|�[�Y�E�B���h�E�̏c��
	const int kHeight = 200;

	// �����x
	const int kAlpha = 200;
}

namespace BackTitleGraph
{
	// �o�b�N�^�C�g���E�B���h�E�̃O���t�B�b�N�t�@�C���p�X
	const char* const kFilePath = "Data/Graphic/Pause/BackTitle.png";
	// �o�b�N�^�C�g���E�B���h�E�̃O���t�B�b�N����
	const Vec2 kDistanceValue = Vec2(0, 10);
	// �o�b�N�^�C�g���E�B���h�E�̕�����
	const EvoLib::Load::DivNum kDivNum = { 1, 1 };
	// �o�b�N�^�C�g�����S���W
	const Vec2 kCenterPos = Vec2(Game::kWindowCenterX, Game::kWindowCenterY -50);
	// �g�嗦
	const double kScale = 0.7;
}

namespace Graph
{
	// �|�[�Y�Z���N�g�O���t�B�b�N�t�@�C���p�X
	const char* const kPauseSelectFilePath = "Data/Graphic/Pause/PauseSelect.png";
	// �|�[�Y�Z���N�g�O���t�B�b�N�̃O���t�B�b�N����
	const Vec2 kPauseSelectDistanceValue = Vec2(0, 20);
	// �|�[�Y�Z���N�g�̏c������
	const int kPauseSelectDivY = 4;
	// �|�[�Y���S���W
	const Vec2 kPauseCenterPos = Vec2(Game::kWindowCenterX+20, Game::kWindowCenterY);

	// �o�b�N�^�C�g���Z���N�g�O���t�B�b�N�t�@�C���p�X
	const char* const kBackTitleSelectFilePath = "Data/Graphic/Selection/Selection.png";
	// �o�b�N�^�C�g���Z���N�g�O���t�B�b�N�̃O���t�B�b�N����
	const Vec2 kBackTitleSelectDistanceValue = Vec2(80, 0);
	// �o�b�N�^�C�g���Z���N�g�̏c������
	const int kBackTitleSelectDivY = 2;
	// �o�b�N�^�C�g�����S���W
	const Vec2 kBackTitleCenterPos = Vec2(Game::kWindowCenterX, Game::kWindowCenterY + 50);

	// �g�嗦
	const double kScale = 0.8;

	// �����x
	const int kAlpha = 100;

	// �I������Ă���O���t�B�b�N�����ɂ��炷
	const float kSelectMoveX = -10;
}

namespace SelectTriangleGraph
{
	// �O���t�B�b�N�t�@�C���p�X
	const char* const kFilePath = "Data/Graphic/Selection/SelectTriangle.png";

	// �g�嗦
	const float kScale = 0.6f;

	// �t���[�����x
	const int kFrameSpeed = 2;

	// �|�[�Y����
	const Vec2 kPauseSelectDistanceValue = Vec2(-220, 0);

	// �o�b�N�^�C�g������
	const Vec2 kBackTitleSelectDistanceValue = Vec2(-110, 0);
}


Pause::Pause():
	m_pauseSelect(),
	m_backTitleSelect(),
	m_windowNameGraph(),
	m_pauseSelectGprah(),
	m_backTitleGraph(),
	m_backTitleSelectGraph(),
	m_selectTriangleGraph(),
	m_pStateMachine(),
	m_pObjectFactory(),
	m_pControllerOption(std::make_shared<ControllerOption>()),
	m_pSoundOption(std::make_shared<SoundOption>())
{
}

Pause::~Pause()
{
	// �O���t�B�b�N�̃f���[�g
	for (auto& handle : m_pauseSelectGprah.handle)
	{
		DeleteGraph(handle);
	};
	for (auto& handle : m_backTitleSelectGraph.handle)
	{
		DeleteGraph(handle);
	};
	for(auto& handle : m_windowNameGraph.handle)
	{
		DeleteGraph(handle);
	}
	for(auto& handle : m_backTitleGraph.handle)
	{
		DeleteGraph(handle);
	}
 
	DeleteGraph(m_selectTriangleGraph);
}

void Pause::Init()
{

	// �R���g���[���[�I�v�V�����̏�����
	m_pControllerOption->Init();

	// �T�E���h�I�v�V�����̏�����
	m_pSoundOption->Init();


	// �O���t�B�b�N�̃��[�h
	Load();

	// �X�e�[�g�}�V���̏�����
	StateInit();



	m_pauseSelect = PauseSelect::Volume;

}

void Pause::Update()
{
	// �X�e�[�g�}�V���̍X�V
	m_pStateMachine.Update();
}

void Pause::Draw()
{
	// �|�[�Y�E�B���h�E�`��
	DrawPauseWindow();

	// �I��`��
	DrawPauseSelect();


	// �X�e�[�g�}�V���̕`��
	m_pStateMachine.Draw();
}

void Pause::StateInit()
{

	// �X�e�[�g�}�V���̏������AEntry
	auto dummy = []() {};

	// �ʏ�X�e�[�g
	{
		auto enter = [this]() { StateNormalEnter(); };
		auto update = [this]() { StateNormalUpdate(); };
		
		m_pStateMachine.AddState(State::Normal, enter, update, dummy, dummy);
	}
	// �|�[�Y�X�e�[�g
	{
		auto enter = [this]() { StatePauseEnter(); };
		auto update = [this]() { StatePauseUpdate(); };
		auto draw = [this]() { StatePauseDraw(); };
		auto exit = [this]() { StatePauseExit(); };

		m_pStateMachine.AddState(State::Pause, enter, update, draw, dummy);
	}
	// ���͐ؑփX�e�[�g
	{
		auto enter = [this]() { StateChangeInputEnter(); };
		auto update = [this]() { StateChangeInputUpdate(); };
		auto draw = [this]() { StateChangeInputDraw(); };

		m_pStateMachine.AddState(State::ChangeInput, enter, update, draw, dummy);
	}
	// ���ʒ����X�e�[�g
	{
		auto enter = [this]() { StateSoundOptionEnter(); };
		auto update = [this]() { StateSoundOptionUpdate(); };
		auto draw = [this]() { StateSoundOptionDraw(); };

		m_pStateMachine.AddState(State::SoundOption, enter, update, draw, dummy);
	}
	// �o�b�N�^�C�g���X�e�[�g
	{
		auto enter = [this]() { StateBackTitleEnter(); };
		auto update = [this]() { StateBackTitleUpdate(); };
		auto draw = [this]() { StateBackTitleDraw(); };

		m_pStateMachine.AddState(State::BackTitle, enter, update, draw, dummy);
	}


	// �����X�e�[�g��ݒ�
	m_pStateMachine.SetState(State::Normal);
}

void Pause::StateNormalEnter()
{
	// �|�[�Y�I���̏�����
	m_pauseSelect = PauseSelect::Resume;
	// �o�b�N�^�C�g���I���̏�����
	m_backTitleSelect = BackTitleSelect::No;
}

void Pause::StateNormalUpdate()
{


	if (Controller::GetInstance()->IsTrigger(Controller::ControllerButton::PAUSE))
	{
		// �|�[�Y�X�e�[�g�ɑJ��
		m_pStateMachine.SetState(State::Pause);
		// �I�u�W�F�N�g�t�@�N�g���[�̃X�e�[�g���|�[�Y�ɐݒ�
		m_pObjectFactory->SetState(ObjectManager::State::Pause);

		// �|�[�Y�����Đ�
		Sound::GetInstance()->Play(kSoundFileName[static_cast<int>(SoundName::Pause)]);
	}
}

void Pause::StatePauseEnter()
{
}

void Pause::StatePauseUpdate()
{
	// �I���X�V
	PauseSelectUpdate();

	// ���菈��
	PauseSelectDecision();

	// �L�����Z���{�^���������ꂽ��|�[�Y�I�����Q�[���ĊJ�Z�b�g����
	if(Controller::GetInstance()->IsTrigger(Controller::ControllerButton::CANCEL))
	{
		m_pauseSelect = PauseSelect::Resume;

		// �L�����Z�������Đ�
		Sound::GetInstance()->Play(kSoundFileName[static_cast<int>(SoundName::Cancel)]);
	}


	// �|�[�Y�{�^���������ꂽ��ʏ�X�e�[�g�ɑJ��
	if (Controller::GetInstance()->IsTrigger(Controller::ControllerButton::PAUSE))
	{
		// �ʏ�X�e�[�g�ɑJ��
		ResumeProcess();

		// �L�����Z�������Đ�
		Sound::GetInstance()->Play(kSoundFileName[static_cast<int>(SoundName::Cancel)]);
	}
}

void Pause::StatePauseDraw()
{
}

void Pause::StatePauseExit()
{

}

void Pause::StateChangeInputEnter()
{
	// �R���g���[���[�I�v�V�����̏�����
	m_pControllerOption->InitSettingItem();
}

void Pause::StateChangeInputUpdate()
{
	// �ݒ荀�ڍX�V
	m_pControllerOption->Update();

	if(m_pControllerOption->GetIsCloseWindow())
	{
		// �|�[�Y�X�e�[�g�ɑJ��
		m_pStateMachine.SetState(State::Pause);
	}
}

void Pause::StateChangeInputDraw()
{
	// �ݒ荀�ڕ`��
	m_pControllerOption->Draw();
}

void Pause::StateSoundOptionEnter()
{
	// �T�E���h�I�v�V�����̏�����
	m_pSoundOption->InitSettingItem();
}

void Pause::StateSoundOptionUpdate()
{
	// �ݒ荀�ڍX�V
	m_pSoundOption->Update();

	if (m_pSoundOption->GetIsCloseWindow())
	{
		// �|�[�Y�X�e�[�g�ɑJ��
		m_pStateMachine.SetState(State::Pause);
	}
}

void Pause::StateSoundOptionDraw()
{
	// �ݒ荀�ڕ`��
	m_pSoundOption->Draw();
}

void Pause::StateBackTitleEnter()
{
}

void Pause::StateBackTitleUpdate()
{
	// �o�b�N�^�C�g���I���X�V
	BackTitleSelectUpdate();
	// �o�b�N�^�C�g�����菈��
	BackTitleSelectDecision();
}

void Pause::StateBackTitleDraw()
{
	// �o�b�N�^�C�g���E�B���h�E�`��
	DrawBackTitleWindow();

	// �o�b�N�^�C�g���I��`��
	DrawBackTitleSelect();
}

void Pause::Load()
{

	// �E�B���h�E���̃O���t�B�b�N�̃��[�h
	{
		// �O���t�B�b�N���[�h
		m_windowNameGraph.handle = EvoLib::Load::LoadDivGraph_EvoLib_Revision
		(WindowNameGraph::kFilePath, WindowNameGraph::kDivNum);

		// �E�B���h�E�̏�Y���W
		const float windowTop_Y = Game::kWindowCenterY - Window::kHeight / 2;


		// ���W�̐ݒ�
		Vec2 pos = Vec2();
		pos.x = Game::kWindowCenterX;
		pos.y = windowTop_Y;

		// ���W�̐ݒ�
		m_windowNameGraph.pos.push_back(pos);
	}

	// �|�[�Y�I���O���t�B�b�N
	{
		// �|�[�Y�I���O���t�B�b�N
		m_pauseSelectGprah.handle = EvoLib::Load::LoadDivGraph_EvoLib_Revision(Graph::kPauseSelectFilePath, EvoLib::Load::DivNum(1, 4));

		// �O���t�B�b�N�̍��W���ϓ��ɔz�u
		const Vec2 graphSize = EvoLib::Calculation::GetGraphSize_EvoLib(m_pauseSelectGprah.handle, Graph::kScale);

		m_pauseSelectGprah.pos = EvoLib::Calculation::GraphEqualization
		(graphSize, Graph::kPauseCenterPos, static_cast<int>(m_pauseSelectGprah.handle.size()), Graph::kPauseSelectDistanceValue, false);
	}

	// �o�b�N�^�C�g���O���t�B�b�N
	{
		// �o�b�N�^�C�g���O���t�B�b�N
		m_backTitleGraph.handle = EvoLib::Load::LoadDivGraph_EvoLib_Revision(BackTitleGraph::kFilePath, BackTitleGraph::kDivNum);

		// �O���t�B�b�N��z�u
		m_backTitleGraph.pos.push_back(BackTitleGraph::kCenterPos);
	}

	// �o�b�N�^�C�g���I���O���t�B�b�N
	{
		// �o�b�N�^�C�g���I���O���t�B�b�N
		m_backTitleSelectGraph.handle = EvoLib::Load::LoadDivGraph_EvoLib_Revision(Graph::kBackTitleSelectFilePath, EvoLib::Load::DivNum(1, 2));

		// �O���t�B�b�N�̍��W���ϓ��ɔz�u
		const Vec2 graphSize = EvoLib::Calculation::GetGraphSize_EvoLib(m_backTitleSelectGraph.handle, Graph::kScale);

		m_backTitleSelectGraph.pos = EvoLib::Calculation::GraphEqualization
		(graphSize, Graph::kBackTitleCenterPos, static_cast<int>(m_backTitleSelectGraph.handle.size()), Graph::kBackTitleSelectDistanceValue, true);
	}

	// �Z���N�g�O�p�`�O���t�B�b�N
	{
		// �O���t�B�b�N���[�h
		m_selectTriangleGraph = LoadGraph(SelectTriangleGraph::kFilePath);
	}
}

void Pause::PauseSelectUpdate()
{
	if(Controller::GetInstance()->IsTrigger(Controller::ControllerButton::UP))
	{
		m_pauseSelect = static_cast<PauseSelect>((static_cast<int>(m_pauseSelect) - 1 + static_cast<int>(PauseSelect::SelectNum)) % static_cast<int>(PauseSelect::SelectNum));

		// �I�������Đ�
		Sound::GetInstance()->Play(kSoundFileName[static_cast<int>(SoundName::Select)]);
	}
	else if (Controller::GetInstance()->IsTrigger(Controller::ControllerButton::DOWN))
	{
		m_pauseSelect = static_cast<PauseSelect>((static_cast<int>(m_pauseSelect) + 1) % static_cast<int>(PauseSelect::SelectNum));

		// �I�������Đ�
		Sound::GetInstance()->Play(kSoundFileName[static_cast<int>(SoundName::Select)]);
	}
}

void Pause::PauseSelectDecision()
{
	// ����{�^����������Ă��Ȃ����return
	if(!Controller::GetInstance()->IsTrigger(Controller::ControllerButton::DECIDE))
	{
		return;
	}


	if (m_pauseSelect != PauseSelect::Resume)
	{
		// ���艹���Đ�
		Sound::GetInstance()->Play(kSoundFileName[static_cast<int>(SoundName::Decision)]);
	}
	else
	{
		// �L�����Z�������Đ�
		Sound::GetInstance()->Play(kSoundFileName[static_cast<int>(SoundName::Cancel)]);
	}


	switch (m_pauseSelect)
	{
	case PauseSelect::Resume:

		// �ʏ�X�e�[�g�ɑJ��
		ResumeProcess();

		break;
	case PauseSelect::Volume:

		// �T�E���h�I�v�V�����X�e�[�g�ɑJ��
		m_pStateMachine.SetState(State::SoundOption);

		break;
	case PauseSelect::ChangeInput:

		// ���͐ؑփX�e�[�g�ɑJ��
		m_pStateMachine.SetState(State::ChangeInput);

		break;
	case PauseSelect::Title:

		// �o�b�N�^�C�g���I���ɑJ��
		m_pStateMachine.SetState(State::BackTitle);

		break;
	
	default:

		// �ʏ�X�e�[�g�ɑJ��
		ResumeProcess();

		break;
	}

	

}

void Pause::BackTitleSelectUpdate()
{


	if (Controller::GetInstance()->IsTrigger(Controller::ControllerButton::LEFT))
	{
		m_backTitleSelect = static_cast<BackTitleSelect>((static_cast<int>(m_backTitleSelect) - 1 + static_cast<int>(BackTitleSelect::SelectNum)) % static_cast<int>(BackTitleSelect::SelectNum));

		// �I�������Đ�
		Sound::GetInstance()->Play(kSoundFileName[static_cast<int>(SoundName::Select)]);
	}
	else if (Controller::GetInstance()->IsTrigger(Controller::ControllerButton::RIGHT))
	{
		m_backTitleSelect = static_cast<BackTitleSelect>((static_cast<int>(m_backTitleSelect) + 1) % static_cast<int>(BackTitleSelect::SelectNum));

		// �I�������Đ�
		Sound::GetInstance()->Play(kSoundFileName[static_cast<int>(SoundName::Select)]);
	}
}

void Pause::BackTitleSelectDecision()
{

	// ����{�^����������Ă��Ȃ����return
	if (!Controller::GetInstance()->IsTrigger(Controller::ControllerButton::DECIDE))
	{
		return;
	}

	switch (m_backTitleSelect)
	{
	case BackTitleSelect::Yes:

		// �^�C�g���ɑJ��
		m_pObjectFactory->ChangeScene(SceneMain::Scene::Title);

		// �����t�𖳌��ɂ���
		Controller::GetInstance()->SetAcceptInput(false);

		// ���艹���Đ�
		Sound::GetInstance()->Play(kSoundFileName[static_cast<int>(SoundName::Decision)]);

		break;
	case BackTitleSelect::No:

		// �|�[�Y�X�e�[�g�ɑJ��
		m_pStateMachine.SetState(State::Pause);

		// �L�����Z�������Đ�
		Sound::GetInstance()->Play(kSoundFileName[static_cast<int>(SoundName::Cancel)]);

		break;
	default:

		// �|�[�Y�X�e�[�g�ɑJ��
		m_pStateMachine.SetState(State::Pause);

		break;
	}
}


void Pause::DrawPauseWindow()
{
	int const windowLeftTopX = Game::kWindowCenterX - Window::kWidth / 2;
	int const windowLeftTopY = Game::kWindowCenterY - Window::kHeight / 2;

	int const windowRightBottomX = Game::kWindowCenterX + Window::kWidth / 2;
	int const windowRightBottomY = Game::kWindowCenterY + Window::kHeight / 2;


	// �����x�ݒ�
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, Window::kAlpha);

	// �|�[�Y�E�B���h�E
	DrawBox(windowLeftTopX, windowLeftTopY, windowRightBottomX, windowRightBottomY, 0x000000, true);

	// �����x����
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// �|�[�Y�E�B���h�E�g
	DrawBox(windowLeftTopX, windowLeftTopY, windowRightBottomX, windowRightBottomY, 0xffffff, false);


	// �E�B���h�E���`��
	DrawRotaGraphF(m_windowNameGraph.pos[0].x, m_windowNameGraph.pos[0].y, WindowNameGraph::kScale, 0.0, m_windowNameGraph.handle[0], true);
}

void Pause::DrawPauseSelect()
{

	// �|�[�Y�I��`��
	{
		// �����x�ݒ�
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, Graph::kAlpha);

		// �I�΂�Ă���I�����͐ԐF�ŕ`�悵�A����ȊO�͔������ŕ`��
		for (int i = 0; i < static_cast<int>(PauseSelect::SelectNum); i++)
		{
			if (m_pauseSelect != static_cast<PauseSelect>(i))
			{
				DrawRotaGraphF(m_pauseSelectGprah.pos[i].x, m_pauseSelectGprah.pos[i].y, Graph::kScale, 0.0, m_pauseSelectGprah.handle[i], true);
			}
		}

		// �����x����
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	// �I�΂�Ă���I�����͐ԐF�ŕ`��
	SetDrawBright(255, 0, 0);

	// �I��`��
	{
		DrawRotaGraphF(m_pauseSelectGprah.pos[static_cast<int>(m_pauseSelect)].x + Graph::kSelectMoveX, m_pauseSelectGprah.pos[static_cast<int>(m_pauseSelect)].y, Graph::kScale, 0.0, m_pauseSelectGprah.handle[static_cast<int>(m_pauseSelect)], true);
	}

	// �I������Ă���O�p�`�`��
	{
		Vec2 pos = Vec2();
		pos.x = (m_pauseSelectGprah.pos[static_cast<int>(m_pauseSelect)].x + Graph::kSelectMoveX);
		pos.y = m_pauseSelectGprah.pos[static_cast<int>(m_pauseSelect)].y;

		pos += SelectTriangleGraph::kPauseSelectDistanceValue;

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

void Pause::DrawBackTitleSelect()
{

	// �o�b�N�^�C�g���`��
	DrawRotaGraphF(m_backTitleGraph.pos[0].x, m_backTitleGraph.pos[0].y, BackTitleGraph::kScale, 0.0, m_backTitleGraph.handle[0], true);


	// �o�b�N�^�C�g���I��`��
	{
		// �����x�ݒ�
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, Graph::kAlpha);

		// �I�΂�Ă���I�����͐ԐF�ŕ`�悵�A����ȊO�͔������ŕ`��
		for (int i = 0; i < static_cast<int>(BackTitleSelect::SelectNum); i++)
		{
			if (m_backTitleSelect != static_cast<BackTitleSelect>(i))
			{
				DrawRotaGraphF(m_backTitleSelectGraph.pos[i].x, m_backTitleSelectGraph.pos[i].y, Graph::kScale, 0.0, m_backTitleSelectGraph.handle[i], true);
			}
		}

		// �����x����
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	// �I�΂�Ă���I�����͐ԐF�ŕ`��
	SetDrawBright(255, 0, 0);

	// �I��`��
	{
		DrawRotaGraphF(m_backTitleSelectGraph.pos[static_cast<int>(m_backTitleSelect)].x, m_backTitleSelectGraph.pos[static_cast<int>(m_backTitleSelect)].y, Graph::kScale, 0.0, m_backTitleSelectGraph.handle[static_cast<int>(m_backTitleSelect)], true);	
	}

	// �I������Ă���O�p�`�`��
	{
		Vec2 pos = Vec2();
		pos.x = m_backTitleSelectGraph.pos[static_cast<int>(m_backTitleSelect)].x;
		pos.y = m_backTitleSelectGraph.pos[static_cast<int>(m_backTitleSelect)].y;

		pos += SelectTriangleGraph::kBackTitleSelectDistanceValue;

		// ��]�`��
		EvoLib::Draw::DrawRotatingImage(
			m_selectTriangleGraph,
			pos,
			SelectTriangleGraph::kFrameSpeed,
			false,
			SelectTriangleGraph::kScale,
			true,
			false,
			true,
			false);
	}

	// �F�����ɖ߂�
	SetDrawBright(255, 255, 255);
}

void Pause::ResumeProcess()
{
	// �ʏ�X�e�[�g�ɑJ��
	m_pStateMachine.SetState(State::Normal);
	// �I�u�W�F�N�g�t�@�N�g���[�̃X�e�[�g��ʏ�ɐݒ�
	m_pObjectFactory->SetState(ObjectManager::State::Normal);
}

void Pause::DrawBackTitleWindow()
{
	int const windowLeftTopX = Game::kWindowCenterX - BackTitleWindow::kWidth / 2;
	int const windowLeftTopY = Game::kWindowCenterY - BackTitleWindow::kHeight / 2;

	int const windowRightBottomX = Game::kWindowCenterX + BackTitleWindow::kWidth / 2;
	int const windowRightBottomY = Game::kWindowCenterY + BackTitleWindow::kHeight / 2;





	// �����x�ݒ�
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, BackTitleWindow::kAlpha);

	// ��ʑS�̂����œh��Ԃ�
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);


	// �|�[�Y�E�B���h�E
	DrawBox(windowLeftTopX, windowLeftTopY, windowRightBottomX, windowRightBottomY, 0x000000, true);

	// �����x����
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// �|�[�Y�E�B���h�E�g
	DrawBox(windowLeftTopX, windowLeftTopY, windowRightBottomX, windowRightBottomY, 0xffffff, false);

	
}
