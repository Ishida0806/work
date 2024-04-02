//
//		File Name ： ChangeEffectStageSelect.h
//		Production： 2023/1/17
//		Author　　： 石田 恭一	
//
#pragma once
#include "ChangeEffect.h"

class ChangeEffectStageSelect : public ChangeEffect
{
	//	定数
public:

	//	フェードの時間
	static const float						  STAGE_FADE_TIME;
	//	ドアの動く速度
	static const float						  DOOR_MOVE_SPEED;
	//	ステージの入場する際のドアの右側の座標
	static const DirectX::SimpleMath::Vector2 STAGE_TO_RIGHT_DOOR_POSITION;
	//	ステージの入場する際のドアの左側の座標
	static const DirectX::SimpleMath::Vector2 STAGE_TO_LEFT_DOOR_POSITION;
	//	ステージの退場する際のドアの右側の座標
	static const DirectX::SimpleMath::Vector2 STAGE_OUT_RIGHT_DOOR_POSITION;
	//	ステージの退場する際のドアの左側の座標
	static const DirectX::SimpleMath::Vector2 STAGE_OUT_LEFT_DOOR_POSITION;

	//	変数
private:

	//	黒の右の座標
	DirectX::SimpleMath::Vector2			    m_blackRightPos;
	//	黒の左の座標
	DirectX::SimpleMath::Vector2			    m_blackLeftPos;
	

	//関数
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ChangeEffectStageSelect();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ChangeEffectStageSelect() override;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// そのシーンに遷移する
	/// </summary>
	void ToChange() override;

	/// <summary>
	/// シーンを抜ける
	/// </summary>
	void OutChange() override;

	/// <summary>
	/// エフェクトの描画
	/// </summary>
	void Draw() override;

	/// <summary>
	/// 事前の初期化を行う
	/// </summary>
	void PreInitialize() override;
};