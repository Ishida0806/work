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


//	�C���^�[�t�F�C�X��錾����
__interface IPlayerPartsFactory
{
	//	�v���C���[�̐g�̂��쐬����
	std::unique_ptr<PlayerBody>		CreatePlayerBody(Player* root, Object* parent);
	//	�v���C���[�̓����쐬����
	std::unique_ptr<PlayerHead>		CreatePlayerHead(Player* root, Object* parent);
	//	�v���C���[�̍��r���쐬����
	std::unique_ptr<PlayerLeftLeg>  CreatePlayerLeftLeg(Player* root, Object* parent);
	//	�v���C���[�̍��r���쐬����
	std::unique_ptr<PlayerLeftArm>  CreatePlayerLeftArm(Player* root, Object* parent);
	//	�v���C���[�̉E�r���쐬����
	std::unique_ptr<PlayerRightArm> CreatePlayerRightArm(Player* root, Object* parent);
	//	�v���C���[�̉E�r���쐬����
	std::unique_ptr<PlayerRightLeg> CreatePlayerRightLeg(Player* root, Object* parent);
	//	�v���C���[�̃}���g�̍쐬
	std::unique_ptr<Cloak>		    CreatePlayerCloak(Player* root, Object* parent);
};