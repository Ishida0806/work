//
//		File Name �F TackleEnemy.h
//		Production�F 2023/11/12
//		Author�@�@�F �Γc ����	
//	
#pragma once

#include "../Object.h"
#include "Enemy.h"

class TackleEnemy : public Enemy
{
	//	�A�N�Z�T
public:

	/// <summary>
	/// �A�N�V������Ԃ��s���邩�m�F����
	/// </summary>
	/// <returns></returns>
	bool IsRedyAbility() override { return m_isTackle; }

	//	�萔
public:

	//	�������x
	static const float									 	 ENEMY_SPEED;
	//	�U���������
	static const float										 LOOK_BACK_SPEED;
	//	�ˌ����x
	static const float										 ENEMY_TACLE_SPEED;
	//	�ˌ���~�܂�ʒu
	static const float										 TACKLE_STOP_DISTANCE;
	//	�G�̒e��
	static const int										 ENEMY_BULLETS_NUM;
	//	�Ƃǂ܂鎞��
	static const float										 ALIVE_TIME;
	//	�ˌ��\�܂ł̎���
	static const float										 TACKLE_ENABLED_TIME;
	//	�e�p�̈����l
	static const float										 SHADOW_ARGUMENT;
	//	�ˌ�����
	static const float										 TACKLE_DISTANCE;
	//	�X�^���^�C��
	static const float										 SWOON_TIME;
	//	�^�b�N���̌o���l
	static const int										 TACKLE_EXP;
	//	�����ݒ�̗�
	static const int										 FIRST_POWER;
	//	�����ݒ�̗̑�
	static const int										 FIRST_HEALTH;
	//	���g�̑傫���̈����l
	static const DirectX::SimpleMath::Vector3				 SCALE_ARGUMENT;
	//	�ʏ�̑傫��
	static const DirectX::SimpleMath::Vector3				 DEFAULT_SCALE;
	//	�����蔻��
	static const Collision::Shape::Sphere					 SPERE_COLLISION;
	//	����̍��G�͈�
	static const Collision::Shape::Sphere					 SEARCH_COLLISION;
	//	����̔��ˉ\�͈�
	static const Collision::Shape::Sphere					 TACKLE_COLLISION;
	//	�ˌ����̉��F
	static const DirectX::SimpleMath::Color					 TACKLE_PREDICTION_YELLOW;
	//	�ˌ����̐ԐF
	static const DirectX::SimpleMath::Color					 TACKLE_PREDICTION_RED;

	//	�\����
public:
	

	//	�^�b�N���̋������������
	enum class TackleState
	{
		// �^�b�N�����J�n����Ă��Ȃ����
		IDLE,        
		// �^�b�N�����i�s���̏��
		ACTIVE,       
		// �^�b�N�����I���������
		FINISHED,   

		//	�X�^��
		SWOON
	};

	//	�ϐ�
private:

	//	�G���f��
	DirectX::Model* m_enemyModel;
	//	�X�^����Ԃ̉�]
	DirectX::SimpleMath::Quaternion				 m_swoonRotate;
	//	�ڕW�̉�]�p
	DirectX::SimpleMath::Quaternion				 m_objectiveRotate;
	//	�v���~�e�B�u�o�b�`�l�p
	std::unique_ptr<DirectX::GeometricPrimitive> m_primitiveBox;
	//	�ˌ��^�[�Q�b�g���W
	DirectX::SimpleMath::Vector3				 m_objectivePosition;
	//	�ˌ��̎��̑傫��
	DirectX::SimpleMath::Vector3				 m_tackleScale;
	//	���x��
	int											 m_level;
	//	�ːi��
	bool										 m_isTackle;
	//	�ːi�N�[���^�C��
	bool										 m_tackleCoolTime;
	//	�ˌ����s��
	bool										 m_tackleExcute;
	//	�e�̑傫��
	float										 m_shadowScale;
	//	�ˌ��܂ł̃C���^�[�o��
	float										 m_tackleInterval;
	//	�ˌ���̂��̏�ɂƂǂ܂鎞��
	float										 m_tackledStayTime;
	//	�ˌ����̎���
	float										 m_tackleAssaultTime;
	//	�X�^�����
	float										 m_swoonTime;
	//	�ˌ��̏��
	TackleState									 m_tackleState;
	//	���ʎq
	ObjectType									 m_objType;

	//	�֐�
public:
	//	�R���X�g���N�^
	TackleEnemy(const DirectX::SimpleMath::Vector3& position, int helath, const int& power, int level, ObjectType obj);
	//	�f�X�g���N�^
	~TackleEnemy();
	//	������
	void Initialize() override;
	//	�X�V
	void Update(const DX::StepTimer& timer) override;
	//	�`��
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj) override;
	//	�I������
	void Finalize() override;

	/// <summary>
	/// �v���C���[�q�b�g
	/// </summary>
	/// <param name="direction"></param>
	/// <param name="nockBack"></param>
	void HitPlayer(const DirectX::SimpleMath::Vector3& direction, const float& nockBack) override;

	/// <summary>
	/// �X�^����Ԃɂ���
	/// </summary>
	void SwoonMode() override;

	//	���ߍ��݊֐�
private:

	//	��������
	void IsAlive();
	//	�w�C�g���[�h
	void HateMode(const DX::StepTimer& timer) ;
	//	�^�b�N������O�̏�����
	void PreTackleInitialize();
	//	�^�b�N�����~�߂����
	bool ShouldStopTackle();
	//	�X�^�����
	bool Swoon(const DX::StepTimer& timer);
	//	�\����
	void ComingTackle(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj);
	//	�^�b�N���̊J�n�ʒu
	DirectX::SimpleMath::Vector3 StartTackle(const DirectX::SimpleMath::Vector3& position, const float& speed);
};