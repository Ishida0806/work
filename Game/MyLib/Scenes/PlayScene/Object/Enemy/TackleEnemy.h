//
//		File Name ： TackleEnemy.h
//		Production： 2023/11/12
//		Author　　： 石田 恭一	
//	
#pragma once

#include "../Object.h"
#include "Enemy.h"

class TackleEnemy : public Enemy
{
	//	アクセサ
public:

	/// <summary>
	/// アクション状態が行えるか確認する
	/// </summary>
	/// <returns></returns>
	bool IsRedyAbility() override { return m_isTackle; }

	//	定数
public:

	//	歩く速度
	static const float									 	 ENEMY_SPEED;
	//	振り向く速さ
	static const float										 LOOK_BACK_SPEED;
	//	突撃速度
	static const float										 ENEMY_TACLE_SPEED;
	//	突撃後止まる位置
	static const float										 TACKLE_STOP_DISTANCE;
	//	敵の弾数
	static const int										 ENEMY_BULLETS_NUM;
	//	とどまる時間
	static const float										 ALIVE_TIME;
	//	突撃可能までの時間
	static const float										 TACKLE_ENABLED_TIME;
	//	影用の引く値
	static const float										 SHADOW_ARGUMENT;
	//	突撃距離
	static const float										 TACKLE_DISTANCE;
	//	スタンタイム
	static const float										 SWOON_TIME;
	//	タックルの経験値
	static const int										 TACKLE_EXP;
	//	初期設定の力
	static const int										 FIRST_POWER;
	//	初期設定の体力
	static const int										 FIRST_HEALTH;
	//	自身の大きさの引く値
	static const DirectX::SimpleMath::Vector3				 SCALE_ARGUMENT;
	//	通常の大きさ
	static const DirectX::SimpleMath::Vector3				 DEFAULT_SCALE;
	//	当たり判定
	static const Collision::Shape::Sphere					 SPERE_COLLISION;
	//	球状の索敵範囲
	static const Collision::Shape::Sphere					 SEARCH_COLLISION;
	//	球状の発射可能範囲
	static const Collision::Shape::Sphere					 TACKLE_COLLISION;
	//	突撃線の黄色
	static const DirectX::SimpleMath::Color					 TACKLE_PREDICTION_YELLOW;
	//	突撃線の赤色
	static const DirectX::SimpleMath::Color					 TACKLE_PREDICTION_RED;

	//	構造体
public:
	

	//	タックルの挙動を示す常態
	enum class TackleState
	{
		// タックルが開始されていない状態
		IDLE,        
		// タックルが進行中の状態
		ACTIVE,       
		// タックルが終了した状態
		FINISHED,   

		//	スタン
		SWOON
	};

	//	変数
private:

	//	敵モデル
	DirectX::Model* m_enemyModel;
	//	スタン状態の回転
	DirectX::SimpleMath::Quaternion				 m_swoonRotate;
	//	目標の回転角
	DirectX::SimpleMath::Quaternion				 m_objectiveRotate;
	//	プリミティブバッチ四角
	std::unique_ptr<DirectX::GeometricPrimitive> m_primitiveBox;
	//	突撃ターゲット座標
	DirectX::SimpleMath::Vector3				 m_objectivePosition;
	//	突撃の時の大きさ
	DirectX::SimpleMath::Vector3				 m_tackleScale;
	//	レベル
	int											 m_level;
	//	突進中
	bool										 m_isTackle;
	//	突進クールタイム
	bool										 m_tackleCoolTime;
	//	突撃を行う
	bool										 m_tackleExcute;
	//	影の大きさ
	float										 m_shadowScale;
	//	突撃までのインターバル
	float										 m_tackleInterval;
	//	突撃後のその場にとどまる時間
	float										 m_tackledStayTime;
	//	突撃中の時間
	float										 m_tackleAssaultTime;
	//	スタン状態
	float										 m_swoonTime;
	//	突撃の状態
	TackleState									 m_tackleState;
	//	識別子
	ObjectType									 m_objType;

	//	関数
public:
	//	コンストラクタ
	TackleEnemy(const DirectX::SimpleMath::Vector3& position, int helath, const int& power, int level, ObjectType obj);
	//	デストラクタ
	~TackleEnemy();
	//	初期化
	void Initialize() override;
	//	更新
	void Update(const DX::StepTimer& timer) override;
	//	描画
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj) override;
	//	終了処理
	void Finalize() override;

	/// <summary>
	/// プレイヤーヒット
	/// </summary>
	/// <param name="direction"></param>
	/// <param name="nockBack"></param>
	void HitPlayer(const DirectX::SimpleMath::Vector3& direction, const float& nockBack) override;

	/// <summary>
	/// スタン状態にする
	/// </summary>
	void SwoonMode() override;

	//	埋め込み関数
private:

	//	生存時間
	void IsAlive();
	//	ヘイトモード
	void HateMode(const DX::StepTimer& timer) ;
	//	タックルする前の初期化
	void PreTackleInitialize();
	//	タックルを止める条件
	bool ShouldStopTackle();
	//	スタン状態
	bool Swoon(const DX::StepTimer& timer);
	//	予測線
	void ComingTackle(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj);
	//	タックルの開始位置
	DirectX::SimpleMath::Vector3 StartTackle(const DirectX::SimpleMath::Vector3& position, const float& speed);
};