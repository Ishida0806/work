#pragma once

class RecoveryItem;
class ReflectItem;
class PowerUPItem;

//	�C���^�[�t�F�C�X��錾����	
__interface IItemFactory
{
	//	�񕜃A�C�e���̍쐬
	std::unique_ptr<RecoveryItem> CreateRecoveryItem(const DirectX::SimpleMath::Vector3& position, const RecoveryItem::ItemType& type);
	//	���˃A�C�e���̍쐬
	std::unique_ptr<ReflectItem>  CreateReflectItem(const DirectX::SimpleMath::Vector3& position, const RecoveryItem::ItemType& type);
	//	�p���[�A�b�v�A�C�e���̍쐬
	std::unique_ptr<PowerUPItem>  CreatePowerUPItem(const DirectX::SimpleMath::Vector3& position, const RecoveryItem::ItemType& type);
};