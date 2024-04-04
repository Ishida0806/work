//
//		File Name ： PlayScene.cpp
//		Production： 2023/6/19
//		Author　　： 石田 恭一	
// 
//		プレイシーン
//	
#include "pch.h"

////////////////////////Scene//////////////////////////////////
#include "Game/MyLib/Scenes/TitleScene/TitleScene.h"
#include "Game/MyLib/Scenes/PlayScene/PlayScene.h"
#include "Game/MyLib/Scenes/StageSelect/StageSelectScene.h"
#include "Game/MyLib/Scenes/ResultScene/ResultScene.h"
////////////////////////////////////////////////////////////////

#include "Game/MyLib/GameDatas/EdditPlayData.h"

//	勝った際の文字列
const std::string				   PlayScene::WIN_STRING			 = "win";
//	負けた際の文字列
const std::string				   PlayScene::LOSE_STRING			 = "lose";
//	右側の壁のあたり判定の大きさ・壁の位置
const DirectX::SimpleMath::Vector3 PlayScene::RIGHT_WALL_SCALE		 = DirectX::SimpleMath::Vector3(1.5f, 5.5f, 26.0f);
const DirectX::SimpleMath::Vector3 PlayScene::RIGHT_WALL_POSITION 	 = DirectX::SimpleMath::Vector3(27.5f, 0.0f, 0.0f);
//	下側の壁のあたり判定の大きさ・壁の位置
const DirectX::SimpleMath::Vector3 PlayScene::UNDER_WALL_SCALE		 = DirectX::SimpleMath::Vector3(26.0f, 5.0f, 1.5f);
const DirectX::SimpleMath::Vector3 PlayScene::UNDER_WALL_POSITION	 = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 27.5f);
//	左側の壁のあたり判定の大きさ・壁の位置
const DirectX::SimpleMath::Vector3 PlayScene::LEFT_WALL_SCALE		 = DirectX::SimpleMath::Vector3(1.5f, 5.0f, 26.0f);
const DirectX::SimpleMath::Vector3 PlayScene::LEFT_WALL_POSITION	 = DirectX::SimpleMath::Vector3(-27.5f, 0.0f, 0.0f);
//	上側の壁のあたり判定の大きさ・壁の位置
const DirectX::SimpleMath::Vector3 PlayScene::TOP_WALL_SCALE		 = DirectX::SimpleMath::Vector3(26.0f, 5.0f, 1.5f);
const DirectX::SimpleMath::Vector3 PlayScene::TOP_WALL_POSITION		 = DirectX::SimpleMath::Vector3(0.0f, 0.0f, -27.5f);
//	カメラの補正座標
const DirectX::SimpleMath::Vector3 PlayScene::CAMERA_OFFSET_POSITION = DirectX::SimpleMath::Vector3(0.0f, 20.0f, 10.0f);
//	突撃敵のあたったさいのノックバック
const DirectX::SimpleMath::Vector3 PlayScene::TACLE_ENEMY_REACTION   = DirectX::SimpleMath::Vector3(2.4f, 12.5f, 5.4f);
//	当たったエフェクトの表示できる数
const int PlayScene::HIT_RENDER_RESTRICTION							 = 30;
//	花吹雪の生成数
const int PlayScene::FALLING_CHERRY_BLOSSOMS_GENERATED				 = 100;
//	壁の大きさ
const int PlayScene::WALL_SCLAE										 = 6;
//	エフェクトの画像の大きさ
const float PlayScene::EFFECT_SIZE									 = 2.0f;
//	その他の敵のリアクション
const float PlayScene::OTHER_ENEMY_REACTION							 = 1.4f;
//	フェードタイム
const float PlayScene::FADE_TIME									 = 5.4f;
//	終了時間
const float PlayScene::FINISHED_TIME								 = 2.8f;


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="game">ゲーム</param>
/// <param name="screen">スクリーンリソース</param>
PlayScene::PlayScene(Game* game, MyLib::ScreenResources* screen, int stagelevel)
	:
	m_game(game),
	m_screen(screen),
	m_worldLevel(stagelevel),
	m_isFinish(false),
	m_isFadeOutTask(false),
	m_isFirstOpen(false),
	m_IsFade(true),
	m_gameResultString(),
	m_fadeTime(0.0f),
	m_finishedTime(0.0f)
{

}

