//
//		File Name �F Enemy.h
//		Production�F 2023/11/12
//		Author�@�@�F �Γc ����	
//	
#pragma once
#include "../Object.h"
#include "Game/MyLib/GameDatas/EnemyHeart.h"

class Object;

class Enemy : public Object
{
	//	�A�N�Z�T
public:

	//	�����蔻��̒ǉ�
	void AddColisionEnemy
	(
		const Collision::Shape::Sphere& colisionSpere, 
		const Collision::Shape::Sphere& searchSpere, 
		const Collision::Shape::Sphere& abilitySpere
	);
	//	�����蔻��̎擾����
	inline  Collision::Shape::Sphere	 GetSphereCollision()	const { return m_sphere; }
	//	���G�͈͂��擾����
	inline  Collision::Shape::Sphere	 GetSearchCollision()	const { return m_searchSphere; }
	//	������ʔ͈͂��擾����
	inline  Collision::Shape::Sphere	 GetAbilityColision()	const { return m_abilitySphere; }
	//	�ڕW���W�̎擾
	inline  DirectX::SimpleMath::Vector3 GetTargetPosition()	const { return m_targetPos; }
	//	���G��Ԃ��H
	inline  bool						 IsInvincible()			const { return m_isInvincible; }
	//	�w�C�g����?
	inline	bool						 IsHate()				const { return m_isHate; }
	//	���S�������H
	inline	bool						 IsDead()				const { return m_isAlive; }
	//	�����Ă��邩
	inline	bool						 IsWalk()				const { return m_isWalk; }
	//	������ʂ��擾����
	inline	bool						 InAbility()			const { return m_inAbility; }
	//	���S�A�j���[�V���������H
	inline	bool						 IsDeadAnimation()		const { return m_deadAnimation; }
	//	�̗͂��擾
	inline  int							 GetHealth()			const { return m_helath; }
	//	�ő�̗͂��擾
	inline  int							 GetMAXHealth()			const { return m_maxHelath; }
	//	�͂��擾
	inline	int							 GetPower()				const { return m_power; }
	//	�G�̌o���l���擾����
	inline	int							 GetEXP()				const { return m_enemyEXPoint; }

	//	���G��Ԃ�ݒ�
	void SetInvincibleFlag(bool flag);
	//	�ڕW���W�̐ݒ肷��
	void SetTargetPosition(const DirectX::SimpleMath::Vector3& pos);
	//	�w�C�g��Ԃ�ݒ肷��
	void SetHate(const bool& flag);
	//	����Z�\�͈͂ɓ��������̃t���O�̐ݒ�
	void SetInAbility(const bool& flag);
	//	�����Ă��邩
	void SetWalk(const bool& flag);
	//	�w�C�g���[�h�ɂ���
	void SetHateMode();
	//	���G���Ԃ����Z�b�g����
	void ResetInvincibleTime();
	//	���S�A�j���[�V�����̊J�n
	void StartDeathAnimation();
	//	���S���m��
	void DeathObject();

	//	�萔
public:

	//	��������
	static const float	RANDOM_TIME;
	//	�ǂ̈ʒu
	static const float	WALL_PLACE;
	//	����
	static const float	ENEMT_TOUCH_REACTION;
	//	���G����
	static const float	INVINCIBLE_TIME;

	//	�񋓌^
public:

	// ����
	enum class Direction
	{
		//	������
		LEFT,
		//	�����
		TOP,
		//	�E����
		RIGHT,
		//	������
		BOTTOM,
		//	�������Ȃ�
		NONE
	};

	//	�ϐ�
private:

