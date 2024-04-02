//
//		File Name �F NormalEnemy.h
//		Production�F 2023/11/12
//		Author�@�@�F �Γc ����	
//	
#pragma once
#include "../Object.h"
#include "Enemy.h"
#include "EnemyLeg.h"

class NormalEnemy : public Enemy
{//	�萔
public:
	//	�e����
	static const float										 ENEMY_SPEED;
	//	�U��������x
	static const float										 LERP_SPEED;
	//	�ǂ̈ʒu
	static const float										 WALL_PLACE;
	//	�G�̒e��
	static const int									 	 ENEMY_BULLETS_NUM;
	//	���ˊԊu
	static const float										 SHOT_TIME;
	//	��������
	static const float										 RANDOM_TIME;
	//	�����ݒ�̗�
	static const int										 FIRST_POWER;
	//	�����ݒ�̗̑�
	static const int										 FIRST_HEALTH;
	//	�m�[�}���̌o���l
	static const int										 NORMAL_EXP;
	//	�e�p�̈����l
	static const float										 SHADOW_ARGUMENT;
	//	�ʏ�̑傫��
	static const DirectX::SimpleMath::Vector3				 DEFAULT_SCALE;
	//	���g�̑傫���̈����l
	static const DirectX::SimpleMath::Vector3				 SCALE_ARGUMENT;
	//	�����蔻��
	static const Collision::Shape::Sphere					 SPERE_COLLISION;
	//	����̍��G�͈�
	static const Collision::Shape::Sphere					 SEARCH_COLLISION;
	//	����̔��ˉ\�͈�
	static const Collision::Shape::Sphere					 SHOT_COLLISION;

	//	�ϐ�
private:
	//	�G���f��
	DirectX::Model*								 m_enemyModel;
	//	�G�̋r
	std::unique_ptr<EnemyLeg>					 m_enemyLeg;
	//	���ˎ��̑傫��
	DirectX::SimpleMath::Vector3				 m_shotAnimationScale;
	//	���ˌ�̃A�j���[�V����
	DirectX::SimpleMath::Vector3				 m_shotAnimationAfterScale;
	//	���ˌ���
	bool										 m_isShot;
	//	���ˌ����ɓ�����
	bool										 m_inShot;
	//	���x��
	int											 m_level;
	//	�e�̑傫��
	float										 m_shadowScale;
	//	���˂܂ł̃C���^�[�o��
	float										 m_shotInterval;
	//	���ɔ��˂���܂ł̎���
	float										 m_shotCoolTime;
	//	�G�̌���
	Direction									 m_direction;
	//	���ʎq
	ObjectType									 m_objType;

	//	�֐�
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="position">���W</param>
	/// <param name="helath">�̗�</param>
	/// <param name="power">��</param>
	/// <param name="level">���x��</param>
	/// <param name="obj">�I�u�W�F�N�g�̃^�C�v</param>
	NormalEnemy(const DirectX::SimpleMath::Vector3& position, const int& helath, const int& power, const int& level, ObjectType	obj);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~NormalEnemy();

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
	/// <param name="view">�r���[</param>
	/// <param name="proj">�v���W�F�N�V����</param>
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj) override;

	/// <summary>
	/// �I������
	/// </summary>
	void Finalize() override;

	//	�A�N�Z�T
public:	

	/// <summary>
	/// �A�N�V������Ԃ��s���邩�m�F����
	/// </summary>
	/// <returns></returns>
	bool IsRedyAbility() override { return m_isShot; }

	/// <summary>
	/// ������ʂ�ݒ肷��
	/// </summary>
	/// <param name="flag"></param>
	void SetAbility(const bool& flag) override;

	//	���ߍ��݊֐�
private:
	//	��������
	void IsAlive();
	//	�ǔ����[�h
	void HateMode(const DX::StepTimer& timer);
};