//
//		File Name ： PlayerArrow.cpp
//		Production： 2023/11/03
//		Author　　： 石田 恭一	
// 
//		カーソルのいる方を表す矢印の処理
//	
#include "pch.h"
#include "PlayerArrow.h"

//	矢印の移動速度
const float PlayerArrow::MOVE_ARROW_SPEED = 0.2f;
//	矢印の回転角のZ
const float PlayerArrow::ARROW_ROTATE_Z   = 2.0f;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="parent">親</param>
/// <param name="arrowModel">矢印モデル</param>
/// <param name="cursolPosition">カーソルの座標</param>
/// <param name="cursolRotate">カーソルの回転角</param>
PlayerArrow::PlayerArrow(
	Object* parent,
	DirectX::Model* arrowModel,
	DirectX::SimpleMath::Vector3* cursolPosition,
	DirectX::SimpleMath::Quaternion* cursolRotate
) 
	:m_parent(parent),
	m_arrowModel(arrowModel),
	m_cursolPosition(cursolPosition),
	m_cursolRotate(cursolRotate),
	m_circleAngle(0.0f),
	m_arrowAngle(0.0f)
{
}

/// <summary>
/// デストラクタ
/// </summary>
PlayerArrow::~PlayerArrow()
{
}

/// <summary>
/// 初期化処理
/// </summary>
void PlayerArrow::Initialize()
{
	m_arrowModel->UpdateEffects
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
void PlayerArrow::Update(const DX::StepTimer& timer)
{
	timer;
	//	毎フレーム回す
	m_arrowAngle  -= DirectX::XMConvertToRadians(ARROW_ROTATE_Z);
	//	
	m_circleAngle -= DirectX::XMConvertToRadians(ARROW_ROTATE_Z);
	//	移動量
	DirectX::SimpleMath::Vector3 vel;
	//	親クラスから取得する
	m_position = m_parent->GetPosition();
	//	距離を算出する
	DirectX::SimpleMath::Vector3 dir = m_parent->GetPosition() - *m_cursolPosition;
	//	座標から角度に変換する デグリー角基準に90度ずれているので補正
	float  cursolAngle = -atan2(dir.z, dir.x) - DirectX::XMConvertToRadians(90.0f);
	//	矢印座標座標
	vel.x = m_parent->GetPosition().x + 4.0f * sinf(cursolAngle);
	vel.z = m_parent->GetPosition().z + 4.0f * cosf(cursolAngle);
	//	矢印座標にゆっくり移動
	m_arrowPosition = DirectX::SimpleMath::Vector3::Lerp(m_arrowPosition, vel, MOVE_ARROW_SPEED);
}

/// <summary>
/// 描画する
/// </summary>
/// <param name="view">ビュー</param>
/// <param name="proj">プロジェクション</param>
void PlayerArrow::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	using namespace DirectX::SimpleMath;

	//	スクリーンリソース
	MyLib::ScreenResources* screen = MyLib::ScreenResources::GetInstance();

	//	移動行列
	//Matrix trans = Matrix::CreateTranslation(m_position);
	////	回転
	//Matrix roate = Matrix::CreateRotationY(m_circleAngle);
	////	ワールド行列
	//Matrix world = roate * trans;
	////	モデルの描画
	//m_circleModel->Draw
	//(
	//	screen->GetDeviceContext(),
	//	*screen->GetCommonState(),
	//	world,
	//	view,
	//	proj
	//);

	//	矢印の行列
	Matrix arrowWorld = Matrix::CreateRotationZ(m_arrowAngle) * Matrix::CreateFromQuaternion(*m_cursolRotate) * Matrix::CreateTranslation(m_arrowPosition);
	//	モデルの描画する
	m_arrowModel->Draw
	(
		screen->GetDeviceContext(),
		*screen->GetCommonState(),
		arrowWorld,
		view,
		proj
	);
}

/// <summary>
/// 終了処理
/// </summary>
void PlayerArrow::Finalize()
{
}
