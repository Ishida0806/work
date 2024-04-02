#pragma once
#include "pch.h"

class Object;
class ItemCapsuleTop;
class ItemCapsuleBottom;

//	�C���^�[�t�F�C�X��錾����
__interface IItemCapsuleFactory
{
	//	�J�v�Z���̏㑤���쐬����
	std::unique_ptr<ItemCapsuleBottom> CreateItemCapsuleTop(Object* parent);
	//	�J�v�Z���̉������쐬����
	std::unique_ptr<ItemCapsuleBottom> CreateItemCapsuleBottom(Object* parent);
};