//
//		File Name ： PlayerHead.cpp
//		Production： 2023/12/27
//		Author　　： 石田 恭一	
// 
//		プレイヤーの各パーツたち
//	
#include "pch.h"
#include "PlayerHead.h"


//	死亡時の加速
const DirectX::SimpleMath::Vector3 PlayerHead::DEATH_ACCELERATION		= DirectX::SimpleMath::Vector3(0.0f, -0.12f, 0.73f);
//	頭の地面の位置
const float						   PlayerHead::GROUND_HEAD_POSITION		= -1.2f;
//	揺れる大きさ
const float						   PlayerHead::SHAKE_VOLUME				=  0.01f;


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="root">ルート</param>
/// <param name="paren">親</param>
PlayerHead::PlayerHead(Player* root, Object* parent)
	:PlayerComponent(root, parent),
	m_model(nullptr),
	m_elapsedTime(0.0f),
	m_excessiveForce(DEATH_ACCELERATION.z)
{

}

/// <summary>
/// デストラクタ
/// </summary>
PlayerHead::~PlayerHead()
{
}

/// <summary>
/// 初期化する
/// </summary>
void PlayerHead::Initialize()
{
	m_model = MyLib::ResourcesData::GetInstance()->GatModel(L"playerHead");
}

/// <summary>
/// 部品を更新する
/// </summary>
/// <param name="timer">タイマー</param>
void PlayerHead::UpdateParts(const DX::StepTimer& timer)
{
	UNREFERENCED_PARAMETER(timer);

	if (GetRoot()->IsAttack())
	{
		//	頭を振る
		SetRotate(GetRotate() * DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(Utility::CreateRandom(-4.f, 4.f))));
	}
	else
	{
		SetRotate(DirectX::SimpleMath::Quaternion::Lerp(GetRotate(), DirectX::SimpleMath::Quaternion::Identity, 0.3f));
	}

	if (GetRoot()->IsWalk())
	{
		//	頭を左右前後に揺らす
		SetPosition(GetPosition() + DirectX::SimpleMath::Vector3(Utility::CreateRandom(-SHAKE_VOLUME, SHAKE_VOLUME), 0.0f, Utility::CreateRandom(-SHAKE_VOLUME, SHAKE_VOLUME)));
	}

	SetPosition(DirectX::SimpleMath::Vector3::Lerp(GetPosition(), DirectX::SimpleMath::Vector3::Zero, 0.1f));
}
 
/// <summary>
/// 死亡アニメーション
/// </summary>
/// <param name="timer">タイマー</param>
void PlayerHead::DeathAnimation(const DX::StepTimer& timer)
{
	UNREFERENCED_PARAMETER(timer);

	using namespace DirectX::SimpleMath;

	if (GetPosition().y <= GROUND_HEAD_POSITION)
	{
		m_elapsedTime += static_cast<float>(timer.GetElapsedSeconds());

		//	力が有り余っているのなら減算
		if (m_excessiveForce <= 0.0f)
		{
			//	移動量
			Vector3 vel = Vector3(0.0f, 0.0f, m_excessiveForce);
			//	移動量を足す
			SetPosition(GetPosition() + Vector3::Transform(vel, GetRoot()->GetRotate()));
		
			//	力を弱める
			m_excessiveForce += static_cast<float>(timer.GetElapsedSeconds());
		}
		else
		{
			m_excessiveForce = 0.0f;
		}

		//	頭を回転させる
		SetRotate(GetRotate() * Quaternion::CreateFromAxisAngle(Vector3::UnitY, DirectX::XMConvertToRadians(5.0f)));

		return;
	}

	SetPosition(GetPosition() + Vector3::Transform(DEATH_ACCELERATION, GetRoot()->GetRotate()));
}

/// <summary>
/// 勝利アニメーション
/// </summary>
/// <param name="timer">タイマー</param>
void PlayerHead::WinAnimation(const DX::StepTimer& timer)
{
	using namespace DirectX::SimpleMath;

	m_elapsedTime += static_cast<float>(timer.GetElapsedSeconds());
	SetPosition(Vector3(0.0f, 0.0f, sinf(m_elapsedTime * 3.0f) * 0.1f));
}

/// <summary>
/// モデルの描画
/// </summary>
/// <param name="model">モデル</param>
/// <param name="world">ワールド</param>
/// <param name="view">ビュー</param>
/// <param name="proj">プロジェクション</param>
void PlayerHead::DrawModel(DirectX::Model* model, const DirectX::SimpleMath::Matrix& world, const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	UNREFERENCED_PARAMETER(world);
	UNREFERENCED_PARAMETER(model);

	//	移動行列
	DirectX::SimpleMath::Matrix trans = DirectX::SimpleMath::Matrix::CreateTranslation(GetRoot()->GetPosition() + GetPosition());
	//	回転行列
	DirectX::SimpleMath::Matrix rotate = DirectX::SimpleMath::Matrix::CreateFromQuaternion(GetRoot()->GetRotate() * GetRotate());
	//	拡大行列
	DirectX::SimpleMath::Matrix scale = DirectX::SimpleMath::Matrix::CreateScale(GetRoot()->GetScale());
	//	ワールド
	DirectX::SimpleMath::Matrix wrd = scale * rotate * trans;
	//	モデルの描画
	PlayerComponent::DrawModel(m_model, wrd, view, proj);
}