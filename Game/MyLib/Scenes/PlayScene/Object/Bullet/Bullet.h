//
//		File Name �F Bullet.h
//		Production�F 2023/7/02
//		Author�@�@�F �Γc ����
//
#pragma once
#include "../Object.h"
#include "BulletFactroy.h"

class OwnerID;

class Bullet : public Object
{
	//	�萔
public:

	//	�p���x
	static const float						  SPEED;
	static const DirectX::SimpleMath::Vector3 ENEMY_SPEED;
	static const DirectX::SimpleMath::Vector3 BOSS_SPEED;
	static const DirectX::SimpleMath::Vector3 REF_SPEED;
	//	�����蔻��̑傫��
	static const float BULLET_RADIUS;
	static const float BOSS_BULLET_RADIUS;

private:

	//	�v���~�e�B�u�o�b�`
	std::unique_ptr<DirectX::GeometricPrimitive> m_primitive;
	//	���x
	DirectX::SimpleMath::Vector3				 m_velocity;
	//	�F
	DirectX::SimpleMath::Color					 m_color;
	//	�傫��
	float										 m_scale;
	//	�g�p���
	bool										 m_used;
	//	���˒�
	bool										 m_isRefrect;
	//	���L��
	int											 m_ownerID;
	//	��
	int											 m_power;
	//	���˃J�E���g
	int											 m_refCount;
	//	�����蔻��
	Collision::Shape::Sphere					 m_bulletSphere;

public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="ownerID">�I�[�i�[</param>
	/// <param name="position">���W</param>
	/// <param name="rotate">��]�p</param>
	/// <param name="color">�F</param>
	/// <param name="power">��</param>
	/// <param name="scale">�傫��</param>
	/// <param name="used">�g�p���</param>
	Bullet(
		BulletFactory::OwnerID  ownerID,
		const DirectX::SimpleMath::Vector3& position, 
		const DirectX::SimpleMath::Quaternion& rotate,
		const DirectX::SimpleMath::Color& color,
		int power,
		float scale,
		bool used
		);

	~Bullet();

	//	�֐�
public:

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

	//	�g�p��Ԃ��擾����
	inline bool IsUsed()							  const	 { return m_used; }
	//	���L�҂��擾
	inline int GetOwner()							  const	 { return m_ownerID; }
	//	�͂��擾����
	inline int GetPower()							  const	 { return m_power; }
	//	�����蔻����擾�����
	inline Collision::Shape::Sphere GetSphere()		  const	 { return m_bulletSphere; }
	//	���ˏ�Ԃ��擾
	inline bool	IsReslect()							  const	 { return m_isRefrect; }
	//	�g�p��Ԃ�ݒ肷��
	void SetUsed(bool used);
	//	����
	void Refrection(const DirectX::SimpleMath::Vector3& position);

	//	���ߍ��݊֐�
private:
	void PreInitialize();
	void CreateDeviceDependentResources();

	DirectX::SimpleMath::Vector3 ShotBullet();
};

