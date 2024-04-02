//
//		File Name ： FallingCherryBlossoms.cpp
//		Production： 2023/2/06
//		Author　　： 石田 恭一	
// 
//		勝利時の花吹雪の実装
//	
#include "pch.h"
#include "FallingCherryBlossoms.h"

//	自身のランダムな座標
const float FallingCherryBlossoms::RANDOM_MINE_POSITION = 7.0f;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="player">プレイヤー</param>
FallingCherryBlossoms::FallingCherryBlossoms(Player* player)
	:
	m_player(player),
	m_randamDirection(0.0f),
	m_randamSpawnYPosition(0.0f)
{
}

/// <summary>
/// デストラクタ
/// </summary>
FallingCherryBlossoms::~FallingCherryBlossoms()
{
}

/// <summary>
/// 初期化処理
/// </summary>
void FallingCherryBlossoms::Initialize()
{
	//	プリミティブバッチの作成	
	m_primitive = DirectX::GeometricPrimitive::CreateCube(MyLib::ScreenResources::GetInstance()->GetDeviceContext());
	//	Y座標の出現位置を決める
	m_randamSpawnYPosition = Utility::CreateRandom(5.0f, 10.0f);
	//	プレイヤーの座標付近に設定する
	DirectX::SimpleMath::Vector3 randomPosition = DirectX::SimpleMath::Vector3(Utility::CreateRandom(-RANDOM_MINE_POSITION, RANDOM_MINE_POSITION), m_randamSpawnYPosition, Utility::CreateRandom(-RANDOM_MINE_POSITION, RANDOM_MINE_POSITION));
	//	座標の設定
	SetPosition(m_player->GetPosition() + randomPosition);
	//	平ぺったくする
	SetScale(DirectX::SimpleMath::Vector3(0.25f, 0.25f, 0.001f));
	//	向きを決める
	m_randamDirection = Utility::CreateRandom(-1.0f, 1.0f);
	//	色もランダムに
	m_colors = DirectX::SimpleMath::Color(1.0f, Utility::CreateRandom(0.0f, 0.3f), Utility::CreateRandom(0.0f, 0.5f));
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="timer">タイマー</param>
void FallingCherryBlossoms::Update(const DX::StepTimer& timer)
{
	//	経過時間を
	float elapsedTime = static_cast<float>(timer.GetElapsedSeconds());
	//	座標の設定する
	DirectX::SimpleMath::Vector3 position = GetPosition();
	//	地面に埋もれたら上に戻す
	if (position.y < -1.0f) { position.y = m_randamSpawnYPosition; } else { position.y -= 2.0f * elapsedTime; }
	//	回転を取得
	DirectX::SimpleMath::Quaternion rotate = GetRotate();
	//	ランダムに回転させる
	rotate *= DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
		(3.0f * elapsedTime) * m_randamDirection, 
		(2.0f * elapsedTime) * m_randamDirection,
		(2.0f* elapsedTime)  * m_randamDirection
	);
	//	回転の設定
	SetRotate(rotate);
	//	座標の設定
	SetPosition(position);
}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="view">ビュー</param>
/// <param name="proj">プロジェクション</param>
void FallingCherryBlossoms::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	//	弾を移動
	DirectX::SimpleMath::Matrix scale  = DirectX::SimpleMath::Matrix::CreateScale(GetScale());
	DirectX::SimpleMath::Matrix trans  = DirectX::SimpleMath::Matrix::CreateTranslation(GetPosition());
	DirectX::SimpleMath::Matrix rotate = DirectX::SimpleMath::Matrix::CreateFromQuaternion(GetRotate());

	DirectX::SimpleMath::Matrix world = scale * rotate * trans;

	//	プリミティブバッチの描画
	m_primitive->Draw(world, view, proj, m_colors);
}

/// <summary>
/// 終了処理
/// </summary>
void FallingCherryBlossoms::Finalize()
{
}
