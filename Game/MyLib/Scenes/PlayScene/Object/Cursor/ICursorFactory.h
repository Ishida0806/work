#pragma once
#include "ICursorComponent.h"
#include "Cursor.h"

__interface ICursorComponent;

// ICursorFactoryインタフェースを定義する
__interface ICursorFactory
{
public:
	// 「砲塔下部」を生成する
	std::unique_ptr<ICursorComponent> CreateCursorBottom(
		ICursorComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& rotate
	);

	// 「砲塔下部脚」を生成する
	std::unique_ptr<ICursorComponent> CreateCursorTop(
		ICursorComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const float& angle
	);
};
