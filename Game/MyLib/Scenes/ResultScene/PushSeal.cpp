
//
//		File Name �F PushSeal.cpp
//		Production�F 2023/11/11
//		Author�@�@�F �Γc ����
//
#include "pch.h"
#include "PushSeal.h"

//	���ʂ̌덷�͈�
const float						   PushSeal::ERROR_RANGE		  = 3.5f;
//	���ʂ̑��x
const float						   PushSeal:: SEAL_SPEED		  = 0.1f;
//	�ڕW���W
const DirectX::SimpleMath::Vector2 PushSeal::MOVE_TARGET_POSITION = DirectX::SimpleMath::Vector2(700.0f, 290.0f);
//	�ڕW�̔��q���������W
const DirectX::SimpleMath::Vector2 PushSeal::TARGET_PUSH_POSITION = DirectX::SimpleMath::Vector2(700.0f, 380.0f);
//	�ڕW�̉�ʊO�̍��W
const DirectX::SimpleMath::Vector2 PushSeal::TARGET_FAR_POSITION  = DirectX::SimpleMath::Vector2(1500.0f, 380.0f);

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="texture">�摜</param>
/// <param name="position">���W</param>
/// <param name="originPosition">�摜�̐^�񒆍��W</param>
PushSeal::PushSeal(
	const DirectX::SimpleMath::Vector2& position,
	const DirectX::SimpleMath::Vector2& originPosition
)
	:m_position(position),
	m_originPosition(originPosition),
	m_angle(0.0f),
	m_texture(nullptr),
	m_isTop(false),
	m_moveTop(false),
	m_moveDown(false),
	m_stateSeal(PUSHSEAL_STATE::MoveTarget)
{
	m_texture = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"push_seal");
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PushSeal::~PushSeal()
{
}

/// <summary>
/// �X�V����
/// </summary>
void PushSeal::Update()
{	
	//	���q�̍X�V�������s��
	switch (m_stateSeal)
	{
	case PushSeal::PUSHSEAL_STATE::MoveTarget:	MoveTarget();	break;
	case PushSeal::PUSHSEAL_STATE::Push:		Push();			break;
	case PushSeal::PUSHSEAL_STATE::MoveOut:		MoveOut();		break;
	case PushSeal::PUSHSEAL_STATE::Finish:						break;
	case PushSeal::PUSHSEAL_STATE::OverID:						break;
	default:													break;
	}
}

/// <summary>
/// �`�揈��
/// </summary>
void PushSeal::Draw()
{
	//	�`�悪���K�v�Ȃ��Ƃ��͂��Ȃ�
	if (m_stateSeal == PUSHSEAL_STATE::Finish)	return;

	//	�ē��L�[�̕`��
	MyLib::ScreenResources::GetInstance()->GetSpriteBatch()->Draw
	(
		m_texture,
		m_position,
		nullptr,
		DirectX::Colors::White,
		0.0f,
		m_originPosition
	);
}

/// <summary>
/// �^�[�Q�b�g�̏ꏊ�Ɉړ����s��
/// </summary>
void PushSeal::MoveTarget()
{
	//	���W�Ɉړ����s��
	m_position = DirectX::SimpleMath::Vector2::Lerp(m_position, MOVE_TARGET_POSITION, SEAL_SPEED);

	//	�ڕW���W�t�߂ɗ����玟�̃X�e�[�g��
	if (m_position.x >= MOVE_TARGET_POSITION.x - ERROR_RANGE && m_position.y >= MOVE_TARGET_POSITION.y - ERROR_RANGE)
	{
		//	���q�̉����Đ�����
		AudioManager::GetInstance()->PlaySoundEffectSE(L"Result_PushSeal");
		//	���̃X�e�[�g��
		m_stateSeal = PUSHSEAL_STATE::Push;
	}
}

/// <summary>
/// �X�^���v������
/// </summary>
void PushSeal::Push()
{
	//	���ɉ�����
	if (!m_moveDown)												m_position = DirectX::SimpleMath::Vector2::Lerp(m_position, TARGET_PUSH_POSITION, SEAL_SPEED);
	if (m_position.y >= TARGET_PUSH_POSITION.y - ERROR_RANGE)		m_moveDown = true;

	//	���삪�I�����Ă��Ȃ��Ȃ�A��
	if (!m_moveDown)	return;

	//	�X�^���v�������ꂽ
	m_isTop = true;

	//	��ւ�����
	if (!m_moveTop)													m_position = DirectX::SimpleMath::Vector2::Lerp(m_position, MOVE_TARGET_POSITION, SEAL_SPEED);
	if (m_position.y <= MOVE_TARGET_POSITION.y + ERROR_RANGE)		m_moveTop = true;

	//	���삪�I�����Ă��Ȃ��Ȃ�A��
	if (!m_moveTop)	return;

	//	���̃X�e�[�g��
	m_stateSeal = PUSHSEAL_STATE::MoveOut;
}

/// <summary>
/// �O�֌�����
/// </summary>
void PushSeal::MoveOut()
{
	//	���W���O�Ɉړ�
	m_position = DirectX::SimpleMath::Vector2::Lerp(m_position, TARGET_FAR_POSITION, SEAL_SPEED);

	//	�ڕW���W�֍s�����玟�̃X�e�[�g��
	if (m_position.x >= TARGET_FAR_POSITION.x - ERROR_RANGE)
		m_stateSeal = PUSHSEAL_STATE::Finish;
}
