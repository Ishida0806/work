//
//		File Name ： PlayerExperiencePointUI.h
//		Production： 2023/11/30
//		Author　　： 石田 恭一	
//	
#pragma once

class Player;

class PlayerExperiencePointUI final
{
	//	定数
public:

	//	MAX画像の座標
	static const DirectX::SimpleMath::Vector2	MAX_POSITION;
	//	体力バー用の座標
	static const float							EXP_POS;
	//	体力バーのX座標
	static const int							EXP_IX;
	//	体力バーのY座標
	static const int							EXP_IY;
	//	体力バーの高さ
	static const int							EXP_IH;


	//	変数
private:
	//	プレイヤー
	Player*					  m_player;
	//	バー画像
	ID3D11ShaderResourceView* m_barTexture;
	//	MAX画像
	ID3D11ShaderResourceView* m_maxTexture;
	//	経験値バー
	float						  m_exBar;

	//	関数
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="player">プレイヤー<</param>
	PlayerExperiencePointUI(Player* player);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~PlayerExperiencePointUI();

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="timer">タイマー</param>
	void Update(const DX::StepTimer& timer);

	/// <summary>
	/// 描画する
	/// </summary>
	void Draw();
};