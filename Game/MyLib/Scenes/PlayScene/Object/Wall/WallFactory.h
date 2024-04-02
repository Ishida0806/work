#pragma once
#include "IWallFactory.h"

__interface IWallFactory;

//	•Ç‚Ìì¬‚ğ’S‚¤Hê
class WallFactory : public IWallFactory
{
public:

	/// <summary>
	/// •Ç‚Ìì¬
	/// </summary>
	/// <param name="position">À•W</param>
	/// <param name="scale">‘å‚«‚³</param>
	/// <param name="angle">Šp“x</param>
	/// <returns>Š—LŒ </returns>
	static std::unique_ptr<Wall> CreateWall(
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Vector3& scale,
		const float& angle
	);
};