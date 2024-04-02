//
//		File Name ： PlayerHPBar.h
//		Production： 2023/10/3
//		Author　　： 石田 恭一
// 
#pragma once

#include "Game/MyLib/GameDatas/IUI.h"

class Player;
interface IUI;

class PlayerHPBar : public IUI
{
	//	定数
public:
	//	赤
	static const DirectX::SimpleMath::Color RED;
	//	黄色
	static const DirectX::SimpleMath::Color YELLOW;
	//	緑
	static const DirectX::SimpleMath::Color GREEN;
	//	体力バー用の座標
	static const int						HP_POS;
	//	体力バーのX座標
	static const int						HP_IX;
	//	体力バーのY座標
	static const int						HP_IY;
	//	体力バーの高さ
	static const int						HP_IH;
	//	誤差の範囲
	static const int						HP_RANGE_VALUE;


	//	アクセサ
public:

	//	プレイヤーがBAD状態になった
	inline bool IsBad() const { return m_isBad; }

	//	プレイヤーのポインターを設定する
	void SetPlayer(Player* player);
	//	体力のステート状態を取得する
	void SetHPState(int state);

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

	Player*						m_pPlayer;
	//	スクリーンリソース
	MyLib::ScreenResources*		m_screen;
	//	リソーシーズデータ
	MyLib::ResourcesData*		m_resources;
	//	プレイヤーの体力バー
	ID3D11ShaderResourceView*	m_hpPlayerBarUI;
	//	BAD状態か
	bool						m_isBad;
	//	プレイヤーの体力をバーで表示したもの
	int							m_hpBar;
	//	プレイヤーの体力をバーで表示したものの現在
	int							m_nowHpBar;
	//	体力状態のステート
	HP_RENDER_STATE				m_hpState;

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	PlayerHPBar();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~PlayerHPBar();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize()						override;

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="timer">タイマー</param>
	void Update(const DX::StepTimer& timer)	override;

	/// <summary>
	/// 描画する
	/// </summary>
	void Draw()								override;

	//	プライベート関数
private:

	//	デバイス依存のリソースの初期化
	void CreateDeviceDependentResources();
	//	バーの描画
	void RenderBar();
};