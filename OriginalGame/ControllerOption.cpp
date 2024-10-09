#include "ControllerOption.h"
#include <DxLib.h>
#include "game.h"
#include "EvoLib.h"
#include "Pad.h"
#include "Sound.h"
#include "ObjectManager.h"

namespace Window
{
	// �|�[�Y�E�B���h�E�̉���
	const int kWidth = 900;

	// �|�[�Y�E�B���h�E�̏c��
	const int kHeight = 650;

	// �����x
	const int kAlpha = 150;
}



namespace WindowNameGraph
{
	// �O���t�B�b�N�t�@�C���p�X
	const char* const kFilePath = "Data/Graphic/ControllerOption/WindowName.png";
	// ������
	const EvoLib::Load::DivNum kDivNum = { 1, 1 };
	// �g�嗦
	const double kScale = 1.0;
}


namespace SettingItemGraph
{
	// �O���t�B�b�N�t�@�C���p�X
	const char* const kFilePath = "Data/Graphic/ControllerOption/SettingItem.png";
	// �O���t�B�b�N�̃O���t�B�b�N����
	const Vec2 kDistanceValue = Vec2(0, 40);
	// ������
	const EvoLib::Load::DivNum kDivNum = { 1, 3 };
	// ���S���W
	const Vec2 kCenterPos = Vec2(Game::kWindowCenterX-200, Game::kWindowCenterY-120);
	// �g�嗦
	const double kScale = 0.5;
	// �����x
	const int kAlpha = 100;
}

namespace BackGraph
{
	// �O���t�B�b�N�t�@�C���p�X
	const char* const kFilePath = "Data/Graphic/Selection/Back.png";
	// ������
	const EvoLib::Load::DivNum kDivNum = { 1, 1 };
	// �g�嗦
	const double kScale = 0.5;
}

namespace SelectTriangleGraph
{
	// �O���t�B�b�N�t�@�C���p�X
	const char* const kFilePath = "Data/Graphic/Selection/SelectTriangle.png";

	// �g�嗦
	const float kScale = 0.6f;

	// �����؊�������
	const Vec2 kAutoSwitchDistance = Vec2(-90, 0);

	// �R���g���[���[�^�C�v�I������
	const Vec2 kCtrlTypeDistance= Vec2(-170, 0);

	// ���̓f�o�C�X�ؑ֋���
	const Vec2 kInputDeviceDistance = Vec2(-150, 0);
}

namespace
{
	struct ControllerSettingGraphInfo
	{
		// �O���t�B�b�N�t�@�C���p�X
		const char* const kFilePath = "";
		// ������
		const EvoLib::Load::DivNum kDivNum = { 1, 1 };
		// �ݒ荀�ڂ���̋���
		const Vec2 kDistanceValue = Vec2(450, 0);
		// �g�嗦
		const double kScale = 0.5;
	};



	// �ݒ荀��
	const std::vector<ControllerSettingGraphInfo> m_controllerSettingGraphInfo =
	{
		// �R���g���[���[�����؊���
		{
			"Data/Graphic/ControllerOption/Switch.png",
			{ 1, 2 },
		
		},
		// �R���g���[���[�^�C�v�I��
		{
			"Data/Graphic/ControllerOption/ControllerType.png",
			{ 1, 3 },
		
		},
		// ���̓f�o�C�X�ؑ�
		{
			"Data/Graphic/ControllerOption/InputDevice.png",
			{ 1, 2 },
		
		},
	};

	// �����x
	const int kAlpha = 100;
}




ControllerOption::ControllerOption():
	m_settingItemSelect(),
	m_controllerSetting(),
	m_isCloseWindow(),
	m_settingItemGraph(),
	m_controllerSettingGraph(),
	m_windowNameGraph(),
	m_backGraph(),
	m_selectTriangleGraph()
{
}

ControllerOption::~ControllerOption()
{
	// �n���h���̉��
	for(auto& handle : m_settingItemGraph.handle)
	{
		DeleteGraph(handle);
	}
	for(auto& graph : m_controllerSettingGraph)
	{
		for(auto& handle : graph.handle)
		{
			DeleteGraph(handle);
		}
	}
	for(auto& handle : m_windowNameGraph.handle)
	{
		DeleteGraph(handle);
	}
	for(auto& handle : m_backGraph.handle)
	{
		DeleteGraph(handle);
	}
	DeleteGraph(m_selectTriangleGraph);
}

