//
//		File Name �F SwingSordEffect.cpp
//		Production�F 2023/1/12
//		Author�@�@�F �Γc ����
// 
//		���������ۂ̃G�t�F�N�g�̕`����s���N���X
//
#include "pch.h"
#include "EnemyHeart.h"
#include "Game/MyLib/Scenes/PlayScene/Object/Enemy/Enemy.h"

const float EnemyHeart::RENDER_TIME = 22.0f;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="enemy">�G</param>
EnemyHeart::EnemyHeart(Enemy* enemy)
	:
	m_enemy(enemy),
	m_coverHeartTexture(nullptr),
	m_heartTexture(nullptr),
	m_size(1.0f),
	m_elapsedTime(0.0f)
{
	//	�X�N���[�����\�[�X
	m_screen = MyLib::ScreenResources::GetInstance();
	//	�o�b�`�G�t�F�N�g
	m_batchEffect = m_screen->GetBasicEffect();
	//	�C���v�b�g���C�A�E�g
	m_inputLayout = m_screen->GetInputLayout();
	// �v���~�e�B�u�o�b�`�̍쐬
	m_primitiveBatch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>>(m_screen->GetDeviceContext());
	//	�n�[�g�̉摜
	m_heartTexture = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"EnemyHeart");
	//	�n�[�g�̔w�i�摜
	m_coverHeartTexture = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"EnemyCoverHeart");
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
EnemyHeart::~EnemyHeart()
{
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void EnemyHeart::Update(const DX::StepTimer& timer)
{
	if (m_enemy->IsDeadAnimation())	return;
	//	�o�ߎ��Ԃ�����
	m_elapsedTime -= static_cast<float>(timer.GetElapsedSeconds());

	float maxHealth =static_cast<float>(m_enemy->GetMAXHealth());
	float health =static_cast<float>(m_enemy->GetHealth());

	m_size = maxHealth / health;
}
/// <summary>
/// �`�揈��
/// </summary>
/// <param name="view">�r���[</param>
/// <param name="proj">�v���W�F�N�V����</param>
void EnemyHeart::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	if (m_enemy->IsDeadAnimation())	return;
	//	�R���e�L�X�g
	auto context = m_screen->GetDeviceContext();
	//	�n�[�g�̉摜
	m_heartTexture = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"EnemyHeart");
	//	�n�[�g�̔w�i�摜
	m_coverHeartTexture = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"EnemyCoverHeart");

	// ���_���
	DirectX::VertexPositionColorTexture vertex[4] =
	{
		DirectX::VertexPositionColorTexture(DirectX::SimpleMath::Vector3( m_size,  0.5f,  m_size),DirectX::SimpleMath::Vector4( 1.0f, 1.0f, 0.0f,  1.0f), DirectX::SimpleMath::Vector2(0.0f, 0.0f)),
		DirectX::VertexPositionColorTexture(DirectX::SimpleMath::Vector3(-m_size,  0.5f,   m_size),DirectX::SimpleMath::Vector4(1.0f, 1.0f, 0.0f,  1.0f), DirectX::SimpleMath::Vector2(1.0f, 0.0f)),
		DirectX::VertexPositionColorTexture(DirectX::SimpleMath::Vector3(-m_size,  0.5f,  -m_size),DirectX::SimpleMath::Vector4(1.0f, 1.0f, 0.0f,  1.0f), DirectX::SimpleMath::Vector2(1.0f, 1.0f)),
		DirectX::VertexPositionColorTexture(DirectX::SimpleMath::Vector3( m_size,  0.5f, -m_size),DirectX::SimpleMath::Vector4( 1.0f, 1.0f, 0.0f,  1.0f), DirectX::SimpleMath::Vector2(0.0f, 1.0f)),
	};


	// ���_���
	DirectX::VertexPositionColorTexture coverVertex[4] =
	{
		DirectX::VertexPositionColorTexture(DirectX::SimpleMath::Vector3(1.0f,  0.5f,   1.0f),DirectX::SimpleMath::Vector4(1.0f, 1.0f, 1.0f,  1.0f), DirectX::SimpleMath::Vector2(0.0f, 0.0f)),
		DirectX::VertexPositionColorTexture(DirectX::SimpleMath::Vector3(-1.0f, 0.5f,   1.0f),DirectX::SimpleMath::Vector4(1.0f, 1.0f, 1.0f,  1.0f), DirectX::SimpleMath::Vector2(1.0f, 0.0f)),
		DirectX::VertexPositionColorTexture(DirectX::SimpleMath::Vector3(-1.0f, 0.5f,  -1.0f),DirectX::SimpleMath::Vector4(1.0f, 1.0f, 1.0f,  1.0f), DirectX::SimpleMath::Vector2(1.0f, 1.0f)),
		DirectX::VertexPositionColorTexture(DirectX::SimpleMath::Vector3(1.0f,  0.5f,  -1.0f),DirectX::SimpleMath::Vector4(1.0f, 1.0f, 1.0f,  1.0f), DirectX::SimpleMath::Vector2(0.0f, 1.0f)),
	};

	// ���Z����
	context->OMSetBlendState(m_screen->GetCommonState()->Additive(), nullptr, 0xFFFFFFFF);
	// �[�x�o�b�t�@�͂Ȃ�
	context->OMSetDepthStencilState(m_screen->GetCommonState()->DepthNone(), 0);
	// �J�����O�͍�����
	context->RSSetState(m_screen->GetCommonState()->CullCounterClockwise());
	//	�`����W
	DirectX::SimpleMath::Vector3 renderPosition = m_enemy->GetPosition();
	//	�G�ɂ���ĕ`��ʒu��ς���
	if (m_enemy->GetType() == Object::ObjectType::BossEnemy) { renderPosition.y = 5.0f; } else { renderPosition.y = 3.0f; }
	//	���[���h
	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::CreateFromQuaternion(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(180.0f)) * 
		DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitX, DirectX::XMConvertToRadians(45.0f))) *
		DirectX::SimpleMath::Matrix::CreateTranslation(renderPosition);

	m_batchEffect->SetWorld(world);
	m_batchEffect->SetView(view);
	m_batchEffect->SetProjection(proj);
	m_batchEffect->Apply(context);
	context->IASetInputLayout(m_inputLayout);

	m_primitiveBatch->Begin();
	m_batchEffect->SetTexture(m_heartTexture.Get());
	m_primitiveBatch->DrawQuad(vertex[0], vertex[1], vertex[2], vertex[3]);
	m_batchEffect->SetTexture(m_coverHeartTexture.Get());
	m_primitiveBatch->DrawQuad(coverVertex[0], coverVertex[1], coverVertex[2], coverVertex[3]);
	m_primitiveBatch->End();
}