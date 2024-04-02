//
//		File Name �F MiniMap.h
//		Production�F 202311/30
//		Author�@�@�F �Γc ����	
//	
#pragma once
#include "Game/MyLib/Scenes/PlayScene/Object/Item/Item.h"

class Enemy;
class Player;

class MiniMap final
{
	//	�萔
public:

	//	�}�b�v�̐^�񒆂̍��W
	static const DirectX::SimpleMath::Vector2 MAP_ORIGIN_POSITION;
	//	�v���C���[�̐^�񒆂̍��W
	static const DirectX::SimpleMath::Vector2 PLAYER_ORIGIN_POSITION;
	//	�G�̐^�񒆂̍��W
	static const DirectX::SimpleMath::Vector2 ENEMY_ORIGIN_POSITION;
	//	�A�C�e���̐^�񒆂̍��W
	static const DirectX::SimpleMath::Vector2 ITEM_ORIGIN_POSITION;
	//	�傫���̔{��
	static const float						  BOSS_SCALE_MAGNIFICATION;
	//	���ꂽ�ꏊ�̍ő�l
	static const float						  DISTANCE_MAX;
	//	���W��傫������
	static const float						  POSITION_MAGNIFICATION;
	//	�I�t�Z�b�g�l��Y���W
	static const float						  PLAYER_POSITION_Y;


	//	�ϐ�
private:
	//	�v���C���[
	Player*								m_player;
	//	�G
	std::vector<Enemy*>					m_enemies;
	//	�A�C�e��
	std::vector<std::shared_ptr<Item>>& m_items;
	//	�}�b�v�̍��W
	DirectX::SimpleMath::Vector2		m_mapPosition;
	//	�G�̑傫��
	DirectX::SimpleMath::Vector2		m_mapScale;
	//	�v���C���[�̃}�b�v
	ID3D11ShaderResourceView*			m_playerMap;
	//	�G�̃}�b�v
	ID3D11ShaderResourceView*			m_enemyMap;
	//	�A�C�e���̃}�b�v
	ID3D11ShaderResourceView*			m_itemMap;
	//	�X�v���C�g�o�b�`
	DirectX::SpriteBatch*				m_spriteBatch;

	//	�֐�
public:
	
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="player">�v���C���[<</param>
	/// <param name="item">�A�C�e��</param>
	MiniMap(Player* player , std::vector<std::shared_ptr<Item>>& item);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~MiniMap();

	/// <summary>
	/// �}�b�v���X�V����
	/// </summary>
	/// <param name="timer">�^�C�}�[</param>
	/// <param name="enemy">�G</param>
	void UpdateMap(const DX::StepTimer& timer, Enemy* enemy);

	/// <summary>
	/// �`�悷��
	/// </summary>
	void Draw();

	//	���ߍ��݊֐�
private:

	/// <summary>
	/// �G���~�j�}�b�v��ɕ`�悷��
	/// </summary>
	void RenderMiniMapEnemy();

	/// <summary>
	/// �A�C�e�����~�j�}�b�v��`�悷��
	/// </summary>
	void RenderMiniMapItem();
};