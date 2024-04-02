
#include "pch.h"
#include "BulletHitParticle.h"

#include <VertexTypes.h>
#include "BinaryFile.h"
#include "Common/ReadData.h"

#define PARTICLE_NUM 12

const std::vector<D3D11_INPUT_ELEMENT_DESC> BulletHitParticle::INPUT_LAYOUT =
{
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0,	0,																			 D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0,	sizeof(DirectX::SimpleMath::Vector3),										 D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,		0,  sizeof(DirectX::SimpleMath::Vector3) + sizeof(DirectX::SimpleMath::Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 },
};


/// <summary>
/// コンストラクタ
/// </summary>
BulletHitParticle::BulletHitParticle()
	:m_particleTexture(nullptr),
	m_isUsed(false),
	m_elapsedTime(0.0f)
{
	//	シェーダーを作成
	CreateSharder();

	m_particleTexture = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"HitBulletTextures");
	// プリミティブバッチの作成
	m_primitevBatch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>>(MyLib::ScreenResources::GetInstance()->GetDeviceContext());

	//	要素の作成
	for (size_t i = 0; i < PARTICLE_NUM; ++i)
	{
		float pos = Utility::CreateRandom(-2.0f, 2.0f);
		float x	  = Utility::CreateRandom(-3.0f, 3.0f);
		float y	  = Utility::CreateRandom(-3.0f, 3.0f);

		float scale = 0.5f;

		m_particles.push_back(
			std::make_unique<HitParticle>(
				0.0f,
				DirectX::SimpleMath::Vector3(pos),																									// 基準座標
				DirectX::SimpleMath::Vector3(x, 5.0f, y), 																							// 速度
				DirectX::SimpleMath::Vector3(0.1f, 0.1f, 0.1f),																						// 加速度
				DirectX::SimpleMath::Vector3(scale), DirectX::SimpleMath::Vector3::Zero,															// 初期スケール、最終スケール
				DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f), DirectX::SimpleMath::Color(0.0f, 0.0f, 0.0f, 0.0f)								// 初期カラー、最終カラー
			)
		);
	}
}

/// <summary>
/// デストラクタ
/// </summary>
BulletHitParticle::~BulletHitParticle()
{
}

/// <summary>
/// 更新
/// </summary>
void BulletHitParticle::Update(const DX::StepTimer& timer)
{
	using namespace DirectX;

	//	使用状態じゃないなら処理を行わない
	if (!m_isUsed)	return;

	//	経過時間を足す
	m_elapsedTime += static_cast<float>(timer.GetElapsedSeconds());
	
	//	パーティクルを更新する
	for (auto& particle : m_particles)
		particle->Update(timer);

	//	時間経過で使用状態をオフにする
	if (m_elapsedTime >= 1.7f)
		m_isUsed = false;
}

/// <summary>
/// 描画する
/// </summary>
/// <param name="view">ビュー</param>
/// <param name="proj">プロジェクション</param>
void BulletHitParticle::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	//	使用状態じゃないなら処理を行わない
	if (!m_isUsed)	return;

	//	コンテキスト
	auto context = MyLib::ScreenResources::GetInstance()->GetDeviceContext();
	//	登録されている頂点をリセット
	m_vertices.clear();

	//	要素分の座標・色・大きさを入れる
	for (auto& particle : m_particles)
	{
		DirectX::VertexPositionColorTexture	 vPCT{};

		vPCT.position = particle->GetPosition();
		vPCT.color = particle->GetNowColor();
		vPCT.textureCoordinate = DirectX::SimpleMath::Vector2(particle->GetNowScale().x, 0.0f);

		m_vertices.push_back(vPCT);
	}

	//	表示する点がない場合は描画を終わる
	if (m_vertices.empty())		return;
	
	//	シェーダーに渡す追加のバッファを作成する。(ConstBuffer）
	ConstBuffer cbuff{};
	cbuff.matView = view.Transpose();
	cbuff.matProj = proj.Transpose();
	cbuff.matWorld = DirectX::SimpleMath::Matrix::Identity.Transpose();
	cbuff.Diffuse = DirectX::SimpleMath::Vector4::One;

	//	受け渡し用バッファの内容更新(ConstBufferからID3D11Bufferへの変換）
	context->UpdateSubresource(m_constantBuffer.Get(), 0, NULL, &cbuff, 0, 0);

	//	シェーダにバッファを渡す
	ID3D11Buffer* cbuffer[1] = { m_constantBuffer.Get() };
	context->VSSetConstantBuffers(0, 1, cbuffer);
	context->GSSetConstantBuffers(0, 1, cbuffer);
	context->PSSetConstantBuffers(0, 1, cbuffer);

	//	コモンステートを呼び出す
	DirectX::CommonStates* state = MyLib::ScreenResources::GetInstance()->GetCommonState();

	//	画像用サンプラー(画像自体の色)の登録
	ID3D11SamplerState* sampler[1] = { state->LinearWrap()};
	context->PSSetSamplers(0, 1, sampler);

	//	半透明描画指定
	ID3D11BlendState* blendstate = state->NonPremultiplied();

	// 透明判定処理
	context->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);

	// 深度バッファに書き込み参照する
	context->OMSetDepthStencilState(state->DepthDefault(), 0);

	// カリングは左周り
	context->RSSetState(state->CullNone());

	//	シェーダをセットする
	context->VSSetShader(m_vertexShader.Get(),	 nullptr, 0);
	context->GSSetShader(m_geometryShader.Get(), nullptr, 0);
	context->PSSetShader(m_pixelShader.Get(),	 nullptr, 0);

	//	ピクセルシェーダにテクスチャを登録する。
	context->PSSetShaderResources(0, 1, &m_particleTexture);

	//	インプットレイアウトの登録
	context->IASetInputLayout(m_inputLayout.Get());

	//	描画を開始する
	m_primitevBatch->Begin();

	//	描画処理
	m_primitevBatch->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &m_vertices[0], m_vertices.size());

	///	描画を終了する
	m_primitevBatch->End();

	//	シェーダの登録を解除しておく
	context->VSSetShader(nullptr, nullptr, 0);
	context->GSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);
}

