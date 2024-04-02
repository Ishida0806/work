//
//		File Name ： PostEffect.h
//		Production： 2023/1/10
//		Author　　： 石田 恭一	
//
#pragma once

class PostEffect
{
	//	列挙型
public:

	enum class PostEffectType
	{
		None = 0,

		PowerUP = 1,
		HealthUP = 2,
		SpeedUP = 3,
		PlayerHPCrisis = 4,

		OverID
	};

	//	アクセサ
public:

	inline PostEffectType			  GetEffectType()	const { return m_postType; }
	//	カラーを取得する
	inline DirectX::SimpleMath::Color GetColor()		const  { return m_color; }
	//	経過時間を取得
	inline float					  GetElapsedTime()	const  { return m_elapsedTime; }
	//	カラーを設定する
	void SetColor(const DirectX::SimpleMath::Color& color)	   { m_color = color; }
	//	カラーをラープで設定する
	void SetLerpColor(const DirectX::SimpleMath::Color& color) { m_color = DirectX::SimpleMath::Color::Lerp(m_color, color, 0.1f); }
	//	経過時間をリセット
	void ResetElapseTime()									   { m_elapsedTime = 0.0f; }

	//	変数
private:

	//	ポストエフェクトのタイプ
	PostEffectType				m_postType;
	//	カラー
	DirectX::SimpleMath::Color	m_color;
	//	経過時間
	float						m_elapsedTime;

	//	関数
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	PostEffect(const PostEffectType& postType)
		:m_postType(postType),
		m_elapsedTime(0.0f)
	{
		m_color = DirectX::SimpleMath::Color(0.0f, 0.0f, 0.0f, 0.0f);
	}

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~PostEffect() = default;

	/// <summary>
	///	初期化処理
	/// </summary>
	virtual void Initialize() 
	{
	};

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="timer">タイマー</param>
	virtual void Update(const DX::StepTimer& timer)
	{ 
		m_elapsedTime += static_cast<float>(timer.GetElapsedSeconds()); 
	}

	/// <summary>
	/// 描画のタイプ
	/// </summary>
	virtual void Draw() 
	{

	};

	/// <summary>
	/// カラーと時間をリセットする
	/// </summary>
	void ResetColorAndTime()
	{
		m_color = DirectX::SimpleMath::Color(0.0f, 0.0f, 0.0f, 0.0f);

		m_elapsedTime = 0.0f;
	}

	/// <summary>
	/// カラーをラープでリセットする
	/// </summary>
	void ResetLerpColor()
	{
		m_color = DirectX::SimpleMath::Color::Lerp(m_color, DirectX::SimpleMath::Color(0.0f, 0.0f, 0.0f, 0.0f), 0.03f);
	}
};