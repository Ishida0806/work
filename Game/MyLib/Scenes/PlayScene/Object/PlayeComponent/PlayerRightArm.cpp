//
//		File Name ： PlayerRightArm.cpp
//		Production： 2023/12/27
//		Author　　： 石田 恭一	
// 
//		プレイヤーの各パーツたち
//	
#include "pch.h"
#include "PlayerRightArm.h"

//	歩く際の揺れる
const float						   PlayerRightArm::WALK_SHAKE		  = 0.01f;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="root">ルート</param>
/// <param name="paren">親</param>
PlayerRightArm::PlayerRightArm(Player* root, Object* parent)
	:PlayerComponent(root, parent),
	m_elapsedTime(0.0f),
	m_model(nullptr)
{

}

/// <summary>
/// デストラクタ
/// </summary>
PlayerRightArm::~PlayerRightArm()
{
}

/// <summary>
/// 初期化する
/// </summary>
void PlayerRightArm::Initialize()
{
	m_model = MyLib::ResourcesData::GetInstance()->GatModel(L"playerRightArm");
}

/// <summary>
/// 部品を更新する
/// </summary>
/// <param name="timer">タイマー</param>
void PlayerRightArm::UpdateParts(const DX::StepTimer& timer)
{
	UNREFERENCED_PARAMETER(timer);
}

/// <summary>
/// 死亡アニメーション
/// </summary>
/// <param name="timer">タイマー</param>
void PlayerRightArm::DeathAnimation(const DX::StepTimer& timer)
{
	UNREFERENCED_PARAMETER(timer);
	//	元の位置の戻す
	SetPosition(DirectX::SimpleMath::Vector3::Lerp(GetPosition(), DirectX::SimpleMath::Vector3::Zero, 0.1f));
}

/// <summary>
/// 勝利アニメーション
/// </summary>
/// <param name="timer">タイマー</param>
void PlayerRightArm::WinAnimation(const DX::StepTimer& timer)
{
	using namespace DirectX::SimpleMath;

	m_elapsedTime += static_cast<float>(timer.GetElapsedSeconds());

	SetRotate(Quaternion(GetRotate() * Quaternion::CreateFromAxisAngle(Vector3::UnitY, DirectX::XMConvertToRadians(sinf(m_elapsedTime * 5.0f) * 3.f))));
	SetRotate(Quaternion(GetRotate() * Quaternion::CreateFromAxisAngle(Vector3::UnitZ, DirectX::XMConvertToRadians(sinf(m_elapsedTime * 5.0f) * 3.f))));

	SetPosition(Vector3(0.0f, 1.7f, 0.0f));
}

/// <summary>
/// モデルの描画
/// </summary>
/// <param name="model">モデル</param>
/// <param name="world">ワールド</param>
/// <param name="view">ビュー</param>
/// <param name="proj">プロジェクション</param>
void PlayerRightArm::DrawModel(DirectX::Model* model, const DirectX::SimpleMath::Matrix& world, const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	UNREFERENCED_PARAMETER(world);
	UNREFERENCED_PARAMETER(model);

	DirectX::SimpleMath::Quaternion parentRotate;
	//	死亡中か？
	if (GetRoot()->IsDeathAnimation()) { parentRotate = GetParent()->GetRotate() * GetRotate(); } else { parentRotate = GetRoot()->GetRotate() * GetRotate(); }
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