/// <summary>
/// ビルボードで描画を行う
/// </summary>
/// <param name="view">ビュー</param>
/// <param name="proj">プロジェクション</param>
/// <param name="eye">カメラの位置</param>
/// <param name="up">軸</param>
void BulletHitParticle::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj, const DirectX::SimpleMath::Vector3& eye, const DirectX::SimpleMath::Vector3& unit)
{
	if (!m_isUsed)	return;

	//	コンテキスト
	auto context = MyLib::ScreenResources::GetInstance()->GetDeviceContext();
	//	距離を算出
	DirectX::SimpleMath::Vector3 cameraDirection = m_tagetPosition - eye;
	//	ビルボード行列の作成
	DirectX::SimpleMath::Matrix bilboard = DirectX::SimpleMath::Matrix::CreateBillboard(DirectX::SimpleMath::Vector3::Zero, cameraDirection, unit);
	//	180回転させる為の行列(右手座標系から左手座標系への変換)
	DirectX::SimpleMath::Matrix rotY = DirectX::SimpleMath::Matrix::Identity;
	rotY._11 *= -1;
	rotY._33 *= -1;
	//	ビールボード行列を180で回転してあげる
	bilboard = rotY * bilboard;
	//	登録されている頂点をリセット
	m_vertices.clear();

	//	正規化
	cameraDirection.Normalize();
	
	//	ソートを行う
	m_particles.sort(
		[&](const std::unique_ptr<HitParticle>& lhs, const std::unique_ptr<HitParticle>& rhs)
		{
			return cameraDirection.Dot(lhs->GetPosition() - eye) < cameraDirection.Dot(rhs->GetPosition() - eye);
		}
	);

	//	要素分の座標・色・大きさを入れる
	for (const auto& particle : m_particles)
	{
		DirectX::VertexPositionColorTexture	vPCT{};

		vPCT.position		   = static_cast<DirectX::XMFLOAT3>(particle->GetPosition());
		vPCT.color			   = static_cast<DirectX::XMFLOAT4>(particle->GetNowColor());
		vPCT.textureCoordinate = static_cast<DirectX::XMFLOAT2>(DirectX::SimpleMath::Vector2(particle->GetNowScale().x, particle->GetNowScale().y));

		m_vertices.push_back(vPCT);
	}

	//	表示する点がない場合は描画を終わる
	if (m_vertices.empty())		return;

	//	シェーダーに渡す追加のバッファを作成する。(ConstBuffer）
	ConstBuffer cbuff{};
	cbuff.matView	= view.Transpose();
	cbuff.matProj	= proj.Transpose();
	cbuff.matWorld	= DirectX::SimpleMath::Matrix::Identity.Transpose();
	cbuff.Diffuse	= DirectX::SimpleMath::Vector4::One;

	//	受け渡し用バッファの内容更新(ConstBufferからID3D11Bufferへの変換）
	context->UpdateSubresource(m_constantBuffer.Get(), 0, NULL, &cbuff, 0, 0);

	//	シェーダにバッファを渡す
	ID3D11Buffer* cbuffer[1] = { m_constantBuffer.Get() };
	context->VSSetConstantBuffers(0, 1, cbuffer);
	context->GSSetConstantBuffers(0, 1, cbuffer);
	context->PSSetConstantBuffers(0, 1, cbuffer);

	//	コモンステートを呼び出す
	DirectX::CommonStates* state = MyLib::ScreenResources::GetInstance()->GetCommonState();

	//	画像用サンプラー(画像自体の色)の登録
	ID3D11SamplerState* sampler[1] = { state->LinearWrap() };
	context->PSSetSamplers(0, 1, sampler);

	//	半透明描画指定
	ID3D11BlendState* blendstate = state->NonPremultiplied();

	// 透明判定処理
	context->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);

	// 深度バッファに読み取り専用参照する
	context->OMSetDepthStencilState(state->DepthRead(), 0);

	// カリングは左周り
	context->RSSetState(state->CullNone());

	//	シェーダをセットする
	context->VSSetShader(m_vertexShader.Get(),	 nullptr, 0);
	context->GSSetShader(m_geometryShader.Get(), nullptr, 0);
	context->PSSetShader(m_pixelShader.Get(),	 nullptr, 0);

	//	ピクセルシェーダにテクスチャを登録する。
	context->VSSetShaderResources(0, 1, &m_particleTexture);
	context->GSSetShaderResources(0, 1, &m_particleTexture);
	context->PSSetShaderResources(0, 1, &m_particleTexture);

	//	インプットレイアウトの登録
	context->IASetInputLayout(m_inputLayout.Get());

	//	描画を開始する
	m_primitevBatch->Begin();

	//	描画処理
	m_primitevBatch->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &m_vertices[0], m_vertices.size());

	///	描画を終了する
	m_primitevBatch->End();

	//	シェーダの登録を解除しておく
	context->VSSetShader(nullptr, nullptr, 0);
	context->GSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);
}

