//
//		File Name �F EnemyLeg.h
//		Production�F 2023/11/12
//		Author�@�@�F �Γc ����	
//	
#pragma 
#include "../Object.h"

class Enemy;

class EnemyLeg final : public Object
{
	//	�ϐ�
private:
	//	�G���f��
	DirectX::Model*								 m_enemyModel;
	//	�e
	Enemy*										 m_parent;

	//	�֐�
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="enemy">���W</param>
	/// <param name="model">���f��</param>
	EnemyLeg(Enemy* enemy, DirectX::Model* model);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~EnemyLeg();

	/// <summary>
	/// ����������
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="timer">�^�C�}�[</param>
	/// <param name="rollAngleSpeed">�r����鑬�x/param>
	void RollLeg(const DX::StepTimer& timer, const float& rollAngleSpeed);

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
};