
#include "pch.h"
#include "HitParticle.h"

/// <summary>
/// �R���X�g���N�^
/// �����͏����ݒ�p�̐��l
/// </summary>
/// <param name="life">��������</param>
/// <param name="pos">���W</param>
/// <param name="velocity">���x</param>
/// <param name="accele">�����x</param>
/// <param name="startScale">�����T�C�Y</param>
/// <param name="endScale">�ŏI�T�C�Y</param>
/// <param name="startColor">�����F</param>
/// <param name="endColor">�ŏI�F</param>
HitParticle::HitParticle(
	float life, 
	DirectX::SimpleMath::Vector3 pos, 
	DirectX::SimpleMath::Vector3 velocity, 
	DirectX::SimpleMath::Vector3 accele, 
	DirectX::SimpleMath::Vector3 startScale, 
	DirectX::SimpleMath::Vector3 endScale, 
	DirectX::SimpleMath::Color startColor, 
	DirectX::SimpleMath::Color endColor
)
	:m_life(life),
	m_startLife(life),
	m_position(pos),
	m_velocity(velocity),
	m_memorryVelocity(velocity),
	m_accele(accele),
	m_memorryAcccele(accele),
	m_startScale(startScale),
	m_endScale(endScale),
	m_startColor(startColor),
	m_endColor(endColor)
{
	
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
HitParticle::~HitParticle()
{
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void HitParticle::Update(const DX::StepTimer& timer)
{
	using namespace DirectX::SimpleMath;

	//�����Ɏg���b���v(1�b��1.0f)���擾����B
	float elapsedTime = static_cast<float>(timer.GetElapsedSeconds());

	float lerpSpeed = 0.1f;

	// �X�P�[��
	m_nowScale = Vector3::Lerp(m_nowScale, m_endScale, lerpSpeed);
	// �F
	m_nowColor = Color::Lerp(m_nowColor, m_endColor, lerpSpeed);
	// ���x�̌v�Z
	m_velocity += m_accele * elapsedTime;
	// ���W�̌v�Z
	m_position += m_velocity * elapsedTime;
	m_life -= elapsedTime;
}

/// <summary>
///  �G�t�F�N�g���J�n����
/// </summary>
/// <param name="position">���W</param>
void HitParticle::StartEffect(DirectX::SimpleMath::Vector3 position)
{
	m_life = m_startLife;

	m_position = position;
	m_velocity = m_memorryVelocity;
	m_accele   = m_memorryAcccele;

	m_nowScale = m_startScale;

	m_nowColor = m_startColor;
}
