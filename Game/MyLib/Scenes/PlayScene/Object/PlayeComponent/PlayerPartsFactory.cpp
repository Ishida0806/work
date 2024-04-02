//
//		File Name ： PlayerPartsFactory.cpp
//		Production： 2023/12/29
//		Author　　： 石田 恭一
// 
//		プレイヤーパーツの作成する工場
//
#include "pch.h"
#include "PlayerPartsFactory.h"

/// <summary>
/// プレイヤーの頭を作成する
/// </summary>
/// <param name="root">ルート</param>
/// <param name="parent">親</param>
/// <returns>所有権</returns>
std::unique_ptr<PlayerHead> PlayerPartsFactory::CreatePlayerHead(Player* root, Object* parent)
{
	std::unique_ptr<PlayerHead> playerHead;
	//  入れる
	playerHead.reset(new PlayerHead(root , parent));
	//  初期化初期化
	playerHead->Initialize();
	//  渡す
	return  std::move(playerHead);
}

/// <summary>
/// プレイヤーの身体を作成する
/// </summary>
/// <param name="root">ルート</param>
/// <param name="parent">親</param>
/// <returns>所有権</returns>
std::unique_ptr<PlayerBody> PlayerPartsFactory::CreatePlayerBody(Player* root, Object* parent)
{
	std::unique_ptr<PlayerBody> playerBody;
	//  入れる
	playerBody.reset(new PlayerBody(root, parent));
	//  初期化初期化
	playerBody->Initialize();
	//  渡す
	return  std::move(playerBody);
}

/// <summary>
/// プレイヤーの左脚を作成する
/// </summary>
/// <param name="root">ルート</param>
/// <param name="parent">親</param>
/// <returns>所有権</returns>
std::unique_ptr<PlayerLeftLeg> PlayerPartsFactory::CreatePlayerLeftLeg(Player* root, Object* parent)
{
	std::unique_ptr<PlayerLeftLeg> playerLeftLeg;
	//  入れる
	playerLeftLeg.reset(new PlayerLeftLeg(root, parent));
	//  初期化初期化
	playerLeftLeg->Initialize();
	//  渡す
	return  std::move(playerLeftLeg);
}

/// <summary>
/// プレイヤーの左腕を作成する
/// </summary>
/// <param name="root">ルート</param>
/// <param name="parent">親</param>
/// <returns>所有権</returns>
std::unique_ptr<PlayerLeftArm> PlayerPartsFactory::CreatePlayerLeftArm(Player* root, Object* parent)
{
	std::unique_ptr<PlayerLeftArm> playerLeftArm;
	//  入れる
	playerLeftArm.reset(new PlayerLeftArm(root, parent));
	//  初期化初期化
	playerLeftArm->Initialize();
	//  渡す
	return  std::move(playerLeftArm);
}

/// <summary>
///	プレイヤーの右腕を作成する
/// </summary>
/// <param name="root">ルート</param>
/// <param name="parent">親</param>
/// <returns>所有権</returns>
std::unique_ptr<PlayerRightArm> PlayerPartsFactory::CreatePlayerRightArm(Player* root, Object* parent)
{
	std::unique_ptr<PlayerRightArm> playerRightArm;
	//  入れる
	playerRightArm.reset(new PlayerRightArm(root, parent));
	//  初期化初期化
	playerRightArm->Initialize();
	//  渡す
	return  std::move(playerRightArm);
}

/// <summary>
///	プレイヤーの右脚を作成する
/// </summary>
/// <param name="root">ルート</param>
/// <param name="parent">親</param>
/// <returns>所有権</returns>
std::unique_ptr<PlayerRightLeg> PlayerPartsFactory::CreatePlayerRightLeg(Player* root, Object* parent)
{
	std::unique_ptr<PlayerRightLeg> playerRightLeg;
	//  入れる
	playerRightLeg.reset(new PlayerRightLeg(root, parent));
	//  初期化初期化
	playerRightLeg->Initialize();
	//  渡す
	return  std::move(playerRightLeg);
}

/// <summary>
///	プレイヤーのマントの作成
/// </summary>
/// <param name="root">ルート</param>
/// <param name="parent">親</param>
/// <returns>所有権</returns>
std::unique_ptr<Cloak> PlayerPartsFactory::CreatePlayerCloak(Player* root, Object* parent)
{
	std::unique_ptr<Cloak> cloak;
	//  入れる
	cloak.reset(new Cloak(root, parent));
	//  初期化初期化
	cloak->Initialize();
	//  渡す
	return  std::move(cloak);
}
