//
//		File Name ： PlayerComponent.h
//		Production： 2023/12/25
//		Author　　： 石田 恭一	
// 
//		プレイヤーの各パーツたちの基底クラス
//	
#pragma once
#include "../Object.h"
#include "../Player.h"
#include "IPlayerComponent.h"

class Player;
class Object;

class PlayerComponent : public Object, public IPlayerComponent
{
	//	アクセサ
public:

	//	一番上の親を取得する
	Player* GetRoot()	{ return m_root; }
	//	親を取得する
	Object* GetParent() { return m_parent; }

	//	変数
private:

	//	一番上の親
	Player* m_root;
	//	親
	Object* m_parent;

	//	関数
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="root">ルート</param>
	/// <param name="paren">親</param>
	PlayerComponent(Player* root, Object* parent)
		:m_root(root),
		m_parent(parent)
	{
	}

	//	デストラクタ
	~PlayerComponent() override {};

	/// <summary>
	/// 初期化する
	/// </summary>
	void Initialize() override {};
	
	/// <summary>
	/// 部品を更新する
	/// </summary>
	/// <param name="timer">タイマー</param>
	void UpdateParts(const DX::StepTimer& timer) override { UNREFERENCED_PARAMETER(timer); }

	/// <summary>
	/// 死亡アニメーション
	/// </summary>
	/// <param name="timer">タイマー</param>
	void DeathAnimation(const DX::StepTimer& timer) override { UNREFERENCED_PARAMETER(timer); }

	/// <summary>
	/// 勝利アニメーション
	/// </summary>
	/// <param name="timer">タイマー</param>
	void WinAnimation(const DX::StepTimer& timer) override { UNREFERENCED_PARAMETER(timer); }
	
	/// <summary>
	/// モデルの描画
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="world">ワールド</param>
	/// <param name="view">ビュー</param>
	/// <param name="proj">プロジェクション</param>
	void DrawModel(DirectX::Model* model, const DirectX::SimpleMath::Matrix& world, const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj) override
	{
		model->Draw
		(
			MyLib::ScreenResources::GetInstance()->GetDeviceContext(),
			*MyLib::ScreenResources::GetInstance()->GetCommonState(),
			world,
			view,
			proj
		);
	}
};