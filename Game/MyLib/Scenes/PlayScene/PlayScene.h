//
//		File Name ： PlayScene.h
//		Production： 2023/6/19
//		Author　　： 石田 恭一	
//
#pragma once

//	インクールドファイル　	-----------------------------------------
#include "Game/MyLib/Scenes/IScene.h"

#include "Game/Game.h"
#include "Common/Floor_Model.h"
#include "Game/MyLib/Scenes/PlayScene/Object/FallingCherryBlossoms/FallingCherryBlossoms.h"
#include "Game/MyLib/Scenes/PlayScene/TutorialSystem/TutorialSystem.h"
#include "Game/MyLib/Scenes/PlayScene/Object/Bullet/BulletManager.h"
#include "Game/MyLib/Scenes/PlayScene/UI/PlayerExperiencePointUI.h"
#include "Game/MyLib/Scenes/PlayScene/Object/Enemy/EnemyManager.h"
#include "Game/MyLib/Scenes/PlayScene/Object/Enemy/EnemyFactory.h"
#include "Game/MyLib/Scenes/PlayScene/Object/Wall/WallFactory.h"
#include "Game/MyLib/Scenes/PlayScene/Object/Item/ItemManager.h"
#include "Game/MyLib/Scenes/PlayScene/Object/SkyDoem/SkyDome.h"
#include "Game/MyLib/Scenes/PlayScene/Wave/PlaySceneWave.h"
#include "Game/MyLib/Scenes/PlayScene/Object/Wall/Wall.h"
#include "Game/MyLib/Scenes/PlayScene/UI/PlayerHPBar.h"
#include "Game/MyLib/Scenes/PlayScene/UI/StartSignal.h"
#include "Game/MyLib/Scenes/PlayScene/Object/Player.h"
#include "Game/MyLib/Scenes/PlayScene/UI/PlayeScore.h"
#include "Game/MyLib/Scenes/PlayScene/UI/LevelCard.h"
#include "Game/MyLib/Scenes/PlayScene/UI/BatMeter.h"
#include "Game/MyLib/Scenes/PlayScene/UI/PlayerUI.h"
#include "Game/MyLib/Scenes/PlayScene/UI/MiniMap.h"
#include "Game/MyLib/GameDatas/BulletHitParticle.h"
#include "Game/MyLib/GameDatas/ColisionObjects.h"
#include "Game/MyLib/GameDatas/PlayPostEffect.h"
#include "Game/MyLib/GameDatas/HitRenderer.h"
#include "Game/MyLib/GameDatas/PlayInfo.h"
#include "Game/MyLib/GameDatas/Number.h"
#include "Game/MyLib/GameDatas/Pause.h"
#include "Game/MyLib/Camera/Camera.h"

//	前方宣言	-----------------------------------------
class Game;
class Player;
class NormalEnemy;
class TackleEnemy;
class BossEnemy;
class Bullet;
class Camera;
class SkyDome;
class Wall;


class PlayScene : public IScene
{
	//	アクセサ
public:

	/// <summary>
	/// レベルを取得する
	/// </summary>
	/// <returns>レベル</returns>
	inline int GetWordLevel()	const { return m_worldLevel; }

	/// <summary>
	/// 初回起動か？
	/// </summary>
	/// <returns>初回起動か</returns>
	inline bool IsFirstOpen()	const { return m_isFirstOpen; }

	//	定数
public:
	//	上側の壁情報
	static const DirectX::SimpleMath::Vector3 TOP_WALL_SCALE;
	static const DirectX::SimpleMath::Vector3 TOP_WALL_POSITION;
	//	右側の壁情報
	static const DirectX::SimpleMath::Vector3 RIGHT_WALL_SCALE;
	static const DirectX::SimpleMath::Vector3 RIGHT_WALL_POSITION;
	//	下側の壁情報
	static const DirectX::SimpleMath::Vector3 UNDER_WALL_SCALE;
	static const DirectX::SimpleMath::Vector3 UNDER_WALL_POSITION;
	//	左側の壁情報
	static const DirectX::SimpleMath::Vector3 LEFT_WALL_SCALE;
	static const DirectX::SimpleMath::Vector3 LEFT_WALL_POSITION;
	//	カメラの補正座標
	static const DirectX::SimpleMath::Vector3 CAMERA_OFFSET_POSITION;
	//	勝った際の文字列
	static const std::string				  WIN_STRING;
	//	負けた際の文字列
	static const std::string				  LOSE_STRING;
	//	壁の大きさ
	static const int						  WALL_SCLAE;
	//	ヒット時のエフェクトの生成限界数
	static const int						  HIT_RENDER_RESTRICTION;
	//	花吹雪の生成数
	static const int						  FALLING_CHERRY_BLOSSOMS_GENERATED;
	//	エフェクトのサイズ
	static const float						  EFFECT_SIZE;
	//	突撃敵のリアクション
	static const DirectX::SimpleMath::Vector3 TACLE_ENEMY_REACTION;
	//	その他の敵のリアクション
	static const float						  OTHER_ENEMY_REACTION;
	//	フェードタイム
	static const float						  FADE_TIME;
	//	終了時間
	static const float						  FINISHED_TIME;

