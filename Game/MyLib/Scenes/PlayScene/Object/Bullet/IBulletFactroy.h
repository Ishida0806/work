//
//		File Name ： IBulletFactroy.h
//		Production： 2023/7/02
//		Author　　： 石田 恭一
// 
#pragma once

class Bullet;

//	インターフェイスの実装を行う
__interface IBulletFactory
{
public:
	// 指定された砲弾配列を生成する
	std::vector<std::unique_ptr<Bullet>> CreateBullets(
		int ownerID,
		const int& number,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& rotate,
		const DirectX::SimpleMath::Color&,
		int power,
		float scale,
		bool used
	);
};