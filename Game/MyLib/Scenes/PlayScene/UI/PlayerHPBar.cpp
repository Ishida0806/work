//
//		File Name �F PlayerHPBar.cpp
//		Production�F 2023/10/3
//		Author�@�@�F �Γc ����
// 
//		HP�o�[
// 
#include "pch.h"
#include "PlayerHPBar.h"
#include "Game/MyLib/Scenes/PlayScene/Object/Player.h"	

//	��
const DirectX::SimpleMath::Color PlayerHPBar::RED	 = DirectX::SimpleMath::Color(1.0, 0.0, 0.0, 1.0f);
//	���F
const DirectX::SimpleMath::Color PlayerHPBar::YELLOW = DirectX::SimpleMath::Color(1.0, 1.0, 0.0, 1.0f);
//	��
const DirectX::SimpleMath::Color PlayerHPBar::GREEN  = DirectX::SimpleMath::Color(0.0, 1.0, 0.0, 1.0f);
//	�̗̓o�[�p�̍��W
 const int  PlayerHPBar::HP_POS						 = 420;
 //	�̗̓o�[��X���W
 const int  PlayerHPBar::HP_IX						 = 147;
 //	�̗̓o�[��Y���W
 const int  PlayerHPBar::HP_IY						 = 60;
 //	�̗̓o�[�̍���
 const int  PlayerHPBar::HP_IH						 = 35;
 //	�덷�͈̔�
 const int  PlayerHPBar::HP_RANGE_VALUE				 = 5;

/// <summary>
/// �R���X�g���N�^
/// </summary>
PlayerHPBar::PlayerHPBar():
	m_hpPlayerBarUI(nullptr),
	m_pPlayer(nullptr),
	m_screen(nullptr),
	m_resources(nullptr),
	m_isBad(false),
	m_hpBar(0),
	m_nowHpBar(0),
	m_hpState(HP_RENDER_STATE::FINE)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayerHPBar::~PlayerHPBar()
{
}

/// <summary>
/// ����������
/// </summary>
void PlayerHPBar::Initialize()
{
	CreateDeviceDependentResources();
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="timer"></param>
void PlayerHPBar::Update(const DX::StepTimer& timer)
{
	UNREFERENCED_PARAMETER(timer);

	//	�̗͂ɂ���ďꏊ�����炷
	m_hpBar = HP_POS * m_pPlayer->GetHealth() / m_pPlayer->GetMaxHealth();

	//	�i�X�ƌ��炷
	if (m_nowHpBar > m_hpBar)
	{
		if (m_nowHpBar - m_hpBar > 30)
		{
			m_nowHpBar -= 10;
		}
		else
		{
			m_nowHpBar--;
		}
	}
	else
	{
		if (m_nowHpBar < m_hpBar)
		{

			m_nowHpBar++;
		}
	}

	//	BAD��Ԃ̎������t���O��ON��
	if (m_hpState == HP_RENDER_STATE::BAD)
	{
		m_isBad = true;
	}
	else
	{
		m_isBad = false;
	}
}

/// <summary>
/// �`�悷��
/// </summary>
void PlayerHPBar::Draw()
{
	// �̗̓o�[��`�悷��
	RenderBar();
}

/// <summary>
/// �̗̓o�[��`�悷��
/// </summary>
void PlayerHPBar::RenderBar()
{
	//	���̘g��`�悷��
	m_screen->GetSpriteBatch()->Draw
	(
		m_hpPlayerBarUI,																										//  �摜��HP BAR
		DirectX::SimpleMath::Rectangle(HP_IX, HP_IY - HP_RANGE_VALUE, HP_POS + HP_RANGE_VALUE, HP_IH + HP_RANGE_VALUE * 2),		//�@���W�E�傫���͏����傫�߂�
		DirectX::SimpleMath::Color(0.0, 0.0, 0.0, 0.7f)																			//	�F���S�^����&&�w�i�𔖂�
	);

	//	�̗͂̏�Ԃɂ���ĕ`��F��ς���
	switch (m_hpState)
	{
	//	���C�ȏ�Ԃȏꍇ
	case PlayerHPBar::HP_RENDER_STATE::FINE:
	
		m_screen->GetSpriteBatch()->Draw
		(
			m_hpPlayerBarUI,
			DirectX::SimpleMath::Rectangle(HP_IX, HP_IY, m_nowHpBar, HP_IH),
			GREEN
		);
		break;
	
	//	�̗͂�������؂�����
	case PlayerHPBar::HP_RENDER_STATE::LITTLE_BAD:
	
		m_screen->GetSpriteBatch()->Draw
		(
			m_hpPlayerBarUI,
			DirectX::SimpleMath::Rectangle(HP_IX, HP_IY, m_nowHpBar, HP_IH),
			YELLOW
		);

		break;
	
	//	1/4�ȉ���
	case PlayerHPBar::HP_RENDER_STATE::BAD:
	
		m_screen->GetSpriteBatch()->Draw
		(
			m_hpPlayerBarUI,
			DirectX::SimpleMath::Rectangle(HP_IX, HP_IY, m_nowHpBar, HP_IH),
			RED
		);
		break;
	
	//	��������ł���̂ŕ`������Ȃ�
	case PlayerHPBar::HP_RENDER_STATE::DEAD:	break;
	default:									break;
	}	
}

/// <summary>
/// �v���C���[�̃|�C���^�[��ݒ肷��
/// </summary>
/// <param name="player"></param>
void PlayerHPBar::SetPlayer(Player* player)
{
	m_pPlayer = player;
}

/// <summary>
/// �̗͂̃X�e�[�g��Ԃ�ݒ肷��
/// </summary>
/// <param name="state">�X�e�[�g</param>
void PlayerHPBar::SetHPState(int state)
{
	m_hpState = static_cast<HP_RENDER_STATE>(state);
}

/// <summary>
/// �f�o�C�X�ˑ��̃��\�[�X�̏�����
/// </summary>
void PlayerHPBar::CreateDeviceDependentResources()
{
	//	�X�N���[�����\�[�X
	m_screen = MyLib::ScreenResources::GetInstance();
	//	���\�[�V�[�Y�f�[�^
	m_resources = MyLib::ResourcesData::GetInstance();
	//	���q�̈����v���C���[�̉摜	
	m_hpPlayerBarUI = m_resources->GatShaderResourceView(L"HPBar");
	//	�̗̓o�[�̏�����
	m_hpBar = HP_POS * m_pPlayer->GetHealth() / m_pPlayer->GetMaxHealth();
	//	�̗̓o�[�̏�����
	m_nowHpBar = m_hpBar;
}