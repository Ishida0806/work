//
//		File Name ： Cloak.cpp
//		Production： 2023/12/27
//		Author　　： 石田 恭一
// 
//		マント	
//	
#include "pch.h"
#include "Cloak.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="root">ルート</param>
/// <param name="parent">親</param>
Cloak::Cloak(Player* root, Object* parent)
	:PlayerComponent(root, parent),
	m_model(nullptr),
	m_elapsedTime(0.0f)
{

}

/// <summary>
/// デストラクタ
/// </summary>
Cloak::~Cloak()
{
}

/// <summary>
/// 初期化処理
/// </summary>
void Cloak::Initialize()
{
	m_model = MyLib::ResourcesData::GetInstance()->GatModel(L"cloak");

	m_model->UpdateEffects
	(
		[&](DirectX::IEffect* effect)
		{
			//	ベーシックエフェクト
			auto basicEffect = dynamic_cast<DirectX::BasicEffect*>(effect);
			//	ポインタは存在するか？
			if (basicEffect)
			{
				//	環境光
				basicEffect->SetAmbientLightColor(DirectX::Colors::White);
			}
		}
	);
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="timer">タイマー</param>
void Cloak::UpdateParts(const DX::StepTimer& timer)
{
	using namespace DirectX::SimpleMath;

	m_elapsedTime += static_cast<float>(timer.GetElapsedSeconds());

	//if (GetRoot()->IsAttack())
	//{
	//	DirectX::SimpleMath::Quaternion lastRotate = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(Vector3::UnitX, 0.3f * sinf(m_elapsedTime));

	//	SetRotate(Quaternion::Lerp(GetRotate(), lastRotate, 0.03f));
	//}
	//else
	//{
	//	SetRotate(DirectX::SimpleMath::Quaternion::Lerp(GetRotate(), DirectX::SimpleMath::Quaternion::Identity, 0.1f));

	//	//m_elapsedTime = 0.0f;
	//}

	if (GetRoot()->IsWalk())
	{
		DirectX::SimpleMath::Vector3 position = GetPosition();

		position.y += sinf(m_elapsedTime);

		SetVelocity(position);
	}
	else
	{
		m_elapsedTime = 0.0f;
	}
}

/// <summary>
/// 死亡アニメーション
/// </summary>
/// <param name="timer">タイマー</param>
void Cloak::DeathAnimation(const DX::StepTimer& timer)
{
	UNREFERENCED_PARAMETER(timer);
}


/// <summary>
/// モデルの描画
/// </summary>
/// <param name="model">モデル</param>
/// <param name="world">ワールド</param>
/// <param name="view">ビュー</param>
/// <param name="proj">プロジェクション</param>
void Cloak::DrawModel(DirectX::Model* model, const DirectX::SimpleMath::Matrix& world, const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	UNREFERENCED_PARAMETER(world);
	UNREFERENCED_PARAMETER(model);

	DirectX::SimpleMath::Quaternion parentRotate;

	//	死亡中か？
	if (GetRoot()->IsDeathAnimation()) { parentRotate = GetParent()->GetRotate() * GetRotate(); } else { parentRotate = GetRoot()->GetRotate() * GetRotate(); }
	//	移動行列
	DirectX::SimpleMath::Matrix trans = DirectX::SimpleMath::Matrix::CreateTranslation(GetRoot()->GetPosition() + DirectX::SimpleMath::Vector3(0.0f, 0.44f, 0.1f));
	//	回転行列
	DirectX::SimpleMath::Matrix rotate = DirectX::SimpleMath::Matrix::CreateFromQuaternion(parentRotate);
	//	拡大行列
	DirectX::SimpleMath::Matrix scale = DirectX::SimpleMath::Matrix::CreateScale(1.5f);
	//	ワールド
	DirectX::SimpleMath::Matrix wrd = scale * rotate * trans;
	//	モデルの描画
	PlayerComponent::DrawModel(m_model, wrd, view, proj);
}
