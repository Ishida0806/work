//
//		File Name ： HitRenderer.h
//		Production： 2023/8/02
//		Author　　： 石田 恭一
//
#pragma once

class HitRenderer
{
	//	定数
public:
	// エフェクト表示時間
	static const float RENDER_TIME;
private:

	MyLib::ScreenResources*														  m_screen;

	DirectX::BasicEffect*														  m_batchEffect;											
	ID3D11InputLayout*															  m_inputLayout;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>							  m_texture;
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_primitiveBatch;
private:

	// 座標
	DirectX::SimpleMath::Vector3 m_pos;		
	// 表示時間
	float m_timer;		
	//	使用状態
	bool m_used;
	//	画像の大きさ
	float m_size;
	//	大きさを記憶する
	float m_memorySize;

	//	アクセサ
public:

	inline bool IsUsed()	const { return m_used; }

public:
	HitRenderer(Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture, float size);
	~HitRenderer();

	void Update();
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj,float size = 1.0f);
	void RenderBillBoard(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj, const DirectX::SimpleMath::Vector3& eye,const DirectX::SimpleMath::Vector3& unit);

	void HitEffect(DirectX::SimpleMath::Vector3 position, const bool& scaleFlag);
};