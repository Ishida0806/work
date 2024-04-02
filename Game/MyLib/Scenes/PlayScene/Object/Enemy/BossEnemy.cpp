//
//		File Name ： BossEnemy.cpp
//		Production： 2023/11/12
//		Author　　： 石田 恭一	
// 
//		ボスの敵のクラス
//	
#include "pch.h"
#include "BossEnemy.h"

#include "Game/MyLib/Scenes/PlayScene/Object/Bullet/BulletFactroy.h"

//	敵が歩く速度
const float						BossEnemy::BOSS_SPEED		= 0.04f;
//	振り向く速さ
const float						BossEnemy::LERP_SPEED		= 0.03f;
//	クランプ用の壁
const float						BossEnemy::WALL_PLACE		= 23.5f;
//	敵が持っている弾の数
const int						BossEnemy::BOSS_BULLETS_NUM	= 50;
//	ボスの経験値
const int						BossEnemy::BOSS_EXP			= 30;
//	球を打つまでのカウント
const float						BossEnemy::SHOT_TIME		= 0.71f;
//	最初に与えられる力
const int						BossEnemy::FIRST_POWER		= 1;
//	初期設定の体力
const int						BossEnemy::FIRST_HEALTH		= 30;
//	影の大きさ
const float						BossEnemy::SHADOW_SCALE		= 7.2f;
//	死亡アニメーションの際に引く値
const float						BossEnemy::SHADOW_ARGUMENT	= 0.072f;
//	死亡アニメーションの際に引く値
const float						BossEnemy::SCALE_ARGUMENT	= 0.01f;
//	当たり判定
const Collision::Shape::Sphere	BossEnemy::SPERE_COLLISION	= Collision::Shape::Sphere(DirectX::SimpleMath::Vector3::Zero, 1.2f);
//	球状の索敵範囲
const Collision::Shape::Sphere	BossEnemy::SEARCH_COLLISION = Collision::Shape::Sphere(DirectX::SimpleMath::Vector3::Zero, 15.0f);
//	球状の発射可能範囲
const Collision::Shape::Sphere	BossEnemy::SHOT_COLLISION	= Collision::Shape::Sphere(DirectX::SimpleMath::Vector3::Zero, 13.5f);

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="position">座標</param>
/// <param name="helath">体力</param>
/// <param name="power">力</param>
/// <param name="level">レベル</param>
/// <param name="obj">オブジェクトのタイプ</param>
BossEnemy::BossEnemy(const DirectX::SimpleMath::Vector3& position, const int& helath, const int& power, const int& level, ObjectType obj)
	:
	Enemy(position, helath, power, BOSS_EXP), 
	m_level(level),
	m_objType(obj),
	m_isShot(false),
	m_isSeartch(false),
	m_direction(Direction::BOTTOM),
	m_shadowScale(SHADOW_SCALE),
	m_scale(1.0f),
	m_randomTime(0.0f),
	m_shotInterval(0.0f)
{
}

/// <summary>
/// デストラクタ
/// </summary>
BossEnemy::~BossEnemy()
{
}

