//
//		File Name ： PlayerExperiencePointUI.cpp
//		Production： 2023/11/30
//		Author　　： 石田 恭一	
// 
//		経験値を管理取得する
//	
#include "pch.h"
#include "PlayerExperiencePointUI.h"

#include "Game/MyLib/Scenes/PlayScene/Object/Player.h"

//	MAX画像の座標
const  DirectX::SimpleMath::Vector2  PlayerExperiencePointUI::MAX_POSITION = { 300.0f,80.0f };
//	体力バー用の座標
const float							 PlayerExperiencePointUI::EXP_POS	   = 418.0f;
//	体力バーのX座標
const int							 PlayerExperiencePointUI::EXP_IX	   = 153;
//	体力バーのY座標
const int							 PlayerExperiencePointUI::EXP_IY	   = 95;
//	体力バーの高さ
const int							 PlayerExperiencePointUI::EXP_IH	   = 15;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="player">プレイヤー</param>
PlayerExperiencePointUI::PlayerExperiencePointUI(Player* player)
	:m_player(player),
	m_barTexture(nullptr),
	m_maxTexture(nullptr),
	m_exBar(0.0f)
{
	//	バー画像
	m_barTexture = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"HPBar");
	//	経験値MAX画像
	m_maxTexture = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"EXPmax");
}

/// <summary>
/// デストラクタ
/// </summary>
PlayerExperiencePointUI::~PlayerExperiencePointUI()
{
}

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="timer">タイマー</param>
void PlayerExperiencePointUI::Update(const DX::StepTimer& timer)
{
	UNREFERENCED_PARAMETER(timer);

	//	経験値
	int exp		= m_player->GetPlayerEXPoint()->GetExperiencePoint();
	//	経験値必要な情報
	int needEXP = m_player->GetPlayerEXPoint()->GetNeedExperiencePoint();
	//	どのくらいの割合？
	float decimal = 0.0f;

	//	レベルが最大値を超えていたら帰れ
	if (m_player->GetPlayerLevel() >= m_player->GetPlayerEXPoint()->MAX_PLAYER_LEVEL)	
	{
		//	座標をいれる
		m_exBar = EXP_POS;
		return;
	}

	//	経験値が0なら行わない
	if (exp <= 0.0f)
	{
		m_exBar = 0.0f;	
	}
	else
	{
		//	体力によって場所をずらす
		decimal = static_cast<float>(exp) / static_cast<float>(needEXP);
	}

	//	徐々に移動
	m_exBar = Utility::Lerp(0.0f, static_cast<float>(EXP_POS), decimal);
}

/// <summary>
/// 描画する
/// </summary>
void PlayerExperiencePointUI::Draw()
{	
	DirectX::SpriteBatch* spriteBatch = MyLib::ScreenResources::GetInstance()->GetSpriteBatch();

	//	バー画像の描画
	spriteBatch->Draw
	(
		m_barTexture,
		DirectX::SimpleMath::Rectangle(EXP_IX, EXP_IY, static_cast<int>(m_exBar), EXP_IH),
		DirectX::Colors::Blue
	);
	
	//	レベルが最大値と同じなら描画
	if (m_player->GetPlayerLevel() == m_player->GetPlayerEXPoint()->MAX_PLAYER_LEVEL)
	{
		//	MAX画像の描画
		spriteBatch->Draw
		(
			m_maxTexture,
			MAX_POSITION
		);
	}
}
