//
//		File Name ： TackleEnemy.cpp
//		Production： 2023/11/12
//		Author　　： 石田 恭一	
//	
#include "pch.h"
#include "TackleEnemy.h"

//	敵が歩く速度
const float							  TackleEnemy::ENEMY_SPEED				= 0.05f;
//	振り向く速さ
const float							  TackleEnemy::LOOK_BACK_SPEED			= 0.04f;
//	突撃の速度								    
const float							  TackleEnemy::ENEMY_TACLE_SPEED		= 0.36f;
//	目標値との距離
const float							  TackleEnemy::TACKLE_STOP_DISTANCE		= 0.8f;
//	突進後とどまる時間					     
const float							  TackleEnemy::ALIVE_TIME				= 1.1f;
//	突撃可能までの時間
const float							  TackleEnemy::TACKLE_ENABLED_TIME		= 1.2f;
//	死亡アニメーションの際に引く値
const float							  TackleEnemy::SHADOW_ARGUMENT			= 0.02f;
//	突撃距離
const float							  TackleEnemy::TACKLE_DISTANCE			= 15.0f;
//	スタンタイム
const float							  TackleEnemy::SWOON_TIME				= 2.4f;
//	最初に与えられる力
const int							  TackleEnemy::FIRST_POWER				= 5;
//	タックルの経験値
const int							  TackleEnemy::TACKLE_EXP				= 5;
//	初期設定の体力
const int							  TackleEnemy::FIRST_HEALTH				= 25;
//	死亡アニメーションの際に引く値
const DirectX::SimpleMath::Vector3	  TackleEnemy::SCALE_ARGUMENT			= DirectX::SimpleMath::Vector3(0.01f, 0.01f, 0.01f);
//	通常の大きさ
const DirectX::SimpleMath::Vector3	  TackleEnemy::DEFAULT_SCALE			= DirectX::SimpleMath::Vector3(0.55f, 0.55f, 0.55f);
//	当たり判定
const Collision::Shape::Sphere		  TackleEnemy::SPERE_COLLISION			= Collision::Shape::Sphere(DirectX::SimpleMath::Vector3::Zero, 0.5f);
//	球状の索敵範囲
const Collision::Shape::Sphere		  TackleEnemy::SEARCH_COLLISION			= Collision::Shape::Sphere(DirectX::SimpleMath::Vector3::Zero, 12.0f);
//	球状の発射可能範囲
const Collision::Shape::Sphere		  TackleEnemy::TACKLE_COLLISION			= Collision::Shape::Sphere(DirectX::SimpleMath::Vector3::Zero, 9.7f);
//	突撃線の黄色
const DirectX::SimpleMath::Color	  TackleEnemy::TACKLE_PREDICTION_YELLOW = DirectX::SimpleMath::Color(0.8f, 0.7f, 0.0f, 1.0f);
//	突撃線の赤色
const DirectX::SimpleMath::Color	  TackleEnemy::TACKLE_PREDICTION_RED	= DirectX::SimpleMath::Color(0.7f, 0.0f, 0.0f, 1.0f);


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="position">座標</param>
/// <param name="helath">体力</param>
/// <param name="power">力</param>
/// <param name="level">レベル</param>
/// <param name="obj">オブジェクトのタイプ</param>
TackleEnemy::TackleEnemy(const DirectX::SimpleMath::Vector3& position, int helath, const int& power, int level, ObjectType obj)
	:Enemy(position, helath, power, TACKLE_EXP ),
	m_level(level),
	m_objType(obj),
	m_isTackle(false),
	m_tackleExcute(false),
	m_tackleCoolTime(false),
	m_tackleInterval(0.0f),
	m_tackleAssaultTime(0.0f),
	m_tackledStayTime(0.0f),
	m_swoonTime(0.0f),
	m_shadowScale(1.2f),
	m_tackleState(TackleState::IDLE)
{
}

/// <summary>
/// デストラクタ
/// </summary>
TackleEnemy::~TackleEnemy()
{
}

