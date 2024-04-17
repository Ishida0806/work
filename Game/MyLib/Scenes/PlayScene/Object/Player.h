//
//		File Name ： Player.h
//		Production： 2023/6/12
//		Author　　： 石田 恭一	
//	
#pragma once

#include "Object.h"
#include "Game/MyLib/Scenes/PlayScene/Object/PlayerCircle/PlayerArrow.h"
#include "Game/MyLib/Scenes/PlayScene/Object/Cursor/Cursor.h"
#include "Game/MyLib/Scenes/PlayScene/Object/Wepons/Sord.h"
#include "Game/MyLib/GameDatas/PlayerStatus.h"
#include "Game/MyLib/GameDatas/PlayerMove.h"


class Sord;
class Cursor;
class PlayerCircle;
class PlayerComponent;

class Player : public Object , public PlayerStatus , public PlayerMove
{
	//	アクセサ
public:

	//	攻撃状態を取得
	inline bool								 IsAttack()					const { return m_sord->IsAttack(); }
	//	生存しているか？
	inline bool								 IsAlive()					const { return m_isAlive; }
	//	死亡アニメーション中か？
	inline bool								 IsDeathAnimation()			const { return m_isDeathAnimation; }
	//	アニメーション中か？
	inline bool								 IsAnimation()				const { return m_isAnimation; }
	//	勝利アニメーション中か？
	inline bool								 IsWinAnimation()			const { return m_isWinAnimation; }
	//	キャラクターの球の当たり判定
	inline Collision::Shape::Sphere			 GetSphere()				const { return m_playerSphere; }
	//	ソードの取得
	inline Sord*							 GetSord()					const { return m_sord.get(); }
	//	剣のカプセルの当たり判定
	inline Collision::Shape::Capsule		 GetSordCapuselColision()	const { return m_sord->GetWeponCapsule(); }
	//	剣の座標
	inline DirectX::SimpleMath::Vector3		 GetSordPosition()			const { return m_sord->GetPosition(); }
	//	カーソルの座標取得する
	inline DirectX::SimpleMath::Vector3		 GetCursorPosition()		const { return m_cursorPosition; }
	//	回転角
	inline DirectX::SimpleMath::Quaternion	 GetCursorRotate()			const { return m_cursorRotate; }
	//	試合結果によってアニメーションをかえる
	void WhyGameResult(const std::string& resultString);

	//定数
public:


	//	衝突事のノックバック
	static const float						  REACTION;
	//	壁の場所
	static const float						  WALL_PLACE;

	//	列挙型
public:

	//	プレイヤーステート
	enum class PlayerParts
	{
		None = 0,

		Head = 1,
		RightArm = 2,
		LeftArm = 3,
		RightLeg = 4,
		LeftLeg = 5,

		OverID
	};

	//	関数
public: 
	
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="playerParam">プレイヤーパラメータ</param>
	Player(PlayerData* playerParam);
	//	デストラクタ
	~Player();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="timer">タイマー</param>
	void Update(const DX::StepTimer& timer) override;

	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="view">ビュー</param>
	/// <param name="proj">プロジェクション</param>
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj) override;

	/// <summary>
	/// 終了処理
	/// </summary>
	void Finalize() override;

	/// <summary>
	/// ダメージを与える
	/// </summary>
	/// <param name="damege">ダメージ量</param>
	void Damege(const int& damege);

	/// <summary>
	/// ダメージを与える
	/// </summary>
	/// <param name="damege">ダメージ量</param>
	/// <param name="direction">距離</param>
	/// <param name="reaction">ふっとばし量</param>
	void Damege(const int& damege,DirectX::SimpleMath::Vector3 direction, float reaction = Player::REACTION);

	/// <summary>
	/// ダメージを与える
	/// </summary>
	/// <param name="damege">ダメージ量</param>
	/// <param name="direction">距離</param>
	/// <param name="reaction">ふっとばし量</param>
	void Damege(const int& damege, DirectX::SimpleMath::Vector3 direction, const DirectX::SimpleMath::Vector3& reaction);

	/// <summary>
	/// 死亡時のアニメーション
	/// </summary>
	/// <param name="timer">タイマー</param>
	void DethAnimation(const DX::StepTimer& timer);

	/// <summary>
	/// 勝利時のアニメーション
	/// </summary>
	/// <param name="timer">タイマー</param>
	void WinAnimation(const DX::StepTimer& timer);

	/// <summary>
	/// 生きているか確認する
	/// </summary>
	/// <returns>死亡状態</returns>
	bool HealthCheck();

	/// <summary>
	/// プレイヤーのアニメーション
	/// </summary>
	/// <param name="timer">タイマー</param>
	void PlayerAnimation(const DX::StepTimer& timer);

	//	埋め込み関数
private:

	//	当たり判定の更新
	void UpdateColison();
	//	プレイヤーと剣の更新
	void UpdatePlayerAndSordLerp();
	//	各オブジェクト情報の作成
	void CreateDeviceDependentResources();
	//	プレイヤーをステージに留まらせる
	void ArriveStage();

	//	変数
private:
	//	プレイヤーのモデル
	DirectX::Model*									 m_playerModel;
	//	プレイヤーパラメータ
	PlayerData*										 m_playerParam;
	//	パーツ達
	std::vector<std::unique_ptr<PlayerComponent>>	 m_playerParts;
	//	プリミティブバッチ
	std::unique_ptr<DirectX::GeometricPrimitive>	 m_primitive;
	//	カーソル
	std::unique_ptr<Cursor>							 m_cursol;
	//	剣
	std::unique_ptr<Sord>							 m_sord;
	//	プレイヤーサークル
	std::unique_ptr<PlayerArrow>					 m_playerArrow;
	//	カーソル座標
	DirectX::SimpleMath::Vector3					 m_cursorPosition;
	//	カーソル回転角
	DirectX::SimpleMath::Quaternion					 m_cursorRotate;
	//	重力
	float											 m_gravity;
	//	アニメーション時間
	float											 m_animationTime;
	//	死亡アニメーション
	bool											 m_isDeathAnimation;
	//	勝利アニメーション
	bool											 m_isWinAnimation;
	//	アニメーション中
	bool											 m_isAnimation;
	//	死んでいるか？
	bool											 m_isAlive;
	//	球
	Collision::Shape::Sphere						 m_playerSphere;
	//	剣のカプセル	
	Collision::Shape::Capsule						 m_sordCapsule;

};