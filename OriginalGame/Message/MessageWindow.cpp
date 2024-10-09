#include "MessageWindow.h"
#include "Controller.h"
#include <DxLib.h>
#include "Vec2.h"
#include "game.h"
#include <cassert>
#include "EvoLib.h"
#include "MessageTextLoader.h"




// �L�����N�^�[
namespace Character
{
	// ���[�̃L�����N�^�[���S���W
	Vec2 kLeftCenterPos = Vec2();

	// �E�[�̃L�����N�^�[���S���W
	Vec2 kRightCenterPos = Vec2();

	// ���[�̔�\���L�����N�^�[���S���W
	Vec2 kLeftCenterPosHide = Vec2();

	// �E�[�̔�\���L�����N�^�[���S���W
	Vec2 kRightCenterPosHide = Vec2();
}


MessageWindow::MessageWindow():
	m_textInfo(),
	m_windowInfo(),
	m_characterInfo(),
	m_moveSpeed(),
	m_graphNotSpeakAlpha(),
	m_isAllTextEnd(),
	m_pMessageTextLoader(std::make_shared<MessageTextLoader>())
{
}

MessageWindow::~MessageWindow()
{
	// �f�[�^�̃A�����[�h
	UnloadData();
}


void MessageWindow::Update()
{
	// ���ׂẴe�L�X�g���I�������ꍇ�A�������I������
	if(m_isAllTextEnd)
	{
		return;
	}

	// �e�L�X�g�����̌Ăяo��
	UpdateTextDisplay();

	// �e�L�X�g��؂�ւ��鏈��
	UpdateTextOnInput();

	// �L�����N�^�[�̍X�V����
	UpdateCharacterPos();
}

void MessageWindow::Draw()
{
	// �L�����N�^�[�̕`��
	DrawCharacter();

	// ���b�Z�[�W�E�B���h�E�̕`��
	DrawMessageWindow();

	// ���b�Z�[�W�e�L�X�g�̕`��
	DrawMessageText();

	// �L�����N�^�[���̕`��
	DrawCharacterNameText();
}

