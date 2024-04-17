//
//		File Name �F BossEnemy.h
//		Production�F 2023/11/12
//		Author�@�@�F �Γc ����	
//	
#pragma once
#include "Enemy.h"
#include "../Bullet/Bullet.h"

class BossEnemy : public Enemy
{//	�萔
public:
	//	��������e��
	static const int										 BOSS_BULLETS_NUM;
	//	�ړ����x
	static const float										 BOSS_SPEED;
	//	��鑬��
	static const float										 LERP_SPEED;
	//	�ǂ̂���ʒu
	static const float										 WALL_PLACE;
	//	���˂̃C���^�[�o��
	static const float										 SHOT_TIME;
	//	�{�X�̌o���l
	static const int										 BOSS_EXP;
	//	�e�̑傫��
	static const float										 SHADOW_SCALE;
	//	���S���̎��g�̑傫����������Ă����傫��
	static const float									     SCALE_ARGUMENT;
	//	���S���̉e�̑傫����������Ă����傫��
	static const float										 SHADOW_ARGUMENT;
	//	�����蔻��
	static const Collision::Shape::Sphere					 SPERE_COLLISION;
	//	����̍��G�͈�
	static const Collision::Shape::Sphere					 SEARCH_COLLISION;
	//	����̔��ˉ\�͈�
	static const Collision::Shape::Sphere					 SHOT_COLLISION;

private:
	//	�G���f��
	DirectX::Model*								 m_bossModel;
	//	���˃t���O
	bool										 m_isShot;
	//	���G��Ԃɓ��������H
	bool										 m_isSeartch;
	//	���x��
	int											 m_level;
	//	�傫��
	float										 m_scale;
	//	���˂܂ł̃C���^�[�o��
	float										 m_shotInterval;
	//	�e�̑傫��
	float										 m_shadowScale;
	//	�����_���ɓ���ւ��܂ł̎���
	float										 m_randomTime;
	//	�G�̌���
	Direction									 m_direction;
	//	���ʎq
	ObjectType 									 m_objType;

	//	�֐�
public:
	//	�R���X�g���N�^
	BossEnemy(const DirectX::SimpleMath::Vector3& position, const int& helath, const int& power, const int& level, ObjectType obj);
	//	�f�X�g���N�^
	~BossEnemy();

	void Initialize() override;
	void Update(const DX::StepTimer& timer) override;
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj) override;
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
	//	�����Ă��邩
	void IsAlive();
	//	�ǔ����[�h
	void HateMode(const DX::StepTimer& timer);
};