	//	�v���~�e�B�u�o�b�`
	std::unique_ptr<DirectX::GeometricPrimitive> m_primitive;
	//	�n�[�g
	std::unique_ptr<EnemyHeart>					 m_heart;
	//	�Ǐ]�^�[�Q�b�g���W
	DirectX::SimpleMath::Vector3				 m_targetPos;
	//	�����蔻��
	Collision::Shape::Sphere					 m_sphere;
	//	����̍��G�͈�
	Collision::Shape::Sphere					 m_searchSphere;
	//	����̔��ˉ\�͈�
	Collision::Shape::Sphere					 m_abilitySphere;
	//	�̗�
	int											 m_helath;
	//	�ő�̗͒l
	int											 m_maxHelath;
	//	��
	int											 m_power;
	//	�G�̌o���l
	int											 m_enemyEXPoint;	
	//	���G����
	float										 m_invincibleTime;
	//	�����_���ɓ���ւ��܂ł̎���
	float										 m_randomTime;
	//	�p�j�s���Ŏg�p�������
	float										 m_wanderOrientation;
	//	�w�C�g����
	bool										 m_isHate;
	//	���G����
	bool										 m_isInvincible;
	//	������ʔ͈͂�
	bool										 m_inAbility;
	//	����ł��邩�H
	bool										 m_isAlive;
	//	
	bool										 m_isWalk;
	//	���S�A�j���[�V����
	bool										 m_deadAnimation;
	//	�G�̌���
	Direction									 m_direction;

	//	�֐�
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="position">���W</param>
	/// <param name="helath">�̗�</param>
	/// <param name="power">��</param>
	/// <param name="enemyEXPoint">�o���l</param>
	Enemy(const DirectX::SimpleMath::Vector3& position, const int& helath , const int& power , const int& enemyEXPoint);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Enemy();

	/// <summary>
	/// ����������
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
	/// <param name="view">�r���[�v���W�F�N�V����</param>
	/// <param name="proj">�r���[</param>
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj) override;

	/// <summary>
	/// �ۉe���쐬����
	/// </summary>
	void CreateShadow(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj, const float& shadowScale);

	/// <summary>
	/// �I������
	/// </summary>
	void Finalize() override;

	/// <summary>
	/// �����ňړ����s��
	/// </summary>
	/// <param name="timer">�^�C�}�[</param>
	void AutoMove(const DX::StepTimer& timer, const float& speed, const float& lookBackSpeed);


	/// <summary>
	/// �ڕW�̌������擾����
	/// </summary>
	/// <returns>����</returns>
	DirectX::SimpleMath::Quaternion GetObjectiveRotate();

	/// <summary>
	/// �G���m�̐ڐG�ŋ����𗣂�
	/// </summary>
	/// <param name="direction"></param>
	void HitEnemyMove(const DirectX::SimpleMath::Vector3& direction);

	/// <summary>
	/// �_���[�W�^����
	/// </summary>
	/// <param name="damege">�_���[�W</param>
	void Damege(int damege);
	
	/// <summary>
	///  ���[���h���x��
	/// </summary>
	/// <param name="health">���x��</param>
	/// <param name="power">�p���[</param>
	/// <param name="level">���x��</param>
	void StatusUP(const int& health, const int& power, const int& level);

	//	�������z�֐�
public:

	/// <summary>
	/// �v���C���[�̏Փˎ�
	/// </summary>
	/// <param name="direction">����</param>
	/// <param name="nockBack"></param>
	virtual void HitPlayer(const DirectX::SimpleMath::Vector3& direction, const float& nockBack) 
	{
		UNREFERENCED_PARAMETER(direction);
		UNREFERENCED_PARAMETER(nockBack);
	};

	/// <summary>
	/// �A�N�V������Ԃ��s���邩�m�F����
	/// </summary>
	/// <returns></returns>
	virtual bool IsRedyAbility() { return false; }

	/// <summary>
	/// ������ʂ�ݒ肷��
	/// </summary>
	/// <param name="flag"></param>
	virtual void SetAbility(const bool& flag) { UNREFERENCED_PARAMETER(flag); }

	/// <summary>
	/// �X�^����Ԃɂ���
	/// </summary>
	virtual void SwoonMode() {};

	//	���ߍ��݊֐�
private:

	//	�����_���ȕ����Ɍ�����ς���
	void RandomMoveDirection(const DX::StepTimer& timer, const float& speed);
	// �U�����m�F�����疳�G
	void Hit(const DX::StepTimer& timer);
	//	�����蔻����X�V����
	void UpdateColision();
	//	�G���[���m�F����
	void ErrorCheck();
	// �����Ă��邩�H	
	void IsAlive();
};