void MessageWindow::LoadData(const std::string& talkDataCsvFilePath)
{
	// ���ׂẴe�L�X�g�I���t���O��false�ɂ���
	m_isAllTextEnd = false;

	// ���[�h�f�[�^
	const MessageTextLoader::LoadData loadData = m_pMessageTextLoader->LoadTextData(talkDataCsvFilePath);

	// ��b���
	{
		// ��b�f�[�^�̃T�C�Y
		const int talkDataSize = static_cast<int>(loadData.talkData.size());

		// ��b�f�[�^�̃T�C�Y���A�v�f��ǉ�
		m_messageElement.resize(talkDataSize);

		// ��b�f�[�^�̃T�C�Y�������[�v
		for (int i = 0; i < talkDataSize; i++)
		{
			// �b������
			m_messageElement[i].talkText = loadData.talkData[i].talkText;

			// �b���L�����N�^�[�ԍ�
			m_messageElement[i].talkCharacterNo = loadData.talkData[i].talkCharacterNo;

			// �L�����N�^�[�̕\��ԍ�
			m_messageElement[i].talkFaceNo = loadData.talkData[i].talkFaceNo;

			// �E�[�ɕ\�����邩�ǂ���
			m_messageElement[i].isRight = loadData.talkData[i].isRight;

			// ���]�`�悷�邩�ǂ���
			m_messageElement[i].isFlip = loadData.talkData[i].isFlip;

			// �e�L�X�g�̃t�H���g�J���[
			m_messageElement[i].fontColor = loadData.talkData[i].fontColor;

			// �t�H���g�̓����x
			{
				// �����x�p�[�Z���e�[�W
				const float percentage = 100.0f - loadData.talkData[i].fontAlpha;
				// �����x��ݒ�
				m_messageElement[i].fontAlpha = EvoLib::Convert::ConvertFromPercentToValue(255, percentage);
			}

			// �t�H���g�̕����T�C�Y�^�C�v
			m_messageElement[i].fontSizeType = FontSize(loadData.talkData[i].fontSizeType);


			// ������k�킹�邩�ǂ���
			m_messageElement[i].isShake = loadData.talkData[i].isShake;

			// �e�L�X�g�X�s�[�h
			m_messageElement[i].drawCharFrame = loadData.talkData[i].drawCharFrame;

			// �t�H���g�^�C�v
			m_messageElement[i].fontType = loadData.talkData[i].fontType;

			// �e�L�X�g�̕�����
			m_messageElement[i].charInterval = loadData.talkData[i].charInterval;

			// �e�L�X�g�T�C�Y����̍s��
			m_messageElement[i].lineInterval = loadData.talkData[i].lineInterval;

			// �L�����N�^�[���J���[
			m_messageElement[i].characterNameColor = loadData.talkData[i].characterNameColor;

			// �L�����N�^�[��
			m_messageElement[i].characterName = loadData.talkData[i].characterName;
		}
	}


	// �E�B���h�E���̏�����
	{

		// �E�B���h�E�̒��S���W��ݒ�
		Vec2 windowCenterPos = Vec2();

		windowCenterPos.x = Game::kScreenWidth * 0.5f;
		windowCenterPos.y = (Game::kScreenHeight - loadData.messageWindowData.messageWindowPosOffsetY) - (loadData.messageWindowData.messageWindowWidth * 0.5f);


		// �E�B���h�E�̍�����W��ݒ�
		m_windowInfo.leftTop.x = loadData.messageWindowData.messageWindowMargin;
		m_windowInfo.leftTop.y = windowCenterPos.y - (loadData.messageWindowData.messageWindowWidth * 0.5f);

		// �E�B���h�E�̉E�����W��ݒ�
		m_windowInfo.rightBottom.x = Game::kScreenWidth - loadData.messageWindowData.messageWindowMargin;
		m_windowInfo.rightBottom.y = windowCenterPos.y + (loadData.messageWindowData.messageWindowWidth * 0.5f);

		loadData.fontData.characterNameFontSize;

		// �L�����N�^�[���̕���ݒ�
		const float characterNameFontSize = loadData.fontData.characterNameFontSize * 1.2f;

		// �L�����N�^�[����\������E�B���h�E�̍�����W��ݒ�
		m_windowInfo.nameLeftTop.x = m_windowInfo.leftTop.x;
		m_windowInfo.nameLeftTop.y = m_windowInfo.leftTop.y - characterNameFontSize;



		m_windowInfo.nameWindowWidth = (loadData.fontData.characterNameCharInterval + characterNameFontSize) * (loadData.fontData.characterNameMaxCharCount + 1);

		m_windowInfo.nameRightBottom.x = m_windowInfo.nameLeftTop.x + m_windowInfo.nameWindowWidth;
		m_windowInfo.nameRightBottom.y = m_windowInfo.nameLeftTop.y + characterNameFontSize;
	}


	// �e�L�X�g���̏�����
	{
		// �e�L�X�g�X�s�[�h���t���[���J�E���g�ɑ��
		m_textInfo.frameCount = loadData.talkData[0].drawCharFrame;

		// �e�L�X�g�ԍ���0�ɂ���
		m_textInfo.currentNumber = 0;

		// ���͂̕\���I���t���O��false�ɂ���
		m_textInfo.isEndText = false;

		// ������𑁂��`�悷��t���O��false�ɂ���
		m_textInfo.isFastDraw = false;

		// �������\�����邩���w�肷��
		m_textInfo.dispCharCount = 0;

		// �������}������
		m_textInfo.m_temp = loadData.talkData[0].talkText.c_str();


		// �t�H���g�֘A
		{
			// �ʏ�t�H���g�T�C�Y���擾
			m_textInfo.normalFontSize = loadData.fontData.normalFontSize;
			// �������t�H���g�T�C�Y���擾
			m_textInfo.smallFontSize = loadData.fontData.smallFontSize;
			// �傫���t�H���g�T�C�Y���擾
			m_textInfo.bigFontSize = loadData.fontData.bigFontSize;

			// �t�H���g�f�[�^�̃T�C�Y
			const int fontDataSize = static_cast<int>(loadData.fontData.fontFilePath.size());

			// �t�H���g�n���h���̃T�C�Y��ݒ�
			m_textInfo.fontHandle.resize(fontDataSize);

			// �t�H���g�̐��������[�v
			for (int i = 0; i < fontDataSize; i++)
			{
				// �ʏ�t�H���g�T�C�Y�̃t�H���g�n���h�����擾
				m_textInfo.fontHandle[i].push_back
				((EvoLib::Load::LoadFont(loadData.fontData.fontFilePath[i].c_str(), loadData.fontData.fontName[i].c_str(), m_textInfo.normalFontSize)));

				// �������t�H���g�T�C�Y�̃t�H���g�n���h�����擾
				m_textInfo.fontHandle[i].push_back
				((EvoLib::Load::LoadFont(loadData.fontData.fontFilePath[i].c_str(), loadData.fontData.fontName[i].c_str(), m_textInfo.smallFontSize)));

				// �傫���t�H���g�T�C�Y�̃t�H���g�n���h�����擾
				m_textInfo.fontHandle[i].push_back
				((EvoLib::Load::LoadFont(loadData.fontData.fontFilePath[i].c_str(), loadData.fontData.fontName[i].c_str(), m_textInfo.bigFontSize)));
			}


			// �L�����N�^�[���̃t�H���g���擾
			m_textInfo.nameFontHandle =
				EvoLib::Load::LoadFont(loadData.fontData.fontFilePath[loadData.fontData.characterNameFontType].c_str(), loadData.fontData.fontName[loadData.fontData.characterNameFontType].c_str(), loadData.fontData.characterNameFontSize);



			// �L�����N�^�[���̕������Ԋu��ݒ�
			m_textInfo.characterNameCharInterval = loadData.fontData.characterNameCharInterval;

			// �t�H���g�T�C�Y���擾
			int fontSize = GetDrawStringWidthToHandle("L", 1, m_textInfo.fontHandle[0][0]);

			// �e�L�X�g�̍��W��ݒ�
			m_textInfo.textPos = Vec2(m_windowInfo.leftTop.x + fontSize, m_windowInfo.leftTop.y + fontSize);
		}
	}

	// �L�����N�^�[���̏�����
	{
		// �L�����N�^�[�̃O���t�B�b�N�n���h���̎擾
		{
			// �L�����N�^�[�f�[�^�̃T�C�Y
			const int characterGraphFilePathSize = static_cast<int>(loadData.characterData.characterFilePath.size());

			// �L�����N�^�[���̃T�C�Y��ݒ�
			m_characterInfo.resize(characterGraphFilePathSize);


			for (int i = 0; i < static_cast<int>(m_characterInfo.size()); i++)
			{
				// �L�����N�^�[�̕�����
				const int SplitX = loadData.characterData.characterSplitX[i];
				const int SplitY = loadData.characterData.characterSplitY[i];

				// �O���t�B�b�N�̕�����
				const EvoLib::Load::DivNum divNum = { SplitX,SplitY };

				// �L�����N�^�[�̃O���t�B�b�N�n���h���̎擾
				m_characterInfo[i].graphicHandle = EvoLib::Load::LoadDivGraph_EvoLib_Revision(loadData.characterData.characterFilePath[i].c_str(), divNum);

				// �L�����N�^�[���E�����ɂ��邩�ǂ���
				m_characterInfo[i].isGraphRight = !loadData.characterData.characterIsRight[i];

				// �L�����N�^�[�̊g�嗦��ݒ�
				m_characterInfo[i].scale = loadData.characterData.characterScale[i];

				// �L�����N�^�[����ݒ�
				m_characterInfo[i].name = loadData.characterData.characterName[i].c_str();

				// �L�����N�^�[�̒����l��ݒ�
				m_characterInfo[i].centerPosOffset =
					Vec2(loadData.characterData.characterAdjustX[i], loadData.characterData.characterAdjustY[i]);


			}
		}

		// ���W�֘A
		{

			// �L�����N�^�[�̒��S���W��ݒ�
			Vec2 characterCenterPos = Vec2();



			characterCenterPos.x = Game::kScreenWidth * 0.5f;
			characterCenterPos.y = (Game::kScreenHeight - loadData.characterData.characterCenterPosOffsetY);


			// �L�����N�^�[�̍��[���W��ݒ�
			Character::kLeftCenterPos.x = loadData.characterData.characterCenterPosOffsetX;
			Character::kLeftCenterPos.y = characterCenterPos.y;

			// �L�����N�^�[�̉E�[���W��ݒ�
			Character::kRightCenterPos.x = Game::kScreenWidth - loadData.characterData.characterCenterPosOffsetX;
			Character::kRightCenterPos.y = characterCenterPos.y;

			loadData.characterData.characterNotSpeakCenterPosOffsetY;

			// �L�����N�^�[�̍��[��\�����W��ݒ�
			Character::kLeftCenterPosHide.x = Character::kLeftCenterPos.x - loadData.characterData.characterNotSpeakCenterPosOffsetY;
			Character::kLeftCenterPosHide.y = Character::kLeftCenterPos.y + loadData.characterData.characterNotSpeakCenterPosOffsetY;

			// �L�����N�^�[�̉E�[��\�����W��ݒ�
			Character::kRightCenterPosHide.x = Character::kRightCenterPos.x + loadData.characterData.characterNotSpeakCenterPosOffsetY;
			Character::kRightCenterPosHide.y = Character::kRightCenterPos.y + loadData.characterData.characterNotSpeakCenterPosOffsetY;
		}

		// �L�����N�^�[�̈ړ����x��ݒ�
		m_moveSpeed = loadData.characterData.characterMoveSpeed;

		// �L�����N�^�[�̓����x��ݒ�
		{
			// �L�����N�^�[���b���Ă��Ȃ����̉摜�̓����x�p�[�Z���e�[�W
			const float percentage = 100.0f - loadData.characterData.characterNotSpeakAlphaPercentage;
			// �L�����N�^�[���b���Ă��Ȃ����̉摜�̓����x��ݒ�
			m_graphNotSpeakAlpha = EvoLib::Convert::ConvertFromPercentToValue(255, percentage);
		}


		// ��Ԃ͂��߂ɕ\������L�����N�^�[�̍��W��ݒ�
		InitCharacterPos(m_messageElement[m_textInfo.currentNumber].isRight);
	}
}

