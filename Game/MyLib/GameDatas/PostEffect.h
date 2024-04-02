//
//		File Name �F PostEffect.h
//		Production�F 2023/1/10
//		Author�@�@�F �Γc ����	
//
#pragma once

class PostEffect
{
	//	�񋓌^
public:

	enum class PostEffectType
	{
		None = 0,

		PowerUP = 1,
		HealthUP = 2,
		SpeedUP = 3,
		PlayerHPCrisis = 4,

		OverID
	};

	//	�A�N�Z�T
public:

	inline PostEffectType			  GetEffectType()	const { return m_postType; }
	//	�J���[���擾����
	inline DirectX::SimpleMath::Color GetColor()		const  { return m_color; }
	//	�o�ߎ��Ԃ��擾
	inline float					  GetElapsedTime()	const  { return m_elapsedTime; }
	//	�J���[��ݒ肷��
	void SetColor(const DirectX::SimpleMath::Color& color)	   { m_color = color; }
	//	�J���[�����[�v�Őݒ肷��
	void SetLerpColor(const DirectX::SimpleMath::Color& color) { m_color = DirectX::SimpleMath::Color::Lerp(m_color, color, 0.1f); }
	//	�o�ߎ��Ԃ����Z�b�g
	void ResetElapseTime()									   { m_elapsedTime = 0.0f; }

	//	�ϐ�
private:

	//	�|�X�g�G�t�F�N�g�̃^�C�v
	PostEffectType				m_postType;
	//	�J���[
	DirectX::SimpleMath::Color	m_color;
	//	�o�ߎ���
	float						m_elapsedTime;

	//	�֐�
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	PostEffect(const PostEffectType& postType)
		:m_postType(postType),
		m_elapsedTime(0.0f)
	{
		m_color = DirectX::SimpleMath::Color(0.0f, 0.0f, 0.0f, 0.0f);
	}

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~PostEffect() = default;

	/// <summary>
	///	����������
	/// </summary>
	virtual void Initialize() 
	{
	};

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="timer">�^�C�}�[</param>
	virtual void Update(const DX::StepTimer& timer)
	{ 
		m_elapsedTime += static_cast<float>(timer.GetElapsedSeconds()); 
	}

	/// <summary>
	/// �`��̃^�C�v
	/// </summary>
	virtual void Draw() 
	{

	};

	/// <summary>
	/// �J���[�Ǝ��Ԃ����Z�b�g����
	/// </summary>
	void ResetColorAndTime()
	{
		m_color = DirectX::SimpleMath::Color(0.0f, 0.0f, 0.0f, 0.0f);

		m_elapsedTime = 0.0f;
	}

	/// <summary>
	/// �J���[�����[�v�Ń��Z�b�g����
	/// </summary>
	void ResetLerpColor()
	{
		m_color = DirectX::SimpleMath::Color::Lerp(m_color, DirectX::SimpleMath::Color(0.0f, 0.0f, 0.0f, 0.0f), 0.03f);
	}
};