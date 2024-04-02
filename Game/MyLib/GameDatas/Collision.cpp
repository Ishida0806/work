//
//		File Name �F Collision.cpp
//		Production�F 2023/7/08
//		Author�@�@�F �Γc ����
// 
//      �l�X�ȓ����蔻����s�����N���X	
//
#include "pch.h"
#include "Collision.h"

/// <summary>
/// 
/// </summary>
/// <param name="a"></param>
/// <param name="b"></param>
/// <param name="c"></param>
void Collision::Shape::Triangle::Set(const DirectX::SimpleMath::Vector3& a, const DirectX::SimpleMath::Vector3& b, const DirectX::SimpleMath::Vector3& c)
{
    // �@���x�N�g�����v�Z
    DirectX::SimpleMath::Vector3 n = (c - a).Cross(b - a);

    // ���ʂ�ݒ�
    p = DirectX::SimpleMath::Plane(a, n);

    // ��BC�Ɋ֘A���镽�ʂ�ݒ�
   // DirectX::SimpleMath::Plane pp = DirectX::SimpleMath::Plane(b, n);
    edgePlaneBC = DirectX::SimpleMath::Plane(b, n.Cross(b - c));

    // ��CA�Ɋ֘A���镽�ʂ�ݒ�
    edgePlaneCA = DirectX::SimpleMath::Plane(c, n.Cross(c - a));

    // �@���x�N�g���𐳋K��
    p.Normalize();
    edgePlaneBC.Normalize();
    edgePlaneCA.Normalize();

    // ��BC�̃X�P�[�����v�Z���ēK�p
    float bc_scale = 1.0f / (a.Dot(edgePlaneBC.Normal()) + edgePlaneBC.D());
    edgePlaneBC.x *= bc_scale;
    edgePlaneBC.y *= bc_scale;
    edgePlaneBC.z *= bc_scale;
    edgePlaneBC.w *= bc_scale;

    // ��CA�̃X�P�[�����v�Z���ēK�p
    float ca_scale = 1.0f / (b.Dot(edgePlaneCA.Normal()) + edgePlaneCA.D());
    edgePlaneCA.x *= ca_scale;
    edgePlaneCA.y *= ca_scale;
    edgePlaneCA.z *= ca_scale;
    edgePlaneCA.w *= ca_scale;
}

//--------------------------------------------------------------------------------
//  �J�v�Z��
Collision::Shape::Capsule::Capsule(const DirectX::SimpleMath::Vector3& start, const DirectX::SimpleMath::Vector3& end,const float& radius)
{
    this->segment.start = start;
    this->segment.end = end;
    this->radius = radius;
}

Collision::Shape::Capsule::Capsule()
    :segment{},
    radius(0.0f)
{

}
//--------------------------------------------------------------------------------

//--------------------------------------------------------------------------------
//  ��
Collision::Shape::Sphere::Sphere(const DirectX::SimpleMath::Vector3& center,const float& radius)
    :center(center),
    radius(radius)
{

}
//  ��
Collision::Shape::Sphere::Sphere()
    :center(DirectX::SimpleMath::Vector3::Zero),
    radius(0.0f)
{

}
//--------------------------------------------------------------------------------

Collision::Shape::Box::Box(const DirectX::SimpleMath::Vector3& center, const DirectX::SimpleMath::Vector3& extents)
    :center(center),
    extents(extents)
{

}

Collision::Shape::Box::Box()
    :center{},
    extents{}
{

}

//--------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------------
// 
// �{�b�N�X�Ƌ��̓����蔻����s���֐�
bool Collision::CheckBoxAndSphereCollision(const Shape::Box& box, const Shape::Sphere& sphere)
{
    // �{�b�N�X�̒��S�Ƌ��̒��S�Ƃ̋������v�Z
    DirectX::SimpleMath::Vector3 distance = sphere.center - box.center;

    // �{�b�N�X�̕��̔����Ƌ��̔��a�̍��v���v�Z
    float boxRadiusX = std::abs(box.extents.x);
    float boxRadiusY = std::abs(box.extents.y);
    float boxRadiusZ = std::abs(box.extents.z);

    // X�������̋������{�b�N�X�̕��̔����Ƌ��̔��a�̍��v���傫���ꍇ�͓������Ă��Ȃ�
    if (std::abs(distance.x) > boxRadiusX + sphere.radius)      return false;

    // Y�������̋������{�b�N�X�̕��̔����Ƌ��̔��a�̍��v���傫���ꍇ�͓������Ă��Ȃ�
    if (std::abs(distance.y) > boxRadiusY + sphere.radius)      return false;

    // Z�������̋������{�b�N�X�̕��̔����Ƌ��̔��a�̍��v���傫���ꍇ�͓������Ă��Ȃ�
    if (std::abs(distance.z) > boxRadiusZ + sphere.radius)      return false;

    // �ǂ̎������ł��������Ă���ꍇ�͓������Ă���
    return true;
}

