//
//		File Name ： EnemyManager.h
//		Production： 2023/11/12
//		Author　　： 石田 恭一	
//	
#pragma once

class Object;
class Player;
class PlayScene;
class PlaySceneWave;
class PlayInfo;
class Enemy;

class EnemyManager
{
	//	列挙型
public:

	// 敵タイプ
	enum class EnemyType
	{
		NormalEnemy = 0,
		TackleEnemy = 1,
		BossEnemy = 2,

		OverID
	};
	//	アクセサ
public:

	//	ボスを取得する
	inline std::vector<std::shared_ptr<Enemy>>&   GetEnemy()		noexcept { return m_enemys; }

	/// <summary>
	/// 敵を作成する
	/// </summary>
	/// <param name="enemy">敵のタイプ</param>
	/// <param name="health">体力</param>
	/// <param name="power">力</param>
	/// <param name="level">レベル</param>
	/// <param name="position">座標</param>
	void CreateEnemy
	(
		const EnemyType& enemy,
		const int& health,
		const int& power, 
		const int& level,
		const DirectX::SimpleMath::Vector3& position = DirectX::SimpleMath::Vector3::Zero
	);

	//	定数
public:

	//	通常の敵の体力
	static const int						  NORMAL_ENEMY_HELATH;
	//	突撃敵の体力
	static const int						  TACLE_ENEMY_HELATH;
	//	ボスの体力
	static const int						  BOSS_ENEMY_HELATH;
	//	ボスの生成の限界数			 
	static const int						  BOSS_ENEMY_RESTRICTION;
	//	普通の敵の生成限界数
	static const int						  NORMAL_ENEMY_RESTRICTION;
	//	突撃の敵の生成限界数
	static const int						  TACLE_ENEMY_RESTRICTION;
	//	ボスの発生速度
	static const float						  BOSS_ENEMY_POP_SPEED;
	//	通常の敵の発生速度
	static const float						  NORMAL_ENEMY_POP_SPEED;
	//	突撃の敵の発生速度
	static const float						  TACLE_ENEMY_POP_SPEED;
	//	追尾モードの限界数
	static const int						  HATE_ENEMY_NUM;
	//	難易度によって増える数
	static const int						  INCREASE_WORLD_LEVEL;
	//	敵の力
	static const int						  ENEMY_POWER;



	//	構造体
private:

	//	敵の数情報
	struct EnemyInformation
	{
		//	存在数
		int		existence;
		//	生成時間
		float	popTime;

		/// <summary>
		/// サイズを「1」増やす
		/// </summary>
		void IncrementSize()
		{
			existence++;
		}

		/// <summary>
		/// 大きさ
		/// </summary>
		/// <returns></returns>
		int size()
		{
			return existence;
		}

		/// <summary>
		/// 出現カウントをリセットする
		/// </summary>
		void ResetCount()
		{
			existence = 0;
		}

		/// <summary>
		/// コンストラクタ
		/// </summary>
		EnemyInformation()
			:existence(0),
			popTime(0.0f)
		{

		}
	};	


	//	変数
private:

	//	プレイシーン
	PlayScene*										 m_playScene;
	//	プレイ情報
	PlayInfo*										 m_playInfo;
	//	プレイシーンのウェーブ
	PlaySceneWave*									 m_playSceneWave;
	//	プレイヤー
	Player*											 m_player;
	//	通常敵
	EnemyInformation								 m_normalEnemyInformation;
	//	突撃敵
	EnemyInformation								 m_tackleEnemyInformation;
	//	ボス
	EnemyInformation								 m_bossEnemyInformation;
	//	ボス敵
	std::vector<std::shared_ptr<Enemy>>				 m_enemys;
	//	追尾状態の限界数
	int												 m_hateReaction;
	//	通常敵の限界生成数
	int												 m_normalReaction;
	//	突撃敵の限界生成数
	int												 m_tackleReaction;

	//	関数
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="playScene">プレイシーン</param>
	/// <param name="player">プレイヤー</param>
	/// <param name="playSceneWave">プレイシーンのウェーブ</param>
	EnemyManager(PlayScene* playScene, Player* player , PlaySceneWave* playSceneWave);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyManager();

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


	/// <summary>
	/// 終了処理
	/// </summary>
	void Finalize();


private:

	/// <summary>
	/// ボスたちを更新
	/// </summary>
	/// <param name="timer">タイマー</param>
	void UpdateBosses(const DX::StepTimer& timer);

	/// <summary>
	/// 通常敵たちを更新
	/// </summary>
	/// <param name="timer">タイマー<</param
	void UpdateNormalEnemies(const DX::StepTimer& timer);

	/// <summary>
	/// 突撃敵たちを更新
	/// </summary>
	/// <param name="timer">タイマー<</param>
	void UpdateTackleEnemies(const DX::StepTimer& timer);	

	/// <summary>
	/// 敵が死んだら削除
	/// </summary>
	void DeadObject();	

	/// <summary>
	/// 追尾モードの敵の数を探す
	/// </summary>
	void FindHateEnemy();	

	/// <summary>
	///	スポーンする敵を選ぶ
	/// </summary>
	void SelectSpawnEnemy();
};