void MessageWindow::InitData()
{
	// �f�[�^�̃A�����[�h
	UnloadData();

	// �e�L�X�g���
	m_textInfo = TextDisplayInfo();

	// �E�B���h�E���
	m_windowInfo = MessageWindowInfo();

	// ���b�Z�[�W�v�f
	m_messageElement.clear();

	// ���ׂẴe�L�X�g���I���������ǂ���
	m_isAllTextEnd = false;
	
}

void MessageWindow::ResetData()
{
	m_textInfo.currentNumber = 0;

	// �\�����镶������������
	m_textInfo.dispCharCount = 0;

	// ���͂̕\���I���t���O��false�ɂ���
	m_textInfo.isEndText = false;

	// ������𑁂��`�悷��t���O��false�ɂ���
	m_textInfo.isFastDraw = false;

	// �t���[���J�E���g���e�L�X�g�X�s�[�h�ɑ��
	m_textInfo.frameCount = m_messageElement[m_textInfo.currentNumber].drawCharFrame;

	// �������}������
	m_textInfo.m_temp = m_messageElement[m_textInfo.currentNumber].talkText;

	// �L�����N�^�[���W������
	InitCharacterPos(m_messageElement[m_textInfo.currentNumber].isRight);


	// ���ׂẴe�L�X�g���I���������ǂ���
	m_isAllTextEnd = false;
}

