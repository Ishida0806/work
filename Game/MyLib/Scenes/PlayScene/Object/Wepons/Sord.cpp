//
//		File Name ： Sord.cpp
//		Production： 2023/6/19
//		Author　　： 石田 恭一
// 
//		剣の動作・描画をまとめたクラス	
//	
#include "pch.h"
#include "Sord.h"
#include "../Player.h"

//	オフセット角度
const float Sord::OFFSET_ANGLE			= 120.0f;
//	武器を攻撃をする時の角度
const float Sord::SWING_ANGLE			= 150.0f;
//	振る速度
const float Sord::SWING_SPEED			= 0.34f;
//	球の半径
const float Sord::SPHERE_RADIUS			= 0.1f;
//	ラープの時間
const float Sord::LERP_TIME				= 0.4f;
//	攻撃後のクールタイム
const float Sord::ATTACK_COOL_TIME		= 0.2f;
//	振り向く速度
const float Sord::TURN_SPEED			= 0.12f;
//	剣を振り終えて次に振れるまでの時間		
const float Sord::SWING_COOLTIME		= 0.54f;
//	剣を振り二回目を振れる可能時間	
const float Sord::SWING_SECOND_CHANCE	= SWING_COOLTIME / 2.0f;
//	剣の地面の位置
const float Sord::GROUND_SORD_POSITION  = -0.082f;
//	線分の始め
const DirectX::SimpleMath::Vector3 Sord::SEGMENT_LENGTH_START	= DirectX::SimpleMath::Vector3(0.0f, 5.0f, 0.0f);
//	線分の終わり
const DirectX::SimpleMath::Vector3 Sord::SEGMENT_LENGTH_END		= DirectX::SimpleMath::Vector3(0.0f,  0.3f, 0.0f);
//	剣のオフセット位置
const DirectX::SimpleMath::Vector3 Sord::SORD_OFFSET_POSITION	= DirectX::SimpleMath::Vector3(0.25f, 0.5f, 0.0f);
//	剣が転がる向き
const DirectX::SimpleMath::Vector3 Sord::SORD_ROLL_DIRECTION	= DirectX::SimpleMath::Vector3(0.0f, 0.0f, -0.02f);
//	剣の落ちる速度
const DirectX::SimpleMath::Vector3 Sord::SORD_FALL_SPEED		= DirectX::SimpleMath::Vector3(0.0f, -0.011f, 0.0f);

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="parent">親</param>
Sord::Sord(Player* parent)
	:m_parent(parent),
	m_sordModel(nullptr),
	m_attackTime(SWING_COOLTIME),
	m_slashAngle(0.0f),
	m_objective(0.0f),
	m_attackCoolTime(0.0f),
	m_isAttack(false),
	m_isAttackCoolTime(false),
	m_secondAttack(false)
{

}

/// <summary>
/// デストラクタ
/// </summary>
Sord::~Sord()
{
}

/// <summary>
/// 初期化処理
/// </summary>
void Sord::Initialize()
{
	CreateDeviceDependentResources();
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="timer">タイマー</param>
void Sord::Update(const DX::StepTimer& timer)
{
    //  攻撃を開始
	Attack(timer);
	//	攻撃させたものを移動
	AttackLerp();
	//	当たり判定を更新
	UpdateColison();
	//	剣の回転角を更新する
	UpdateSordLerp();
}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="view">ビュー</param>
/// <param name="proj">プロジェクション</param>
void Sord::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	//	コモンステート
	DirectX::CommonStates* state				 = MyLib::ScreenResources::GetInstance()->GetCommonState();
	//	コンテキスト
	auto context								 = MyLib::ScreenResources::GetInstance()->GetDeviceContext();

	// 移動行列の作成
	DirectX::SimpleMath::Matrix  trans;

	if (m_parent->IsDeathAnimation())
	{
		trans = DirectX::SimpleMath::Matrix::CreateTranslation(GetPosition());
	}
	else
	{
		trans = DirectX::SimpleMath::Matrix::CreateTranslation(m_parent->GetPosition() + SORD_OFFSET_POSITION);
	}	
	// 回転行列の作成
	DirectX::SimpleMath::Matrix  rotation = DirectX::SimpleMath::Matrix::CreateFromQuaternion(GetRotate() * m_slashRotate * m_offsetRotate );
	// ワールド行列の作成（回転、移動を適用）
	m_sordMatrix = rotation * trans;
	// モデルの描画
	m_sordModel->Draw
	(
		context,
		*state,
		m_sordMatrix,
		view, 
		proj
	);
}

/// <summary>
/// 終了処理
/// </summary>
void Sord::Finalize()
{
}

/// <summary>
/// デバイス依存の物を初期化
/// </summary>
void Sord::CreateDeviceDependentResources()
{
	//	剣のモデルを取得する
	m_sordModel = MyLib::ResourcesData::GetInstance()->GatModel(L"Sord");
	//	当たり判定の半径を初期化
	m_sordCapusel.radius		= SPHERE_RADIUS;
	//	線分の最初
	m_sordCapusel.segment.start = SEGMENT_LENGTH_START;
	//	線分の最後
	m_sordCapusel.segment.end	= SEGMENT_LENGTH_END;
	//	回転のオフセット値
	m_offsetRotate = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitZ, DirectX::XMConvertToRadians(90.0f)) *
		DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY,			   DirectX::XMConvertToRadians((-150.0f)));
	//	識別子を登録する
	SetType(ObjectType::Sord);
}

