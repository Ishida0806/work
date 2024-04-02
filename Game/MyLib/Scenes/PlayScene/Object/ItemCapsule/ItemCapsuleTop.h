//
//		File Name ： ItemCapsuleTop.h
//		Production： 2023/12/06
//		Author　　： 石田 恭一	
//
#pragma once 
#include "../Object.h"
#include "IItemCapsuleComponent.h"

class ItemCapsuleTop : public Object, public IItemCapsuleComponent
{
	//	変数
private:

	//	親
	Object*			m_parent;
	//	モデル
	DirectX::Model* m_model;

	//	関数
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="Object">親</param>
	ItemCapsuleTop(Object* parent);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ItemCapsuleTop();

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
	/// <param name="view">ビュー</param>
	/// <param name="proj">プロジェクション</param>
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj) override;

	/// <summary>
	/// 終了処理
	/// </summary>
	void Finalize() override;
};