void MessageWindow::UnloadData()
{
	// �O���t�B�b�N�n���h���̉��
	{
		// �L�����N�^�[���̃T�C�Y
		const int characterInfoSize = static_cast<int>(m_characterInfo.size());

		// �L�����N�^�[���̃T�C�Y�������[�v
		for (int i = 0; i < characterInfoSize; i++)
		{
			// �O���t�B�b�N�n���h���̃T�C�Y
			const int graphicHandleSize = static_cast<int>(m_characterInfo[i].graphicHandle.size());

			// �O���t�B�b�N�n���h���̃T�C�Y�������[�v
			for (int j = 0; j < graphicHandleSize; j++)
			{
				// �O���t�B�b�N�n���h���̉��
				DeleteGraph(m_characterInfo[i].graphicHandle[j]);
			}
		}
	}

	// �t�H���g�n���h���̉��
	{
		// �t�H���g�f�[�^�̃T�C�Y
		const int fontDataSize = static_cast<int>(m_textInfo.fontHandle.size());

		// �t�H���g�f�[�^�̃T�C�Y�������[�v
		for (int i = 0; i < fontDataSize; i++)
		{
			// �t�H���g�n���h���̃T�C�Y
			const int fontHandleSize = static_cast<int>(m_textInfo.fontHandle[i].size());

			// �t�H���g�n���h���̃T�C�Y�������[�v
			for (int j = 0; j < fontHandleSize; j++)
			{
				// �t�H���g�n���h���̉��
				DeleteFontToHandle(m_textInfo.fontHandle[i][j]);
			}
		}
	}
}

void MessageWindow::UpdateTextDisplay()
{
	// ���͂̕\�����I����Ă����ꍇ�A�������I������
	if (m_textInfo.isEndText)
	{
		return;
	}

	// ������𑁂��`�悷��t���O�������Ă��Ȃ��ꍇ�A�t���[���J�E���g�����炷
	if (!m_textInfo.isFastDraw)
	{
		// �t���[���J�E���g�����炷
		m_textInfo.frameCount--;

		// �t���[���J�E���g��0�ɂȂ������A�e�L�X�g�X�s�[�h���t���[���J�E���g�ɑ�����A�\�����镶�����𑝂₷
		if (m_textInfo.frameCount <= 0)
		{
			// �e�L�X�g�X�s�[�h���t���[���J�E���g�ɑ��
			m_textInfo.frameCount = m_messageElement[m_textInfo.currentNumber].drawCharFrame;

			// �\�����镶�����𑝂₷
			m_textInfo.dispCharCount++;
		}
	}
	else
	{
		// �\�����镶�����𑝂₷
		m_textInfo.dispCharCount++;
	}

	// �o�C�g�����J�E���g
	int currentByte = 0;

	// ������̃o�C�g�����J�E���g
	for (int i = 0; i < m_textInfo.dispCharCount; i++)
	{
		// ������̃o�C�g�����J�E���g
		const int tempSize = static_cast<int>(m_textInfo.m_temp.size());

		// ������̃o�C�g���𒴂����ꍇ�A�������I������
		if (currentByte >= m_textInfo.m_temp.size())
		{
			m_textInfo.isEndText = true;

			// �\�����镶�����S�ĕ\��������A�\�����镶�����𕶎���̒����ɂ���
			m_textInfo.dispCharCount = static_cast<int>(m_textInfo.m_temp.size());

			break;
		}

		// �����f�[�^���擾
		unsigned char charData = m_textInfo.m_temp[currentByte]; 
		
		// �`�F�b�N���镶��
		if (charData == '\n')
		{
			// ���s�����̏ꍇ
			currentByte += 2; // ���s�������X�L�b�v
			continue;
		}
		else if (charData < 0x80)
		{
			currentByte += 1;
		}
		else
		{
			currentByte += 2;
		}
	}
}


