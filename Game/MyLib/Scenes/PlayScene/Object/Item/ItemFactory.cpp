#include "pch.h"
#include "ItemFactory.h"

/// <summary>
/// �񕜃A�C�e���𐶐�����
/// </summary>
/// <param name="position">���W</param>
/// <param name="type">�A�C�e���̎��</param>
/// <returns>���L��</returns>
std::unique_ptr<RecoveryItem> ItemFactory::CreateRecoveryItem(const DirectX::SimpleMath::Vector3& position, const RecoveryItem::ItemType& type)
{
	std::unique_ptr<RecoveryItem> item;

	item.reset(new RecoveryItem(position, type));
	item->Initialize();

	return std::move(item);
}

/// <summary>
/// ���˃A�C�e���̍쐬
/// </summary>
/// <param name="position">���W</param>
/// <param name="type">�A�C�e���̎��</param>
/// <returns>���L��</returns>
std::unique_ptr<ReflectItem> ItemFactory::CreateReflectItem(const DirectX::SimpleMath::Vector3& position, const RecoveryItem::ItemType& type)
{
	std::unique_ptr<ReflectItem> item;

	item.reset(new ReflectItem(position, type));
	item->Initialize();

	return std::move(item);
}

/// <summary>
/// �p���[�A�b�v�A�C�e���̍쐬
/// </summary>
/// <param name="position">���W</param>
/// <param name="type">�A�C�e���̎��</param>
/// <returns>���L��</returns>
std::unique_ptr<PowerUPItem> ItemFactory::CreatePowerUPItem(const DirectX::SimpleMath::Vector3& position, const RecoveryItem::ItemType& type)
{
	std::unique_ptr<PowerUPItem> item;

	item.reset(new PowerUPItem(position, type));
	item->Initialize();

	return std::move(item);
}
