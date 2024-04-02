//
//		File Name ： TitleStringUI.cpp
//		Production： 2023/11/11
//		Author　　： 石田 恭一
// 
//		タイトルの案内の描画・更新
//
#include "pch.h"
#include "TitleStringUI.h"

#include "TitleScene.h"


//	揺らす大きさ
const float					      TitleStringUI::SHAKE_TEXTURE					= 0.1f;
//	揺らす速さ
const float					      TitleStringUI::SHAKE_SPEED					= 2.5f;
//	角度を戻す速度
const float						  TitleStringUI::MOVE_BACKANGLE_SPEED			= 0.1f;
//	プレイゲームの真ん中座標
const DirectX::SimpleMath::Vector2 TitleStringUI::PLAYGAME_ORIGIN_POSITION		= DirectX::SimpleMath::Vector2(137.5f, 40.5f);
//	コンフィグの真ん中座標
const DirectX::SimpleMath::Vector2 TitleStringUI::CONFIG_ORIGIN_POSITION		= DirectX::SimpleMath::Vector2(100.5f, 40.5f);
//	エンドゲームの真ん中座標
const DirectX::SimpleMath::Vector2 TitleStringUI::ENDGAME_ORIGIN_POSITION		= DirectX::SimpleMath::Vector2(123.0f, 40.5f);

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="texture">画像</param>
/// <param name="texture">OFF時の画像</param>
/// <param name="position">座標</param>
/// <param name="index">番号</param>
TitleStringUI::TitleStringUI(
	ID3D11ShaderResourceView* texture, 
	ID3D11ShaderResourceView* offTexture, 
	const DirectX::SimpleMath::Vector2& position,
	const int& index
)
	:m_texture(texture),
	m_offTexture(offTexture),
	m_position(position),
	m_type(index),
	m_angle(0.0f),
	m_offsetX(0.0f),
	m_state(0)
{
	//	型
	TitleScene::STATE type = static_cast<TitleScene::STATE>(index);

	//	種類によって変える
	switch (type)
	{
	case TitleScene::STATE::IDLE:													break;
	case TitleScene::STATE::PLAY:	m_originPosition = PLAYGAME_ORIGIN_POSITION;	break;
	case TitleScene::STATE::CONFIG:	m_originPosition = CONFIG_ORIGIN_POSITION;		break;
	case TitleScene::STATE::END:	m_originPosition = ENDGAME_ORIGIN_POSITION;		break;
	case TitleScene::STATE::NONE:													break;
	default:																		break;
	}

	//	大きさを初期化する
	m_scale = TitleUI::BASE_SCALE;
}

/// <summary>
/// デストラクタ
/// </summary>
TitleStringUI::~TitleStringUI()
{
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="state">セレクトされた番号</param>
void TitleStringUI::Update(const int& state)
{
	m_state = state;

	SelectUI();
}

/// <summary>
/// 描画処理
/// </summary>
void TitleStringUI::Draw()
{	
	TitleScene::STATE state = static_cast<TitleScene::STATE>(m_state);

	//	アイドリング状態なら帰れ
	if (state == TitleScene::STATE::IDLE)	return;

	//	型
	TitleScene::STATE Istate = static_cast<TitleScene::STATE>(m_type);

	if (state == Istate)
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
	else
	{
		//	描画を任せる
		TitleUI::Draw
		(
			m_offTexture,
			m_position,
			DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f),
			m_angle,
			m_originPosition,
			m_scale
		);
	}
}

/// <summary>
/// セレクトされた時の更新処理
/// </summary>
void TitleStringUI::SelectUI()
{
	//	現在の型
	TitleScene::STATE state = static_cast<TitleScene::STATE>(m_state);
	//	型
	TitleScene::STATE Istate = static_cast<TitleScene::STATE>(m_type);

	//	アイドリング状態なら帰れ
	if (state == TitleScene::STATE::IDLE)	return;

	if (state == Istate)
	{
		//	経過時間を取得する
		float elapsedTime = MyLib::ElapsedTime::GetInstance()->GetElapsedTime();

		//	角度を上下運動させる
		m_angle = SHAKE_TEXTURE * sinf(elapsedTime * SHAKE_SPEED);
	}
	else
	{
		//	ゆっくり戻す
		m_angle = Utility::Lerp(m_angle, 0.0f, MOVE_BACKANGLE_SPEED);
	}
}
