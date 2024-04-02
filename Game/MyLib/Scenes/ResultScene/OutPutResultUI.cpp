
#include "pch.h"
#include "OutPutResultUI.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="texture">画像</param>
/// <param name="position">座標</param>
/// <param name="originPosition">画像の真ん中座標</param>
OutPutResultUI::OutPutResultUI(
	ID3D11ShaderResourceView* texture, 
	const DirectX::SimpleMath::Vector2& position,
	const DirectX::SimpleMath::Vector2& originPosition
)
	:m_texture(texture),
	m_position(position),
	m_originPosition(originPosition),
	m_angle(0.0f),
	m_alfa(1.0f)
{
}

/// <summary>
/// デストラクタ
/// </summary>
OutPutResultUI::~OutPutResultUI()
{
}

/// <summary>
/// 更新処理
/// </summary>
void OutPutResultUI::Update()
{
	m_alfa = sinf(MyLib::ElapsedTime::GetInstance()->GetElapsedTime() * 2.5f);
}

/// <summary>
/// 描画処理
/// </summary>
void OutPutResultUI::Draw()
{
	//	案内キーの描画
	MyLib::ScreenResources::GetInstance()->GetSpriteBatch()->Draw
	(
		m_texture,
		m_position,
		nullptr,
		DirectX::SimpleMath::Color(m_alfa, m_alfa, m_alfa, m_alfa),
		0.0f,
		m_originPosition
	);
}