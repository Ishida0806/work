//
//		File Name ： ChangeEffectTitle.h
//		Production： 2023/1/17
//		Author　　： 石田 恭一	
//
#pragma once
#include "ChangeEffect.h"

class ChangeEffectTitle : public ChangeEffect
{
	//	定数
public:

	//	フェードの時間
	static const float TITLE_FADE_TIME;
	

	//関数
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ChangeEffectTitle();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ChangeEffectTitle() override;

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
};