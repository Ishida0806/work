//
//		File Name ： Player.cpp
//		Production： 2023/6/12
//		Author　　： 石田 恭一	
// 
//		プレイヤーの管理クラス
//	
#include "pch.h"
#include "Player.h"
#include "PlayeComponent/PlayerPartsFactory.h"
#include "../PlayScene.h"


//	衝突事のノックバック	
const float Player::REACTION									 = 0.9f;
//	壁の場所	
const float Player::WALL_PLACE									 = 23.5f;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="playerParam">プレイヤーパラメータ</param>
Player::Player(PlayerData* playerParam)
	:
	m_playerParam(playerParam),
	Object(playerParam->position),
	PlayerStatus(this, playerParam->playerHealth),
	PlayerMove(this),
	m_animationTime(0.0f),
	m_gravity(0.0f),
	m_isAlive(false),
	m_isDeathAnimation(false),
	m_isWinAnimation(false),
	m_isAnimation(false)
{
}

/// <summary>
/// デストラクタ
/// </summary>
Player::~Player()
{
	Finalize();
}

/// <summary>
/// 初期化
/// </summary>
void Player::Initialize()
{
	CreateDeviceDependentResources();
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="timer">タイマー</param>
void Player::Update(const DX::StepTimer& timer)
{
	//	死亡アニメーション中なら帰れ
	if (m_isAnimation || m_isAlive)	return;
	//	プレイヤーステータスの更新
	PlayerStatus::Update(timer);
	//　プレイヤーを動かす
	PlayerMove::MovePlayer();
	//	当たり判定の更新
	UpdateColison();
	//	カーソル更新
	m_cursol->Update(timer);
	//	カーソルの座標を更新
	m_cursorPosition = m_cursol->GetPosition();
	// プレイヤーと剣の更新
	UpdatePlayerAndSordLerp();	
	//	剣の更新
	m_sord->Update(timer);
	//	プレイヤーサークルを更新する
	m_playerArrow->Update(timer);
	//	プレイヤーをステージに留まらせる
	ArriveStage();
	//	プレイヤーパーツの更新
	for (const auto& parts : m_playerParts)	parts->UpdateParts(timer);
}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="view">ビュー</param>
/// <param name="proj">プロジェクション</param>
void Player::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	//	影を作る
	DirectX::SimpleMath::Matrix shadowWorld = DirectX::SimpleMath::Matrix::CreateScale(1.5f, 0.01f, 1.5f) * DirectX::SimpleMath::Matrix::CreateTranslation(GetPosition().x, 0.01f, GetPosition().z);
	//	影を描画する
	m_primitive->Draw
	(
		shadowWorld,
		view,
		proj,
		DirectX::Colors::Black
	);
	//	移動行列
	DirectX::SimpleMath::Matrix trans  = DirectX::SimpleMath::Matrix::CreateTranslation(GetPosition());
	//	回転行列
	DirectX::SimpleMath::Matrix rotate = DirectX::SimpleMath::Matrix::CreateFromQuaternion(GetRotate());
	//	拡大行列
	DirectX::SimpleMath::Matrix scale  = DirectX::SimpleMath::Matrix::CreateScale(GetScale());
	//	ワールド
	DirectX::SimpleMath::Matrix world  = scale * rotate * trans;
	//	勝利アニメーション中は描画しない
	if (!m_isWinAnimation) 
	{ 
		//	カーソルの描画
		m_cursol->Render(view, proj);
		//	剣の描画
		m_sord->Render(view, proj); 
		//	プレイヤーサークルを描画
		m_playerArrow->Render(view, proj);
	}
	//	モデルの描画
	for (const auto& parts : m_playerParts)	parts->DrawModel(nullptr, world, view, proj);	
}

/// <summary>
///	終了処理
/// </summary>
void Player::Finalize()
{
	m_cursol->Finalize();
	m_sord->Finalize();
}

