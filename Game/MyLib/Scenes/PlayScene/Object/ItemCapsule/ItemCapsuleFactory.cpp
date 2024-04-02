//
//		File Name �F ItemCapsuleFactory.cpp
//		Production�F 2023/12/06
//		Author�@�@�F �Γc ����
//
#include "pch.h"
#include "ItemCapsuleFactory.h"

/// <summary>
/// �J�v�Z���̏㑤���쐬����
/// </summary>
/// <param name="parent">�e</param>
/// <returns>���L��</returns>
std::unique_ptr<ItemCapsuleTop> ItemCapsuleFactory::CreateItemCapsuleTop(Object* parent)
{
    //  �C���X�^���X���쐬����
    std::unique_ptr<ItemCapsuleTop> item;
    //  �����
    item.reset(new ItemCapsuleTop(parent));
    //  ������������
    item->Initialize();
    //  �n��
    return  move(item);
}

/// <summary>
/// �J�v�Z���̉������쐬����
/// </summary>
/// <param name="parent">�e</param>
/// <returns>���L��</returns>
std::unique_ptr<ItemCapsuleBottom> ItemCapsuleFactory::CreateItemCapsuleBottom(Object* parent)
{
    //  �C���X�^���X���쐬����
    std::unique_ptr<ItemCapsuleBottom> item;   
    //  �����
    item.reset(new ItemCapsuleBottom(parent));
    //  ������������
    item->Initialize();
    //  �n��
    return  move(item);
}
