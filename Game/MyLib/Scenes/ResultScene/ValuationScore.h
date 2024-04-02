//
//		File Name ： ValuationScore.h
//		Production： 2023/11/12
//		Author　　： 石田 恭一	
//
#pragma once

class ValuationScore
{
	//	定数
public:

	//	下幅の増加量
	static const double						  INCREASE_BOTTOM;
	//	評価の場所
	static const DirectX::SimpleMath::Vector2 VALUCATION_POSITION;
	//	評価の真ん中の場所
	static const DirectX::SimpleMath::Vector2 VALUCATION_ORIGIN_POSITION;
	//	評価画像の大きさ
	static const DirectX::SimpleMath::Vector2 VALUCATION_BASE_SCALE;
	//	曲げる角度
	static const float						  TARGET_ANGLE;
	//	イージーステージがセレクトされた
	static const int						  SELECT_EASY;
	//	ノーマルステージがセレクトされた
	static const int						  SELECT_NORMAL;
	//	ハードステージがセレクトされた
	static const int						  SELECT_HARD;
	//	エンドレスステージがセレクトされた
	static const int						  SELECT_ENDRES;


	//	変数
private:

	//	判子の画像
	ID3D11ShaderResourceView* m_valutationTex;
	//	リソースマネージャ
	MyLib::ResourcesData*	  m_res;
	//	描画してもいいか？
	bool					  m_isDraw;

	//	関数
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	ValuationScore();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ValuationScore();

	/// <summary>
	/// 初期化処理
	/// </summary>
	/// <param name="selectStage">セレクトされたステージ番号</param>
	/// <param name="score">スコア</param>
	void Initialize(const int& selectStage, const int& score);
	
	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="isTop">上に上がったか？</param>
	void Update(const bool& isTop);

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

	/// <summary>
	/// 終了処理
	/// </summary>
	void FInalize();
};