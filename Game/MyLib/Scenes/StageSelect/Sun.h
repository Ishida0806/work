//
//		File Name �F Sun.h
//		Production�F 2023/11/25
//		Author�@�@�F �Γc ����	
//
#pragma once


class Sun final
{
	//	�A�N�Z�T
public:

	//	�摜�̐^��
	static const DirectX::SimpleMath::Vector2  ORIGIN_SUN_TEXTURE;

	//	�ϐ�
private:

	//	���W
	DirectX::SimpleMath::Vector2	m_position;
	//	�ڕW���W
	DirectX::SimpleMath::Vector2	m_targetPosition;
	//	��������
	DirectX::SimpleMath::Vector2	m_scale;
	//	�摜
	ID3D11ShaderResourceView*		m_sunTexture;
	//	���݂̃X�e�[�W
	int								m_stage;
	//	�p�x
	float							m_angle;
	//	�A���t�@�l
	float							m_alfa;
	//	���Ɉړ����邽�߂̎���
	float							m_startTime;

	//	�֐�
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Sun();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Sun();

	/// <summary>
	/// ����������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="timer">�^�C�}�[</param>
	/// <param name="stageNum">�X�e�[�W�ԍ�/param>
	void Update(const DX::StepTimer& timer, const int& stageNum);

	/// <summary>
	/// �`�悷��
	/// </summary>
	void Draw();

	//	���ߍ��݊֐�
private:

	/// <summary>
	/// �f�o�C�X�ˑ��̃��\�[�X�̏�����
	/// </summary>
	void CreateDeviceDependentResources();
};

