//
//		File Name ： TitleScene.cpp
//		Production： 2023/9/14
//		Author　　： 石田 恭一
//
#include "pch.h"
#include "Game/Game.h"

////////////////////////Scene//////////////////////////////////
#include "TitleScene.h"
#include "Game/MyLib/Scenes/StageSelect/StageSelectScene.h"
#include "Game/MyLib/Scenes/PlayScene/PlayScene.h"
#include "Game/MyLib/Scenes/ResultScene/ResultScene.h"
////////////////////////////////////////////////////////////////

//  タイトルのフェード時間
const float TitleScene::TITLE_FADE_ARRIVE_TIME = 1.6f;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="game"></param>
TitleScene::TitleScene(Game* game)
	:m_game(game),
	m_uiAlfa(0.0f),
	m_elapsedTime(0.0f),
	m_fadeTime(0.0f),
	m_finTime(0.0f),
	m_state(STATE::IDLE),
	m_backGroundTexture(nullptr),
	m_uiTexture(nullptr),
	m_resources(nullptr),
	m_screen(nullptr),
	m_fadeStart(false),
	m_isFin(false),
	m_alfaValue(false)
{

}

/// <summary>
/// デストラクタ
/// </summary>
TitleScene::~TitleScene()
{

}

/// <summary>
/// 初期化処理
/// </summary>
void TitleScene::Initialize()
{		
	CreateDeviceDependentResources();
}	

/// <summary>
/// 更新処理
/// </summary>
/// <param name="timer">タイマー</param>
void TitleScene::Update(const DX::StepTimer& timer)
{
	//	経過時間を足す
	m_elapsedTime += static_cast<float>(timer.GetElapsedSeconds());
	//	int型にする
	int state = static_cast<int>(m_state);

	//	ポーズ中は処理を行わない
	if (m_config->IsPause())
	{
		m_config->Update();
		return;
	}

	//	タイトルロゴの更新
	m_titleLogo->Update(state);
	//	各ギアの更新
	for (const auto& gear : m_gears)				gear->Update(state);
	//	タイトル文字の更新
	for (const auto& titleUI : m_titleStringUIs)	titleUI->Update(state);

	//	各ステートを更新する
	UpdateState(timer);

	//	終了コマンドが入力されたら実行する
	if (!m_isFin)	return;
	
	//	経過時間を足す
	m_finTime += static_cast<float>(timer.GetElapsedSeconds());

	//	既定量まできたら実行する
	if (m_finTime >= 0.5f)
	{
		PostQuitMessage(0);
	}
}

/// <summary>
/// 描画処理
/// </summary>
void TitleScene::Render()
{
	//	描画を開始する
	m_screen->GetSpriteBatch()->Begin();

	//	後ろの背景の画像を描画する
	m_screen->GetSpriteBatch()->Draw(m_backGroundTexture, m_backPos);
	//	タイトルロゴの描画
	m_titleLogo->Draw();

	// UIを描画する
	RenderUI();
	//	各ギアの描画
	for (const auto& gear	 : m_gears)				gear->Draw();
	//	タイトル文字の描画
	for (const auto& titleUI : m_titleStringUIs)	titleUI->Draw();

	//	ポーズ画面を描画する
	if (m_config->IsPause())
		m_config->Render();

	//	描画を終了する
	m_screen->GetSpriteBatch()->End();
}

/// <summary>
/// 終了処理
/// </summary>
void TitleScene::Finalize()
{
	
}

/// <summary>
/// 各ステートを更新する
/// </summary>
void TitleScene::UpdateState(const DX::StepTimer& timer)
{
	//	ステートの状態により処理を変える
	switch (m_state)
	{
		//	初期状態
	case TitleScene::STATE::IDLE:	UpdateIdle();		break;
	//	プレイシーンに行く
	case TitleScene::STATE::PLAY:	UpdatePlay(timer);	break;
	//	コンフィグ
	case TitleScene::STATE::CONFIG:	UpdateConfig();		break;
	//	ゲームを終了する
	case TitleScene::STATE::END:	UpdateEnd();		break;
	//	ノーン
	case TitleScene::STATE::NONE:						break;
	default:											break;
	}
}

