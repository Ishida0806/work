//
//		File Name ： Gear.cpp
//		Production： 2023/11/11
//		Author　　： 石田 恭一
// 
//		タイトルのギアの更新・描画を行う
//
#include "pch.h"
#include "Gear.h"

#include "TitleScene.h"

//	ロゴが動く速度
const float						   Gear::MOVE_GEAR_SPEED	  = 0.02f;
//	ギア速度
const float						   Gear::GEAR_SPEED			  = 2.0f;
//	ギアを回る速度
const float						   Gear::MOVE_GEAR_RADIAN	  = -1.0f;
//	ギアの目標座標
const float						   Gear::GEAR_TARGET_POSITION = 100.0f;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="texture">画像</param>
/// <param name="position">座標</param>
/// <param name="originPosition">真ん中の座標</param>
/// <param name="Direction">向き</param>
Gear::Gear(ID3D11ShaderResourceView* texture, const DirectX::SimpleMath::Vector2& position, const DirectX::SimpleMath::Vector2& originPosition, const Direction& direction)
	:m_texture(texture),
	m_position(position),
	m_originPosition(originPosition),
	m_isDirection(direction),
	m_angle(0.0f),
	m_state(0)
{
	//	大きさを戻す
	m_scale = TitleUI::BASE_SCALE;
}

/// <summary>
/// デストラクタ
/// </summary>
Gear::~Gear()
{
}


/// <summary>
/// 更新処理
/// </summary>
/// <param name="state">タイトルのステート</param>
void Gear::Update(const int& state)
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
void Gear::Draw()
{
	//	描画を任せる
	TitleUI::Draw
	(
		m_texture,
		m_position,
		DirectX::SimpleMath::Color(0.0f, 0.0f, 0.0f, 0.5f),
		m_angle,
		m_originPosition,
		m_scale
	);
}

/// <summary>
/// アイドリング状態の更新
/// </summary>
void Gear::UpdateIdle()
{
	TitleScene::STATE state = static_cast<TitleScene::STATE>(m_state);

	//	アイドリング以外は帰れ
	if (state != TitleScene::STATE::IDLE)		return;
	//	経過時間を取得する
	float elapsedTime = MyLib::ElapsedTime::GetInstance()->GetElapsedTime();
	//	歯車を回す
	m_angle = DirectX::XMConvertToRadians(elapsedTime * GEAR_SPEED);

	//	逆向きにする
	if (m_isDirection == Direction::Right)	m_angle *= MOVE_GEAR_RADIAN;
}

/// <summary>
/// アイドリング状態以外の更新
/// </summary>
void Gear::UpdateNoteIdle()
{
	TitleScene::STATE state = static_cast<TitleScene::STATE>(m_state);
	//	アイドリンなら帰れ
	if (state == TitleScene::STATE::IDLE)		return;
	//	向きによって場所を変える
	switch (m_isDirection)
	{
	case Gear::Direction::Right:	m_position = DirectX::SimpleMath::Vector2::Lerp(m_position, DirectX::SimpleMath::Vector2(m_position.x + GEAR_TARGET_POSITION, m_position.y + GEAR_TARGET_POSITION), MOVE_GEAR_SPEED);	break;
	case Gear::Direction::Left:		m_position = DirectX::SimpleMath::Vector2::Lerp(m_position, DirectX::SimpleMath::Vector2(m_position.x - GEAR_TARGET_POSITION, m_position.y + GEAR_TARGET_POSITION), MOVE_GEAR_SPEED);	break;
	case Gear::Direction::OverID:																																															break;
	default:																																																				break;
	}
}