void MessageWindow::UpdateTextOnInput()
{
	if (Controller::GetInstance()->IsTrigger(Controller::ControllerButton::DECIDE))
	{
		// ���͂̕\�����I����Ă����ꍇ�A�������I������
		if (m_textInfo.isEndText)
		{


			// ���̃e�L�X�g������ꍇ�A���̃e�L�X�g�ɂ���
			if (m_textInfo.currentNumber < (static_cast<int>(m_messageElement.size()) - 1))
			{
			

				// ������
				{
					// ���̃e�L�X�g�ԍ��ɂ���
					m_textInfo.currentNumber++;
					// �\�����镶������������
					m_textInfo.dispCharCount = 0;

					// ���͂̕\���I���t���O��false�ɂ���
					m_textInfo.isEndText = false;

					// ������𑁂��`�悷��t���O��false�ɂ���
					m_textInfo.isFastDraw = false;

					// �t���[���J�E���g���e�L�X�g�X�s�[�h�ɑ��
					m_textInfo.frameCount = m_messageElement[m_textInfo.currentNumber].drawCharFrame;
				}

				// �������}������
				m_textInfo.m_temp = m_messageElement[m_textInfo.currentNumber].talkText;

				// �L�����N�^�[���W������
				InitCharacterPos(m_messageElement[m_textInfo.currentNumber].isRight);
			}
			else
			{
				// ���ׂẴe�L�X�g���I�������ꍇ�A�t���O�𗧂Ă�
				m_isAllTextEnd = true;
			}
		}
		else
		{
			// ������𑁂��`�悷��t���O��true�ɂ���
			m_textInfo.isFastDraw = true;
		}
	}
}

void MessageWindow::DrawMessageText()
{

	// ���݂̃e�L�X�g�ԍ�
	const int currentNumber = m_textInfo.currentNumber;

	// �e�L�X�g�̍��W
	Vec2 textPos = m_textInfo.textPos;

	int currentByte = 0;

	// �t�H���g�ԍ�
	const int fontNumber = m_messageElement[currentNumber].fontType;

	// �t�H���g�n���h���̌���i��F����̕����ʒu�Ńt�H���g��ύX����j
	const int fontHandle = m_textInfo.fontHandle[fontNumber][static_cast<int>(m_messageElement[currentNumber].fontSizeType)];

	// �e�L�X�g�̐F
	const int color = m_messageElement[currentNumber].fontColor;

	// �s��
	const float lineSpace = m_textInfo.normalFontSize * m_messageElement[currentNumber].lineInterval; // �s��

	// ���s�������ǂ���
	bool isLineBreak = false;

	bool isLineBreak_test = false;



	// �`��u�����h���[�h���A���t�@�u�����h�ɂ���
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_messageElement[currentNumber].fontAlpha);


	for (int i = 0; i < m_textInfo.dispCharCount; i++)
	{
		if (currentByte >= m_textInfo.m_temp.size()) break;
		unsigned char charData = m_textInfo.m_temp[currentByte];
		int size = 0;

	

		if (charData == '\\')
		{
			// ���s�����̏ꍇ
			textPos.x = m_textInfo.textPos.x; // �s�̐擪�ɖ߂�
			textPos.y += GetFontSizeToHandle(fontHandle); // �s�̍��������Z
			textPos.y += lineSpace; // �s�Ԃ����Z

			currentByte += 2; // ���s�������X�L�b�v

			isLineBreak = true;

			isLineBreak_test = true;

			continue;
		}
		else if (IsTextInWindow(textPos, fontHandle))
		{
			textPos.x = m_textInfo.textPos.x; // �s�̐擪�ɖ߂�
			textPos.y += GetFontSizeToHandle(fontHandle); // �s�̍��������Z
			textPos.y += lineSpace; // �s�Ԃ����Z

			isLineBreak = true;

			continue;
		}
		else
		{
			if (i != 0 && !isLineBreak)
			{
				// �e�L�X�g�̉�����ǉ�
				textPos.x += m_messageElement[currentNumber].charInterval;
			}
		}
		


		if (charData < 0x80) 
		{
			size = 1;
		}
		else {
			size = 2;
		}

		int shakeX = GetRand(2) - 1;
		int shakeY = GetRand(2) - 1;

		// �e�L�X�g�̗h���ݒ�
		if (!m_messageElement[currentNumber].isShake)
		{
			shakeX = 0;
			shakeY = 0;
		}

		Vec2 shakePos = textPos;
		shakePos.x += shakeX;
		shakePos.y += shakeY;




		// ������̕`��
		DrawStringFToHandle(shakePos.x, shakePos.y, m_textInfo.m_temp.substr(currentByte, size).c_str(), color, fontHandle);

		
		textPos.x += GetDrawStringWidth(m_textInfo.m_temp.substr(currentByte, size).c_str(), size, fontHandle);

		currentByte += size;

		isLineBreak = false;
		isLineBreak_test = false;
	}

	// �`��u�����h���[�h���m�[�u�����h�ɂ���
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void MessageWindow::DrawCharacterNameText()
{
	

	int currentByte = 0;

	// �t�H���g�n���h���̌���i��F����̕����ʒu�Ńt�H���g��ύX����j
	const int fontHandle = m_textInfo.nameFontHandle;

	// �e�L�X�g�̐F
	const int color = m_messageElement[m_textInfo.currentNumber].characterNameColor;


	// �������}������
	std::string temp = m_messageElement[m_textInfo.currentNumber].characterName;

	



	// �\�����镶�����S�ĕ\��������A�\�����镶�����𕶎���̒����ɂ���
	const int dispCharCount = static_cast<int>(temp.size());


	Vec2 nameWindowCenterPos = Vec2();
	nameWindowCenterPos.x = m_windowInfo.nameLeftTop.x + (m_windowInfo.nameWindowWidth * 0.5f);
	nameWindowCenterPos.y = m_windowInfo.nameLeftTop.y;

	float textWidth = static_cast<float>(GetDrawStringWidthToHandle(temp.c_str(), dispCharCount, fontHandle));
	textWidth *= 1.1f;


	// �e�L�X�g�̍��W
	Vec2 textPos = Vec2();
	textPos.x = nameWindowCenterPos.x - (textWidth * 0.5f);
	textPos.y = nameWindowCenterPos.y;


	for (int i = 0; i < dispCharCount; i++)
	{
		if (currentByte >= temp.size()) break;
		unsigned char charData = temp[currentByte];
		int size = 0;


		if (i != 0)
		{
			// �e�L�X�g�̉��������Z
			textPos.x += m_textInfo.characterNameCharInterval;
		}

	
		if (charData < 0x80)
		{
			size = 1;
		}
		else {
			size = 2;
		}

	
		// ������̕`��
		DrawStringFToHandle(textPos.x, textPos.y, temp.substr(currentByte, size).c_str(), color, fontHandle);


		textPos.x += GetDrawStringWidth(temp.substr(currentByte, size).c_str(), size, fontHandle);

		currentByte += size;
	}
}


