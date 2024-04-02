//
//		File Name ： Bullet.cpp
//		Production： 2023/7/02
//		Author　　： 石田 恭一
// 
//		弾の実装を行ったクラス
//
#include "pch.h"
#include "Bullet.h"

//	進行速度
const float						   Bullet::SPEED			= 0.22f;
//	敵弾の速度
const DirectX::SimpleMath::Vector3 Bullet::ENEMY_SPEED		= DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.1f);
//	ボス弾の速度
const DirectX::SimpleMath::Vector3 Bullet::BOSS_SPEED		= DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.15f);
//	反射された際の進む速度
const DirectX::SimpleMath::Vector3 Bullet::REF_SPEED		= DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.25f);
//	敵の弾のあたり判定の大きさ
const float Bullet::BULLET_RADIUS							= 0.4f;
//	ボスの弾のあたり判定の大きさ
const float Bullet::BOSS_BULLET_RADIUS						= 0.5f;


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="ownerID">オーナー</param>
/// <param name="position">座標</param>
/// <param name="rotate">回転角</param>
/// <param name="color">色</param>
/// <param name="power">力</param>
/// <param name="scale">大きさ</param>
/// <param name="used">使用状態</param>
Bullet::Bullet(BulletFactory::OwnerID ownerID, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& rotate, const DirectX::SimpleMath::Color& color, int power, float scale, bool used)
	:
	Object(position, rotate),
	m_ownerID(static_cast<int>(ownerID)),
	m_color(color),
	m_power(power),
	m_scale(scale),
	m_used(used),
	m_refCount(0),
	m_primitive{},
	m_isRefrect(false)
{
}

/// <summary>
/// デストラクタ
/// </summary>
Bullet::~Bullet()
{
}

/// <summary>
/// 初期化処理
/// </summary>
void Bullet::Initialize()
{
	CreateDeviceDependentResources();
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="timer">タイマー</param>
void Bullet::Update(const DX::StepTimer& timer)
{
	using namespace DirectX;
	timer;
	SetVelocity(m_velocity);
	//	移動する 
	SetVelocity(ShotBullet());
	//	Y軸を固定させる	
	SimpleMath::Vector3 position = GetPosition();
	position.y = 0.8f;
	SetPosition(position);
	//	弾の当たり判定に代入する
	position.y = 0.5f;
	m_bulletSphere.center = position;
}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="view">ビュー</param>
/// <param name="proj">プロジェクション</param>
void Bullet::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	//	弾を移動
	DirectX::SimpleMath::Matrix scale = DirectX::SimpleMath::Matrix::CreateScale(m_scale);
	DirectX::SimpleMath::Matrix trans = DirectX::SimpleMath::Matrix::CreateTranslation(GetPosition());
	//	球のワールド
	DirectX::SimpleMath::Matrix world = scale * trans;
	//	反射状態によって描画を変える
	if (m_isRefrect)
	{
		//	プリミティブバッチの描画
		m_primitive->Draw(world, view, proj, DirectX::Colors::White);
	}
	else
	{
		m_primitive->Draw(world, view, proj, m_color);
	}

	//	影を作る
	scale = DirectX::SimpleMath::Matrix::CreateScale(0.3f, 0.01f, 0.3f);
	trans = DirectX::SimpleMath::Matrix::CreateTranslation(GetPosition().x, 0.0f, GetPosition().z);
	//	シャドー行列の作成
	DirectX::SimpleMath::Matrix shadowWorld = scale * trans;
	//	モデルの描画を行う
	m_primitive->Draw(shadowWorld, view, proj, DirectX::SimpleMath::Color(0.0f, 0.0f, 0.0f, 1.0f));	
}

/// <summary>
/// 終了処理
/// </summary>
void Bullet::Finalize()
{

}

/// <summary>
/// 再使用時の初期化処理
/// </summary>
void Bullet::PreInitialize()
{
	m_isRefrect = false;
	//m_refCount  = 3;
	m_velocity  = DirectX::SimpleMath::Vector3::Zero;
}

/// <summary>
/// デバイス依存の初期化
/// </summary>
void Bullet::CreateDeviceDependentResources()
{
	//　プリミティブバッチの初期化
	m_primitive = DirectX::GeometricPrimitive::CreateSphere(MyLib::ScreenResources::GetInstance()->GetDeviceContext(), 1.0f);
	
	//	持ち主によって当たり判定を変える
	if(m_ownerID == static_cast<int>(BulletFactory::OwnerID::ENEMY))		m_bulletSphere.radius = BULLET_RADIUS;
	if(m_ownerID == static_cast<int>(BulletFactory::OwnerID::BOSS))			m_bulletSphere.radius = BOSS_BULLET_RADIUS;
}

/// <summary>
/// 弾を更新する
/// </summary>
/// <returns>VELOCITY</returns>
DirectX::SimpleMath::Vector3 Bullet::ShotBullet()
{
	using namespace DirectX::SimpleMath;

	//	反射状態なら帰れ
	if (m_isRefrect)	return Vector3::Zero;
	//	敵のオーナー
	BulletFactory::OwnerID Owner = static_cast<BulletFactory::OwnerID>(m_ownerID);

	//	所有者によって弾の速度を変える
	switch (Owner)
	{
	//	所有者が敵の場合
	case BulletFactory::OwnerID::ENEMY:	return Vector3::Transform(ENEMY_SPEED, GetRotate());	break;
	//	所有者が敵の場合
	case BulletFactory::OwnerID::BOSS:	return Vector3::Transform(BOSS_SPEED,  GetRotate());	break;
	//	それ以外は帰れ
	default:							return Vector3::Zero;									break;
	}
}

/// <summary>
/// 使用状態を設定する
/// </summary>
/// <param name="used">使用状態</param>
void Bullet::SetUsed(bool used)
{
	m_used = used;
	//	使用状態に移行したら値を初期化
	if (m_used) { PreInitialize(); }
}

/// <summary>
/// 反射を行う
/// </summary>
/// <param name="position">座標</param>
void Bullet::Refrection(const DirectX::SimpleMath::Vector3& position)
{
	//	距離を算出する
	DirectX::SimpleMath::Vector3 direction = GetPosition() - position;
	direction.y = 0.0f;
	direction.Normalize();
	//	反射角に向かって進む
	if (!m_isRefrect) { m_velocity = direction * SPEED; } else { m_velocity = direction * (SPEED * 1.5f); }

	//	反射状態に
	m_isRefrect = true;	
}