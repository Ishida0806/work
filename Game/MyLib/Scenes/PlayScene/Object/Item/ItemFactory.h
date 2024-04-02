#pragma once
#include "RecoveryItem.h"
#include "ReflectItem.h"
#include "PowerUPItem.h"
#include "IItemFactory.h"


class ItemFactory : public IItemFactory
{
public:
	//  �񕜃A�C�e���𐶐�����
	static 	std::unique_ptr<RecoveryItem> CreateRecoveryItem(const DirectX::SimpleMath::Vector3& position, const RecoveryItem::ItemType& type);
	//	���˃A�C�e���̍쐬
	static 	std::unique_ptr<ReflectItem>  CreateReflectItem(const DirectX::SimpleMath::Vector3& position, const RecoveryItem::ItemType& type);
	//	�p���[�A�b�v�A�C�e���̍쐬
	static	std::unique_ptr<PowerUPItem>  CreatePowerUPItem(const DirectX::SimpleMath::Vector3& position, const RecoveryItem::ItemType& type);
};