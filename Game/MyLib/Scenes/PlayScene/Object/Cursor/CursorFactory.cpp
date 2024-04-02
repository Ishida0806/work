//
//		File Name �F CursorFactory.cpp
//		Production�F 2023/7/02
//		Author�@�@�F �Γc ����
// 
//	�J�[�\�������̍H��
//
#include "pch.h"
#include "CursorFactory.h"

class Cursor;
class CursorBottom;
class CursorTop;

// �@�J�[�\�������𐶐�����
std::unique_ptr<ICursorComponent> CursorFactory::CreateCursorBottom(ICursorComponent* parent, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& rotate)
{
	std::unique_ptr<ICursorComponent> cursorBottom;
	// TurretBottom�N���X�̃C���X�^���X�𐶐�����
	cursorBottom.reset(new CursorBottom(parent, position, rotate));
	// ����������
	cursorBottom->Initialize();
	// TurretBottom�N���X�̃C���X�^���X��Ԃ�
	return move(cursorBottom);
}

//  �J�[�\���㕔�𐶐�����
std::unique_ptr<ICursorComponent> CursorFactory::CreateCursorTop(
	ICursorComponent* parent,
	const DirectX::SimpleMath::Vector3& position,
	const float& angle
)
{
	std::unique_ptr<ICursorComponent> cursorTop;
	// TurretTop�N���X�̃C���X�^���X�𐶐�����
	cursorTop.reset(new CursorTop(parent, position, angle));
	// ����������
	cursorTop->Initialize();
	// TurretTop�N���X�̃C���X�^���X��Ԃ�
	return move(cursorTop);
}