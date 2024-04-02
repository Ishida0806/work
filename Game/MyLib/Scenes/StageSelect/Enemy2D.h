//
//		File Name ： Enemy2D.h
//		Production： 2023/10/25
//		Author　　： 石田 恭一	
//
#pragma once


class Enemy2D
{
	//	アクセサ
public:

	//	生成数
	static const int						   GENERATION_ENEMY2D;
	//	画像の真ん中
	static const DirectX::SimpleMath::Vector2  ORIGIN_ENEMY2D_TEXTURE;

	//	変数
private:

	//	座標
	DirectX::SimpleMath::Vector2	m_enemy2DPos;
	//	画像
	ID3D11ShaderResourceView*		m_enemy2DTexture;
	//	ランダムな向き
	int								m_randomDirection;
	//	角度
	float							m_angle;
	//	ランダムな大きさ
	float							m_randomScale;
	//	ランダムな速度
	float							m_randomSpeed;
	//	ランダムな揺れ幅
	float							m_randomShake;

	//	関数
public:
	
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="texture">画像</param>
	/// <param name="position">座標</param>
	Enemy2D(ID3D11ShaderResourceView* texture,const DirectX::SimpleMath::Vector2& position);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Enemy2D();

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

	//	プライベート関数
private:

	/// <summary>
	/// デバイス依存のリソースの初期化
	/// </summary>
	void CreateDeviceDependentResources();
};

