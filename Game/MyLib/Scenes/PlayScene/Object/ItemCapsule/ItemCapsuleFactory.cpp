//
//		File Name ： ItemCapsuleFactory.cpp
//		Production： 2023/12/06
//		Author　　： 石田 恭一
//
#include "pch.h"
#include "ItemCapsuleFactory.h"

/// <summary>
/// カプセルの上側を作成する
/// </summary>
/// <param name="parent">親</param>
/// <returns>所有権</returns>
std::unique_ptr<ItemCapsuleTop> ItemCapsuleFactory::CreateItemCapsuleTop(Object* parent)
{
    //  インスタンスを作成する
    std::unique_ptr<ItemCapsuleTop> item;
    //  入れる
    item.reset(new ItemCapsuleTop(parent));
    //  初期化初期化
    item->Initialize();
    //  渡す
    return  move(item);
}

/// <summary>
/// カプセルの下側を作成する
/// </summary>
/// <param name="parent">親</param>
/// <returns>所有権</returns>
std::unique_ptr<ItemCapsuleBottom> ItemCapsuleFactory::CreateItemCapsuleBottom(Object* parent)
{
    //  インスタンスを作成する
    std::unique_ptr<ItemCapsuleBottom> item;   
    //  入れる
    item.reset(new ItemCapsuleBottom(parent));
    //  初期化初期化
    item->Initialize();
    //  渡す
    return  move(item);
}
