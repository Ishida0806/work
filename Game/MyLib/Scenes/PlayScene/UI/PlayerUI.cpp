//
//		File Name �F PlayerUI.cpp
//		Production�F 2023/10/2
//		Author�@�@�F �Γc ����
// 
#include "pch.h"
#include "PlayerUI.h"
#include "../../PlayScene/Object/Player.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
PlayerUI::PlayerUI()
	:m_screen(nullptr),
	m_resources(nullptr),
	m_pPlayer(nullptr),
	m_goodPlayer(nullptr),
	m_littleBadPlayer(nullptr),
	m_badPlayer(nullptr),
	m_deathPlayer(nullptr),
	m_hpState(HP_RENDER_STATE::FINE)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayerUI::~PlayerUI()
{
}

/// <summary>
/// ����������
/// </summary>
void PlayerUI::Initialize()
{
	CreateDeviceDependentResources();
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void PlayerUI::Update(const DX::StepTimer& timer)
{
	UNREFERENCED_PARAMETER(timer);

	//	�v���C���[�̗̑͂̍ő�l���擾����
	int maxPlayerHp = m_pPlayer->GetMaxHealth();
	//	�v���C���[�̌��݂̗̑͒l���擾����
	int nowPlayerHp = m_pPlayer->GetHealth();

	//	�v���C���[�̍ő�l�̔����ȏ�Ȃ�
	if (maxPlayerHp / 2 <= nowPlayerHp)
	{
		m_hpState = HP_RENDER_STATE::FINE;
	}
	//	�v���C���[�̍ő�l�̔����ȉ� && �v���C���[�̍ő�l��4����1�ȏ�Ȃ�
	else if(maxPlayerHp / 2 >= nowPlayerHp && maxPlayerHp / 4 <= nowPlayerHp)
	{
		m_hpState = HP_RENDER_STATE::LITTLE_BAD;
	}
	// �v���C���[�̍ő�l��4����1�ȏ�Ȃ� && 0����Ȃ�
	else if(maxPlayerHp / 4 >= nowPlayerHp && 0 < nowPlayerHp)
	{
		m_hpState = HP_RENDER_STATE::BAD;
	}
	//	����ȊO�͎���ł���
	else 
	{
		m_hpState = HP_RENDER_STATE::DEAD;
	}
}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="spriteBatch">�X�v���C�g�o�b�`</param>
void PlayerUI::Draw()
{
	//	
	m_screen->GetSpriteBatch()->Draw
	(
		MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"PlayerUIBackGround"),
		DirectX::SimpleMath::Vector2::Zero
	);

	//	�̗͂̏�Ԃɂ���ĕ`���ς���
	RenderHPState();
}

/// <summary>
/// �f�o�C�X�ˑ��̃��\�[�X�̏�����
/// </summary>
void PlayerUI::CreateDeviceDependentResources()
{
	//	�X�N���[�����\�[�X
	m_screen = MyLib::ScreenResources::GetInstance();
	//	���\�[�V�[�Y�f�[�^
	m_resources = MyLib::ResourcesData::GetInstance();
	//	���q�̈����v���C���[�̉摜	
	m_badPlayer = m_resources->GatShaderResourceView(L"Bad_Player");
	//	���q�̗ǂ��v���C���[�̉摜
	m_goodPlayer = m_resources->GatShaderResourceView(L"Good_Player");
	//	���q�̏��������v���C���[�̉摜
	m_littleBadPlayer = m_resources->GatShaderResourceView(L"Little_Bad");
	//	�v���C���[�̎��񂾂Ƃ��̉摜
	m_deathPlayer = m_resources->GatShaderResourceView(L"Death_Player");
}

/// <summary>
/// �̗͂̏�Ԃɂ���ĕ`���ς���
/// </summary>
void PlayerUI::RenderHPState()
{	
	switch (m_hpState)
	{
	case PlayerUI::HP_RENDER_STATE::FINE:
	{
		m_screen->GetSpriteBatch()->Draw(
			m_goodPlayer,
			DirectX::SimpleMath::Vector2::Zero
		);

		break;
	}
	case PlayerUI::HP_RENDER_STATE::LITTLE_BAD:
	{
		m_screen->GetSpriteBatch()->Draw(
			m_littleBadPlayer,
			DirectX::SimpleMath::Vector2::Zero
		);
		break;
	}
	case PlayerUI::HP_RENDER_STATE::BAD:
	{
		m_screen->GetSpriteBatch()->Draw(
			m_badPlayer,
			DirectX::SimpleMath::Vector2::Zero
		);
		break;
	case PlayerUI::HP_RENDER_STATE::DEAD:
	{
		m_screen->GetSpriteBatch()->Draw(
			m_deathPlayer,
			DirectX::SimpleMath::Vector2::Zero
		);
		break;
	}
	}
	default:	break;
	}
}

void PlayerUI::SetPlayer(Player* player)
{
	m_pPlayer = player;
}
