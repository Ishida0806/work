//
//		File Name ： ReflectItem.cpp
//		Production： 2023/12/1
//		Author　　： 石田 恭一	
//
#include "pch.h"
#include "ReflectItem.h"


//	増加する角度
const float ReflectItem::INCREASE_ANGLE = 2.0f;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="position">座標</param>
/// <param name="itemType">アイテムの種類</param>
ReflectItem::ReflectItem(const DirectX::SimpleMath::Vector3& position, const ItemType& itemType)
	:Item(position, itemType),
	m_model(nullptr)
{
}

/// <summary>
/// デストラクタ
/// </summary>
ReflectItem::~ReflectItem()
{
}

/// <summary>
/// 初期化処理
/// </summary>
void ReflectItem::Initialize()
{
	m_model = MyLib::ResourcesData::GetInstance()->GatModel(L"bat");

	Item::Initialize();
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="timer">タイマー</param>
void ReflectItem::Update(const DX::StepTimer& timer)
{
	//	アイテムを取得した
	//if (IsTookItem())	return;

	SetAngle(GetAngle() + DirectX::XMConvertToRadians(INCREASE_ANGLE));

	m_reflectRotate = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, GetAngle());
	m_reflectRotate = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitZ, GetAngle());


	//	基底クラスを更新する
	Item::Update(timer);
}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="view">ビュー</param>
/// <param name="proj">プロジェクション</param>
void ReflectItem::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
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

	MyLib::ScreenResources* screen	  = MyLib::ScreenResources::GetInstance();
	//	スケーリング行列を作成する
	DirectX::SimpleMath::Matrix scale = DirectX::SimpleMath::Matrix::CreateScale(GetScale());
	//	移動行列を作成	
	DirectX::SimpleMath::Matrix trans = DirectX::SimpleMath::Matrix::CreateTranslation(GetPosition());
	//	回転行列を作成
	DirectX::SimpleMath::Matrix roate = DirectX::SimpleMath::Matrix::CreateFromQuaternion(m_reflectRotate);
	//	ワールド行列を作成
	DirectX::SimpleMath::Matrix world = scale * roate * trans;
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
void ReflectItem::Finalize()
{
	Item::Finalize();
}
