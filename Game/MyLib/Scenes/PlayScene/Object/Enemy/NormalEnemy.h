//
//		File Name ： NormalEnemy.h
//		Production： 2023/11/12
//		Author　　： 石田 恭一	
//	
#pragma once
#include "../Object.h"
#include "Enemy.h"
#include "EnemyLeg.h"

class NormalEnemy : public Enemy
{//	定数
public:
	//	各速さ
	static const float										 ENEMY_SPEED;
	//	振り向く速度
	static const float										 LERP_SPEED;
	//	壁の位置
	static const float										 WALL_PLACE;
	//	敵の弾数
	static const int									 	 ENEMY_BULLETS_NUM;
	//	発射間隔
	static const float										 SHOT_TIME;
	//	乱数時間
	static const float										 RANDOM_TIME;
	//	初期設定の力
	static const int										 FIRST_POWER;
	//	初期設定の体力
	static const int										 FIRST_HEALTH;
	//	ノーマルの経験値
	static const int										 NORMAL_EXP;
	//	影用の引く値
	static const float										 SHADOW_ARGUMENT;
	//	通常の大きさ
	static const DirectX::SimpleMath::Vector3				 DEFAULT_SCALE;
	//	自身の大きさの引く値
	static const DirectX::SimpleMath::Vector3				 SCALE_ARGUMENT;
	//	当たり判定
	static const Collision::Shape::Sphere					 SPERE_COLLISION;
	//	球状の索敵範囲
	static const Collision::Shape::Sphere					 SEARCH_COLLISION;
	//	球状の発射可能範囲
	static const Collision::Shape::Sphere					 SHOT_COLLISION;

	//	変数
private:
	//	敵モデル
	DirectX::Model*								 m_enemyModel;
	//	敵の脚
	std::unique_ptr<EnemyLeg>					 m_enemyLeg;
	//	発射時の大きさ
	DirectX::SimpleMath::Vector3				 m_shotAnimationScale;
	//	発射後のアニメーション
	DirectX::SimpleMath::Vector3				 m_shotAnimationAfterScale;
	//	発射圏内
	bool										 m_isShot;
	//	発射圏内に入った
	bool										 m_inShot;
	//	レベル
	int											 m_level;
	//	影の大きさ
	float										 m_shadowScale;
	//	発射までのインターバル
	float										 m_shotInterval;
	//	次に発射するまでの時間
	float										 m_shotCoolTime;
	//	敵の向き
	Direction									 m_direction;
	//	識別子
	ObjectType									 m_objType;

	//	関数
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="position">座標</param>
	/// <param name="helath">体力</param>
	/// <param name="power">力</param>
	/// <param name="level">レベル</param>
	/// <param name="obj">オブジェクトのタイプ</param>
	NormalEnemy(const DirectX::SimpleMath::Vector3& position, const int& helath, const int& power, const int& level, ObjectType	obj);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~NormalEnemy();

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

	//	アクセサ
public:	

	/// <summary>
	/// アクション状態が行えるか確認する
	/// </summary>
	/// <returns></returns>
	bool IsRedyAbility() override { return m_isShot; }

	/// <summary>
	/// 特殊効果を設定する
	/// </summary>
	/// <param name="flag"></param>
	void SetAbility(const bool& flag) override;

	//	埋め込み関数
private:
	//	生存中か
	void IsAlive();
	//	追尾モード
	void HateMode(const DX::StepTimer& timer);
};