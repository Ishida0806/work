#pragma once
#include "ICursorComponent.h"
#include "Cursor.h"

__interface ICursorComponent;

// ICursorFactory�C���^�t�F�[�X���`����
__interface ICursorFactory
{
public:
	// �u�C�������v�𐶐�����
	std::unique_ptr<ICursorComponent> CreateCursorBottom(
		ICursorComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& rotate
	);

	// �u�C�������r�v�𐶐�����
	std::unique_ptr<ICursorComponent> CreateCursorTop(
		ICursorComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const float& angle
	);
};