/// <summary>
/// 衝突時に呼ぶ
/// </summary>
/// <param name="position"></param>
void BulletHitParticle::Hit(DirectX::SimpleMath::Vector3 position)
{
	m_elapsedTime = 0.0f;

	m_isUsed = true;
	m_tagetPosition = position;

	for (const auto& particle : m_particles)
		particle->StartEffect(m_tagetPosition);
}

/// <summary>
/// シェーダーを作成
/// </summary>
void BulletHitParticle::CreateSharder()
{
	//	デバイス
	auto device = MyLib::ScreenResources::GetInstance()->GetDevice();

	// ピクセルシェーダーの作成
	std::vector<uint8_t> vsData = DX::ReadData(L"Resources/CSO/ParticleVS.cso");
	std::vector<uint8_t> gsData = DX::ReadData(L"Resources/CSO/ParticleGS.cso");
	std::vector<uint8_t> psData = DX::ReadData(L"Resources/CSO/ParticlePS.cso");

	//インプットレイアウトの作成
	device->CreateInputLayout(
		&INPUT_LAYOUT[0],
		static_cast<UINT>(INPUT_LAYOUT.size()),
		vsData.data(),
		vsData.size(),
		m_inputLayout.GetAddressOf()
	);

	// 頂点シェーダ作成
	if (FAILED(device->CreateVertexShader(vsData.data(), vsData.size(), NULL, m_vertexShader.ReleaseAndGetAddressOf())))
	{
		// エラー
		MessageBox(0, L"CreateVertexShader Failed.", NULL, MB_OK);
		return;
	}

	// ジオメトリシェーダ作成
	if (FAILED(device->CreateGeometryShader(gsData.data(), gsData.size(), NULL, m_geometryShader.ReleaseAndGetAddressOf())))
	{
		// エラー
		MessageBox(0, L"CreateGeometryShader Failed.", NULL, MB_OK);
		return;
	}
	// ピクセルシェーダ作成
	if (FAILED(device->CreatePixelShader(psData.data(), psData.size(), NULL, m_pixelShader.ReleaseAndGetAddressOf())))
	{
		// エラー
		MessageBox(0, L"CreatePixelShader Failed.", NULL, MB_OK);
		return;
	}

	//シェーダーにデータを渡すためのコンスタントバッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ConstBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	device->CreateBuffer(&bd, nullptr, &m_constantBuffer);
}
