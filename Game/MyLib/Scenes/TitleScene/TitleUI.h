//
//		File Name �F TitleUI.h
//		Production�F 2023/11/11
//		Author�@�@�F �Γc ����
//
#pragma once

class TitleUI
{
	//	�萔
public:

	//	�ʏ�̑傫��
	static const DirectX::SimpleMath::Vector2  BASE_SCALE;

	//	�֐�
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	TitleUI();

	/// <summary>
	/// ���z�f�X�g���N�^
	/// </summary>
	virtual ~TitleUI() = default;


	/// <summary>
	/// �`�悷��
	/// </summary>
	/// <param name="texture">�摜</param>
	/// <param name="position">���W</param>
	/// <param name="color">�F</param>
	/// <param name="angele">�p�x</param>
	/// <param name="originPosition">���S���W</param>
	/// <param name="scale">�傫��</param>
	void Draw
	(
		ID3D11ShaderResourceView*	 texture = nullptr,
		DirectX::SimpleMath::Vector2 position = DirectX::SimpleMath::Vector2::Zero,
		DirectX::SimpleMath::Color	 color = DirectX::SimpleMath::Color(0.0f, 0.0f, 0.0f, 0.5f),
		float angle = 0.0f,
		DirectX::SimpleMath::Vector2 originPosition = DirectX::SimpleMath::Vector2::Zero,
		DirectX::SimpleMath::Vector2 scale = DirectX::SimpleMath::Vector2::One
	);

};