//
//		File Name ： BulletFactroy.h
//		Production： 2023/7/02
//		Author　　： 石田 恭一
// 
#pragma once

#include "Game/MyLib/Scenes/PlayScene/Object/Bullet/IBulletFactroy.h"

class BulletFactory : public IBulletFactory
{
public:
	//	プレイヤーの弾色
	static const DirectX::SimpleMath::Color PLAYER_BULLETS_COLOR;
	static const DirectX::SimpleMath::Color ENEMY_BULLETS_COLOR;
	static const DirectX::SimpleMath::Color BOSS_BULLETS_COLOR;

public:
	//	誰が所持しているか
	enum class OwnerID
	{
		ENEMY = 0,
		BOSS  = 1,

		OVER
	};

public:

	/// <summary>
	/// 指定された砲弾配列を生成する
	/// </summary>
	/// <param name="ownerID">オーナー</param>
	/// <param name="position">座標</param>
	/// <param name="rotate">回転角</param>
	/// <param name="color">色</param>
	/// <param name="power">力</param>
	/// <param name="scale">大きさ</param>
	/// <param name="used">使用状態</param>
	/// <returns>作成されたアドレス・所有権</returns>
	static std::unique_ptr<Bullet> CreateBullets(
		OwnerID ownerID,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& rotate,
		const DirectX::SimpleMath::Color& color,
		int power,
		float scale,
		bool  used = false
	);
};