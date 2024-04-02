#include "pch.h"
#include "ItemFactory.h"

/// <summary>
/// 回復アイテムを生成する
/// </summary>
/// <param name="position">座標</param>
/// <param name="type">アイテムの種類</param>
/// <returns>所有権</returns>
std::unique_ptr<RecoveryItem> ItemFactory::CreateRecoveryItem(const DirectX::SimpleMath::Vector3& position, const RecoveryItem::ItemType& type)
{
	std::unique_ptr<RecoveryItem> item;

	item.reset(new RecoveryItem(position, type));
	item->Initialize();

	return std::move(item);
}

/// <summary>
/// 反射アイテムの作成
/// </summary>
/// <param name="position">座標</param>
/// <param name="type">アイテムの種類</param>
/// <returns>所有権</returns>
std::unique_ptr<ReflectItem> ItemFactory::CreateReflectItem(const DirectX::SimpleMath::Vector3& position, const RecoveryItem::ItemType& type)
{
	std::unique_ptr<ReflectItem> item;

	item.reset(new ReflectItem(position, type));
	item->Initialize();

	return std::move(item);
}

/// <summary>
/// パワーアップアイテムの作成
/// </summary>
/// <param name="position">座標</param>
/// <param name="type">アイテムの種類</param>
/// <returns>所有権</returns>
std::unique_ptr<PowerUPItem> ItemFactory::CreatePowerUPItem(const DirectX::SimpleMath::Vector3& position, const RecoveryItem::ItemType& type)
{
	std::unique_ptr<PowerUPItem> item;

	item.reset(new PowerUPItem(position, type));
	item->Initialize();

	return std::move(item);
}