/// <summary>
/// ダメージを反映
/// </summary>
/// <param name="damege">ダメージ</param>
void Player::Damege(const int& damege)
{
	//	無敵タイムじゃないなら帰れ
	if (IsInvincible())	return;
	//	体力を減らす
	SetDamege(damege);
}

/// <summary>
/// ダメージを与える
/// </summary>
/// <param name="damege">ダメージ</param>
/// <param name="direction">どの距離によってるか</param>
void Player::Damege(const int& damege, DirectX::SimpleMath::Vector3 direction, float reaction)
{
	//	無敵タイムじゃないなら帰れ
	if (IsInvincible())	return;
	//	体力を減らす
	SetDamege(damege);
	//	ノックバックを与える
	DirectX::SimpleMath::Vector3 vel = direction * reaction;
	//	少し浮かす
	vel.y += 0.5f;
	//	座標に加算
	SetVelocity(vel);
}

/// <summary>
/// ダメージを与える
/// </summary>
/// <param name="damege">ダメージ量</param>
/// <param name="direction">距離</param>
/// <param name="reaction">ふっとばし量</param>
void Player::Damege(const int& damege, DirectX::SimpleMath::Vector3 direction, const DirectX::SimpleMath::Vector3& reaction)
{
	//	無敵タイムじゃないなら帰れ
	if (IsInvincible())	return;
	//	体力を減らす
	SetDamege(damege);
	//	ノックバックを与える
	DirectX::SimpleMath::Vector3 vel = direction * reaction;
	//	浮かす
	vel.y += 1.0f;
	//	座標に加算
	SetVelocity(vel);
}

/// <summary>
/// 死亡時のアニメーション
/// </summary>
/// <param name="timer">タイマー</param>
/// <param name="flag">フラグ</param>
void Player::DethAnimation(const DX::StepTimer& timer)
{
	using namespace DirectX::SimpleMath;

	if (!m_isDeathAnimation)	return;

	//	経過時間を足す
	m_animationTime += static_cast<float>(timer.GetElapsedSeconds());

	if (m_isDeathAnimation)
	{
		for (const auto& parts : m_playerParts)	parts->DeathAnimation(timer);
		//	ソード死亡アニメーション
		m_sord->SordDeathAniamtion();
	}
	//	死亡アニメーション時間が終わったら確実に殺す
	if (m_animationTime >= m_playerParam->deathAnimationTime)
	{
		m_isAnimation	   = false;
		m_isAlive		   = true;
	}
}

/// <summary>
/// 勝利時のアニメーション
/// </summary>
/// <param name="timer">タイマー</param>
void Player::WinAnimation(const DX::StepTimer& timer)
{
	using namespace DirectX::SimpleMath;

	if (!m_isWinAnimation)	return;

	//	経過時間を足す
	m_animationTime += static_cast<float>(timer.GetElapsedSeconds());

	if (m_isWinAnimation)
	{
		for (const auto& parts : m_playerParts) 
		{ 
			parts->WinAnimation(timer);
		}
	}
	//	勝利アニメーション時間が終わったらフラグを変える
	if (m_animationTime >= m_playerParam->winAnimationTime)
	{
		m_isAnimation = false;
	}
}


/// <summary>
/// 各オブジェクト情報の作成
/// </summary>
void Player::CreateDeviceDependentResources()
{
	//	プレイヤーモデルを取得
	m_playerModel = MyLib::ResourcesData::GetInstance()->GatModel(L"playerHead");
	//	カーソルを作成する
	m_cursol = std::make_unique<Cursor>(GetPosition(), m_cursorRotate, GetAngle());
	m_cursol->Initialize();
	//	剣を作成する
	m_sord = std::make_unique<Sord>(this);
	m_sord->Initialize();

	//	プレイヤーサークル
	m_playerArrow = std::make_unique<PlayerArrow>(
		this,
		MyLib::ResourcesData::GetInstance()->GatModel(L"arrow"),
		&m_cursorPosition,
		&m_cursorRotate
	);
	//	サークルの初期化
	m_playerArrow->Initialize();
	//	球の半径
	m_playerSphere.radius = 0.8f;
	//	球の真ん中
	m_playerSphere.center = GetPosition();
	//　プリミティブバッチの初期化
	m_primitive = DirectX::GeometricPrimitive::CreateSphere(MyLib::ScreenResources::GetInstance()->GetDeviceContext(), 1.0f);
	//	識別子を登録する
	SetType(ObjectType::Player);
	//	当たり判定を追加する
	AddColision(&m_playerSphere, Object::ColisionType::NormalColision);
	//	大きさを設定する
	SetScale(m_playerParam->modelScale);
	//	要素の追加
	m_playerParts.push_back(PlayerPartsFactory::CreatePlayerBody(this, this));
	//	プレイヤーステータスの初期化
	PlayerStatus::Initialize();
}

