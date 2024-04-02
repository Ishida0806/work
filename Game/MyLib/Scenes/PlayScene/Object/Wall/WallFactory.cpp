#include "pch.h"
#include "WallFactory.h"
#include "Wall.h"

/// <summary>
/// 壁を作成する
/// </summary>
/// <param name="position">座標</param>
/// <param name="angle">角度</param>
/// <returns>所有権</returns>
std::unique_ptr<Wall>WallFactory::CreateWall(
	const DirectX::SimpleMath::Vector3& position,
	const DirectX::SimpleMath::Vector3& scale,
	const float& angle
)
{
	//	壁の初期化
	std::unique_ptr<Wall> walls;
	//	要素の初期化
	walls.reset(new Wall(position, scale , angle));
	//	要素の初期化
	walls->Initialize();
	// 壁クラスのインスタンスを返す
	return std::move(walls);
}
