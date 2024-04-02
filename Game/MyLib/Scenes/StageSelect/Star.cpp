//
//		File Name �F Star.cpp
//		Production�F 2023/11/02
//		Author�@�@�F �Γc ����
// 
//		���ɕ����Ԑ��̕`��X�V���s��	
// 
#include "pch.h"
#include "Star.h"

#include "StageSelectScene.h"

//	���̉摜�̒����̍��W
const DirectX::SimpleMath::Vector2	Star::ORIGIN_STAR_POSITION = DirectX::SimpleMath::Vector2(35.3f, 79.45);

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="starTexture">�摜</param>
/// <param name="position">���W</param>
/// <param name="color">�F</param>
/// <param name="scale">�傫��</param>
/// <param name="speed">���x</param>
/// <param name="lifeCount">��������</param>
Star::Star(
	ID3D11ShaderResourceView* starTexture,
	const DirectX::SimpleMath::Vector2& position,
	const DirectX::SimpleMath::Color& color, 
	const DirectX::SimpleMath::Vector2& scale,
	const float& speed,
	const float& lifeCount
) :m_starTexture(starTexture),
	m_position(position),
	m_memoryPosition(position),
	m_memoryColor(color),
	m_color(color),
	m_memoryScale(scale),
	m_scale(scale),
	m_speed(speed),
	m_lifeCount(lifeCount),
	m_memoryLifeCount(lifeCount),
	m_isUsed(false)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Star::~Star()
{
}

/// <summary>
/// ����������
/// </summary>
void Star::Initialize()
{
	//	�ŏ��͕`������Ȃ�
	m_lifeCount = 0.0f;
	m_isUsed = false;
	m_scale = DirectX::SimpleMath::Vector2::Zero;
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void Star::Update(const DX::StepTimer& timer)
{
	//	���g�p��ԂȂ琶�����Ԃ𑫂�
	if (!m_isUsed) 
	{
		m_lifeCount += static_cast<float>(timer.GetElapsedSeconds());

		//	���߂�ꂽ�������Ԃ𒴂�����g�p��Ԃ�
		if (m_lifeCount >= m_memoryLifeCount)
		{
			BeginStar();
		}
		else
		{
			return;
		}
	}

	//	���������Ԃ����炷
	m_lifeCount -= static_cast<float>(timer.GetElapsedSeconds());

	//	�X�P�[����i�X�Ə�����
	m_scale = DirectX::SimpleMath::Vector2::Lerp(m_scale, DirectX::SimpleMath::Vector2::Zero, m_speed);

	//	�������Ԃ�0�ɂȂ����疢�g�p��Ԃ�
	if (m_isUsed && m_lifeCount < 0.0f)
	{
		m_isUsed = false;
		m_scale = DirectX::SimpleMath::Vector2::Zero;
	}

}

/// <summary>
/// �`�悷��
/// </summary>
void Star::Draw()
{
	//	�X�v���C�g�o�b�`
	DirectX::SpriteBatch* spriteBatch = MyLib::ScreenResources::GetInstance()->GetSpriteBatch();

	//	�`��s��
	spriteBatch->Draw
	(
		m_starTexture,
		m_position,
		nullptr,
		m_color,
		0.0f,
		ORIGIN_STAR_POSITION,
		m_scale
	);
}

/// <summary>
/// �I������
/// </summary>
void Star::Finalize()
{
}


/// <summary>
/// �J�n����
/// </summary>
void Star::BeginStar()
{
	//	���W
	m_position  = m_memoryPosition;
	//	�F
	m_color		= m_memoryColor;
	//	�傫��
	m_scale		= m_memoryScale;
	//	��������
	m_lifeCount = m_memoryLifeCount;
	//	�g�p���
	m_isUsed	= true;
}