//
//		File Name ： TitleLogo.cpp
//		Production： 2023/11/11
//		Author　　： 石田 恭一
// 
//		タイトルのロゴの更新・描画を行う
//
#include "pch.h"

#include "TitleLogo.h"
#include "TitleScene.h"


//	ターゲットのY座標
const float						   TitleLogo::LOGO_TARGET_POSITION_Y = 250.0f;
//	ロゴが動く速度
const float						   TitleLogo::MOVE_LOGO_SPEED		 = 0.02f;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="texture">画像</param>
/// <param name="position">座標</param>
/// <param name="originPosition">真ん中の座標</param>
TitleLogo::TitleLogo(
	ID3D11ShaderResourceView* texture, 
	const DirectX::SimpleMath::Vector2& position, 
	const DirectX::SimpleMath::Vector2& originPosition
)
	:m_texture(texture),
	m_position(position),
	m_originPosition(originPosition),
	m_angle(0.0f),
	m_state(0)
{
	//	大きさを初期化する
	m_scale = TitleUI::BASE_SCALE;;
}

/// <summary>
/// デストラクタ
/// </summary>
TitleLogo::~TitleLogo()
{
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="state">タイトルのステート</param>
void TitleLogo::Update(const int& state)
{
	m_state = state;
	// アイドリング状態の更新
	UpdateIdle();
	// アイドリング状態以外の更新
	UpdateNoteIdle();
}

/// <summary>
/// 更新処理
/// </summary>
void TitleLogo::Draw()
{
	//	描画を任せる
	TitleUI::Draw
	(
		m_texture, 
		m_position, 
		DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f),
		m_angle, 
		m_originPosition,
		m_scale
	);
}

/// <summary>
/// アイドリング状態の更新
/// </summary>
void TitleLogo::UpdateIdle()
{
	TitleScene::STATE state = static_cast<TitleScene::STATE>(m_state);

	//	アイドリング以外は帰れ
	if (state != TitleScene::STATE::IDLE)		return;

	float elapsedTime = MyLib::ElapsedTime::GetInstance()->GetElapsedTime();

	//	ロゴの画像を縮小させる
	m_scale.x = BASE_SCALE.x + 0.1f * sinf(elapsedTime);
}

/// <summary>
/// アイドリング状態以外の更新
/// </summary>
void TitleLogo::UpdateNoteIdle()
{
	TitleScene::STATE state = static_cast<TitleScene::STATE>(m_state);
	//	アイドリンなら帰れ
	if (state == TitleScene::STATE::IDLE)		return;

	//	ロゴの大きさをもとの大きさに戻す
	m_scale = DirectX::SimpleMath::Vector2::Lerp(m_scale, BASE_SCALE, MOVE_LOGO_SPEED);
	
	//	ロゴ少し上に動かす
	m_position.y = Utility::Lerp(m_position.y, LOGO_TARGET_POSITION_Y, MOVE_LOGO_SPEED);
}