void ControllerOption::Init()
{
	// �O���t�B�b�N�̃��[�h
	Load();
}

void ControllerOption::Update()
{
	// �R���g���[���[�ݒ�擾
	m_controllerSetting = Controller::GetInstance()->GetControllerSetting();

	// �I�����ڂ̍X�V
	UpdateSettingItem();

	// �R���g���[���[�ݒ�̍X�V
	UpdateControllerSetting();

	// �L�����Z���{�^���������ꂽ��E�B���h�E�����
	if (Controller::GetInstance()->IsTrigger(Controller::ControllerButton::CANCEL))
	{
		m_isCloseWindow = true;

		// �L�����Z�������Đ�
		Sound::GetInstance()->Play(kSoundFileName[static_cast<int>(SoundName::Cancel)]);
	}
}

void ControllerOption::Draw()
{
	// �E�B���h�E�̕`��
	DrawWindow();

	// �ݒ荀�ڂ̕`��
	DrawSettingItem();

	// �R���g���[���[�ݒ�̕`��
	DrawControllerSetting();

	// �R���g���[���[�����̕`��
	DrawControllerExplanation();


	// �߂�{�^���̕`��
	DrawRotaGraphF(m_backGraph.pos[0].x, m_backGraph.pos[0].y, BackGraph::kScale, 0.0, m_backGraph.handle[0], TRUE);
}

void ControllerOption::InitSettingItem()
{
	// �I�����ڂ̏�����
	m_settingItemSelect = SettingItemSenect::AUTO_SWITCH;

	// �E�B���h�E����邩�ǂ���
	m_isCloseWindow = false;
}

void ControllerOption::Load()
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


	// �ݒ荀�ڂ̃O���t�B�b�N�̃��[�h
	{
		// �O���t�B�b�N���[�h
		m_settingItemGraph.handle = EvoLib::Load::LoadDivGraph_EvoLib_Revision
		(SettingItemGraph::kFilePath, SettingItemGraph::kDivNum);

		// ���W�̐ݒ�
		const Vec2 graphSize = EvoLib::Calculation::GetGraphSize_EvoLib(m_settingItemGraph.handle, SettingItemGraph::kScale);

		// ���W�̐ݒ�
		m_settingItemGraph.pos = EvoLib::Calculation::GraphEqualization
		(graphSize, SettingItemGraph::kCenterPos, static_cast<int>(m_settingItemGraph.handle.size()), SettingItemGraph::kDistanceValue, false);

	}
	
	{
		// �Z���N�g��
		const int selectNum = static_cast<int>(SettingItemSenect::SELECT_NUM);

		// ���T�C�Y
		m_controllerSettingGraph.resize(selectNum);

		for (int i = 0; i < selectNum; i++)
		{
			// �ݒ�i���o�[
			const int settingNum = static_cast<int>(SettingItemSenect(i));


			// �O���t�B�b�N���[�h
			m_controllerSettingGraph[i].handle = EvoLib::Load::LoadDivGraph_EvoLib_Revision
			(m_controllerSettingGraphInfo[settingNum].kFilePath, m_controllerSettingGraphInfo[settingNum].kDivNum);

			// ���W�̐ݒ�
			const Vec2 pos = m_settingItemGraph.pos[i] + m_controllerSettingGraphInfo[settingNum].kDistanceValue;

			// ���W�̐ݒ�
			m_controllerSettingGraph[i].pos.push_back(pos);
		}
	}

	// �o�b�N�O���t�B�b�N�̃��[�h
	{
		// �O���t�B�b�N���[�h
		m_backGraph.handle = EvoLib::Load::LoadDivGraph_EvoLib_Revision
		(BackGraph::kFilePath,BackGraph::kDivNum);

		// �E�B���h�E�̉�Y���W
		const float windowBottom_Y = Game::kWindowCenterY + Window::kHeight / 2;
		// �E�B���h�E�̉EX���W
		const float windowRight_X = Game::kWindowCenterX + Window::kWidth / 2;

		// ���W�̐ݒ�
		const Vec2 graphSize = EvoLib::Calculation::GetGraphSize_EvoLib(m_backGraph.handle, BackGraph::kScale);


		// ���W�̐ݒ�
		Vec2 pos = Vec2();
		pos.x = windowRight_X - (graphSize.x * 0.5f);
		pos.y = windowBottom_Y - (graphSize.y * 0.5f);

		// ���W�̐ݒ�
		m_backGraph.pos.push_back(pos);
	}

	// �I���O�p�`�̃O���t�B�b�N�̃��[�h
	m_selectTriangleGraph = LoadGraph(SelectTriangleGraph::kFilePath);
}

