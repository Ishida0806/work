//
//		File Name ： StageSelectScene.cpp
//		Production： 2023/9/14
//		Author　　： 石田 恭一
// 
//		ステージをセレクトをする場所
//
#include "pch.h"
#include "Game/Game.h"

////////////////////////Scene//////////////////////////////////
#include "Game/MyLib/Scenes/TitleScene/TitleScene.h"
#include "Game/MyLib/Scenes/StageSelect/StageSelectScene.h"
#include "Game/MyLib/Scenes/PlayScene/PlayScene.h"
#include "Game/MyLib/Scenes/ResultScene/ResultScene.h"
////////////////////////////////////////////////////////////////


//	アニメーションを実行中なら操作を行わない
const float StageSelectScene::COOL_TIME										= 0.55f;
//	通常時の大きさ
const float StageSelectScene::BASE_SCALE									= 0.5f;
//	フェード時の目標大きさ
const float StageSelectScene::FADE_TARGET_SCALE								= 0.75f;
//	画像の感覚
const float StageSelectScene::DISTANCE										= 1000.0f;
//	ラープの速度
const float StageSelectScene::LERP_SPEED									= 0.08f;
//	ラープ時の大きさの速度
const float StageSelectScene::LERP_SCALE_SPEED								= 0.1f;
//	終了タイム
const float StageSelectScene::FIN_TIME										= 1.6f;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="game">ゲーム</param>
StageSelectScene::StageSelectScene(Game* game)
	:m_game(game),
	m_screen(nullptr),
	m_resorces(nullptr),
	m_escTexture(nullptr),
	m_stageSelectBackGroundStageFrameworkTexture(nullptr),
	m_stageState(CHOOSE_STAGE::STAGE_1),
	m_elapsedTime(0.0f),
	m_moveCoolTime(0.0f),
	m_preMove(false),
	m_isChanegeScene(false),
	m_isMoveDirection(MOVE_DIRECTION::CENTER)
{
	
}

/// <summary>
/// デストラクタ
/// </summary>
StageSelectScene::~StageSelectScene()
{
	//	ステージセレクト終了時に音楽を止める
	AudioManager::GetInstance()->StopSoundEffect(L"PlayStageBGM");
}

