//
//		File Name ： MiniMap.h
//		Production： 202311/30
//		Author　　： 石田 恭一	
//	
#pragma once
#include "Game/MyLib/Scenes/PlayScene/Object/Item/Item.h"

class Enemy;
class Player;

class MiniMap final
{
	//	定数
public:

	//	マップの真ん中の座標
	static const DirectX::SimpleMath::Vector2 MAP_ORIGIN_POSITION;
	//	プレイヤーの真ん中の座標
	static const DirectX::SimpleMath::Vector2 PLAYER_ORIGIN_POSITION;
	//	敵の真ん中の座標
	static const DirectX::SimpleMath::Vector2 ENEMY_ORIGIN_POSITION;
	//	アイテムの真ん中の座標
	static const DirectX::SimpleMath::Vector2 ITEM_ORIGIN_POSITION;
	//	大きさの倍率
	static const float						  BOSS_SCALE_MAGNIFICATION;
	//	離れた場所の最大値
	static const float						  DISTANCE_MAX;
	//	座標を大きくする
	static const float						  POSITION_MAGNIFICATION;
	//	オフセット値のY座標
	static const float						  PLAYER_POSITION_Y;


	//	変数
private:
	//	プレイヤー
	Player*								m_player;
	//	敵
	std::vector<Enemy*>					m_enemies;
	//	アイテム
	std::vector<std::shared_ptr<Item>>& m_items;
	//	マップの座標
	DirectX::SimpleMath::Vector2		m_mapPosition;
	//	敵の大きさ
	DirectX::SimpleMath::Vector2		m_mapScale;
	//	プレイヤーのマップ
	ID3D11ShaderResourceView*			m_playerMap;
	//	敵のマップ
	ID3D11ShaderResourceView*			m_enemyMap;
	//	アイテムのマップ
	ID3D11ShaderResourceView*			m_itemMap;
	//	スプライトバッチ
	DirectX::SpriteBatch*				m_spriteBatch;

	//	関数
public:
	
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="player">プレイヤー<</param>
	/// <param name="item">アイテム</param>
	MiniMap(Player* player , std::vector<std::shared_ptr<Item>>& item);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~MiniMap();

	/// <summary>
	/// マップを更新する
	/// </summary>
	/// <param name="timer">タイマー</param>
	/// <param name="enemy">敵</param>
	void UpdateMap(const DX::StepTimer& timer, Enemy* enemy);

	/// <summary>
	/// 描画する
	/// </summary>
	void Draw();

	//	埋め込み関数
private:

	/// <summary>
	/// 敵をミニマップ上に描画する
	/// </summary>
	void RenderMiniMapEnemy();

	/// <summary>
	/// アイテムをミニマップを描画する
	/// </summary>
	void RenderMiniMapItem();
};