int MessageWindow::GetDrawStringWidth(const char* str, const int& length, const int& fontHandle)
{
	// ������̕����v�Z
	int originalWidth = GetDrawStringWidthToHandle(str, length, fontHandle);
	return originalWidth;
}

bool MessageWindow::IsTextInWindow(const Vec2 textPos, const int fontHandle)
{
	// �t�H���g�T�C�Y���擾
	const int fontSize = GetFontSizeToHandle(fontHandle);

	// �e�L�X�g�̉E�[���W���v�Z
	const float textRightPos = textPos.x + (fontSize*2);

	// �e�L�X�g�̉E�[���W���E�B���h�E�̉E�[���W�𒴂��Ă���ꍇ�Atrue��Ԃ�
	if (m_windowInfo.rightBottom.x <= textRightPos)
	{
		return true;	
	}

	

	return false;
}





void MessageWindow::DrawMessageWindow()
{
	// �`��u�����h���[�h���A���t�@�u�����h�i�T�O���j�ɂ���
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);

	// ���b�Z�[�W�E�B���h�E�̕`��
	DrawBoxAA(m_windowInfo.leftTop.x, m_windowInfo.leftTop.y, m_windowInfo.rightBottom.x, m_windowInfo.rightBottom.y, 0xffffff, true);

	// �L�����N�^�[����\������E�B���h�E�̕`��
	DrawBoxAA(m_windowInfo.nameLeftTop.x, m_windowInfo.nameLeftTop.y, m_windowInfo.nameRightBottom.x, m_windowInfo.nameRightBottom.y, 0xffffff, true);

	// �`��u�����h���[�h���m�[�u�����h�ɂ���
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// ���b�Z�[�W�E�B���h�E�̕`��
	DrawBoxAA(m_windowInfo.leftTop.x, m_windowInfo.leftTop.y, m_windowInfo.rightBottom.x, m_windowInfo.rightBottom.y, 0xffffff, false);

	// �L�����N�^�[����\������E�B���h�E�̕`��
	DrawBoxAA(m_windowInfo.nameLeftTop.x, m_windowInfo.nameLeftTop.y, m_windowInfo.nameRightBottom.x, m_windowInfo.nameRightBottom.y, 0xffffff, false);
}

void MessageWindow::InitCharacterPos(const bool& isRightDraw)
{
	// �L�����N�^�[�ԍ�
	const int characterNumber = m_messageElement[m_textInfo.currentNumber].talkCharacterNo;

	// ��O�̃e�L�X�g�ԍ�
	const int beforeTextNumber = m_textInfo.currentNumber - 1;



	if (beforeTextNumber < 0)
	{
		SetUpCharacterPos(m_messageElement[m_textInfo.currentNumber].isRight, characterNumber, false);

		return;
	}

	// �L�����N�^�[�ԍ�
	const int characterBeforeNumber = m_messageElement[beforeTextNumber].talkCharacterNo;


	if (m_messageElement[m_textInfo.currentNumber].isRight == m_messageElement[beforeTextNumber].isRight &&
		characterNumber == characterBeforeNumber)
	{
		return;
	}



	SetUpCharacterPos(m_messageElement[beforeTextNumber].isRight, characterBeforeNumber, true);


	SetUpCharacterPos(m_messageElement[m_textInfo.currentNumber].isRight, characterNumber, false);
}


