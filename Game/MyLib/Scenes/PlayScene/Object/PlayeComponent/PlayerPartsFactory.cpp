//
//		File Name �F PlayerPartsFactory.cpp
//		Production�F 2023/12/29
//		Author�@�@�F �Γc ����
// 
//		�v���C���[�p�[�c�̍쐬����H��
//
#include "pch.h"
#include "PlayerPartsFactory.h"

/// <summary>
/// �v���C���[�̓����쐬����
/// </summary>
/// <param name="root">���[�g</param>
/// <param name="parent">�e</param>
/// <returns>���L��</returns>
std::unique_ptr<PlayerHead> PlayerPartsFactory::CreatePlayerHead(Player* root, Object* parent)
{
	std::unique_ptr<PlayerHead> playerHead;
	//  �����
	playerHead.reset(new PlayerHead(root , parent));
	//  ������������
	playerHead->Initialize();
	//  �n��
	return  std::move(playerHead);
}

/// <summary>
/// �v���C���[�̐g�̂��쐬����
/// </summary>
/// <param name="root">���[�g</param>
/// <param name="parent">�e</param>
/// <returns>���L��</returns>
std::unique_ptr<PlayerBody> PlayerPartsFactory::CreatePlayerBody(Player* root, Object* parent)
{
	std::unique_ptr<PlayerBody> playerBody;
	//  �����
	playerBody.reset(new PlayerBody(root, parent));
	//  ������������
	playerBody->Initialize();
	//  �n��
	return  std::move(playerBody);
}

/// <summary>
/// �v���C���[�̍��r���쐬����
/// </summary>
/// <param name="root">���[�g</param>
/// <param name="parent">�e</param>
/// <returns>���L��</returns>
std::unique_ptr<PlayerLeftLeg> PlayerPartsFactory::CreatePlayerLeftLeg(Player* root, Object* parent)
{
	std::unique_ptr<PlayerLeftLeg> playerLeftLeg;
	//  �����
	playerLeftLeg.reset(new PlayerLeftLeg(root, parent));
	//  ������������
	playerLeftLeg->Initialize();
	//  �n��
	return  std::move(playerLeftLeg);
}

/// <summary>
/// �v���C���[�̍��r���쐬����
/// </summary>
/// <param name="root">���[�g</param>
/// <param name="parent">�e</param>
/// <returns>���L��</returns>
std::unique_ptr<PlayerLeftArm> PlayerPartsFactory::CreatePlayerLeftArm(Player* root, Object* parent)
{
	std::unique_ptr<PlayerLeftArm> playerLeftArm;
	//  �����
	playerLeftArm.reset(new PlayerLeftArm(root, parent));
	//  ������������
	playerLeftArm->Initialize();
	//  �n��
	return  std::move(playerLeftArm);
}

/// <summary>
///	�v���C���[�̉E�r���쐬����
/// </summary>
/// <param name="root">���[�g</param>
/// <param name="parent">�e</param>
/// <returns>���L��</returns>
std::unique_ptr<PlayerRightArm> PlayerPartsFactory::CreatePlayerRightArm(Player* root, Object* parent)
{
	std::unique_ptr<PlayerRightArm> playerRightArm;
	//  �����
	playerRightArm.reset(new PlayerRightArm(root, parent));
	//  ������������
	playerRightArm->Initialize();
	//  �n��
	return  std::move(playerRightArm);
}

/// <summary>
///	�v���C���[�̉E�r���쐬����
/// </summary>
/// <param name="root">���[�g</param>
/// <param name="parent">�e</param>
/// <returns>���L��</returns>
std::unique_ptr<PlayerRightLeg> PlayerPartsFactory::CreatePlayerRightLeg(Player* root, Object* parent)
{
	std::unique_ptr<PlayerRightLeg> playerRightLeg;
	//  �����
	playerRightLeg.reset(new PlayerRightLeg(root, parent));
	//  ������������
	playerRightLeg->Initialize();
	//  �n��
	return  std::move(playerRightLeg);
}

/// <summary>
///	�v���C���[�̃}���g�̍쐬
/// </summary>
/// <param name="root">���[�g</param>
/// <param name="parent">�e</param>
/// <returns>���L��</returns>
std::unique_ptr<Cloak> PlayerPartsFactory::CreatePlayerCloak(Player* root, Object* parent)
{
	std::unique_ptr<Cloak> cloak;
	//  �����
	cloak.reset(new Cloak(root, parent));
	//  ������������
	cloak->Initialize();
	//  �n��
	return  std::move(cloak);
}
