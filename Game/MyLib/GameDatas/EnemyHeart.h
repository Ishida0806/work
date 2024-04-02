//
//		File Name ： EnemyHeart.h
//		Production： 2023/8/02
//		Author　　： 石田 恭一
//
#pragma once
class Enemy;

class EnemyHeart
{
	//	定数
public:
	// エフェクト表示時間
	static const float RENDER_TIME;

	//	変数
private:
	//	スクリーンリソース
	MyLib::ScreenResources*														  m_screen;
	//	バッチエフェクト
	DirectX::BasicEffect*														  m_batchEffect;	
	//	インプットレイアウト
	ID3D11InputLayout*															  m_inputLayout;
	//	ハート画像
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>							  m_heartTexture;
	//	ハートの背景画像
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>							  m_coverHeartTexture;
	//	プリミティブバッチ
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_primitiveBatch;
	//	敵
	Enemy*																		  m_enemy;
	// 経過時間
	float m_elapsedTime;		
	//	画像の大きさ
	float m_size;

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="enemy">敵</param>
	EnemyHeart(Enemy* enemy);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyHeart();

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="timer">タイマー</param>
	void Update(const DX::StepTimer& timer);

	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="view">ビュー</param>
	/// <param name="proj">プロジェクション</param>
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj);
};