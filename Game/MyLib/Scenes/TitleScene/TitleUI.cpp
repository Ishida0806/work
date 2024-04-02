//
//		File Name ： TitleUI.cpp
//		Production： 2023/11/11
//		Author　　： 石田 恭一
// 
//		タイトルで描画するものの基底クラス
//
#include "pch.h"
#include "TitleUI.h"

//	画像のデフォルトの大きさ
const DirectX::SimpleMath::Vector2 TitleUI::BASE_SCALE = DirectX::SimpleMath::Vector2(0.9f, 0.9f);

/// <summary>
/// コンストラクタ
/// </summary>
TitleUI::TitleUI() 
{
}

/// <summary>
/// 描画する
/// </summary>
/// <param name="texture">画像</param>
/// <param name="position">座標</param>
/// <param name="color">色</param>
/// <param name="angele">角度</param>
/// <param name="originPosition">中心座標</param>
/// <param name="scale">大きさ</param>
void TitleUI::Draw(ID3D11ShaderResourceView* texture, DirectX::SimpleMath::Vector2 position, DirectX::SimpleMath::Color	 color, float angle, DirectX::SimpleMath::Vector2 originPosition, DirectX::SimpleMath::Vector2 scale)
{
	DirectX::SpriteBatch* spriteBatch = MyLib::ScreenResources::GetInstance()->GetSpriteBatch();

	spriteBatch->Draw
	(
		texture,
		position,
		nullptr,
		color,
		angle,
		originPosition,
		scale
	);
}