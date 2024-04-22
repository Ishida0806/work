//
//		File Name �F PlayerSwingSpeedEffect.cpp
//		Production�F 2023/1/10
//		Author�@�@�F �Γc ����	
//
#include "pch.h"
#include "PlayerSwingSpeedEffect.h"


//	�^�C�}�[�̉���
const float						   PlayerSwingSpeedEffect::TIMER_SPEED				= 7.0f;
//	�|�X�g�G�t�F�N�g�̐^��
const DirectX::SimpleMath::Vector2 PlayerSwingSpeedEffect::CRISIS_ORIGIN_POSITION	= DirectX::SimpleMath::Vector2(762.5f, 427.5);

/// <summary>
/// �R���X�g���N�^
/// </summary>
PlayerSwingSpeedEffect::PlayerSwingSpeedEffect()
	:
	PostEffect(PostEffect::PostEffectType::SwingSpeedUP)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayerSwingSpeedEffect::~PlayerSwingSpeedEffect()
{
}

/// <summary>
/// ����������
/// </summary>
void PlayerSwingSpeedEffect::Initialize()
{
	m_texture = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"ColourlessBoard");
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void PlayerSwingSpeedEffect::Update(const DX::StepTimer& timer)
{
	PostEffect::Update(timer);

	DirectX::SimpleMath::Color color = GetColor();

	color.x = sinf(GetElapsedTime() * TIMER_SPEED);
	color.y = sinf(GetElapsedTime() * TIMER_SPEED);

	color.w = 0.0f;
	
	color.x = Utility::Clamp(color.x, 0.0f, 0.4f);
	color.y = Utility::Clamp(color.y, 0.0f, 0.4f);

	SetLerpColor(color);
}

/// <summary>
/// �`�揈��
/// </summary>
void PlayerSwingSpeedEffect::Draw()
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
