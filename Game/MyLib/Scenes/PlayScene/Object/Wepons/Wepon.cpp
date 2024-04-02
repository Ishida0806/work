//
//		File Name ： Wepon.cpp
//		Production： 2023/6/19
//		Author　　： 石田 恭一
// 
//		剣の動作・描画をまとめたクラス	
//	
#include "pch.h"
#include "Wepon.h"
#include "../Player.h"

//	オフセット角度
const float Wepon::OFFSET_ANGLE			= 120.0f;
//	武器を攻撃をする時の角度
const float Wepon::SWING_ANGLE			= 150.0f;
//	振る速度
const float Wepon::SWING_SPEED			= 0.34f;
//	球の半径
const float Wepon::SPHERE_RADIUS		= 0.1f;
//	ラープの時間
const float Wepon::LERP_TIME			= 0.4f;
//	振り向く速度
const float Wepon::TURN_SPEED			= 0.12f;
//	剣を振り終えて次に振れるまでの時間		
const float Wepon::SWING_COOLTIME		= 0.54f;
//	剣を振り二回目を振れる可能時間	
const float Wepon::SWING_SECOND_CHANCE	 = SWING_COOLTIME / 2.0f;
//	剣の地面の位置
const float Wepon::GROUND_SORD_POSITION  = -0.082f;
//	線分の始め
const DirectX::SimpleMath::Vector3 Wepon::SEGMENT_LENGTH_START	= DirectX::SimpleMath::Vector3(0.0f, 5.0f, 0.0f);
//	線分の終わり
const DirectX::SimpleMath::Vector3 Wepon::SEGMENT_LENGTH_END		= DirectX::SimpleMath::Vector3(0.0f,  0.3f, 0.0f);
//	剣のオフセット位置
const DirectX::SimpleMath::Vector3 Wepon::SORD_OFFSET_POSITION	= DirectX::SimpleMath::Vector3(0.25f, 0.4f, 0.0f);
//	剣が転がる向き
const DirectX::SimpleMath::Vector3 Wepon::SORD_ROLL_DIRECTION	= DirectX::SimpleMath::Vector3(0.0f, 0.0f, -0.02f);
//	剣の落ちる速度
const DirectX::SimpleMath::Vector3 Wepon::SORD_FALL_SPEED		= DirectX::SimpleMath::Vector3(0.0f, -0.011f, 0.0f);

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="parent">親</param>
Wepon::Wepon(Player* parent)
	:m_parent(parent),
	m_sordModel(nullptr),
	m_attackTime(SWING_COOLTIME),
	m_slashAngle(0.0f),
	m_objective(0.0f),
	m_isAttack(false),
	m_secondAttack(false)
{

}

/// <summary>
/// デストラクタ
/// </summary>
Wepon::~Wepon()
{
}

/// <summary>
/// 初期化処理
/// </summary>
void Wepon::Initialize()
{
	CreateDeviceDependentResources();
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="timer">タイマー</param>
void Wepon::Update(const DX::StepTimer& timer)
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
void Wepon::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	UNREFERENCED_PARAMETER(view);
	UNREFERENCED_PARAMETER(proj);
}

/// <summary>
/// 終了処理
/// </summary>
void Wepon::Finalize()
{
}

/// <summary>
/// デバイス依存の物を初期化
/// </summary>
void Wepon::CreateDeviceDependentResources()
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
void Wepon::Attack(const DX::StepTimer& timer)
{
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

	//	経過時間を足す
	m_attackTime -= static_cast<float>(timer.GetElapsedSeconds());
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
		m_attackTime   = SWING_COOLTIME;
		m_slashAngle   = 0.0f;
		m_objective	   = 0.0f;
		m_isAttack	   = false;
		m_secondAttack = false;
	}
}

/// <summary>
/// ラープを開始する
/// </summary>
void Wepon::AttackLerp()
{
	DirectX::SimpleMath::Quaternion slashRotate = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitX, DirectX::XMConvertToRadians(m_slashAngle));
	m_slashRotate								= DirectX::SimpleMath::Quaternion::Lerp(m_slashRotate, slashRotate, LERP_TIME);
}

/// <summary>
/// 当たり判定を更新
/// </summary>
void Wepon::UpdateColison()
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
void Wepon::UpdateSordLerp()
{
	DirectX::SimpleMath::Quaternion playerRotate = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitX, *m_cursolAngle);
	SetRotate(DirectX::SimpleMath::Quaternion::Lerp(GetRotate(), playerRotate, TURN_SPEED));
}


/// <summary>
/// 剣の死亡時のアニメーション
/// </summary>
void Wepon::SordDeathAniamtion()
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
bool Wepon::ShouldSwingStartFlag()
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
bool Wepon::ShouldSwingSecondFlag()
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
