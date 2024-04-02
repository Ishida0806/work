
#pragma once

class HitParticle
{
	//	�A�N�Z�T
public:

	//	���W���擾����
	inline  DirectX::SimpleMath::Vector3 GetPosition()	const { return m_position; }
	//	�ړ��ʂ��擾����
	inline  DirectX::SimpleMath::Vector3 GetVelocity()	const { return m_velocity; }
	//	�����x���擾����
	inline  DirectX::SimpleMath::Vector3 GetAccele()	const { return m_accele; }
	//	���݂̑傫�����擾����
	inline  DirectX::SimpleMath::Vector3 GetNowScale()	const { return m_nowScale; }
	//	�X�^�[�g���̑傫������������
	inline  DirectX::SimpleMath::Vector3 GetStartScale()const { return m_startScale; }
	//	�G���h���̑傫������������
	inline  DirectX::SimpleMath::Vector3 GetEndScale()	const { return m_endScale; }
	//	�������Ԃ��擾����
	inline  float GetLife()								const { return m_life; }
	//	�X�^�[�g���̐������Ԃ��擾����
	inline  float GetStartLife()						const { return m_startLife; }
	//	���݂̐F���擾����
	inline  DirectX::SimpleMath::Color GetNowColor()	const { return m_nowColor; }
	//	�X�^�[�g���̐F���擾����
	inline  DirectX::SimpleMath::Color GetStartColor()	const { return m_startColor; }
	//	�G���h���̐F���擾����
	inline  DirectX::SimpleMath::Color GetEndColor()	const { return m_endColor; }

private:
	//	���W
	DirectX::SimpleMath::Vector3	m_position;

	//	���x
	DirectX::SimpleMath::Vector3	m_velocity;
	DirectX::SimpleMath::Vector3	m_memorryVelocity;
	//	�����x
	DirectX::SimpleMath::Vector3	m_accele;
	DirectX::SimpleMath::Vector3	m_memorryAcccele;

	//	�X�P�[��
	DirectX::SimpleMath::Vector3	m_nowScale;
	DirectX::SimpleMath::Vector3	m_startScale;
	DirectX::SimpleMath::Vector3	m_endScale;

	//	�J���[
	DirectX::SimpleMath::Color		m_nowColor;
	DirectX::SimpleMath::Color		m_startColor;
	DirectX::SimpleMath::Color		m_endColor;

	//	��������
	float							m_life;
	float							m_startLife;

public:

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
	HitParticle(
		float life,
		DirectX::SimpleMath::Vector3 pos,
		DirectX::SimpleMath::Vector3 velocity,
		DirectX::SimpleMath::Vector3 accele,
		DirectX::SimpleMath::Vector3 startScale, DirectX::SimpleMath::Vector3 endScale,
		DirectX::SimpleMath::Color startColor, DirectX::SimpleMath::Color endColor
	);
	~HitParticle();

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="timer">�^�C�}�[</param>
	void Update(const DX::StepTimer& timer);


	/// <summary>
	///  �G�t�F�N�g���J�n����
	/// </summary>
	/// <param name="position">���W</param>
	void StartEffect(DirectX::SimpleMath::Vector3 position);
};

