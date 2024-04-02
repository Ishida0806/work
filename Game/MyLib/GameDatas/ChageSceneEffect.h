//
//		File Name ： ChageSceneEffect.h
//		Production： 2023/1/17
//		Author　　： 石田 恭一	
//
#pragma once
#include "ChangeEffect.h"
class Game;

class ChageSceneEffect final
{
	//	列挙型
public:


	//	アクセサ
public:	

	/// <summary>
	/// シーン遷移のエフェクトの要求を設定
	/// </summary>
	/// <param name="requestType">リクエストタイプ</param>
	/// <param name="fadeType">ファードタイプ</param>
	void RequestChangeEffect(const ChangeEffect::ChangeSceneType& requestType, const ChangeEffect::ChangeSceneFadeType& fadeType);

	//	変数
private:

	//	ゲーム
	Game*									   m_game;
	//	シーン遷移のエフェクト達
	std::vector<std::unique_ptr<ChangeEffect>> m_fadeEffects;

	//関数
public:

	/// <summary>
	/// 初期化処理
	/// </summary>
	/// <param name="game">ゲーム</param>
	ChageSceneEffect(Game* game);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ChageSceneEffect();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="timer">タイマー</param>
	void Update(const DX::StepTimer& timer);

	/// <summary>
	/// エフェクトの描画
	/// </summary>
	void DrawEffect();
};