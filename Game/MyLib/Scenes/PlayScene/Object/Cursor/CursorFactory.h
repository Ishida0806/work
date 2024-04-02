//
//		File Name �F CursorFactory.h
//		Production�F 2023/7/02
//		Author�@�@�F �Γc ����
//
#pragma once
#include "ICursorFactory.h"
#include "ICursorComponent.h"
#include "CursorFactory.h"

interface ICursorComponent;
__interface ICursorFactory;

class Cursor;
class CurorFactory;
class CursorBottom;
class CursorTop;

class CursorFactory : public ICursorFactory
{
public:
	// �u�C�������v�𐶐�����
	static std::unique_ptr<ICursorComponent> CreateCursorBottom(
		ICursorComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& rotate
	);

	//�u�C�������r�v�𐶐�����
	static std::unique_ptr<ICursorComponent> CreateCursorTop(
		ICursorComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const float& angle
	);
};