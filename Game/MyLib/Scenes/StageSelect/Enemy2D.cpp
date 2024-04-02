//
//		File Name �F Enemy2D.cpp
//		Production�F 2023/10/25
//		Author�@�@�F �Γc ����	
// 
//		2d�G�̕`��E�X�V���s��
// 
#include "pch.h"
#include "Enemy2D.h"

//	������
const int Enemy2D::GENERATION_ENEMY2D = 35;
//	�摜�̐^��
const DirectX::SimpleMath::Vector2 Enemy2D::ORIGIN_ENEMY2D_TEXTURE = DirectX::SimpleMath::Vector2(112.0f, 91.5f);

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="texture">�摜</param>
/// <param name="position">���W</param>
Enemy2D::Enemy2D(ID3D11ShaderResourceView* texture, const DirectX::SimpleMath::Vector2& position)
	:m_enemy2DTexture(texture),
	m_enemy2DPos(position),
	m_randomDirection(0),
	m_angle(0.0f),
	m_randomScale(0.0f),
	m_randomSpeed(0.0f),
	m_randomShake(0.0f)
{
	//	�h������
	if (rand() % 2 == 0)
	{
		m_randomDirection = -1;
	}
	else 
	{
		m_randomDirection = 1;
	}

	//	�����_���ȑ��x
	m_randomSpeed = Utility::CreateRandom(0.2f, 0.5f);
	//	�����_���ȑ傫��
	m_randomScale = Utility::CreateRandom(0.1f, 0.5f);
	//	�����_���ȗh�ꕝ
	m_randomShake = Utility::CreateRandom(10.0f, 15.0f);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Enemy2D::~Enemy2D()
{
}

/// <summary>
/// ����������
/// </summary>
void Enemy2D::Initialize()
{
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void Enemy2D::Update(const DX::StepTimer& timer)
{
	//	���x�𑫂�
	m_enemy2DPos.y += m_randomSpeed;
	//	�E�ɍ��ɗh�炷
	m_angle = (m_randomShake * m_randomDirection) * sinf(static_cast<float>(timer.GetTotalSeconds()) * 3.0f);
	//	��ʊO�ɍs�������܂Ŗ߂�
	if (m_enemy2DPos.y >= 765.0f)
		m_enemy2DPos.y = -45.0f;
}

/// <summary>
/// �`�悷��
/// </summary>
void Enemy2D::Draw()
{
	//	�X�v���C�g�o�b�`
	DirectX::SpriteBatch* spriteBatch = MyLib::ScreenResources::GetInstance()->GetSpriteBatch();

	//	�`��s��
	spriteBatch->Draw
	(
		m_enemy2DTexture,
		m_enemy2DPos,
		nullptr,
		DirectX::Colors::White,
		DirectX::XMConvertToRadians(m_angle),
		ORIGIN_ENEMY2D_TEXTURE,
		DirectX::SimpleMath::Vector2(m_randomScale, m_randomScale)
	);
}

/// <summary>
/// �f�o�C�X�ˑ��̃��\�[�X�̏�����
/// </summary>
void Enemy2D::CreateDeviceDependentResources()
{
	
}
