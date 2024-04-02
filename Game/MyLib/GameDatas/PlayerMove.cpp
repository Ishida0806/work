//
//		File Name �F PlayerMove.cpp
//		Production�F 2023/1/30
//		Author�@�@�F �Γc ����	
// 
//		�v���C���[�̈ړ��̎���
//
#include "pch.h"
#include "PlayerMove.h"
#include "Game/MyLib/Scenes/PlayScene/Object/Player.h"

//	���鑬�x
const float						  DASH_SPEED = 0.04f;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="player">�v���C���[</param>
PlayerMove::PlayerMove(Player* player)
	:m_player(player),
	m_isDash(false),
	m_isWalk(false)
{

}

/// <summary>
/// �v���C���[�̈ړ�����
/// </summary>
void PlayerMove::MovePlayer()
{
	auto input = MyLib::InputSystem::GetInstance()->GetKeyboard()->GetState();
	//auto mouse = MyLib::InputSystem::GetInstance()->GetStateTracker();

	bool isWalk = false;

	//	�ړ��ʂ̏�����
	DirectX::SimpleMath::Vector3 velocity = DirectX::SimpleMath::Vector3::Zero;

	//	�O�i
	if (input.W)
	{
		velocity -= DirectX::SimpleMath::Vector3(0.0f, 0.0f, 1.0f);
		isWalk = true;
	}
	//	��i
	else if (input.S)
	{
		velocity += DirectX::SimpleMath::Vector3(0.0f, 0.0f, 1.0f);
		isWalk = true;
	}
	//	�E�i
	if (input.A)
	{
		velocity -= DirectX::SimpleMath::Vector3(1.0f, 0.0f, 0.0f);
		isWalk = true;
	}
	//	���i
	else if (input.D)
	{
		velocity += DirectX::SimpleMath::Vector3(1.0f, 0.0f, 0.0f);
		isWalk = true;
	}
	//	�m�[�}���C�Y
	velocity.Normalize();

	//	���V�t�g������Ă�����_�b�V������
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

	//	�����Ă��邩�m�F����
	if (isWalk)	m_isWalk = true;
	else 		m_isWalk = false;


	//	���W���Ɉړ��ʂ𑫂�
	m_player->SetPosition(m_player->GetPosition() + velocity);

#ifdef _DEBUG

	if (input.F1)
	{
		m_player->HealthZero();
	}

#endif // _DEBUG
}