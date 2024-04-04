//
//		File Name ： TutorialSystem.h
//		Production： 2024/4/04
//		Author　　： 石田 恭一	
//	
#pragma once
#include "Game/MyLib/GameDatas/FiniteStateMachine.h"

class EnemyManager;
class PlayScene;

class TutorialSystem
{
	//	列挙型
public:

	//	チュートリアルシステム
	enum class TutorialState
	{
		MovingMethod		= 0,
		WeponMethod			= 1,
		KillEnemyMethod		= 2,
		FinishMethod		= 3,

		OverID				= 4
	};

	//	アクセサ
public:

	//	敵のマネージャーを取得する
	inline EnemyManager* GetEnemyManager()	const					{ return m_enemyManager; }
	//	プレイシーンを取得する
	inline PlayScene*	GetPlayScene ()		const					{ return m_playScene; }

	//	チュートリアル案内画像の設定
	inline void SetGuideTexture(ID3D11ShaderResourceView* texture);

	//	エイリアス宣言
public:

	using TUTORIALSTATE  = FiniteStateMachine<TutorialSystem, TutorialSystem::TutorialState>;
	using ITUTORIALSTATE = TUTORIALSTATE::IState;

	//	変数
private:

	//	有限ステートマシーン
	std::unique_ptr<TUTORIALSTATE>	m_fsm;
	//	画像
	ID3D11ShaderResourceView*		m_guideTutorialTexture;
	//	敵のマネージャー
	EnemyManager*					m_enemyManager;
	//	プレイシーン
	PlayScene*						m_playScene;
	

	//	関数
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="playScene">プレイシーン</param>
	/// <param name="enemyManager">敵マネージャ</param>
	TutorialSystem(PlayScene* playScene , EnemyManager* enemyManager);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~TutorialSystem();

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
	void Render();

	/// <summary>
	/// 終了処理
	/// </summary>
	void Finalize();
};