/// <summary>
/// デストラクタ
/// </summary>
PlayScene::~PlayScene()
{
	Finalize();
}

/// <summary>
/// 初期化
/// </summary>
void PlayScene::Initialize()
{
	CreateDeviceDependentResources();
}

/// <summary>
/// 更新
/// </summary>
/// <param name="timer">タイマー</param>
void PlayScene::Update(const DX::StepTimer& timer)
{
	//	ポーズ中か
	if (NowPause())	return;
	//	フェード中か
	if (NowFade(timer))	return;
	//	プレイヤーは生きてるか
	IsAlivePlayer();
	//	プレイヤーのアニメーション
	m_player->PlayerAnimation(timer);
	//	花の更新
	if (m_fallingCherryBlossoms.size() != 0) { for (const auto& flower : m_fallingCherryBlossoms)		flower->Update(timer); }
	//	ゲームが終了したか？
	if(IsFinished(timer))	return;
	//	カメラを更新する
	UpdateCamera(timer);
	//	ゲームが終了しているなら戻す
	if (m_isFinish)	return;
	//	レベルアップのカードの更新
	if (m_levelCard->Update(timer))	return;
	//	ポストエフェクトの更新
	m_postEffect->Update(timer);
	//	プレイヤーのアップデート
	m_player->Update(timer);
	//	プレイヤーのUI更新
	m_playerUI->Update(timer);
	//	プレイヤーの体力バーUI更新
	m_playerBarUI->SetHPState(m_playerUI->GetState());
	//	プレイヤーの体力バーUI更新
	m_playerBarUI->Update(timer);
	//	更新処理する
	m_playScore->Update(timer);
	//	経験値を更新する
	m_expBar->Update(timer);
	//	アニメーション中は処理を行わない
	if (m_player->IsAnimation())	return;
	//	敵のマネージャーを更新する
	m_enemyManager->Update(timer);
	//	アイテムのマネージャーを更新する
	m_itemManager->Update(timer);
	//	弾のマネージャーを更新する
	m_bulletManager->Update(timer);
	//	技能の判定の更新
	m_colisionObjects->UpdateAbility();
	//	当たり判定の更新
	m_colisionObjects->UpdateColision();
	//	ミニマップを更新する
	UpdateMiniMap(timer);
	//	チュートリアル中か？ && 	プレイシーンのウェーブの更新する
	if (m_isFirstOpen) { m_tutorialSystem->Update(timer); }	else { m_playSceneWave->Update(); }
	//	ヒットエフェクトを更新
	for (const auto& hitRender : m_hitRenders)				hitRender->Update();
	//	ヒットエフェクトを更新
	for (const auto& hitRender : m_hitBulletRenders)		hitRender->Update();
	//	ヒットエフェクトを更新
	for (const auto& particle : m_hitBulletPatricles)		particle->Update(timer);
	//	ステージの型にキャスト
	StageSelectScene::CHOOSE_STAGE stage = static_cast<StageSelectScene::CHOOSE_STAGE>(GetWordLevel());
	//	ステージ4以外は終了条件が存在しているため処理を行う
	if (stage != StageSelectScene::CHOOSE_STAGE::STAGE_4)
	{
		if (m_playSceneWave->IsFinalWave() && m_enemyManager->GetEnemy().size() == 0)
		{
			//	勝った
			m_gameResultString = WIN_STRING;
			//	花吹雪の作成
			for (size_t index = 0; index < FALLING_CHERRY_BLOSSOMS_GENERATED; index++)	m_fallingCherryBlossoms.push_back(std::make_unique<FallingCherryBlossoms>(m_player.get()));
			//	花を初期化する
			for (const auto& flower : m_fallingCherryBlossoms)							flower->Initialize();
			//	音楽を止める
			AudioManager::GetInstance()->StopSoundEffect(L"PlayGameBgm01");
			//	勝利音楽の再生
			AudioManager::GetInstance()->PlaySoundEffectSE(L"PlayWinBGM");
		}
	}
	//	サイズが0じゃないなら
	if (m_gameResultString.size() != 0 && !m_isFirstOpen)
	{
		//	ゲームの勝敗をプレイヤーに教える
		m_player->WhyGameResult(m_gameResultString);
		//	ゲーム終了
		m_isFinish = true;
	}
}

