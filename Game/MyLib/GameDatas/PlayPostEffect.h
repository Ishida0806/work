//
//		File Name �F PlayPostEffect.h
//		Production�F 2023/1/10
//		Author�@�@�F �Γc ����	
//
#pragma once
#include "PostEffect.h"
#include "PlayerHPCrisisEffect.h"
#include "PlayerSpeedEffect.h"
#include "PlayerCureEffect.h"
#include "PlayerPowerffect.h"

class PlayerHPBar;
class Player;

class PlayPostEffect
{
	//	�萔
public:

	//	�`�掞��
	static const float RENDER_EFFECT_TIME;

	//	�ϐ�
private:

	//	HPBar
	PlayerHPBar*							  m_playerHPBar;
	//	���x���J�[�h
	Player*									  m_player;
	//	�^�X�N
	std::vector<PostEffect::PostEffectType>	  m_task;
	//	�G�t�F�N�g
	std::vector<std::unique_ptr<PostEffect>>  m_effects;
	//	�o�ߎ���
	float									  m_elapsedTime;
	//	�̗�UP�̕`�掞��
	float									  m_healthUPEffectRenderTime;
	//	���xUP�̕`�掞��
	float									  m_speedUPEffectRenderTime;
	//	��UP�̕`�掞��
	float									  m_powerUPEffectRenderTime;
	//	���x���オ�����ۂ̕`��t���O
	bool									  m_speedUPEffectRenderFlag;
	//	�̗͂��オ�����ۂ̕`��t���O
	bool									  m_healthUPEffectRenderFlag;
	//	�͂��オ�����ۂ̕`��t���O
	bool									  m_powerUPEffectRenderFlag;

	//	�֐�
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	PlayPostEffect(PlayerHPBar* playerHPBar, Player* player);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~PlayPostEffect();

	/// <summary>
	///	����������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="timer">�^�C�}�[</param>
	void Update(const DX::StepTimer& timer);

	/// <summary>
	/// �`��̃^�C�v
	/// </summary>
	void Draw();
};