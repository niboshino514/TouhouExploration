#include "SoundOption.h"
#include "game.h"
#include "EvoLib.h"
#include "Controller.h"
#include "Sound.h"
#include "ObjectManager.h"


namespace Window
{
	// �|�[�Y�E�B���h�E�̉���
	const int kWidth = 650;

	// �|�[�Y�E�B���h�E�̏c��
	const int kHeight = 350;

	// �����x
	const int kAlpha = 150;
}

namespace WindowNameGraph
{
	// �O���t�B�b�N�t�@�C���p�X
	const char* const kFilePath = "Data/Graphic/SoundOption/WindowName.png";
	// ������
	const EvoLib::Load::DivNum kDivNum = { 1, 1 };
	// �g�嗦
	const double kScale = 1.0;
}

namespace SettingItemGraph
{
	// �O���t�B�b�N�t�@�C���p�X
	const char* const kFilePath = "Data/Graphic/SoundOption/SelectItem.png";
	// �O���t�B�b�N�̃O���t�B�b�N����
	const Vec2 kDistanceValue = Vec2(0, 40);
	// ������
	const EvoLib::Load::DivNum kDivNum = { 1, 2 };
	// ���S���W
	const Vec2 kCenterPos = Vec2(Game::kWindowCenterX - 200, Game::kWindowCenterY);
	// �g�嗦
	const double kScale = 0.8;
	// �����x
	const int kAlpha = 100;
}

namespace SoundVolumeGraph
{

	// �O���t�B�b�N�t�@�C���p�X
	const char* const kFilePath = "Data/Graphic/SoundOption/Bar.png";

	// �O���t�B�b�N�̃O���t�B�b�N����
	const Vec2 kDistanceValue = Vec2(0, 65);

	// ������
	const EvoLib::Load::DivNum kDivNum = { 1, 2 };

	// ���S���W
	const Vec2 kCenterPos = Vec2(Game::kWindowCenterX, Game::kWindowCenterY);

	// �g�嗦
	const double kBigScale = 0.5;
	const double kSmallScale = 0.3;

	// �����x
	const int kAlpha = 100;

	// ����
	constexpr int kWidth = 50;
}

namespace SelectTriangleGraph
{
	// �O���t�B�b�N�t�@�C���p�X
	const char* const kFilePath = "Data/Graphic/Selection/SelectTriangle.png";

	// �g�嗦
	const float kScale = 0.7f;

	// ����
	const Vec2 kDistance = Vec2(-160, 0);
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

namespace
{
	constexpr int kSoundVolumeMax = 6;
}


SoundOption::SoundOption():
	m_windowNameGraph(),
	m_settingItemGraph(),
	m_soundVolumeGraph(),
	m_selectTriangleGraph(),
	m_backGraph(),
	m_settingItemSelect(),
	m_soundVolume(),
	m_isCloseWindow()
{
}

SoundOption::~SoundOption()
{
	// �O���t�B�b�N�̉��
	for(auto& handle : m_windowNameGraph.handle)
	{
		DeleteGraph(handle);
	}
	for(auto& handle : m_settingItemGraph.handle)
	{
		DeleteGraph(handle);
	}
	for (auto& handle : m_soundVolumeGraph.handle)
	{
		DeleteGraph(handle);
	}
	for(auto& handle : m_backGraph.handle)
	{
		DeleteGraph(handle);
	}
	DeleteGraph(m_selectTriangleGraph);
}

void SoundOption::Init()
{
	// �T�E���h�{�����[���̏�����
	const int bgmVolume = static_cast<int>(EvoLib::Convert::ConvertFromPercentToValue(kSoundVolumeMax, static_cast<float>(Sound::GetInstance()->GetSoundVolume().bgm)));
	const int seVolume = static_cast<int>(EvoLib::Convert::ConvertFromPercentToValue(kSoundVolumeMax, static_cast<float>(Sound::GetInstance()->GetSoundVolume().se)));
	

	m_soundVolume.bgmVolume = bgmVolume;
	m_soundVolume.seVolume = seVolume;


	// �O���t�B�b�N�̃��[�h
	Load();
}

void SoundOption::Update()
{
	// �ݒ荀�ڂ̍X�V
	UpdateSettingItem();

	// BGM�̉��ʒ���
	UpdateSoundBgmVolume();

	// SE�̉��ʒ���
	UpdateSoundSeVolume();

	// �L�����Z���{�^���������ꂽ��E�B���h�E�����
	if (Controller::GetInstance()->IsTrigger(Controller::ControllerButton::CANCEL))
	{
		m_isCloseWindow = true;

		// �L�����Z�������Đ�
		Sound::GetInstance()->Play(kSoundFileName[static_cast<int>(SoundName::Cancel)]);
	}
}

void SoundOption::Draw()
{
	// �E�B���h�E�̕`��
	DrawWindow();

	// �ݒ荀�ڂ̕`��
	DrawSettingItem();

	// BGM�̉��ʂ̕`��
	DrawSoundBgmVolume();

	// SE�̉��ʂ̕`��
	DrawSoundSeVolume();

	// �߂�{�^���̕`��
	DrawRotaGraphF(m_backGraph.pos[0].x, m_backGraph.pos[0].y, BackGraph::kScale, 0.0, m_backGraph.handle[0], TRUE);
}

void SoundOption::InitSettingItem()
{
	// �ݒ荀�ڂ̏�����
	m_settingItemSelect = SettingItemSenect::BGM;

	// �E�B���h�E����邩�ǂ���
	m_isCloseWindow = false;
}

void SoundOption::Load()
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

