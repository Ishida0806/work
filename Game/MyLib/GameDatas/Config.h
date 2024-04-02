//
//		File Name ： Config.h
//		Production： 2023/10/1
//		Author　　： 石田 恭一
// 
#pragma once

class Config
{
	//	アクセサ
public:
	//	ポーズ中か？
	inline bool IsPause()	const { return m_isPause; }
	//	ポーズ中を設定する
	void SetPause(bool flag);

	//	定数
public:

	//	移動量
	static const float VELOCITY;
	//	座標のXの最大値
	static const float X_MAX;
	//	状態による増加量
	static const float X_INCREMENT;
	//	画像の大きさ
	static const DirectX::SimpleMath::Vector2 BASE_SCALE;
	//	選択されているときの大きさ
	static const DirectX::SimpleMath::Vector2 SELECT_SCALE;

	//	ステート
public:

	enum class STATE_SOUND
	{
		SE = 0,
		BGM = 1
	};

	//	変数
private:
	//	オーディオマネージャ
	AudioManager*					m_audio;
	//	スプライトバッチ
	DirectX::SpriteBatch*			m_sprite;
	//	ボタンの画像
	ID3D11ShaderResourceView*		m_button;
	//	バーの画像
	ID3D11ShaderResourceView*		m_bar;
	//	黒の画像
	ID3D11ShaderResourceView*		m_black;
	//	案内キーの画像
	ID3D11ShaderResourceView*		m_guideKey;
	//	SEの画像
	ID3D11ShaderResourceView*		m_guideSE;
	//	BGMの画像
	ID3D11ShaderResourceView*		m_guideBGM;
	//	ESCAPEきーのUI
	ID3D11ShaderResourceView*		m_esc;
	//	ボタンの座標上部
	DirectX::SimpleMath::Vector2	m_buttonTopPos;
	//	ボタンの座標下部
	DirectX::SimpleMath::Vector2	m_buttonUnderPos;
	//	バーの座標上部
	DirectX::SimpleMath::Vector2	m_barTopPos;
	//	バーの座標下部
	DirectX::SimpleMath::Vector2	m_barUnderPos;
	//	黒の画像の座標
	DirectX::SimpleMath::Vector2	m_blackPos;
	//	案内キーの画像位置
	DirectX::SimpleMath::Vector2	m_guidePos;
	//	SEの画像位置
	DirectX::SimpleMath::Vector2	m_sePos;
	//	BGMの画像位置
	DirectX::SimpleMath::Vector2	m_bgmPos;
	//	SEの画像の大きさ
	DirectX::SimpleMath::Vector2	m_seScale;
	//	BGM	の画像の大きさ
	DirectX::SimpleMath::Vector2	m_bgmScale;
	//	ポーズ中か？
	bool							m_isPause;
	//	seの透明度
	float							m_seAlfa;
	//	bgmの透明度
	float							m_bgmAlfa;
	//	ステート
	STATE_SOUND						m_stateSound;

	//	関数
public:

	Config();
	~Config();

	//	初期化処理
	void Initialize();
	//	更新処理
	void Update();
	//	描画処理
	void Render();
	//	終了処理
	void Finalize();

	//	プライベート関数
private:

	//	デバイス依存のリソースの初期化
	void CreateDeviceDependentResources();
	void UpdateAlfa();
	void UpdateKey();
	void RenderUI();
	void CheckState();
};