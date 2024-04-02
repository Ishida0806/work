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

    // ��ʃ��[�h��ݒ肷��֐��iTRUE�F�t���X�N���[���j
    void SetFullscreenState(BOOL value);

    //  �}�E�X�J�[�\���̕\��
    void ShowMouseCursor(bool isShow);

private:

    void Update(DX::StepTimer const& timer);
    void Render();

    void Clear();

    void CreateDeviceDependentResources();
    void CreateWindowSizeDependentResources();
    //  �v���W�F�N�V�������쐬����
    void CreateProjection();
    //  �V�[�����쐬
    void CreateScene();
    //  �f�[�^�̍쐬
    void AddSound();
    void AddTexture();
    void AddModel();

    //  �ϐ�
private:
    //  �X�N���[�����\�[�X
    MyLib::ScreenResources*                 m_screens;
    //  ���\�[�X�f�[�^
    MyLib::ResourcesData*                   m_resourcesData;
    //  �G���v�X�h�^�C��
    MyLib::ElapsedTime*                     m_elapsed;
    //  �C���v�b�g�V�X�e��
    MyLib::InputSystem*                     m_input;
    //  �I�[�f�B�I�}�l�[�W��
    AudioManager*                           m_audioManager;
    // �f�o�C�X���\�[�X
    DX::DeviceResources*                    m_deviceResources;
    // �X�N���[��
    DX::StepTimer                           m_timer;
    // �V�[���}�l�[�W���[
    std::unique_ptr<SceneManager>           m_sceneManager;
    //  �V�[���J�ڂ̍ۂ̕`��G�t�F�N�g
    std::unique_ptr<ChageSceneEffect>       m_changeSceneEffect;
    //  ��ʃ��[�h   �iTRUE�ɏ�����
    BOOL m_fullscreen;
public:

    //  �V�[���}�l�[�W���[���擾����
    SceneManager*            GetSceneManager()       const { return m_sceneManager.get();}
    //  �`�F���W�G�t�F�N�g���擾����
    ChageSceneEffect*        GetChangeEffect()       const { return m_changeSceneEffect.get();}
};
