//
//		File Name ： Enemy.cpp
//		Production： 2023/11/12
//		Author　　： 石田 恭一	
//	
#include "pch.h"
#include "Enemy.h"
#include "Game/MyLib/GameDatas/SteeringBehavior.h"

//	ランダムで移動方向が変わる時間
const float Enemy::RANDOM_TIME			= 1.8f;
//	クランプ用の壁								  
const float Enemy::WALL_PLACE			= 23.5f;
//	ノックバック
const float Enemy::ENEMT_TOUCH_REACTION = 0.055f;
//	無敵の時間
const float Enemy::INVINCIBLE_TIME		= 0.44f;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="position">座標</param>
/// <param name="helath">体力</param>
/// <param name="power">力</param>
/// <param name="enemyEXPoint">敵の経験値</param>
Enemy::Enemy(const DirectX::SimpleMath::Vector3& position, const int& helath, const int& power, const int& enemyEXPoint)
	:
	Object(position),
	m_helath(helath),
	m_maxHelath(helath),
	m_power(power),
	m_enemyEXPoint(enemyEXPoint),
	m_randomTime(RANDOM_TIME),
	m_invincibleTime(0.0f),
	m_wanderOrientation(0.0f),
	m_isHate(false),
	m_isWalk(false),
	m_isAlive(false),
	m_inAbility(false),
	m_isInvincible(false),
	m_deadAnimation(false),
	m_sphere{},
	m_searchSphere{},
	m_abilitySphere{}
{
}

/// <summary>
/// デストラクタ
/// </summary>
Enemy::~Enemy()
{
}

/// <summary>
/// 初期化処理
/// </summary>
void Enemy::Initialize()
{
	ErrorCheck();

	//	当たり判定の更新する
	UpdateColision();

	//	丸影用
	m_primitive = DirectX::GeometricPrimitive::CreateSphere(MyLib::ScreenResources::GetInstance()->GetDeviceContext(), 1.0f);

	//	ハート
	m_heart = std::make_unique<EnemyHeart>(this);
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="timer">タイマー</param>
void Enemy::Update(const DX::StepTimer& timer)
{
	using namespace DirectX::SimpleMath;

	//	生きているか
	IsAlive();

	// 攻撃を確認したら無敵
	Hit(timer);

	//	ハートの更新
	m_heart->Update(timer);

	// 壁判定
	float x = Utility::Clamp(GetPosition().x, -WALL_PLACE, WALL_PLACE);
	float y = GetPosition().y;
	float z = Utility::Clamp(GetPosition().z, -WALL_PLACE, WALL_PLACE);

	// 当たり判定の更新
	UpdateColision();

	//	クランプした値を入れる
	SetPosition(Vector3(x, y, z));
}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="view">ビュープロジェクション</param>
/// <param name="proj">ビュー</param>
void Enemy::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	view;
	proj;

	//	ハートの描画
	//m_heart->Render(view, proj);
}

/// <summary>
/// 丸影を作成
/// </summary>
/// <param name="view">ビュー</param>
/// <param name="proj">プロジェクション</param>
void Enemy::CreateShadow(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj, const float& shadowScale)
{
	DirectX::SimpleMath::Matrix shadowWorld = DirectX::SimpleMath::Matrix::CreateScale(shadowScale, 0.001f, shadowScale) * DirectX::SimpleMath::Matrix::CreateTranslation(GetPosition().x, 0.01f, GetPosition().z + 1.0f);
	m_primitive->Draw(shadowWorld, view, proj, DirectX::SimpleMath::Color(0.0f, 0.0f, 0.0f, 0.5f));
}

/// <summary>
/// 終了処理
/// </summary>
void Enemy::Finalize()
{
}

