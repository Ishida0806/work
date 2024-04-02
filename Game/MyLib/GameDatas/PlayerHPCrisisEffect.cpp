//
//		File Name �F PlayerHPCrisisEffect.cpp
//		Production�F 2023/1/10
//		Author�@�@�F �Γc ����	
//
#include "pch.h"
#include "PlayerHPCrisisEffect.h"


//	�^�C�}�[�̉���
const float						   PlayerHPCrisisEffect::TIMER_SPEED				= 6.0f;
//	�ԐF�̔Z�x	
const float						   PlayerHPCrisisEffect::RED_DENSITY				= 0.8f;
//	�ʏ�̑傫��X
const float						   PlayerHPCrisisEffect::DEFAULT_SCALE_X			= 0.85f;
//	�ʏ�̑傫��Y
const float						   PlayerHPCrisisEffect::DEFAULT_SCALE_Y			= 0.82f;
//	�g��̕␳�l
const float						   PlayerHPCrisisEffect::CORRECTION_EXPANSION		= 0.01f;
//	�|�X�g�G�t�F�N�g�̐^��
const DirectX::SimpleMath::Vector2 PlayerHPCrisisEffect::CRISIS_ORIGIN_POSITION	= DirectX::SimpleMath::Vector2(794.0f, 444.0f);

/// <summary>
/// �R���X�g���N�^
/// </summary>
PlayerHPCrisisEffect::PlayerHPCrisisEffect()
	:PostEffect(PostEffect::PostEffectType::PlayerHPCrisis)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayerHPCrisisEffect::~PlayerHPCrisisEffect()
{
}

/// <summary>
/// ����������
/// </summary>
void PlayerHPCrisisEffect::Initialize()
{
	m_texture = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"PinchEffect");
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void PlayerHPCrisisEffect::Update(const DX::StepTimer& timer)
{
	PostEffect::Update(timer);

	DirectX::SimpleMath::Color color = GetColor();

	//	�Ԃ�ς���
	color.x = sinf(GetElapsedTime() * TIMER_SPEED) + RED_DENSITY;

	SetColor(color);

	//	�g��g������
	m_scale.x = DEFAULT_SCALE_X + sinf(GetElapsedTime() * TIMER_SPEED) * CORRECTION_EXPANSION;
	m_scale.y = DEFAULT_SCALE_Y + sinf(GetElapsedTime() * TIMER_SPEED) * CORRECTION_EXPANSION;
}

/// <summary>
/// �`�揈��
/// </summary>
void PlayerHPCrisisEffect::Draw()
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
		m_scale
	);
}
