//
//		File Name �F PlayerPartsFactory.h
//		Production�F 2023/12/29
//		Author�@�@�F �Γc ����
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

	//	�v���C���[�̐g�̂��쐬����
	static std::unique_ptr<PlayerBody> CreatePlayerBody(Player* root, Object* parent);
	//	�v���C���[�̓����쐬����
	static std::unique_ptr<PlayerHead> CreatePlayerHead(Player* root, Object* parent);
	//	�v���C���[�̍��r���쐬����
	static std::unique_ptr<PlayerLeftLeg> CreatePlayerLeftLeg(Player* root, Object* parent);
	//	�v���C���[�̍��r���쐬����
	static std::unique_ptr<PlayerLeftArm> CreatePlayerLeftArm(Player* root, Object* parent);
	//	�v���C���[�̉E�r���쐬����
	static std::unique_ptr<PlayerRightArm> CreatePlayerRightArm(Player* root, Object* parent);
	//	�v���C���[�̉E�r���쐬����
	static std::unique_ptr<PlayerRightLeg> CreatePlayerRightLeg(Player* root, Object* parent);
	//	�v���C���[�̃}���g�̍쐬
	static std::unique_ptr<Cloak>		   CreatePlayerCloak(Player* root, Object* parent);
};