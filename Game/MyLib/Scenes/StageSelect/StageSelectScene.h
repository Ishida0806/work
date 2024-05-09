//
//		File Name ： StageSelectScene.h
//		Production： 2023/9/14
//		Author　　： 石田 恭一
//
#pragma once
#include "Game/MyLib/Scenes/IScene.h"

#include "Game/MyLib/Scenes/StageSelect/Bird.h"
#include "Game/MyLib/Scenes/StageSelect/Enemy2D.h"
#include "Game/MyLib/Scenes/StageSelect/Door2D.h"
#include "Game/MyLib/Scenes/StageSelect/KeyFont.h"
#include "Game/MyLib/Scenes/StageSelect/Player2D.h"
#include "Game/MyLib/Scenes/StageSelect/StageCircle.h"
#include "Game/MyLib/Scenes/StageSelect/StarManager.h"
#include "Game/MyLib/Scenes/StageSelect/StageBackGround.h"

class Game;
class Door2D;
class Enemy2D;
class KeyFont;


interface IScene;

class StageSelectScene : public IScene
{
	//	定数
public:
	//	クールタイム
	static const float						  COOL_TIME;
	//	デフォルトの大きさ
	static const float						  BASE_SCALE;
	//	フェード時の目標大きさ
	static const float						  FADE_TARGET_SCALE;
	//	距離
	static const float						  DISTANCE;
	//	ラープ時の速度
	static const float						  LERP_SPEED;
	//	ラープ時の大きさの速度
	static const float						  LERP_SCALE_SPEED;
	//	アニメーションタイム
	static const float						  FIN_TIME;


	//	enum
public:
	//	ステージ数
	enum class CHOOSE_STAGE
	{
		STAGE_1 = 0,
		STAGE_2 = 1,
		STAGE_3 = 2,
		STAGE_4 = 3,

		OverID
	};
	//	KEY入力でどちらに動いたか
	enum class MOVE_DIRECTION
	{
		CENTER = 0,
		RIGHT = 1,
		LEFT = 2,
	};

	//	変数
private:
	//	ゲーム
	Game*										m_game;
	//	敵の2D画像
	std::vector<std::unique_ptr<Enemy2D>>		m_enemies2D;
	//	ドアの2D画像
	std::vector<std::unique_ptr<Door2D>>		m_doors2D;
	//	ステージ円
	std::vector<std::unique_ptr<StageCircle>>   m_stageCircles;
	//	キー画像
	std::vector<std::unique_ptr<KeyFont>>		m_keys2D;
	//	背景画像のクラス
	std::unique_ptr<StageBackGround>		    m_stageBackGround;
	//	星々
	std::unique_ptr<StarManager>			    m_starManeger;
	//	鳥
	std::unique_ptr<Bird>						m_bird;
	//	プレイヤーの2D
	std::unique_ptr<Player2D>					m_player2D;
	//	スクリーンリソース
	MyLib::ScreenResources*						m_screen;
	//	リソース
	MyLib::ResourcesData*					    m_resorces;
	//	バックグラウンドの枠
	ID3D11ShaderResourceView*				    m_stageSelectBackGroundStageFrameworkTexture;
	//	エスケープキー
	ID3D11ShaderResourceView*				    m_escTexture;
	//	画像の大きさ
	DirectX::SimpleMath::Vector2				m_doorScale;
	//	ステートが終わったか
	bool									    m_preMove;
	//	
	bool									    m_isChanegeScene;
	//	経過時間
	float									    m_elapsedTime;
	//	アニメーションのクールタイム
	float									    m_moveCoolTime;
	//	チェンジステート 
	CHOOSE_STAGE							    m_stageState;
	//	どちらに動いたか
	MOVE_DIRECTION							    m_isMoveDirection;

	//	関数
public:
	StageSelectScene(Game* game);
	~StageSelectScene();

	//	初期化処理
	void Initialize() override;
	//	更新処理
	void Update(const DX::StepTimer& timer) override;
	//	描画処理
	void Render() override;
	//	終了処理	
	void Finalize() override;

	//	プライベート関数
private:
	//	デバイス依存のリソース
	void CreateDeviceDependentResources();
	//	UIを更新する
	void UpdateUIs(const DX::StepTimer& timer);
	//	キーが押されたら
	void InputKey();
	//	プレイヤーの情報を更新する
	void UpdatePlayer();
	//	プレイシーンにいくためのドアを更新する
	void UpdateDoor(const DX::StepTimer& timer);
	//	ステート状態を更新
	void CheckState();
	//	キーの指示を描画する
	void RenderKey();
	//	ドアを描画する
	void RenderDoor();
};