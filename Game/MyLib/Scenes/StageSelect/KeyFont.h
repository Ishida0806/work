//
//		File Name ： KeyFont.h
//		Production： 2023/11/01
//		Author　　： 石田 恭一	
// 
#pragma once

class KeyFont
{
	//	定数
public:

	//	画像の真ん中の位置の初期化する	
	static const DirectX::SimpleMath::Vector2 ORIGIN_KEY_TEXTURE;
	//	キーの大きさ
	static const DirectX::SimpleMath::Vector2 SCALE_KEY_TEXTURE;
	//	動く速さ
	static const float						  MOVE_KEY_SPEED;

	//	列挙型
public:

	enum class FONT_TYPE
	{
		LEFT  = 0,
		RIGHT = 1,

		OverID = 2
	};

	//		アクセサ
public:

	inline FONT_TYPE GetType()	const { return m_fontType; }

	//	変数
private:

	//	キー画像
	ID3D11ShaderResourceView*		m_keyFontTexture;
	//	キー座標
	DirectX::SimpleMath::Vector2	m_keyPosition;
	//	どっちの向きかな？
	FONT_TYPE						m_fontType;
	//	経過時間
	float							m_elapsedTime;
			
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="type">タイプ</param>
	/// <param name="position">座標</param>
	KeyFont(const FONT_TYPE type, const DirectX::SimpleMath::Vector2 position);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~KeyFont();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="timer">タイマー</param>
	void Update(const DX::StepTimer& timer);

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();
};