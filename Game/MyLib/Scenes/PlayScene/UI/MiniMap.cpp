//
//		File Name ： MiniMap.cpp
//		Production： 202311/30
//		Author　　： 石田 恭一	
// 
//		ミニマップの実装・更新を行う
//	
#include "pch.h"
#include "MiniMap.h"

#include "../Object/Player.h"
#include "../Object/Enemy/Enemy.h"

//	マップの真ん中の座標
const DirectX::SimpleMath::Vector2 MiniMap::MAP_ORIGIN_POSITION			= DirectX::SimpleMath::Vector2(131.0f, 132.5f);
//	プレイヤーの真ん中の座標
const DirectX::SimpleMath::Vector2 MiniMap::PLAYER_ORIGIN_POSITION		= DirectX::SimpleMath::Vector2(7.0f, 14.5f);
//	敵の真ん中の座標
const DirectX::SimpleMath::Vector2 MiniMap::ENEMY_ORIGIN_POSITION		= DirectX::SimpleMath::Vector2(7.5f, 7.5f);
//	アイテムの真ん中の座標
const DirectX::SimpleMath::Vector2 MiniMap::ITEM_ORIGIN_POSITION		= DirectX::SimpleMath::Vector2(7.5f, 7.5f);
//	大きさの倍率
const float						   MiniMap::BOSS_SCALE_MAGNIFICATION	= 1.5f;
//	離れた場所の最大値
const float						   MiniMap::DISTANCE_MAX			    = 30.0f;
//	座標を大きくする
const float						   MiniMap::POSITION_MAGNIFICATION		= 1.7f;
//	オフセット値のY座標
const float						   MiniMap::PLAYER_POSITION_Y			= 2.0f;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="player">プレイヤー<</param>
/// <param name="item">アイテム</param>
MiniMap::MiniMap(Player* player, std::vector<std::shared_ptr<Item>>& item)
	:m_player(player),
	m_items(item),
	m_spriteBatch(nullptr),
	m_playerMap(nullptr),
	m_enemyMap(nullptr),
	m_itemMap(nullptr)
{
	int w, h;
	//	画面サイズを取得する
	MyLib::ScreenResources::GetInstance()->GetScreenSize(w, h);
	//	マップの座標
	m_mapPosition = DirectX::SimpleMath::Vector2(w - MAP_ORIGIN_POSITION.x, MAP_ORIGIN_POSITION.y);
	//	マップの大きさ
	m_mapScale    = DirectX::SimpleMath::Vector2::One;
	//	プレイヤーの画像を取得する
	m_playerMap   = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"playerMap");
	//	敵の画像を取得する
	m_enemyMap	  = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"enemyMap");
	//	アイテムの画像を取得する
	m_itemMap	  = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"itemMap");
	//	スプライトバッチ
	m_spriteBatch = MyLib::ScreenResources::GetInstance()->GetSpriteBatch();
}

/// <summary>
/// デストラクタ
/// </summary>
MiniMap::~MiniMap()
{
}

/// <summary>
/// マップを更新する
/// </summary>
/// <param name="timer">タイマー</param>
/// <param name="enemy">敵のポインター</param>
void MiniMap::UpdateMap(const DX::StepTimer& timer, Enemy* enemy)
{
	UNREFERENCED_PARAMETER(timer);

	DirectX::SimpleMath ::Vector3 enemyPosition  = enemy->GetPosition();
	DirectX::SimpleMath ::Vector3 playerPosition = m_player->GetPosition();
	//	距離を算出する
	DirectX::SimpleMath::Vector3 direction = playerPosition - enemyPosition;

	//	あまりにも大きすぎる座標は蹴る
	if (abs(direction.x) <= DISTANCE_MAX || abs(direction.z) <= DISTANCE_MAX)
	{
		m_enemies.push_back(enemy);
	}	
}

/// <summary>
/// 描画を行う
/// </summary>
void MiniMap::Draw()
{
	//	ミニマップの描画を行う
	m_spriteBatch->Draw
	(
		MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"map"),
		m_mapPosition,
		nullptr,
		DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 0.5), 
		0.0f,
		MAP_ORIGIN_POSITION
	);

	// 敵をミニマップ上に描画する
	RenderMiniMapEnemy();

	// アイテムをミニマップを描画する
	RenderMiniMapItem();

	//	真ん中に出現
	//	描画を行う
	m_spriteBatch->Draw
	(
		m_playerMap,
		DirectX::SimpleMath::Vector2(m_mapPosition.x, m_mapPosition.y + PLAYER_POSITION_Y),
		nullptr,
		DirectX::Colors::White,
		-m_player->GetRotate().ToEuler().y,
		PLAYER_ORIGIN_POSITION
	);
}

/// <summary>
/// 敵をミニマップ上に描画する
/// </summary>
void MiniMap::RenderMiniMapEnemy()
{
	//	数分描画を行う
	for (const auto& enemy : m_enemies)
	{
		float x = m_player->GetPosition().x - enemy->GetPosition().x;
		float y = m_player->GetPosition().z - enemy->GetPosition().z;

		Object::ObjectType obj = enemy->GetType();

		if (obj == Object::ObjectType::BossEnemy)
		{
			m_mapScale.x = BOSS_SCALE_MAGNIFICATION;
			m_mapScale.y = BOSS_SCALE_MAGNIFICATION;
		}
		else
		{
			m_mapScale.x = 1.0f;
			m_mapScale.y = 1.0f;
		}

		//	少し大きくする
		x *= POSITION_MAGNIFICATION;
		y *= POSITION_MAGNIFICATION;

		DirectX::SimpleMath::Vector2  position = DirectX::SimpleMath::Vector2(m_mapPosition.x - x, m_mapPosition.y - y);

		//	真ん中に出現
		m_spriteBatch->Draw
		(
			m_enemyMap,
			position,
			nullptr,
			DirectX::Colors::White,
			0.0f,
			ENEMY_ORIGIN_POSITION,
			m_mapScale
		);
	}
	//	敵のクリア
	m_enemies.clear();
}

/// <summary>
/// アイテムをミニマップを描画する
/// </summary>
void MiniMap::RenderMiniMapItem()
{
	//	アイテムの描画
	for (const auto& item : m_items)
	{
		float x = m_player->GetPosition().x - item->GetPosition().x;
		float y = m_player->GetPosition().z - item->GetPosition().z;

		//	少し大きくする
		x *= POSITION_MAGNIFICATION;
		y *= POSITION_MAGNIFICATION;

		DirectX::SimpleMath::Vector2  position = DirectX::SimpleMath::Vector2(m_mapPosition.x - x, m_mapPosition.y - y);

		//	真ん中に出現
		m_spriteBatch->Draw
		(
			m_itemMap,
			position,
			nullptr,
			DirectX::Colors::White,
			0.0f,
			ITEM_ORIGIN_POSITION
		);
	}	
}
