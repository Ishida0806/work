
#include "pch.h"
#include "Player2D.h"

//	�v���C���[�摜�̐^�񒆂̍��W
const DirectX::SimpleMath::Vector2 Player2D::PLAYER_ORIGIN_TEXTURE = DirectX::SimpleMath::Vector2(110.0f, 172.5f);
//	�v���C���[�̃f�t�H���g�̑傫��
const float						   Player2D::PLAYER_BASE_SCALE	   = 0.75f;
//	��������
const float						   Player2D::MOVE_PLAYER_SPEED	   = 0.08f;



/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="texture">�摜</param>
/// <param name="position">���W</param>
Player2D::Player2D(ID3D11ShaderResourceView* texture, const DirectX::SimpleMath::Vector2 position)
	:m_texture(texture),
	m_position(position),
	m_playerState(PLAYER_STATE::IDLE),
	m_playerAnimationTime(0.0f)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Player2D::~Player2D()
{
}

/// <summary>
/// ����������
/// </summary>
void Player2D::Initialize()
{
	m_scale = DirectX::SimpleMath::Vector2(0.75f);
}			

/// <summary>
/// �X�V����
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void Player2D::Update(const DX::StepTimer& timer)
{
	UpdatePlayerState(timer);
}

/// <summary>
/// �`�揈��
/// </summary>
void Player2D::Draw()
{
	//	�X�v���C�g�o�b�`
	DirectX::SpriteBatch* spriteBatch = MyLib::ScreenResources::GetInstance()->GetSpriteBatch();

	float angle = 0.0f;

	//	�`����s��
	spriteBatch->Draw
	(
		m_texture,
		m_position,
		nullptr,
		DirectX::Colors::White,
		angle,
		PLAYER_ORIGIN_TEXTURE,
		m_scale
	);
}

/// <summary>
/// �v���C���[�̃A�j���[�V�������J�n����
/// </summary>
void Player2D::BeginChangeSceneAnimation()
{
	m_playerState = PLAYER_STATE::FIRST;
}

void Player2D::UpdatePlayerState(const DX::StepTimer& timer)
{
	//	�v���C���[�̃X�e�[�g
	switch (m_playerState)
	{
	case Player2D::PLAYER_STATE::IDLE:
	{
		//	��������
		float secnd = static_cast<float>(timer.GetTotalSeconds() * 3.0f);
		//	�v���C���[���㉺�Ɉړ�������
		m_position.y += 2.0f * sinf(secnd * 2.5f);
		break;
	}
	//	�ŏ��̃A�j���[�V����
	case Player2D::PLAYER_STATE::FIRST:
	{
		//	���ɉ����点��
		m_position.x -= sinf(1.0f);
		m_position.y -= sinf(2.0f);

		//	����̂Ƃ���܂ōs�����玟�̑J�ڂ�
		if (m_position.x <= 260.0f)
		{
			m_playerState = PLAYER_STATE::SECOND;
		}

		break;
	}
	//	���Ɍ������ăv���C���[���ˌ�
	case Player2D::PLAYER_STATE::SECOND:
	{
		//	���W�������Â��炷
		m_position = DirectX::SimpleMath::Vector2::Lerp(m_position, DirectX::SimpleMath::Vector2(700.0f, 300.0f), MOVE_PLAYER_SPEED);
		//	�o�ߎ��Ԃ����Ԃ𑫂�
		m_playerAnimationTime += static_cast<float>(timer.GetElapsedSeconds());

		//	�v���C���[�̑傫�������񂾂�Ə�����
		m_scale.x = Utility::Lerp(m_scale.x, 0.0f, MOVE_PLAYER_SPEED / 2.0f);
		m_scale.y = Utility::Lerp(m_scale.y, 0.0f, MOVE_PLAYER_SPEED / 2.0f);

		break;
	}
	case Player2D::PLAYER_STATE::OverID:	break;
	default:								break;
	}
}


