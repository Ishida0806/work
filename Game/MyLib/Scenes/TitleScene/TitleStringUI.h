//
//		File Name ： TitleStringUI.h
//		Production： 2023/11/11
//		Author　　： 石田 恭一
//
#pragma once

#include "TitleUI.h"

class TitleStringUI : public TitleUI
{
	//	定数
public:

	//	揺らす大きさ
	static const float					      SHAKE_TEXTURE;
	//	揺らす速さ
	static const float					      SHAKE_SPEED;
	//	角度を戻す速度
	static const float						  MOVE_BACKANGLE_SPEED;
	//	プレイゲームの真ん中座標
	static const DirectX::SimpleMath::Vector2 PLAYGAME_ORIGIN_POSITION;
	//	コンフィグの真ん中座標
	static const DirectX::SimpleMath::Vector2 CONFIG_ORIGIN_POSITION;
	//	エンドゲームの真ん中座標
	static const DirectX::SimpleMath::Vector2 ENDGAME_ORIGIN_POSITION;


	//	列挙型
public:

	//	文字タイプ
	enum class StirngType
	{
		PLay = 0,
		Config = 1,
		End = 2,

		OverID = 3		
	};


	//	変数
private:

	//	画像
	ID3D11ShaderResourceView*	 m_texture;
	//	OFF時
	ID3D11ShaderResourceView*	 m_offTexture;
	//	座標
	DirectX::SimpleMath::Vector2 m_position;
	//	真ん中の座標
	DirectX::SimpleMath::Vector2 m_originPosition;
	//	大きさ
	DirectX::SimpleMath::Vector2 m_scale;
	//	タイトルの状態
	int							 m_state;
	//	角度
	float						 m_angle;
	//	オフセット値
	float						 m_offsetX;
	//	タイプ
	int							 m_type;


	//	関数
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="texture">画像</param>
	/// <param name="texture">OFF時の画像</param>
	/// <param name="position">座標</param>
	/// <param name="index">番号</param>
	TitleStringUI(
		ID3D11ShaderResourceView* texture,
		ID3D11ShaderResourceView* offTexture,
		const DirectX::SimpleMath::Vector2& position,
		const int& index
	);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~TitleStringUI();


	void Update(const int& state);
	void Draw();

private:
	void SelectUI();
};