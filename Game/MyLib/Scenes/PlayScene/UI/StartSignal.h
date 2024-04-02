//
//		File Name ： StartSignal.h
//		Production： 2023/10/17
//		Author　　： 石田 恭一	
//	
#pragma once

#include "Game/MyLib/GameDatas/IUI.h"

interface IUI;

class StartSignal : public IUI
{
	//	定数
public:

	//	GO画像の真ん中の座標
	static const DirectX::SimpleMath::Vector2 ORIGIN_GO_POSITION;
	//	READY画像の真ん中の座標
	static const DirectX::SimpleMath::Vector2 ORIGIN_READY_POSITION;
	//	画像のデフォルトの大きさ
	static const DirectX::SimpleMath::Vector2 BASE_SCALE;
	//	GOが出たときに少し揺れる
	static const float						  SHAKE_GO_POSITION;

	//	アクセサ
public:

	/// <summary>
	/// フェードに必要な時間を設定する
	/// </summary>
	/// <param name="pFadeTimer">:フェードタイムのポインター</param>
	/// <param name="fadeMaxTime">:マックス時間</param>
	void SetFadeTime(float* pFadeTimer,float fadeMaxTime);

	//	ステート状態
private:

	enum class STATE
	{
		IDLE = 0,
		READY = 1,
		GO = 2,
		FINISH = 3
	};

	//	変数
private:
	//	スクリーンリソース
	MyLib::ScreenResources*   m_screen;
	//	リソーシーズデータ
	MyLib::ResourcesData*	  m_resources;
	//	READY画像の座標
	DirectX::SimpleMath::Vector2 m_readyPosition;
	//	GO画像の座標
	DirectX::SimpleMath::Vector2 m_goPosition;
	//	READY画像
	ID3D11ShaderResourceView* m_readyUi;
	//	GO画像
	ID3D11ShaderResourceView* m_goUi;
	//	次に行くポインターのカウント
	float*					  m_pNextCount;
	//	次に行くカウントのマックス値
	float					  m_maxFadeCount;
	//	描画するステート
	STATE					  m_renderState;

	//	関数
public:

	StartSignal();
	~StartSignal();

	//	初期化処理
	void Initialize() override;
	//	更新処理
	void Update(const DX::StepTimer& timer) override;
	//	描画する
	void Draw() override;

	//	プライベート関数
private:
	//	デバイス依存のリソースの初期化
	void CreateDeviceDependentResources();
};