/// <summary>
/// 更新処理
/// </summary>
void TitleScene::UpdateIdle()
{
	//	キーボードの情報とマウスの入力情報を受け取る
	auto input = MyLib::InputSystem::GetInstance()->GetKeyTracer();
	auto mouse = MyLib::InputSystem::GetInstance()->GetStateTracker();

	//	位置を少し動かす
	m_uiPos.y += 0.1f * sinf(m_elapsedTime);
	//	SPACEキーを押させるのを促すためにアルファ値を変える
	m_uiAlfa = sinf(m_elapsedTime * 2.0f) + 1.0f;
	//	プレイステートへ遷移する
	if (input->pressed.Space || mouse->leftButton == mouse->PRESSED)
	{
		//	音を再生する
		AudioManager::GetInstance()->PlaySoundEffectSE(L"PlaySE01_Accept");
		//	アルファ値を初期化
		m_uiAlfa = 0.0f;
		//	プレイステートに行く
		m_state = STATE::PLAY;
	}
}

/// <summary>
/// プレイステートを更新する
/// </summary>
void TitleScene::UpdatePlay(const DX::StepTimer& timer)
{
	//	キーボードの情報とマウスの入力情報を受け取る
	auto input = MyLib::InputSystem::GetInstance()->GetKeyTracer();
	auto mouse = MyLib::InputSystem::GetInstance()->GetStateTracker();

	//	スペースキーかマウスの左クリックでシーン遷移する
	if (input->pressed.W && !m_fadeStart)
	{
		//	オーディオマネージャの音を再生
		AudioManager::GetInstance()->PlaySoundEffectSE(L"PlaySE02_MoveTitle");
		m_state = STATE::END;
	}

	if (input->pressed.S && !m_fadeStart)
	{
		//	オーディオマネージャの音を再生
		AudioManager::GetInstance()->PlaySoundEffectSE(L"PlaySE02_MoveTitle");
		m_state = STATE::CONFIG;
	}

	//	スペースキーかマウスの左クリックでシーン遷移する
	if (input->pressed.Space && !m_fadeStart || mouse->leftButton == mouse->PRESSED && !m_fadeStart)
	{
		//	オーディオマネージャの音を再生
		AudioManager::GetInstance()->PlaySoundEffectSE(L"PlaySE01_Accept");
		//	フェードをスタート	
		m_fadeStart = true;
		//	エフェクトの退出処理の開始
		m_game->GetChangeEffect()->RequestChangeEffect(ChangeEffect::ChangeSceneType::Title, ChangeEffect::ChangeSceneFadeType::Out);
	}

	//	シーン遷移が開始されたら処理を行う
	if (!m_fadeStart)	return;
	
	//	経過時間を足す
	m_fadeTime += static_cast<float>(timer.GetElapsedSeconds());

	if (m_fadeTime >= TITLE_FADE_ARRIVE_TIME)
	{
		//	BGMを音楽を止める
		AudioManager::GetInstance()->StopSoundEffect(L"PlayTitleBGM");
		//	ステージセレクトへいく
		m_game->GetSceneManager()->ChangeScene<StageSelectScene>(m_game);
	}	
}

/// <summary>
/// コンフィグステートを更新する
/// </summary>
void TitleScene::UpdateConfig()
{
	//	キーボードの情報とマウスの入力情報を受け取る
	auto input = MyLib::InputSystem::GetInstance()->GetKeyTracer();
	auto mouse = MyLib::InputSystem::GetInstance()->GetStateTracker();

	//	スペースキーかマウスの左クリックでシーン遷移する
	if (input->pressed.W)
	{
		//	オーディオマネージャの音を再生
		AudioManager::GetInstance()->PlaySoundEffectSE(L"PlaySE02_MoveTitle");
		m_state = STATE::PLAY;
	}

	if (input->pressed.S)
	{
		//	オーディオマネージャの音を再生
		AudioManager::GetInstance()->PlaySoundEffectSE(L"PlaySE02_MoveTitle");
		m_state = STATE::END;
	}

	//	スペースキーかマウスの左クリックでコンフィグを開く
	if (input->pressed.Space || mouse->leftButton == mouse->PRESSED)
	{
		m_config->SetPause(true);
		m_config->Initialize();
		//	seを再生する
		AudioManager::GetInstance()->PlaySoundEffectSE(L"Open_SE01");
	}
}

