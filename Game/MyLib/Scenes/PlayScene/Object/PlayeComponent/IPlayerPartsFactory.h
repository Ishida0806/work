#pragma once
#include "pch.h"

class Cloak;
class Player;
class Object;
class PlayerHead;
class PlayerBody;
class PlayerLeftLeg;
class PlayerLeftArm;
class PlayerRightArm;
class PlayerRightLeg;


//	インターフェイスを宣言する
__interface IPlayerPartsFactory
{
	//	プレイヤーの身体を作成する
	std::unique_ptr<PlayerBody>		CreatePlayerBody(Player* root, Object* parent);
	//	プレイヤーの頭を作成する
	std::unique_ptr<PlayerHead>		CreatePlayerHead(Player* root, Object* parent);
	//	プレイヤーの左脚を作成する
	std::unique_ptr<PlayerLeftLeg>  CreatePlayerLeftLeg(Player* root, Object* parent);
	//	プレイヤーの左腕を作成する
	std::unique_ptr<PlayerLeftArm>  CreatePlayerLeftArm(Player* root, Object* parent);
	//	プレイヤーの右腕を作成する
	std::unique_ptr<PlayerRightArm> CreatePlayerRightArm(Player* root, Object* parent);
	//	プレイヤーの右脚を作成する
	std::unique_ptr<PlayerRightLeg> CreatePlayerRightLeg(Player* root, Object* parent);
	//	プレイヤーのマントの作成
	std::unique_ptr<Cloak>		    CreatePlayerCloak(Player* root, Object* parent);
};