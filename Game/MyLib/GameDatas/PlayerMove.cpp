//
//		File Name ： PlayerMove.cpp
//		Production： 2023/1/30
//		Author　　： 石田 恭一	
// 
//		プレイヤーの移動の実装
//
#include "pch.h"
#include "PlayerMove.h"
#include "Game/MyLib/Scenes/PlayScene/Object/Player.h"

//	走る速度
const float						  DASH_SPEED = 0.04f;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="player">プレイヤー</param>
PlayerMove::PlayerMove(Player* player)
	:m_player(player),
	m_isDash(false),
	m_isWalk(false)
{

}

/// <summary>
/// プレイヤーの移動処理
/// </summary>
void PlayerMove::MovePlayer()
{
	auto input = MyLib::InputSystem::GetInstance()->GetKeyboard()->GetState();
	//auto mouse = MyLib::InputSystem::GetInstance()->GetStateTracker();

	bool isWalk = false;

	//	移動量の初期化
	DirectX::SimpleMath::Vector3 velocity = DirectX::SimpleMath::Vector3::Zero;

	//	前進
	if (input.W)
	{
		velocity -= DirectX::SimpleMath::Vector3(0.0f, 0.0f, 1.0f);
		isWalk = true;
	}
	//	後進
	else if (input.S)
	{
		velocity += DirectX::SimpleMath::Vector3(0.0f, 0.0f, 1.0f);
		isWalk = true;
	}
	//	右進
	if (input.A)
	{
		velocity -= DirectX::SimpleMath::Vector3(1.0f, 0.0f, 0.0f);
		isWalk = true;
	}
	//	左進
	else if (input.D)
	{
		velocity += DirectX::SimpleMath::Vector3(1.0f, 0.0f, 0.0f);
		isWalk = true;
	}
	//	ノーマライズ
	velocity.Normalize();

	//	左シフト押されていたらダッシュする
	if (input.LeftShift)
	{
		velocity *= m_player->GetSpeed() + DASH_SPEED;
		m_isDash = true;
	}
	else
	{
		velocity *= m_player->GetSpeed();
		m_isDash = false;
	}

	//	歩いているか確認する
	if (isWalk)	m_isWalk = true;
	else 		m_isWalk = false;


	//	座標情報に移動量を足す
	m_player->SetPosition(m_player->GetPosition() + velocity);

#ifdef _DEBUG

	if (input.F1)
	{
		m_player->HealthZero();
	}

#endif // _DEBUG
}