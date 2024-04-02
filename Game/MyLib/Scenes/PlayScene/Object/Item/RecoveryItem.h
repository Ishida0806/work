//
//		File Name ： RecoveryItem.h
//		Production： 2023/12/1
//		Author　　： 石田 恭一	
//
#pragma once
#include "../Item/Item.h"

class Item;

class RecoveryItem : public Item
{
	//	変数
private:

	//	モデル
	DirectX::Model* m_model;

	//	関数
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="position">座標</param>
	/// <param name="itemType">アイテムの種類</param>
	RecoveryItem(const DirectX::SimpleMath::Vector3& position, const ItemType& itemType = ItemType::None);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~RecoveryItem();

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
};