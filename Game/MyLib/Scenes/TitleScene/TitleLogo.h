//
//		File Name ： TitleLogo.h
//		Production： 2023/11/11
//		Author　　： 石田 恭一
//
#pragma once

#include "TitleUI.h"

class TitleLogo : public TitleUI
{
public:


	//	ターゲットのY座標
	static const float  LOGO_TARGET_POSITION_Y;
	//	ロゴが動く速度
	static const float  MOVE_LOGO_SPEED;


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
	TitleLogo(
		ID3D11ShaderResourceView* texture,
		const DirectX::SimpleMath::Vector2& position,
		const DirectX::SimpleMath::Vector2& originPosition
	);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~TitleLogo();


	void Update(const int& state);
	void Draw();

private:
	void UpdateIdle();
	void UpdateNoteIdle();
};