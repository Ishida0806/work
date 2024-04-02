//	
//		File Name �F SteeringBehavior.h
//		Production�F 2023/12/25
//		Author�@�@�F �Γc ����	
// 
//		���Ǎs���֘A�̃w�b�_�t�@�C��
//	
#pragma once
#include "pch.h"
#include "Game/MyLib/Scenes/PlayScene/Object/Object.h"

namespace SteeringBehavior
{
	/// <summary>
	/// �T���s��
	/// </summary>
	/// <param name="obj">�Ώ�</param>
	/// <param name="targetPosition">�ڕW���W</param>
	/// <param name="speed">���x</param>
	/// <returns>���Ǘ�</returns>
	static inline DirectX::SimpleMath::Vector3 Seek(const Object* obj, const DirectX::SimpleMath::Vector3& targetPosition, const float& speed)
	{
		// �ڕW�ʒu�ւ̕����x�N�g���̎Z�o
		DirectX::SimpleMath::Vector3 toTarget = targetPosition - obj->GetPosition();

		// ��]���x�̎Z�o
		toTarget.Normalize();
		DirectX::SimpleMath::Vector3 desiredVelocity = toTarget * speed;

		// ���Ǘ͂̎Z�o
		DirectX::SimpleMath::Vector3 steeringForce = desiredVelocity;

		// ���Ǘ͂̕ԋp
		return steeringForce;
	}

	/// <summary>
	/// �p�j�s��
	/// </summary>
	/// <param name="obj">�Ώ�</param>
	/// <param name="wanderAngle"> �p�j�s���p�^�[�Q�b�g�ւ̊p�x</param>
	/// <param name="speed">���x</param>
	/// <param name="wanderRadius">�p�j�s���p�~�̔��a</param>
	/// <param name="wanderDistance">�p�j�s���p�~�܂ł̋���</param>
	/// <param name="wanderMaxAngularDisplacement">�p�j�s���p�^�[�Q�b�g�ւ̊p�x�̍ő�p�ψ�</param>
	/// <returns>���Ǘ�</returns>
	static inline DirectX::SimpleMath::Vector3 Wander(const Object* obj, float* wanderAngle, const float& speed,float wanderRadius, float wanderDistance, float wanderMaxAngularDisplacement)
	{
		float randomDir= Utility::CreateRandom(-1.0, 1.0);

		DirectX::SimpleMath::Vector3 ForWard = DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3::Forward, obj->GetRotate());

		// �p�j�s���p�~�̒��S�̎Z�o
		DirectX::SimpleMath::Vector3 wanderCenter = obj->GetPosition() + ForWard * wanderDistance;

		// �^�[�Q�b�g�ւ̊p�x��ω�
		*wanderAngle += randomDir * wanderMaxAngularDisplacement;
		float radian = DirectX::XMConvertToRadians(*wanderAngle);
		DirectX::SimpleMath::Vector3 wanderTargetDirection{ std::cos(radian), 0.0f, std::sin(radian) };

		// �p�j�s���p�~�̉~����̃^�[�Q�b�g�̈ʒu�̎Z�o(�G�[�W�F���g����̑��΍��W)
		DirectX::SimpleMath::Vector3 wanderTarget = wanderCenter + wanderTargetDirection * wanderRadius;

		// �T���s���ɂ�鑀�Ǘ͂̎Z�o
		DirectX::SimpleMath::Vector3 steeringForce = Seek(obj , wanderTarget , speed);

		// ���Ǘ͂̕ԋp
		return steeringForce;
	}
}