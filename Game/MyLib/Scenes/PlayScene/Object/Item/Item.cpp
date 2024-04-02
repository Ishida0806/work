//
//		File Name ： Item.cpp
//		Production： 2023/12/1
//		Author　　： 石田 恭一	
//
#include "pch.h"
#include "Item.h"

//	経過時間を早める
const float Item::INCREASE_TIMER	  = 2.5f;
//	サイン波を小さくする
const float Item::LIMITS_VALUE		  = 0.01f;
//	大きさを小さくする値
const float Item::SCALE_SMALLER_VALUE = 0.05f;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="position">座標</param>
/// <param name="itemType">アイテムの種類</param>
Item::Item(const DirectX::SimpleMath::Vector3& position, const ItemType& itemType)
	:
	Object(position),
	m_itemType(itemType),
	m_elapsedTime(0.0f),
	m_isTookItem(false), 
	m_isTookAnimation(false)
{
}

/// <summary>
/// デストラクタ
/// </summary>
Item::~Item()
{
}

/// <summary>
/// 初期化処理
/// </summary>
void Item::Initialize()
{
	//	当たり判定の設定をする
	m_sphere.center = GetPosition();
	m_sphere.radius = 0.7f;
	//	オブジェクトのタイプを設定する
	SetType(Object::ObjectType::Item);

	m_itemCapsule = std::make_unique<ItemCapsule>(this);
	m_itemCapsule->Initialize();
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="timer">タイマー</param>
void Item::Update(const DX::StepTimer& timer)
{
	//	取得時のアニメーション
	if (m_isTookAnimation)
	{
		SetScale(GetScale() - DirectX::SimpleMath::Vector3(SCALE_SMALLER_VALUE));

		//	0.0より大きいなら帰れ
		if (GetScale().x > 0.0f && GetScale().y > 0.0f && GetScale().z > 0.0f)	return;

		//	アイテムを取得した
		m_isTookItem = true;

		return;
	}

	//	経過時間を取得する
	m_elapsedTime = static_cast<float>(timer.GetTotalSeconds());
	//	座標を取得する
	DirectX::SimpleMath::Vector3 position = GetPosition();
	//	ふよふよさせる
	position.y += LIMITS_VALUE * sinf(m_elapsedTime * INCREASE_TIMER);
	//	ある程度まで行ったら初期化する
	if (m_elapsedTime >= 1000.0f)	m_elapsedTime = 0.0f;
	//	座標を設定する
	SetPosition(position);
	//	カプセルの更新
	m_itemCapsule->Update(timer);
}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="view">ビュープロジェクション</param>
/// <param name="proj">ビュー</param>
void Item::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	//	カプセルの描画
	m_itemCapsule->Render(view, proj);
}

/// <summary>
/// 終了処理
/// </summary>
void Item::Finalize()
{
}

/// <summary>
/// アイテムが取得された
/// </summary>
void Item::TookItem()
{
	m_isTookAnimation = true;
}

/// <summary>
/// 当たり判定を設定する
/// </summary>
/// <param name="sphere">球</param>
void Item::SetSphere(const Collision::Shape::Sphere& sphere)
{
	m_sphere = sphere;
}