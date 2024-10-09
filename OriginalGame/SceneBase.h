#pragma once

// �Q�[���V�[�����N���X
class SceneBase
{
protected:

	// �t�F�[�h
	struct Fade
	{
		// �t�F�[�h�̏��
		enum State
		{
			// �t�F�[�h�C��
			In,
			// �t�F�[�h�A�E�g
			Out,
			// �t�F�[�h�C������
			InEnd,
			// �t�F�[�h�A�E�g����
			OutEnd,
		};

		// �t�F�[�h�̏��
		State state = InEnd;

		// �t�F�[�h�̑��x
		int speed = 0;

		// �t�F�[�h�̐F
		int color = 0x000000;

		// �t�F�[�h�̃A���t�@�l
		int alpha = 0;
	};

public:
	SceneBase() {}
	virtual ~SceneBase() {}


	virtual void Init() {}
	virtual void End() {}

	virtual SceneBase* Update() { return this; }
	virtual void Draw() {}

	// �V�[���I��
	virtual bool isEnd() { return false; }

	// �t�F�[�h�C�����I�����Ă��邩�ǂ���
	bool IsFadeInEnd() { return m_fade.state == Fade::InEnd; }


protected:

	/// <summary>
	/// �t�F�[�h�C���ݒ�
	/// </summary>
	/// <param name="fadeSpeed">�t�F�[�h�X�s�[�h</param>
	/// <param name="fadeColor">�t�F�[�h�J���[</param>
	void SetFadeIn(const int& fadeSpeed, const int& fadeColor);

	/// <summary>
	/// �t�F�[�h�A�E�g�ݒ�
	/// </summary>
	/// <param name="fadeSpeed">�t�F�[�h�X�s�[�h</param>
	/// <param name="fadeColor">�t�F�[�h�J���[</param>
	void SetFadeOut(const int& fadeSpeed, const int& fadeColor);

	/// <summary>
	/// �t�F�[�h�A�E�g���I�����Ă��邩�ǂ���
	/// </summary>
	/// <returns>�t�F�[�h�A�E�g���I�����Ă��邩�ǂ����t���O��Ԃ�</returns>
	bool IsFadeOutEnd();

	/// <summary>
	/// �t�F�[�h�X�V
	/// </summary>
	void UpdateFade();

	/// <summary>
	/// �t�F�[�h�`��
	/// </summary>
	void DrawFade();

	/// <summary>
	/// �t�F�[�h�A�E�g�����ǂ���
	/// </summary>
	/// <returns>�t�F�[�h�A�E�g�t���O</returns>
	bool GetIsFadeOut() { return m_fade.state == Fade::Out; }

	/// <summary>
	/// �t�F�[�h�A���t�@�l�擾
	/// </summary>
	/// <returns>�t�F�[�h�A���t�@�l</returns>
	int GetFadeAlpha() { return m_fade.alpha; }

	/// <summary>
	/// �t�F�[�h�A�E�g���A���񂾂񉹂��������Ȃ鏈��
	/// </summary>
	void FadeOutSound();

protected:

	// ���̃V�[��
	SceneBase* m_nextScene = nullptr;

private:
	// �t�F�[�h
	Fade m_fade;
};