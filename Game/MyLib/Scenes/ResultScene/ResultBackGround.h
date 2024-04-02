//
//		File Name �F ResultBackGround.h
//		Production�F 2023/11/12
//		Author�@�@�F �Γc ����	
//
#pragma once

class ResultBackGround
{
	//	�萔
public:

	//	�w�i�摜�̍��W
	static const DirectX::SimpleMath::Vector2 BACKGROUND_POSITION;
	//	�w�i�摜�̐^�񒆂̍��W
	static const DirectX::SimpleMath::Vector2 BACKGROUND_ORIGIN_POSITION;
	//	�傫���Ȃ鑬�x
	static const float						  SCLAE_UP_SPEED;
	//	�K��l�𒴂�����̑傫���Ȃ鑬�x
	static const float						  SCLAE_AFTER_SPEED;
	//	�ڕW�̑傫��
	static const float						  TARGET_SCALE;
	//	��鑬�x
	static const float						  TURN_SPEED;
	//	���W�̈ړ����x
	static const float						  POSITION_SPEED;
	//	�傫���̌덷�͈�
	static const float						  ERROR_RANGE_SCALE;
	//	�ڕW�̊p�x
	static const float						  TARGET_ANGLE;
	//	�ڕW�̍ŏI�傫��
	static const float						  TARGET_FINAL_SCALE;


	//	�ϐ�
private:

	//	�傫��
	DirectX::SimpleMath::Vector2	m_sacle;
	//	���W
	DirectX::SimpleMath::Vector2	m_position;
	//	�摜
	ID3D11ShaderResourceView*		m_texture;
	//	�p�x
	float							m_targetAngle;
	float							m_angle;

	//	�֐�
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	ResultBackGround();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~ResultBackGround();

	/// <summary>
	/// ����������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <returns></returns>
	bool Update();

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw();

	//	�g�ݍ��݊֐�
private:

	/// <summary>
	/// �ڕW�p�x�܂ł̋������Z�o����
	/// </summary>
	/// <param name="targetAngle">�ڕW�p�x</param>
	/// <returns>�ڕW�p�x</returns>
	float ConvartTargetAngle(const float& targetAngle);
};