/// <summary>
/// 描画
/// </summary>
void PlayScene::Render()
{
	//	コンテキストの宣言
	auto context = m_screen->GetDeviceResources()->GetD3DDeviceContext();
	//　各行列を宣言
	DirectX::SimpleMath::Matrix proj  = m_screen->GetProjectionMatrix();
	//　ビューを作成
	DirectX::SimpleMath::Matrix view = DirectX::SimpleMath::Matrix::CreateLookAt
	(
		m_camera->GetEyePosition() + CAMERA_OFFSET_POSITION,
		m_camera->GetTargetPosition(),
		DirectX::SimpleMath::Vector3::UnitY
	);
	//	ビューを設定
	m_screen->SetViewMatrix(view);
	//	壁を要素ごとに描画
	for (const auto& wall : m_walls)	wall->Draw(view, proj);
	//	プレイヤー描画
	m_player->Render(view, proj);
	//　床の描画
	m_floor_Model->Render(context, view, proj, WALL_SCLAE);
	//	スカイドームの描画
	m_skyDome->Render(view, proj);	
	//	弾のマネージャーを描画する
	m_bulletManager->Render(view, proj);
	//	アイテムのマネージャーを描画する
	m_itemManager->Render(view, proj);
	//	敵のマネージャを描画する
	m_enemyManager->Render(view, proj);
	//	花を描画する
	if (m_fallingCherryBlossoms.size() != 0) { for (const auto& flower : m_fallingCherryBlossoms)	flower->Render(view, proj); }
	//	アニメーション中はUIを消す
	if (m_player->IsDeathAnimation() || m_player->IsWinAnimation())	return;
	//	エフェクトを描画する
	for (const auto& hitRender : m_hitRenders)			hitRender->Render(view, proj);
	//	エフェクトを描画する
	for (const auto& hitRender : m_hitBulletRenders)	hitRender->RenderBillBoard(view, proj, m_camera->GetEyePosition(), DirectX::SimpleMath::Vector3(0.0f, 1.0f, 1.0f));
	//	エフェクトを描画する
	for (const auto& particle : m_hitBulletPatricles)	particle->Render(view, proj, m_camera->GetEyePosition(), DirectX::SimpleMath::Vector3::Up);
	//	UIを描画する
	UIRender();


#ifdef _DEBUG

	std::wostringstream health;
	health << "HP : " << m_player->GetHealth() << " / " << m_player->GetMaxHealth();
	m_screen->RenderDebugFont(health.str().c_str(), DirectX::SimpleMath::Vector2(0.0f, 260.0f));
	std::wostringstream power;
	power << "POW : " << m_player->GetPower();
	m_screen->RenderDebugFont(power.str().c_str(), DirectX::SimpleMath::Vector2(0.0f, 300.0f));
	std::wostringstream position;
	position << "X : " << m_player->GetPosition().x << "Y : " << m_player->GetPosition().y << "Z : " << m_player->GetPosition().z;
	m_screen->RenderDebugFont(position.str().c_str(), DirectX::SimpleMath::Vector2(0.0f, 340.0f));

#endif // _DEBUG
}

/// <summary>
/// 終了処理
/// </summary>
void PlayScene::Finalize()
{
	m_player->Finalize();
	//
	m_enemyManager->Finalize();
	//	音楽を止める
	AudioManager::GetInstance()->StopSoundEffect(L"PlayGameBgm01");
}

