#pragma once
#include "pch.h"

class Object;
class ItemCapsuleTop;
class ItemCapsuleBottom;

//	インターフェイスを宣言する
__interface IItemCapsuleFactory
{
	//	カプセルの上側を作成する
	std::unique_ptr<ItemCapsuleBottom> CreateItemCapsuleTop(Object* parent);
	//	カプセルの下側を作成する
	std::unique_ptr<ItemCapsuleBottom> CreateItemCapsuleBottom(Object* parent);
};