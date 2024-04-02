//
//		File Name ： StageBackGround.h
//		Production： 2023/11/01
//		Author　　： 石田 恭一	
// 
#pragma once

class StageBackGround final
{
	//	定数
public:
	//	夜明け前の色
	static const DirectX::SimpleMath::Vector4 DAWN_COLOR;
	//	朝の色
	static const DirectX::SimpleMath::Vector4 MORNING_COLOR;
	//	昼ごろの色
	static const DirectX::SimpleMath::Vector4 DAYTIME_COLOR;
	//	夜の色
	static const DirectX::SimpleMath::Vector4 NIGHT_COLOR;

	//	構造体
public:
	//	コンストバッファー
	struct ConstBuffer
	{
		DirectX::SimpleMath::Vector4	Diffuse;
	};

	//	変数
private:
	//	ピクセルシェーダ
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_PS_Stage;
	//	コンストバッファ
	Microsoft::WRL::ComPtr<ID3D11Buffer>	  m_cBuffer;
	//	画像
	ID3D11ShaderResourceView*				  m_backGroundTexture;
	//	ステージ用のコンストバッファー
	ConstBuffer								  m_stageBackGroundConstBuffer;
	//	目標色
	DirectX::SimpleMath::Vector4			  m_targetColor;
	//	ステージシーンの最大ステージ量
	int										  m_maxStageNum;

	//	関数
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="backGroundTexture">画像</param>
	StageBackGround(ID3D11ShaderResourceView* backGroundTexture, const int& maxStage);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~StageBackGround();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update(const int& selectStage);

	/// <summary>
	/// 描画する
	/// </summary>
	void Draw();

	/// <summary>
	/// 終了処理
	/// </summary>
	void Finalize();
};