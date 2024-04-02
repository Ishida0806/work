#pragma once
#include "IWallFactory.h"

__interface IWallFactory;

//	�ǂ̍쐬��S���H��
class WallFactory : public IWallFactory
{
public:

	/// <summary>
	/// �ǂ̍쐬
	/// </summary>
	/// <param name="position">���W</param>
	/// <param name="scale">�傫��</param>
	/// <param name="angle">�p�x</param>
	/// <returns>���L��</returns>
	static std::unique_ptr<Wall> CreateWall(
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Vector3& scale,
		const float& angle
	);
};