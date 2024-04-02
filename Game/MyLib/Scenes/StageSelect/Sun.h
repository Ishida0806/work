//
//		File Name ： Sun.h
//		Production： 2023/11/25
//		Author　　： 石田 恭一	
//
#pragma once


class Sun final
{
	//	アクセサ
public:

	//	画像の真ん中
	static const DirectX::SimpleMath::Vector2  ORIGIN_SUN_TEXTURE;

	//	変数
private:

	//	座標
	DirectX::SimpleMath::Vector2	m_position;
	//	目標座標
	DirectX::SimpleMath::Vector2	m_targetPosition;
	//	おおきさ
	DirectX::SimpleMath::Vector2	m_scale;
	//	画像
	ID3D11ShaderResourceView*		m_sunTexture;
	//	現在のステージ
	int								m_stage;
	//	角度
	float							m_angle;
	//	アルファ値
	float							m_alfa;
	//	次に移動するための時間
	float							m_startTime;

	//	関数
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Sun();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Sun();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="timer">タイマー</param>
	/// <param name="stageNum">ステージ番号/param>
	void Update(const DX::StepTimer& timer, const int& stageNum);

	/// <summary>
	/// 描画する
	/// </summary>
	void Draw();

	//	埋め込み関数
private:

	/// <summary>
	/// デバイス依存のリソースの初期化
	/// </summary>
	void CreateDeviceDependentResources();
};

