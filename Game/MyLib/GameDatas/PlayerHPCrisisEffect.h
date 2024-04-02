//
//		File Name ： PlayerHPCrisisEffect.h
//		Production： 2023/1/10
//		Author　　： 石田 恭一	
//
#pragma once
#include "PostEffect.h"

class PlayerHPCrisisEffect : public PostEffect
{
	//	定数
public:

	//	タイマーの加速
	static const float						  TIMER_SPEED;
	//	赤色の濃度
	static const float						  RED_DENSITY;
	//	通常の大きさX
	static const float						  DEFAULT_SCALE_X;
	//	通常の大きさY
	static const float						  DEFAULT_SCALE_Y;
	//	拡大の補正値
	static const float						  CORRECTION_EXPANSION;
	//	ポストエフェクトの真ん中
	static const DirectX::SimpleMath::Vector2 CRISIS_ORIGIN_POSITION;

	//	変数
private:

	//	画像
	ID3D11ShaderResourceView*	 m_texture;
	//	おおきさ
	DirectX::SimpleMath::Vector2 m_scale;
	
	//	関数
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	PlayerHPCrisisEffect();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~PlayerHPCrisisEffect() override;

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