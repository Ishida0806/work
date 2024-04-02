//
//		File Name ： CursorFactory.h
//		Production： 2023/7/02
//		Author　　： 石田 恭一
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
	// 「砲塔下部」を生成する
	static std::unique_ptr<ICursorComponent> CreateCursorBottom(
		ICursorComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& rotate
	);

	//「砲塔下部脚」を生成する
	static std::unique_ptr<ICursorComponent> CreateCursorTop(
		ICursorComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const float& angle
	);
};