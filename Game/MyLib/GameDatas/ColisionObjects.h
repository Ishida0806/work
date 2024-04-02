
#pragma once

#include "Game/MyLib/Scenes/PlayScene/Object/Object.h"
#include "Game/MyLib/Scenes/PlayScene/Object/Player.h"
#include "Game/MyLib/Scenes/PlayScene/Object/Wall/Wall.h"
#include "Game/MyLib/Scenes/PlayScene/Object/Item/Item.h"
#include "Game/MyLib/Scenes/PlayScene/Object/Bullet/Bullet.h"
#include "Game/MyLib/Scenes/PlayScene/Object/Enemy/BossEnemy.h"
#include "Game/MyLib/Scenes/PlayScene/Object/Enemy/TackleEnemy.h"
#include "Game/MyLib/Scenes/PlayScene/Object/Enemy/NormalEnemy.h"

class PlayScene;
class Object;
class Player;
class Bullet;
class Wall;
class Item;
class Enemy;

class ColisionObjects
{
public:



private:
	//	プレイシーンのポインター
	PlayScene*											m_playScene;
	//	プレイヤーのポインター
	Player*												m_player;
	//	ボスのポインター
	std::vector<std::shared_ptr<Enemy>>&				m_enemys;
	//	砲弾配列のポインター
	std::vector<std::unique_ptr<Bullet>>&				m_bullets;
	//	壁たちのポインター
	std::vector<std::unique_ptr<Wall>>&					m_walls;
	//	アイテム
	std::vector<std::shared_ptr<Item>>&					m_items;

public:
	 
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="playScene">プレイシーン</param>
	/// <param name="player">プレイヤー<</param>
	/// <param name="enemys">敵達</param>
	/// <param name="bullets">弾</param>
	/// <param name="walls">壁</param>
	/// <param name="items">アイテム</param>
	ColisionObjects
	(
		PlayScene*								   playScene,
		Player*									   player,
		std::vector<std::shared_ptr<Enemy>>*	   enemys,
		std::vector<std::unique_ptr<Bullet>>*	   bullets,
		std::vector<std::unique_ptr<Wall>>*		   walls,
		std::vector<std::shared_ptr<Item>>*		   items
	);

	void UpdateAbility();
	void UpdateColision();
	void UpdateItem();

private:


	//	弾たちの当たり判定
	void ColisionBullets();
	//	プレイヤーの当たり判定
	void ColisionPlayer();
	//	敵たちの当たり判定
	void ColisionEnemies();
	//	敵たちのサークル当たり判定
	void InEnemiesSearch();
	//	敵たちの特殊効果
	void InEnemiesAbility();
};