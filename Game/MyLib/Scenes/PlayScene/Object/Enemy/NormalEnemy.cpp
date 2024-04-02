//
//		File Name ： NormalEnemy.cpp
//		Production： 2023/11/12
//		Author　　： 石田 恭一	
// 
//		通常の敵のクラス
//	
#include "pch.h"
#include "NormalEnemy.h"

#include "Game/MyLib/Scenes/PlayScene/Object/Bullet/BulletFactroy.h"

//	敵が歩く速度
const float NormalEnemy::ENEMY_SPEED							= 0.047f;
//	振り向く速さ
const float NormalEnemy::LERP_SPEED								= 0.03f;
//	クランプ用の壁
const float NormalEnemy::WALL_PLACE								= 23.5f;
//	敵が持っている弾の数
const int   NormalEnemy::ENEMY_BULLETS_NUM						= 100;
//	球を打つまでのカウント
const float NormalEnemy::SHOT_TIME								= 0.86f;
//	ランダムで移動方向が変わる時間
const float NormalEnemy::RANDOM_TIME							= 3.5f;
//	最初に与えられる力
const int   NormalEnemy::FIRST_POWER							= 2;
//	初期設定の体力
const int   NormalEnemy::FIRST_HEALTH							= 15;
//	ノーマルの経験値
const int   NormalEnemy::NORMAL_EXP								= 3;
//	死亡アニメーションの際に引く値
const float NormalEnemy::SHADOW_ARGUMENT						= 0.02f;
//	当たり判定
const Collision::Shape::Sphere	   NormalEnemy::SPERE_COLLISION		= Collision::Shape::Sphere(DirectX::SimpleMath::Vector3::Zero, 0.6f);
//	球状の索敵範囲
const Collision::Shape::Sphere	   NormalEnemy::SEARCH_COLLISION	= Collision::Shape::Sphere(DirectX::SimpleMath::Vector3::Zero, 10.2f);
//	球状の発射可能範囲
const Collision::Shape::Sphere	   NormalEnemy::SHOT_COLLISION		= Collision::Shape::Sphere(DirectX::SimpleMath::Vector3::Zero, 9.6f);
//	死亡アニメーションの際に引く値
const DirectX::SimpleMath::Vector3 NormalEnemy::SCALE_ARGUMENT		= DirectX::SimpleMath::Vector3(0.01f, 0.01f, 0.01f);
//	通常の大きさ
const DirectX::SimpleMath::Vector3 NormalEnemy::DEFAULT_SCALE		= DirectX::SimpleMath::Vector3(0.55f, 0.55f, 0.55f);

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="position">座標</param>
/// <param name="helath">体力</param>
/// <param name="power">力</param>
/// <param name="level">レベル</param>
/// <param name="obj">オブジェクトのタイプ</param>
NormalEnemy::NormalEnemy(const DirectX::SimpleMath::Vector3& position, const int& helath, const int& power, const int& level, ObjectType obj)
	:
	Enemy(position, helath, power, NORMAL_EXP), 
	m_level(level),
	m_objType(obj),
	m_isShot(false),
	m_inShot(false),
	m_direction(Direction::BOTTOM),
	m_shotInterval(0.0f),
	m_shotCoolTime(0.0f),
	m_shadowScale(1.2f)
{
}

/// <summary>
/// デストラクタ
/// </summary>
NormalEnemy::~NormalEnemy()
{
}

