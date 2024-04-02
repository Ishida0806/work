//
//		File Name �F ItemCapsuleFactory.h
//		Production�F 2023/12/06
//		Author�@�@�F �Γc ����
//
#pragma once
#include "IItemCapsuleFactory.h"
#include "ItemCapsuleBottom.h"
#include "ItemCapsuleTop.h"

interface IItemCapsuleFactory;
class ItemCapsuleBottom;
class ItemCapsuleTop;

class ItemCapsuleFactory : public IItemCapsuleFactory
{
public:
	
	/// <summary>
	/// �J�v�Z���̏㑤���쐬����
	/// </summary>
	/// <param name="parent">�e</param>
	/// <returns>���L��</returns>
	static std::unique_ptr<ItemCapsuleTop> CreateItemCapsuleTop(Object* parent);

	/// <summary>
	/// �J�v�Z���̉������쐬����
	/// </summary>
	/// <param name="parent">�e</param>
	/// <returns>���L��</returns>
	static std::unique_ptr<ItemCapsuleBottom> CreateItemCapsuleBottom(Object* parent);
};