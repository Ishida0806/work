//
//		File Name ： Collision.cpp
//		Production： 2023/7/08
//		Author　　： 石田 恭一
// 
//      様々な当たり判定を行ったクラス	
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
    // 法線ベクトルを計算
    DirectX::SimpleMath::Vector3 n = (c - a).Cross(b - a);

    // 平面を設定
    p = DirectX::SimpleMath::Plane(a, n);

    // 辺BCに関連する平面を設定
   // DirectX::SimpleMath::Plane pp = DirectX::SimpleMath::Plane(b, n);
    edgePlaneBC = DirectX::SimpleMath::Plane(b, n.Cross(b - c));

    // 辺CAに関連する平面を設定
    edgePlaneCA = DirectX::SimpleMath::Plane(c, n.Cross(c - a));

    // 法線ベクトルを正規化
    p.Normalize();
    edgePlaneBC.Normalize();
    edgePlaneCA.Normalize();

    // 辺BCのスケールを計算して適用
    float bc_scale = 1.0f / (a.Dot(edgePlaneBC.Normal()) + edgePlaneBC.D());
    edgePlaneBC.x *= bc_scale;
    edgePlaneBC.y *= bc_scale;
    edgePlaneBC.z *= bc_scale;
    edgePlaneBC.w *= bc_scale;

    // 辺CAのスケールを計算して適用
    float ca_scale = 1.0f / (b.Dot(edgePlaneCA.Normal()) + edgePlaneCA.D());
    edgePlaneCA.x *= ca_scale;
    edgePlaneCA.y *= ca_scale;
    edgePlaneCA.z *= ca_scale;
    edgePlaneCA.w *= ca_scale;
}

//--------------------------------------------------------------------------------
//  カプセル
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
//  球
Collision::Shape::Sphere::Sphere(const DirectX::SimpleMath::Vector3& center,const float& radius)
    :center(center),
    radius(radius)
{

}
//  球
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
// ボックスと球の当たり判定を行う関数
bool Collision::CheckBoxAndSphereCollision(const Shape::Box& box, const Shape::Sphere& sphere)
{
    // ボックスの中心と球の中心との距離を計算
    DirectX::SimpleMath::Vector3 distance = sphere.center - box.center;

    // ボックスの幅の半分と球の半径の合計を計算
    float boxRadiusX = std::abs(box.extents.x);
    float boxRadiusY = std::abs(box.extents.y);
    float boxRadiusZ = std::abs(box.extents.z);

    // X軸方向の距離がボックスの幅の半分と球の半径の合計より大きい場合は当たっていない
    if (std::abs(distance.x) > boxRadiusX + sphere.radius)      return false;

    // Y軸方向の距離がボックスの幅の半分と球の半径の合計より大きい場合は当たっていない
    if (std::abs(distance.y) > boxRadiusY + sphere.radius)      return false;

    // Z軸方向の距離がボックスの幅の半分と球の半径の合計より大きい場合は当たっていない
    if (std::abs(distance.z) > boxRadiusZ + sphere.radius)      return false;

    // どの軸方向でも当たっている場合は当たっている
    return true;
}

//-----------------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------
/// <summary>
///  球と球の当たり判定
/// </summary>
/// <param name="_sphereA"></param>
/// <param name="_sphereB"></param>
/// <returns>接触判定</returns>
bool Collision::CheckSphereAndSphere(const Shape::Sphere& sphereA, const Shape::Sphere& sphereB)
{
    //  球の中心の差
    DirectX::SimpleMath::Vector3 half = sphereA.center - sphereB.center;

    //  距離
    float distance = half.Length();
    //  合計の半径
    float sphere = sphereA.radius + sphereB.radius;
    //  離れた距離が半径の合算以下ならtrue
    return distance <= sphere;
}
//--------------------------------------------------------------------------------

//------------------------------------------------------------------

/// <summary>
/// 最接近点の取得 (始点・終点・点)
/// </summary>
/// <param name="a"></param>
/// <param name="b"></param>
/// <param name="c"></param>
/// <returns></returns>
float Collision::SqDistPointSegment(const DirectX::SimpleMath::Vector3& a, const DirectX::SimpleMath::Vector3& b, const DirectX::SimpleMath::Vector3& c)
{
    // ベクトルabは線分abを表すベクトル（bからaへ向かうベクトル）
    DirectX::SimpleMath::Vector3 ab = b - a;
    // ベクトルacは点cから線分の始点aへ向かうベクトル
    DirectX::SimpleMath::Vector3 ac = c - a;
    // ベクトルbcは点cから線分の終点bへ向かうベクトル
    DirectX::SimpleMath::Vector3 bc = c - b;
    // eはベクトルacとabの内積を表す
    float e = ac.Dot(ab);
    // acとabの内積が0.0以下の場合、点cは線分abの始点aの裏側にある
    if (e <= FLT_EPSILON)
    {
        // 最短距離は点cから線分の始点aまでの距離の二乗を返す
        return ac.Dot(ac);
    }
    // fはベクトルabとabの内積を表す
    float f = ab.Dot(ab);
    // ベクトルacとベクトルabの内積がabとabの内積以上の場合、点cは線分abの終点bの裏側にある
    if (e >= f)
    {
        // 最短距離は点cから線分の終点bまでの距離の二乗を返す
        return bc.Dot(bc);
    }
    // それ以外の場合、点cは線分abの間にある
    // 最短距離は点cから線分abへの垂線の足までの距離の二乗を返す
    return ac.Dot(ac) - e * e / f;
}

//----------------------------------------------------------------------------------


//	カプセルと球体 -----------------------------------------------------------------

/// <summary>
/// カプセルと球体
/// </summary>
/// <param name="_capsule">カプセル</param>
/// <param name="_sphere">球</param>
/// <returns>当たり判定有無</returns>
bool Collision::CheckCapsuleAndSphere(const Shape::Capsule& capsule, const Shape::Sphere& sphere)
{
    // 球の中心とカプセルの中心の線分との距離の平方を計算
    float dist2 = SqDistPointSegment(capsule.segment.start, capsule.segment.end, sphere.center);

    // 球とカプセルの半径を合算した値
    float radius = sphere.radius + capsule.radius;

    // 球とカプセルが重なっているかを判定する
    // 距離の平方が球とカプセルの半径の二乗の和以下の場合、重なっているとみなす
    return dist2 <= radius * radius;
}

//----------------------------------------------------------------------------------

/// <summary>
/// 球と球の円を算出する
/// </summary>
/// <param name="sphere1">球</param>
/// <param name="sphere2">球</param>
/// <returns></returns>
DirectX::SimpleMath::Vector3 Collision::HitDirectionSphereAndSphere(Shape::Sphere sphere1, Shape::Sphere sphere2)
{
    DirectX::SimpleMath::Vector3 hitDirection;
    //  向きを算出
    hitDirection = sphere1.center - sphere2.center;
    hitDirection.Normalize();

    return hitDirection;
}

