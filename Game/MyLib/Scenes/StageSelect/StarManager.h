//
//		File Name ： StarManager.h
//		Production： 2023/11/02
//		Author　　： 石田 恭一	
// 
#pragma once

#include "Star.h"

class StarManager final
{
private:

	//	画像
	ID3D11ShaderResourceView*		   m_starTexture;
	//	星たちをまとめる
	std::vector<std::unique_ptr<Star>> m_stars;
	//	現在のステージ
	int								   m_stage;


public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="backGroundTexture">画像</param>
	StarManager(ID3D11ShaderResourceView* starTexture);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~StarManager();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="timer">タイマー</param>
	/// <param name="selectStage">ステージセレクトナンバー</param>
	void Update(const DX::StepTimer& timer, const int& selectStage);

	/// <summary>
	/// 描画する
	/// </summary>
	void Draw();

	/// <summary>
	/// 終了処理
	/// </summary>
	void Finalize();
};