//
//		File Name ： PlayerSwingSpeedEffect.h
//		Production： 2023/1/15
//		Author　　： 石田 恭一	
//
#pragma once
#include "PostEffect.h"

class PlayerSwingSpeedEffect : public PostEffect
{
	//	定数
public:

	//	タイマーの加速
	static const float						  TIMER_SPEED;
	//	ポストエフェクトの真ん中
	static const DirectX::SimpleMath::Vector2 CRISIS_ORIGIN_POSITION;

	//	変数
private:

	//	画像
	ID3D11ShaderResourceView*	 m_texture;
	
	//	関数
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	PlayerSwingSpeedEffect();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~PlayerSwingSpeedEffect() override;

	/// <summary>
	///	初期化処理
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="timer">タイマー</param>
	void Update(const DX::StepTimer& timer) override;

	/// <summary>
	/// 描画のタイプ
	/// </summary>
	void Draw() override;
};