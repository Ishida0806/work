//
//		File Name ： EnemyLeg.cpp
//		Production： 2023/11/12
//		Author　　： 石田 恭一	
//	
#include "pch.h"
#include "EnemyLeg.h"
#include "Enemy.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="enemy">座標</param>
/// <param name="model">モデル</param>
EnemyLeg::EnemyLeg(Enemy* enemy, DirectX::Model* model)
	:m_parent(enemy),
	m_enemyModel(model)
{
}

/// <summary>
/// デストラクタ
/// </summary>
EnemyLeg::~EnemyLeg()
{
}

/// <summary>
///	初期化処理
/// </summary>
void EnemyLeg::Initialize()
{
	
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="timer">タイマー</param>
/// <param name="rollSpeed">脚が回る速度/param>
void EnemyLeg::RollLeg(const DX::StepTimer& timer, const float& rollAngleSpeed)
{

	timer;

	if (m_parent->IsWalk() && m_parent->GetType() == ObjectType::NormalEnemy)
	{
		//	脚を回す
		SetRotate(GetRotate() * DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(-rollAngleSpeed)));
	}
	else if(!m_parent->IsWalk() && m_parent->GetType() == ObjectType::NormalEnemy)
	{
		//	脚を回す
		SetRotate(DirectX::SimpleMath::Quaternion::Lerp(GetRotate(), DirectX::SimpleMath::Quaternion::Identity, 0.1f));
	}
}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="view">ビュー</param>
/// <param name="proj">プロジェクション</param>
void EnemyLeg::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	//	スクリーンリソース
	auto screen = MyLib::ScreenResources::GetInstance();
	// スケール行列
	DirectX::SimpleMath::Matrix scale = DirectX::SimpleMath::Matrix::CreateScale(m_parent->GetScale());
	// 位置行列
	DirectX::SimpleMath::Matrix trans = DirectX::SimpleMath::Matrix::CreateTranslation(m_parent->GetPosition());
	// 回転行列
	DirectX::SimpleMath::Matrix rotate = DirectX::SimpleMath::Matrix::CreateFromQuaternion(GetRotate() * m_parent->GetRotate());
	// ワールド変換行列に変換（スケール、回転、位置の順で適用）
	DirectX::SimpleMath::Matrix world = scale * rotate * trans;
	// 敵が無敵状態または死亡アニメーション中の場合、特殊な描画を行う
	m_enemyModel->Draw(screen->GetDeviceContext(), *screen->GetCommonState(), world, view, proj);
}

/// <summary>
/// 終了処理
/// </summary>
void EnemyLeg::Finalize()
{
}
