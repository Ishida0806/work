#pragma once
#include "RecoveryItem.h"
#include "ReflectItem.h"
#include "PowerUPItem.h"
#include "IItemFactory.h"


class ItemFactory : public IItemFactory
{
public:
	//  回復アイテムを生成する
	static 	std::unique_ptr<RecoveryItem> CreateRecoveryItem(const DirectX::SimpleMath::Vector3& position, const RecoveryItem::ItemType& type);
	//	反射アイテムの作成
	static 	std::unique_ptr<ReflectItem>  CreateReflectItem(const DirectX::SimpleMath::Vector3& position, const RecoveryItem::ItemType& type);
	//	パワーアップアイテムの作成
	static	std::unique_ptr<PowerUPItem>  CreatePowerUPItem(const DirectX::SimpleMath::Vector3& position, const RecoveryItem::ItemType& type);
};