void ControllerOption::UpdateSettingItem()
{
	// �Z���N�g��
	int selectNum = static_cast<int>(SettingItemSenect::SELECT_NUM);

	// �I�[�g�X�C�b�`��ON�̏ꍇ�A�I����������炷
	if (m_controllerSetting.autoSwitch == Controller::AutoSwitch::ON)
	{
		selectNum--;
	}


	if(Controller::GetInstance()->IsTrigger(Controller::ControllerButton::DOWN))
	{
		// �I�����ڂ̍X�V
		m_settingItemSelect = static_cast<SettingItemSenect>((static_cast<int>(m_settingItemSelect) + 1) % selectNum);

		// �R���g���[���[�ݒ�̍X�V
		Controller::GetInstance()->SetControllerSetting(m_controllerSetting);

		// �I�������Đ�
		Sound::GetInstance()->Play(kSoundFileName[static_cast<int>(SoundName::Select)]);
	}
	else if(Controller::GetInstance()->IsTrigger(Controller::ControllerButton::UP))
	{
		// �I�����ڂ̍X�V
		m_settingItemSelect = static_cast<SettingItemSenect>((static_cast<int>(m_settingItemSelect) - 1 + selectNum) % selectNum);

		// �R���g���[���[�ݒ�̍X�V
		Controller::GetInstance()->SetControllerSetting(m_controllerSetting);

		// �I�������Đ�
		Sound::GetInstance()->Play(kSoundFileName[static_cast<int>(SoundName::Select)]);
	}
}

void ControllerOption::UpdateControllerSetting()
{
	// �I�����ڂɂ���ď����𕪂���
	switch (m_settingItemSelect)
	{
	case ControllerOption::SettingItemSenect::AUTO_SWITCH:

		// �I�[�g�X�C�b�`��ON�̏ꍇ
		UpdateAutoSwitch();
		break;
	case ControllerOption::SettingItemSenect::CTRL_TYPE:

		// �R���g���[���[�^�C�v�I��
		UpdateCtrlType();
		break;
	case ControllerOption::SettingItemSenect::INPUT_DEVICE:

		// ���̓f�o�C�X�ؑ�
		UpdateInputDevice();
		break;
	default:

		// �I�[�g�X�C�b�`��ON�̏ꍇ
		UpdateAutoSwitch();
		break;
	}
}

void ControllerOption::UpdateAutoSwitch()
{
	// �Z���N�g��
	const int selectNum = static_cast<int>(Controller::AutoSwitch::AUTO_SWITCH_NUM);

	if (Controller::GetInstance()->IsTrigger(Controller::ControllerButton::RIGHT))
	{
		// �I�����ڂ̍X�V
		m_controllerSetting.autoSwitch = static_cast<Controller::AutoSwitch>((static_cast<int>(m_controllerSetting.autoSwitch) + 1) % selectNum);

		// �R���g���[���[�ݒ�̍X�V
		Controller::GetInstance()->SetControllerSetting(m_controllerSetting);

		// �I�������Đ�
		Sound::GetInstance()->Play(kSoundFileName[static_cast<int>(SoundName::Select)]);
	}
	else if (Controller::GetInstance()->IsTrigger(Controller::ControllerButton::LEFT))
	{
		// �I�����ڂ̍X�V
		m_controllerSetting.autoSwitch = static_cast<Controller::AutoSwitch>((static_cast<int>(m_controllerSetting.autoSwitch) - 1 + selectNum) % selectNum);

		// �R���g���[���[�ݒ�̍X�V
		Controller::GetInstance()->SetControllerSetting(m_controllerSetting);

		// �I�������Đ�
		Sound::GetInstance()->Play(kSoundFileName[static_cast<int>(SoundName::Select)]);
	}
}

