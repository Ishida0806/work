#pragma once

class Wall;

// インタフェースを定義する
__interface IWallFactory
{
	// 「壁」を生成する
	std::unique_ptr<Wall> CreateWall(
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Vector3& scale,
		const float& angle
	);
};