	// �T�E���h�{�����[���̃O���t�B�b�N�̃��[�h
	{
		// �O���t�B�b�N���[�h
		m_soundVolumeGraph.handle = EvoLib::Load::LoadDivGraph_EvoLib_Revision
		(SoundVolumeGraph::kFilePath, SoundVolumeGraph::kDivNum);

		// ���W�̐ݒ�
		const Vec2 graphSize = EvoLib::Calculation::GetGraphSize_EvoLib(m_soundVolumeGraph.handle, SoundVolumeGraph::kBigScale);

		// ���W�̐ݒ�
		m_soundVolumeGraph.pos = EvoLib::Calculation::GraphEqualization
		(graphSize, SoundVolumeGraph::kCenterPos, static_cast<int>(m_soundVolumeGraph.handle.size()), SoundVolumeGraph::kDistanceValue, false);

	}

	// �o�b�N�O���t�B�b�N�̃��[�h
	{
		// �O���t�B�b�N���[�h
		m_backGraph.handle = EvoLib::Load::LoadDivGraph_EvoLib_Revision
		(BackGraph::kFilePath, BackGraph::kDivNum);

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

void SoundOption::UpdateSettingItem()
{
	if (Controller::GetInstance()->IsTrigger(Controller::ControllerButton::DOWN))
	{
		// �I�����ڂ̍X�V
		m_settingItemSelect = static_cast<SettingItemSenect>((static_cast<int>(m_settingItemSelect) + 1) % static_cast<int>(SettingItemSenect::SELECT_NUM));

		// �I�������Đ�
		Sound::GetInstance()->Play(kSoundFileName[static_cast<int>(SoundName::Select)]);
	}
	else if (Controller::GetInstance()->IsTrigger(Controller::ControllerButton::UP))
	{
		// �I�����ڂ̍X�V
		m_settingItemSelect = static_cast<SettingItemSenect>((static_cast<int>(m_settingItemSelect) - 1 + static_cast<int>(SettingItemSenect::SELECT_NUM)) % static_cast<int>(SettingItemSenect::SELECT_NUM));

		// �I�������Đ�
		Sound::GetInstance()->Play(kSoundFileName[static_cast<int>(SoundName::Select)]);
	}
}

void SoundOption::UpdateSoundBgmVolume()
{
	// BGM�̉��ʒ����ȊO���I������Ă���ꍇ�A�����𔲂���
	if(m_settingItemSelect != SettingItemSenect::BGM)
	{
		return;
	}



	// ���ʂ̍X�V
	if (Controller::GetInstance()->IsTrigger(Controller::ControllerButton::RIGHT))
	{

		// ������[�v
		m_soundVolume.bgmVolume++;

		if(m_soundVolume.bgmVolume >= kSoundVolumeMax)
		{
			m_soundVolume.bgmVolume = 0;
		}

		// ���ʂ̃p�[�Z���e�[�W�����߂�
		const int soundPercentageVolume = EvoLib::Convert::PercentageRate(static_cast<float>(kSoundVolumeMax), static_cast<float>(m_soundVolume.bgmVolume));

		// ���ʂ̍X�V
		Sound::GetInstance()->SetSoundVolume(Sound::SoundType::BGM, soundPercentageVolume);
		
		// �I�������Đ�
		Sound::GetInstance()->Play(kSoundFileName[static_cast<int>(SoundName::Select)]);
	}
	else if (Controller::GetInstance()->IsTrigger(Controller::ControllerButton::LEFT))
	{

		// �������[�v
		m_soundVolume.bgmVolume--;

		if(m_soundVolume.bgmVolume < 0)
		{
			m_soundVolume.bgmVolume = kSoundVolumeMax;
		}



		// ���ʂ̃p�[�Z���e�[�W�����߂�
		const int soundPercentageVolume = EvoLib::Convert::PercentageRate(static_cast<float>(kSoundVolumeMax), static_cast<float>(m_soundVolume.bgmVolume));

		// ���ʂ̍X�V
		Sound::GetInstance()->SetSoundVolume(Sound::SoundType::BGM, soundPercentageVolume);
	
		// �I�������Đ�
		Sound::GetInstance()->Play(kSoundFileName[static_cast<int>(SoundName::Select)]);
	}
}

void SoundOption::UpdateSoundSeVolume()
{
	if(m_settingItemSelect != SettingItemSenect::SE)
	{
		return;
	}


	// ���ʂ̍X�V
	if(Controller::GetInstance()->IsTrigger(Controller::ControllerButton::RIGHT))
	{
		
		m_soundVolume.seVolume++;

		if(m_soundVolume.seVolume >= kSoundVolumeMax)
		{
			m_soundVolume.seVolume = 0;
		}

		// ���ʂ̃p�[�Z���e�[�W�����߂�
		const int soundPercentageVolume = EvoLib::Convert::PercentageRate(static_cast<float>(kSoundVolumeMax), static_cast<float>(m_soundVolume.seVolume));

		// ���ʂ̍X�V
		Sound::GetInstance()->SetSoundVolume(Sound::SoundType::SE, soundPercentageVolume);

		// �I�������Đ�
		Sound::GetInstance()->Play(kSoundFileName[static_cast<int>(SoundName::Select)]);
	}
	else if(Controller::GetInstance()->IsTrigger(Controller::ControllerButton::LEFT))
	{
	
		m_soundVolume.seVolume--;

		if(m_soundVolume.seVolume < 0)
		{
			m_soundVolume.seVolume = kSoundVolumeMax;
		}

		// ���ʂ̃p�[�Z���e�[�W�����߂�
		const int soundPercentageVolume = EvoLib::Convert::PercentageRate(static_cast<float>(kSoundVolumeMax), static_cast<float>(m_soundVolume.seVolume));

		// ���ʂ̍X�V
		Sound::GetInstance()->SetSoundVolume(Sound::SoundType::SE, soundPercentageVolume);

		// �I�������Đ�
		Sound::GetInstance()->Play(kSoundFileName[static_cast<int>(SoundName::Select)]);
	}
}

void SoundOption::DrawWindow()
{
	int const windowLeftTopX = Game::kWindowCenterX - Window::kWidth / 2;
	int const windowLeftTopY = Game::kWindowCenterY - Window::kHeight / 2;

	int const windowRightBottomX = Game::kWindowCenterX + Window::kWidth / 2;
	int const windowRightBottomY = Game::kWindowCenterY + Window::kHeight / 2;


	// �����x�ݒ�
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, Window::kAlpha);

	// ��ʑS�̂����œh��Ԃ�
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);

