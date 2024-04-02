//
//		File Name ： ChangeEffectPlay.h
//		Production： 2023/1/17
//		Author　　： 石田 恭一	
//
#pragma once
#include "ChangeEffect.h"

class ChangeEffectPlay : public ChangeEffect
{
	//	定数
public:

	//	フェードの時間
	static const float						  PLAY_FADE_TIME;
	//	アルファの値の減る値
	static const float						  DIMINISH_ALFA_VALUE;
	//	退出フェード時の補正値
	static const float						  CORRECTION_OUT_FADE;

	//	変数
private:



	//関数
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ChangeEffectPlay();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ChangeEffectPlay() override;

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