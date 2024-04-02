//
//		File Name ： TitleScene.h
//		Production： 2023/9/14
//		Author　　： 石田 恭一
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
    //  定数
public:

    //  タイトルのフェード時間
    static const float TITLE_FADE_ARRIVE_TIME;

    //  イーナム
public:

    enum class STATE
    {
        IDLE    = 0,
        PLAY    = 1,
        CONFIG  = 2,
        END     = 3,

        NONE
    };

    //  変数
private:
    //  ゲーム
    Game*                                         m_game;
    //	リソースデータ
    MyLib::ResourcesData*                         m_resources;
    //  スクリーンリソース
    MyLib::ScreenResources*                       m_screen;
    //  ポーズ
    std::unique_ptr<Config>                       m_config;
    //  タイトルロゴ
    std::unique_ptr<TitleLogo>                    m_titleLogo;
    //  ギア
    std::vector<std::unique_ptr<Gear>>            m_gears;
    //  タイトルの文字たち
    std::vector<std::unique_ptr<TitleStringUI>>   m_titleStringUIs;
    //  背景の座標
    DirectX::SimpleMath::Vector2                  m_backPos;
    //  UIの座標
    DirectX::SimpleMath::Vector2                  m_uiPos;   
    //  終わるまでに少し時間を稼ぐ
    float                                         m_finTime;
    //  フェードの時間
    float                                         m_fadeTime;
    //  アルファ値
    float                                         m_uiAlfa;
    //  秒数
    float                                         m_elapsedTime;
    //  背景
    ID3D11ShaderResourceView*                     m_backGroundTexture;
    //  UI
    ID3D11ShaderResourceView*                     m_uiTexture;
    //  ステート
    STATE                                         m_state;
    //  スタートフェード
    bool                                          m_fadeStart;
    //  アルファステート
    bool                                          m_alfaValue;
    //  ゲーム終了が押されたか？
    bool                                          m_isFin;

    //  関数
public:
    // コンストラクタ
    TitleScene(Game* game);
    // デストラクタ
    ~TitleScene();
    // 初期化処理
    void Initialize() override;
    // 更新処理
    void Update(const DX::StepTimer& timer) override;
    // 描画処理
    void Render() override;
    // 終了処理
    void Finalize() override;


    //プライベート関数
private:
    //  各ステートを更新する
    void UpdateState(const DX::StepTimer& timer);

    void UpdateIdle();
    void UpdatePlay(const DX::StepTimer& timer);
    void UpdateConfig();
    void UpdateEnd();

    void RenderUI();


 private:

    void CreateDeviceDependentResources();
};
