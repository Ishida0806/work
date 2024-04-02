//
//		File Name �F ChangeEffect.h
//		Production�F 2023/1/10
//		Author�@�@�F �Γc ����	
//
#pragma once
#include "pch.h"

class ChangeEffect
{
	//	�񋓌^
public:

	//	�V�[���J�ڂ̃^�C�v
	enum class ChangeSceneFadeType
	{
		None = 0,

		To	= 1,
		Out	= 2,

		OverID
	};

	//	�V�[���^�C�v
	enum class ChangeSceneType
	{
		None = 0,

		Title   = 1,
		Select  = 2,
		Play	= 3,
		Result  = 4,

		OverID
	};

	//	�A�N�Z�T
public:

	//	�؂�ւ���^�C�v
	inline ChangeSceneType			  GetChangeType()		const	{ return m_changeType; }
	//	�V�[���̃t�F�[�h�^�C�v���擾����
	inline ChangeSceneFadeType		  GetChangeFadeType()	const	{ return m_fadeType; }
	//	�摜�̎擾����
	inline ID3D11ShaderResourceView*  GetTexture()			const	{ return m_texture; }
	//	�J���[���擾����
	inline DirectX::SimpleMath::Color GetColor()			const	{ return m_color; }
	//	�o�ߎ��Ԃ��擾
	inline float					  GetElapsedTime()		const	{ return m_elapsedTime; }
	//	�J���[��ݒ肷��
	void SetColor(const DirectX::SimpleMath::Color& color)			{ m_color = color; }
	//	�V�[���̃t�F�[�h�^�C�v��ݒ肷��
	void SetSceneFadeType(const ChangeSceneFadeType& fadeType)		{ m_fadeType = fadeType; }
	//	�J���[�����[�v�Őݒ肷��
	void SetLerpColor(const DirectX::SimpleMath::Color& color)		{ m_color = DirectX::SimpleMath::Color::Lerp(m_color, color, 0.1f); }
	//	�摜��ݒ肷��
	void SetTexure(ID3D11ShaderResourceView* texture)				{ m_texture = texture; }
	//	�o�ߎ��Ԃ����Z�b�g
	void ResetElapseTime()											{ m_elapsedTime = 0.0f; }


	//	�ϐ�
private:

	//	�摜
	ID3D11ShaderResourceView*	m_texture;
	//	�V�[���J�ڂ̍ۂ̃^�C�v
	ChangeSceneType				m_changeType;
	//	�V�[����ς���^�C�v
	ChangeSceneFadeType			m_fadeType;
	//	�J���[
	DirectX::SimpleMath::Color	m_color;
	//	�o�ߎ���
	float						m_elapsedTime;

	//	�֐�
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="changeType">�؂�ւ��̃^�C�v</param>
	ChangeEffect(const ChangeSceneType& changeType)
		:m_changeType(changeType),
		m_fadeType(ChangeSceneFadeType::None),
		m_elapsedTime(0.0f),
		m_texture(nullptr)
	{
		m_color = DirectX::SimpleMath::Color(0.0f, 0.0f, 0.0f, 0.0f);
	}

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~ChangeEffect() = default;

	/// <summary>
	///	����������
	/// </summary>
	virtual void Initialize()
	{

	}

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="timer">�^�C�}�[</param>
	void UpdateElapsedTime(const DX::StepTimer& timer)
	{
		m_elapsedTime += static_cast<float>(timer.GetElapsedSeconds());
	}

	/// <summary>
	/// ���̃V�[���ɑJ�ڂ���
	/// </summary>
	virtual void ToChange() = 0;

	/// <summary>
	/// �V�[���𔲂���
	/// </summary>
	virtual void OutChange()= 0;

	/// <summary>
	/// �`��̃^�C�v
	/// </summary>
	virtual void Draw()
	{

	};

	/// <summary>
	/// ���O�̏��������s��
	/// </summary>
	virtual void PreInitialize() {};

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

protected:

	/// <summary>
	/// �V�[���̃t�F�[�h���I������
	/// </summary>
	void FinishedChangeScene()
	{
		//	���ԂƐF�̓��Z�b�g
		ResetColorAndTime();
		//	�I������
		m_fadeType = ChangeSceneFadeType::None;
	}
};