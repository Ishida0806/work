//
//		File Name �F ResultBackGround.cpp
//		Production�F 2023/11/12
//		Author�@�@�F �Γc ����	
// 
//		�w�i�摜�̕`�揈��
//
#include "pch.h"
#include "ResultBackGround.h"
#include <math.h>

//	�w�i�摜�̍��W
const DirectX::SimpleMath::Vector2 ResultBackGround::BACKGROUND_POSITION		= DirectX::SimpleMath::Vector2(670.0f, 450.0f); 
//	�w�i�摜�̐^�񒆂̍��W
const DirectX::SimpleMath::Vector2 ResultBackGround::BACKGROUND_ORIGIN_POSITION = DirectX::SimpleMath::Vector2(384.5f, 465.0f);
//	�傫���Ȃ鑬�x
const float						   ResultBackGround::SCLAE_UP_SPEED				= 0.002f;
//	�K��l�𒴂�����̑傫���Ȃ鑬�x
const float						   ResultBackGround::SCLAE_AFTER_SPEED			= 0.05f;
//	�ڕW�̑傫��
const float						   ResultBackGround::TARGET_SCALE				= 0.125f;
//	��鑬�x
const float						   ResultBackGround::TURN_SPEED					= 10.0f;
//	���W�̈ړ����x
const float						   ResultBackGround::POSITION_SPEED				= 0.03f;
//	�傫���̌덷�͈�
const float						   ResultBackGround::ERROR_RANGE_SCALE			= 0.005f;
//	�ڕW�̊p�x
const float						   ResultBackGround::TARGET_ANGLE				= 10.0f;
//	�ڕW�̍ŏI�傫��
const float						   ResultBackGround::TARGET_FINAL_SCALE			= 0.95f;


/// <summary>
/// �X�V����
/// </summary>
ResultBackGround::ResultBackGround()
	:m_texture(nullptr),
	m_angle(0.0f),
	m_targetAngle(0.0f)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ResultBackGround::~ResultBackGround()
{
}

/// <summary>
/// ����������
/// </summary>
void ResultBackGround::Initialize()
{
	m_texture = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"Result_ScoreBackGround");

	m_position = { 1050.0f,0.0f };
}

/// <summary>
/// �X�V����
/// </summary>
/// <returns>�g�p</returns>
bool ResultBackGround::Update()
{
	using namespace DirectX::SimpleMath;


	//	�傫�������̒l�𒴂���܂Œx�����A���̂��Ƃ͑���
	if (m_sacle.x <= TARGET_SCALE && m_sacle.y <= TARGET_SCALE)
	{
		//	���X�Ɋg��
		m_sacle = Vector2::Lerp(m_sacle, Vector2::One, SCLAE_UP_SPEED);
		//	���X�ɉ�
		m_angle += DirectX::XMConvertToRadians(TURN_SPEED);
		//	���W�����X�Ɉړ�
		m_position = Vector2::Lerp(m_position, BACKGROUND_POSITION, 0.01f);
	}
	else
	{	
		if (m_sacle.x >= TARGET_FINAL_SCALE && m_sacle.y >= TARGET_FINAL_SCALE)
		{
			m_angle = Utility::Lerp(m_angle , m_targetAngle, 0.05f);

			if (m_angle >= m_targetAngle - ERROR_RANGE_SCALE)
			{
				return true;
			}
		}
		else
		{
			//	���X�ɖ߂�
			m_angle += DirectX::XMConvertToRadians(TURN_SPEED);
			// �⊮��̊p�x���X�V
			m_targetAngle = ConvartTargetAngle(DirectX::XMConvertToRadians(TARGET_ANGLE)) + m_angle;
			//	���W�����X�Ɉړ�
			m_position = Vector2::Lerp(m_position, BACKGROUND_POSITION, POSITION_SPEED);
			//	���X�Ɋg��
			m_sacle = Vector2::Lerp(m_sacle, Vector2::One, SCLAE_AFTER_SPEED);
		}
	}	
	
	return false;
}

/// <summary>
/// �`�揈��
/// </summary>
void ResultBackGround::Draw()
{
	//	�X�v���C�g�o�b�`
	DirectX::SpriteBatch* spriteBath = MyLib::ScreenResources::GetInstance()->GetSpriteBatch();

	//	�w�i�摜�̕`��
	spriteBath->Draw
	(
		m_texture,
		m_position,
		nullptr,
		DirectX::Colors::White,
		m_angle,
		BACKGROUND_ORIGIN_POSITION,
		m_sacle
	);
}

/// <summary>
/// �ڕW�p�x�܂ł̋������Z�o����
/// </summary>
/// <param name="targetAngle">�ڕW�p�x</param>
/// <returns>�ڕW�p�x</returns>
float ResultBackGround::ConvartTargetAngle(const float& targetAngle)
{
	//	������̃f�[�^�ɂ���
	float rad = fmod(m_angle, DirectX::XMConvertToRadians(360.0f));
	//	������̃f�[�^�̂ǂ̂��炢�̊p�x�ɂ��邩�v�Z
	float ans = DirectX::XMConvertToRadians(360.0f) - rad;
	//	�ڕW�l�ƌv�Z
	return targetAngle + ans;
}
