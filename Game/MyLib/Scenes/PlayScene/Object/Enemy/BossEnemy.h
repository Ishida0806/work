//
//		File Name ： BossEnemy.h
//		Production： 2023/11/12
//		Author　　： 石田 恭一	
//	
#pragma once
#include "Enemy.h"
#include "../Bullet/Bullet.h"

class BossEnemy : public Enemy
{//	定数
public:
	//	所持する弾数
	static const int										 BOSS_BULLETS_NUM;
	//	移動速度
	static const float										 BOSS_SPEED;
	//	回る速さ
	static const float										 LERP_SPEED;
	//	壁のある位置
	static const float										 WALL_PLACE;
	//	発射のインターバル
	static const float										 SHOT_TIME;
	//	ボスの経験値
	static const int										 BOSS_EXP;
	//	影の大きさ
	static const float										 SHADOW_SCALE;
	//	死亡時の自身の大きさが引かれていく大きさ
	static const float									     SCALE_ARGUMENT;
	//	死亡時の影の大きさが引かれていく大きさ
	static const float										 SHADOW_ARGUMENT;
	//	当たり判定
	static const Collision::Shape::Sphere					 SPERE_COLLISION;
	//	球状の索敵範囲
	static const Collision::Shape::Sphere					 SEARCH_COLLISION;
	//	球状の発射可能範囲
	static const Collision::Shape::Sphere					 SHOT_COLLISION;

private:
	//	敵モデル
	DirectX::Model*								 m_bossModel;
	//	発射フラグ
	bool										 m_isShot;
	//	索敵状態に入ったか？
	bool										 m_isSeartch;
	//	レベル
	int											 m_level;
	//	大きさ
	float										 m_scale;
	//	発射までのインターバル
	float										 m_shotInterval;
	//	影の大きさ
	float										 m_shadowScale;
	//	ランダムに入れ替わるまでの時間
	float										 m_randomTime;
	//	敵の向き
	Direction									 m_direction;
	//	識別子
	ObjectType 									 m_objType;

	//	関数
public:
	//	コンストラクタ
	BossEnemy(const DirectX::SimpleMath::Vector3& position, const int& helath, const int& power, const int& level, ObjectType obj);
	//	デストラクタ
	~BossEnemy();

	void Initialize() override;
	void Update(const DX::StepTimer& timer) override;
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj) override;
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
	//	生きているか
	void IsAlive();
	//	追尾モード
	void HateMode(const DX::StepTimer& timer);
};