//-----------------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------
/// <summary>
///  ���Ƌ��̓����蔻��
/// </summary>
/// <param name="_sphereA"></param>
/// <param name="_sphereB"></param>
/// <returns>�ڐG����</returns>
bool Collision::CheckSphereAndSphere(const Shape::Sphere& sphereA, const Shape::Sphere& sphereB)
{
    //  ���̒��S�̍�
    DirectX::SimpleMath::Vector3 half = sphereA.center - sphereB.center;

    //  ����
    float distance = half.Length();
    //  ���v�̔��a
    float sphere = sphereA.radius + sphereB.radius;
    //  ���ꂽ���������a�̍��Z�ȉ��Ȃ�true
    return distance <= sphere;
}
//--------------------------------------------------------------------------------

//------------------------------------------------------------------

/// <summary>
/// �Őڋߓ_�̎擾 (�n�_�E�I�_�E�_)
/// </summary>
/// <param name="a"></param>
/// <param name="b"></param>
/// <param name="c"></param>
/// <returns></returns>
float Collision::SqDistPointSegment(const DirectX::SimpleMath::Vector3& a, const DirectX::SimpleMath::Vector3& b, const DirectX::SimpleMath::Vector3& c)
{
    // �x�N�g��ab�͐���ab��\���x�N�g���ib����a�֌������x�N�g���j
    DirectX::SimpleMath::Vector3 ab = b - a;
    // �x�N�g��ac�͓_c��������̎n�_a�֌������x�N�g��
    DirectX::SimpleMath::Vector3 ac = c - a;
    // �x�N�g��bc�͓_c��������̏I�_b�֌������x�N�g��
    DirectX::SimpleMath::Vector3 bc = c - b;
    // e�̓x�N�g��ac��ab�̓��ς�\��
    float e = ac.Dot(ab);
    // ac��ab�̓��ς�0.0�ȉ��̏ꍇ�A�_c�͐���ab�̎n�_a�̗����ɂ���
    if (e <= FLT_EPSILON)
    {
        // �ŒZ�����͓_c��������̎n�_a�܂ł̋����̓���Ԃ�
        return ac.Dot(ac);
    }
    // f�̓x�N�g��ab��ab�̓��ς�\��
    float f = ab.Dot(ab);
    // �x�N�g��ac�ƃx�N�g��ab�̓��ς�ab��ab�̓��ψȏ�̏ꍇ�A�_c�͐���ab�̏I�_b�̗����ɂ���
    if (e >= f)
    {
        // �ŒZ�����͓_c��������̏I�_b�܂ł̋����̓���Ԃ�
        return bc.Dot(bc);
    }
    // ����ȊO�̏ꍇ�A�_c�͐���ab�̊Ԃɂ���
    // �ŒZ�����͓_c�������ab�ւ̐����̑��܂ł̋����̓���Ԃ�
    return ac.Dot(ac) - e * e / f;
}

//----------------------------------------------------------------------------------


//	�J�v�Z���Ƌ��� -----------------------------------------------------------------

/// <summary>
/// �J�v�Z���Ƌ���
/// </summary>
/// <param name="_capsule">�J�v�Z��</param>
/// <param name="_sphere">��</param>
/// <returns>�����蔻��L��</returns>
bool Collision::CheckCapsuleAndSphere(const Shape::Capsule& capsule, const Shape::Sphere& sphere)
{
    // ���̒��S�ƃJ�v�Z���̒��S�̐����Ƃ̋����̕������v�Z
    float dist2 = SqDistPointSegment(capsule.segment.start, capsule.segment.end, sphere.center);

    // ���ƃJ�v�Z���̔��a�����Z�����l
    float radius = sphere.radius + capsule.radius;

    // ���ƃJ�v�Z�����d�Ȃ��Ă��邩�𔻒肷��
    // �����̕��������ƃJ�v�Z���̔��a�̓��̘a�ȉ��̏ꍇ�A�d�Ȃ��Ă���Ƃ݂Ȃ�
    return dist2 <= radius * radius;
}

//----------------------------------------------------------------------------------

/// <summary>
/// ���Ƌ��̉~���Z�o����
/// </summary>
/// <param name="sphere1">��</param>
/// <param name="sphere2">��</param>
/// <returns></returns>
DirectX::SimpleMath::Vector3 Collision::HitDirectionSphereAndSphere(Shape::Sphere sphere1, Shape::Sphere sphere2)
{
    DirectX::SimpleMath::Vector3 hitDirection;
    //  �������Z�o
    hitDirection = sphere1.center - sphere2.center;
    hitDirection.Normalize();

    return hitDirection;
}