	//	変数
private:
	//	ゲーム
	Game*												m_game;
	//	スクリーンリソース
	MyLib::ScreenResources*								m_screen;
	//	ポーズ
	std::unique_ptr<Pause>								m_pause;
	//	カメラ
	std::unique_ptr<Camera>								m_camera;	
	//	床モデル	
	std::unique_ptr<Floor_Model>						m_floor_Model;
	//	プレイヤー
	std::unique_ptr<Player>								m_player;
	//	プレイヤーのUI
	std::unique_ptr<PlayerUI>							m_playerUI;
	//	ゲームスタートの合図
	std::unique_ptr<StartSignal>						m_startSignal;
	//	パーティかるエフェクト
	std::vector<std::unique_ptr<BulletHitParticle>>		m_hitBulletPatricles;
	//	プレイヤーの体力バーUI
	std::unique_ptr<PlayerHPBar>						m_playerBarUI;
	//	プレイスコア
	std::unique_ptr<PlayeScore>							m_playScore;
	//	ミニマップ
	std::unique_ptr<MiniMap>							m_miniMap;
	//	壁
	std::vector<std::unique_ptr<Wall>>					m_walls;
	//	ヒットレンダー
	std::vector<std::unique_ptr<HitRenderer>>			m_hitRenders;
	//	弾ヒット時のエフェクト
	std::vector<std::unique_ptr<HitRenderer>>			m_hitBulletRenders;
	//	花吹雪
	std::vector<std::unique_ptr<FallingCherryBlossoms>>	m_fallingCherryBlossoms;
	//	スカイドーム
	std::unique_ptr<SkyDome>							m_skyDome;
	//	敵のマネージャー
	std::unique_ptr<EnemyManager>						m_enemyManager;
	//	アイテムのマネージャー
	std::unique_ptr<ItemManager>						m_itemManager;
	//	弾のマネージャ
	std::unique_ptr<BulletManager>						m_bulletManager;
	//	当たり判定を行う
	std::unique_ptr<ColisionObjects>					m_colisionObjects;
	//	経験値のバー
	std::unique_ptr<PlayerExperiencePointUI>			m_expBar;
	//	レベルアップ時のカード
	std::unique_ptr<LevelCard>							m_levelCard;
	//	プレイシーンで使うポストエフェクト	
	std::unique_ptr<PlayPostEffect>						m_postEffect;
	//	プレイシーンのウェーブ
	std::unique_ptr<PlaySceneWave>						m_playSceneWave;
	//	チュートリアル
	std::unique_ptr<TutorialSystem>						m_tutorialSystem;
	//	ゲーム結果
	std::string											m_gameResultString;
	//	フェード中の時間
	float												m_fadeTime;
	//	終了時間
	float												m_finishedTime;
	//	敵全体のレベル
	int													m_worldLevel;
	//	開始のフェード中か？
	bool												m_IsFade;
	//	終了条件
	bool												m_isFinish;
	//	フェードアウトのタスク
	bool												m_isFadeOutTask;
	//	初回起動か
	bool												m_isFirstOpen;

public:
	//	コンストラクタ
	PlayScene(Game* game, MyLib::ScreenResources* screen, int stagelevel = 0);
	//	デストラクタ
	~PlayScene();

	//	初期化処理
	void Initialize() override;
	//	更新処理
	void Update(const DX::StepTimer& timer) override;
	//	描画処理
	void Render() override;
	//	終了処理	
	void Finalize() override;
	//	エフェクトを描画するし大きさを変える
	void HitRnder(const DirectX::SimpleMath::Vector3& position);
	//	エフェクトを描画するし大きさを変える
	void HitRnder(const DirectX::SimpleMath::Vector3& position, const Enemy* enemy);
	//	エフェクトを判定描画する
	void HitBulletRnder(const DirectX::SimpleMath::Vector3& position);
	//  タイトルシーンに切り変える
	void ChangeSceneTitle();
	//	マウスカーソルを見せるか
	void ShowMouse(const bool& isShow);
	//	チュートリアル終了
	void FinishTutorial();


	//	埋め込み関数
private:
	//	デバイス依存のリソースの初期化
	void CreateDeviceDependentResources();
	//	ゲームの終了条件を満たしたか確認する
	bool IsFinished(const DX::StepTimer& timer);
	//	カメラを更新する
	void UpdateCamera(const DX::StepTimer& timer);
	//	ミニマップを更新する
	void UpdateMiniMap(const DX::StepTimer& timer);
	//	プレイヤーは生きてるか
	void IsAlivePlayer();
	//	UIを描画する
	void UIRender(); 
	//	フェード中か
	bool NowFade(const DX::StepTimer& timer);
	//	ポーズ中か
	bool NowPause();
};