void ControllerOption::UpdateCtrlType()
{
	// �Z���N�g��
	const int selectNum = static_cast<int>(Controller::PadType::PAD_TYPE_NUM);

	if (Controller::GetInstance()->IsTrigger(Controller::ControllerButton::RIGHT))
	{
		// �I�����ڂ̍X�V
		m_controllerSetting.padType = static_cast<Controller::PadType>((static_cast<int>(m_controllerSetting.padType) + 1) % selectNum);

		// �R���g���[���[�ݒ�̍X�V
		Controller::GetInstance()->SetControllerSetting(m_controllerSetting);

		// �I�������Đ�
		Sound::GetInstance()->Play(kSoundFileName[static_cast<int>(SoundName::Select)]);
	}
	else if (Controller::GetInstance()->IsTrigger(Controller::ControllerButton::LEFT))
	{
		// �I�����ڂ̍X�V
		m_controllerSetting.padType = static_cast<Controller::PadType>((static_cast<int>(m_controllerSetting.padType) - 1 + selectNum) % selectNum);

		// �R���g���[���[�ݒ�̍X�V
		Controller::GetInstance()->SetControllerSetting(m_controllerSetting);

		// �I�������Đ�
		Sound::GetInstance()->Play(kSoundFileName[static_cast<int>(SoundName::Select)]);
	}
}

void ControllerOption::UpdateInputDevice()
{
	// �Z���N�g��
	const int selectNum = static_cast<int>(Controller::ControllerType::CONTROLLER_NUM);

	if (Pad::IsTrigger(PAD_INPUT_RIGHT))
	{
		// �I�����ڂ̍X�V
		m_controllerSetting.controllerType = static_cast<Controller::ControllerType>((static_cast<int>(m_controllerSetting.controllerType) + 1) % selectNum);

		// �R���g���[���[�ݒ�̍X�V
		Controller::GetInstance()->SetControllerSetting(m_controllerSetting);

		// �I�������Đ�
		Sound::GetInstance()->Play(kSoundFileName[static_cast<int>(SoundName::Select)]);
	}
	else if (Pad::IsTrigger(PAD_INPUT_LEFT))
	{
		// �I�����ڂ̍X�V
		m_controllerSetting.controllerType = static_cast<Controller::ControllerType>((static_cast<int>(m_controllerSetting.controllerType) - 1 + selectNum) % selectNum);

		// �R���g���[���[�ݒ�̍X�V
		Controller::GetInstance()->SetControllerSetting(m_controllerSetting);

		// �I�������Đ�
		Sound::GetInstance()->Play(kSoundFileName[static_cast<int>(SoundName::Select)]);
	}
}

void ControllerOption::DrawWindow()
{
	int const windowLeftTopX = Game::kWindowCenterX - Window::kWidth / 2;
	int const windowLeftTopY = Game::kWindowCenterY - Window::kHeight / 2;

	int const windowRightBottomX = Game::kWindowCenterX + Window::kWidth / 2;
	int const windowRightBottomY = Game::kWindowCenterY + Window::kHeight / 2;


	// �����x�ݒ�
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, Window::kAlpha);

	DrawBox(0,0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);

	// �|�[�Y�E�B���h�E
	DrawBox(windowLeftTopX, windowLeftTopY, windowRightBottomX, windowRightBottomY, 0x000000, true);

	// �����x����
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// �|�[�Y�E�B���h�E�g
	DrawBox(windowLeftTopX, windowLeftTopY, windowRightBottomX, windowRightBottomY, 0xffffff, false);




	// �E�B���h�E���̕`��
	DrawRotaGraphF(m_windowNameGraph.pos[0].x, m_windowNameGraph.pos[0].y, WindowNameGraph::kScale, 0.0, m_windowNameGraph.handle[0], TRUE);
}

