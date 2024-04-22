//
//		File Name �F Sord.h
//		Production�F 2023/6/19
//		Author�@�@�F �Γc ����	
//	
#pragma once
#include "../Object.h"

class Player;

class Sord : public Object
{
	//	�A�N�Z�T
public:

	// ����̃R���C�_�[�擾
	inline Collision::Shape::Capsule GetWeponCapsule() const { return m_sordCapusel; }
	//	�U����
	inline bool IsAttack()							   const { return m_isAttack; }
	//	�U���N�[���^�C���̎擾
	inline float GetAttackCoolTime()				   const { return m_attackCoolTime; }
	//	�U�鑬�x�̏オ��
	void UpSwingSpeed();

	//	�萔
public:

	//	���̗����鑬�x
	static const DirectX::SimpleMath::Vector3 SORD_FALL_SPEED;
	//	�����]�������
	static const DirectX::SimpleMath::Vector3 SORD_ROLL_DIRECTION;
	//	�����̎n��
	static const DirectX::SimpleMath::Vector3 SEGMENT_LENGTH_START;
	//	�����̏I���
	static const DirectX::SimpleMath::Vector3 SEGMENT_LENGTH_END;
	//	���̃I�t�Z�b�g�ʒu
	static const DirectX::SimpleMath::Vector3 SORD_OFFSET_POSITION;
	//	�I�t�Z�b�g�p�x
	static const float						  OFFSET_ANGLE;
	//	���킪�U�������鎞�̊p�x
	static const float						  SWING_ANGLE;
	//	�U�鑬�x
	static const float						  SWING_SPEED;
	//	���x���A�b�v���̏オ�鑬�x
	static const float						  SWING_SPEED_UP_VALUE;
	//	�U��������x
	static const float						  TURN_SPEED;
	//	���̔��a
	static const float						  SPHERE_RADIUS;
	//	�U���̎���					  
	static const float						  ATTACK_TIME;
	//	�U����̎���					  
	static const float						  ATTACK_AFTER_TIME;
	//	�U����̃N�[���^�C��
	static const float						  ATTACK_COOL_TIME;
	//	���̒n�ʂ̈ʒu
	static const float						  GROUND_SORD_POSITION;
	//	����U��I���Ď��ɐU���܂ł̎���				  
	static const float						  SWING_COOLTIME;
	//	����U����ڂ�U���\����				  
	static const float						  SWING_SECOND_CHANCE;

	//	�ϐ�
private:

	//	���̃��f��
	DirectX::Model* m_sordModel;
	//	��]�p
	DirectX::SimpleMath::Quaternion m_slashRotate;
	//	��]�̃I�t�Z�b�g
	DirectX::SimpleMath::Quaternion m_offsetRotate;
	//	�}�g���b�N�X
	DirectX::SimpleMath::Matrix		m_sordMatrix;
	//	�e
	Player*							m_parent;
	//	�U���̊p�x
	float							m_slashAngle;
	//	�ڕW�l
	float							m_objective;
	//	�U���̃N�[���^�C��
	float							m_attackTime;
	//	�U����̃N�[���^�C��
	float							m_attackCoolTime;
	//	�U����̃N�[���^�C����Z������
	float							m_shortAttackTime;
	//	�U���t���O
	bool							m_isAttack;
	//	�U����̃N�[���^�C������
	bool							m_isAttackCoolTime;
	//	���ڂ̍U��
	bool							m_secondAttack;
	//	���̃J�v�Z���̓����蔻��
	Collision::Shape::Capsule		m_sordCapusel;

	//	�֐�
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="parent">�e</param>
	Sord(Player* parent);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Sord();

	/// <summary>
	///	����������
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="timer">�^�C�}�[</param>
	void Update(const DX::StepTimer& timer) override;

	/// <summary>
	/// �`�揈��
	/// </summary>
	/// <param name="view">�r���[</param>
	/// <param name="proj">�v���W�F�N�V����</param>
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj) override;

	/// <summary>
	///	�I������
	/// </summary>
	void Finalize() override;

	/// <summary>
	/// �f�o�C�X�ˑ��̃��\�[�X�̍쐬
	/// </summary>
	void CreateDeviceDependentResources();

	/// <summary>
	/// ���̎��S���̃A�j���[�V����
	/// </summary>
	void SordDeathAniamtion();

	//	���ߍ��݊֐�
private:

	//	 �U��
	void Attack(const DX::StepTimer& timer);
	//	�U�����������̂��ړ�
	void AttackLerp();
	//	�����蔻����X�V
	void UpdateColison();
	//	���̉�]�p���X�V����
	void UpdateSordLerp();
	//	 �U����U��ŏ��̏����𖞂����Ă��邩
	bool ShouldSwingStartFlag();
	//	 �U����U����ڂ̏����𖞂����Ă��邩
	bool ShouldSwingSecondFlag();
};