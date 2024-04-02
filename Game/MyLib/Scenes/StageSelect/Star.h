//
//		File Name ： Star.h
//		Production： 2023/11/02
//		Author　　： 石田 恭一	
// 
#pragma once

class Star final
{
	//	定数
public:

	//	星の画像の中央の座標
	static const DirectX::SimpleMath::Vector2	ORIGIN_STAR_POSITION;

	//	変数
private:

	//	画像
	ID3D11ShaderResourceView*		m_starTexture;
	//	座標
	DirectX::SimpleMath::Vector2	m_position;
	//	記憶座標
	DirectX::SimpleMath::Vector2	m_memoryPosition;
	//	色
	DirectX::SimpleMath::Color		m_color;
	//	記憶の色
	DirectX::SimpleMath::Color		m_memoryColor;
	//	現在のスケール
	DirectX::SimpleMath::Vector2	m_scale;
	//	最初ののスケール
	DirectX::SimpleMath::Vector2	m_memoryScale;
	//	速度
	float							m_speed;
	//	生存時間
	float							m_lifeCount;
	//	記憶の生存時間
	float							m_memoryLifeCount;
	//	使用状態
	bool							m_isUsed;

public:
	 
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="starTexture">画像</param>
	/// <param name="position">座標</param>
	/// <param name="color">色</param>
	/// <param name="scale">大きさ</param>
	/// <param name="speed">速度</param>
	/// <param name="lifeCount">生存時間</param>
	Star
	(
		ID3D11ShaderResourceView* starTexture,
		const DirectX::SimpleMath::Vector2& position,
		const DirectX::SimpleMath::Color&   color,
		const DirectX::SimpleMath::Vector2& scale,
		const float&						speed,
		const float&						lifeCount
	);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Star();

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
	/// 描画する
	/// </summary>
	void Draw();

	/// <summary>
	/// 終了処理
	/// </summary>
	void Finalize();

	//	埋め込み関数
private:

	/// <summary>
	/// 開始する
	/// </summary>
	void BeginStar();
};