void MessageWindow::SetUpCharacterPos(const bool& isRightDraw, const int& characterNumber, const bool isBeforeNumber)
{
	if (!isBeforeNumber)
	{
		// ���[�ɕ\�����邩�ǂ���
		if (!isRightDraw)
		{
			m_characterInfo[characterNumber].pos = Character::kLeftCenterPosHide;
			m_characterInfo[characterNumber].pos.y += m_characterInfo[characterNumber].centerPosOffset.y;
			m_characterInfo[characterNumber].pos.x += m_characterInfo[characterNumber].centerPosOffset.x;

			m_characterInfo[characterNumber].targetPos = Character::kLeftCenterPos;
			m_characterInfo[characterNumber].targetPos.y += m_characterInfo[characterNumber].centerPosOffset.y;
			m_characterInfo[characterNumber].targetPos.x += m_characterInfo[characterNumber].centerPosOffset.x;

		}
		else
		{
			m_characterInfo[characterNumber].pos = Character::kRightCenterPosHide;
			m_characterInfo[characterNumber].pos.y += m_characterInfo[characterNumber].centerPosOffset.y;
			m_characterInfo[characterNumber].pos.x -= m_characterInfo[characterNumber].centerPosOffset.x;

			m_characterInfo[characterNumber].targetPos = Character::kRightCenterPos;
			m_characterInfo[characterNumber].targetPos.y += m_characterInfo[characterNumber].centerPosOffset.y;
			m_characterInfo[characterNumber].targetPos.x -= m_characterInfo[characterNumber].centerPosOffset.x;
		}
	}
	else
	{
		// ���[�ɕ\�����邩�ǂ���
		if (!isRightDraw)
		{
			m_characterInfo[characterNumber].pos = Character::kLeftCenterPos;
			m_characterInfo[characterNumber].pos.y += m_characterInfo[characterNumber].centerPosOffset.y;
			m_characterInfo[characterNumber].pos.x += m_characterInfo[characterNumber].centerPosOffset.x;

			m_characterInfo[characterNumber].targetPos = Character::kLeftCenterPosHide;
			m_characterInfo[characterNumber].targetPos.y += m_characterInfo[characterNumber].centerPosOffset.y;
			m_characterInfo[characterNumber].targetPos.x += m_characterInfo[characterNumber].centerPosOffset.x;
		}
		else
		{
			m_characterInfo[characterNumber].pos = Character::kRightCenterPos;
			m_characterInfo[characterNumber].pos.y += m_characterInfo[characterNumber].centerPosOffset.y;
			m_characterInfo[characterNumber].pos.x -= m_characterInfo[characterNumber].centerPosOffset.x;


			m_characterInfo[characterNumber].targetPos = Character::kRightCenterPosHide;
			m_characterInfo[characterNumber].targetPos.y += m_characterInfo[characterNumber].centerPosOffset.y;
			m_characterInfo[characterNumber].targetPos.x -= m_characterInfo[characterNumber].centerPosOffset.x;
		}
	}

	// �ړ��ʂ�������
	m_characterInfo[characterNumber].vec = Vec2();

	// �E���ɕ\������Ă��邩�ǂ���
	m_characterInfo[characterNumber].isRightDraw = isRightDraw;
}

void MessageWindow::UpdateCharacterPos()
{

	// �L�����N�^�[�ԍ�
	const int characterNumber = m_messageElement[m_textInfo.currentNumber].talkCharacterNo;


	// �L�����N�^�[�̍��W���ړ�
	{
		m_characterInfo[characterNumber].vec = EvoLib::Calculation::TargetMoveValue(m_characterInfo[characterNumber].pos, m_characterInfo[characterNumber].targetPos, m_moveSpeed);

		m_characterInfo[characterNumber].pos += m_characterInfo[characterNumber].vec;

		if(EvoLib::Calculation::IsTargetRangeValue(m_characterInfo[characterNumber].pos.x, m_characterInfo[characterNumber].targetPos.x, m_moveSpeed))
		{
			m_characterInfo[characterNumber].pos.x = m_characterInfo[characterNumber].targetPos.x;
		}

		if(EvoLib::Calculation::IsTargetRangeValue(m_characterInfo[characterNumber].pos.y, m_characterInfo[characterNumber].targetPos.y, m_moveSpeed))
		{
			m_characterInfo[characterNumber].pos.y = m_characterInfo[characterNumber].targetPos.y;
		}
	}

	// ��O�̃e�L�X�g�ԍ�
	const int beforeTextNumber = m_textInfo.currentNumber - 1;

	// ��O�̃e�L�X�g�ԍ���0�����̏ꍇ�A�������I������
	if (beforeTextNumber < 0)
	{
		return;
	}

	// �L�����N�^�[�ԍ�
	const int characterBeforeNumber = m_messageElement[beforeTextNumber].talkCharacterNo;


	// �L�����N�^�[�̍��W���ړ�
	{
		m_characterInfo[characterBeforeNumber].vec = EvoLib::Calculation::TargetMoveValue(m_characterInfo[characterBeforeNumber].pos, m_characterInfo[characterBeforeNumber].targetPos, m_moveSpeed);

		m_characterInfo[characterBeforeNumber].pos += m_characterInfo[characterBeforeNumber].vec;


		if (EvoLib::Calculation::IsTargetRangeValue(m_characterInfo[characterBeforeNumber].pos.x, m_characterInfo[characterBeforeNumber].targetPos.x, m_moveSpeed))
		{
			m_characterInfo[characterBeforeNumber].pos.x = m_characterInfo[characterBeforeNumber].targetPos.x;
		}

		if (EvoLib::Calculation::IsTargetRangeValue(m_characterInfo[characterBeforeNumber].pos.y, m_characterInfo[characterBeforeNumber].targetPos.y, m_moveSpeed))
		{
			m_characterInfo[characterBeforeNumber].pos.y = m_characterInfo[characterBeforeNumber].targetPos.y;
		}
	}
}

