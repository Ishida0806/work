//
//		File Name �F PlayerStatus.h
//		Production�F 2023/1/30
//		Author�@�@�F �Γc ����	
//
#pragma once
#include "Game/MyLib/Scenes/PlayScene/Object/PlayerExperiencePoint/PlayerExperiencePoint.h"
#include "Game/MyLib/GameDatas/PostEffect.h"

class PlayerStatus 
{
	//	�A�N�Z�T
public:

	//	�v���C���[�̌o���l�̃|�C���^�[���擾����
	PlayerExperiencePoint*			 GetPlayerEXPoint()			const { return m_playerEP.get(); }
	//	���x�����擾����
	int								 GetPlayerLevel()			const { return m_level; }
	//	�̗͂̍ő�l���擾
	int								 GetMaxHealth()				const { return m_maxHealth; }
	//	�̗͂��擾
	int								 GetHealth()				const { return m_health; }
	//	�U���͂��擾
	int								 GetPower()					const { return m_power + m_attckPower; }
	//	�f�������擾����
	float							 GetSpeed()					const { return m_speed; }
	//	��UP��I�񂾁H
	bool							 ChoosePowerUP()			const { return m_powerUP; }
	//	���xUP��I�񂾁H
	bool							 ChooseSpeedUP()			const { return m_speedUP; }
	//	�̗�UP��I�񂾁H
	bool							 ChooseHealthUP()			const { return m_healthUP; }
	//	�U�鑬�xUP��I�񂾁H
	bool							 ChooseSwingSpeedUP()		const { return m_swingSpeedUP; }
	//	�_���[�W���󂯂����H
	bool							 IsDamege()					const { return m_isDamege; }
	//	���G���Ԃ��H
	bool							 IsInvincible()				const { return m_isInvincible; }
	//	�̗͂��[���ɂ���
	void HealthZero();
	//	���G��Ԃ�ݒ肷��
	void SetInvincible(const bool& flag);
	//	�_���[�W��Ԃ̐ݒ肷��
	void SetDamegeCondition(const bool& flag);
	//	�_���[�W��ݒ肷��
	void SetDamege(const int& damege);
	//	�Z���N�g�����Ώۂ𑝂₵��
	void SelectedUpStatus(const PostEffect::PostEffectType& effectType);
	//	�̗͂𑝂₷
	void UpMaxHP();
	//	���x�𑝂₷
	void UpSpeed();
	//	�͂��オ��
	void UpPower();
	//	���̐U�鑬�x
	void UpSwingSpeed();
	//	���x�����オ�����I
	void UpLevel();

	//	�萔
public:

	//	�v���C���[�̍ŏ��̃��x��
	static const int						  FIRST_LEVEL;
	//	�v���C���[�̗�
	static const int						  FIRST_POWER;
	//	�������x
	static const float						  FIRST_SPEED;
	//	�񕜂���l
	static const int						  RECOVERY_VALUE;
	//	���G����
	static const float						  INVINCIBLE_TIME;
	//	�p���[�A�b�v�^�C��
	static const float						  POWER_UP_TIME;
	//	�񕜎���
	static const float						  RECOVERY_TIME;

	//	�ϐ�
private:

	//	�v���C���[�̌o���l���Ǘ�
	std::unique_ptr<PlayerExperiencePoint>			 m_playerEP;
	//	�v���C���[
	Player*											 m_player;
	//	���x��
	int												 m_level;
	//	�̗͂̍ő�l
	int												 m_maxHealth;
	//	�̗�
	int												 m_health;
	//	�v���C���[�̍U����
	int												 m_power;
	//	�ꎞ�I�ȍU���E�̏��
	int												 m_attckPower;
	//	���G���Ԃ��H
	float											 m_invincibleTime;
	//	�񕜂��\�ɂȂ�܂ł̎���	
	float											 m_lifeRerecoveryTime;
	//	�p���[�A�b�v�p������
	float											 m_powerUPTime;
	//	���x
	float											 m_speed;
	//	�񕜒����H
	bool											 m_isRecovery;
	//	�p���[�A�b�v��
	bool											 m_isPowerUP;
	//	�̗͂��オ�����I
	bool											 m_healthUP;
	//	���x���オ�����I
	bool											 m_speedUP;
	//	�U�鑬�x���オ�����I
	bool											 m_swingSpeedUP;
	//	�͂����オ�����I
	bool											 m_powerUP;
	//	�_���[�W���󂯂��I	
	bool											 m_isDamege;
	//	���G���Ԃ��H
	bool											 m_isInvincible;

	//	�֐�
public:

	//	�R���X�g���N�^
	PlayerStatus(Player* player, const int& health);
	//	�f�X�g���N�^
	~PlayerStatus();
	//	����������
	void Initialize();
	//	�X�V����
	void Update(const DX::StepTimer& timer);
	// �v���C���[���p���[�A�b�v�A�C�e�����擾����
	void GetPowerUPItem();
	// �v���C���[���񕜃A�C�e�����擾����
	void GetRecoveryItem();

	//	���ߍ��݊֐�
private:

	//	�񕜂��s��
	void Recovery(const DX::StepTimer& timer);
	//	�p���[�A�b�v��Ԃ̐������m�F����
	void CheckPowerUP(const DX::StepTimer& timer);
	//	���G���ǂ����m�F����
	void CheckInvincibility(const DX::StepTimer& timer);
};