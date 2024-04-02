//
//		File Name ： PlayerLeftArm.h
//		Production： 2023/12/27
//		Author　　： 石田 恭一	
// 
//		プレイヤーの各パーツたち
//	
#pragma once
#include "../Player.h"
#include "../PlayeComponent/PlayerComponent.h"

class Player;

class PlayerLeftArm : public PlayerComponent
{
	//	定数
public:

	//	死亡時の加速
	static const DirectX::SimpleMath::Vector3 DEATH_ACCELERATION;
	//	歩く際の揺れる
	static const float						  CORRECTION_SPEED;
	//	時間の加速度
	static const float						  ACCELERATION_TIMER;
	//	座標を戻す速度
	static const float						  RETURN_SPEED;

	//	変数
private:

	//	モデル
	DirectX::Model* m_model;
	//	経過時間
	float			m_elapsedTime;


	//	関数
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="root">ルート</param>
	/// <param name="paren">親</param>
	PlayerLeftArm(Player* root, Object* parent);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~PlayerLeftArm();

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
	/// 勝利アニメーション
	/// </summary>
	/// <param name="timer">タイマー</param>
	void WinAnimation(const DX::StepTimer& timer) override;

	/// <summary>
	/// モデルの描画
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="world">ワールド</param>
	/// <param name="view">ビュー</param>
	/// <param name="proj">プロジェクション</param>
	void DrawModel(DirectX::Model* model, const DirectX::SimpleMath::Matrix& world, const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj) override;
};