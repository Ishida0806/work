
#pragma once

class Player;

class LevelCardEffect
{
	//	アクセサ
public:

	//	クリック可能か？
	inline bool IsClickAble()	const { return m_clickAble; }
	//	準備できたか？
	inline bool IsReady()		const { return m_isReady; }
	//	クリックが押された
	void SetClick();

	//	定数
public:

	//	カードの真ん中の座標
	static const DirectX::SimpleMath::Vector2 CARD_ORIGIN_POSITION;
	//	カードの座標
	static const DirectX::SimpleMath::Vector2 CARD_POSITION;
	//	マウスカーソル接触後のスケール
	static const DirectX::SimpleMath::Vector2 CARD_SCALE;
	//	カードのずらす座標	
	static const float						  OFFSET_POSITION;

	//	変数
private:

	//	プレイヤー
	Player*							m_player;
	//	目標座標
	DirectX::SimpleMath::Vector2	m_targetPosition;
	//	現在の座標
	DirectX::SimpleMath::Vector2	m_position;
	//	大きさ
	DirectX::SimpleMath::Vector2	m_scale;
	//	画像
	ID3D11ShaderResourceView*		m_texture;
	//	カードのタイプ
	int								m_type;
	//	クリック可能か
	bool							m_clickAble;
	//	準備可能OKか
	bool							m_isReady;

	//	関数
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="player">プレイヤー</param>
	/// <param name="type">タイプ/param>
	LevelCardEffect(Player* player, const int& type);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~LevelCardEffect();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// キーで選択されている
	/// </summary>
	void SelectKey();

	/// <summary>
	/// キーで選択されていない
	/// </summary>
	void SelectNotKey();

	/// <summary>
	/// 退出処理
	/// </summary>
	void Exit();

	/// <summary>
	/// 描画する
	/// </summary>
	void Draw();

	/// <summary>
	/// カードの中にマウスカーソルが入って来た
	/// </summary>
	/// <param name="mousePosition">マウスカーソルの座標</param>
	bool InMouseCarsor(const DirectX::SimpleMath::Vector2& mousePosition);

	/// <summary>
	/// クリックされた
	/// </summary>
	void Click();

	//	埋め込み関数
private:

	//	座標を指定地に
	void ResetPosition();
	//	大きさをかえる
	void ResizeScale();
};