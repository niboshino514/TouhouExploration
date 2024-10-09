#pragma once
#include <memory>
#include <vector>

class Effect;

class EffectManager
{
public:
	EffectManager();
	virtual ~EffectManager();

	
	void Init();
	void Update();
	void Draw();


	void CreateEffect();
private:

	// �G�t�F�N�g�n���h��
	int m_effectHandle;

	// �t���[���J�E���g
	int m_frameCount;

	// �G�t�F�N�g���X�g
	std::vector<std::shared_ptr<Effect>> m_pEffectList;

};

