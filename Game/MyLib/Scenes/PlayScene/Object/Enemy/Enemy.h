//
//		File Name ： Enemy.h
//		Production： 2023/11/12
//		Author　　： 石田 恭一	
//	
#pragma once
#include "../Object.h"
#include "Game/MyLib/GameDatas/EnemyHeart.h"

class Object;

class Enemy : public Object
{
	//	アクセサ
public:

	//	当たり判定の追加
	void AddColisionEnemy
	(
		const Collision::Shape::Sphere& colisionSpere, 
		const Collision::Shape::Sphere& searchSpere, 
		const Collision::Shape::Sphere& abilitySpere
	);
	//	当たり判定の取得する
	inline  Collision::Shape::Sphere	 GetSphereCollision()	const { return m_sphere; }
	//	索敵範囲を取得する
	inline  Collision::Shape::Sphere	 GetSearchCollision()	const { return m_searchSphere; }
	//	特殊効果範囲を取得する
	inline  Collision::Shape::Sphere	 GetAbilityColision()	const { return m_abilitySphere; }
	//	目標座標の取得
	inline  DirectX::SimpleMath::Vector3 GetTargetPosition()	const { return m_targetPos; }
	//	無敵状態か？
	inline  bool						 IsInvincible()			const { return m_isInvincible; }
	//	ヘイト中か?
	inline	bool						 IsHate()				const { return m_isHate; }
	//	死亡したか？
	inline	bool						 IsDead()				const { return m_isAlive; }
	//	歩いているか
	inline	bool						 IsWalk()				const { return m_isWalk; }
	//	特殊効果を取得する
	inline	bool						 InAbility()			const { return m_inAbility; }
	//	死亡アニメーション中か？
	inline	bool						 IsDeadAnimation()		const { return m_deadAnimation; }
	//	体力を取得
	inline  int							 GetHealth()			const { return m_helath; }
	//	最大体力を取得
	inline  int							 GetMAXHealth()			const { return m_maxHelath; }
	//	力を取得
	inline	int							 GetPower()				const { return m_power; }
	//	敵の経験値を取得する
	inline	int							 GetEXP()				const { return m_enemyEXPoint; }

	//	無敵状態を設定
	void SetInvincibleFlag(bool flag);
	//	目標座標の設定する
	void SetTargetPosition(const DirectX::SimpleMath::Vector3& pos);
	//	ヘイト状態を設定する
	void SetHate(const bool& flag);
	//	特殊技能範囲に入ったかのフラグの設定
	void SetInAbility(const bool& flag);
	//	歩いているか
	void SetWalk(const bool& flag);
	//	ヘイトモードにする
	void SetHateMode();
	//	無敵時間をリセットする
	void ResetInvincibleTime();
	//	死亡アニメーションの開始
	void StartDeathAnimation();
	//	死亡が確定
	void DeathObject();

	//	定数
public:

	//	乱数時間
	static const float	RANDOM_TIME;
	//	壁の位置
	static const float	WALL_PLACE;
	//	挙動
	static const float	ENEMT_TOUCH_REACTION;
	//	無敵時間
	static const float	INVINCIBLE_TIME;

	//	列挙型
public:

	// 方向
	enum class Direction
	{
		//	左向き
		LEFT,
		//	上向き
		TOP,
		//	右向き
		RIGHT,
		//	下向き
		BOTTOM,
		//	何もしない
		NONE
	};

	//	変数
private:

