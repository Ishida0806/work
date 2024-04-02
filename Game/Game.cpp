//
// Game.cpp
//
#include "pch.h"
#include "Game.h"
#include "Common/DeviceResources.h"

//////////////////////////シーン追加/////////////////////////////////
#include "Game/MyLib/Scenes/TitleScene/TitleScene.h"
#include "Game/MyLib/Scenes/StageSelect/StageSelectScene.h"
#include "Game/MyLib/Scenes/PlayScene/PlayScene.h"
#include "Game/MyLib/Scenes/ResultScene/ResultScene.h"
/////////////////////////////////////////////////////////////////////

extern void ExitGame() noexcept;

using namespace DirectX;

using Microsoft::WRL::ComPtr;

Game::Game() noexcept(false)
    :m_sceneManager(nullptr),
    m_screens(nullptr),
    m_deviceResources(nullptr),
    m_fullscreen(TRUE)
{
    //  スクリーンリソースの作成
    m_screens         = MyLib::ScreenResources::GetInstance();
    //  インプットシステムの作成
    m_input           = MyLib::InputSystem::GetInstance();
    //  リソーシーズデータの作成
    m_resourcesData   = MyLib::ResourcesData::GetInstance();
    //  エレプスドタイムの作成
    m_elapsed         = MyLib::ElapsedTime::GetInstance();
    //  オーディオマネージャの作成
    m_audioManager = AudioManager::GetInstance();
    //  パラメータマネージャーの作成
    m_paramManager = MyLib::ParamManager::GetInstane();
    //　デバイスリソースの作成
    m_deviceResources = m_screens->GetDeviceResources();

    m_deviceResources->RegisterDeviceNotify(this);
}

// Initialize the Direct3D resources required to run.
void Game::Initialize(HWND window, int width, int height)
{
    //m_timer.SetFixedTimeStep(true);
    //m_timer.SetTargetElapsedSeconds(1.0 / 60); // 60fpsに設定
    //  ウインドウの大きさを設定する
    m_deviceResources->SetWindow(window, width, height);
    //  デバイスリソースを初期化する
    m_deviceResources->CreateDeviceResources();
    //  デバイス依存のリソースの初期化
    CreateDeviceDependentResources();

    m_deviceResources->CreateWindowSizeDependentResources();
    CreateWindowSizeDependentResources();

    //  マウスカーソルを消す
    ShowMouseCursor(TRUE);
}

#pragma region Frame Update
// Executes the basic game loop.
void Game::Tick()
{
    m_timer.Tick([&]()
    {
        Update(m_timer);
    });

    Render();
}

// Updates the world.
void Game::Update(DX::StepTimer const& timer)
{
    //  経過時間を取得する
    float elapsedTime = float(timer.GetElapsedSeconds());
    //  経過時間を設定する
    m_elapsed->SetElapsedTime(elapsedTime);
    //  入力情報を更新する
    m_input->Update();
    //  音を更新する
    m_audioManager->Update();
    //  シーンマネージャーを更新する
    m_sceneManager->Update(timer);
    //  シーンを変える際のエフェクトの更新
    m_changeSceneEffect->Update(timer);
}
#pragma endregion

#pragma region Frame Render
// Draws the scene.
void Game::Render()
{
    // Don't try to render anything before the first Update.
    if (m_timer.GetFrameCount() == 0)
    {
        return;
    }
    // バックバッファをクリアする
    Clear();
    // パフォーマンス開始イベント
    m_deviceResources->PIXBeginEvent(L"Render");
    //ここにシーン呼び出し
    m_sceneManager->Render();
    //  シーンを変える際の描画
    m_changeSceneEffect->DrawEffect();

#ifdef _DEBUG

    // fpsの表示
    std::wostringstream oss, time;
    oss << "fps:" << m_timer.GetFramesPerSecond();
    m_screens->RenderDebugFont(oss.str().c_str(), SimpleMath::Vector2(0.0f, 220.0f));
    //  経過時間を表示する
    time << "elapsedTime :" << m_elapsed->GetElapsedTime();
    m_screens->RenderDebugFont(time.str().c_str(), SimpleMath::Vector2(0.0f, 240.0f));

#endif // _DEBUG

    m_deviceResources->PIXEndEvent();

    // パフォーマンス終了イベント
    m_deviceResources->PIXEndEvent();

    // 新規フレームを描画する
    m_deviceResources->Present();
}

