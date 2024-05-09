//
//		File Name ： ItemManager.cpp
//		Production： 2023/12/1
//		Author　　： 石田 恭一	
//
#include "pch.h"
#include "ItemManager.h"
#include "ItemFactory.h"

//	出現する場所
const float ItemManager::SPAWN_PLACE = 20.0f;
//	出現する時間
const float ItemManager::SPAWN_TIME  = 30.0f;
//	生成限界数
const int	ItemManager::SPAWN_ITEM = 3;

/// <summary>
/// コンストラクタ
/// </summary>
ItemManager::ItemManager()
	:m_spwanItemTime(0.0f)
{
}

/// <summary>
/// デストラクタ
/// </summary>
ItemManager::~ItemManager()
{
}

/// <summary>
/// 初期化処理
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
/// 更新処理
/// </summary>
/// <param name="timer">タイマー</param>
void ItemManager::Update(const DX::StepTimer& timer)
{
	//	取得したアイテムを取消す
	TookItems();

	for (const auto& item : m_items)
	{
		item->Update(timer);
	}

	// アイテムを出現する
	SpawnItem(timer);
}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="view">ビュー</param>
/// <param name="proj">プロジェクション</param>
void ItemManager::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	for (const auto& item : m_items)
	{
		item->Render(view, proj);
	}
}

/// <summary>
/// 終了処理
/// </summary>
void ItemManager::Finalize()
{
	for (const auto& item : m_items)
	{
		item->Finalize();
	}
}

/// <summary>
/// 取得したアイテムを取消す
/// </summary>
void ItemManager::TookItems()
{
	// 条件を満たすオブジェクトを削除
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
/// アイテムを出現する
/// </summary>
void ItemManager::SpawnItem(const DX::StepTimer& timer)
{
	//	生成限界数にたっしているなら帰れ
	if (m_items.size() >= SPAWN_ITEM)	return;

	//	出現するY座標
	float y = 1.0f;
	//	経過時間を足す
	m_spwanItemTime += static_cast<float>(timer.GetElapsedSeconds());

	if (m_spwanItemTime >= SPAWN_TIME)
	{
		//	スポーン時間はリセットする
		m_spwanItemTime = 0.0f;

		//	0～6の値をランダムで取得する
		int random = rand() % 6;

		//	ランダムでどちらから始めるか決める
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
		//	ランダムでどちらから始めるか決める
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