
//
//		File Name �F OutPutResultUI.h
//		Production�F 2023/11/11
//		Author�@�@�F �Γc ����
//
#pragma once

class OutPutResultUI
{
public:


	//	�^�[�Q�b�g��Y���W
	static const float  LOGO_TARGET_POSITION_Y;
	//	���S���������x
	static const float  MOVE_LOGO_SPEED;


	//	�ϐ�
private:

	//	�摜
	ID3D11ShaderResourceView*		 m_texture;
	//	���W
	DirectX::SimpleMath::Vector2	 m_position;
	//	�^�񒆂̍��W
	DirectX::SimpleMath::Vector2	 m_originPosition;
	//	�傫��
	DirectX::SimpleMath::Vector2	 m_scale;
	//	�p�x
	float							 m_angle;
	//	�A���t�@�l
	float							 m_alfa;



	//	�֐�
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="texture">�摜</param>
	/// <param name="position">���W</param>
	/// <param name="originPosition">�^�񒆂̍��W</param>
	OutPutResultUI(
		ID3D11ShaderResourceView* texture,
		const DirectX::SimpleMath::Vector2& position,
		const DirectX::SimpleMath::Vector2& originPosition
	);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~OutPutResultUI();

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw();
};