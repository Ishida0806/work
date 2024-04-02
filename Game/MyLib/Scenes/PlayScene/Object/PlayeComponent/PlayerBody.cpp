//
//		File Name ： PlayerBody.cpp
//		Production： 2023/12/27
//		Author　　： 石田 恭一	
// 
//		プレイヤーの各パーツたち
//	
#include "pch.h"
#include "PlayerBody.h"

#include "../PlayeComponent/PlayerPartsFactory.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="root">ルート</param>
/// <param name="paren">親</param>
PlayerBody::PlayerBody(Player* root, Object* parent)
	:PlayerComponent(root, parent),
	m_model(nullptr)
{

}

/// <summary>
/// デストラクタ
/// </summary>
PlayerBody::~PlayerBody()
{
}

/// <summary>
/// 初期化する
/// </summary>
void PlayerBody::Initialize()
{
	m_model = MyLib::ResourcesData::GetInstance()->GatModel(L"playerBody");

	//	パーツの追加
	m_playerParts.push_back(PlayerPartsFactory::CreatePlayerHead(	GetRoot(),	this));
	m_playerParts.push_back(PlayerPartsFactory::CreatePlayerLeftArm(GetRoot(),  this));
	m_playerParts.push_back(PlayerPartsFactory::CreatePlayerRightArm(GetRoot(), this));
	m_playerParts.push_back(PlayerPartsFactory::CreatePlayerLeftLeg(GetRoot(),  this));
	m_playerParts.push_back(PlayerPartsFactory::CreatePlayerRightLeg(GetRoot(), this));
	m_playerParts.push_back(PlayerPartsFactory::CreatePlayerCloak(	GetRoot(),  this));
}

/// <summary>
/// 部品を更新する
/// </summary>
/// <param name="timer">タイマー</param>
void PlayerBody::UpdateParts(const DX::StepTimer& timer)
{
	for (const auto& parts : m_playerParts)	parts->UpdateParts(timer);
}

/// <summary>
/// 死亡アニメーション
/// </summary>
/// <param name="timer">タイマー</param>
void PlayerBody::DeathAnimation(const DX::StepTimer& timer)
{
	//	プレイヤーを横向きに倒す
	SetRotate
	(
		DirectX::SimpleMath::Quaternion::Lerp
		(
			GetRotate(),
			DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitX, DirectX::XMConvertToRadians(90.0f)) * GetRoot()->GetRotate(),
			0.01f
		)
	);

	for (const auto& parts : m_playerParts) { parts->DeathAnimation(timer); }
}

/// <summary>
/// 勝利アニメーション
/// </summary>
/// <param name="timer">タイマー</param>
void PlayerBody::WinAnimation(const DX::StepTimer& timer)
{
	using namespace DirectX::SimpleMath;
	//	経過時間を足す
	m_elapsedTime += static_cast<float>(timer.GetElapsedSeconds());
	//	パーツの更新
	for (const auto& parts : m_playerParts) { parts->WinAnimation(timer); }
	//	体を左右に揺らす
	SetPosition(Vector3(sinf(m_elapsedTime * 2.0f) * 0.01f , 0.0f, 0.0f));
}

/// <summary>
/// モデルの描画
/// </summary>
/// <param name="model">モデル</param>
/// <param name="world">ワールド</param>
/// <param name="view">ビュー</param>
/// <param name="proj">プロジェクション</param>
void PlayerBody::DrawModel(DirectX::Model* model, const DirectX::SimpleMath::Matrix& world, const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	UNREFERENCED_PARAMETER(world);
	UNREFERENCED_PARAMETER(model);

	DirectX::SimpleMath::Quaternion parentRotate;

	//	死亡中か？
	if (GetRoot()->IsDeathAnimation())	parentRotate = GetRotate();
	else								parentRotate = GetRoot()->GetRotate() * GetRotate();

	//	移動行列
	DirectX::SimpleMath::Matrix trans = DirectX::SimpleMath::Matrix::CreateTranslation(GetRoot()->GetPosition() + GetPosition());
	//	回転行列
	DirectX::SimpleMath::Matrix rotate = DirectX::SimpleMath::Matrix::CreateFromQuaternion(parentRotate);
	//	拡大行列
	DirectX::SimpleMath::Matrix scale = DirectX::SimpleMath::Matrix::CreateScale(GetRoot()->GetScale());
	//	ワールド
	DirectX::SimpleMath::Matrix wrd = scale * rotate * trans;
	//	モデルの描画
	PlayerComponent::DrawModel(m_model, wrd, view, proj);

	for (const auto& parts : m_playerParts)	parts->DrawModel(nullptr, wrd, view, proj);
}