/// <summary>
/// 初期化処理
/// </summary>
void BossEnemy::Initialize()
{
	//	敵のモデルを取得
	m_bossModel = MyLib::ResourcesData::GetInstance()->GatModel(L"bossEnemy");
	//	当たり判定の追加
	AddColisionEnemy
	(
		SPERE_COLLISION,
		SEARCH_COLLISION,
		SHOT_COLLISION
	);
	//	識別子を設定する
	SetType(m_objType);
	//	基底クラスの初期化
	Enemy::Initialize();
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="timer">タイマー</param>
void BossEnemy::Update(const DX::StepTimer& timer)
{
	//	生きているか
	IsAlive();

	///	死亡アニメーション中なら処理を行わない
	if (IsDeadAnimation())	return;

	//	追尾状態に入るまで索敵モードにする
	if (!IsHate())
	{
		//	敵を自動移動させる
		AutoMove(timer, BOSS_SPEED, LERP_SPEED);
	}
	else
	{
		//	プレイヤーを追尾
		HateMode(timer);
	}

	// 壁判定
	Enemy::Update(timer);
}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="view">ビュー</param>
/// <param name="proj">プロジェクション</param>
void BossEnemy::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	auto screen = MyLib::ScreenResources::GetInstance();

	//	丸影を作成
	CreateShadow(view, proj, m_shadowScale);

	DirectX::SimpleMath::Matrix scale	= DirectX::SimpleMath::Matrix::CreateScale(m_scale);
	DirectX::SimpleMath::Matrix trans	= DirectX::SimpleMath::Matrix::CreateTranslation(GetPosition());
	DirectX::SimpleMath::Matrix rotate  = DirectX::SimpleMath::Matrix::CreateFromQuaternion(GetRotate());

	DirectX::SimpleMath::Matrix world	= scale * rotate * trans;

	if (IsDeadAnimation())
	{
		m_bossModel->Draw(screen->GetDeviceContext(), *screen->GetCommonState(), world, view, proj, true);
	}
	else
	{
		m_bossModel->Draw(screen->GetDeviceContext(), *screen->GetCommonState(), world, view, proj);
	}
}

/// <summary>
/// 終了処理
/// </summary>
void BossEnemy::Finalize()
{
}

/// <summary>
/// 特殊効果を設定する
/// </summary>
/// <param name="flag"></param
void BossEnemy::SetAbility(const bool& flag)
{
	m_isShot = flag;
}

/// <summary>
/// 生きているか？
/// </summary>
void BossEnemy::IsAlive()
{
	//	体力が0以下なら死亡アニメーションを行う
	if (GetHealth() >= 0)	return;
	
	//	デスアニメーション前に音を出す
	if (!IsDeadAnimation())
	//	SEを再生する
	AudioManager::GetInstance()->PlaySoundEffectSE(L"Deth_AnimationSE01");

	//	死亡アニメーションを実行
	StartDeathAnimation();

	//	影と自身の大きさを縮小する
	m_shadowScale -= SHADOW_ARGUMENT;
	m_scale		  -= SCALE_ARGUMENT;

	if (m_scale < 0.0f)
	{
		//	0以下なら殺す
		DeathObject();
	}	
}

/// <summary>
/// 追尾状態
/// </summary>
/// <param name="timer">タイマー　　</param>
void BossEnemy::HateMode(const DX::StepTimer& timer)
{

	auto offset = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(90.0f));

	SetRotate(DirectX::SimpleMath::Quaternion::Lerp(GetRotate(), GetObjectiveRotate() * offset, LERP_SPEED));

	//	発射圏内に入っていなかったら追従する
	if (!InAbility())
	{
		//	発射圏内から少しでも抜けたら初期化
		m_shotInterval = 0.0f;
		// キャラクターの位置から目標位置へのベクトルを計算
		DirectX::SimpleMath::Vector3 direction = GetTargetPosition() - GetPosition();
		// ベクトルを正規化して速度をかける
		direction.Normalize();
		DirectX::SimpleMath::Vector3 velocity = direction * BOSS_SPEED;
		// 位置を更新
		SetVelocity(velocity);
	}
	else
	{
		// キャラクターの位置から目標位置へのベクトルを計算
		DirectX::SimpleMath::Vector3 direction = GetTargetPosition() - GetPosition();
		//	距離
		float distance = direction.Length();

		//	一定の距離を保つ
		if (distance >= 12.0f)
		{
			// ベクトルを正規化して速度をかける
			direction.Normalize();
			DirectX::SimpleMath::Vector3 velocity = direction * BOSS_SPEED;
			// 位置を更新
			SetVelocity(velocity);
		}
		else
		{
			// ベクトルを正規化して速度をかける
			direction.Normalize();
			DirectX::SimpleMath::Vector3 velocity = direction * BOSS_SPEED;
			// 位置を更新
			SetVelocity(-velocity);
		}

		m_shotInterval += static_cast<float>(timer.GetElapsedSeconds());

		//	発射範囲に入っているなら弾を発射する
		if (m_shotInterval <= SHOT_TIME)	return;
		
		m_isShot = true;
		m_shotInterval = 0.0f;
	}
}