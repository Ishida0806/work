//
//		File Name ： ScoreOutPut.h
//		Production： 2023/11/12
//		Author　　： 石田 恭一	
//
#pragma once

class Number;
class PlayInfo;

class ScoreOutPut
{
	//	定数
public:

	//	スコアの座標
	static const DirectX::SimpleMath::Vector2 SCORE_POSITION;
	//	スコアの真ん中の座標
	static const DirectX::SimpleMath::Vector2 SCORE_ORIGIN_POSITION;

	//	変数
private:

	//	プレイインフォメーション
	PlayInfo* m_pPlayInfo;
	//	スコアを表示する
	std::unique_ptr<Number>		m_pScore;
	//	　ノーマルスコアを表示する
	std::unique_ptr<Number>		m_pNormalKnock;
	//	　突撃スコアを表示する
	std::unique_ptr<Number>		m_pTackleKnock;
	//	　ボススコアを表示する
	std::unique_ptr<Number>		m_pBossKnock;

	//	関数
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ScoreOutPut();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ScoreOutPut();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <returns></returns>
	bool Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();
};