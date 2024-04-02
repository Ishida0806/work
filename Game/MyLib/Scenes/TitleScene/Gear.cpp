//
//		File Name �F Gear.cpp
//		Production�F 2023/11/11
//		Author�@�@�F �Γc ����
// 
//		�^�C�g���̃M�A�̍X�V�E�`����s��
//
#include "pch.h"
#include "Gear.h"

#include "TitleScene.h"

//	���S���������x
const float						   Gear::MOVE_GEAR_SPEED	  = 0.02f;
//	�M�A���x
const float						   Gear::GEAR_SPEED			  = 2.0f;
//	�M�A����鑬�x
const float						   Gear::MOVE_GEAR_RADIAN	  = -1.0f;
//	�M�A�̖ڕW���W
const float						   Gear::GEAR_TARGET_POSITION = 100.0f;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="texture">�摜</param>
/// <param name="position">���W</param>
/// <param name="originPosition">�^�񒆂̍��W</param>
/// <param name="Direction">����</param>
Gear::Gear(ID3D11ShaderResourceView* texture, const DirectX::SimpleMath::Vector2& position, const DirectX::SimpleMath::Vector2& originPosition, const Direction& direction)
	:m_texture(texture),
	m_position(position),
	m_originPosition(originPosition),
	m_isDirection(direction),
	m_angle(0.0f),
	m_state(0)
{
	//	�傫����߂�
	m_scale = TitleUI::BASE_SCALE;
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Gear::~Gear()
{
}


/// <summary>
/// �X�V����
/// </summary>
/// <param name="state">�^�C�g���̃X�e�[�g</param>
void Gear::Update(const int& state)
{
	m_state = state;
	// �A�C�h�����O��Ԃ̍X�V
	UpdateIdle();
	// �A�C�h�����O��ԈȊO�̍X�V
	UpdateNoteIdle();
}

/// <summary>
/// �X�V����
/// </summary>
void Gear::Draw()
{
	//	�`���C����
	TitleUI::Draw
	(
		m_texture,
		m_position,
		DirectX::SimpleMath::Color(0.0f, 0.0f, 0.0f, 0.5f),
		m_angle,
		m_originPosition,
		m_scale
	);
}

/// <summary>
/// �A�C�h�����O��Ԃ̍X�V
/// </summary>
void Gear::UpdateIdle()
{
	TitleScene::STATE state = static_cast<TitleScene::STATE>(m_state);

	//	�A�C�h�����O�ȊO�͋A��
	if (state != TitleScene::STATE::IDLE)		return;
	//	�o�ߎ��Ԃ��擾����
	float elapsedTime = MyLib::ElapsedTime::GetInstance()->GetElapsedTime();
	//	���Ԃ���
	m_angle = DirectX::XMConvertToRadians(elapsedTime * GEAR_SPEED);

	//	�t�����ɂ���
	if (m_isDirection == Direction::Right)	m_angle *= MOVE_GEAR_RADIAN;
}

/// <summary>
/// �A�C�h�����O��ԈȊO�̍X�V
/// </summary>
void Gear::UpdateNoteIdle()
{
	TitleScene::STATE state = static_cast<TitleScene::STATE>(m_state);
	//	�A�C�h�����Ȃ�A��
	if (state == TitleScene::STATE::IDLE)		return;
	//	�����ɂ���ďꏊ��ς���
	switch (m_isDirection)
	{
	case Gear::Direction::Right:	m_position = DirectX::SimpleMath::Vector2::Lerp(m_position, DirectX::SimpleMath::Vector2(m_position.x + GEAR_TARGET_POSITION, m_position.y + GEAR_TARGET_POSITION), MOVE_GEAR_SPEED);	break;
	case Gear::Direction::Left:		m_position = DirectX::SimpleMath::Vector2::Lerp(m_position, DirectX::SimpleMath::Vector2(m_position.x - GEAR_TARGET_POSITION, m_position.y + GEAR_TARGET_POSITION), MOVE_GEAR_SPEED);	break;
	case Gear::Direction::OverID:																																															break;
	default:																																																				break;
	}
}
