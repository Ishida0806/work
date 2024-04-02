//
//		File Name ： BulletManager.h
//		Production： 2023/7/02
//		Author　　： 石田 恭一
//
#pragma once

class Bullet;
class Enemy;

class BulletManager
{
	//	アクセサ
public:

	//	弾を取得する
	inline std::vector<std::unique_ptr<Bullet>>& GetBullet()		noexcept { return m_bullets; };

	//	定数
public:

	//	敵の弾の力					 
	static const int						  ENEMY_BULLET_POWER;
	//	ボスの弾の力
	static const int						  BOSS_BULLET_POWER;
	//	ボスの弾の大きさ
	static const float						  BOSS_BULLET_SCLAE;
	//	敵の弾の大きさ
	static const float						  ENEMY_BULLET_SCLAE;

	//	変数
private:

	//	ボスのポインター
	std::vector<std::shared_ptr<Enemy>>&	   m_enemys;
	//	砲弾配列
	std::vector<std::unique_ptr<Bullet>>	   m_bullets;

	//	変数
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="enemy">敵たち</param>
	BulletManager(std::vector<std::shared_ptr<Enemy>>& enemy);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~BulletManager();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="timer">タイマー</param>
	void Update(const DX::StepTimer& timer);

	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="view">ビュー</param>
	/// <param name="proj">プロジェクション</param>
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj);


	//	プライベート関数
private:

	/// <summary>
	/// 通常の弾を更新更新する
	/// </summary>
	/// <param name="timer">タイマー</param>
	void UpdateNormalBullet(const DX::StepTimer& timer);

	/// <summary>
	/// 敵の弾たちを発射する
	/// </summary>
	void ShotEnemyBullets();

	/// <summary>
	/// ボスの弾たちを発射する
	/// </summary>
	void ShotBossBullets();
	
	
};