/// <summary>
/// デバイス依存のリソースを作成する
/// </summary>
void PlayScene::CreateDeviceDependentResources()
{
	//	プレイヤーの呼び出し
	m_player = std::make_unique<Player>(&MyLib::ParamManager::GetInstane()->GetPlayerData());
	//	プレイヤーの初期化
	m_player->Initialize();
	//	プレイシーンのウェーブを作成
	m_playSceneWave = std::make_unique<PlaySceneWave>(this);
	//	初期化を行う
	m_playSceneWave->Initialize();
	//	敵のマネージャーを作成
	m_enemyManager = std::make_unique<EnemyManager>(this, m_player.get() , m_playSceneWave.get());
	//	敵のマネージャーを初期化する
	m_enemyManager->Initialize();
	//	アイテムのマネージャーを作成
	m_itemManager = std::make_unique<ItemManager>();
	//	アイテムのマネージャーを初期化する
	m_itemManager->Initialize();
	//	ヒットエフェクトの設定
	for (size_t index = 0; index < HIT_RENDER_RESTRICTION; ++index)
		m_hitRenders.push_back(std::make_unique<HitRenderer>(MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"HitTextures"), EFFECT_SIZE));
	//	ヒットエフェクトの設定　　
	for (size_t index = 0; index < HIT_RENDER_RESTRICTION; ++index)
		m_hitBulletRenders.push_back(
			std::make_unique<HitRenderer>(
				MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"HitBulletTextures"),
				EFFECT_SIZE
			)
		);
	//	弾ヒット時のエフェクト描画する
	for (size_t i = 0; i < HIT_RENDER_RESTRICTION; i++)	m_hitBulletPatricles.push_back(std::make_unique<BulletHitParticle>());
	//	バレットマネージャの作成
	m_bulletManager = std::make_unique<BulletManager>(m_enemyManager->GetEnemy());
	//	バレットマネージャの初期化
	m_bulletManager->Initialize();
	// 最初のビュー行列の位置を決める
	DirectX::SimpleMath::Vector3 eye(50.0f, 430.0f, 15.0f);
	DirectX::SimpleMath::Vector3 target(0.0f, 0.0f, 0.0f);
	DirectX::SimpleMath::Vector3 up(0.0f, 1.0f, 0.0f);
	//	カメラの初期化
	m_camera = std::make_unique<Camera>(eye, target, up, m_player.get());
	//初期化
	m_camera->Initialize();
	//	ミニマップの作成
	m_miniMap = std::make_unique<MiniMap>(m_player.get(),m_itemManager->GetItem());
	//床モデルの作成
	m_floor_Model = std::make_unique<Floor_Model>();
	//	スカイドーム
	m_skyDome = std::make_unique<SkyDome>(m_worldLevel);
	//	プレイヤーのUIを作成
	m_playerUI = std::make_unique<PlayerUI>();
	//	プレイヤーのポインターを設定する
	m_playerUI->SetPlayer(m_player.get());
	//	初期化する
	m_playerUI->Initialize();
	//	プレイヤーの体力バーUIを作成
	m_playerBarUI = std::make_unique<PlayerHPBar>();
	//	プレイヤーのポインターを設定する
	m_playerBarUI->SetPlayer(m_player.get());
	//	プレイスコア
	m_playScore = std::make_unique<PlayeScore>();
	//	初期化する
	m_playScore->Initialize();
	//	初期化する
	m_playerBarUI->Initialize();
	//	プレイヤーのスタートシグナルを作成
	m_startSignal = std::make_unique<StartSignal>();
	//	フェードタイムのポインタを取得する
	m_startSignal->SetFadeTime(&m_fadeTime, FADE_TIME);
	//	初期化する
	m_startSignal->Initialize();
	//	ポーズ画面の作成
	m_pause = std::make_unique<Pause>(this);
	//	初期化処理
	m_pause->Initialize();
	//	壁
	m_walls.push_back(WallFactory::CreateWall(RIGHT_WALL_POSITION, RIGHT_WALL_SCALE, DirectX::XMConvertToRadians(0.0f)));
	m_walls.push_back(WallFactory::CreateWall(UNDER_WALL_POSITION, UNDER_WALL_SCALE, DirectX::XMConvertToRadians(90.0f)));
	m_walls.push_back(WallFactory::CreateWall(LEFT_WALL_POSITION,  LEFT_WALL_SCALE,  DirectX::XMConvertToRadians(180.0f)));
	m_walls.push_back(WallFactory::CreateWall(TOP_WALL_POSITION,   TOP_WALL_SCALE,	 DirectX::XMConvertToRadians(270.0f)));
	//	当たり判定の登録を行う
	m_colisionObjects = std::make_unique<ColisionObjects>(this, m_player.get(), &m_enemyManager->GetEnemy(), &m_bulletManager->GetBullet(), &m_walls, &m_itemManager->GetItem());
	//	経験値バーを作成する
	m_expBar = std::make_unique<PlayerExperiencePointUI>(m_player.get());
	//	レベルアップの作成
	m_levelCard = std::make_unique<LevelCard>(this, m_player.get());
	//	レベルアップの初期化処理
	m_levelCard->Initialize();
	//	ポストエフェクトの作成
	m_postEffect = std::make_unique<PlayPostEffect>(m_playerBarUI.get(), m_player.get());
	//	初期化処理
	m_postEffect->Initialize();
	//	オーディオマネージャの音を再生
	AudioManager::GetInstance()->PlaySoundEffectBGM(L"PlayGameBgm01");
	//	エフェクトの入場処理の開始
	m_game->GetChangeEffect()->RequestChangeEffect(ChangeEffect::ChangeSceneType::Play, ChangeEffect::ChangeSceneFadeType::To);
	//	マウス
	ShowMouse(true);
	//	一応からにしておく
	m_gameResultString = {};
	//	チュートリアルを作成する
	m_tutorialSystem = std::make_unique<TutorialSystem>(this , m_enemyManager.get());
	//	初回起動か
	EdditPlayData playData;
	playData.OpenPlayData();
	m_isFirstOpen = playData.IsFirstOpen();
}

