//
//		File Name ： PlayerPartsFactory.h
//		Production： 2023/12/29
//		Author　　： 石田 恭一
//
#pragma once
#include "IPlayerPartsFactory.h"
#include "../Cloak/Cloak.h"
#include "PlayerHead.h"
#include "PlayerBody.h"
#include "PlayerRightArm.h"
#include "PlayerLeftArm.h"
#include "PlayerRightLeg.h"
#include "PlayerLeftLeg.h"

__interface IPlayerPartsFactory;

class PlayerPartsFactory : public IPlayerPartsFactory
{
public:

	//	プレイヤーの身体を作成する
	static std::unique_ptr<PlayerBody> CreatePlayerBody(Player* root, Object* parent);
	//	プレイヤーの頭を作成する
	static std::unique_ptr<PlayerHead> CreatePlayerHead(Player* root, Object* parent);
	//	プレイヤーの左脚を作成する
	static std::unique_ptr<PlayerLeftLeg> CreatePlayerLeftLeg(Player* root, Object* parent);
	//	プレイヤーの左腕を作成する
	static std::unique_ptr<PlayerLeftArm> CreatePlayerLeftArm(Player* root, Object* parent);
	//	プレイヤーの右腕を作成する
	static std::unique_ptr<PlayerRightArm> CreatePlayerRightArm(Player* root, Object* parent);
	//	プレイヤーの右脚を作成する
	static std::unique_ptr<PlayerRightLeg> CreatePlayerRightLeg(Player* root, Object* parent);
	//	プレイヤーのマントの作成
	static std::unique_ptr<Cloak>		   CreatePlayerCloak(Player* root, Object* parent);
};