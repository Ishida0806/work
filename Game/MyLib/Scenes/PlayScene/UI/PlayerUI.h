//
//		File Name ： PlayerUI.h
//		Production： 2023/10/2
//		Author　　： 石田 恭一
// 
#pragma once
#include "Game/MyLib/GameDatas/IUI.h"

interface IUI;
class Player;

class PlayerUI : public IUI
{
	//	アクセサ
public:

	//	体力の状態を取得する
	int GetState()	const { return static_cast<int>(m_hpState); }
	//	プレイヤーのポインターを設定する
	void SetPlayer(Player* player);

	//	ステート
private:

	//	HP状態によるステート
	enum class HP_RENDER_STATE
	{
		FINE = 0,
		LITTLE_BAD = 1,
		BAD = 2,
		DEAD = 3
	};

	//	変数
private:
	//	プレイヤー
	Player*					m_pPlayer;
	//	スクリーンリソース
	MyLib::ScreenResources* m_screen;
	//	リソーシーズデータ
	MyLib::ResourcesData*   m_resources;
	//	調子の良いプレイヤーの画像
	ID3D11ShaderResourceView* m_goodPlayer;
	//	調子の悪いプレイヤーの画像
	ID3D11ShaderResourceView* m_badPlayer;
	//	調子の少し悪いプレイヤーの画像
	ID3D11ShaderResourceView* m_littleBadPlayer;
	//	死んだときの画像
	ID3D11ShaderResourceView* m_deathPlayer;
	//	体力の状態
	HP_RENDER_STATE			 m_hpState;

	//	関数
public:

	PlayerUI();
	~PlayerUI();

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
	//	体力の状態によって描画を変える
	void RenderHPState();
};