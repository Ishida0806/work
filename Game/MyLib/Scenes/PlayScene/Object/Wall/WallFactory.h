#pragma once
#include "IWallFactory.h"

__interface IWallFactory;

//	壁の作成を担う工場
class WallFactory : public IWallFactory
{
public:

	/// <summary>
	/// 壁の作成
	/// </summary>
	/// <param name="position">座標</param>
	/// <param name="scale">大きさ</param>
	/// <param name="angle">角度</param>
	/// <returns>所有権</returns>
	static std::unique_ptr<Wall> CreateWall(
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Vector3& scale,
		const float& angle
	);
};