/// <summary>
/// 初期化処理
/// </summary>
void TackleEnemy::Initialize()
{
	//	モデルを取得
	m_enemyModel = MyLib::ResourcesData::GetInstance()->GatModel(L"enemy_tackle");
	//	通常の大きささ
	SetScale(DEFAULT_SCALE);
	//	当たり判定の追加
	AddColisionEnemy
	(
		SPERE_COLLISION,
		SEARCH_COLLISION,
		TACKLE_COLLISION
	);

	//	最初は-z軸方面に向かせる
	SetRotate(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, GetAngle()));	
	//	突撃範囲用
	m_primitiveBox = DirectX::GeometricPrimitive::CreateBox(MyLib::ScreenResources::GetInstance()->GetDeviceContext(), DirectX::SimpleMath::Vector3(0.5f, 0.008f, 1.0f));
	//	識別子を設定する
	SetType(m_objType);
	//	基底クラスの初期化
	Enemy::Initialize();
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="timer">タイマー</param>
void TackleEnemy::Update(const DX::StepTimer& timer)
{
	using namespace DirectX::SimpleMath;

	//	生きているか
	IsAlive();

	//	地面に埋もれないように
	SetPosition(Vector3(GetPosition().x, 0.0f, GetPosition().z));
	//	死亡アニメーション中なら処理を行わない
	if (IsDeadAnimation())	return;
	//	スタン
	if(Swoon(timer))		return;
	//	追尾状態に入るまで索敵モードにする
	if (!IsHate())
	{
		//	敵を自動移動させる
		AutoMove(timer, ENEMY_SPEED, LOOK_BACK_SPEED);
	}
	else
	{
		//	プレイヤーを追尾
		HateMode(timer);
	}
	//	基底クラスを更新する
	Enemy::Update(timer);
}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="view">ビュー</param>
/// <param name="proj">プロジェクション</param>
void TackleEnemy::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	auto screen = MyLib::ScreenResources::GetInstance();

	//	突撃の予告線を描画
	ComingTackle(view, proj); 
	//	丸影を作る
	CreateShadow(view, proj, m_shadowScale);
	// スケール行列
	DirectX::SimpleMath::Matrix scale = DirectX::SimpleMath::Matrix::CreateScale(GetScale() + m_tackleScale);
	// 位置行列
	DirectX::SimpleMath::Matrix trans = DirectX::SimpleMath::Matrix::CreateTranslation(GetPosition());
	// 回転行列
	DirectX::SimpleMath::Matrix rotate = DirectX::SimpleMath::Matrix::CreateFromQuaternion(GetRotate() * m_swoonRotate);
	// ワールド変換行列に変換（スケール、回転、位置の順で適用）
	DirectX::SimpleMath::Matrix world	= scale * rotate * trans;

	// 敵が無敵状態または死亡アニメーション中の場合、ワイヤーフレームの描画を行う
	if (IsDeadAnimation())
	{
		m_enemyModel->Draw(screen->GetDeviceContext(), *screen->GetCommonState(), world, view, proj, true);
	}
	else
	{
		// 通常の描画を行う
		m_enemyModel->Draw(screen->GetDeviceContext(), *screen->GetCommonState(), world, view, proj);
	}
}

/// <summary>
/// 終了処理
/// </summary>
void TackleEnemy::Finalize()
{
}

/// <summary>
/// プレイヤーヒット
/// </summary>
/// <param name="direction"></param>
/// <param name="nockBack"></param>
void TackleEnemy::HitPlayer(const DirectX::SimpleMath::Vector3& direction, const float& nockBack)
{
	DirectX::SimpleMath::Vector3 vel = direction * nockBack;
	//	移動量を足す
	SetPosition(GetPosition() + vel);
	//	ヒットはしているので突撃状態を終える
	m_tackleState = TackleState::FINISHED;
}

