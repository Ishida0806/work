
//
//		File Name ： PushSeal.cpp
//		Production： 2023/11/11
//		Author　　： 石田 恭一
//
#include "pch.h"
#include "PushSeal.h"

//	共通の誤差範囲
const float						   PushSeal::ERROR_RANGE		  = 3.5f;
//	共通の速度
const float						   PushSeal:: SEAL_SPEED		  = 0.1f;
//	目標座標
const DirectX::SimpleMath::Vector2 PushSeal::MOVE_TARGET_POSITION = DirectX::SimpleMath::Vector2(700.0f, 290.0f);
//	目標の判子を押す座標
const DirectX::SimpleMath::Vector2 PushSeal::TARGET_PUSH_POSITION = DirectX::SimpleMath::Vector2(700.0f, 380.0f);
//	目標の画面外の座標
const DirectX::SimpleMath::Vector2 PushSeal::TARGET_FAR_POSITION  = DirectX::SimpleMath::Vector2(1500.0f, 380.0f);

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="texture">画像</param>
/// <param name="position">座標</param>
/// <param name="originPosition">画像の真ん中座標</param>
PushSeal::PushSeal(
	const DirectX::SimpleMath::Vector2& position,
	const DirectX::SimpleMath::Vector2& originPosition
)
	:m_position(position),
	m_originPosition(originPosition),
	m_angle(0.0f),
	m_texture(nullptr),
	m_isTop(false),
	m_moveTop(false),
	m_moveDown(false),
	m_stateSeal(PUSHSEAL_STATE::MoveTarget)
{
	m_texture = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"push_seal");
}

/// <summary>
/// デストラクタ
/// </summary>
PushSeal::~PushSeal()
{
}

/// <summary>
/// 更新処理
/// </summary>
void PushSeal::Update()
{	
	//	判子の更新処理を行う
	switch (m_stateSeal)
	{
	case PushSeal::PUSHSEAL_STATE::MoveTarget:	MoveTarget();	break;
	case PushSeal::PUSHSEAL_STATE::Push:		Push();			break;
	case PushSeal::PUSHSEAL_STATE::MoveOut:		MoveOut();		break;
	case PushSeal::PUSHSEAL_STATE::Finish:						break;
	case PushSeal::PUSHSEAL_STATE::OverID:						break;
	default:													break;
	}
}

/// <summary>
/// 描画処理
/// </summary>
void PushSeal::Draw()
{
	//	描画がが必要ないときはしない
	if (m_stateSeal == PUSHSEAL_STATE::Finish)	return;

	//	案内キーの描画
	MyLib::ScreenResources::GetInstance()->GetSpriteBatch()->Draw
	(
		m_texture,
		m_position,
		nullptr,
		DirectX::Colors::White,
		0.0f,
		m_originPosition
	);
}

/// <summary>
/// ターゲットの場所に移動を行う
/// </summary>
void PushSeal::MoveTarget()
{
	//	座標に移動を行う
	m_position = DirectX::SimpleMath::Vector2::Lerp(m_position, MOVE_TARGET_POSITION, SEAL_SPEED);

	//	目標座標付近に来たら次のステートへ
	if (m_position.x >= MOVE_TARGET_POSITION.x - ERROR_RANGE && m_position.y >= MOVE_TARGET_POSITION.y - ERROR_RANGE)
	{
		//	判子の音を再生する
		AudioManager::GetInstance()->PlaySoundEffectSE(L"Result_PushSeal");
		//	次のステートへ
		m_stateSeal = PUSHSEAL_STATE::Push;
	}
}

/// <summary>
/// スタンプを押す
/// </summary>
void PushSeal::Push()
{
	//	下に下がる
	if (!m_moveDown)												m_position = DirectX::SimpleMath::Vector2::Lerp(m_position, TARGET_PUSH_POSITION, SEAL_SPEED);
	if (m_position.y >= TARGET_PUSH_POSITION.y - ERROR_RANGE)		m_moveDown = true;

	//	操作が終了していないなら帰れ
	if (!m_moveDown)	return;

	//	スタンプが押された
	m_isTop = true;

	//	上へあがる
	if (!m_moveTop)													m_position = DirectX::SimpleMath::Vector2::Lerp(m_position, MOVE_TARGET_POSITION, SEAL_SPEED);
	if (m_position.y <= MOVE_TARGET_POSITION.y + ERROR_RANGE)		m_moveTop = true;

	//	操作が終了していないなら帰れ
	if (!m_moveTop)	return;

	//	次のステートへ
	m_stateSeal = PUSHSEAL_STATE::MoveOut;
}

/// <summary>
/// 外へ向かう
/// </summary>
void PushSeal::MoveOut()
{
	//	座標を外に移動
	m_position = DirectX::SimpleMath::Vector2::Lerp(m_position, TARGET_FAR_POSITION, SEAL_SPEED);

	//	目標座標へ行けたら次のステートへ
	if (m_position.x >= TARGET_FAR_POSITION.x - ERROR_RANGE)
		m_stateSeal = PUSHSEAL_STATE::Finish;
}
