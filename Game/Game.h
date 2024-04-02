//
// Game.h
//

#pragma once
#include "Game/MyLib/Scenes/SceneManager.h"
#include "Game/MyLib/GameDatas/ChageSceneEffect.h"

// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game final : public DX::IDeviceNotify
{
public:

    Game() noexcept(false);
    ~Game() = default;

    Game(Game&&) = default;
    Game& operator= (Game&&) = default;

    Game(Game const&) = delete;
    Game& operator= (Game const&) = delete;

    // Initialization and management
    void Initialize(HWND window, int width, int height);

    // Basic game loop
    void Tick();

    // IDeviceNotify
    void OnDeviceLost() override;
    void OnDeviceRestored() override;

    // Messages
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowMoved();
    void OnDisplayChange();
    void OnWindowSizeChanged(int width, int height);

    // Properties
    void GetDefaultSize( int& width, int& height ) const noexcept;

    // 画面モードを設定する関数（TRUE：フルスクリーン）
    void SetFullscreenState(BOOL value);

    //  マウスカーソルの表示
    void ShowMouseCursor(bool isShow);

private:

    void Update(DX::StepTimer const& timer);
    void Render();

    void Clear();

    void CreateDeviceDependentResources();
    void CreateWindowSizeDependentResources();
    //  プロジェクションを作成する
    void CreateProjection();
    //  シーンを作成
    void CreateScene();
    //  データの作成
    void AddSound();
    void AddTexture();
    void AddModel();

    //  変数
private:
    //  スクリーンリソース
    MyLib::ScreenResources*                 m_screens;
    //  リソースデータ
    MyLib::ResourcesData*                   m_resourcesData;
    //  エレプスドタイム
    MyLib::ElapsedTime*                     m_elapsed;
    //  インプットシステム
    MyLib::InputSystem*                     m_input;
    //  オーディオマネージャ
    AudioManager*                           m_audioManager;
    // デバイスリソース
    DX::DeviceResources*                    m_deviceResources;
    // スクリーン
    DX::StepTimer                           m_timer;
    // シーンマネージャー
    std::unique_ptr<SceneManager>           m_sceneManager;
    //  シーン遷移の際の描画エフェクト
    std::unique_ptr<ChageSceneEffect>       m_changeSceneEffect;
    //  画面モード   （TRUEに初期化
    BOOL m_fullscreen;
public:

    //  シーンマネージャーを取得する
    SceneManager*            GetSceneManager()       const { return m_sceneManager.get();}
    //  チェンジエフェクトを取得する
    ChageSceneEffect*        GetChangeEffect()       const { return m_changeSceneEffect.get();}
};
