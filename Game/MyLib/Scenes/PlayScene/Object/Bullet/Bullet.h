//
//		File Name ： Bullet.h
//		Production： 2023/7/02
//		Author　　： 石田 恭一
//
#pragma once
#include "../Object.h"
#include "BulletFactroy.h"

class OwnerID;

class Bullet : public Object
{
	//	定数
public:

	//	角速度
	static const float						  SPEED;
	static const DirectX::SimpleMath::Vector3 ENEMY_SPEED;
	static const DirectX::SimpleMath::Vector3 BOSS_SPEED;
	static const DirectX::SimpleMath::Vector3 REF_SPEED;
	//	当たり判定の大きさ
	static const float BULLET_RADIUS;
	static const float BOSS_BULLET_RADIUS;

private:

	//	プリミティブバッチ
	std::unique_ptr<DirectX::GeometricPrimitive> m_primitive;
	//	速度
	DirectX::SimpleMath::Vector3				 m_velocity;
	//	色
	DirectX::SimpleMath::Color					 m_color;
	//	大きさ
	float										 m_scale;
	//	使用状態
	bool										 m_used;
	//	反射中
	bool										 m_isRefrect;
	//	所有者
	int											 m_ownerID;
	//	力
	int											 m_power;
	//	反射カウント
	int											 m_refCount;
	//	当たり判定
	Collision::Shape::Sphere					 m_bulletSphere;

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="ownerID">オーナー</param>
	/// <param name="position">座標</param>
	/// <param name="rotate">回転角</param>
	/// <param name="color">色</param>
	/// <param name="power">力</param>
	/// <param name="scale">大きさ</param>
	/// <param name="used">使用状態</param>
	Bullet(
		BulletFactory::OwnerID  ownerID,
		const DirectX::SimpleMath::Vector3& position, 
		const DirectX::SimpleMath::Quaternion& rotate,
		const DirectX::SimpleMath::Color& color,
		int power,
		float scale,
		bool used
		);

	~Bullet();

	//	関数
public:

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

	//	使用状態を取得する
	inline bool IsUsed()							  const	 { return m_used; }
	//	所有者を取得
	inline int GetOwner()							  const	 { return m_ownerID; }
	//	力を取得する
	inline int GetPower()							  const	 { return m_power; }
	//	当たり判定を取得するを
	inline Collision::Shape::Sphere GetSphere()		  const	 { return m_bulletSphere; }
	//	反射状態を取得
	inline bool	IsReslect()							  const	 { return m_isRefrect; }
	//	使用状態を設定する
	void SetUsed(bool used);
	//	反射
	void Refrection(const DirectX::SimpleMath::Vector3& position);

	//	埋め込み関数
private:
	void PreInitialize();
	void CreateDeviceDependentResources();

	DirectX::SimpleMath::Vector3 ShotBullet();
};

