//
//		File Name ： Sord.h
//		Production： 2023/6/19
//		Author　　： 石田 恭一	
//	
#pragma once
#include "../Object.h"

class Player;

class Sord : public Object
{
	//	アクセサ
public:

	// 武器のコライダー取得
	inline Collision::Shape::Capsule GetWeponCapsule() const { return m_sordCapusel; }
	//	攻撃中
	inline bool IsAttack()							   const { return m_isAttack; }
	//	攻撃クールタイムの取得
	inline float GetAttackCoolTime()				   const { return m_attackCoolTime; }
	//	振る速度の上がる
	void UpSwingSpeed();

	//	定数
public:

	//	剣の落ちる速度
	static const DirectX::SimpleMath::Vector3 SORD_FALL_SPEED;
	//	剣が転がる向き
	static const DirectX::SimpleMath::Vector3 SORD_ROLL_DIRECTION;
	//	線分の始め
	static const DirectX::SimpleMath::Vector3 SEGMENT_LENGTH_START;
	//	線分の終わり
	static const DirectX::SimpleMath::Vector3 SEGMENT_LENGTH_END;
	//	剣のオフセット位置
	static const DirectX::SimpleMath::Vector3 SORD_OFFSET_POSITION;
	//	オフセット角度
	static const float						  OFFSET_ANGLE;
	//	武器が攻撃をする時の角度
	static const float						  SWING_ANGLE;
	//	振る速度
	static const float						  SWING_SPEED;
	//	レベルアップ時の上がる速度
	static const float						  SWING_SPEED_UP_VALUE;
	//	振り向く速度
	static const float						  TURN_SPEED;
	//	球の半径
	static const float						  SPHERE_RADIUS;
	//	攻撃の時間					  
	static const float						  ATTACK_TIME;
	//	攻撃後の時間					  
	static const float						  ATTACK_AFTER_TIME;
	//	攻撃後のクールタイム
	static const float						  ATTACK_COOL_TIME;
	//	剣の地面の位置
	static const float						  GROUND_SORD_POSITION;
	//	剣を振り終えて次に振れるまでの時間				  
	static const float						  SWING_COOLTIME;
	//	剣を振り二回目を振れる可能時間				  
	static const float						  SWING_SECOND_CHANCE;

	//	変数
private:

	//	剣のモデル
	DirectX::Model* m_sordModel;
	//	回転角
	DirectX::SimpleMath::Quaternion m_slashRotate;
	//	回転のオフセット
	DirectX::SimpleMath::Quaternion m_offsetRotate;
	//	マトリックス
	DirectX::SimpleMath::Matrix		m_sordMatrix;
	//	親
	Player*							m_parent;
	//	攻撃の角度
	float							m_slashAngle;
	//	目標値
	float							m_objective;
	//	攻撃のクールタイム
	float							m_attackTime;
	//	攻撃後のクールタイム
	float							m_attackCoolTime;
	//	攻撃後のクールタイムを短くする
	float							m_shortAttackTime;
	//	攻撃フラグ
	bool							m_isAttack;
	//	攻撃後のクールタイム中か
	bool							m_isAttackCoolTime;
	//	二回目の攻撃
	bool							m_secondAttack;
	//	剣のカプセルの当たり判定
	Collision::Shape::Capsule		m_sordCapusel;

	//	関数
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parent">親</param>
	Sord(Player* parent);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Sord();

	/// <summary>
	///	初期化処理
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
	///	終了処理
	/// </summary>
	void Finalize() override;

	/// <summary>
	/// デバイス依存のリソースの作成
	/// </summary>
	void CreateDeviceDependentResources();

	/// <summary>
	/// 剣の死亡時のアニメーション
	/// </summary>
	void SordDeathAniamtion();

	//	埋め込み関数
private:

	//	 攻撃
	void Attack(const DX::StepTimer& timer);
	//	攻撃させたものを移動
	void AttackLerp();
	//	当たり判定を更新
	void UpdateColison();
	//	剣の回転角を更新する
	void UpdateSordLerp();
	//	 攻撃を振る最初の条件を満たしているか
	bool ShouldSwingStartFlag();
	//	 攻撃を振る二回目の条件を満たしているか
	bool ShouldSwingSecondFlag();
};