	// �|�[�Y�E�B���h�E
	DrawBox(windowLeftTopX, windowLeftTopY, windowRightBottomX, windowRightBottomY, 0x000000, true);

	// �����x����
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// �|�[�Y�E�B���h�E�g
	DrawBox(windowLeftTopX, windowLeftTopY, windowRightBottomX, windowRightBottomY, 0xffffff, false);




	// �E�B���h�E���̕`��
	DrawRotaGraphF(m_windowNameGraph.pos[0].x, m_windowNameGraph.pos[0].y, WindowNameGraph::kScale, 0.0, m_windowNameGraph.handle[0], TRUE);

}

void SoundOption::DrawSettingItem()
{
	// �ݒ荀�ڂ̕`��
	for (int i = 0; i < static_cast<int>(m_settingItemGraph.handle.size()); i++)
	{
		// �I������Ă��Ȃ����ڂ𓧖��ɂ��ĕ`��
		if(static_cast<int>(m_settingItemSelect) != i)
		{
			
			// �����x�ݒ�
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, SettingItemGraph::kAlpha);
		}
		else
		{
			// �I�΂�Ă���I�����͐ԐF�ŕ`��
			SetDrawBright(255, 0, 0);
		}

		// �O���t�B�b�N�̕`��
		DrawRotaGraphF(m_settingItemGraph.pos[i].x, m_settingItemGraph.pos[i].y, SettingItemGraph::kScale, 0.0, m_settingItemGraph.handle[i], TRUE);


		// �F�����ɖ߂�
		SetDrawBright(255, 255, 255);
		// �����x����
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

void SoundOption::DrawSoundBgmVolume()
{
	if(m_settingItemSelect != SettingItemSenect::BGM)
	{
		// �����x�ݒ�
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, SoundVolumeGraph::kAlpha);
	}
	else
	{
		// �I�΂�Ă���I�����͐ԐF�ŕ`��
		SetDrawBright(255, 0, 0);

		// �O�p�`�̍��W
		Vec2 trianglePos = m_soundVolumeGraph.pos[0];
		trianglePos.x += ((kSoundVolumeMax / 2) - 1) * SoundVolumeGraph::kWidth;

		// ����
		Vec2 distance = SelectTriangleGraph::kDistance;


		EvoLib::Draw::DrawRotatingImage(
			m_selectTriangleGraph,
			Vec2(trianglePos.x + distance.x, trianglePos.y + distance.y),
			0,
			false,
			SelectTriangleGraph::kScale,
			true,
			true,
			true,
			false);

		EvoLib::Draw::DrawRotatingImage(
			m_selectTriangleGraph,
			Vec2(trianglePos.x - distance.x, trianglePos.y - distance.y),
			0,
			false,
			SelectTriangleGraph::kScale,
			true,
			false,
			true,
			false);
	}


	for (int i = 0; i < kSoundVolumeMax-1; i++)
	{
		Vec2 pos = m_soundVolumeGraph.pos[0];
		pos.x += i * SoundVolumeGraph::kWidth;

		

		if (i >= m_soundVolume.bgmVolume)
		{
			// �O���t�B�b�N�̕`��
			DrawRotaGraphF(pos.x, pos.y, SoundVolumeGraph::kSmallScale, 0.0, m_soundVolumeGraph.handle[1], TRUE);

		}

		if(i < m_soundVolume.bgmVolume)
		{
			// �O���t�B�b�N�̕`��
			DrawRotaGraphF(pos.x, pos.y, SoundVolumeGraph::kBigScale, 0.0, m_soundVolumeGraph.handle[0], TRUE);
		}
	}

	// �����x����
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	// �F�����ɖ߂�
	SetDrawBright(255, 255, 255);
}

