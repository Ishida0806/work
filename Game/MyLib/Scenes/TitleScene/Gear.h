//
//		File Name �F Gear.h
//		Production�F 2023/11/11
//		Author�@�@�F �Γc ����
//
#pragma once

#include "TitleUI.h"

class Gear : public TitleUI
{
public:

	//	�M�A���������x
	static const float						   MOVE_GEAR_SPEED;
	//	�M�A����鑬�x
	static const float						   MOVE_GEAR_RADIAN;
	//	�M�A���x
	static const float						   GEAR_SPEED;
	//	�M�A�̖ڕW���W
	static const float						   GEAR_TARGET_POSITION;

	//	�񋓌^
public:

	//	����
	enum class Direction
	{
		Right = 0,
		Left = 1,

		OverID = 2
	};


	//	�ϐ�
private:

	//	�摜
	ID3D11ShaderResourceView*	 m_texture;
	//	���W
	DirectX::SimpleMath::Vector2 m_position;
	//	�^�񒆂̍��W
	DirectX::SimpleMath::Vector2 m_originPosition;
	//	�傫��
	DirectX::SimpleMath::Vector2 m_scale;
	//	�����̏��
	Direction					 m_isDirection;
	//	�p�x
	float						 m_angle;
	//	�^�C�g���̏��
	int							 m_state;


	//	�֐�
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="texture">�摜</param>
	/// <param name="position">���W</param>
	/// <param name="originPosition">�^�񒆂̍��W</param>
	/// <param name="Direction">����</param>
	Gear(
		ID3D11ShaderResourceView* texture,
		const DirectX::SimpleMath::Vector2& position,
		const DirectX::SimpleMath::Vector2& originPosition,
		const Direction&					direction
	);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Gear();


	void Update(const int& state);
	void Draw();

private:
	void UpdateIdle();
	void UpdateNoteIdle();
};