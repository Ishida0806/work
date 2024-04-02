//
//		File Name �F Star.h
//		Production�F 2023/11/02
//		Author�@�@�F �Γc ����	
// 
#pragma once

class Star final
{
	//	�萔
public:

	//	���̉摜�̒����̍��W
	static const DirectX::SimpleMath::Vector2	ORIGIN_STAR_POSITION;

	//	�ϐ�
private:

	//	�摜
	ID3D11ShaderResourceView*		m_starTexture;
	//	���W
	DirectX::SimpleMath::Vector2	m_position;
	//	�L�����W
	DirectX::SimpleMath::Vector2	m_memoryPosition;
	//	�F
	DirectX::SimpleMath::Color		m_color;
	//	�L���̐F
	DirectX::SimpleMath::Color		m_memoryColor;
	//	���݂̃X�P�[��
	DirectX::SimpleMath::Vector2	m_scale;
	//	�ŏ��̂̃X�P�[��
	DirectX::SimpleMath::Vector2	m_memoryScale;
	//	���x
	float							m_speed;
	//	��������
	float							m_lifeCount;
	//	�L���̐�������
	float							m_memoryLifeCount;
	//	�g�p���
	bool							m_isUsed;

public:
	 
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="starTexture">�摜</param>
	/// <param name="position">���W</param>
	/// <param name="color">�F</param>
	/// <param name="scale">�傫��</param>
	/// <param name="speed">���x</param>
	/// <param name="lifeCount">��������</param>
	Star
	(
		ID3D11ShaderResourceView* starTexture,
		const DirectX::SimpleMath::Vector2& position,
		const DirectX::SimpleMath::Color&   color,
		const DirectX::SimpleMath::Vector2& scale,
		const float&						speed,
		const float&						lifeCount
	);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Star();

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
	/// �`�悷��
	/// </summary>
	void Draw();

	/// <summary>
	/// �I������
	/// </summary>
	void Finalize();

	//	���ߍ��݊֐�
private:

	/// <summary>
	/// �J�n����
	/// </summary>
	void BeginStar();
};