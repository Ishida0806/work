//
//		File Name �F EnemyLeg.cpp
//		Production�F 2023/11/12
//		Author�@�@�F �Γc ����	
//	
#include "pch.h"
#include "EnemyLeg.h"
#include "Enemy.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="enemy">���W</param>
/// <param name="model">���f��</param>
EnemyLeg::EnemyLeg(Enemy* enemy, DirectX::Model* model)
	:m_parent(enemy),
	m_enemyModel(model)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
EnemyLeg::~EnemyLeg()
{
}

/// <summary>
///	����������
/// </summary>
void EnemyLeg::Initialize()
{
	
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="timer">�^�C�}�[</param>
/// <param name="rollSpeed">�r����鑬�x/param>
void EnemyLeg::RollLeg(const DX::StepTimer& timer, const float& rollAngleSpeed)
{

	timer;

	if (m_parent->IsWalk() && m_parent->GetType() == ObjectType::NormalEnemy)
	{
		//	�r����
		SetRotate(GetRotate() * DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(-rollAngleSpeed)));
	}
	else if(!m_parent->IsWalk() && m_parent->GetType() == ObjectType::NormalEnemy)
	{
		//	�r����
		SetRotate(DirectX::SimpleMath::Quaternion::Lerp(GetRotate(), DirectX::SimpleMath::Quaternion::Identity, 0.1f));
	}
}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="view">�r���[</param>
/// <param name="proj">�v���W�F�N�V����</param>
void EnemyLeg::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	//	�X�N���[�����\�[�X
	auto screen = MyLib::ScreenResources::GetInstance();
	// �X�P�[���s��
	DirectX::SimpleMath::Matrix scale = DirectX::SimpleMath::Matrix::CreateScale(m_parent->GetScale());
	// �ʒu�s��
	DirectX::SimpleMath::Matrix trans = DirectX::SimpleMath::Matrix::CreateTranslation(m_parent->GetPosition());
	// ��]�s��
	DirectX::SimpleMath::Matrix rotate = DirectX::SimpleMath::Matrix::CreateFromQuaternion(GetRotate() * m_parent->GetRotate());
	// ���[���h�ϊ��s��ɕϊ��i�X�P�[���A��]�A�ʒu�̏��œK�p�j
	DirectX::SimpleMath::Matrix world = scale * rotate * trans;
	// �G�����G��Ԃ܂��͎��S�A�j���[�V�������̏ꍇ�A����ȕ`����s��
	m_enemyModel->Draw(screen->GetDeviceContext(), *screen->GetCommonState(), world, view, proj);
}

/// <summary>
/// �I������
/// </summary>
void EnemyLeg::Finalize()
{
}
