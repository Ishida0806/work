//
//		File Name �F ItemManager.cpp
//		Production�F 2023/12/1
//		Author�@�@�F �Γc ����	
//
#include "pch.h"
#include "ItemManager.h"
#include "ItemFactory.h"

//	�o������ꏊ
const float ItemManager::SPAWN_PLACE = 20.0f;
//	�o�����鎞��
const float ItemManager::SPAWN_TIME  = 30.0f;
//	�������E��
const int	ItemManager::SPAWN_ITEM = 3;

/// <summary>
/// �R���X�g���N�^
/// </summary>
ItemManager::ItemManager()
	:m_spwanItemTime(0.0f)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ItemManager::~ItemManager()
{
}

/// <summary>
/// ����������
/// </summary>
void ItemManager::Initialize()
{
#pragma region DEBUG
	//m_items.push_back
	//(
	//	ItemFactory::CreatePowerUPItem
	//	(
	//		DirectX::SimpleMath::Vector3(
	//			Utility::CreateRandom(-SPAWN_PLACE, SPAWN_PLACE),
	//			1.0f,
	//			Utility::CreateRandom(-SPAWN_PLACE, SPAWN_PLACE)),
	//		RecoveryItem::ItemType::PowUp
	//	)
	//);
	//m_items.push_back
	//(
	//	ItemFactory::CreateRecoveryItem
	//	(
	//		DirectX::SimpleMath::Vector3(
	//			Utility::CreateRandom(-SPAWN_PLACE, SPAWN_PLACE),
	//			1.0f,
	//			Utility::CreateRandom(-SPAWN_PLACE, SPAWN_PLACE)),
	//		RecoveryItem::ItemType::Recovery
	//	)
	//);	
	//m_items.push_back
	//(
	//	ItemFactory::CreateReflectItem
	//	(
	//		DirectX::SimpleMath::Vector3(
	//			Utility::CreateRandom(-SPAWN_PLACE, SPAWN_PLACE),
	//			1.0f,
	//			Utility::CreateRandom(-SPAWN_PLACE, SPAWN_PLACE)),
	//		RecoveryItem::ItemType::Reflect
	//	)
	//);

#pragma endregion
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void ItemManager::Update(const DX::StepTimer& timer)
{
	//	�擾�����A�C�e���������
	TookItems();

	for (const auto& item : m_items)
	{
		item->Update(timer);
	}

	// �A�C�e�����o������
	SpawnItem(timer);
}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="view">�r���[</param>
/// <param name="proj">�v���W�F�N�V����</param>
void ItemManager::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	for (const auto& item : m_items)
	{
		item->Render(view, proj);
	}
}

/// <summary>
/// �I������
/// </summary>
void ItemManager::Finalize()
{
	for (const auto& item : m_items)
	{
		item->Finalize();
	}
}

/// <summary>
/// �擾�����A�C�e���������
/// </summary>
void ItemManager::TookItems()
{
	// �����𖞂����I�u�W�F�N�g���폜
	m_items.erase(
		std::remove_if(
			m_items.begin(), m_items.end(),
			[&](const std::shared_ptr<Item>& item)
			{
				if (item->IsTookItem())
				{
					return true;
				}
				return false;
			}),
		m_items.end()
	);
}

/// <summary>
/// �A�C�e�����o������
/// </summary>
void ItemManager::SpawnItem(const DX::StepTimer& timer)
{
	//	�������E���ɂ������Ă���Ȃ�A��
	if (m_items.size() >= SPAWN_ITEM)	return;

	//	�o������Y���W
	float y = 1.0f;
	//	�o�ߎ��Ԃ𑫂�
	m_spwanItemTime += static_cast<float>(timer.GetElapsedSeconds());

	if (m_spwanItemTime >= SPAWN_TIME)
	{
		//	�X�|�[�����Ԃ̓��Z�b�g����
		m_spwanItemTime = 0.0f;

		//	0�`6�̒l�������_���Ŏ擾����
		int random = rand() % 6;

		//	�����_���łǂ��炩��n�߂邩���߂�
		if (random >= 0 && random <= 3)
		{
			m_items.push_back
			(
				ItemFactory::CreatePowerUPItem
				(
					DirectX::SimpleMath::Vector3(
						Utility::CreateRandom(-SPAWN_PLACE, SPAWN_PLACE),
						y,
						Utility::CreateRandom(-SPAWN_PLACE, SPAWN_PLACE)),
					RecoveryItem::ItemType::PowUp
				)
			);
		}
		//	�����_���łǂ��炩��n�߂邩���߂�
		else if (random >= 3 && random <= 6)
		{
			m_items.push_back
			(
				ItemFactory::CreateRecoveryItem
				(
					DirectX::SimpleMath::Vector3(
						Utility::CreateRandom(-SPAWN_PLACE, SPAWN_PLACE),
						y,
						Utility::CreateRandom(-SPAWN_PLACE, SPAWN_PLACE)),
					RecoveryItem::ItemType::Recovery
				)
			);
		}
		//else
		//{
		//	m_items.push_back
		//	(
		//		ItemFactory::CreateReflectItem
		//		(
		//			DirectX::SimpleMath::Vector3(
		//				Utility::CreateRandom(-SPAWN_PLACE, SPAWN_PLACE),
		//				y,
		//				Utility::CreateRandom(-SPAWN_PLACE, SPAWN_PLACE)),
		//			RecoveryItem::ItemType::Reflect
		//		)
		//	);
		//}
	}
}