/// <summary>
/// プレイヤーが生存しているか確認
/// </summary>
/// <param name="timer"></param>
void PlayScene::IsAlivePlayer()
{
	//	死んでいないなら帰れ
	if (!m_player->HealthCheck()) return;
	//	0じゃないなら入ってるから帰れ
	if (m_gameResultString.size() != 0)	return;
	//	ゲームクリア失敗
	m_gameResultString = LOSE_STRING;
	//	音楽を止める
	AudioManager::GetInstance()->StopSoundEffect(L"PlayGameBgm01");
	//	敗北音楽の再生
	AudioManager::GetInstance()->PlaySoundEffectSE(L"PlayLoseBGM");
}

/// <summary>
/// ゲームを終了した？
/// </summary>
/// <param name="timer">タイマー</param>
bool PlayScene::IsFinished(const DX::StepTimer& timer)
{
	//	ゲームが終わってないなら戻れ
	if (!m_isFinish)				return false;
	//	アニメーション中なら帰れ
	if (m_player->IsAnimation())	return false;
	//	経過時間を足す　
	m_finishedTime += static_cast<float>(timer.GetElapsedSeconds());
	//	経過時間でシーン変異
	if (m_finishedTime >= FINISHED_TIME)
	{
		//	経過時間を止める
		m_playScore->StopElapsedTimer();
		//	リザルトシーン
		m_game->GetSceneManager()->ChangeScene<ResultScene>(m_game, m_worldLevel);

		return true;
	}	

	return false;
}

/// <summary>
/// カメラを更新する
/// </summary>
/// <param name="timer">タイマー</param>
void PlayScene::UpdateCamera(const DX::StepTimer& timer)
{
	//	カメラを更新する
	m_camera->Update(timer, m_IsFade);
	//	エフェクトの退場処理の開始
	if (m_camera->IsDeathCamera() && !m_isFadeOutTask)
	{
		//	タスクが実行された
		m_isFadeOutTask = true;
		//	退出フェードを開始する
		m_game->GetChangeEffect()->RequestChangeEffect(ChangeEffect::ChangeSceneType::Play, ChangeEffect::ChangeSceneFadeType::Out);
	}

	//	ダメージ状態なら戻す
	if (m_player->IsDamege())	m_player->SetDamegeCondition(false);
}

/// <summary>
/// フェード中か
/// </summary>
/// <returns></returns>
bool PlayScene::NowFade(const DX::StepTimer& timer)
{
	//	開幕にフェードをつける
	if (m_IsFade)
	{
		//	カメラの位置を移動する
		m_camera->Update(timer, m_IsFade);
		//	経過時間を足していく
		m_fadeTime += static_cast<float>(timer.GetElapsedSeconds());
		//	スタートの合図を更新する
		m_startSignal->Update(timer);
		//	時間経過でフェード時間を終える
		if (m_fadeTime >= FADE_TIME)
		{
			m_IsFade = false;
			//	経過時間を0にする
			MyLib::ElapsedTime::GetInstance()->RestElapsedTime();

			return false;
		}

		return true;
	}

	return false;
}

