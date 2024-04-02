//
//		File Name ： Object.cpp
//		Production： 2023/6/19
//		Author　　： 石田 恭一	
// 
//		各オブジェクトの基底クラス
//	
#include "pch.h"
#include "Object.h"

/// <summary>
/// コンストラクタ
/// </summary>
Object::Object()
	:m_scale(1.0f),
	m_angle(0.0f)
{
}

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="position">座標</param>
Object::Object(const DirectX::SimpleMath::Vector3& position)
	:m_position(position),
	m_scale(1.0f),
	m_angle(0.0f)
{
}

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="position">座標</param>
/// <param name="rotate">回転角</param>
Object::Object(const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion rotate)
	:m_position(position),
	m_rotate(rotate),
	m_scale(1.0f),
	m_angle(0.0f)
{
}

/// <summary>
/// デストラクタ
/// </summary>
Object::~Object()
{
}

/// <summary>
/// 初期化処理
/// </summary>
void Object::Initialize()
{
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="timer">タイマー</param>
void Object::Update(const DX::StepTimer& timer)
{
	timer;
}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="view">ビュー</param>
/// <param name="proj">プロジェクション</param>
void Object::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	view;
	proj;
}

/// <summary>
/// 終了処理
/// </summary>
void Object::Finalize()
{

}

/// <summary>
/// 通常の当たり判定を取得する
/// </summary>
/// <param name="type">当たり判定の種類</param>
/// <param name="size">大きさ</param>
/// <returns>ポインター<</returns>
Collision::CollisionBehavior* Object::GetColision(ColisionType type, unsigned int& size) const
{
	//	サイズを返す
	size = static_cast<unsigned int>(m_shapeColision.size());
	//	ポインターを返す
	return m_shapeColision.at(type);
}

/// <summary>
/// 座標を設定する
/// </summary>
/// <param name="position"></param>
void Object::SetPosition(const DirectX::SimpleMath::Vector3& position)
{
	m_position = position;
}

/// <summary>
/// 移動量を設定する
/// </summary>
/// <param name="velocity">移動量</param>
void Object::SetVelocity(const DirectX::SimpleMath::Vector3& velocity)
{
	m_position += velocity;
}

/// <summary>
/// 大きさを設定する
/// </summary>
/// <param name="scale">大きさ</param>
void Object::SetScale(const DirectX::SimpleMath::Vector3& scale)
{
	m_scale = scale;
}

/// <summary>
/// 回転角を設定する
/// </summary>
/// <param name="rotate"></param>
void Object::SetRotate(const DirectX::SimpleMath::Quaternion& rotate)
{
	m_rotate = rotate;
}

/// <summary>
/// 角度を設定する
/// </summary>
/// <param name="angle"></param>
void Object::SetAngle(const float& angle)
{
	m_angle = angle;
}

/// <summary>
/// IDを設定する
/// </summary>
/// <param name="id"></param>
void Object::SetType(const Object::ObjectType& obj)
{
	m_objType = obj;
}