/// <summary>
/// 初期化処理
/// </summary>
void NormalEnemy::Initialize()
{
	//	敵のモデルを取得
	m_enemyModel = MyLib::ResourcesData::GetInstance()->GatModel(L"normalEnemy");
	//	通常の大きささ
	SetScale(DEFAULT_SCALE);
	//	敵の足を作成
	m_enemyLeg = std::make_unique<EnemyLeg>(this, MyLib::ResourcesData::GetInstance()->GatModel(L"normalEnemyLeg"));
	//	初期化処理
	m_enemyLeg->Initialize();

	//	判定の追加
	Enemy::AddColisionEnemy
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
void NormalEnemy::Update(const DX::StepTimer& timer)
{
	using namespace DirectX::SimpleMath;

	//	生きているか
	IsAlive();

	//	地面に埋もれないように
	SetPosition(Vector3(GetPosition().x, 0.0f, GetPosition().z));

	///	死亡アニメーション中なら処理を行わない
	if (IsDeadAnimation())	return;

	//	追尾状態に入るまで索敵モードにする
	if (!IsHate())
	{
		//	敵を自動移動させる
		AutoMove(timer, ENEMY_SPEED, LERP_SPEED);
	}
	else
	{
		//	プレイヤーを追尾
		HateMode(timer);
	}

	//	発射時のアニメーション
	m_shotAnimationScale = DirectX::SimpleMath::Vector3::Lerp(m_shotAnimationScale, DirectX::SimpleMath::Vector3(m_shotInterval / 2.8f, m_shotInterval / 2.8f, 0.0f), 0.1f);
	//	発射時のアニメーション
	m_shotAnimationAfterScale = DirectX::SimpleMath::Vector3::Lerp(m_shotAnimationAfterScale, DirectX::SimpleMath::Vector3(0.0f, -m_shotCoolTime / 3.6f, 0.0f), 0.1f);

	// 基底クラスを設定する
	Enemy::Update(timer);

	//	足を回す
	m_enemyLeg->RollLeg(timer, 7.0f);
}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="view">ビュー</param>
/// <param name="proj">プロジェクション</param>
void NormalEnemy::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	auto screen = MyLib::ScreenResources::GetInstance();
	//	足の描画
	m_enemyLeg->Render(view, proj);
	//	丸影を作る
	CreateShadow(view, proj, m_shadowScale);
	// スケール行列
	DirectX::SimpleMath::Matrix scale = DirectX::SimpleMath::Matrix::CreateScale(GetScale() + m_shotAnimationScale + m_shotAnimationAfterScale);
	// 位置行列
	DirectX::SimpleMath::Matrix trans = DirectX::SimpleMath::Matrix::CreateTranslation(GetPosition());
	// 回転行列
	DirectX::SimpleMath::Matrix rotate = DirectX::SimpleMath::Matrix::CreateFromQuaternion(GetRotate()); 
	// ワールド変換行列に変換（スケール、回転、位置の順で適用）
	DirectX::SimpleMath::Matrix world = scale * rotate * trans;
	// 敵が無敵状態または死亡アニメーション中の場合、特殊な描画を行う
	if (IsDeadAnimation())
	{
		m_enemyModel->Draw(screen->GetDeviceContext(), *screen->GetCommonState(), world, view, proj, true);
	}
	else // 通常の描画を行います
	{
		m_enemyModel->Draw(screen->GetDeviceContext(), *screen->GetCommonState(), world, view, proj);
	}

	Enemy::Render(view, proj);
}

/// <summary>
/// 終了処理
/// </summary>
void NormalEnemy::Finalize()
{
}

/// <summary>
/// 特殊効果を設定する
/// </summary>
/// <param name="flag"></param>
void NormalEnemy::SetAbility(const bool& flag)
{
	m_isShot = flag;
}

/// <summary>
/// 生きているか？
/// </summary>
void NormalEnemy::IsAlive()
{
	//	死んでいないなら帰れ
	if (GetHealth() >= 0)	return;

	//	デスアニメーション前に音を出す
	if (!IsDeadAnimation())
		//	SEを再生する
		AudioManager::GetInstance()->PlaySoundEffectSE(L"Deth_AnimationSE01");

	//	死亡アニメーションを実行
	StartDeathAnimation();

	//	自身の大きさと影の大きさを縮小
	SetScale(GetScale() - SCALE_ARGUMENT);
	m_shadowScale -= SHADOW_ARGUMENT;
	//	アニメーションはゼロにする
	m_shotAnimationScale = DirectX::SimpleMath::Vector3::Zero;

	if (GetScale().x < 0.0f && GetScale().y < 0.0f && GetScale().z < 0.0f)
	{
		//	0以下なら殺す
		DeathObject();
	}	
}

/// <summary>
/// 追尾モード
/// </summary>
/// <param name="timer"></param>
void NormalEnemy::HateMode(const DX::StepTimer& timer)
{

	if (m_shotCoolTime > 0.0f)
	{
		m_shotCoolTime -= static_cast<float>(timer.GetElapsedSeconds()); 
		return;
	}
	//	プレイヤーを見るようにする
	SetRotate(DirectX::SimpleMath::Quaternion::Lerp(GetRotate(), GetObjectiveRotate(), LERP_SPEED));

	//	発射圏内に入っていなかったら追従する
	if (!InAbility() && !m_inShot)
	{
		//	歩いている
		SetWalk(true);
		//	発射圏内から少しでも抜けたら初期化
		//	m_shotInterval = 0.0f;
		// 向きを算出する
		DirectX::SimpleMath::Vector3 direction = GetTargetPosition() - GetPosition();
		//	長さがある程度越しているなら追尾モードから抜ける
		if (abs(direction.Length()) > 25.0f)
		{
			SetHate(false);
		}

		// ベクトルを正規化して速度をかける
		direction.Normalize();
		DirectX::SimpleMath::Vector3 vel = direction * ENEMY_SPEED;

		//	移動量を足す
		SetVelocity(vel);
	}
	else
	{
		//	歩いていない
		SetWalk(false);

		//	発射圏内に入った
		m_inShot = true;

		//	経過時間を足す
		m_shotInterval += static_cast<float>(timer.GetElapsedSeconds());

		//	発射範囲に入っているなら弾を発射する
		if (m_shotInterval <= SHOT_TIME)	return;

		m_isShot	   = true;
		m_inShot	   = false;
		m_shotInterval = 0.0f;
		m_shotCoolTime = 1.0f;
	}
}