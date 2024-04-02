//
//		File Name �F BulletManager.h
//		Production�F 2023/7/02
//		Author�@�@�F �Γc ����
//
#pragma once

class Bullet;
class Enemy;

class BulletManager
{
	//	�A�N�Z�T
public:

	//	�e���擾����
	inline std::vector<std::unique_ptr<Bullet>>& GetBullet()		noexcept { return m_bullets; };

	//	�萔
public:

	//	�G�̒e�̗�					 
	static const int						  ENEMY_BULLET_POWER;
	//	�{�X�̒e�̗�
	static const int						  BOSS_BULLET_POWER;
	//	�{�X�̒e�̑傫��
	static const float						  BOSS_BULLET_SCLAE;
	//	�G�̒e�̑傫��
	static const float						  ENEMY_BULLET_SCLAE;

	//	�ϐ�
private:

	//	�{�X�̃|�C���^�[
	std::vector<std::shared_ptr<Enemy>>&	   m_enemys;
	//	�C�e�z��
	std::vector<std::unique_ptr<Bullet>>	   m_bullets;

	//	�ϐ�
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="enemy">�G����</param>
	BulletManager(std::vector<std::shared_ptr<Enemy>>& enemy);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~BulletManager();

	/// <summary>
	/// ����������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="timer">�^�C�}�[</param>
	void Update(const DX::StepTimer& timer);

	/// <summary>
	/// �`�揈��
	/// </summary>
	/// <param name="view">�r���[</param>
	/// <param name="proj">�v���W�F�N�V����</param>
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj);


	//	�v���C�x�[�g�֐�
private:

	/// <summary>
	/// �ʏ�̒e���X�V�X�V����
	/// </summary>
	/// <param name="timer">�^�C�}�[</param>
	void UpdateNormalBullet(const DX::StepTimer& timer);

	/// <summary>
	/// �G�̒e�����𔭎˂���
	/// </summary>
	void ShotEnemyBullets();

	/// <summary>
	/// �{�X�̒e�����𔭎˂���
	/// </summary>
	void ShotBossBullets();
	
	
};