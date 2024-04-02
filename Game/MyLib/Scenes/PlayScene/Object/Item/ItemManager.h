//
//		File Name ： ItemManager.h
//		Production： 2023/12/1
//		Author　　： 石田 恭一	
//
#pragma once
#include "../Item/Item.h"

class Item;

class ItemManager
{
	//	アクセサ
public:

	//	アイテムを取得する
	inline std::vector<std::shared_ptr<Item>>& GetItem()		noexcept { return m_items; };

	//	定数
public:

	//	出現する場所
	static const float SPAWN_PLACE;
	//	出現する時間
	static const float SPAWN_TIME;
	//	生成限界数
	static const int   SPAWN_ITEM;

	//	変数
private:

	//	アイテム達
	std::vector<std::shared_ptr<Item>> m_items;
	//	出現時間
	float							   m_spwanItemTime;

	//	関数
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ItemManager();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ItemManager();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="timer">タイマー</param>
	void Update(const DX::StepTimer& timer);

	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="view">ビュープロジェクション</param>
	/// <param name="proj">ビュー</param>
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj);

	/// <summary>
	/// 終了処理
	/// </summary>
	void Finalize();

	//	埋め込み関数
private:

	/// <summary>
	/// アイテムを出現する
	/// </summary>
	void SpawnItem(const DX::StepTimer& timer);

	/// <summary>
	/// 取得したアイテムを取消す
	/// </summary>
	void TookItems();
};