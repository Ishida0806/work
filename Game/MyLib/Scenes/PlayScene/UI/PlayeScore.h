//
//		File Name ： PlayeScore.h
//		Production： 2023/11/27
//		Author　　： 石田 恭一
// 
#pragma once

#include "Game/MyLib/GameDatas/IUI.h"

class Number;
class PlayInfo;
interface IUI;

class PlayeScore : public IUI
{
	//	定数
public:
	//	数字の座標
	static const DirectX::SimpleMath::Vector2 NUM_POSITION;
	//	スコアの座標
	static const DirectX::SimpleMath::Vector2 SCORE_POSITION;

	//	変数
private:

	//	プレイインフォメーション
	PlayInfo*					m_playInfo;
	//	スコア表示
	std::unique_ptr<Number>		m_scoreDisplay;
	//	プレイヤーの体力バー
	ID3D11ShaderResourceView*	m_scoreBackGround;

	//	関数
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	PlayeScore();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~PlayeScore();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize()						override;

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="timer">タイマー</param>
	void Update(const DX::StepTimer& timer)	override;

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw()								override;

	/// <summary>
	/// 経過時間を止める
	/// </summary>
	void StopElapsedTimer();

	//	埋め込み関数
private:

	//	デバイス依存のリソースの初期化
	void CreateDeviceDependentResources();
};