//
//		File Name ： Pause.h
//		Production： 2023/10/1
//		Author　　： 石田 恭一
// 
#pragma once

class PlayScene;

class Pause
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
	static const float						  VELOCITY;
	//	座標のXの最大値
	static const float						  X_MAX;
	//	状態による増加量
	static const float						  X_INCREMENT;
	//	画像の大きさ
	static const DirectX::SimpleMath::Vector2 BASE_SCALE;
	//	選択されているときの大きさ
	static const DirectX::SimpleMath::Vector2 SELECT_SCALE;

	//	ステート
public:

	enum class STATE_SOUND
	{
		SE = 0,
		BGM = 1,
		TITLE = 2,
		END = 3,

		OverID = 4
	};

	//	変数
private:
	//	プレイシーン
	PlayScene*						m_playScene;
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
	//	タイトル
	ID3D11ShaderResourceView*		m_title;
	//	ENDの画像
	ID3D11ShaderResourceView*		m_end;
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
	//	Titleの位置
	DirectX::SimpleMath::Vector2	m_titlePos;
	// ENDGAMEの位置
	DirectX::SimpleMath::Vector2	m_endGamePos;
	//	SEの大きさ
	DirectX::SimpleMath::Vector2	m_seScale;
	//	BGMの大きさ
	DirectX::SimpleMath::Vector2	m_bgmScale;
	//	Titleの大きさ
	DirectX::SimpleMath::Vector2	m_titleScale;
	//	ENDGAMEの大きさ
	DirectX::SimpleMath::Vector2	m_endGameScale;
	//	ポーズ中か？
	bool							m_isPause;
	//	seの透明度
	float							m_seAlfa;
	//	bgmの透明度
	float							m_bgmAlfa;
	//	endの透明度
	float							m_endAlfa;
	//	titleの透明度
	float							m_titleAlfa;
	//	ステート
	STATE_SOUND						m_stateSound;

	//	関数
public:

	Pause(PlayScene* playScene);
	~Pause();

	//	初期化処理
	void Initialize();
	//	更新処理
	void Update();
	//	描画処理
	void Render();
	//	終了処理
	void Finalize();

	//	組み込み関数関数
private:

	//	デバイス依存のリソースの初期化
	void CreateDeviceDependentResources();
	//	アルファ地を変化させる
	void UpdateAlfa();
	//	キー情報を更新する
	void UpdateKey();
	//	UIの描画
	void RenderUI();
	//	ステート状態を変化させる
	void CheckState();
};