
#include "pch.h"
#include "LevelCardEffect.h"

#include "LevelCard.h"
#include "../Object/Player.h"

//	カードの真ん中の座標
const DirectX::SimpleMath::Vector2 LevelCardEffect::CARD_ORIGIN_POSITION	  = { 131.0f,170.0f };
//	カードの座標
const DirectX::SimpleMath::Vector2 LevelCardEffect::CARD_POSITION			  = { 250.0f,350.0f };
//	マウスカーソル接触後のスケール
const DirectX::SimpleMath::Vector2 LevelCardEffect::CARD_SCALE			  = { 1.3f,1.3f };
//	カードのずらす座標
const float						LevelCardEffect::OFFSET_POSITION		  = 400.0f;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="player">プレイヤー</param>
/// <param name="type">タイプ/param>
LevelCardEffect::LevelCardEffect(Player* player, const int& type)
	:m_player(player),
	m_type(type),
	m_texture(nullptr),
	m_clickAble(false),
	m_isReady(false)
{
}

/// <summary>
/// デストラクタ
/// </summary>
LevelCardEffect::~LevelCardEffect()
{
}

/// <summary>
/// 初期化処理
/// </summary>
void LevelCardEffect::Initialize()
{
	//	タイプ
	LevelCard::CardType type = static_cast<LevelCard::CardType>(m_type);

	//	タイプごとにカード入れる
	switch (type)
	{
	case LevelCard::CardType::PowerUP:		m_texture = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"PowerUPCard");	 break;
	case LevelCard::CardType::HealthUP:		m_texture = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"HealthUPCard"); break;
	case LevelCard::CardType::SpeedUP:		m_texture = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"SpeedUPCard");  break;
	default:																														 break;
	}

	//	座標をずらす
	m_targetPosition = DirectX::SimpleMath::Vector2(CARD_POSITION.x + (OFFSET_POSITION * static_cast<float>(m_type)), CARD_POSITION.y);

	//	座標を指定地に
	ResetPosition();

	//	大きさは1
	m_scale = DirectX::SimpleMath::Vector2::One;
}

/// <summary>
/// 更新処理
/// </summary>
void LevelCardEffect::Update()
{
	//	準備状態なら帰れ
	if (m_isReady)	return;

	// 大きさをかえる
	ResizeScale();

	//	目標座標へいく
	m_position = DirectX::SimpleMath::Vector2::Lerp(m_position, m_targetPosition, 0.05f);
}

/// <summary>
/// キー選択されている
/// </summary>
void LevelCardEffect::SelectKey()
{
	m_clickAble = true;
}

/// <summary>
/// キー選択されていない
/// </summary>
void LevelCardEffect::SelectNotKey()
{
	m_clickAble = false;
}

/// <summary>
/// 退出処理
/// </summary>
void LevelCardEffect::Exit()
{
	if (!m_isReady) return;

	// 大きさをかえる
	ResizeScale();

	m_position.y += 15.0f;

	if (m_position.y >= 1000.0f)
	{
		//	座標を指定地に
		ResetPosition();
		//	準備終了する
		m_isReady = false;
	}
}

/// <summary>
/// 描画する
/// </summary>
void LevelCardEffect::Draw()
{
	MyLib::ScreenResources::GetInstance()->GetSpriteBatch()->Draw
	(
		m_texture,
		m_position,
		nullptr,
		DirectX::Colors::White,
		0.0f,
		CARD_ORIGIN_POSITION,
		m_scale
	);
}


/// <summary>
/// カードの中にマウスカーソルが入って来た
/// </summary>
/// <param name="mousePosition">マウスカーソルの座標</param>
bool LevelCardEffect::InMouseCarsor(const DirectX::SimpleMath::Vector2& mousePosition)
{
	//	準備状態なら帰れ
	if (m_isReady)	return false;

	//	左側の大きさX
	float leftExtensX  = m_position.x  - CARD_ORIGIN_POSITION.x;
	//	左側の大きさY
	float leftExtensY  = m_position.y  - CARD_ORIGIN_POSITION.y;
	//	右側の大きさX
	float rightExtensX = m_position.x + CARD_ORIGIN_POSITION.x;
	//	右側の大きさY
	float rightExtensY = m_position.y + CARD_ORIGIN_POSITION.y;

	if ( 
		leftExtensX  < mousePosition.x && leftExtensY  < mousePosition.y &&
		rightExtensX > mousePosition.x && rightExtensY > mousePosition.y
		)
	{	
		//	最初だけ音を鳴らす
		if(!m_clickAble)
			AudioManager::GetInstance()->PlaySoundEffectSE(L"inCard");

		m_clickAble = true;

		return true;
	}
	else
	{
		m_clickAble = false;
	}

	return false;
}

/// <summary>
/// クリックされた
/// </summary>
void LevelCardEffect::Click()
{
	//	準備状態なら帰れ
	if (m_isReady)	return;

	//	タイプ
	LevelCard::CardType type = static_cast<LevelCard::CardType>(m_type);

	//	タイプ		
	switch (type)
	{
	case LevelCard::CardType::PowerUP:
		//	音を鳴らす
		AudioManager::GetInstance()->PlaySoundEffectSE(L"powerCardUP");
		//	プレイヤーの筋力を上げる
		m_player->UpPower();
		break;
	case LevelCard::CardType::HealthUP:	
		//	音を鳴らす
		AudioManager::GetInstance()->PlaySoundEffectSE(L"healthCardUP");
		//	プレイヤーの最大体力を上げる
		m_player->UpMaxHP();
		break;
	case LevelCard::CardType::SpeedUP:
		//	音を鳴らす
		AudioManager::GetInstance()->PlaySoundEffectSE(L"speedCardUP");
		//	プレイヤーの速度を上げる
		m_player->UpSpeed();	 
		break;
	default:													 break;
	}

	//	準備状態に
	m_isReady	= true;
	m_clickAble = false;
}

/// <summary>
/// 座標を指定地に
/// </summary>
void LevelCardEffect::ResetPosition()
{
	//	X座標はずらしたままで
	m_position.x = m_targetPosition.x;
	//	Y座標を上にする
	m_position.y = -OFFSET_POSITION;
}

/// <summary>
/// 大きさをかえる
/// </summary>
void LevelCardEffect::ResizeScale()
{
	if (m_clickAble)
	{
		m_scale = DirectX::SimpleMath::Vector2::Lerp(m_scale, CARD_SCALE, 0.1f);
	}
	else
	{
		m_scale = DirectX::SimpleMath::Vector2::Lerp(m_scale, DirectX::SimpleMath::Vector2::One, 0.1f);
	}
}

/// <summary>
/// クリックが押された
/// </summary>
void LevelCardEffect::SetClick()
{
	//	準備状態じゃないなら帰れ
	if (m_isReady)	return;

	m_isReady   = true;
	m_clickAble = false;
}