//
//		File Name ： ResultScene.h
//		Production： 2023/9/14
//		Author　　： 石田 恭一
//
#pragma once
#include "Game/MyLib/Scenes/IScene.h"
#include "Game/MyLib/Scenes/ResultScene/PushSeal.h"
#include "Game/MyLib/Scenes/ResultScene/ScoreOutPut.h"
#include "Game/MyLib/Scenes/ResultScene/OutPutResultUI.h"
#include "Game/MyLib/Scenes/ResultScene/ValuationScore.h"
#include "Game/MyLib/Scenes/ResultScene/ResultBackGround.h"

interface IScene;

class ResultScene : public IScene
{
	//	定数
public:

	//	簡単な難易度の加算文章
	static const float EASY_ADDITION;
	//	通常の難易度の加算文章
	static const float NORMAL_ADDITION;
	//	難しい難易度の加算文章
	static const float HARD_ADDITION;
	//	エンドレス難易度の加算文章
	static const float ENDRES_ADDITION;
	//	PUSHUIの座標
	static const DirectX::SimpleMath::Vector2 PUSH_SPACE_POSITION;
	//	PUSHUIの真ん中座標
	static const DirectX::SimpleMath::Vector2 PUSH_SPACE_ORIGIN_POSITION;


	//	変数
private:
	//	ゲーム
	Game*								m_game;
	//	スクリーンリソース
	MyLib::ScreenResources*				m_screen;
	//	リソーシーズデータ
	MyLib::ResourcesData*				m_resorces;
	//  背景画像
	ID3D11ShaderResourceView*			m_backGroundTexture;
	//	背景のテーブル
	ID3D11ShaderResourceView*			m_tableBackGroundTexture;
	//	判子
	std::unique_ptr<PushSeal>			m_pushSeal;
	//	スコアアウトプット
	std::unique_ptr<ScoreOutPut>		m_scoreOutPut;
	//	スコアを評価する
	std::unique_ptr<ValuationScore>		m_valucationScore;
	//	指示キー
	std::unique_ptr<OutPutResultUI>		m_pushSpase;
	//	背景画像
	std::unique_ptr<ResultBackGround>	m_resultBackGround;
	//	終了時間
	float								m_finishedTime;
	//	セレクトされたステージ
	int									m_stageNum;
	//	フラグを決める
	bool								m_judScore;
	//	終了フラグ
	bool								m_isFinished;

	//	関数
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="game">ゲーム</param>
	ResultScene(Game* game, int stageSelect = 0);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ResultScene();

	//	初期化処理
	void Initialize() override;
	//	更新処理
	void Update(const DX::StepTimer& timer) override;
	//	描画処理
	void Render() override;
	//	終了処理	
	void Finalize() override;

private:

	//	デバイス依存のリソース
	void CreateDeviceDependentResources();
};