/// <summary>
/// 初期化処理
/// </summary>
void StageSelectScene::Initialize()
{
	//	デバイス依存のリソースの初期化する
	CreateDeviceDependentResources();
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="timer"></param>
void StageSelectScene::Update(const DX::StepTimer& timer)
{
	//	ステージ
	int stageNum = static_cast<int>(m_stageState);
	//	経過時間を足す
	m_elapsedTime += static_cast<float>(timer.GetElapsedSeconds());
	//	背景画像を更新する
	m_stageBackGround->Update(static_cast<int>(m_stageState));
	// UI達を更新する
	UpdateUIs(timer);
	//	キーが押されたら
	InputKey();
	//	シーン切り替え確認
	if (m_isChanegeScene)	return;
	//	ステートの状態を確認する
	CheckState();
	//	ドアを更新する
	UpdateDoor(timer);
	//	プレイヤーを更新する
	UpdatePlayer();
	//	鳥の更新
	m_bird->Update(timer, stageNum);
	//	太陽の更新
	m_sun->Update(timer, stageNum);
	//	敵たちの更新
	for (auto& enemy2d : m_enemies2D)			enemy2d->Update(timer);
	//	ステージサークルの更新
	for (const auto& circle : m_stageCircles)	circle->Update(timer, stageNum);
	//	プレイヤーを更新する
	m_player2D->Update(timer);
	//	星マネージャの更新
	m_starManeger->Update(timer, stageNum);
	//	2秒経過したらシーン遷移
	if (m_player2D->GetFinAnimationTime() >= FIN_TIME)
	{
		m_game->GetSceneManager()->ChangeScene<PlayScene>(m_game, m_screen, stageNum);
	}
}

/// <summary>
/// 描画処理
/// </summary>
void StageSelectScene::Render()
{	
	//	背景画像の描画
	m_stageBackGround->Draw();

	//	描画を始める
	m_screen->GetSpriteBatch()->Begin();

	//	星マネージャの更新
	m_starManeger->Draw();

	//	鳥の描画
	m_bird->Draw();

	//	太陽の描画
	//m_sun->Draw();

	//	敵の描画する
	for (auto& enemy2d : m_enemies2D)	enemy2d->Draw();

	//	背景画像の描画
	m_screen->GetSpriteBatch()->Draw
	(
		m_stageSelectBackGroundStageFrameworkTexture,
		DirectX::SimpleMath::Vector2(-10.0f, -5.0f)
	);
	//	ドアを描画する
	RenderDoor();
	//	キーを描画する
	RenderKey();
	//	プレイヤーの描画
	m_player2D->Draw();
	//	ステージサークルの描画
	for (const auto& circle : m_stageCircles)		circle->Draw();
	//	エスケープキーの描画
	m_screen->GetSpriteBatch()->Draw
	(
		m_escTexture,
		DirectX::SimpleMath::Vector2::Zero
	);
	//	描画を終える
	m_screen->GetSpriteBatch()->End();
}

/// <summary>
/// 終了処理
/// </summary>
void StageSelectScene::Finalize()
{
}

/// <summary>
/// デバイス依存のリソース
/// </summary>
void StageSelectScene::CreateDeviceDependentResources()
{
	//	スクリーンリソース
	m_screen		  = MyLib::ScreenResources::GetInstance();
	//	リソーシーズ
	m_resorces		  = MyLib::ResourcesData::GetInstance();
	//	背景画像のフレームワーク
	m_stageSelectBackGroundStageFrameworkTexture = m_resorces->GatShaderResourceView(L"StageFramework");
	//	エスケープキー
	m_escTexture = m_resorces->GatShaderResourceView(L"EscapeUI");
	//	画面の高さ・横幅
	int s_height, s_weight;
	//	スクリーンサイズを取得する
	m_screen->GetScreenSize(s_weight, s_height);
	//	画面サイズの半分
	DirectX::SimpleMath::Vector2 half_screen = DirectX::SimpleMath::Vector2(static_cast<float>(s_weight) / 2.0f, static_cast<float>(s_height) / 2.0f);
	//	ドアに渡す要素
	std::initializer_list<ID3D11ShaderResourceView*> doorResources
	{
		m_resorces->GatShaderResourceView(L"Door_Easy"),
		m_resorces->GatShaderResourceView(L"EasyFont"),
		m_resorces->GatShaderResourceView(L"Door_Normal"),
		m_resorces->GatShaderResourceView(L"NormalFont"),
		m_resorces->GatShaderResourceView(L"Door_Hard"),
		m_resorces->GatShaderResourceView(L"HardFont"),
		m_resorces->GatShaderResourceView(L"Door_Extra"),
		m_resorces->GatShaderResourceView(L"EndresFont"),
	};
	//	星を作成する
	m_starManeger = std::make_unique<StarManager>(m_resorces->GatShaderResourceView(L"star"));
	m_starManeger->Initialize();
	int num = 0;
	//	2dドアの作成
	for (auto itr = doorResources.begin(); itr != doorResources.end(); itr += 2)
	{
		m_doors2D.push_back
		(
			std::make_unique<Door2D>
			(
				*(itr),
				*(itr + 1),
				half_screen + (DirectX::SimpleMath::Vector2(DISTANCE * static_cast<float>(num),-30.0f)),
				DISTANCE
			)
		);
		num++;
	}
	//	敵の2D画像を作成する
	for (int i = 0; i < Enemy2D::GENERATION_ENEMY2D; i++)
	{
		if (i % 2 == 0)
		{
			m_enemies2D.push_back
			(
				std::make_unique<Enemy2D>
				(
					m_resorces->GatShaderResourceView(L"NormalEnemyTexure"),
					DirectX::SimpleMath::Vector2(Utility::CreateRandom(25.0f, 1255.0f), Utility::CreateRandom(25.0f, 680.0f))
				)
			);
		}
		else
		{
			m_enemies2D.push_back
			(
				std::make_unique<Enemy2D>
				(
					m_resorces->GatShaderResourceView(L"TackleEnemyTexure"),
					DirectX::SimpleMath::Vector2(Utility::CreateRandom(25.0f, 1255.0f), Utility::CreateRandom(25.0f, 680.0f))
				)
			);
		}
	}
	//	最大値を取得する
	int maxSize = static_cast<int>(KeyFont::FONT_TYPE::OverID);
	//	キーフォントの作成
	for (int index = 0; index < maxSize; index++)
	{
		//	現在の番号をフォントタイプ型に変換する
		KeyFont::FONT_TYPE nowType = static_cast<KeyFont::FONT_TYPE>(index);
		//	要素を追加
		m_keys2D.push_back
		(
			std::make_unique<KeyFont>
			(
				nowType,
				DirectX::SimpleMath::Vector2(350.0f + 580.0f * index, 420.0f)
			)
		);
		//	初期化処理
		m_keys2D[index]->Initialize();
	}
	//	ステージの最大数
	size_t stageMax = static_cast<size_t>(CHOOSE_STAGE::OverID);
	//	ステージサークルの作成
	for (int i = 0; i < stageMax; i++) 
	{
		m_stageCircles.push_back(std::make_unique<StageCircle>
			(
				MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"Stage_Circle"),
				DirectX::SimpleMath::Vector2(525.0f +( 60.0f * i), 660.0f ),
				i
			)
		);
	}
	//	鳥
	m_bird = std::make_unique<Bird>();
	//	初期化する
	m_bird->Initialize();
	//	太陽
	m_sun = std::make_unique<Sun>();
	//	初期化する
	m_sun->Initialize();
	//	ステージの背景
	m_stageBackGround = std::make_unique<StageBackGround>(m_resorces->GatShaderResourceView(L"StageSelect_BackGround"), static_cast<int>(CHOOSE_STAGE::OverID));
	//	初期化処理
	m_stageBackGround->Initialize();
	//	プレイヤーの位置を初期化する
	m_player2D = std::make_unique<Player2D>(m_resorces->GatShaderResourceView(L"player2d"), DirectX::SimpleMath::Vector2(350.0f, static_cast<float>(s_height) / 1.5f));
	//	初期化を行う
	m_player2D->Initialize();
	//	オーディオマネージャの音を再生
	AudioManager::GetInstance()->PlaySoundEffectBGM(L"PlayStageBGM");
	//	エフェクトの入場処理の開始
	m_game->GetChangeEffect()->RequestChangeEffect(ChangeEffect::ChangeSceneType::Select, ChangeEffect::ChangeSceneFadeType::To);
}

