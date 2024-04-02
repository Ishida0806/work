//
//		File Name �F FallingCherryBlossoms.cpp
//		Production�F 2023/2/06
//		Author�@�@�F �Γc ����	
// 
//		�������̉Ԑ���̎���
//	
#include "pch.h"
#include "FallingCherryBlossoms.h"

//	���g�̃����_���ȍ��W
const float FallingCherryBlossoms::RANDOM_MINE_POSITION = 7.0f;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="player">�v���C���[</param>
FallingCherryBlossoms::FallingCherryBlossoms(Player* player)
	:
	m_player(player),
	m_randamDirection(0.0f),
	m_randamSpawnYPosition(0.0f)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
FallingCherryBlossoms::~FallingCherryBlossoms()
{
}

/// <summary>
/// ����������
/// </summary>
void FallingCherryBlossoms::Initialize()
{
	//	�v���~�e�B�u�o�b�`�̍쐬	
	m_primitive = DirectX::GeometricPrimitive::CreateCube(MyLib::ScreenResources::GetInstance()->GetDeviceContext());
	//	Y���W�̏o���ʒu�����߂�
	m_randamSpawnYPosition = Utility::CreateRandom(5.0f, 10.0f);
	//	�v���C���[�̍��W�t�߂ɐݒ肷��
	DirectX::SimpleMath::Vector3 randomPosition = DirectX::SimpleMath::Vector3(Utility::CreateRandom(-RANDOM_MINE_POSITION, RANDOM_MINE_POSITION), m_randamSpawnYPosition, Utility::CreateRandom(-RANDOM_MINE_POSITION, RANDOM_MINE_POSITION));
	//	���W�̐ݒ�
	SetPosition(m_player->GetPosition() + randomPosition);
	//	���؂���������
	SetScale(DirectX::SimpleMath::Vector3(0.25f, 0.25f, 0.001f));
	//	���������߂�
	m_randamDirection = Utility::CreateRandom(-1.0f, 1.0f);
	//	�F�������_����
	m_colors = DirectX::SimpleMath::Color(1.0f, Utility::CreateRandom(0.0f, 0.3f), Utility::CreateRandom(0.0f, 0.5f));
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void FallingCherryBlossoms::Update(const DX::StepTimer& timer)
{
	//	�o�ߎ��Ԃ�
	float elapsedTime = static_cast<float>(timer.GetElapsedSeconds());
	//	���W�̐ݒ肷��
	DirectX::SimpleMath::Vector3 position = GetPosition();
	//	�n�ʂɖ����ꂽ���ɖ߂�
	if (position.y < -1.0f) { position.y = m_randamSpawnYPosition; } else { position.y -= 2.0f * elapsedTime; }
	//	��]���擾
	DirectX::SimpleMath::Quaternion rotate = GetRotate();
	//	�����_���ɉ�]������
	rotate *= DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
		(3.0f * elapsedTime) * m_randamDirection, 
		(2.0f * elapsedTime) * m_randamDirection,
		(2.0f* elapsedTime)  * m_randamDirection
	);
	//	��]�̐ݒ�
	SetRotate(rotate);
	//	���W�̐ݒ�
	SetPosition(position);
}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="view">�r���[</param>
/// <param name="proj">�v���W�F�N�V����</param>
void FallingCherryBlossoms::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	//	�e���ړ�
	DirectX::SimpleMath::Matrix scale  = DirectX::SimpleMath::Matrix::CreateScale(GetScale());
	DirectX::SimpleMath::Matrix trans  = DirectX::SimpleMath::Matrix::CreateTranslation(GetPosition());
	DirectX::SimpleMath::Matrix rotate = DirectX::SimpleMath::Matrix::CreateFromQuaternion(GetRotate());

	DirectX::SimpleMath::Matrix world = scale * rotate * trans;

	//	�v���~�e�B�u�o�b�`�̕`��
	m_primitive->Draw(world, view, proj, m_colors);
}

/// <summary>
/// �I������
/// </summary>
void FallingCherryBlossoms::Finalize()
{
}
