//
//		File Name ： PlayerHPBar.cpp
//		Production： 2023/10/3
//		Author　　： 石田 恭一
// 
//		HPバー
// 
#include "pch.h"
#include "PlayerHPBar.h"
#include "Game/MyLib/Scenes/PlayScene/Object/Player.h"	

//	赤
const DirectX::SimpleMath::Color PlayerHPBar::RED	 = DirectX::SimpleMath::Color(1.0, 0.0, 0.0, 1.0f);
//	黄色
const DirectX::SimpleMath::Color PlayerHPBar::YELLOW = DirectX::SimpleMath::Color(1.0, 1.0, 0.0, 1.0f);
//	緑
const DirectX::SimpleMath::Color PlayerHPBar::GREEN  = DirectX::SimpleMath::Color(0.0, 1.0, 0.0, 1.0f);
//	体力バー用の座標
 const int  PlayerHPBar::HP_POS						 = 420;
 //	体力バーのX座標
 const int  PlayerHPBar::HP_IX						 = 147;
 //	体力バーのY座標
 const int  PlayerHPBar::HP_IY						 = 60;
 //	体力バーの高さ
 const int  PlayerHPBar::HP_IH						 = 35;
 //	誤差の範囲
 const int  PlayerHPBar::HP_RANGE_VALUE				 = 5;

/// <summary>
/// コンストラクタ
/// </summary>
PlayerHPBar::PlayerHPBar():
	m_hpPlayerBarUI(nullptr),
	m_pPlayer(nullptr),
	m_screen(nullptr),
	m_resources(nullptr),
	m_isBad(false),
	m_hpBar(0),
	m_nowHpBar(0),
	m_hpState(HP_RENDER_STATE::FINE)
{
}

/// <summary>
/// デストラクタ
/// </summary>
PlayerHPBar::~PlayerHPBar()
{
}

/// <summary>
/// 初期化処理
/// </summary>
void PlayerHPBar::Initialize()
{
	CreateDeviceDependentResources();
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="timer"></param>
void PlayerHPBar::Update(const DX::StepTimer& timer)
{
	UNREFERENCED_PARAMETER(timer);

	//	体力によって場所をずらす
	m_hpBar = HP_POS * m_pPlayer->GetHealth() / m_pPlayer->GetMaxHealth();

	//	段々と減らす
	if (m_nowHpBar > m_hpBar)
	{
		if (m_nowHpBar - m_hpBar > 30)
		{
			m_nowHpBar -= 10;
		}
		else
		{
			m_nowHpBar--;
		}
	}
	else
	{
		if (m_nowHpBar < m_hpBar)
		{

			m_nowHpBar++;
		}
	}

	//	BAD状態の時だけフラグでONに
	if (m_hpState == HP_RENDER_STATE::BAD)
	{
		m_isBad = true;
	}
	else
	{
		m_isBad = false;
	}
}

/// <summary>
/// 描画する
/// </summary>
void PlayerHPBar::Draw()
{
	// 体力バーを描画する
	RenderBar();
}

/// <summary>
/// 体力バーを描画する
/// </summary>
void PlayerHPBar::RenderBar()
{
	//	下の枠を描画する
	m_screen->GetSpriteBatch()->Draw
	(
		m_hpPlayerBarUI,																										//  画像はHP BAR
		DirectX::SimpleMath::Rectangle(HP_IX, HP_IY - HP_RANGE_VALUE, HP_POS + HP_RANGE_VALUE, HP_IH + HP_RANGE_VALUE * 2),		//　座標・大きさは少し大きめに
		DirectX::SimpleMath::Color(0.0, 0.0, 0.0, 0.7f)																			//	色完全真っ白&&背景を薄く
	);

	//	体力の状態によって描画色を変える
	switch (m_hpState)
	{
	//	元気な状態な場合
	case PlayerHPBar::HP_RENDER_STATE::FINE:
	
		m_screen->GetSpriteBatch()->Draw
		(
			m_hpPlayerBarUI,
			DirectX::SimpleMath::Rectangle(HP_IX, HP_IY, m_nowHpBar, HP_IH),
			GREEN
		);
		break;
	
	//	体力が半分を切ったら
	case PlayerHPBar::HP_RENDER_STATE::LITTLE_BAD:
	
		m_screen->GetSpriteBatch()->Draw
		(
			m_hpPlayerBarUI,
			DirectX::SimpleMath::Rectangle(HP_IX, HP_IY, m_nowHpBar, HP_IH),
			YELLOW
		);

		break;
	
	//	1/4以下で
	case PlayerHPBar::HP_RENDER_STATE::BAD:
	
		m_screen->GetSpriteBatch()->Draw
		(
			m_hpPlayerBarUI,
			DirectX::SimpleMath::Rectangle(HP_IX, HP_IY, m_nowHpBar, HP_IH),
			RED
		);
		break;
	
	//	もう死んでいるので描画もしない
	case PlayerHPBar::HP_RENDER_STATE::DEAD:	break;
	default:									break;
	}	
}

/// <summary>
/// プレイヤーのポインターを設定する
/// </summary>
/// <param name="player"></param>
void PlayerHPBar::SetPlayer(Player* player)
{
	m_pPlayer = player;
}

/// <summary>
/// 体力のステート状態を設定する
/// </summary>
/// <param name="state">ステート</param>
void PlayerHPBar::SetHPState(int state)
{
	m_hpState = static_cast<HP_RENDER_STATE>(state);
}

/// <summary>
/// デバイス依存のリソースの初期化
/// </summary>
void PlayerHPBar::CreateDeviceDependentResources()
{
	//	スクリーンリソース
	m_screen = MyLib::ScreenResources::GetInstance();
	//	リソーシーズデータ
	m_resources = MyLib::ResourcesData::GetInstance();
	//	調子の悪いプレイヤーの画像	
	m_hpPlayerBarUI = m_resources->GatShaderResourceView(L"HPBar");
	//	体力バーの初期化
	m_hpBar = HP_POS * m_pPlayer->GetHealth() / m_pPlayer->GetMaxHealth();
	//	体力バーの初期化
	m_nowHpBar = m_hpBar;
}