/// <summary>
/// UI達を更新する
/// </summary>
/// <param name="timer">タイマー</param>
void StageSelectScene::UpdateUIs(const DX::StepTimer& timer)
{
	//	プレイヤーのアニメーション状態がアイドリング以外なら帰れ
	if (m_player2D->GetState() != Player2D::PLAYER_STATE::IDLE) return;

	//	移動中なら帰れ
	if (m_isMoveDirection != MOVE_DIRECTION::CENTER)		return;

	//	画像を拡大をさせる
	m_doorScale.x = 0.35f * (2.0f + cosf(m_elapsedTime * 2.5f));
	m_doorScale.y = 0.35f * (2.0f + cosf(m_elapsedTime * 2.5f));

	//	ある程度の大きさまでいったら補正をかける
	if (m_doorScale.x >= 0.70f)
	{
		//	クランプをかける
		m_doorScale.x = Utility::Clamp(m_doorScale.x, 0.0f, 0.70f);
		//	経過時間を少し進める
		m_elapsedTime += 0.071f;
	}
	if (m_doorScale.y >= 0.70f)
	{
		//	クランプをかける
		m_doorScale.y = Utility::Clamp(m_doorScale.y, 0.0f, 0.70f);
		//	経過時間を少し進める
		m_elapsedTime += 0.071f;
	}

	//	キーたちを更新する
	for (const auto& key2D : m_keys2D)
		key2D->Update(timer);
}