/// <summary>
/// 生きているか？
/// </summary>
void TackleEnemy::IsAlive()
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
	m_tackleScale = DirectX::SimpleMath::Vector3::Zero;

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
void TackleEnemy::HateMode(const DX::StepTimer& timer)
{
	using namespace DirectX::SimpleMath;

	Vector3 vel = Vector3::Zero;

	switch (m_tackleState)
	{
	// タックルが開始されていない場合の処理
	case TackleState::IDLE:
	{
		if (InAbility() && !m_tackleExcute)
		{
			m_tackleExcute = true;
			//	プレイヤーを見るようにする
			m_objectiveRotate = GetObjectiveRotate();
			//	目標座標を設定する
			m_objectivePosition = GetTargetPosition() - Vector3::Transform(Vector3(0.0f, 0.0f, 3.5f), m_objectiveRotate);
		}
		//	突撃範囲内にいるなら
		if (m_tackleExcute)
		{			
			//	突撃時の大きさ
			m_tackleScale -= DirectX::SimpleMath::Vector3(0.002f, 0.002f, 0.002f);

			SetRotate(Quaternion::Lerp(GetRotate(), m_objectiveRotate, LOOK_BACK_SPEED));
			//	経過時間を足す
			m_tackleInterval += static_cast<float>(timer.GetElapsedSeconds());

			//	突撃圏内に入って指定時間たつと突撃に移行する
			if (m_tackleInterval >= TACKLE_ENABLED_TIME)
			{
				m_tackleState = TackleState::ACTIVE;
			}

			return;
		}
		//	向きを取得する
		Vector3 dir = GetTargetPosition() - GetPosition();
		//	離れすぎたら追尾を抜ける
		if (dir.Length() >= TACKLE_DISTANCE)
		{
			SetHate(false);
		}

		//	プレイヤーを見るようにする
		SetRotate(Quaternion::Lerp(GetRotate(), GetObjectiveRotate(), LOOK_BACK_SPEED));
		// キャラクターの位置から目標位置へのベクトルを計算
		Vector3 direction = GetTargetPosition() - GetPosition();
		// ベクトルを正規化して速度をかける
		direction.Normalize();
		vel = direction * ENEMY_SPEED;
		//	移動量を足す
		SetPosition(GetPosition() + vel);

		break;
	}
	// 突撃中の挙動
	case TackleState::ACTIVE:
	{		
		//	突撃前に初期化
		if (!m_isTackle)
		{
			PreTackleInitialize();
		}
		//	段々と戻す
		m_tackleScale = DirectX::SimpleMath::Vector3::Lerp(m_tackleScale, DirectX::SimpleMath::Vector3::Zero, 0.1f);
		//	経過時間を足す
		m_tackleAssaultTime += static_cast<float>(timer.GetElapsedSeconds());
		// タックルを終了すべき条件をチェック
		if (ShouldStopTackle() || m_tackleAssaultTime >= 1.2f)
		{
			// タックルを終了
			m_tackleState = TackleState::FINISHED;
		}

		// タックル中の挙動
		vel = StartTackle(m_objectivePosition, ENEMY_TACLE_SPEED);
		//	移動量を足す
		SetPosition(GetPosition() + vel);

		break;
	}
	// タックルが終了した場合の挙動
	case TackleState::FINISHED:
	{	
		//	突撃は終了
		m_isTackle = false;
		//	経過時間を足す
		m_tackledStayTime += static_cast<float>(timer.GetElapsedSeconds());
		//	少しその場にとどまる
		if (m_tackledStayTime >= ALIVE_TIME)
		{
			//	値を初期化する
			m_tackleInterval = 0.0f;
			m_tackleAssaultTime = 0.0f;
			m_tackledStayTime = 0.0f;
			m_swoonTime = 0.0f;
			m_tackleExcute = false;
			m_tackleState = TackleState::IDLE;
			m_tackleScale = DirectX::SimpleMath::Vector3::Zero;
		}

		break;
	}
	default:	break;
	}
}

