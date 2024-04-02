//
//		File Name ： Item.h
//		Production： 2023/12/1
//		Author　　： 石田 恭一	
//
#pragma once
#include "../Object.h"
#include "../ItemCapsule/ItemCapsule.h"

class Object;

class Item : public Object
{
	//	列挙型
public:

	//	アイテムの種類
	enum class ItemType
	{
		None = 0,

		Recovery,
		Reflect,
		PowUp,

		OverID
	};

	//	アクセサ
public:	


	//	当たり判定の取得
	Collision::Shape::Sphere GetSpere()			const { return m_sphere; }
	//	アイテムンタイプを取得する
	ItemType				 GetItemType()		const { return m_itemType; }
	//	アイテムを取得した	
	bool					 IsTookItem()		const { return m_isTookItem; }
	//	取得アニメーション中か？
	bool					 IsTookAnimation()	const { return m_isTookAnimation; }
	//	当たり判定を設定する
	void SetSphere(const Collision::Shape::Sphere& sphere);

	//	定数
public:

	//	経過時間を早める
	static const float INCREASE_TIMER;
	//	サイン波を小さくする
	static const float LIMITS_VALUE;
	//	大きさを小さくする値
	static const float SCALE_SMALLER_VALUE;

	//	変数
private:

	//アイテムの種類
	ItemType									 m_itemType;
	//	当たり判定
	Collision::Shape::Sphere					 m_sphere;
	//	アイテムのカプセル
	std::unique_ptr<ItemCapsule>				 m_itemCapsule;
	//	経過時間
	float									  	 m_elapsedTime;
	//	プレイヤーがアイテムを取得した
	bool										 m_isTookItem;
	//	取得時のアニメーション
	bool										 m_isTookAnimation;

	//	関数
public:
	
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="position">座標</param>
	/// <param name="itemType">アイテムの種類</param>
	Item(const DirectX::SimpleMath::Vector3& position, const ItemType& itemType = ItemType::None);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Item();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="timer">タイマー</param>
	void Update(const DX::StepTimer& timer) override;

	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="view">ビュープロジェクション</param>
	/// <param name="proj">ビュー</param>
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj) override;

	/// <summary>
	/// 終了処理
	/// </summary>
	void Finalize() override;

	/// <summary>
	/// アイテムが取得された
	/// </summary>
	void TookItem();
};