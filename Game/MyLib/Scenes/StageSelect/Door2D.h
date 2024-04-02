//
//		File Name �F Door2D.h
//		Production�F 2023/10/25
//		Author�@�@�F �Γc ����	
//
#pragma once


class Door2D
{
	//	�A�N�Z�T
public:

	/// <summary>
	/// �h�A���W���擾����
	/// </summary>
	/// <returns>���W</returns>
	inline DirectX::SimpleMath::Vector2 GetDoorPosition()	const { return m_doorPos; }

	//	�萔
public:

	//	�摜�̐^�񒆂̈ʒu
	static const DirectX::SimpleMath::Vector2 ORIGIN_TEXTURE;
	//	�ړ����x
	static const float						  MOVE_SPEED;

	//	enum
public:

	//	�ǂ���ɓ������H
	enum class MOVE_DIRECTION
	{
		CENTER = 0,
		RIGHT = 1,
		LEFT = 2,
	};

	//	�ϐ�
private:

	//	�h�A�̎ʐ^
	ID3D11ShaderResourceView*		m_doorTexture;
	//	�t�H���g�̎ʐ^
	ID3D11ShaderResourceView*		m_fontTexture;
	//	�摜�̎ʐ^
	DirectX::SimpleMath::Vector2	m_doorPos;
	//	�t�H���g�̍��W
	DirectX::SimpleMath::Vector2	m_fontPos;
	//	�ړ�����ۂ̖ڕW�l
	DirectX::SimpleMath::Vector2	m_doorTargetPos;
	//	�ړ�����
	float							m_distance;
	//	�g�p���
	bool							m_used;
	//	�ǂ���Ɉړ�������
	MOVE_DIRECTION					m_moveState;

	//	�֐�
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="doorTexture">�h�A�̉摜</param>
	/// <param name="fontTexture">�t�H���g�̉摜</param>
	/// <param name="position">���W</param>
	/// <param name="distance">����Ă��鋗��</param>
	Door2D(ID3D11ShaderResourceView* doorTexture, ID3D11ShaderResourceView* fontTexture, const DirectX::SimpleMath::Vector2& position, const float& distance);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Door2D();

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update(bool used);

	/// <summary>
	/// �`�悷��
	/// </summary>
	/// <param name="scale">�傫��</param>
	void Draw(const DirectX::SimpleMath::Vector2& scale);

	/// <summary>
	/// ���W�����肷��
	/// </summary>
	void TargetPosDecision(int state);

private:


};
