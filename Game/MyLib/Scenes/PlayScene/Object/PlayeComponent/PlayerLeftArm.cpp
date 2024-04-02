//
//		File Name ： PlayerLeftArm.cpp
//		Production： 2023/12/27
//		Author　　： 石田 恭一	
// 
//		プレイヤーの各パーツたち
//	
#include "pch.h"
#include "PlayerLeftArm.h"

//	死亡時の加速
const DirectX::SimpleMath::Vector3 PlayerLeftArm::DEATH_ACCELERATION = DirectX::SimpleMath::Vector3(-0.35f, -0.025f, -0.020f);
//	歩く際の揺れる
const float						   PlayerLeftArm::CORRECTION_SPEED	 = 0.0125f;
//	時間の加速度
const float						   PlayerLeftArm::ACCELERATION_TIMER = 5.0f;
//	座標を戻す速度
const float						   PlayerLeftArm::RETURN_SPEED		 = 0.1f;


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="root">ルート</param>
/// <param name="paren">親</param>
PlayerLeftArm::PlayerLeftArm(Player* root, Object* parent)
	:PlayerComponent(root, parent),
	m_model(nullptr),
	m_elapsedTime(0.0f)
{

}

/// <summary>
/// デストラクタ
/// </summary>
PlayerLeftArm::~PlayerLeftArm()
{
}

/// <summary>
/// 初期化する
/// </summary>
void PlayerLeftArm::Initialize()
{
	m_model = MyLib::ResourcesData::GetInstance()->GatModel(L"playerLeftArm");
}

/// <summary>
/// 部品を更新する
/// </summary>
/// <param name="timer">タイマー</param>
void PlayerLeftArm::UpdateParts(const DX::StepTimer& timer)
{
	UNREFERENCED_PARAMETER(timer);

	using namespace DirectX::SimpleMath;
	//	経過時間を足す
	if (GetRoot()->IsWalk())
	{
		m_elapsedTime += static_cast<float>(timer.GetElapsedSeconds());
		//	腕を上下に揺らす
		SetPosition(GetPosition() + DirectX::SimpleMath::Vector3(0.0f, 0.0f, sinf(m_elapsedTime * ACCELERATION_TIMER) * CORRECTION_SPEED));
	}
	else
	{
		m_elapsedTime = 0.0f;
		SetPosition(DirectX::SimpleMath::Vector3::Lerp(GetPosition(), DirectX::SimpleMath::Vector3::Zero, RETURN_SPEED));
	}
	//	元の位置の戻す
	SetPosition(DirectX::SimpleMath::Vector3::Lerp(GetPosition(), DirectX::SimpleMath::Vector3::Zero, RETURN_SPEED));
}

/// <summary>
/// 死亡アニメーション
/// </summary>
/// <param name="timer">タイマー</param>
void PlayerLeftArm::DeathAnimation(const DX::StepTimer& timer)
{
	UNREFERENCED_PARAMETER(timer);
}

/// <summary>
/// 勝利アニメーション
/// </summary>
/// <param name="timer">タイマー</param>
void PlayerLeftArm::WinAnimation(const DX::StepTimer& timer)
{
	using namespace DirectX::SimpleMath;

	//if (m_elapsedTime == 0.0f)
	//{
	//	//	初回入場時初期化
	//	SetRotate(DirectX::SimpleMath::Quaternion::Identity);
	//}

	m_elapsedTime += static_cast<float>(timer.GetElapsedSeconds());

	SetRotate(Quaternion(GetRotate() * Quaternion::CreateFromAxisAngle(Vector3::UnitY, DirectX::XMConvertToRadians(-sinf(m_elapsedTime * 5.0f) * 3.f))));
	SetRotate(Quaternion(GetRotate() * Quaternion::CreateFromAxisAngle(Vector3::UnitZ, DirectX::XMConvertToRadians(-sinf(m_elapsedTime * 5.0f) * 3.f))));

	SetPosition(Vector3(0.0f, 1.7f, 0.0f));
}

/// <summary>
/// モデルの描画
/// </summary>
/// <param name="model">モデル</param>
/// <param name="world">ワールド</param>
/// <param name="view">ビュー</param>
/// <param name="proj">プロジェクション</param>
void PlayerLeftArm::DrawModel(DirectX::Model* model, const DirectX::SimpleMath::Matrix& world, const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	UNREFERENCED_PARAMETER(world);
	UNREFERENCED_PARAMETER(model);


	DirectX::SimpleMath::Quaternion parentRotate;

	//	死亡中か？
	if (GetRoot()->IsDeathAnimation())	parentRotate = GetParent()->GetRotate() * GetRotate();
	else								parentRotate = GetRoot()->GetRotate() * GetRotate();

	//	移動行列
	DirectX::SimpleMath::Matrix trans = DirectX::SimpleMath::Matrix::CreateTranslation(GetRoot()->GetPosition() + GetPosition());
	//	回転行列
	DirectX::SimpleMath::Matrix rotate = DirectX::SimpleMath::Matrix::CreateFromQuaternion(parentRotate);
	//	拡大行列
	DirectX::SimpleMath::Matrix scale = DirectX::SimpleMath::Matrix::CreateScale(GetRoot()->GetScale());
	//	ワールド
	DirectX::SimpleMath::Matrix wrd = scale * rotate * trans;

	PlayerComponent::DrawModel(m_model, wrd, view, proj);
}