void SoundOption::DrawSoundSeVolume()
{
	if(m_settingItemSelect != SettingItemSenect::SE)
	{
		// �����x�ݒ�
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, SoundVolumeGraph::kAlpha);
	}
	else
	{
		// �I�΂�Ă���I�����͐ԐF�ŕ`��
		SetDrawBright(255, 0, 0);

		// �O�p�`�̍��W
		Vec2 trianglePos = m_soundVolumeGraph.pos[1];
		trianglePos.x += ((kSoundVolumeMax / 2) - 1) * SoundVolumeGraph::kWidth;

		// ����
		Vec2 distance = SelectTriangleGraph::kDistance;


		EvoLib::Draw::DrawRotatingImage(
			m_selectTriangleGraph,
			Vec2(trianglePos.x + distance.x, trianglePos.y + distance.y),
			0,
			false,
			SelectTriangleGraph::kScale,
			true,
			true,
			true,
			false);

		EvoLib::Draw::DrawRotatingImage(
			m_selectTriangleGraph,
			Vec2(trianglePos.x - distance.x, trianglePos.y - distance.y),
			0,
			false,
			SelectTriangleGraph::kScale,
			true,
			false,
			true,
			false);
	}

	for(int i = 0; i < kSoundVolumeMax-1; i++)
	{
		Vec2 pos = m_soundVolumeGraph.pos[1];
		pos.x += i * SoundVolumeGraph::kWidth;

		if (i >= m_soundVolume.seVolume)
		{
			// �O���t�B�b�N�̕`��
			DrawRotaGraphF(pos.x, pos.y, SoundVolumeGraph::kSmallScale, 0.0, m_soundVolumeGraph.handle[1], TRUE);
		}

		if(i < m_soundVolume.seVolume)
		{
			// �O���t�B�b�N�̕`��
			DrawRotaGraphF(pos.x, pos.y, SoundVolumeGraph::kBigScale, 0.0, m_soundVolumeGraph.handle[0], TRUE);
		}
	}

	// �����x����
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	// �F�����ɖ߂�
	SetDrawBright(255, 255, 255);

}
