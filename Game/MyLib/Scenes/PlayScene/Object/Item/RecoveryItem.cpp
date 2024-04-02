//
//		File Name ： RecoveryItem.cpp
//		Production： 2023/12/1
//		Author　　： 石田 恭一	
//
#include "pch.h"
#include "RecoveryItem.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="position">座標</param>
/// <param name="itemType">アイテムの種類</param>
RecoveryItem::RecoveryItem(const DirectX::SimpleMath::Vector3& position, const ItemType& itemType)
	:Item(position, itemType),
	m_model(nullptr)
{
}

/// <summary>
/// デストラクタ
/// </summary>
RecoveryItem::~RecoveryItem()
{
}

/// <summary>
/// 初期化処理
/// </summary>
void RecoveryItem::Initialize()
{
	m_model = MyLib::ResourcesData::GetInstance()->GatModel(L"recovery");

	Item::Initialize();
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="timer">タイマー</param>
void RecoveryItem::Update(const DX::StepTimer& timer)
{
	//	基底クラスを更新する
	Item::Update(timer);
}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="view">ビュー</param>
/// <param name="proj">プロジェクション</param>
void RecoveryItem::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	//	ラムダ式で関数オブジェクトを引数に
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
	//	アイテムの描画
	Item::Render(view, proj);
	//	スクリーン
	MyLib::ScreenResources* screen	  = MyLib::ScreenResources::GetInstance();
	//	スケーリング行列を作成する
	DirectX::SimpleMath::Matrix scale = DirectX::SimpleMath::Matrix::CreateScale(GetScale());
	//	移動行列を作成	
	DirectX::SimpleMath::Matrix trans = DirectX::SimpleMath::Matrix::CreateTranslation(GetPosition());

	//	移動行列
	DirectX::SimpleMath::Matrix world = scale * trans;
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
void RecoveryItem::Finalize()
{
	Item::Finalize();
}
