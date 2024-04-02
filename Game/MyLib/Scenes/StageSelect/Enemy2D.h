//
//		File Name �F Enemy2D.h
//		Production�F 2023/10/25
//		Author�@�@�F �Γc ����	
//
#pragma once


class Enemy2D
{
	//	�A�N�Z�T
public:

	//	������
	static const int						   GENERATION_ENEMY2D;
	//	�摜�̐^��
	static const DirectX::SimpleMath::Vector2  ORIGIN_ENEMY2D_TEXTURE;

	//	�ϐ�
private:

	//	���W
	DirectX::SimpleMath::Vector2	m_enemy2DPos;
	//	�摜
	ID3D11ShaderResourceView*		m_enemy2DTexture;
	//	�����_���Ȍ���
	int								m_randomDirection;
	//	�p�x
	float							m_angle;
	//	�����_���ȑ傫��
	float							m_randomScale;
	//	�����_���ȑ��x
	float							m_randomSpeed;
	//	�����_���ȗh�ꕝ
	float							m_randomShake;

	//	�֐�
public:
	
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="texture">�摜</param>
	/// <param name="position">���W</param>
	Enemy2D(ID3D11ShaderResourceView* texture,const DirectX::SimpleMath::Vector2& position);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Enemy2D();

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

	//	�v���C�x�[�g�֐�
private:

	/// <summary>
	/// �f�o�C�X�ˑ��̃��\�[�X�̏�����
	/// </summary>
	void CreateDeviceDependentResources();
};

