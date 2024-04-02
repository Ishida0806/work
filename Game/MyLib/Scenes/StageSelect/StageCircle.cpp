//
//		File Name ： StageCircle.cpp
//		Production： 2023/11/02
//		Author　　： 石田 恭一	
// 
#include "pch.h"
#include "StageCircle.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="texture">画像</param>
/// <param name="position">座標</param>
StageCircle::StageCircle(ID3D11ShaderResourceView* texture, const DirectX::SimpleMath::Vector2& position, const int& ID)
	:m_texture(texture),
	m_position(position),
	m_ID(ID)
{
	m_color = DirectX::SimpleMath::Vector4::One;
}

/// <summary>
/// デストラクタ
/// </summary>
StageCircle::~StageCircle()
{
}

/// <summary>
/// 初期化処理
/// </summary>
void StageCircle::Initialize()
{

}

/// <summary>
/// 更新処理
/// </summary>
void StageCircle::Update(const DX::StepTimer& timer, const int& stageNum)
{
	timer;

	if (stageNum == m_ID)		m_color = DirectX::Colors::Black;
	else						m_color = DirectX::Colors::White;

}

/// <summary>
/// 描画する
/// </summary>
void StageCircle::Draw()
{
	//	スプライトバッチ
	DirectX::SpriteBatch* spriteBatch = MyLib::ScreenResources::GetInstance()->GetSpriteBatch();
	//	描画する
	spriteBatch->Draw
	(
		m_texture,
		m_position,
		m_color
	);
}

/// <summary>
/// 終了処理
/// </summary>
void StageCircle::Finalize()
{
}
