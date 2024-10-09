#include "TransparentBlockChip.h"
#include <DxLib.h>

#include <filesystem>
#include "EvoLib.h"

TransparentBlockChip::TransparentBlockChip()
{
}

TransparentBlockChip::~TransparentBlockChip()
{
}

void TransparentBlockChip::Init()
{
	// �I�u�W�F�N�gID��ݒ�
	m_objectID = ObjectID::TransparentBlockChip;
}

void TransparentBlockChip::Update()
{
	// �Փˏ���
	Collision();
}

void TransparentBlockChip::Draw()
{
	// �M�~�b�N�t���O�������Ă��Ȃ��ꍇ�͕`�悵�Ȃ�
	if (!m_isGimmick)
	{
		return;
	}


	// �I�t�Z�b�g�l���擾
	const Vec2 offset = GameData::GetInstance()->GetCameraPos();

	// �`��l�p�`
	Square drawSquare = m_square;
	drawSquare.A += offset;
	drawSquare.B += offset;
	drawSquare.C += offset;
	drawSquare.D += offset;

	// �����u���b�N�`��
	DrawBoxAA(drawSquare.A.x, drawSquare.A.y, drawSquare.C.x, drawSquare.C.y, 0xffffff, TRUE);
}
