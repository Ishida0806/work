
#pragma once

class Number
{
	//	アクセサ
public:

	/// <summary>
	/// 数字たちの座標を取得する
	/// </summary>
	/// <returns>/ 数字たちの座標</returns>
	inline DirectX::SimpleMath::Vector2 GetNumberPos()	const	{ return m_numPosition; }

	/// <summary>
	/// スコアの座標を取得する
	/// </summary>
	/// <returns>スコアの座標</returns>
	inline DirectX::SimpleMath::Vector2 GetScorePos()	const	{ return m_scorePosition; }


	/// <summary>
	/// スコアを取得する
	/// </summary>
	/// <returns>スコア</returns>
	inline int GetScore()								const	{ return m_score; }

	/// <summary>
	/// 番号の座標を設定する
	/// </summary>
	/// <param name="pos">座標</param>
	void SetNumberPos(const DirectX::SimpleMath::Vector2& pos);

	/// <summary>
	/// スコアの座標を設定する
	/// </summary>
	/// <param name="pos">座標</param>
	void SetScorePos(const DirectX::SimpleMath::Vector2& pos);

	/// <summary>
	/// スコアを設定する
	/// </summary>
	/// <param name="score">スコア</param>
	void SetScore(const int& score);

	//	定数
public:

	//  スコアの増加量
	static const float						  INCREMENT_SCORE_SPEED;
	//	数字ごとの距離
	static const float						  DISTANCE_NUMBER;
	//	目標値
	static const int						  TARGET_INCREMENT_SCORE;
	//	最大桁数
	static const int						  MAX_DIGIT;
	//	数字の真ん中
	static const DirectX::SimpleMath::Vector2 NUMBER_TEXTURE_ORIGIN;

	//	列挙型
public:

	//	序数
	enum class OrdinalNumber
	{
		ZEROTH	= 0,
		FIRST	= 1,
		SECOND  = 2,
		THIRD	= 3,
		FOURTH	= 4,
		FIFTH	= 5,
		SIXTH	= 6,
		SEVENTH	= 7,
		EIGHTH	= 8,
		NINTH	= 9
	};

	//	変数
private:

	//	数字画像
	ID3D11ShaderResourceView*		m_numTexture;
	//	スコアの画像
	ID3D11ShaderResourceView*		m_scoreTexture;
	//	数字の座標
	DirectX::SimpleMath::Vector2	m_numPosition;
	//	スコアの座標
	DirectX::SimpleMath::Vector2	m_scorePosition;
	//	スプライトバッチ
	DirectX::SpriteBatch*			m_spriteBatch;
	//	スコア
	int								m_score;

	//	関数
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="texture">画像</param>
	/// <param name="position">表示座標</param>
	Number(ID3D11ShaderResourceView* texture,const DirectX::SimpleMath::Vector2& position);

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="texture">画像</param>
	/// <param name="position">表示座標</param>
	/// <param name="score">スコア</param>
	Number(ID3D11ShaderResourceView* texture, const DirectX::SimpleMath::Vector2& position,const int& score);

	///
	~Number();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新する
	/// </summary>
	/// <param name="score"></param>
	void Update(int score);

	/// <summary>
	/// 描画を行う
	/// </summary>
	void Draw();

	/// <summary>
	/// 数字のみ描画を行う
	/// </summary>
	void DrawNumber(float size = 1.0f, float interval = 1.0f);

	/// <summary>
	/// 数字を描画する
	/// </summary>
	void DrawWaveNumber();

	/// <summary>
	/// 描画を行う・サイズを変更する
	/// </summary>
	/// <param name="interval">画像の間隔</param>
	void Draw(float interval);

	//	プライベート関数
private:
	//	デバイス依存のリソース
	void CreateDeviceDependentResources();


	/// <summary>
	/// 表示する画像範囲を決める
	/// </summary>
	/// <param name="score">スコア「一桁」</param>
	/// <returns>画像の範囲内</returns>
	RECT JudDigit(int score);

	/// <summary>
	/// 各桁の数字を取得
	/// </summary>
	/// <param name="number">数字</param>
	/// <param name="digitPosition">桁何個目か</param>
	/// <returns>その桁が何個目か</returns>
	int GetDigitAt(int number, int digitPosition);


	/// <summary>
	/// ストリング型に
	/// </summary>
	/// <param name="value">スコアの値</param>
	/// <returns>string</returns>
	std::string GetString(int value);
};