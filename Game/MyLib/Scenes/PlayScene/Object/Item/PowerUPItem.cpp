//
//		File Name ： PowerUPItem.cpp
//		Production： 2023/12/1
//		Author　　： 石田 恭一	
//
#include "pch.h"
#include "PowerUPItem.h"

//	増加する角度
const float PowerUPItem::INCREASE_ANGLE = 2.0f;
//	揺らす範囲の制限
const float PowerUPItem::SHAKE_RANGE	= 0.3f;



/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="position">座標</param>
/// <param name="itemType">アイテムの種類</param>
PowerUPItem::PowerUPItem(const DirectX::SimpleMath::Vector3& position, const ItemType& itemType)
	:Item(position, itemType),
	m_model(nullptr),
	m_elapsedTime(0.0f)
{
}

/// <summary>
/// デストラクタ
/// </summary>
PowerUPItem::~PowerUPItem()
{
}

/// <summary>
/// 初期化処理
/// </summary>
void PowerUPItem::Initialize()
{
	m_model = MyLib::ResourcesData::GetInstance()->GatModel(L"armPower");

	Item::Initialize();
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="timer">タイマー</param>
void PowerUPItem::Update(const DX::StepTimer& timer)
{
	//	基底クラスを更新する
	Item::Update(timer);

	//	経過時間を取得する
	m_elapsedTime = static_cast<float>(timer.GetTotalSeconds());

	m_powerUPRotate = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, SHAKE_RANGE * sinf(m_elapsedTime));

	//	ある程度まで行ったら初期化する
	if (m_elapsedTime >= 1000.0f)	m_elapsedTime = 0.0f;
}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="view">ビュー</param>
/// <param name="proj">プロジェクション</param>
void PowerUPItem::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{

	m_model->UpdateEffects
	(
		[&](DirectX::IEffect* effect)
		{
			auto basicEffect = dynamic_cast<DirectX::BasicEffect*>(effect);
			//	キャストできたか？
			if (basicEffect)
			{
				//	画像入らない
				basicEffect->SetTexture(nullptr);
			}
		}
	);

	Item::Render(view, proj);

	MyLib::ScreenResources*		screen = MyLib::ScreenResources::GetInstance();
	//	スケーリング行列を作成する
	DirectX::SimpleMath::Matrix scale  = DirectX::SimpleMath::Matrix::CreateScale(GetScale());
	//	移動行列を作成	
	DirectX::SimpleMath::Matrix trans  = DirectX::SimpleMath::Matrix::CreateTranslation(GetPosition());
	//	回転行列
	DirectX::SimpleMath::Matrix rotate = DirectX::SimpleMath::Matrix::CreateFromQuaternion(m_powerUPRotate);
	//	ワールド行列を作成
	DirectX::SimpleMath::Matrix world  = scale * rotate * trans;
	//	モデル描画処理
	m_model->Draw
		(
			screen->GetDeviceContext(),
			*screen->GetCommonState(),
			world,
			view,
			proj
		);
}

/// <summary>
/// 終了処理
/// </summary>
void PowerUPItem::Finalize()
{
	Item::Finalize();
}