/// <summary>
/// ポーズ中か
/// </summary>
/// <returns></returns>
bool PlayScene::NowPause()
{
	//	入力情報をを受け取り
	auto input = MyLib::InputSystem::GetInstance()->GetKeyTracer();

	//	ポーズ中なら止める
	if (m_pause->IsPause())
	{
		m_pause->Update();
		//	ポーズ中ならこれ以上処理を行わない
		return true;
	}

	//	Escapeを押されたらポーズへ
	if (input->pressed.Escape)
	{
		//	ポーズにする
		m_pause->SetPause(true);
		//	初期化する
		m_pause->Initialize();
		//	seを再生する
		AudioManager::GetInstance()->PlaySoundEffectSE(L"Open_SE01");

		return true;
	}

	return false;
}

/// <summary>
/// ミニマップを更新する
/// </summary>
/// <param name="timer"></param>
void PlayScene::UpdateMiniMap(const DX::StepTimer& timer)
{
	for (const auto& enemy : m_enemyManager->GetEnemy())	m_miniMap->UpdateMap(timer, enemy.get());
}

/// <summary>
/// エフェクトを描画するし大きさを変える
/// </summary>
/// <param name="position">座標</param>
void PlayScene::HitRnder(const DirectX::SimpleMath::Vector3& position)
{
	bool scaleFlag = false;

	for (const auto& hitRender : m_hitRenders)
	{
		//	使用中なら次を探す
		if (hitRender->IsUsed())	continue;

		//	エフェクトを描画
		hitRender->HitEffect(position, scaleFlag);
		break;
	}
}

/// <summary>
/// エフェクトのの設定をオンにする
/// </summary>
/// <param name="position">座標</param>
/// <param name="enemy">敵のポインター</param>
void PlayScene::HitRnder(const DirectX::SimpleMath::Vector3& position, const Enemy* enemy)
{
	bool scaleFlag = false;

	for (const auto& hitRender : m_hitRenders)
	{
		//	使用中なら次を探す
		if (hitRender->IsUsed())	continue;

		//	ボスの時だけ大きくする
		if (enemy->GetType() == Object::ObjectType::BossEnemy) scaleFlag = true;

		//	エフェクトを描画
		hitRender->HitEffect(position, scaleFlag);
		break;
	}
}

/// <summary>
/// エフェクトのの設定をオンにする
/// </summary>
/// <param name="position">座標</param>
void PlayScene::HitBulletRnder(const DirectX::SimpleMath::Vector3& position)
{
	for (const auto& hitRender : m_hitBulletPatricles)
	{
		//	使用中なら次を探す
		if (hitRender->IsUsed())	continue;
		//	エフェクトを描画
		hitRender->Hit(position);
		break;
	}
}

/// <summary>
/// タイトルシーンに切り変える
/// </summary>
void PlayScene::ChangeSceneTitle()
{
	//	リザルトシーン
	m_game->GetSceneManager()->ChangeScene<TitleScene>(m_game);
}

/// <summary>
/// マウスカーソルを見せるか
/// </summary>
/// <param name="isShow">見せるかどうか</param>
void PlayScene::ShowMouse(const bool& isShow)
{
	m_game->ShowMouseCursor(isShow);
}

/// <summary>
/// チュートリアル終了
/// </summary>
void PlayScene::FinishTutorial()
{
	//	エフェクトの入場処理の開始
	m_game->GetChangeEffect()->RequestChangeEffect(ChangeEffect::ChangeSceneType::Play, ChangeEffect::ChangeSceneFadeType::To);
	//	初回起動終了
	m_isFirstOpen = false;
}

/// <summary>
/// UIを描画する
/// </summary>
void PlayScene::UIRender()
{
	//	描画を開始する
	m_screen->GetSpriteBatch()->Begin();
	//	ポストエフェクトの描画
	if(!m_isFinish)	m_postEffect->Draw();
	//	ウェーブ数の描画
	m_playSceneWave->Draw();
	//	プレイヤーの体力バーUIを描画する
	m_playerBarUI->Draw();
	//	プレイヤーのUIを描画する
	m_playerUI->Draw();
	//	経験値バーを描画する
	m_expBar->Draw();
	//	描画する
	m_playScore->Draw();
	//フェード中なら描画する
	if (m_IsFade)	m_startSignal->Draw();
	//	ミニマップの描画する
	m_miniMap->Draw();
	//	レベルアップのカードの描画
	m_levelCard->Draw();
	//	ポーズ中なら描画する
	if (m_pause->IsPause())	m_pause->Render();
	//	チュートリアルの描画
	m_tutorialSystem->Render();
	//	描画を終了する
	m_screen->GetSpriteBatch()->End();
}