/// <summary>
/// 攻撃
/// </summary>
/// <param name="timer"></param>
void Sord::Attack(const DX::StepTimer& timer)
{
	//	経過時間を足す
	float elapsedTime = static_cast<float>(timer.GetElapsedSeconds());

	//auto mouse = MyLib::InputSystem::GetInstance()->GetStateTracker();

	//	攻撃クールタイムは発生中か？
	if (m_isAttackCoolTime)
	{
		//	経過時間を引く
		m_attackCoolTime -= elapsedTime;

		//	終わっているなら直ちに終了する && いないなら帰れ
		if (m_attackCoolTime < 0.0f)
		{
			m_isAttackCoolTime = false;
		}
		else
		{
			return;
		}
	}

	//	攻撃条件を満たしているか
	if (ShouldSwingStartFlag())
	{
		m_isAttack = true;
		m_objective = m_slashAngle + SWING_ANGLE;
		//	音を再生する
		AudioManager::GetInstance()->PlaySoundEffectSE(L"Swing_Sword_SE01");
	}

	//	攻撃中じゃないなら処理を行わない
	if (!m_isAttack)	return;
	//	経過時間を引く
	m_attackTime -= elapsedTime;
	//	ラープさせる
	m_slashAngle = Utility::Lerp(m_slashAngle, m_objective, SWING_SPEED);

	//	振れる条件
	if (m_attackTime > 0.0f && m_attackTime <= SWING_SECOND_CHANCE && ShouldSwingSecondFlag())
	{
		m_attackTime += SWING_COOLTIME / 2.f;
		m_secondAttack = true;
		m_objective -= SWING_ANGLE;

		//	音を再生する
		AudioManager::GetInstance()->PlaySoundEffectSE(L"Swing_Sword_SE02");		
	}

	//	攻撃を終えるまでの時間
	if (m_attackTime < 0.0f)
	{
		m_attackTime	   = SWING_COOLTIME;
		m_attackCoolTime   = ATTACK_COOL_TIME;
		m_slashAngle	   = 0.0f;
		m_objective		   = 0.0f;
		m_secondAttack	   = false;
		m_isAttack		   = false;
		m_isAttackCoolTime = true;
	}
}

/// <summary>
/// ラープを開始する
/// </summary>
void Sord::AttackLerp()
{
	DirectX::SimpleMath::Quaternion slashRotate = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitX, DirectX::XMConvertToRadians(m_slashAngle));
	m_slashRotate								= DirectX::SimpleMath::Quaternion::Lerp(m_slashRotate, slashRotate, LERP_TIME);
}

/// <summary>
/// 当たり判定を更新
/// </summary>
void Sord::UpdateColison()
{
	//	線分の最初と最後の値を初期化
	m_sordCapusel.segment.start = SEGMENT_LENGTH_START;
	m_sordCapusel.segment.end	= SEGMENT_LENGTH_END;
	//	現在地に当たり判定を大きさ分移動する
	m_sordCapusel.segment.start = DirectX::SimpleMath::Vector3::Transform(m_sordCapusel.segment.start, m_sordMatrix);
	m_sordCapusel.segment.end	= DirectX::SimpleMath::Vector3::Transform(m_sordCapusel.segment.end,   m_sordMatrix);
}

/// <summary>
/// 剣の回転角を更新する
/// </summary>
void Sord::UpdateSordLerp()
{
	//	プレイヤーの回転角をX軸
	DirectX::SimpleMath::Quaternion playerRotate = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitX, m_parent->GetRotate().ToEuler().y);
	SetRotate(DirectX::SimpleMath::Quaternion::Lerp(GetRotate(), playerRotate, TURN_SPEED));
}


/// <summary>
/// 剣の死亡時のアニメーション
/// </summary>
void Sord::SordDeathAniamtion()
{
	using namespace DirectX::SimpleMath;

	if (GetPosition().y <= GROUND_SORD_POSITION)
	{
		SetPosition(GetPosition() +  Vector3::Transform(SORD_ROLL_DIRECTION, m_parent->GetRotate()));

		return;
	}

	SetPosition(GetPosition() + SORD_FALL_SPEED);
}

/// <summary>
/// 攻撃を振る最初の条件を満たしているか
/// </summary>
/// <returns>条件を満たしているか</returns>
bool Sord::ShouldSwingStartFlag()
{
	auto mouse  = MyLib::InputSystem::GetInstance()->GetStateTracker();
	auto key	= MyLib::InputSystem::GetInstance()->GetKeyTracer();

	if (
		mouse->leftButton == mouse->PRESSED && !m_isAttack ||
		key->pressed.K && !m_isAttack
		)
	{
		return true;
	}

	return false;
}

/// <summary>
/// 攻撃を振る二回目の条件を満たしているか
/// </summary>
/// <returns>条件を満たしているか</returns>
bool Sord::ShouldSwingSecondFlag()
{
	auto mouse = MyLib::InputSystem::GetInstance()->GetStateTracker();
	auto key   = MyLib::InputSystem::GetInstance()->GetKeyTracer();

	if (
		mouse->leftButton == mouse->PRESSED && !m_secondAttack && m_isAttack ||
		key->pressed.K						&& !m_secondAttack && m_isAttack
		)
	{
		return true;
	}

	return false;
}
