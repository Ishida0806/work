//
//		File Name �F PlayerPowerffect.cpp
//		Production�F 2023/1/10
//		Author�@�@�F �Γc ����	
//
#include "pch.h"
#include "PlayerPowerffect.h"


//	�^�C�}�[�̉���
const float						   PlayerPowerffect::TIMER_SPEED				= 7.0f;
//	�|�X�g�G�t�F�N�g�̐^��
const DirectX::SimpleMath::Vector2 PlayerPowerffect::CRISIS_ORIGIN_POSITION	= DirectX::SimpleMath::Vector2(762.5f, 427.5);

/// <summary>
/// �R���X�g���N�^
/// </summary>
PlayerPowerffect::PlayerPowerffect()
	:PostEffect(PostEffect::PostEffectType::PowerUP)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayerPowerffect::~PlayerPowerffect()
{
}

/// <summary>
/// ����������
/// </summary>
void PlayerPowerffect::Initialize()
{
	m_texture = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"ColourlessBoard");
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void PlayerPowerffect::Update(const DX::StepTimer& timer)
{
	PostEffect::Update(timer);

	DirectX::SimpleMath::Color color = GetColor();
	//	���₵���茸�炵����
	color.x = sinf(GetElapsedTime() * TIMER_SPEED);
	//	�A���t�@�l�͌Œ�
	color.w = 0.0f;
	//	�J���[�̏���l�����߂�
	color.x = Utility::Clamp(color.x, 0.0f, 0.6f);

	SetLerpColor(color);

}

/// <summary>
/// �`�揈��
/// </summary>
void PlayerPowerffect::Draw()
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
