//
//		File Name ： Gear.h
//		Production： 2023/11/11
//		Author　　： 石田 恭一
//
#pragma once

#include "TitleUI.h"

class Gear : public TitleUI
{
public:

	//	ギアが動く速度
	static const float						   MOVE_GEAR_SPEED;
	//	ギアを回る速度
	static const float						   MOVE_GEAR_RADIAN;
	//	ギア速度
	static const float						   GEAR_SPEED;
	//	ギアの目標座標
	static const float						   GEAR_TARGET_POSITION;

	//	列挙型
public:

	//	向き
	enum class Direction
	{
		Right = 0,
		Left = 1,

		OverID = 2
	};


	//	変数
private:

	//	画像
	ID3D11ShaderResourceView*	 m_texture;
	//	座標
	DirectX::SimpleMath::Vector2 m_position;
	//	真ん中の座標
	DirectX::SimpleMath::Vector2 m_originPosition;
	//	大きさ
	DirectX::SimpleMath::Vector2 m_scale;
	//	自分の状態
	Direction					 m_isDirection;
	//	角度
	float						 m_angle;
	//	タイトルの状態
	int							 m_state;


	//	関数
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="texture">画像</param>
	/// <param name="position">座標</param>
	/// <param name="originPosition">真ん中の座標</param>
	/// <param name="Direction">向き</param>
	Gear(
		ID3D11ShaderResourceView* texture,
		const DirectX::SimpleMath::Vector2& position,
		const DirectX::SimpleMath::Vector2& originPosition,
		const Direction&					direction
	);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Gear();


	void Update(const int& state);
	void Draw();

private:
	void UpdateIdle();
	void UpdateNoteIdle();
};