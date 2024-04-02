//
//		File Name ： Collision.h
//		Production： 2023/7/08
//		Author　　： 石田 恭一	
//
#pragma once

namespace Collision
{
	struct CollisionBehavior
	{
		enum class ShapeType
		{
			Sphere,
			Box,
			Triangle,
			Capsule
		};

		virtual ShapeType GetShapeType() const = 0; 
	};

	// ================================================ 形状 
	struct Shape
	{
		// ---------------------------------- 線分 ---------------------------------------
		struct Segment
		{
			DirectX::SimpleMath::Vector3 start;
			DirectX::SimpleMath::Vector3 end;
		};

		// ---------------------------------- 球 -----------------------------------------

		struct Sphere : public CollisionBehavior
		{
			DirectX::SimpleMath::Vector3	center;
			float							radius;

		public:

			Sphere(const DirectX::SimpleMath::Vector3& center,const float& radius);
			Sphere();
			~Sphere() = default;

			/// <summary>
			/// 自身の型を返す
			/// </summary>
			/// <returns>型</returns>
			ShapeType GetShapeType() const override { return ShapeType::Sphere; }
		};

		// ---------------------------------- ボックス ------------------------------------
		class Box : public CollisionBehavior
		{
		public:
			DirectX::SimpleMath::Vector3 center;		// 中心座標
			DirectX::SimpleMath::Vector3 extents;		// 幅の半分(xyz各要素)



		public:
			Box(const DirectX::SimpleMath::Vector3& center, const DirectX::SimpleMath::Vector3& extents);
			Box();
			~Box() = default;

			/// <summary>
			/// 自身の型を返す
			/// </summary>
			/// <returns>型</returns>
			ShapeType GetShapeType() const override { return ShapeType::Box; }
		};

		//	---------------------------------- カプセル ------------------------------------

		struct Capsule : public CollisionBehavior
		{
			Segment segment;
			float radius;

		public:
			Capsule(const DirectX::SimpleMath::Vector3& start, const DirectX::SimpleMath::Vector3& end,const float& radius);
			Capsule();
			~Capsule() = default;

			/// <summary>
			/// 自身の型を返す
			/// </summary>
			/// <returns>型</returns>
			ShapeType GetShapeType() const override { return ShapeType::Capsule; }
		};

		// ---------------------------------- 三角平面 ------------------------------------
		struct Triangle : public CollisionBehavior
		{
			// 三角形の平面方程式
			DirectX::SimpleMath::Plane p;
			// 辺BCの平面方程式（重心座標の頂点aに対する重みuを与える）
			DirectX::SimpleMath::Plane edgePlaneBC;
			// 辺CAの平面方程式（重心座標の頂点bに対する重みvを与える）
			DirectX::SimpleMath::Plane edgePlaneCA;

			//	三角形をセットする
			void Set(const DirectX::SimpleMath::Vector3& a, const DirectX::SimpleMath::Vector3& b, const DirectX::SimpleMath::Vector3& c);

			/// <summary>
			/// 自身の型を返す
			/// </summary>
			/// <returns>型</returns>
			ShapeType GetShapeType() const override { return ShapeType::Triangle; }
		};
	};

	//---------------------------------------------------------------------------------
	// 形状 ===========================================================================

	float SqDistPointSegment(const DirectX::SimpleMath::Vector3& a, const DirectX::SimpleMath::Vector3& b, const DirectX::SimpleMath::Vector3& c);
	bool  CheckBoxAndSphereCollision(const Shape::Box& box, const Shape::Sphere& sphere);
	bool  CheckSphereAndSphere(const Shape::Sphere& sphereA, const Shape::Sphere& sphereB);
	bool  CheckCapsuleAndSphere(const Shape::Capsule& capsule, const Shape::Sphere& sphere);

	DirectX::SimpleMath::Vector3 HitDirectionSphereAndSphere(Shape::Sphere sphere1, Shape::Sphere sphere2);
}