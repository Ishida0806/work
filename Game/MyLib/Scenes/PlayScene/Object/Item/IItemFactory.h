#pragma once

class RecoveryItem;
class ReflectItem;
class PowerUPItem;

//	インターフェイスを宣言する	
__interface IItemFactory
{
	//	回復アイテムの作成
	std::unique_ptr<RecoveryItem> CreateRecoveryItem(const DirectX::SimpleMath::Vector3& position, const RecoveryItem::ItemType& type);
	//	反射アイテムの作成
	std::unique_ptr<ReflectItem>  CreateReflectItem(const DirectX::SimpleMath::Vector3& position, const RecoveryItem::ItemType& type);
	//	パワーアップアイテムの作成
	std::unique_ptr<PowerUPItem>  CreatePowerUPItem(const DirectX::SimpleMath::Vector3& position, const RecoveryItem::ItemType& type);
};