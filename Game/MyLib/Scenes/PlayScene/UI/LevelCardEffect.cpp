
#include "pch.h"
#include "LevelCardEffect.h"

#include "LevelCard.h"
#include "../Object/Player.h"

//	�J�[�h�̐^�񒆂̍��W
const DirectX::SimpleMath::Vector2 LevelCardEffect::CARD_ORIGIN_POSITION	  = { 131.0f,170.0f };
//	�J�[�h�̍��W
const DirectX::SimpleMath::Vector2 LevelCardEffect::CARD_POSITION			  = { 250.0f,350.0f };
//	�}�E�X�J�[�\���ڐG��̃X�P�[��
const DirectX::SimpleMath::Vector2 LevelCardEffect::CARD_SCALE			  = { 1.3f,1.3f };
//	�J�[�h�̂��炷���W
const float						LevelCardEffect::OFFSET_POSITION		  = 400.0f;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="player">�v���C���[</param>
/// <param name="type">�^�C�v/param>
LevelCardEffect::LevelCardEffect(Player* player, const int& type)
	:m_player(player),
	m_type(type),
	m_texture(nullptr),
	m_clickAble(false),
	m_isReady(false)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
LevelCardEffect::~LevelCardEffect()
{
}

/// <summary>
/// ����������
/// </summary>
void LevelCardEffect::Initialize()
{
	//	�^�C�v
	LevelCard::CardType type = static_cast<LevelCard::CardType>(m_type);

	//	�^�C�v���ƂɃJ�[�h�����
	switch (type)
	{
	case LevelCard::CardType::PowerUP:		m_texture = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"PowerUPCard");	 break;
	case LevelCard::CardType::HealthUP:		m_texture = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"HealthUPCard"); break;
	case LevelCard::CardType::SpeedUP:		m_texture = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"SpeedUPCard");  break;
	default:																														 break;
	}

	//	���W�����炷
	m_targetPosition = DirectX::SimpleMath::Vector2(CARD_POSITION.x + (OFFSET_POSITION * static_cast<float>(m_type)), CARD_POSITION.y);

	//	���W���w��n��
	ResetPosition();

	//	�傫����1
	m_scale = DirectX::SimpleMath::Vector2::One;
}

/// <summary>
/// �X�V����
/// </summary>
void LevelCardEffect::Update()
{
	//	������ԂȂ�A��
	if (m_isReady)	return;

	// �傫����������
	ResizeScale();

	//	�ڕW���W�ւ���
	m_position = DirectX::SimpleMath::Vector2::Lerp(m_position, m_targetPosition, 0.05f);
}

/// <summary>
/// �L�[�I������Ă���
/// </summary>
void LevelCardEffect::SelectKey()
{
	m_clickAble = true;
}

/// <summary>
/// �L�[�I������Ă��Ȃ�
/// </summary>
void LevelCardEffect::SelectNotKey()
{
	m_clickAble = false;
}

/// <summary>
/// �ޏo����
/// </summary>
void LevelCardEffect::Exit()
{
	if (!m_isReady) return;

	// �傫����������
	ResizeScale();

	m_position.y += 15.0f;

	if (m_position.y >= 1000.0f)
	{
		//	���W���w��n��
		ResetPosition();
		//	�����I������
		m_isReady = false;
	}
}

/// <summary>
/// �`�悷��
/// </summary>
void LevelCardEffect::Draw()
{
	MyLib::ScreenResources::GetInstance()->GetSpriteBatch()->Draw
	(
		m_texture,
		m_position,
		nullptr,
		DirectX::Colors::White,
		0.0f,
		CARD_ORIGIN_POSITION,
		m_scale
	);
}


/// <summary>
/// �J�[�h�̒��Ƀ}�E�X�J�[�\���������ė���
/// </summary>
/// <param name="mousePosition">�}�E�X�J�[�\���̍��W</param>
bool LevelCardEffect::InMouseCarsor(const DirectX::SimpleMath::Vector2& mousePosition)
{
	//	������ԂȂ�A��
	if (m_isReady)	return false;

	//	�����̑傫��X
	float leftExtensX  = m_position.x  - CARD_ORIGIN_POSITION.x;
	//	�����̑傫��Y
	float leftExtensY  = m_position.y  - CARD_ORIGIN_POSITION.y;
	//	�E���̑傫��X
	float rightExtensX = m_position.x + CARD_ORIGIN_POSITION.x;
	//	�E���̑傫��Y
	float rightExtensY = m_position.y + CARD_ORIGIN_POSITION.y;

	if ( 
		leftExtensX  < mousePosition.x && leftExtensY  < mousePosition.y &&
		rightExtensX > mousePosition.x && rightExtensY > mousePosition.y
		)
	{	
		//	�ŏ���������炷
		if(!m_clickAble)
			AudioManager::GetInstance()->PlaySoundEffectSE(L"inCard");

		m_clickAble = true;

		return true;
	}
	else
	{
		m_clickAble = false;
	}

	return false;
}

/// <summary>
/// �N���b�N���ꂽ
/// </summary>
void LevelCardEffect::Click()
{
	//	������ԂȂ�A��
	if (m_isReady)	return;

	//	�^�C�v
	LevelCard::CardType type = static_cast<LevelCard::CardType>(m_type);

	//	�^�C�v		
	switch (type)
	{
	case LevelCard::CardType::PowerUP:
		//	����炷
		AudioManager::GetInstance()->PlaySoundEffectSE(L"powerCardUP");
		//	�v���C���[�̋ؗ͂��グ��
		m_player->UpPower();
		break;
	case LevelCard::CardType::HealthUP:	
		//	����炷
		AudioManager::GetInstance()->PlaySoundEffectSE(L"healthCardUP");
		//	�v���C���[�̍ő�̗͂��グ��
		m_player->UpMaxHP();
		break;
	case LevelCard::CardType::SpeedUP:
		//	����炷
		AudioManager::GetInstance()->PlaySoundEffectSE(L"speedCardUP");
		//	�v���C���[�̑��x���グ��
		m_player->UpSpeed();	 
		break;
	default:													 break;
	}

	//	������Ԃ�
	m_isReady	= true;
	m_clickAble = false;
}

/// <summary>
/// ���W���w��n��
/// </summary>
void LevelCardEffect::ResetPosition()
{
	//	X���W�͂��炵���܂܂�
	m_position.x = m_targetPosition.x;
	//	Y���W����ɂ���
	m_position.y = -OFFSET_POSITION;
}

/// <summary>
/// �傫����������
/// </summary>
void LevelCardEffect::ResizeScale()
{
	if (m_clickAble)
	{
		m_scale = DirectX::SimpleMath::Vector2::Lerp(m_scale, CARD_SCALE, 0.1f);
	}
	else
	{
		m_scale = DirectX::SimpleMath::Vector2::Lerp(m_scale, DirectX::SimpleMath::Vector2::One, 0.1f);
	}
}

/// <summary>
/// �N���b�N�������ꂽ
/// </summary>
void LevelCardEffect::SetClick()
{
	//	������Ԃ���Ȃ��Ȃ�A��
	if (m_isReady)	return;

	m_isReady   = true;
	m_clickAble = false;
}