//
//		File Name ： HitRenderer.cpp
//		Production： 2023/8/02
//		Author　　： 石田 恭一
// 
//		当たった際のエフェクトの描画を行うクラス
//
#include "pch.h"
#include "HitRenderer.h"

const float HitRenderer::RENDER_TIME = 22.0f;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="texture">画像</param>
/// <param name="size">サイズ</param>
HitRenderer::HitRenderer(Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture, float size)
	:m_texture(texture),
	m_size(size),
	m_memorySize(size),
	m_used(false)
{
	m_screen = MyLib::ScreenResources::GetInstance();
	m_batchEffect = m_screen->GetBasicEffect();
	m_inputLayout = m_screen->GetInputLayout();
	// プリミティブバッチの作成
	m_primitiveBatch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>>(m_screen->GetDeviceContext());
}

/// <summary>
/// デストラクタ
/// </summary>
HitRenderer::~HitRenderer()
{
}

/// <summary>
/// 更新処理
/// </summary>
void HitRenderer::Update()
{
	if (!m_used)	return;
	
	m_timer--;
	if (m_timer <= 0)
		m_used = false;
}

/// <summary>
/// 描画する
/// </summary>
/// <param name="view">ビュー</param>
/// <param name="proj">プロジェクション</param>
/// <param name="size">引かれる || 足される数</param>
void HitRenderer::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj, float size)
{
	if (!m_used)	return;

	auto context = m_screen->GetDeviceContext();

	float alpha = (m_timer / RENDER_TIME * 200.0f) * 0.01f;
	m_size *= size;

	// 頂点情報
	DirectX::VertexPositionColorTexture vertex[4] =
	{
		DirectX::VertexPositionColorTexture(DirectX::SimpleMath::Vector3(  m_size,  0.5f,  m_size),DirectX::SimpleMath::Vector4(1.0f, 1.0f, 1.0f,  alpha), DirectX::SimpleMath::Vector2(0.0f, 0.0f)),
		DirectX::VertexPositionColorTexture(DirectX::SimpleMath::Vector3( -m_size, 0.5f,   m_size),DirectX::SimpleMath::Vector4(1.0f, 1.0f, 1.0f,  alpha), DirectX::SimpleMath::Vector2(1.0f, 0.0f)),
		DirectX::VertexPositionColorTexture(DirectX::SimpleMath::Vector3( -m_size, 0.5f,  -m_size),DirectX::SimpleMath::Vector4(1.0f, 1.0f, 1.0f,  alpha), DirectX::SimpleMath::Vector2(1.0f, 1.0f)),
		DirectX::VertexPositionColorTexture(DirectX::SimpleMath::Vector3(  m_size,  0.5f, -m_size),DirectX::SimpleMath::Vector4(1.0f, 1.0f, 1.0f,  alpha), DirectX::SimpleMath::Vector2(0.0f, 1.0f)),
	};

	// 加算合成
	context->OMSetBlendState(m_screen->GetCommonState()->Additive(), nullptr, 0xFFFFFFFF);
	// 深度バッファはなし
	context->OMSetDepthStencilState(m_screen->GetCommonState()->DepthNone(), 0);
	// カリングは左周り
	context->RSSetState(m_screen->GetCommonState()->CullCounterClockwise());

	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::CreateTranslation(m_pos);

	m_batchEffect->SetWorld(world);
	m_batchEffect->SetView(view);
	m_batchEffect->SetProjection(proj);
	m_batchEffect->SetTexture(m_texture.Get());
	m_batchEffect->Apply(context);
	context->IASetInputLayout(m_inputLayout);

	m_primitiveBatch->Begin();
	m_primitiveBatch->DrawQuad(vertex[0], vertex[1], vertex[2], vertex[3]);
	m_primitiveBatch->End();
}

/// <summary>
/// ビルボードを描画する
/// </summary>
/// <param name="view">ビュー</param>
/// <param name="proj">プロジェクション</param>
/// <param name="eye">アイ</param>
/// <param name="unit">軸</param>
void HitRenderer::RenderBillBoard(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj, const DirectX::SimpleMath::Vector3& eye, const DirectX::SimpleMath::Vector3& unit)
{
	if (!m_used)	return;

	//	ビルボード行列の作成
	DirectX::SimpleMath::Matrix bilboard = DirectX::SimpleMath::Matrix::CreateBillboard(DirectX::SimpleMath::Vector3::Zero, m_pos - eye, unit);
	//	180回転させる為の行列(右手座標系から左手座標系への変換)
	DirectX::SimpleMath::Matrix rotY = DirectX::SimpleMath::Matrix::Identity;
	rotY._11 = -1;
	rotY._33 = -1;

	//	ビールボード行列を180で回転してあげる
	bilboard = rotY * bilboard;

	auto context = m_screen->GetDeviceContext();

	float alpha = (m_timer / RENDER_TIME * 200.0f) * 0.01f;
	m_size -= 0.03f;

	// 頂点情報
	DirectX::VertexPositionColorTexture vertex[4] =
	{
		DirectX::VertexPositionColorTexture(DirectX::SimpleMath::Vector3( m_size,  0.5f, m_size), DirectX::SimpleMath::Vector4(1.0f, 1.0f, 1.0f,  alpha), DirectX::SimpleMath::Vector2(0.0f, 0.0f)),
		DirectX::VertexPositionColorTexture(DirectX::SimpleMath::Vector3(-m_size,  0.5f, m_size),DirectX::SimpleMath::Vector4(1.0f, 1.0f, 1.0f,  alpha), DirectX::SimpleMath::Vector2(1.0f, 0.0f)),
		DirectX::VertexPositionColorTexture(DirectX::SimpleMath::Vector3(-m_size,  0.5f, -m_size),DirectX::SimpleMath::Vector4(1.0f, 1.0f, 1.0f,  alpha), DirectX::SimpleMath::Vector2(1.0f, 1.0f)),
		DirectX::VertexPositionColorTexture(DirectX::SimpleMath::Vector3( m_size,  0.5f, -m_size), DirectX::SimpleMath::Vector4(1.0f, 1.0f, 1.0f,  alpha), DirectX::SimpleMath::Vector2(0.0f, 1.0f)),
	};

	// 加算合成
	context->OMSetBlendState(m_screen->GetCommonState()->Additive(), nullptr, 0xFFFFFFFF);
	// 深度バッファはなし
	context->OMSetDepthStencilState(m_screen->GetCommonState()->DepthNone(), 0);
	// カリングは左周り
	context->RSSetState(m_screen->GetCommonState()->CullCounterClockwise());

	bilboard *= DirectX::SimpleMath::Matrix::CreateTranslation(m_pos);

	m_batchEffect->SetWorld(bilboard);
	m_batchEffect->SetView(view);
	m_batchEffect->SetProjection(proj);
	m_batchEffect->SetTexture(m_texture.Get());
	m_batchEffect->Apply(context);
	context->IASetInputLayout(m_inputLayout);

	m_primitiveBatch->Begin();
	m_primitiveBatch->DrawQuad(vertex[0], vertex[1], vertex[2], vertex[3]);
	m_primitiveBatch->End();
}


/// <summary>
/// エフェクトヒット時の処理
/// </summary>
/// <param name="position">座標</param>
/// <param name="scaleFlag">大きさ</param>
void HitRenderer::HitEffect(DirectX::SimpleMath::Vector3 position, const bool& scaleFlag)
{
	m_used = true;
	m_pos  = position;
	m_timer= RENDER_TIME;

	//	大きさを変えるフラグがONなら変える
	if(scaleFlag)			m_size = m_memorySize * 2.0f;
	else 					m_size = m_memorySize;
}
