//
//		File Name ： PlayerUI.cpp
//		Production： 2023/10/2
//		Author　　： 石田 恭一
// 
#include "pch.h"
#include "PlayerUI.h"
#include "../../PlayScene/Object/Player.h"

/// <summary>
/// コンストラクタ
/// </summary>
PlayerUI::PlayerUI()
	:m_screen(nullptr),
	m_resources(nullptr),
	m_pPlayer(nullptr),
	m_goodPlayer(nullptr),
	m_littleBadPlayer(nullptr),
	m_badPlayer(nullptr),
	m_deathPlayer(nullptr),
	m_hpState(HP_RENDER_STATE::FINE)
{
}

/// <summary>
/// デストラクタ
/// </summary>
PlayerUI::~PlayerUI()
{
}

/// <summary>
/// 初期化処理
/// </summary>
void PlayerUI::Initialize()
{
	CreateDeviceDependentResources();
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="timer">タイマー</param>
void PlayerUI::Update(const DX::StepTimer& timer)
{
	UNREFERENCED_PARAMETER(timer);

	//	プレイヤーの体力の最大値を取得する
	int maxPlayerHp = m_pPlayer->GetMaxHealth();
	//	プレイヤーの現在の体力値を取得する
	int nowPlayerHp = m_pPlayer->GetHealth();

	//	プレイヤーの最大値の半分以上なら
	if (maxPlayerHp / 2 <= nowPlayerHp)
	{
		m_hpState = HP_RENDER_STATE::FINE;
	}
	//	プレイヤーの最大値の半分以下 && プレイヤーの最大値の4分の1以上なら
	else if(maxPlayerHp / 2 >= nowPlayerHp && maxPlayerHp / 4 <= nowPlayerHp)
	{
		m_hpState = HP_RENDER_STATE::LITTLE_BAD;
	}
	// プレイヤーの最大値の4分の1以上なら && 0より上なら
	else if(maxPlayerHp / 4 >= nowPlayerHp && 0 < nowPlayerHp)
	{
		m_hpState = HP_RENDER_STATE::BAD;
	}
	//	それ以外は死んでいる
	else 
	{
		m_hpState = HP_RENDER_STATE::DEAD;
	}
}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="spriteBatch">スプライトバッチ</param>
void PlayerUI::Draw()
{
	//	
	m_screen->GetSpriteBatch()->Draw
	(
		MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"PlayerUIBackGround"),
		DirectX::SimpleMath::Vector2::Zero
	);

	//	体力の状態によって描画を変える
	RenderHPState();
}

/// <summary>
/// デバイス依存のリソースの初期化
/// </summary>
void PlayerUI::CreateDeviceDependentResources()
{
	//	スクリーンリソース
	m_screen = MyLib::ScreenResources::GetInstance();
	//	リソーシーズデータ
	m_resources = MyLib::ResourcesData::GetInstance();
	//	調子の悪いプレイヤーの画像	
	m_badPlayer = m_resources->GatShaderResourceView(L"Bad_Player");
	//	調子の良いプレイヤーの画像
	m_goodPlayer = m_resources->GatShaderResourceView(L"Good_Player");
	//	調子の少し悪いプレイヤーの画像
	m_littleBadPlayer = m_resources->GatShaderResourceView(L"Little_Bad");
	//	プレイヤーの死んだときの画像
	m_deathPlayer = m_resources->GatShaderResourceView(L"Death_Player");
}

/// <summary>
/// 体力の状態によって描画を変える
/// </summary>
void PlayerUI::RenderHPState()
{	
	switch (m_hpState)
	{
	case PlayerUI::HP_RENDER_STATE::FINE:
	{
		m_screen->GetSpriteBatch()->Draw(
			m_goodPlayer,
			DirectX::SimpleMath::Vector2::Zero
		);

		break;
	}
	case PlayerUI::HP_RENDER_STATE::LITTLE_BAD:
	{
		m_screen->GetSpriteBatch()->Draw(
			m_littleBadPlayer,
			DirectX::SimpleMath::Vector2::Zero
		);
		break;
	}
	case PlayerUI::HP_RENDER_STATE::BAD:
	{
		m_screen->GetSpriteBatch()->Draw(
			m_badPlayer,
			DirectX::SimpleMath::Vector2::Zero
		);
		break;
	case PlayerUI::HP_RENDER_STATE::DEAD:
	{
		m_screen->GetSpriteBatch()->Draw(
			m_deathPlayer,
			DirectX::SimpleMath::Vector2::Zero
		);
		break;
	}
	}
	default:	break;
	}
}

void PlayerUI::SetPlayer(Player* player)
{
	m_pPlayer = player;
}