/// <summary>
/// 自動的に移動を行う
/// </summary>
/// <param name="timer"></param>
void Enemy::AutoMove(const DX::StepTimer& timer, const float& speed, const float& lookBackSpeed)
{
	using namespace DirectX;

	RandomMoveDirection(timer , speed);

	//	歩いている
	m_isWalk = true;

	//	角度をラープさせる
	SimpleMath::Quaternion rotate = SimpleMath::Quaternion::CreateFromAxisAngle(SimpleMath::Vector3::UnitY, XMConvertToRadians(GetAngle()));
	SetRotate(SimpleMath::Quaternion::Lerp(GetRotate(), rotate, lookBackSpeed));

	//	移動量を座標に足す
	//SetVelocity(SteeringBehavior::Wander(this, &m_wanderOrientation, speed, 1.0f, 3.0f, 15.0f));
}

/// <summary>
/// 目標の向きを取得する
/// </summary>
/// <returns>向き</returns>
DirectX::SimpleMath::Quaternion Enemy::GetObjectiveRotate()
{
	//	向きを算出
	DirectX::SimpleMath::Vector3 dir = GetTargetPosition() - GetPosition();
	//	y軸は参照しない
	dir.y = 0.0f;
	//	向きを返す
	return DirectX::SimpleMath::Quaternion::FromToRotation(DirectX::SimpleMath::Vector3::Forward, dir);
}

/// <summary>
/// 敵同士の接触で距離を離す
/// </summary>
/// <param name="direction"></param>
void Enemy::HitEnemyMove(const DirectX::SimpleMath::Vector3& direction)
{
	DirectX::SimpleMath::Vector3 vel = direction * ENEMT_TOUCH_REACTION;
	//	移動量を足す
	SetVelocity(vel);
}

/// <summary>
/// ダメージ与える
/// </summary>
/// <param name="damege">ダメージ</param>
void Enemy::Damege(int damege)
{
	//	ダメージ分体力を減らす
	m_helath -= damege;

	//	無敵にする
	m_isInvincible = true;

	//	無敵タイムをリセットする
	ResetInvincibleTime();

	if (IsHate())	return;

	//	追尾状態に
	m_isHate = true;
}

/// <summary>
///  ワールドレベル
/// </summary>
/// <param name="health">レベル</param>
/// <param name="power">パワー</param>
/// <param name="level">レベル</param>
void Enemy::StatusUP(const int& health, const int& power, const int& level)
{
	//	体力をレベル分増やす
	m_helath = m_helath + (health * level);
	//	力を設定する
	m_power += power * level;
}

/// <summary>
/// ランダムな方向に向きを変える
/// </summary>
/// <param name="timer">タイマー</param>
/// <param name="speed">速度</param>
void Enemy::RandomMoveDirection(const DX::StepTimer& timer, const float& speed)
{
	using namespace DirectX;

	SimpleMath::Vector3 vel = SimpleMath::Vector3::Zero;

	m_randomTime += static_cast<float>(timer.GetElapsedSeconds());

	//	経過で向いてる向きを変える
	if (m_randomTime >= RANDOM_TIME)
	{
		//	4方向をランダムで決める
		int randomDirection = rand() % 4;
		//	出た値を[Direction]型にキャスト
		Direction dir = static_cast<Direction>(randomDirection);
		//	向きを決める
		switch (dir)
		{
		case Direction::LEFT:		m_direction = Direction::LEFT;		break;
		case Direction::TOP:		m_direction = Direction::TOP;		break;
		case Direction::RIGHT:		m_direction = Direction::RIGHT;		break;
		case Direction::BOTTOM:		m_direction = Direction::BOTTOM;	break;
		default:														break;
		}
		//	ランダムするまでの時間を変える
		m_randomTime = 0.0f;
	}

	//	ランダムで指定されたほうを向く
	switch (m_direction)
	{
		//	左向きの場合
	case Enemy::Direction::LEFT:
	{
		SetAngle(90.0f);
		vel.x -= speed;
		break;
	}
	//	上向きの場合
	case Enemy::Direction::TOP:
	{
		SetAngle(180.0f);
		vel.z += speed;
		break;
	}
	//	右向きの場合
	case Enemy::Direction::RIGHT:
	{
		SetAngle(270.0f);
		vel.x += speed;
		break;
	}
	//	下向きの場合
	case Enemy::Direction::BOTTOM:
	{
		SetAngle(0.0f);
		vel.z -= speed;
		break;
	}
	default:	break;
	}

	//	移動量を座標に足す
	SetVelocity(vel);
}

