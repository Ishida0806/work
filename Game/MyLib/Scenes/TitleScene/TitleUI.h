//
//		File Name ： TitleUI.h
//		Production： 2023/11/11
//		Author　　： 石田 恭一
//
#pragma once

class TitleUI
{
	//	定数
public:

	//	通常の大きさ
	static const DirectX::SimpleMath::Vector2  BASE_SCALE;

	//	関数
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	TitleUI();

	/// <summary>
	/// 仮想デストラクタ
	/// </summary>
	virtual ~TitleUI() = default;


	/// <summary>
	/// 描画する
	/// </summary>
	/// <param name="texture">画像</param>
	/// <param name="position">座標</param>
	/// <param name="color">色</param>
	/// <param name="angele">角度</param>
	/// <param name="originPosition">中心座標</param>
	/// <param name="scale">大きさ</param>
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