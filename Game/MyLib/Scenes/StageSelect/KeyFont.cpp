//
//		File Name ： KeyFont.cpp
//		Production： 2023/11/01
//		Author　　： 石田 恭一	
// 
//		キーの描画・更新を行う
// 
#include "pch.h"
#include "KeyFont.h"

//	画像の真ん中の位置の初期化する
const DirectX::SimpleMath::Vector2 KeyFont::ORIGIN_KEY_TEXTURE = DirectX::SimpleMath::Vector2(250.0f, 300.0f);
//	キーの大きさ
const DirectX::SimpleMath::Vector2 KeyFont::SCALE_KEY_TEXTURE = DirectX::SimpleMath::Vector2(0.3f, 0.3f);
//	動く速さ
const float						   KeyFont::MOVE_KEY_SPEED = 0.5f;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="type">タイプ</param>
/// <param name="position">座標</param>
KeyFont::KeyFont(const FONT_TYPE type,DirectX::SimpleMath::Vector2 position)
	:m_fontType(type),
	m_keyPosition(position),
	m_keyFontTexture(nullptr),
	m_elapsedTime(0.0f)
{
}

/// <summary>
/// デストラクタ
/// </summary>
KeyFont::~KeyFont()
{
}

/// <summary>
/// 初期化処理
/// </summary>
void KeyFont::Initialize()
{
	//	フォントのタイプを変える
	switch (m_fontType)
	{
	case KeyFont::FONT_TYPE::LEFT:	m_keyFontTexture = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"Key_Holding_A");	break;
	case KeyFont::FONT_TYPE::RIGHT:	m_keyFontTexture = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"Key_Holding_D");	break;
	default:																															break;
	}
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="timer">タイマー</param>
void KeyFont::Update(const DX::StepTimer& timer)
{
	//	少し早く
	m_elapsedTime = static_cast<float>(timer.GetElapsedSeconds() * 3.0f);

	//	座標キーを移動する
	//	
	switch (m_fontType)
	{
	case KeyFont::FONT_TYPE::LEFT:	 m_keyPosition.x -= MOVE_KEY_SPEED * sinf(m_elapsedTime);		break;
	case KeyFont::FONT_TYPE::RIGHT:	 m_keyPosition.x += MOVE_KEY_SPEED * sinf(m_elapsedTime);		break;
	default:																						break;
	}
}

/// <summary>
/// 描画処理
/// </summary>
void KeyFont::Draw()
{
	//	スプライトバッチ
	DirectX::SpriteBatch* spriteBatch = MyLib::ScreenResources::GetInstance()->GetSpriteBatch();

	float angle = 0.0f;

	//	描画を行う
	spriteBatch->Draw
	(
		m_keyFontTexture,
		m_keyPosition,
		nullptr,
		DirectX::Colors::White,
		angle,
		ORIGIN_KEY_TEXTURE,
		SCALE_KEY_TEXTURE
	);	
}
