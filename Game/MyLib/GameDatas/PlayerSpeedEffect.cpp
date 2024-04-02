//
//		File Name �F PlayerSpeedEffect.cpp
//		Production�F 2023/1/10
//		Author�@�@�F �Γc ����	
//
#include "pch.h"
#include "PlayerSpeedEffect.h"


//	�^�C�}�[�̉���
const float						   PlayerSpeedEffect::TIMER_SPEED				= 7.0f;
//	�|�X�g�G�t�F�N�g�̐^��
const DirectX::SimpleMath::Vector2 PlayerSpeedEffect::CRISIS_ORIGIN_POSITION	= DirectX::SimpleMath::Vector2(762.5f, 427.5);

/// <summary>
/// �R���X�g���N�^
/// </summary>
PlayerSpeedEffect::PlayerSpeedEffect()
	:PostEffect(PostEffect::PostEffectType::SpeedUP)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayerSpeedEffect::~PlayerSpeedEffect()
{
}

/// <summary>
/// ����������
/// </summary>
void PlayerSpeedEffect::Initialize()
{
	m_texture = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"ColourlessBoard");
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void PlayerSpeedEffect::Update(const DX::StepTimer& timer)
{

	PostEffect::Update(timer);

	DirectX::SimpleMath::Color color = GetColor();

	color.z = sinf(GetElapsedTime() * TIMER_SPEED);

	color.w = 0.0f;
	
	color.z = Utility::Clamp(color.z, 0.0f, 0.4f);

	SetLerpColor(color);
}

/// <summary>
/// �`�揈��
/// </summary>
void PlayerSpeedEffect::Draw()
{
	//	�X�v���C�g�o�b�`
	DirectX::SpriteBatch* spriteBatch = MyLib::ScreenResources::GetInstance()->GetSpriteBatch();

	spriteBatch->Draw
	(
		m_texture,
		DirectX::SimpleMath::Vector2(640.0f, 360.0f),
		nullptr,
		GetColor(),
		0.0f,
		CRISIS_ORIGIN_POSITION,
		DirectX::SimpleMath::Vector2::One
	);
}
