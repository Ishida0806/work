//
//		File Name �F MiniMap.cpp
//		Production�F 202311/30
//		Author�@�@�F �Γc ����	
// 
//		�~�j�}�b�v�̎����E�X�V���s��
//	
#include "pch.h"
#include "MiniMap.h"

#include "../Object/Player.h"
#include "../Object/Enemy/Enemy.h"

//	�}�b�v�̐^�񒆂̍��W
const DirectX::SimpleMath::Vector2 MiniMap::MAP_ORIGIN_POSITION			= DirectX::SimpleMath::Vector2(131.0f, 132.5f);
//	�v���C���[�̐^�񒆂̍��W
const DirectX::SimpleMath::Vector2 MiniMap::PLAYER_ORIGIN_POSITION		= DirectX::SimpleMath::Vector2(7.0f, 14.5f);
//	�G�̐^�񒆂̍��W
const DirectX::SimpleMath::Vector2 MiniMap::ENEMY_ORIGIN_POSITION		= DirectX::SimpleMath::Vector2(7.5f, 7.5f);
//	�A�C�e���̐^�񒆂̍��W
const DirectX::SimpleMath::Vector2 MiniMap::ITEM_ORIGIN_POSITION		= DirectX::SimpleMath::Vector2(7.5f, 7.5f);
//	�傫���̔{��
const float						   MiniMap::BOSS_SCALE_MAGNIFICATION	= 1.5f;
//	���ꂽ�ꏊ�̍ő�l
const float						   MiniMap::DISTANCE_MAX			    = 30.0f;
//	���W��傫������
const float						   MiniMap::POSITION_MAGNIFICATION		= 1.7f;
//	�I�t�Z�b�g�l��Y���W
const float						   MiniMap::PLAYER_POSITION_Y			= 2.0f;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="player">�v���C���[<</param>
/// <param name="item">�A�C�e��</param>
MiniMap::MiniMap(Player* player, std::vector<std::shared_ptr<Item>>& item)
	:m_player(player),
	m_items(item),
	m_spriteBatch(nullptr),
	m_playerMap(nullptr),
	m_enemyMap(nullptr),
	m_itemMap(nullptr)
{
	int w, h;
	//	��ʃT�C�Y���擾����
	MyLib::ScreenResources::GetInstance()->GetScreenSize(w, h);
	//	�}�b�v�̍��W
	m_mapPosition = DirectX::SimpleMath::Vector2(w - MAP_ORIGIN_POSITION.x, MAP_ORIGIN_POSITION.y);
	//	�}�b�v�̑傫��
	m_mapScale    = DirectX::SimpleMath::Vector2::One;
	//	�v���C���[�̉摜���擾����
	m_playerMap   = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"playerMap");
	//	�G�̉摜���擾����
	m_enemyMap	  = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"enemyMap");
	//	�A�C�e���̉摜���擾����
	m_itemMap	  = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"itemMap");
	//	�X�v���C�g�o�b�`
	m_spriteBatch = MyLib::ScreenResources::GetInstance()->GetSpriteBatch();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
MiniMap::~MiniMap()
{
}

/// <summary>
/// �}�b�v���X�V����
/// </summary>
/// <param name="timer">�^�C�}�[</param>
/// <param name="enemy">�G�̃|�C���^�[</param>
void MiniMap::UpdateMap(const DX::StepTimer& timer, Enemy* enemy)
{
	UNREFERENCED_PARAMETER(timer);

	DirectX::SimpleMath ::Vector3 enemyPosition  = enemy->GetPosition();
	DirectX::SimpleMath ::Vector3 playerPosition = m_player->GetPosition();
	//	�������Z�o����
	DirectX::SimpleMath::Vector3 direction = playerPosition - enemyPosition;

	//	���܂�ɂ��傫��������W�͏R��
	if (abs(direction.x) <= DISTANCE_MAX || abs(direction.z) <= DISTANCE_MAX)
	{
		m_enemies.push_back(enemy);
	}	
}

/// <summary>
/// �`����s��
/// </summary>
void MiniMap::Draw()
{
	//	�~�j�}�b�v�̕`����s��
	m_spriteBatch->Draw
	(
		MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"map"),
		m_mapPosition,
		nullptr,
		DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 0.5), 
		0.0f,
		MAP_ORIGIN_POSITION
	);

	// �G���~�j�}�b�v��ɕ`�悷��
	RenderMiniMapEnemy();

	// �A�C�e�����~�j�}�b�v��`�悷��
	RenderMiniMapItem();

	//	�^�񒆂ɏo��
	//	�`����s��
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
/// �G���~�j�}�b�v��ɕ`�悷��
/// </summary>
void MiniMap::RenderMiniMapEnemy()
{
	//	�����`����s��
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

		//	�����傫������
		x *= POSITION_MAGNIFICATION;
		y *= POSITION_MAGNIFICATION;

		DirectX::SimpleMath::Vector2  position = DirectX::SimpleMath::Vector2(m_mapPosition.x - x, m_mapPosition.y - y);

		//	�^�񒆂ɏo��
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
	//	�G�̃N���A
	m_enemies.clear();
}

/// <summary>
/// �A�C�e�����~�j�}�b�v��`�悷��
/// </summary>
void MiniMap::RenderMiniMapItem()
{
	//	�A�C�e���̕`��
	for (const auto& item : m_items)
	{
		float x = m_player->GetPosition().x - item->GetPosition().x;
		float y = m_player->GetPosition().z - item->GetPosition().z;

		//	�����傫������
		x *= POSITION_MAGNIFICATION;
		y *= POSITION_MAGNIFICATION;

		DirectX::SimpleMath::Vector2  position = DirectX::SimpleMath::Vector2(m_mapPosition.x - x, m_mapPosition.y - y);

		//	�^�񒆂ɏo��
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
