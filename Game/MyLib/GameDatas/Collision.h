//
//		File Name �F Collision.h
//		Production�F 2023/7/08
//		Author�@�@�F �Γc ����	
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

	// ================================================ �`�� 
	struct Shape
	{
		// ---------------------------------- ���� ---------------------------------------
		struct Segment
		{
			DirectX::SimpleMath::Vector3 start;
			DirectX::SimpleMath::Vector3 end;
		};

		// ---------------------------------- �� -----------------------------------------

		struct Sphere : public CollisionBehavior
		{
			DirectX::SimpleMath::Vector3	center;
			float							radius;

		public:

			Sphere(const DirectX::SimpleMath::Vector3& center,const float& radius);
			Sphere();
			~Sphere() = default;

			/// <summary>
			/// ���g�̌^��Ԃ�
			/// </summary>
			/// <returns>�^</returns>
			ShapeType GetShapeType() const override { return ShapeType::Sphere; }
		};

		// ---------------------------------- �{�b�N�X ------------------------------------
		class Box : public CollisionBehavior
		{
		public:
			DirectX::SimpleMath::Vector3 center;		// ���S���W
			DirectX::SimpleMath::Vector3 extents;		// ���̔���(xyz�e�v�f)



		public:
			Box(const DirectX::SimpleMath::Vector3& center, const DirectX::SimpleMath::Vector3& extents);
			Box();
			~Box() = default;

			/// <summary>
			/// ���g�̌^��Ԃ�
			/// </summary>
			/// <returns>�^</returns>
			ShapeType GetShapeType() const override { return ShapeType::Box; }
		};

		//	---------------------------------- �J�v�Z�� ------------------------------------

		struct Capsule : public CollisionBehavior
		{
			Segment segment;
			float radius;

		public:
			Capsule(const DirectX::SimpleMath::Vector3& start, const DirectX::SimpleMath::Vector3& end,const float& radius);
			Capsule();
			~Capsule() = default;

			/// <summary>
			/// ���g�̌^��Ԃ�
			/// </summary>
			/// <returns>�^</returns>
			ShapeType GetShapeType() const override { return ShapeType::Capsule; }
		};

		// ---------------------------------- �O�p���� ------------------------------------
		struct Triangle : public CollisionBehavior
		{
			// �O�p�`�̕��ʕ�����
			DirectX::SimpleMath::Plane p;
			// ��BC�̕��ʕ������i�d�S���W�̒��_a�ɑ΂���d��u��^����j
			DirectX::SimpleMath::Plane edgePlaneBC;
			// ��CA�̕��ʕ������i�d�S���W�̒��_b�ɑ΂���d��v��^����j
			DirectX::SimpleMath::Plane edgePlaneCA;

			//	�O�p�`���Z�b�g����
			void Set(const DirectX::SimpleMath::Vector3& a, const DirectX::SimpleMath::Vector3& b, const DirectX::SimpleMath::Vector3& c);

			/// <summary>
			/// ���g�̌^��Ԃ�
			/// </summary>
			/// <returns>�^</returns>
			ShapeType GetShapeType() const override { return ShapeType::Triangle; }
		};
	};

	//---------------------------------------------------------------------------------
	// �`�� ===========================================================================

	float SqDistPointSegment(const DirectX::SimpleMath::Vector3& a, const DirectX::SimpleMath::Vector3& b, const DirectX::SimpleMath::Vector3& c);
	bool  CheckBoxAndSphereCollision(const Shape::Box& box, const Shape::Sphere& sphere);
	bool  CheckSphereAndSphere(const Shape::Sphere& sphereA, const Shape::Sphere& sphereB);
	bool  CheckCapsuleAndSphere(const Shape::Capsule& capsule, const Shape::Sphere& sphere);

	DirectX::SimpleMath::Vector3 HitDirectionSphereAndSphere(Shape::Sphere sphere1, Shape::Sphere sphere2);
}