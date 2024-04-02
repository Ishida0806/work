//
//		File Name ： Cloak.h
//		Production： 2023/12/27
//		Author　　： 石田 恭一	
//	
#pragma once
#include "../PlayeComponent/PlayerComponent.h"

class Cloak : public PlayerComponent
{
	//	変数
private:

	//	モデル
	DirectX::Model*					m_model;
	//	経過時間
	float							m_elapsedTime;

	//	関数
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="root">ルート</param>
	/// <param name="parent">親</param>
	Cloak(Player* root, Object* parent);
	
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Cloak();

	/// <summary>
	/// 初期化する
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// 部品を更新する
	/// </summary>
	/// <param name="timer">タイマー</param>
	void UpdateParts(const DX::StepTimer& timer) override;

	/// <summary>
	/// 死亡アニメーション
	/// </summary>
	/// <param name="timer">タイマー</param>
	void DeathAnimation(const DX::StepTimer& timer) override;

	/// <summary>
	/// モデルの描画
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="world">ワールド</param>
	/// <param name="view">ビュー</param>
	/// <param name="proj">プロジェクション</param>
	void DrawModel(DirectX::Model* model, const DirectX::SimpleMath::Matrix& world, const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj) override;
};