/// <summary>
/// タックルの終了条件
/// </summary>
/// <returns></returns>
bool TackleEnemy::ShouldStopTackle()
{
	// タックルを終了すべき条件をチェック
	if ((m_objectivePosition - GetPosition()).Length() <= TACKLE_STOP_DISTANCE && m_isTackle)
	{
		return true;
	}
	
	return false;
}

/// <summary>
/// スタン状態
/// </summary>
/// <param name="timer">タイマー</param>
/// <returns></returns>
bool TackleEnemy::Swoon(const DX::StepTimer& timer)
{
	//	突撃状態なら
	if (m_tackleState == TackleState::SWOON)
	{
		//	敵を回す
		m_swoonRotate *= DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(5.0f));
		//	時間を足す
		m_swoonTime += static_cast<float>(timer.GetElapsedSeconds());
		//	基底クラスを更新する
		Enemy::Update(timer);
		//	スタン状態の半分位までは後ろに下がる
		if (m_swoonTime < SWOON_TIME / 1.5f)
		{
			//	後ろに下がる
			DirectX::SimpleMath::Vector3 BackSpeed = DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(0.0f, 0.0f, ENEMY_SPEED), GetRotate());
			SetPosition(GetPosition() + BackSpeed);
		}
		//	スタン状態
		if (m_swoonTime > SWOON_TIME)
		{
			m_tackleState = TackleState::FINISHED;
		}

		return true;
	}
	else
	{
		m_swoonRotate = DirectX::SimpleMath::Quaternion::Identity;
	}

	return false;
}

/// <summary>
/// 突撃範囲を教えてあげる
/// </summary>
/// <param name="view">ビュー</param>
/// <param name="proj">プロジェクション</param>
void TackleEnemy::ComingTackle(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	using namespace DirectX::SimpleMath;

	//	突撃範囲に入ったら描画 || 死亡アニメーション中は描画しない || 追尾モードは描画しない
	if (IsDeadAnimation() || !IsHate())	return;
	//	描画時間
	float renderTime = TACKLE_ENABLED_TIME / 5.0f;

	//	入った瞬間描画は変なので少し経ったら && 状態が待機状態なら
	if (m_tackleInterval >= renderTime && m_tackleState == TackleState::IDLE)
	{
		// タックル中の挙動
		Matrix world = DirectX::SimpleMath::Matrix::CreateScale(m_tackleInterval * 3.4f, 1.f, 8.0f) * Matrix::CreateTranslation(0.0f, 0.0f, -4.0f) *(Matrix::CreateFromQuaternion(GetRotate())) * Matrix::CreateTranslation(GetPosition());

		//	突撃間際になれば色を変える
		if (m_tackleInterval >= TACKLE_ENABLED_TIME - 0.24f)
		{
			//	予測線の描画
			m_primitiveBox->Draw(world, view, proj, TACKLE_PREDICTION_RED);
		}
		else
		{
			//	予測線の描画
			m_primitiveBox->Draw(world, view, proj, TACKLE_PREDICTION_YELLOW);
		}
	}
}

/// <summary>
/// 指定された速度でついていく
/// </summary>
/// <param name="position">目標座標</param>
/// <param name="speed">速度</param>
/// <returns>移動量</returns>
DirectX::SimpleMath::Vector3 TackleEnemy::StartTackle(const DirectX::SimpleMath::Vector3& position, const float& speed)
{
	// キャラクターの位置から目標位置へのベクトルを計算
	DirectX::SimpleMath::Vector3 direction = position - GetPosition();

	// ベクトルを正規化して速度をかける
	direction.Normalize();
	return  direction * speed;
}

/// <summary>
/// スタン状態にする
/// </summary>
void TackleEnemy::SwoonMode()
{
	m_tackleState = TackleState::SWOON;
}

/// <summary>
/// 突撃の際の初期化処理
/// </summary>
void TackleEnemy::PreTackleInitialize()
{
	m_isTackle = true;
}