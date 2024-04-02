
#pragma once

#include <list>
#include "HitParticle.h"


class BulletHitParticle
{
	//	アクセサ
public:

	//	使用状態を取得する
	inline bool IsUsed()	const { return m_isUsed; }

	//	構造体
public:

	//データ受け渡し用コンスタントバッファ送信
	struct ConstBuffer
	{
		DirectX::SimpleMath::Matrix		matWorld;
		DirectX::SimpleMath::Matrix		matView;
		DirectX::SimpleMath::Matrix		matProj;
		DirectX::SimpleMath::Vector4	Diffuse;
	};

	//	定数
public:

	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;

	//	変数
private:
	//	パーティクル
	std::list<std::unique_ptr<HitParticle>>										  m_particles;
	// 入力レイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout>									  m_inputLayout;
	// 頂点シェーダ
	Microsoft::WRL::ComPtr<ID3D11VertexShader>									  m_vertexShader;
	// ピクセルシェーダ
	Microsoft::WRL::ComPtr<ID3D11PixelShader>									  m_pixelShader;
	// ジオメトリシェーダ
	Microsoft::WRL::ComPtr<ID3D11GeometryShader>								  m_geometryShader;
	//	コンスタントバッファー
	Microsoft::WRL::ComPtr<ID3D11Buffer>										  m_constantBuffer;
	// プリミティブバッチ
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_primitevBatch;
	//	頂点情報
	std::vector<DirectX::VertexPositionColorTexture>							  m_vertices;
	//	エフェクト
	ID3D11ShaderResourceView*													  m_particleTexture;
	//	目標座標
	DirectX::SimpleMath::Vector3												  m_tagetPosition;
	//	使用状態
	bool																		  m_isUsed;
	//	経過時間
	float																		  m_elapsedTime;

	//	関数
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	BulletHitParticle();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~BulletHitParticle();

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

	/// <summary>
	/// ビルボードで描画を行う
	/// </summary>
	/// <param name="view">ビュー</param>
	/// <param name="proj">プロジェクション</param>
	/// <param name="eye">カメラの位置</param>
	/// <param name="up">軸</param>
	void Render(
		const DirectX::SimpleMath::Matrix& view, 
		const DirectX::SimpleMath::Matrix& proj,
		const DirectX::SimpleMath::Vector3& eye, 
		const DirectX::SimpleMath::Vector3& unit
	);


	/// <summary>
	/// 衝突時に呼び出す
	/// </summary>
	/// <param name="position"座標</param>
	void Hit(DirectX::SimpleMath::Vector3 position);

private:

	/// <summary>
	/// シェーダーを作成
	/// </summary>
	void CreateSharder();

};