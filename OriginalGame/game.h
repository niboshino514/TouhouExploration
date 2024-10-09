#pragma once

namespace Game
{
	// �E�C���h�E���[�h�ݒ�
	constexpr bool kWindowMode = true;
	// �E�C���h�E��
	const char* const kTitleText = "OriginalGame";

	// �E�C���h�E�T�C�Y
	constexpr int kScreenWidth = 1400;
	constexpr int kScreenHeight = 800;

	// �E�C���h�E�T�C�Y(float�^)
	constexpr float kScreenWidth_F = static_cast<float>(kScreenWidth);
	constexpr float kScreenHeight_F = static_cast<float>(kScreenHeight);


	// �E�B���h�E���S���W
	constexpr int kWindowCenterX = kScreenWidth / 2;
	constexpr int kWindowCenterY = kScreenHeight / 2;

	// �E�B���h�E���S���W(float�^)
	constexpr float kWindowCenterX_F = kScreenWidth_F * 0.5f;
	constexpr float kWindowCenterY_F = kScreenHeight_F * 0.5f;

	// �J���[���[�h
	constexpr int kColorDepth = 32;		// 32 or 16
};