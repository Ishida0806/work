//
//		File Name �F TitleScene.h
//		Production�F 2023/9/14
//		Author�@�@�F �Γc ����
//
#pragma once

#include "Game/MyLib/GameDatas/Fade.h"
#include "Game/MyLib/GameDatas/Config.h"
#include "TitleStringUI.h"
#include "../IScene.h"
#include "TitleLogo.h"
#include "TitleUI.h"
#include "Gear.h"

interface IScene;
class Game;

class TitleScene : public IScene
{
    //  �萔
public:

    //  �^�C�g���̃t�F�[�h����
    static const float TITLE_FADE_ARRIVE_TIME;

    //  �C�[�i��
public:

    enum class STATE
    {
        IDLE    = 0,
        PLAY    = 1,
        CONFIG  = 2,
        END     = 3,

        NONE
    };

    //  �ϐ�
private:
    //  �Q�[��
    Game*                                         m_game;
    //	���\�[�X�f�[�^
    MyLib::ResourcesData*                         m_resources;
    //  �X�N���[�����\�[�X
    MyLib::ScreenResources*                       m_screen;
    //  �|�[�Y
    std::unique_ptr<Config>                       m_config;
    //  �^�C�g�����S
    std::unique_ptr<TitleLogo>                    m_titleLogo;
    //  �M�A
    std::vector<std::unique_ptr<Gear>>            m_gears;
    //  �^�C�g���̕�������
    std::vector<std::unique_ptr<TitleStringUI>>   m_titleStringUIs;
    //  �w�i�̍��W
    DirectX::SimpleMath::Vector2                  m_backPos;
    //  UI�̍��W
    DirectX::SimpleMath::Vector2                  m_uiPos;   
    //  �I���܂łɏ������Ԃ��҂�
    float                                         m_finTime;
    //  �t�F�[�h�̎���
    float                                         m_fadeTime;
    //  �A���t�@�l
    float                                         m_uiAlfa;
    //  �b��
    float                                         m_elapsedTime;
    //  �w�i
    ID3D11ShaderResourceView*                     m_backGroundTexture;
    //  UI
    ID3D11ShaderResourceView*                     m_uiTexture;
    //  �X�e�[�g
    STATE                                         m_state;
    //  �X�^�[�g�t�F�[�h
    bool                                          m_fadeStart;
    //  �A���t�@�X�e�[�g
    bool                                          m_alfaValue;
    //  �Q�[���I���������ꂽ���H
    bool                                          m_isFin;

    //  �֐�
public:
    // �R���X�g���N�^
    TitleScene(Game* game);
    // �f�X�g���N�^
    ~TitleScene();
    // ����������
    void Initialize() override;
    // �X�V����
    void Update(const DX::StepTimer& timer) override;
    // �`�揈��
    void Render() override;
    // �I������
    void Finalize() override;


    //�v���C�x�[�g�֐�
private:
    //  �e�X�e�[�g���X�V����
    void UpdateState(const DX::StepTimer& timer);

    void UpdateIdle();
    void UpdatePlay(const DX::StepTimer& timer);
    void UpdateConfig();
    void UpdateEnd();

    void RenderUI();


 private:

    void CreateDeviceDependentResources();
};
