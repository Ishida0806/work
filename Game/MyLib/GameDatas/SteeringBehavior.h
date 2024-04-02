//	
//		File Name ： SteeringBehavior.h
//		Production： 2023/12/25
//		Author　　： 石田 恭一	
// 
//		操舵行動関連のヘッダファイル
//	
#pragma once
#include "pch.h"
#include "Game/MyLib/Scenes/PlayScene/Object/Object.h"

namespace SteeringBehavior
{
	/// <summary>
	/// 探索行動
	/// </summary>
	/// <param name="obj">対象</param>
	/// <param name="targetPosition">目標座標</param>
	/// <param name="speed">速度</param>
	/// <returns>操舵力</returns>
	static inline DirectX::SimpleMath::Vector3 Seek(const Object* obj, const DirectX::SimpleMath::Vector3& targetPosition, const float& speed)
	{
		// 目標位置への方向ベクトルの算出
		DirectX::SimpleMath::Vector3 toTarget = targetPosition - obj->GetPosition();

		// 希望速度の算出
		toTarget.Normalize();
		DirectX::SimpleMath::Vector3 desiredVelocity = toTarget * speed;

		// 操舵力の算出
		DirectX::SimpleMath::Vector3 steeringForce = desiredVelocity;

		// 操舵力の返却
		return steeringForce;
	}

	/// <summary>
	/// 徘徊行動
	/// </summary>
	/// <param name="obj">対象</param>
	/// <param name="wanderAngle"> 徘徊行動用ターゲットへの角度</param>
	/// <param name="speed">速度</param>
	/// <param name="wanderRadius">徘徊行動用円の半径</param>
	/// <param name="wanderDistance">徘徊行動用円までの距離</param>
	/// <param name="wanderMaxAngularDisplacement">徘徊行動用ターゲットへの角度の最大角変位</param>
	/// <returns>操舵力</returns>
	static inline DirectX::SimpleMath::Vector3 Wander(const Object* obj, float* wanderAngle, const float& speed,float wanderRadius, float wanderDistance, float wanderMaxAngularDisplacement)
	{
		float randomDir= Utility::CreateRandom(-1.0, 1.0);

		DirectX::SimpleMath::Vector3 ForWard = DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3::Forward, obj->GetRotate());

		// 徘徊行動用円の中心の算出
		DirectX::SimpleMath::Vector3 wanderCenter = obj->GetPosition() + ForWard * wanderDistance;

		// ターゲットへの角度を変化
		*wanderAngle += randomDir * wanderMaxAngularDisplacement;
		float radian = DirectX::XMConvertToRadians(*wanderAngle);
		DirectX::SimpleMath::Vector3 wanderTargetDirection{ std::cos(radian), 0.0f, std::sin(radian) };

		// 徘徊行動用円の円周上のターゲットの位置の算出(エージェントからの相対座標)
		DirectX::SimpleMath::Vector3 wanderTarget = wanderCenter + wanderTargetDirection * wanderRadius;

		// 探索行動による操舵力の算出
		DirectX::SimpleMath::Vector3 steeringForce = Seek(obj , wanderTarget , speed);

		// 操舵力の返却
		return steeringForce;
	}
}