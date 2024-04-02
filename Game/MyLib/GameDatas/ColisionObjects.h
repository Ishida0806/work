
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
	//	�v���C�V�[���̃|�C���^�[
	PlayScene*											m_playScene;
	//	�v���C���[�̃|�C���^�[
	Player*												m_player;
	//	�{�X�̃|�C���^�[
	std::vector<std::shared_ptr<Enemy>>&				m_enemys;
	//	�C�e�z��̃|�C���^�[
	std::vector<std::unique_ptr<Bullet>>&				m_bullets;
	//	�ǂ����̃|�C���^�[
	std::vector<std::unique_ptr<Wall>>&					m_walls;
	//	�A�C�e��
	std::vector<std::shared_ptr<Item>>&					m_items;

public:
	 
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="playScene">�v���C�V�[��</param>
	/// <param name="player">�v���C���[<</param>
	/// <param name="enemys">�G�B</param>
	/// <param name="bullets">�e</param>
	/// <param name="walls">��</param>
	/// <param name="items">�A�C�e��</param>
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


	//	�e�����̓����蔻��
	void ColisionBullets();
	//	�v���C���[�̓����蔻��
	void ColisionPlayer();
	//	�G�����̓����蔻��
	void ColisionEnemies();
	//	�G�����̃T�[�N�������蔻��
	void InEnemiesSearch();
	//	�G�����̓������
	void InEnemiesAbility();
};