/// <summary>
///	エンドステートを更新する
/// </summary>
void TitleScene::UpdateEnd()
{
	//	キーボードの情報とマウスの入力情報を受け取る
	auto input = MyLib::InputSystem::GetInstance()->GetKeyTracer();
	auto mouse = MyLib::InputSystem::GetInstance()->GetStateTracker();

	//	ステートから移動する
	if (input->pressed.W )
	{
		AudioManager::GetInstance()->PlaySoundEffectSE(L"PlaySE02_MoveTitle");
		m_state = STATE::CONFIG;
	}
	//	ステートから移動する
	if (input->pressed.S)
	{
		AudioManager::GetInstance()->PlaySoundEffectSE(L"PlaySE02_MoveTitle");
		m_state = STATE::PLAY;
	}

	//	スペースキーかマウスの左クリックでゲーム終了
	if (input->pressed.Space || mouse->leftButton == mouse->PRESSED)
	{
		//	オーディオマネージャの音を再生
		AudioManager::GetInstance()->PlaySoundEffectSE(L"PlaySE01_Accept");

		m_isFin = true;
	}
}

/// <summary>
/// UIを描画する
/// </summary>
void TitleScene::RenderUI()
{
	//	アイドリング状態以外は帰れ
	if (m_state != STATE::IDLE)	return;


	//	UIの画像を描画する
	m_screen->GetSpriteBatch()->Draw
	(
		m_uiTexture,
		m_uiPos,
		nullptr,
		DirectX::SimpleMath::Color(m_uiAlfa, m_uiAlfa, m_uiAlfa, m_uiAlfa),
		0.0f,
		DirectX::SimpleMath::Vector2(156.5f, 40.5f),
		DirectX::SimpleMath::Vector2(1.2f, 1.2f)
	);
}

/// <summary>
/// デバイス依存のリソースの初期化
/// </summary>
void TitleScene::CreateDeviceDependentResources()
{
	//	スクリーンリソースを取得する
	m_screen = MyLib::ScreenResources::GetInstance();
	//	リソーシーズデータを取得する
	m_resources = MyLib::ResourcesData::GetInstance();
	//	ポーズ画面を作成
	m_config = std::make_unique<Config>();

	m_uiTexture = m_resources->GatShaderResourceView(L"title_UI"),

	//	背景のテクスチャを取得する
	m_backGroundTexture = m_resources->GatShaderResourceView(L"title_back");
	//	タイトルロゴの作成
	m_titleLogo = std::make_unique<TitleLogo>
	(
		m_resources->GatShaderResourceView(L"titleLogo"),
		DirectX::SimpleMath::Vector2(580.0f, 300.0f),
		DirectX::SimpleMath::Vector2(500.0f, 100.0f)
	);

	//	最大の数
	int maxDirection = static_cast<int>(Gear::Direction::OverID);
	//	ギアを作成
	for (int i = 0; i < maxDirection; i++)
	{
		m_gears.push_back
		(
			std::make_unique<Gear>
			(
				m_resources->GatShaderResourceView(L"gear"),
				DirectX::SimpleMath::Vector2(1250.0f - (1230.0f * i), 800.0f),
				DirectX::SimpleMath::Vector2(361.5f, 358.0f),
				static_cast<Gear::Direction>(i)
			)
		);
	}

	//	ドアに渡す要素
	std::initializer_list<ID3D11ShaderResourceView*> stringUIResources
	{
		m_resources->GatShaderResourceView(L"title_UI_PlayGame_Off"),
		m_resources->GatShaderResourceView(L"title_UI_PlayGame"),
		m_resources->GatShaderResourceView(L"title_UI_Config_Off"),
		m_resources->GatShaderResourceView(L"title_UI_Config"),
		m_resources->GatShaderResourceView(L"title_UI_EndGame_Off"),
		m_resources->GatShaderResourceView(L"title_UI_EndGame")
	};

	//	最初の番号
	int index = static_cast<int>(TitleScene::STATE::PLAY);
	//	ずらすための値
	int range = 0;

	for (auto itr = stringUIResources.begin(); itr != stringUIResources.end(); itr += 2)
	{
		m_titleStringUIs.push_back
		(
			std::make_unique<TitleStringUI>
			(
				*(itr),
				*(itr + 1),
				DirectX::SimpleMath::Vector2(640.0f, 550.0f + (40.0f * range)),
				index
			)
		);

		range++;
		index++;
	}

	//	UIの画像を初期化
	m_uiPos		= DirectX::SimpleMath::Vector2(640.0f, 600.0f);
	//	フェイドフラグの初期化
	m_fadeStart = false;

	m_alfaValue = false;
	//	ステートをアイドルモードに
	m_state = STATE::IDLE;
	//	アルファ値を初期化する
	m_uiAlfa = 1.0f;
	//	オーディオマネージャの音を再生
	AudioManager::GetInstance()->PlaySoundEffectBGM(L"PlayTitleBGM");
}