/// <summary>
/// キーが押されたら
/// </summary>
void StageSelectScene::InputKey()
{
	//	プレイヤーのアニメーション状態がアイドリング以外なら帰れ
	if (m_player2D->GetState() != Player2D::PLAYER_STATE::IDLE) return;

	//	移動中なら帰れ
	if(m_isMoveDirection	  != MOVE_DIRECTION::CENTER)		return;

	//	キーボードの情報とマウスの入力情報を受け取る
	auto input = MyLib::InputSystem::GetInstance()->GetKeyTracer();
	auto mouse = MyLib::InputSystem::GetInstance()->GetStateTracker();
	//	Dキーを入力 && 移動中じゃないなら操作を受け取る
	if (input->pressed.D && m_stageState != CHOOSE_STAGE::STAGE_4)
	{
		m_elapsedTime = 0.0f;
		m_doorScale.x = BASE_SCALE;
		m_doorScale.y = BASE_SCALE;
		m_isMoveDirection = MOVE_DIRECTION::RIGHT;
		for (const auto& door2d : m_doors2D)
			door2d->TargetPosDecision(static_cast<int>(m_isMoveDirection));
		//	音を再生する
		AudioManager::GetInstance()->PlaySoundEffectSE(L"PlaySE02_MoveTitle");
	}
	//	Aキーを入力 && 移動中じゃないなら操作を受け取る
	if (input->pressed.A && m_stageState != CHOOSE_STAGE::STAGE_1)
	{
		m_elapsedTime = 0.0f;
		m_doorScale.x = BASE_SCALE;
		m_doorScale.y = BASE_SCALE;
		m_isMoveDirection = MOVE_DIRECTION::LEFT;
		for (const auto& door2d : m_doors2D)
			door2d->TargetPosDecision(static_cast<int>(m_isMoveDirection));
		//	音を再生する
		AudioManager::GetInstance()->PlaySoundEffectSE(L"PlaySE02_MoveTitle");
	}
	//	シーンを切り替える
	if (input->pressed.Escape)
	{
		//	シーンを切り替える
		m_game->GetSceneManager()->ChangeScene<TitleScene>(m_game);
		//	SEを再生する
		AudioManager::GetInstance()->PlaySoundEffectSE(L"Close_SE01");
		//	フラグを行う
		m_isChanegeScene = true;
	}

	//	スペースを入力 || マウス入力で　&& 移動中じゃないなら操作を受け取る && プレイヤーがアニメーション中じゃないなら
	if (input->pressed.Space  ||	
		mouse->leftButton == mouse->PRESSED)
	{
		//	アニメーションを開始する
		m_player2D->BeginChangeSceneAnimation();
		//	SEを再生する
		AudioManager::GetInstance()->PlaySoundEffectSE(L"PlaySE01_Accept");
	}
}

/// <summary>
/// プレイヤーの情報を更新する
/// </summary>
void StageSelectScene::UpdatePlayer()
{
	//	プレイヤーのアニメーション状況がアイドリングなら帰れ
	if (m_player2D->GetState() == Player2D::PLAYER_STATE::IDLE)	return;
	
	if (m_player2D->GetState() == Player2D::PLAYER_STATE::FIRST)
	{
		//	大きさを小さくする
		m_doorScale.x = Utility::Lerp(m_doorScale.x, BASE_SCALE / 2.0f, LERP_SCALE_SPEED);
		m_doorScale.y = Utility::Lerp(m_doorScale.y, BASE_SCALE / 2.0f, LERP_SCALE_SPEED);
	}
	if (m_player2D->GetState() == Player2D::PLAYER_STATE::SECOND)
	{
		//	大きさを大きくする
		m_doorScale.x = Utility::Lerp(m_doorScale.x, FADE_TARGET_SCALE, LERP_SCALE_SPEED);
		m_doorScale.y = Utility::Lerp(m_doorScale.y, FADE_TARGET_SCALE, LERP_SCALE_SPEED);
	}
}

