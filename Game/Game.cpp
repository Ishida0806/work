//
// Game.cpp
//
#include "pch.h"
#include "Game.h"
#include "Common/DeviceResources.h"

//////////////////////////�V�[���ǉ�/////////////////////////////////
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
    //  �X�N���[�����\�[�X�̍쐬
    m_screens         = MyLib::ScreenResources::GetInstance();
    //  �C���v�b�g�V�X�e���̍쐬
    m_input           = MyLib::InputSystem::GetInstance();
    //  ���\�[�V�[�Y�f�[�^�̍쐬
    m_resourcesData   = MyLib::ResourcesData::GetInstance();
    //  �G���v�X�h�^�C���̍쐬
    m_elapsed         = MyLib::ElapsedTime::GetInstance();
    //  �I�[�f�B�I�}�l�[�W���̍쐬
    m_audioManager = AudioManager::GetInstance();
    //  �p�����[�^�}�l�[�W���[�̍쐬
    m_paramManager = MyLib::ParamManager::GetInstane();
    //�@�f�o�C�X���\�[�X�̍쐬
    m_deviceResources = m_screens->GetDeviceResources();

    m_deviceResources->RegisterDeviceNotify(this);
}

// Initialize the Direct3D resources required to run.
void Game::Initialize(HWND window, int width, int height)
{
    //m_timer.SetFixedTimeStep(true);
    //m_timer.SetTargetElapsedSeconds(1.0 / 60); // 60fps�ɐݒ�
    //  �E�C���h�E�̑傫����ݒ肷��
    m_deviceResources->SetWindow(window, width, height);
    //  �f�o�C�X���\�[�X������������
    m_deviceResources->CreateDeviceResources();
    //  �f�o�C�X�ˑ��̃��\�[�X�̏�����
    CreateDeviceDependentResources();

    m_deviceResources->CreateWindowSizeDependentResources();
    CreateWindowSizeDependentResources();

    //  �}�E�X�J�[�\��������
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
    //  �o�ߎ��Ԃ��擾����
    float elapsedTime = float(timer.GetElapsedSeconds());
    //  �o�ߎ��Ԃ�ݒ肷��
    m_elapsed->SetElapsedTime(elapsedTime);
    //  ���͏����X�V����
    m_input->Update();
    //  �����X�V����
    m_audioManager->Update();
    //  �V�[���}�l�[�W���[���X�V����
    m_sceneManager->Update(timer);
    //  �V�[����ς���ۂ̃G�t�F�N�g�̍X�V
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
    // �o�b�N�o�b�t�@���N���A����
    Clear();
    // �p�t�H�[�}���X�J�n�C�x���g
    m_deviceResources->PIXBeginEvent(L"Render");
    //�����ɃV�[���Ăяo��
    m_sceneManager->Render();
    //  �V�[����ς���ۂ̕`��
    m_changeSceneEffect->DrawEffect();

#ifdef _DEBUG

    // fps�̕\��
    std::wostringstream oss, time;
    oss << "fps:" << m_timer.GetFramesPerSecond();
    m_screens->RenderDebugFont(oss.str().c_str(), SimpleMath::Vector2(0.0f, 220.0f));
    //  �o�ߎ��Ԃ�\������
    time << "elapsedTime :" << m_elapsed->GetElapsedTime();
    m_screens->RenderDebugFont(time.str().c_str(), SimpleMath::Vector2(0.0f, 240.0f));

#endif // _DEBUG

    m_deviceResources->PIXEndEvent();

    // �p�t�H�[�}���X�I���C�x���g
    m_deviceResources->PIXEndEvent();

    // �V�K�t���[����`�悷��
    m_deviceResources->Present();
}