void MessageWindow::DrawCharacter()
{
	// ���݂̃L�����N�^�[�ԍ�
	const int characterNumber = m_messageElement[m_textInfo.currentNumber].talkCharacterNo;

	// �O��̃L�����N�^�[�ԍ�
	int characterBeforeNumber = 0;

	// ��O�̃e�L�X�g�ԍ�
	const int beforeTextNumber = m_textInfo.currentNumber - 1;

	// ���]���ĕ`�悷�邩�ǂ���
	bool isGraphReverse = false;

	
	isGraphReverse = IsFlipCharacter(characterNumber, m_textInfo.currentNumber);
	

	// �L�����N�^�[�̕`��
	DrawRotaGraphF
	(
		m_characterInfo[characterNumber].pos.x,
		m_characterInfo[characterNumber].pos.y,
		m_characterInfo[characterNumber].scale,
		0.0, 
		m_characterInfo[characterNumber].graphicHandle[m_messageElement[m_textInfo.currentNumber].talkFaceNo],
		true, 
		isGraphReverse
	);
	

	// �������ɂ��ĕ`��
	{
		// ��O�̃e�L�X�g�ԍ���0�����̏ꍇ�A�������I������
		if (beforeTextNumber < 0)
		{
			return;
		}

		// �O��̃L�����N�^�[�ԍ����
		characterBeforeNumber = m_messageElement[beforeTextNumber].talkCharacterNo;



		// �ǂ��炩�Е��ɃL�����N�^�[���\������Ă��Ȃ��ꍇ�A�\��������
 		if(m_messageElement[m_textInfo.currentNumber].isRight == m_messageElement[beforeTextNumber].isRight)
		{
			bool isRightDraw = m_messageElement[m_textInfo.currentNumber].isRight;

			for (int i = m_textInfo.currentNumber; i >= 0; --i)
			{
				if (isRightDraw != m_messageElement[i].isRight)
				{
					// �`��u�����h���[�h���A���t�@�u�����h�i�T�O���j�ɂ���
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_graphNotSpeakAlpha);

					int number = m_messageElement[i].talkCharacterNo;

					
					if (characterNumber == number)
					{
						continue;
					}

					if(isRightDraw == m_characterInfo[number].isRightDraw)
					{
						continue;
					}



					isGraphReverse = IsFlipCharacter(number, i);



					DrawRotaGraphF
					(
						m_characterInfo[number].pos.x, 
						m_characterInfo[number].pos.y, 
						m_characterInfo[number].scale, 
						0.0, 
						m_characterInfo[number].graphicHandle[m_messageElement[i].talkFaceNo],
						true, 
						isGraphReverse
					);

					// �`��u�����h���[�h���m�[�u�����h�ɂ���
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

					return;
				}
			}
		}
		else
		{

 			if (characterNumber == characterBeforeNumber)
			{
				return;
			}


			isGraphReverse = IsFlipCharacter(characterBeforeNumber, beforeTextNumber);

			// �`��u�����h���[�h���A���t�@�u�����h
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_graphNotSpeakAlpha);

			// �L�����N�^�[�̕`��
			DrawRotaGraphF
			(
				m_characterInfo[characterBeforeNumber].pos.x, 
				m_characterInfo[characterBeforeNumber].pos.y, 
				m_characterInfo[characterBeforeNumber].scale,
				0.0, 
				m_characterInfo[characterBeforeNumber].graphicHandle[m_messageElement[beforeTextNumber].talkFaceNo], 
				true, 
				isGraphReverse
			);

			// �`��u�����h���[�h���m�[�u�����h�ɂ���
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
	}
}

bool MessageWindow::IsFlipCharacter(const int& characterNumber, const int& textNumber)
{
	if (m_characterInfo[characterNumber].isGraphRight)
	{
		// �������Ȃ����true��Ԃ�
		const bool isRightDraw = m_messageElement[textNumber].isRight;

		const bool isFlip = m_messageElement[textNumber].isFlip;


		if(isRightDraw == isFlip)
		{
			return true;
		}
		
		if (!isRightDraw == isFlip)
		{
			return false;
		}
	}
	else
	{
		// �������Ȃ����false��Ԃ�

		const bool isRightDraw = m_messageElement[textNumber].isRight;

		const bool isFlip = m_messageElement[textNumber].isFlip;

		if (isRightDraw == isFlip)
		{
			return false;
		}

		if (!isRightDraw == isFlip)
		{
			return true;
		}
	}

	return false;
}