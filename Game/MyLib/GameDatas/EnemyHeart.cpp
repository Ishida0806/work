//
//		File Name ： SwingSordEffect.cpp
//		Production： 2023/1/12
//		Author　　： 石田 恭一
// 
//		当たった際のエフェクトの描画を行うクラス
//
#include "pch.h"
#include "EnemyHeart.h"
#include "Game/MyLib/Scenes/PlayScene/Object/Enemy/Enemy.h"

const float EnemyHeart::RENDER_TIME = 22.0f;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="enemy">敵</param>
EnemyHeart::EnemyHeart(Enemy* enemy)
	:
	m_enemy(enemy),
	m_coverHeartTexture(nullptr),
	m_heartTexture(nullptr),
	m_size(1.0f),
	m_elapsedTime(0.0f)
{
	//	スクリーンリソース
	m_screen = MyLib::ScreenResources::GetInstance();
	//	バッチエフェクト
	m_batchEffect = m_screen->GetBasicEffect();
	//	インプットレイアウト
	m_inputLayout = m_screen->GetInputLayout();
	// プリミティブバッチの作成
	m_primitiveBatch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>>(m_screen->GetDeviceContext());
	//	ハートの画像
	m_heartTexture = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"EnemyHeart");
	//	ハートの背景画像
	m_coverHeartTexture = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"EnemyCoverHeart");
}

/// <summary>
/// デストラクタ
/// </summary>
EnemyHeart::~EnemyHeart()
{
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="timer">タイマー</param>
void EnemyHeart::Update(const DX::StepTimer& timer)
{
	if (m_enemy->IsDeadAnimation())	return;
	//	経過時間を引く
	m_elapsedTime -= static_cast<float>(timer.GetElapsedSeconds());

	float maxHealth =static_cast<float>(m_enemy->GetMAXHealth());
	float health =static_cast<float>(m_enemy->GetHealth());

	m_size = maxHealth / health;
}
/// <summary>
/// 描画処理
/// </summary>
/// <param name="view">ビュー</param>
/// <param name="proj">プロジェクション</param>
void EnemyHeart::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	if (m_enemy->IsDeadAnimation())	return;
	//	コンテキスト
	auto context = m_screen->GetDeviceContext();
	//	ハートの画像
	m_heartTexture = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"EnemyHeart");
	//	ハートの背景画像
	m_coverHeartTexture = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"EnemyCoverHeart");

	// 頂点情報
	DirectX::VertexPositionColorTexture vertex[4] =
	{
		DirectX::VertexPositionColorTexture(DirectX::SimpleMath::Vector3( m_size,  0.5f,  m_size),DirectX::SimpleMath::Vector4( 1.0f, 1.0f, 0.0f,  1.0f), DirectX::SimpleMath::Vector2(0.0f, 0.0f)),
		DirectX::VertexPositionColorTexture(DirectX::SimpleMath::Vector3(-m_size,  0.5f,   m_size),DirectX::SimpleMath::Vector4(1.0f, 1.0f, 0.0f,  1.0f), DirectX::SimpleMath::Vector2(1.0f, 0.0f)),
		DirectX::VertexPositionColorTexture(DirectX::SimpleMath::Vector3(-m_size,  0.5f,  -m_size),DirectX::SimpleMath::Vector4(1.0f, 1.0f, 0.0f,  1.0f), DirectX::SimpleMath::Vector2(1.0f, 1.0f)),
		DirectX::VertexPositionColorTexture(DirectX::SimpleMath::Vector3( m_size,  0.5f, -m_size),DirectX::SimpleMath::Vector4( 1.0f, 1.0f, 0.0f,  1.0f), DirectX::SimpleMath::Vector2(0.0f, 1.0f)),
	};


	// 頂点情報
	DirectX::VertexPositionColorTexture coverVertex[4] =
	{
		DirectX::VertexPositionColorTexture(DirectX::SimpleMath::Vector3(1.0f,  0.5f,   1.0f),DirectX::SimpleMath::Vector4(1.0f, 1.0f, 1.0f,  1.0f), DirectX::SimpleMath::Vector2(0.0f, 0.0f)),
		DirectX::VertexPositionColorTexture(DirectX::SimpleMath::Vector3(-1.0f, 0.5f,   1.0f),DirectX::SimpleMath::Vector4(1.0f, 1.0f, 1.0f,  1.0f), DirectX::SimpleMath::Vector2(1.0f, 0.0f)),
		DirectX::VertexPositionColorTexture(DirectX::SimpleMath::Vector3(-1.0f, 0.5f,  -1.0f),DirectX::SimpleMath::Vector4(1.0f, 1.0f, 1.0f,  1.0f), DirectX::SimpleMath::Vector2(1.0f, 1.0f)),
		DirectX::VertexPositionColorTexture(DirectX::SimpleMath::Vector3(1.0f,  0.5f,  -1.0f),DirectX::SimpleMath::Vector4(1.0f, 1.0f, 1.0f,  1.0f), DirectX::SimpleMath::Vector2(0.0f, 1.0f)),
	};

	// 加算合成
	context->OMSetBlendState(m_screen->GetCommonState()->Additive(), nullptr, 0xFFFFFFFF);
	// 深度バッファはなし
	context->OMSetDepthStencilState(m_screen->GetCommonState()->DepthNone(), 0);
	// カリングは左周り
	context->RSSetState(m_screen->GetCommonState()->CullCounterClockwise());
	//	描画座標
	DirectX::SimpleMath::Vector3 renderPosition = m_enemy->GetPosition();
	//	敵によって描画位置を変える
	if (m_enemy->GetType() == Object::ObjectType::BossEnemy) { renderPosition.y = 5.0f; } else { renderPosition.y = 3.0f; }
	//	ワールド
	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::CreateFromQuaternion(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(180.0f)) * 
		DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitX, DirectX::XMConvertToRadians(45.0f))) *
		DirectX::SimpleMath::Matrix::CreateTranslation(renderPosition);

	m_batchEffect->SetWorld(world);
	m_batchEffect->SetView(view);
	m_batchEffect->SetProjection(proj);
	m_batchEffect->Apply(context);
	context->IASetInputLayout(m_inputLayout);

	m_primitiveBatch->Begin();
	m_batchEffect->SetTexture(m_heartTexture.Get());
	m_primitiveBatch->DrawQuad(vertex[0], vertex[1], vertex[2], vertex[3]);
	m_batchEffect->SetTexture(m_coverHeartTexture.Get());
	m_primitiveBatch->DrawQuad(coverVertex[0], coverVertex[1], coverVertex[2], coverVertex[3]);
	m_primitiveBatch->End();
}