/// <summary>
/// 攻撃を確認したら無敵
/// </summary>
/// <param name="timer">タイマー</param>
void Enemy::Hit(const DX::StepTimer& timer)
{
	// もし無敵でないなら、何もしない
	if (!m_isInvincible) return;

	// 無敵時間を経過時間だけ増加させる
	m_invincibleTime += static_cast<float>(timer.GetElapsedSeconds());

	// もし無敵時間が指定した時間を超えたら何もしない
	if (m_invincibleTime <= INVINCIBLE_TIME)	return;

	// 無敵時間が終わったら初期化する
	ResetInvincibleTime();
	// 無敵状態を解除する
	m_isInvincible = false;
}

/// <summary>
/// 当たり判定の更新
/// </summary>
void Enemy::UpdateColision()
{
	DirectX::SimpleMath::Vector3 pos = GetPosition();
	pos.y = 0.5f;

	//	当たり判定更新
	m_sphere.center = pos;

	//　索敵範囲を判定更新
	m_searchSphere.center = pos;

	//	突撃範囲を判定更新
	m_abilitySphere.center = pos;
}

/// <summary>
/// 目標座標の設定する
/// </summary>
/// <param name="pos">目標座標</param>
void Enemy::SetTargetPosition(const DirectX::SimpleMath::Vector3& pos)
{
	m_targetPos = pos;
}

/// <summary>
/// ヘイト状態を設定する
/// </summary>
void Enemy::SetHate(const bool& flag)
{
	m_isHate = flag;
}

/// <summary>
/// 特殊技能範囲に入ったかのフラグの設定
/// </summary>
/// <param name="flag">フラグ</param>
void Enemy::SetInAbility(const bool& flag)
{
	m_inAbility = flag;
}

/// <summary>
/// 歩いているか
/// </summary>
/// <param name="walk"></param>
void Enemy::SetWalk(const bool& walk)
{
	m_isWalk = walk;
}

/// <summary>
/// ヘイトモードにする
/// </summary>
void Enemy::SetHateMode()
{
	m_isHate = true;
}

/// <summary>
/// 無敵時間をリセットする
/// </summary>
void Enemy::ResetInvincibleTime()
{
	m_invincibleTime = 0.0f;
}

/// <summary>
/// 死亡アニメーションの開始
/// </summary>
void Enemy::StartDeathAnimation()
{
	m_deadAnimation = true;
}

/// <summary>
/// 死亡が確定
/// </summary>
void Enemy::DeathObject()
{
	m_isAlive = true;
}

/// <summary>
/// 当たり判定の追加
/// </summary>
/// <param name="colisionSpere">当たり判定の広さ</param>
/// <param name="searchSpere">索敵範囲</param>
/// <param name="abilitySpere">特殊範囲</param>
void Enemy::AddColisionEnemy(const Collision::Shape::Sphere& colisionSpere, const Collision::Shape::Sphere& searchSpere, const Collision::Shape::Sphere& abilitySpere)
{
	m_sphere		= colisionSpere;
	m_searchSphere  = searchSpere;
	m_abilitySphere = abilitySpere;
}

/// <summary>
/// 無敵判定フラグ
/// </summary>
/// <param name="flag">フラグ</param>
void Enemy::SetInvincibleFlag(bool flag)
{
	m_isInvincible = flag;
}

/// <summary>
/// エラーを確認する
/// </summary>
void Enemy::ErrorCheck()
{
	//	もし当たり判定が追加されていないなら止める
	assert(m_sphere.radius > 0.0f);
	assert(m_searchSphere.radius > 0.0f);
	assert(m_abilitySphere.radius > 0.0f);
}

/// <summary>
/// 生きているか？
/// </summary>
void Enemy::IsAlive()
{

}