//
//		File Name �F TitleStringUI.h
//		Production�F 2023/11/11
//		Author�@�@�F �Γc ����
//
#pragma once

#include "TitleUI.h"

class TitleStringUI : public TitleUI
{
	//	�萔
public:

	//	�h�炷�傫��
	static const float					      SHAKE_TEXTURE;
	//	�h�炷����
	static const float					      SHAKE_SPEED;
	//	�p�x��߂����x
	static const float						  MOVE_BACKANGLE_SPEED;
	//	�v���C�Q�[���̐^�񒆍��W
	static const DirectX::SimpleMath::Vector2 PLAYGAME_ORIGIN_POSITION;
	//	�R���t�B�O�̐^�񒆍��W
	static const DirectX::SimpleMath::Vector2 CONFIG_ORIGIN_POSITION;
	//	�G���h�Q�[���̐^�񒆍��W
	static const DirectX::SimpleMath::Vector2 ENDGAME_ORIGIN_POSITION;


	//	�񋓌^
public:

	//	�����^�C�v
	enum class StirngType
	{
		PLay = 0,
		Config = 1,
		End = 2,

		OverID = 3		
	};


	//	�ϐ�
private:

	//	�摜
	ID3D11ShaderResourceView*	 m_texture;
	//	OFF��
	ID3D11ShaderResourceView*	 m_offTexture;
	//	���W
	DirectX::SimpleMath::Vector2 m_position;
	//	�^�񒆂̍��W
	DirectX::SimpleMath::Vector2 m_originPosition;
	//	�傫��
	DirectX::SimpleMath::Vector2 m_scale;
	//	�^�C�g���̏��
	int							 m_state;
	//	�p�x
	float						 m_angle;
	//	�I�t�Z�b�g�l
	float						 m_offsetX;
	//	�^�C�v
	int							 m_type;


	//	�֐�
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="texture">�摜</param>
	/// <param name="texture">OFF���̉摜</param>
	/// <param name="position">���W</param>
	/// <param name="index">�ԍ�</param>
	TitleStringUI(
		ID3D11ShaderResourceView* texture,
		ID3D11ShaderResourceView* offTexture,
		const DirectX::SimpleMath::Vector2& position,
		const int& index
	);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~TitleStringUI();


	void Update(const int& state);
	void Draw();

private:
	void SelectUI();
};