void ControllerOption::DrawSettingItem()
{
	// �ݒ荀�ڂ̕`��
	for (size_t i = 0; i < m_settingItemGraph.handle.size(); i++)
	{
		if (m_controllerSetting.autoSwitch == Controller::AutoSwitch::ON &&
			SettingItemSenect(i) == SettingItemSenect::INPUT_DEVICE)
		{
			// �����x�ݒ�
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, SettingItemGraph::kAlpha);
		}

		DrawRotaGraphF(m_settingItemGraph.pos[i].x, m_settingItemGraph.pos[i].y, SettingItemGraph::kScale, 0.0, m_settingItemGraph.handle[i], TRUE);

		// �����x����
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

void ControllerOption::DrawControllerSetting()
{
	// �O���t�B�b�N��
	const int selectNum = static_cast<int>(m_controllerSettingGraph.size());

	// �ݒ荀�ڂ̕`��
	for (int i = 0; i < selectNum; i++)
	{



		// �ݒ�i���o�[
		const int settingNum = static_cast<int>(SettingItemSenect(i));
		// �摜�i���o�[
		int graphNum = 0;

		switch (SettingItemSenect(i))
		{
		case ControllerOption::SettingItemSenect::AUTO_SWITCH:
			// �摜�i���o�[
			graphNum = static_cast<int>(m_controllerSetting.autoSwitch);
			break;
		case ControllerOption::SettingItemSenect::CTRL_TYPE:
			// �摜�i���o�[
			graphNum = static_cast<int>(m_controllerSetting.padType);
			break;
		case ControllerOption::SettingItemSenect::INPUT_DEVICE:
			// �摜�i���o�[
			graphNum = static_cast<int>(m_controllerSetting.controllerType);
			break;
		default:
			// �摜�i���o�[
			graphNum = 0;
			break;
		}

		// �I�΂�Ă���I�����͐ԐF�ŕ`��
		if(m_settingItemSelect == SettingItemSenect(i))
		{
			// �I�΂�Ă���I�����͐ԐF�ŕ`��
			SetDrawBright(255, 0, 0);

			Vec2 trianglePos = m_controllerSettingGraph[i].pos[0];

			Vec2 pos = Vec2();


			switch (m_settingItemSelect)
			{
			case ControllerOption::SettingItemSenect::AUTO_SWITCH:

				pos += SelectTriangleGraph::kAutoSwitchDistance;
				break;
			case ControllerOption::SettingItemSenect::CTRL_TYPE:

				pos += SelectTriangleGraph::kCtrlTypeDistance;
				break;
			case ControllerOption::SettingItemSenect::INPUT_DEVICE:

				pos += SelectTriangleGraph::kInputDeviceDistance;
				break;
			
			default:
				break;
			}

			EvoLib::Draw::DrawRotatingImage(
				m_selectTriangleGraph,
				Vec2(trianglePos.x + pos.x, trianglePos.y + pos.y),
				0,
				false,
				SelectTriangleGraph::kScale,
				true,
				true,
				true,
				false);

			EvoLib::Draw::DrawRotatingImage(
				m_selectTriangleGraph,
				Vec2(trianglePos.x - pos.x, trianglePos.y - pos.y),
				0,
				false,
				SelectTriangleGraph::kScale,
				true,
				false,
				true,
				false);

			
		}
		else
		{
			// �����x�ݒ�
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, Window::kAlpha);
		}

		
		


		// �O���t�B�b�N�̕`��
		DrawRotaGraphF(
			m_controllerSettingGraph[i].pos[0].x, 
			m_controllerSettingGraph[i].pos[0].y, 
			m_controllerSettingGraphInfo[settingNum].kScale,
			0.0, m_controllerSettingGraph[i].handle[graphNum], TRUE);

		// �F�����ɖ߂�
		SetDrawBright(255, 255, 255);
		// �����x����
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

void ControllerOption::DrawControllerExplanation()
{
	int const width = 600;
	int const height = 280;

	int const setPosX = 0;
	int const setPosY = 150;


	int const leftTopX = (Game::kWindowCenterX - width / 2) + setPosX;
	int const leftTopY = (Game::kWindowCenterY - height / 2) + setPosY;

	int const rightBottomX = (Game::kWindowCenterX + width / 2) + setPosX;
	int const rightBottomY = (Game::kWindowCenterY + height / 2) + setPosY;




	DrawBox(leftTopX, leftTopY, rightBottomX, rightBottomY, 0xffffff, false);


}