/// <summary>
/// ドアの更新を受け取ったら更新を行う
/// </summary>
void StageSelectScene::UpdateDoor(const DX::StepTimer& timer)
{
	//	現在選択中のステージ番号
	int stageNum = static_cast<int>(m_stageState);
	//	セレクトフラグ
	bool selectFLag = false;
	//	
	for (size_t i = 0; i < m_doors2D.size(); i++)
	{
		if (i == stageNum)
		{
			//	この番号が選択された！
			selectFLag = true;
			m_doors2D[i]->Update(selectFLag);
		}
		else
		{
			//	この番号が選択されなかった
			m_doors2D[i]->Update(selectFLag);
		}
	}

	//	アニメーション実行中ならラープを行う
	if (m_isMoveDirection == MOVE_DIRECTION::RIGHT)
	{
		//	経過時間を足す
		m_moveCoolTime += static_cast<float>(timer.GetElapsedSeconds());
		//	移動が終わったら値を初期化する
		if (m_moveCoolTime >= COOL_TIME)
		{
			m_isMoveDirection = MOVE_DIRECTION::CENTER;
			m_preMove = false;
			m_moveCoolTime = 0.0f;
			m_elapsedTime = 0.0f;
			m_doorScale.x = BASE_SCALE;
			m_doorScale.y = BASE_SCALE;
		}
	}
	//	アニメーション実行中ならラープを行う
	if (m_isMoveDirection == MOVE_DIRECTION::LEFT)
	{
		//	経過時間を足す
		m_moveCoolTime += static_cast<float>(timer.GetElapsedSeconds());
		//	移動が終わったら値を初期化する
		if (m_moveCoolTime >= COOL_TIME)
		{
			m_isMoveDirection = MOVE_DIRECTION::CENTER;
			m_preMove		= false;
			m_moveCoolTime	= 0.0f;
			m_elapsedTime = 0.0f;
			m_doorScale.x = BASE_SCALE;
			m_doorScale.y = BASE_SCALE;
		}
	}
}

/// <summary>
/// 現在のステートに対して処理を行う
/// </summary>
void StageSelectScene::CheckState()
{
	if (m_isMoveDirection == MOVE_DIRECTION::CENTER )	return;

	if (m_preMove == true)							return;

	int nowStageNum  = static_cast<int>(m_stageState);
	int nextStageNum = static_cast<int>(m_stageState);

	int maxStageNum = static_cast<int>(CHOOSE_STAGE::OverID);

	//	左が押されたら
	if (m_isMoveDirection == MOVE_DIRECTION::RIGHT)
	{
		//	ステージ番号をインクリメント
		nextStageNum++;

		if (nextStageNum < maxStageNum)
			nowStageNum++;
	}
	else
	{
		//	ステージ番号をデクリメント
		nextStageNum--;

		//	ステージ番号が0より大きなら
		if (nextStageNum >= 0)
			nowStageNum--;
	}

	m_stageState = static_cast<CHOOSE_STAGE>(nowStageNum);
	m_preMove = true;
}

/// <summary>
/// キーを描画する
/// </summary>
void StageSelectScene::RenderKey()
{
	//	プレイヤーのアニメーション状態がアイドリング以外なら帰れ
	if (m_player2D->GetState() != Player2D::PLAYER_STATE::IDLE)	return;

	//	最大値
	int size = static_cast<int>(KeyFont::FONT_TYPE::OverID);
	//	右側
	int right = static_cast<int>(KeyFont::FONT_TYPE::RIGHT);
	//	左側
	int left = static_cast<int>(KeyFont::FONT_TYPE::LEFT);

	for (int i = 0; i < size; i++)
	{
		//	現在の番号
		int nowSize = static_cast<int>(m_keys2D[i]->GetType());
		//	右側の値なら表示
		if (nowSize == left)
		{
			if (m_stageState != CHOOSE_STAGE::STAGE_1 && m_isMoveDirection == MOVE_DIRECTION::CENTER)
			{
				m_keys2D[nowSize]->Draw();
			}
		}
		//	左側の値なら表示
		else if(nowSize == right)
		{
			if (m_stageState != CHOOSE_STAGE::STAGE_4 && m_isMoveDirection == MOVE_DIRECTION::CENTER)
			{
				m_keys2D[nowSize]->Draw();
			}
		}
	}
}

/// <summary>
/// ドアを描画する
/// </summary>
void StageSelectScene::RenderDoor()
{
	unsigned int stageState = static_cast<int>(m_stageState);

	for (size_t i = 0; i < m_doors2D.size(); i++)
	{
		if (i == stageState)
		{
			m_doors2D[i]->Draw(m_doorScale);
		}
		else
		{
			m_doors2D[i]->Draw(DirectX::SimpleMath::Vector2(BASE_SCALE, BASE_SCALE));
		}
	}
}