//
//		File Name ： StageCircle.h
//		Production： 2023/11/02
//		Author　　： 石田 恭一	
// 
#pragma once

class StageCircle
{
private:


	//	画像
	ID3D11ShaderResourceView*						 m_texture;
	//	座標
	DirectX::SimpleMath::Vector2					 m_position;
	//	色
	DirectX::SimpleMath::Color						 m_color;
	//	識別子
	int												 m_ID;

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="texture">画像</param>
	/// <param name="position">座標</param>
	/// <param name="ID">識別子</param>
	StageCircle(ID3D11ShaderResourceView* texture,const DirectX::SimpleMath::Vector2& position,const int& ID);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~StageCircle();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="timer">タイマー</param>
	/// <param name="stageNum">ステージ番号</param>
	void Update(const DX::StepTimer& timer, const int& stageNum);

	/// <summary>
	/// 描画する
	/// </summary>
	void Draw();

	/// <summary>
	/// 終了処理
	/// </summary>
	void Finalize();
};