	//	プリミティブバッチ
	std::unique_ptr<DirectX::GeometricPrimitive> m_primitive;
	//	ハート
	std::unique_ptr<EnemyHeart>					 m_heart;
	//	追従ターゲット座標
	DirectX::SimpleMath::Vector3				 m_targetPos;
	//	当たり判定
	Collision::Shape::Sphere					 m_sphere;
	//	球状の索敵範囲
	Collision::Shape::Sphere					 m_searchSphere;
	//	球状の発射可能範囲
	Collision::Shape::Sphere					 m_abilitySphere;
	//	体力
	int											 m_helath;
	//	最大体力値
	int											 m_maxHelath;
	//	力
	int											 m_power;
	//	敵の経験値
	int											 m_enemyEXPoint;	
	//	無敵時間
	float										 m_invincibleTime;
	//	ランダムに入れ替わるまでの時間
	float										 m_randomTime;
	//	徘徊行動で使用する方向
	float										 m_wanderOrientation;
	//	ヘイト中か
	bool										 m_isHate;
	//	無敵時間
	bool										 m_isInvincible;
	//	特殊効果範囲を
	bool										 m_inAbility;
	//	死んでいるか？
	bool										 m_isAlive;
	//	
	bool										 m_isWalk;
	//	死亡アニメーション
	bool										 m_deadAnimation;
	//	敵の向き
	Direction									 m_direction;

	//	関数
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="position">座標</param>
	/// <param name="helath">体力</param>
	/// <param name="power">力</param>
	/// <param name="enemyEXPoint">経験値</param>
	Enemy(const DirectX::SimpleMath::Vector3& position, const int& helath , const int& power , const int& enemyEXPoint);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Enemy();

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
	/// <param name="view">ビュープロジェクション</param>
	/// <param name="proj">ビュー</param>
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj) override;

	/// <summary>
	/// 丸影を作成する
	/// </summary>
	void CreateShadow(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj, const float& shadowScale);

	/// <summary>
	/// 終了処理
	/// </summary>
	void Finalize() override;

	/// <summary>
	/// 自動で移動を行う
	/// </summary>
	/// <param name="timer">タイマー</param>
	void AutoMove(const DX::StepTimer& timer, const float& speed, const float& lookBackSpeed);


	/// <summary>
	/// 目標の向きを取得する
	/// </summary>
	/// <returns>向き</returns>
	DirectX::SimpleMath::Quaternion GetObjectiveRotate();

	/// <summary>
	/// 敵同士の接触で距離を離す
	/// </summary>
	/// <param name="direction"></param>
	void HitEnemyMove(const DirectX::SimpleMath::Vector3& direction);

	/// <summary>
	/// ダメージ与える
	/// </summary>
	/// <param name="damege">ダメージ</param>
	void Damege(int damege);
	
	/// <summary>
	///  ワールドレベル
	/// </summary>
	/// <param name="health">レベル</param>
	/// <param name="power">パワー</param>
	/// <param name="level">レベル</param>
	void StatusUP(const int& health, const int& power, const int& level);

	//	純粋仮想関数
public:

	/// <summary>
	/// プレイヤーの衝突時
	/// </summary>
	/// <param name="direction">向き</param>
	/// <param name="nockBack"></param>
	virtual void HitPlayer(const DirectX::SimpleMath::Vector3& direction, const float& nockBack) 
	{
		UNREFERENCED_PARAMETER(direction);
		UNREFERENCED_PARAMETER(nockBack);
	};

	/// <summary>
	/// アクション状態が行えるか確認する
	/// </summary>
	/// <returns></returns>
	virtual bool IsRedyAbility() { return false; }

	/// <summary>
	/// 特殊効果を設定する
	/// </summary>
	/// <param name="flag"></param>
	virtual void SetAbility(const bool& flag) { UNREFERENCED_PARAMETER(flag); }

	/// <summary>
	/// スタン状態にする
	/// </summary>
	virtual void SwoonMode() {};

	//	埋め込み関数
private:

	//	ランダムな方向に向きを変える
	void RandomMoveDirection(const DX::StepTimer& timer, const float& speed);
	// 攻撃を確認したら無敵
	void Hit(const DX::StepTimer& timer);
	//	当たり判定を更新する
	void UpdateColision();
	//	エラーを確認する
	void ErrorCheck();
	// 生きているか？	
	void IsAlive();
};