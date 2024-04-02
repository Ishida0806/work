//
//		File Name ： CursorFactory.cpp
//		Production： 2023/7/02
//		Author　　： 石田 恭一
// 
//	カーソルたちの工場
//
#include "pch.h"
#include "CursorFactory.h"

class Cursor;
class CursorBottom;
class CursorTop;

// 　カーソル下部を生成する
std::unique_ptr<ICursorComponent> CursorFactory::CreateCursorBottom(ICursorComponent* parent, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& rotate)
{
	std::unique_ptr<ICursorComponent> cursorBottom;
	// TurretBottomクラスのインスタンスを生成する
	cursorBottom.reset(new CursorBottom(parent, position, rotate));
	// 初期化する
	cursorBottom->Initialize();
	// TurretBottomクラスのインスタンスを返す
	return move(cursorBottom);
}

//  カーソル上部を生成する
std::unique_ptr<ICursorComponent> CursorFactory::CreateCursorTop(
	ICursorComponent* parent,
	const DirectX::SimpleMath::Vector3& position,
	const float& angle
)
{
	std::unique_ptr<ICursorComponent> cursorTop;
	// TurretTopクラスのインスタンスを生成する
	cursorTop.reset(new CursorTop(parent, position, angle));
	// 初期化する
	cursorTop->Initialize();
	// TurretTopクラスのインスタンスを返す
	return move(cursorTop);
}