
#pragma once
#include "LevelCardEffect.h"
#include "LevelCardBackGround.h"

class PlayScene;
class Player;

class LevelCard
{
	//	定数
public:

	//	背景画像の中心点
	static const DirectX::SimpleMath::Vector2 BACKGROUND_ORIGIN_POSITION;
	//	待機時間
	static const float						  WAIT_SECONDS;


	//	列挙型
public:

	//	カードのタイプ
	enum class CardType
	{
		PowerUP	= 0,
		HealthUP	= 1,
		SpeedUP	= 2,

		OverID = 3
	};

	//	変数
private:

	//	プレイシーン
	PlayScene*									  m_playScene;
	//	プレイヤー
	Player*										  m_player;
	//	カード達
	std::vector<std::unique_ptr<LevelCardEffect>> m_cards;
	//	背景画像クラス
	std::unique_ptr<LevelCardBackGround>		  m_backGround;
	//	クリックされた
	bool										  m_isClick;
	//	待機時間を終了
	bool										  m_finStand;
	//	待機時間
	float										  m_standbyTime;
	//	プレイヤーのレベル
	int											  m_playerLevel;
	//	選ばれている番号
	int											  m_selectCard;

	//	関数
public:

	/// <summary>
	///	コンストラクタ
	/// </summary>
	/// <param name="playScene">プレイシーン</param>
	/// <param name="player">プレイヤー</param>
	LevelCard(PlayScene* playScene ,  Player* player);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~LevelCard();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="timer">タイマー</param>
	/// <returns>使用状態</returns>
	bool Update(const DX::StepTimer& timer);

	/// <summary>
	/// 描画する
	/// </summary>
	void Draw();

	//	埋め込み関数
private:

	//	キーの操作
	bool KeyUpdate();
	//	マウスの更新
	bool MouseUpdate();
	//	クリックされた
	bool ClickedCard();

	//	マウス座標を取得する
	DirectX::SimpleMath::Vector2 GetMousePosition();
};