/// <summary>
/// 生きているか確認する
/// </summary>
/// <returns>死亡状態</returns>
bool Player::HealthCheck()
{
	//	体力が0より大きいなら帰れ
	if (GetHealth() > 0) return false;
	//	体力を0に
	HealthZero();
	//	死亡した
	return true;
}

/// <summary>
/// プレイヤーをステージに留まらせる
/// </summary>
void Player::ArriveStage()
{
	//	プレイヤーの位置を制御する
	float x = Utility::Clamp(GetPosition().x, -WALL_PLACE, WALL_PLACE);
	float y = Utility::Clamp(GetPosition().y,  0.0f		 , 50.0f);
	float z = Utility::Clamp(GetPosition().z, -WALL_PLACE, WALL_PLACE);
	//	重力
	if (y > 0.0f) { m_gravity -= m_playerParam->gravity; }	else  { m_gravity = 0.0f; }
	//	重力
	y += m_gravity;
	//	クランプの制御実装
	SetPosition(DirectX::SimpleMath::Vector3(x, y, z));
}

/// <summary>
///  プレイヤーのアニメーション
/// </summary>
/// <param name="timer">タイマー</param>
void Player::PlayerAnimation(const DX::StepTimer& timer)
{
	//	死亡アニメーション
	if (m_isDeathAnimation) { DethAnimation(timer);}
	//	勝利アニメーション
	if (m_isWinAnimation)	{ WinAnimation(timer); }
}

/// <summary>
/// 試合結果によってアニメーションをかえる
/// </summary>
/// <param name="resultString">試合結果</param>
void Player::WhyGameResult(const std::string& resultString)
{
	//	勝ち
	if (resultString == PlayScene::WIN_STRING)
	{
		m_isWinAnimation = true;
		//	アニメーションを開始する
		m_isAnimation = true;
		//	怖いので初期化
		SetRotate(DirectX::SimpleMath::Quaternion::Identity);
		//	正面を向く
		SetRotate(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY,DirectX::XMConvertToRadians(180.0f)));
	}
	//	負け
	else if(resultString == PlayScene::LOSE_STRING)
	{
		m_isDeathAnimation = true;
		//	アニメーションを開始する
		m_isAnimation = true;
	}
}

/// <summary>
///	コリジョンの更新
/// </summary>
void Player::UpdateColison()
{
	DirectX::SimpleMath::Vector3 posCenter = GetPosition();
	posCenter.y += 1.0f;
	m_playerSphere.center = posCenter;
}

/// <summary>
/// プレイヤーと剣の更新
/// </summary>
void Player::UpdatePlayerAndSordLerp()
{
	//	向きを算出する
	DirectX::SimpleMath::Vector3 dir = m_cursol->GetPosition() - GetPosition();
	//	向いている方向に向く
	m_cursorRotate = DirectX::SimpleMath::Quaternion::FromToRotation(DirectX::SimpleMath::Vector3::Forward, dir);
	//	攻撃中ならラープを行わない
	if (m_sord->IsAttack())	return;
	//	ラープさせる
	SetRotate(DirectX::SimpleMath::Quaternion::Lerp(GetRotate(), m_cursorRotate, m_playerParam->turnSpeed));
}