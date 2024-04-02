//
//		File Name ： ItemCapsuleFactory.h
//		Production： 2023/12/06
//		Author　　： 石田 恭一
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
	/// カプセルの上側を作成する
	/// </summary>
	/// <param name="parent">親</param>
	/// <returns>所有権</returns>
	static std::unique_ptr<ItemCapsuleTop> CreateItemCapsuleTop(Object* parent);

	/// <summary>
	/// カプセルの下側を作成する
	/// </summary>
	/// <param name="parent">親</param>
	/// <returns>所有権</returns>
	static std::unique_ptr<ItemCapsuleBottom> CreateItemCapsuleBottom(Object* parent);
};