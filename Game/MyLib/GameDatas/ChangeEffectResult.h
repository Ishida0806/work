//
//		File Name ： ChangeEffectResult.h
//		Production： 2023/1/17
//		Author　　： 石田 恭一	
//
#pragma once
#include "ChangeEffect.h"

class ChangeEffectResult : public ChangeEffect
{
	//	定数
public:

	//	フェードの時間
	static const float						  RESULT_FADE_TIME;
	//	退出フェード時の補正値
	static const float						  CORRECTION_OUT_FADE;

	//	変数
private:



	//関数
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ChangeEffectResult();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ChangeEffectResult() override;

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