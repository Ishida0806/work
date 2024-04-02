//
//		File Name ： ResultScene.cpp
//		Production： 2023/9/14
//		Author　　： 石田 恭一
// 
//		リザルトシーン
//
#include "pch.h"

#include "Game/Game.h"
////////////////////////Scene//////////////////////////////////
#include "Game/MyLib/Scenes/TitleScene/TitleScene.h"
#include "Game/MyLib/Scenes/StageSelect/StageSelectScene.h"
#include "Game/MyLib/Scenes/PlayScene/PlayScene.h"
#include "Game/MyLib/Scenes/ResultScene/ResultScene.h"
////////////////////////////////////////////////////////////////


//	簡単な難易度の加算文章
const float ResultScene::EASY_ADDITION	 = 1.0f;
//	通常の難易度の加算文章
const float ResultScene::NORMAL_ADDITION = 1.2f;
//	難しい難易度の加算文章
const float ResultScene::HARD_ADDITION	 = 1.4f;
//	エンドレス難易度の加算文章
const float ResultScene::ENDRES_ADDITION = 1.5f;
//	PUSHUIの座標
const DirectX::SimpleMath::Vector2 ResultScene::PUSH_SPACE_POSITION		   = DirectX::SimpleMath::Vector2(665.0f, 640.0f);
//	PUSHUIの真ん中座標
const DirectX::SimpleMath::Vector2 ResultScene::PUSH_SPACE_ORIGIN_POSITION = DirectX::SimpleMath::Vector2(175.5, 53.5f);


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="game"></param>
/// <param name="score"></param>
ResultScene::ResultScene(Game* game, int stageSelect)
	:m_game(game),
	m_stageNum(stageSelect),
	m_screen(nullptr),
	m_resorces(nullptr),
	m_backGroundTexture(nullptr),
	m_tableBackGroundTexture(nullptr),
	m_judScore(false),
	m_isFinished(false),
	m_finishedTime(0.0f)
{
	
}

/// <summary>
/// デストラクタ
/// </summary>
ResultScene::~ResultScene()
{
	AudioManager::GetInstance()->StopSoundEffect(L"ResultBGM");
}

/// <summary>
/// 初期化処理
/// </summary>
void ResultScene::Initialize()
{
	//	デバイス依存のリソース
	CreateDeviceDependentResources();
}

/// <summary>
/// 後進処理
/// </summary>
/// <param name="timer">タイマー</param>
void ResultScene::Update(const DX::StepTimer& timer)
{
	auto input = MyLib::InputSystem::GetInstance()->GetKeyTracer();
	auto mouse = MyLib::InputSystem::GetInstance()->GetStateTracker();

	if (!m_resultBackGround->Update())	return;

	//	スコア更新し終わったらTRUEに
	if (m_scoreOutPut->Update())
	{
		//	初回のみSEを再生する
		if (!m_judScore)
		{
			m_judScore = true;
		}
		//	判子を更新
		m_pushSeal->Update();
		//	スコアの評価値を更新する
		m_valucationScore->Update(m_pushSeal->IsTop());
		//	UIキーを更新する
		m_pushSpase->Update();
	}

	if (!m_scoreOutPut->Update())	return;

	//	アクションを起こしたら条件を満たす
	if (input->pressed.Space && !m_isFinished ||
		mouse->leftButton && !m_isFinished)
	{
		//	終了条件を満たした
		m_isFinished = true;
		//	音を鳴らす
		AudioManager::GetInstance()->PlaySoundEffectSE(L"PlaySE01_Accept");
		//	エフェクトの退場処理の開始
		m_game->GetChangeEffect()->RequestChangeEffect(ChangeEffect::ChangeSceneType::Result, ChangeEffect::ChangeSceneFadeType::Out);
	}

	//	終了条件を満たしていないなら帰れ
	if (!m_isFinished)	return;

	m_finishedTime += static_cast<float>(timer.GetElapsedSeconds());

	if (m_finishedTime > 3.2f)
	{
		//	シーンを切り替える
		m_game->GetSceneManager()->ChangeScene<TitleScene>(m_game);
	}
}

/// <summary>
/// 描画処理
/// </summary>
void ResultScene::Render()
{
	//	スプライトバッチ
	DirectX::SpriteBatch* spriteBath = m_screen->GetSpriteBatch();

	//	描画を開始する
	spriteBath->Begin();

	//	背景画像の描画
	spriteBath->Draw
	(
		m_backGroundTexture,
		DirectX::SimpleMath::Vector2::Zero
	);

	//	背景画像の描画
	spriteBath->Draw
	(
		m_tableBackGroundTexture,
		DirectX::SimpleMath::Vector2(-130.0f,-100.0f)
	);

	//	背景画像の描画
	m_resultBackGround->Draw();

	if (m_resultBackGround->Update())
	{
		//	スコアを描画する
		m_scoreOutPut->Draw();

		//	スコアが一緒になったら描画する
		if (m_judScore)
		{
			//	評価を描画
			m_valucationScore->Draw();
			//	スコアが一緒になったら描画する
			m_pushSpase->Draw();
			//	判子を描画する
			m_pushSeal->Draw();
		}
	}

	//	描画を終了する
	spriteBath->End();
}

/// <summary>
/// 終了処理
/// </summary>
void ResultScene::Finalize()
{

}

/// <summary>
///	デバイス依存のリソース
/// </summary>
void ResultScene::CreateDeviceDependentResources()
{
	//	スクリーンリソース
	m_screen = MyLib::ScreenResources::GetInstance();
	//	リソーシーズ
	m_resorces = MyLib::ResourcesData::GetInstance();
	//	背景画像
	m_backGroundTexture = m_resorces->GatShaderResourceView(L"Result_table");
	//	背景画像
	m_tableBackGroundTexture = m_resorces->GatShaderResourceView(L"tableBackGround");
	//	スコアアウトプット
	m_scoreOutPut	  =	 std::make_unique<ScoreOutPut>();
	//	スコアの初期化
	m_scoreOutPut->Initialize();
	//	評価スコア
	m_valucationScore = std::make_unique<ValuationScore>();
	//	スコアの評価値を初期化する
	m_valucationScore->Initialize(m_stageNum, PlayInfo::GetInstance()->GetScore());

	//	PUSHUIキーの作成
	m_pushSpase = std::make_unique<OutPutResultUI>
		(
			m_resorces->GatShaderResourceView(L"ResultUISpaceKey"),
			PUSH_SPACE_POSITION,
			PUSH_SPACE_ORIGIN_POSITION
		);

	m_pushSeal = std::make_unique<PushSeal>
		(
			DirectX::SimpleMath::Vector2(640.0f, -200.0f),
			DirectX::SimpleMath::Vector2(135.0f, 201.0f)
		);
		
	//	背景画像
	m_resultBackGround = std::make_unique<ResultBackGround>();
	//	初期化処理
	m_resultBackGround->Initialize();
	
	//	曲を再生する
	AudioManager::GetInstance()->PlaySoundEffectBGM(L"ResultBGM");
}
