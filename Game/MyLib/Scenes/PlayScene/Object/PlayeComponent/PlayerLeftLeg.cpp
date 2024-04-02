//
//		File Name ： PlayerLeftLeg.cpp
//		Production： 2023/12/27
//		Author　　： 石田 恭一	
// 
//		プレイヤーの各パーツたち
//	
#include "pch.h"
#include "PlayerLeftLeg.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="root">ルート</param>
/// <param name="paren">親</param>
PlayerLeftLeg::PlayerLeftLeg(Player* root, Object* parent)
	:PlayerComponent(root, parent),
	m_model(nullptr),
	m_elapsedTime(0.0f)
{
	
}

/// <summary>
/// デストラクタ
/// </summary>
PlayerLeftLeg::~PlayerLeftLeg()
{
}

/// <summary>
/// 初期化する
/// </summary>
void PlayerLeftLeg::Initialize()
{
	m_model = MyLib::ResourcesData::GetInstance()->GatModel(L"playerLeftLeg");
}

/// <summary>
/// 部品を更新する
/// </summary>
/// <param name="timer">タイマー</param>
void PlayerLeftLeg::UpdateParts(const DX::StepTimer& timer)
{
	UNREFERENCED_PARAMETER(timer);

	//	経過時間を足す
	if (GetRoot()->IsWalk())
	{
		m_elapsedTime -= static_cast<float>(timer.GetElapsedSeconds());
		//	頭を上下に揺らす
		SetPosition(GetPosition() + DirectX::SimpleMath::Vector3(0.0f, 0.0f, sinf(m_elapsedTime * 5.0f) * 0.08f));
	}
	else
	{
		m_elapsedTime = 0.0f;
		SetPosition(DirectX::SimpleMath::Vector3::Lerp(GetPosition(), DirectX::SimpleMath::Vector3::Zero, 0.2f));
	}

	SetPosition(DirectX::SimpleMath::Vector3::Lerp(GetPosition(), DirectX::SimpleMath::Vector3::Zero, 0.1f));
}

/// <summary>
/// 死亡アニメーション
/// </summary>
/// <param name="timer">タイマー</param>
void PlayerLeftLeg::DeathAnimation(const DX::StepTimer& timer)
{
	UNREFERENCED_PARAMETER(timer);


}

/// <summary>
/// 勝利アニメーション
/// </summary>
/// <param name="timer">タイマー</param>
void PlayerLeftLeg::WinAnimation(const DX::StepTimer& timer)
{
	using namespace DirectX::SimpleMath;
	//	経過時間を足す
	m_elapsedTime += static_cast<float>(timer.GetElapsedSeconds());
	//	脚を少しうごかす
	SetPosition(Vector3(0.0f, sinf(m_elapsedTime * 3.0f) * 0.05f, 0.0f));
}

/// <summary>
/// モデルの描画
/// </summary>
/// <param name="model">モデル</param>
/// <param name="world">ワールド</param>
/// <param name="view">ビュー</param>
/// <param name="proj">プロジェクション</param>
void PlayerLeftLeg::DrawModel(DirectX::Model* model, const DirectX::SimpleMath::Matrix& world, const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
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