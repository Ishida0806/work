
//
//		File Name �F Player2D.h
//		Production�F 2023/11/03
//		Author�@�@�F �Γc ����	
// 
#pragma once

class Player2D
{
	//	�萔
public:

	//	�v���C���[�摜�̐^�񒆂̍��W
	static const DirectX::SimpleMath::Vector2 PLAYER_ORIGIN_TEXTURE;
	//	�v���C���[�̃f�t�H���g�̑傫��
	static const float						  PLAYER_BASE_SCALE;
	//	��������
	static const float						  MOVE_PLAYER_SPEED;

	//	�񋓌^
public:

	//	�v���C���[�A�j���[�V�����̏��
	enum class PLAYER_STATE
	{
		IDLE = 0,
		FIRST = 1,
		SECOND = 2,

		OverID
	};

	//		�A�N�Z�T
public:


	inline PLAYER_STATE GetState()				const { return m_playerState; }
	inline float		GetFinAnimationTime()	const { return m_playerAnimationTime; }

	//	�ϐ�
private:

	//	�v���C���[�̉摜
	ID3D11ShaderResourceView*		m_texture;
	//	�v���C���[�̍��W
	DirectX::SimpleMath::Vector2	m_position;
	//	�v���C���[�̃A�j���[�V�������
	PLAYER_STATE					m_playerState;
	//	�v���C���[�̑傫��������������
	DirectX::SimpleMath::Vector2	m_scale;
	//	�v���C���[�̃A�j���[�V�����̎���
	float							m_playerAnimationTime;



public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="texture">�摜</param>
	/// <param name="position">���W</param>
	Player2D(ID3D11ShaderResourceView* texture, const DirectX::SimpleMath::Vector2 position);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Player2D();

	/// <summary>
	/// ����������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="timer">�^�C�}�[</param>
	void Update(const DX::StepTimer& timer);

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw();

	/// <summary>
	/// �v���C���[�̃A�j���[�V�������J�n����
	/// </summary>
	void BeginChangeSceneAnimation();

private:

	void UpdatePlayerState(const DX::StepTimer& timer);

};