// Helper method to clear the back buffers.
void Game::Clear()
{
    // デバイスリソース
    m_deviceResources->PIXBeginEvent(L"Clear");

    // ビューをクリアする
    auto context      = m_deviceResources->GetD3DDeviceContext();
    auto renderTarget = m_deviceResources->GetRenderTargetView();
    auto depthStencil = m_deviceResources->GetDepthStencilView();

    context->ClearRenderTargetView(renderTarget, Colors::CornflowerBlue);
    context->ClearDepthStencilView(depthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    context->OMSetRenderTargets(1, &renderTarget, depthStencil);

    // ビューポートを設定する
    auto const viewport = m_deviceResources->GetScreenViewport();
    context->RSSetViewports(1, &viewport);

    m_deviceResources->PIXEndEvent();
}
#pragma endregion

#pragma region Message Handlers
// Message handlers
void Game::OnActivated()
{
    // TODO: Game is becoming active window.
}

void Game::OnDeactivated()
{
    // TODO: Game is becoming background window.
}

void Game::OnSuspending()
{
    // TODO: Game is being power-suspended (or minimized).
}

void Game::OnResuming()
{
    m_timer.ResetElapsedTime();

    // TODO: Game is being power-resumed (or returning from minimize).
}

void Game::OnWindowMoved()
{
    auto const r = m_deviceResources->GetOutputSize();
    m_deviceResources->WindowSizeChanged(r.right, r.bottom);

    //------------------------------------追加---------------------------------------//

  // フルスクリーンか調べる
    BOOL fullscreen = FALSE;

    m_deviceResources->GetSwapChain()->GetFullscreenState(&fullscreen, nullptr);
    // フルスクリーンが解除されてしまった時の処理
    if (m_fullscreen != fullscreen)
    {
        m_fullscreen = fullscreen;
        // ResizeBuffers関数を呼び出す
        m_deviceResources->CreateWindowSizeDependentResources();
    }

    //------------------------------------追加---------------------------------------//
}

void Game::OnDisplayChange()
{
    m_deviceResources->UpdateColorSpace();
}

void Game::OnWindowSizeChanged(int width, int height)
{
    if (!m_deviceResources->WindowSizeChanged(width, height))
        return;

    CreateWindowSizeDependentResources();

    // TODO: Game window is being resized.
}


// Properties
void Game::GetDefaultSize(int& width, int& height) const noexcept
{
    // TODO: Change to desired default window size (note minimum size is 320x200).
    width = 1280;
    height = 720;
}

//  フルスクリーンにする
void Game::SetFullscreenState(BOOL value)
{
    m_fullscreen = value;
    m_deviceResources->GetSwapChain()->SetFullscreenState(m_fullscreen, nullptr);
    if (value) m_deviceResources->CreateWindowSizeDependentResources();
}

//  マウスカーソルを表示する
void Game::ShowMouseCursor(bool isShow)
{
    if (isShow)
    {
        //  マウスカーソルを表示
        ShowCursor(TRUE);
    }
    else
    {
        //  マウスカーソルを消す
        ShowCursor(FALSE);
    }
}

#pragma endregion

#pragma region Direct3D Resources
// These are the resources that depend on the device.
void Game::CreateDeviceDependentResources()
{
    //  スクリーンリソースの初期化
    m_screens->Initialize();
    //  リソースの読み込み
    m_resourcesData->Initialize();
    //  シーンマネージャーの作成
    m_sceneManager = std::make_unique<SceneManager>();
    //  初期化する
    m_audioManager->Initialize();
    //  リソースのロード
    m_paramManager->LoadData();
    // BGMとSEを登録する
    AddSound();
    //  画像を追加する
    AddTexture();
    //  モデルを追加
    AddModel();
    //  シーンを変える先のエフェクトの描画
    m_changeSceneEffect = std::make_unique<ChageSceneEffect>(this);
    //  初期化を行う
    m_changeSceneEffect->Initialize();
    //  プロジェクションを作成
    CreateProjection();
    //  シーンを作成
    CreateScene();
}

// Allocate all memory resources that change on a window SizeChanged event.
void Game::CreateWindowSizeDependentResources()
{
    // デバイスに依存したオブジェクトを初期化する(ウィンドウサイズから独立した)
    int width, height;

    // ウィンドウの既定サイズを取得する
    GetDefaultSize(width, height);
    m_screens->SetScreenSize(width, height);
}

void Game::OnDeviceLost()
{
    // TODO: Add Direct3D resource cleanup here.
}

void Game::CreateProjection()
{
    using namespace DirectX::SimpleMath;

    // ウィンドウサイズを取得する
    RECT size = m_screens->GetDeviceResources()->GetOutputSize();

    float Near = 0.1f;
    float Far = 1200.0f;

    // プロジェクションを生成する
    m_screens->SetProjectionMatrix
    (
        Matrix::CreatePerspectiveFieldOfView
        (
            DirectX::XMConvertToRadians(45.0f),
            static_cast<float>(size.right) / static_cast<float>(size.bottom),
            Near,
            Far
        )
    );
}

/// <summary>
///     シーンを作成
/// </summary>
void Game::CreateScene()
{
   m_sceneManager->ChangeScene<TitleScene>(this);
   //m_sceneManager->ChangeScene<StageSelectScene>(this);
   //m_sceneManager->ChangeScene<PlayScene>(this, m_screens);
   //m_sceneManager->ChangeScene<ResultScene>(this);
}

/// <summary>
/// サウンドを追加
/// </summary>
void Game::AddSound()
{
    m_audioManager->AddSoundEffect(L"PlaySE01_Accept");
    m_audioManager->AddSoundEffect(L"PlaySE02_MoveTitle");
    m_audioManager->AddSoundEffect(L"PlayTitleBGM");
    m_audioManager->AddSoundEffect(L"PlayStageBGM");
    m_audioManager->AddSoundEffect(L"PlayGameBgm01");
    m_audioManager->AddSoundEffect(L"Swing_Sword_SE01");
    m_audioManager->AddSoundEffect(L"Swing_Sword_SE02");
    m_audioManager->AddSoundEffect(L"Hit_Bullet_SE01");
    m_audioManager->AddSoundEffect(L"Hit_RF_Bullet_SE01");
    m_audioManager->AddSoundEffect(L"Hit_Player_SE01");
    m_audioManager->AddSoundEffect(L"SHOT_BULLET_SE01");
    m_audioManager->AddSoundEffect(L"SHOT_BULLET_SE02");
    m_audioManager->AddSoundEffect(L"Deth_AnimationSE01");
    m_audioManager->AddSoundEffect(L"Open_SE01");
    m_audioManager->AddSoundEffect(L"Close_SE01");
    m_audioManager->AddSoundEffect(L"RecoverSE01");
    m_audioManager->AddSoundEffect(L"PlayStartSE01");
    m_audioManager->AddSoundEffect(L"PlayStartSE02");
    m_audioManager->AddSoundEffect(L"ResultBGM");
    m_audioManager->AddSoundEffect(L"Result_PushSeal");
    m_audioManager->AddSoundEffect(L"Result_NumberChange");
    m_audioManager->AddSoundEffect(L"PowerUP");
    m_audioManager->AddSoundEffect(L"HaveWeapon");
    m_audioManager->AddSoundEffect(L"inCard");
    m_audioManager->AddSoundEffect(L"powerCardUP");
    m_audioManager->AddSoundEffect(L"healthCardUP");
    m_audioManager->AddSoundEffect(L"speedCardUP");
    m_audioManager->AddSoundEffect(L"expUP");
    m_audioManager->AddSoundEffect(L"levelUP");
    m_audioManager->AddSoundEffect(L"PlayLoseBGM");
    m_audioManager->AddSoundEffect(L"PlayWinBGM");
}

/// <summary>
/// 画像を追加する
/// </summary>
void Game::AddTexture()
{
    MyLib::ResourcesData::GetInstance()->AddShaderResourceView(L"FloorTexture");
    MyLib::ResourcesData::GetInstance()->AddShaderResourceView(L"gear");
    MyLib::ResourcesData::GetInstance()->AddShaderResourceView(L"BlackTexture");
    MyLib::ResourcesData::GetInstance()->AddShaderResourceView(L"HitTextures");
    MyLib::ResourcesData::GetInstance()->AddShaderResourceView(L"HitBulletTextures");
    MyLib::ResourcesData::GetInstance()->AddShaderResourceView(L"titleLogo");
    MyLib::ResourcesData::GetInstance()->AddShaderResourceView(L"title_back");
    MyLib::ResourcesData::GetInstance()->AddShaderResourceView(L"title_UI");
    MyLib::ResourcesData::GetInstance()->AddShaderResourceView(L"title_UI_PlayGame");
    MyLib::ResourcesData::GetInstance()->AddShaderResourceView(L"title_UI_PlayGame_Off");
    MyLib::ResourcesData::GetInstance()->AddShaderResourceView(L"title_UI_EndGame");
    MyLib::ResourcesData::GetInstance()->AddShaderResourceView(L"title_UI_EndGame_Off");
    MyLib::ResourcesData::GetInstance()->AddShaderResourceView(L"title_UI_Config");
    MyLib::ResourcesData::GetInstance()->AddShaderResourceView(L"title_UI_Config_Off");
    MyLib::ResourcesData::GetInstance()->AddShaderResourceView(L"Door_Easy");
    MyLib::ResourcesData::GetInstance()->AddShaderResourceView(L"Door_Normal");
    MyLib::ResourcesData::GetInstance()->AddShaderResourceView(L"Door_Hard");
    MyLib::ResourcesData::GetInstance()->AddShaderResourceView(L"Door_Extra");
    MyLib::ResourcesData::GetInstance()->AddShaderResourceView(L"player2d");
    MyLib::ResourcesData::GetInstance()->AddShaderResourceView(L"stageSelectScene");
    MyLib::ResourcesData::GetInstance()->AddShaderResourceView(L"EasyFont");
    MyLib::ResourcesData::GetInstance()->AddShaderResourceView(L"NormalFont");
    MyLib::ResourcesData::GetInstance()->AddShaderResourceView(L"HardFont");
    MyLib::ResourcesData::GetInstance()->AddShaderResourceView(L"EndresFont");
    MyLib::ResourcesData::GetInstance()->AddShaderResourceView(L"Key_Holding_D");
    MyLib::ResourcesData::GetInstance()->AddShaderResourceView(L"Key_Holding_A");
    MyLib::ResourcesData::GetInstance()->AddShaderResourceView(L"NormalEnemyTexure");
    MyLib::ResourcesData::GetInstance()->AddShaderResourceView(L"TackleEnemyTexure");
    MyLib::ResourcesData::GetInstance()->AddShaderResourceView(L"Key_Holding_A");
    MyLib::ResourcesData::GetInstance()->AddShaderResourceView(L"Button");
    MyLib::ResourcesData::GetInstance()->AddShaderResourceView(L"Bar");
    MyLib::ResourcesData::GetInstance()->AddShaderResourceView(L"GuideKey");
    MyLib::ResourcesData::GetInstance()->AddShaderResourceView(L"PauseUITextureSE");
    MyLib::ResourcesData::GetInstance()->AddShaderResourceView(L"PauseUITextureBGM");
    MyLib::ResourcesData::GetInstance()->AddShaderResourceView(L"EscapeUI");
    MyLib::ResourcesData::GetInstance()->AddShaderResourceView(L"Bad_Player");
    MyLib::ResourcesData::GetInstance()->AddShaderResourceView(L"Little_Bad");
    MyLib::ResourcesData::GetInstance()->AddShaderResourceView(L"Good_Player");
    MyLib::ResourcesData::GetInstance()->AddShaderResourceView(L"Death_Player");
    MyLib::ResourcesData::GetInstance()->AddShaderResourceView(L"HPBar");
    MyLib::ResourcesData::GetInstance()->AddShaderResourceView(L"StageSelect_BackGround");
    MyLib::ResourcesData::GetInstance()->AddShaderResourceView(L"Ready_UI");
    MyLib::ResourcesData::GetInstance()->AddShaderResourceView(L"Go_UI");
    MyLib::ResourcesData::GetInstance()->AddShaderResourceView(L"score");
    MyLib::ResourcesData::GetInstance()->AddShaderResourceView(L"number");
    MyLib::ResourcesData::GetInstance()->AddShaderResourceView(L"Sky_Fine");
    MyLib::ResourcesData::GetInstance()->AddShaderResourceView(L"Sky_Cloudy");
    MyLib::ResourcesData::GetInstance()->AddShaderResourceView(L"Sky_Evening");
    MyLib::ResourcesData::GetInstance()->AddShaderResourceView(L"Sky_Night");
    MyLib::ResourcesData::GetInstance()->AddShaderResourceView(L"StageFramework");
    MyLib::ResourcesData::GetInstance()->AddShaderResourceView(L"star");
    MyLib::ResourcesData::GetInstance()->AddShaderResourceView(L"Stage_Circle");
    MyLib::ResourcesData::GetInstance()->AddShaderResourceView(L"PauseUITextureEndGame");
    MyLib::ResourcesData::GetInstance()->AddShaderResourceView(L"PauseUITextureTitle");
    MyLib::ResourcesData::GetInstance()->AddShaderResourceView(L"PauseUITextureSegment");
    MyLib::ResourcesData::GetInstance()->AddShaderResourceView(L"ResultUISpaceKey");
    MyLib::ResourcesData::GetInstance()->AddShaderResourceView(L"valuationS");
    MyLib::ResourcesData::GetInstance()->AddShaderResourceView(L"valuationA");
    MyLib::ResourcesData::GetInstance()->AddShaderResourceView(L"valuationB");
    MyLib::ResourcesData::GetInstance()->AddShaderResourceView(L"valuationC");
    MyLib::ResourcesData::GetInstance()->AddShaderResourceView(L"Result_ScoreBackGround");
    MyLib::ResourcesData::GetInstance()->AddShaderResourceView(L"Result_table");
    MyLib::ResourcesData::GetInstance()->AddShaderResourceView(L"Numbers");
    MyLib::ResourcesData::GetInstance()->AddShaderResourceView(L"push_seal");
    MyLib::ResourcesData::GetInstance()->AddShaderResourceView(L"tableBackGround");
    MyLib::ResourcesData::GetInstance()->AddShaderResourceView(L"PlayScoreBackGround");
    MyLib::ResourcesData::GetInstance()->AddShaderResourceView(L"PlayerUIBackGround");
    MyLib::ResourcesData::GetInstance()->AddShaderResourceView(L"Bird");
    MyLib::ResourcesData::GetInstance()->AddShaderResourceView(L"sun");
    MyLib::ResourcesData::GetInstance()->AddShaderResourceView(L"map");
    MyLib::ResourcesData::GetInstance()->AddShaderResourceView(L"playerMap");
    MyLib::ResourcesData::GetInstance()->AddShaderResourceView(L"enemyMap");
    MyLib::ResourcesData::GetInstance()->AddShaderResourceView(L"cure");
    MyLib::ResourcesData::GetInstance()->AddShaderResourceView(L"itemMap");
    MyLib::ResourcesData::GetInstance()->AddShaderResourceView(L"PowerUPCard");
    MyLib::ResourcesData::GetInstance()->AddShaderResourceView(L"HealthUPCard");
    MyLib::ResourcesData::GetInstance()->AddShaderResourceView(L"SpeedUPCard");
    MyLib::ResourcesData::GetInstance()->AddShaderResourceView(L"leverUpCardBackGround");
    MyLib::ResourcesData::GetInstance()->AddShaderResourceView(L"EXPmax");
    MyLib::ResourcesData::GetInstance()->AddShaderResourceView(L"ColourlessBoard");
    MyLib::ResourcesData::GetInstance()->AddShaderResourceView(L"PinchEffect");
    MyLib::ResourcesData::GetInstance()->AddShaderResourceView(L"WaveDisplay");
    MyLib::ResourcesData::GetInstance()->AddShaderResourceView(L"EnemyHeart");
    MyLib::ResourcesData::GetInstance()->AddShaderResourceView(L"EnemyCoverHeart");
}

/// <summary>
/// モデルを追加
/// </summary>
void Game::AddModel()
{
    MyLib::ResourcesData::GetInstance()->AddModel(L"floor");
    MyLib::ResourcesData::GetInstance()->AddModel(L"cursorTop");
    MyLib::ResourcesData::GetInstance()->AddModel(L"cursorBottom");
    MyLib::ResourcesData::GetInstance()->AddModel(L"skydoam");
    MyLib::ResourcesData::GetInstance()->AddModel(L"Sord");
    MyLib::ResourcesData::GetInstance()->AddModel(L"playerHead");
    MyLib::ResourcesData::GetInstance()->AddModel(L"playerLeftArm");
    MyLib::ResourcesData::GetInstance()->AddModel(L"playerLeftLeg");
    MyLib::ResourcesData::GetInstance()->AddModel(L"playerRightArm");
    MyLib::ResourcesData::GetInstance()->AddModel(L"playerRightLeg");
    MyLib::ResourcesData::GetInstance()->AddModel(L"playerBody");
    MyLib::ResourcesData::GetInstance()->AddModel(L"enemy");
    MyLib::ResourcesData::GetInstance()->AddModel(L"normalEnemy");
    MyLib::ResourcesData::GetInstance()->AddModel(L"normalEnemyLeg");
    MyLib::ResourcesData::GetInstance()->AddModel(L"enemy_tackle");
    MyLib::ResourcesData::GetInstance()->AddModel(L"bossEnemy");
    MyLib::ResourcesData::GetInstance()->AddModel(L"wall");
    MyLib::ResourcesData::GetInstance()->AddModel(L"cloak");
    MyLib::ResourcesData::GetInstance()->AddModel(L"arrow");
    MyLib::ResourcesData::GetInstance()->AddModel(L"capsuleTop");
    MyLib::ResourcesData::GetInstance()->AddModel(L"capsuleBottom");
    MyLib::ResourcesData::GetInstance()->AddModel(L"recovery");
    MyLib::ResourcesData::GetInstance()->AddModel(L"bat");
    MyLib::ResourcesData::GetInstance()->AddModel(L"armPower");
}

void Game::OnDeviceRestored()
{
    CreateDeviceDependentResources();
    CreateWindowSizeDependentResources();
}
#pragma endregion