// Helper method to clear the back buffers.
void Game::Clear()
{
    // �f�o�C�X���\�[�X
    m_deviceResources->PIXBeginEvent(L"Clear");

    // �r���[���N���A����
    auto context      = m_deviceResources->GetD3DDeviceContext();
    auto renderTarget = m_deviceResources->GetRenderTargetView();
    auto depthStencil = m_deviceResources->GetDepthStencilView();

    context->ClearRenderTargetView(renderTarget, Colors::CornflowerBlue);
    context->ClearDepthStencilView(depthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    context->OMSetRenderTargets(1, &renderTarget, depthStencil);

    // �r���[�|�[�g��ݒ肷��
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

    //------------------------------------�ǉ�---------------------------------------//

  // �t���X�N���[�������ׂ�
    BOOL fullscreen = FALSE;

    m_deviceResources->GetSwapChain()->GetFullscreenState(&fullscreen, nullptr);
    // �t���X�N���[������������Ă��܂������̏���
    if (m_fullscreen != fullscreen)
    {
        m_fullscreen = fullscreen;
        // ResizeBuffers�֐����Ăяo��
        m_deviceResources->CreateWindowSizeDependentResources();
    }

    //------------------------------------�ǉ�---------------------------------------//
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

//  �t���X�N���[���ɂ���
void Game::SetFullscreenState(BOOL value)
{
    m_fullscreen = value;
    m_deviceResources->GetSwapChain()->SetFullscreenState(m_fullscreen, nullptr);
    if (value) m_deviceResources->CreateWindowSizeDependentResources();
}

//  �}�E�X�J�[�\����\������
void Game::ShowMouseCursor(bool isShow)
{
    if (isShow)
    {
        //  �}�E�X�J�[�\����\��
        ShowCursor(TRUE);
    }
    else
    {
        //  �}�E�X�J�[�\��������
        ShowCursor(FALSE);
    }
}

#pragma endregion

#pragma region Direct3D Resources
// These are the resources that depend on the device.
void Game::CreateDeviceDependentResources()
{
    //  �X�N���[�����\�[�X�̏�����
    m_screens->Initialize();
    //  ���\�[�X�̓ǂݍ���
    m_resourcesData->Initialize();
    //  �V�[���}�l�[�W���[�̍쐬
    m_sceneManager = std::make_unique<SceneManager>();
    //  ����������
    m_audioManager->Initialize();
    //  ���\�[�X�̃��[�h
    m_paramManager->LoadData();
    // BGM��SE��o�^����
    AddSound();
    //  �摜��ǉ�����
    AddTexture();
    //  ���f����ǉ�
    AddModel();
    //  �V�[����ς����̃G�t�F�N�g�̕`��
    m_changeSceneEffect = std::make_unique<ChageSceneEffect>(this);
    //  ���������s��
    m_changeSceneEffect->Initialize();
    //  �v���W�F�N�V�������쐬
    CreateProjection();
    //  �V�[�����쐬
    CreateScene();
}

// Allocate all memory resources that change on a window SizeChanged event.
void Game::CreateWindowSizeDependentResources()
{
    // �f�o�C�X�Ɉˑ������I�u�W�F�N�g������������(�E�B���h�E�T�C�Y����Ɨ�����)
    int width, height;

    // �E�B���h�E�̊���T�C�Y���擾����
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

    // �E�B���h�E�T�C�Y���擾����
    RECT size = m_screens->GetDeviceResources()->GetOutputSize();

    float Near = 0.1f;
    float Far = 1200.0f;

    // �v���W�F�N�V�����𐶐�����
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
///     �V�[�����쐬
/// </summary>
void Game::CreateScene()
{
   m_sceneManager->ChangeScene<TitleScene>(this);
   //m_sceneManager->ChangeScene<StageSelectScene>(this);
   //m_sceneManager->ChangeScene<PlayScene>(this, m_screens);
   //m_sceneManager->ChangeScene<ResultScene>(this);
}

/// <summary>
/// �T�E���h��ǉ�
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
/// �摜��ǉ�����
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
/// ���f����ǉ�
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
