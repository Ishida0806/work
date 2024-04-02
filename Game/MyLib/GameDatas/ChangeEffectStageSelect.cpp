//
//		File Name �F ChangeEffectStageSelect.cpp
//		Production�F 2023/1/17
//		Author�@�@�F �Γc ����	
//
#include "pch.h"
#include "ChangeEffectStageSelect.h"

//	�t�F�[�h�̎���
const float						   ChangeEffectStageSelect::STAGE_FADE_TIME					= 7.2f;
//	�h�A�̓������x
const float						   ChangeEffectStageSelect::DOOR_MOVE_SPEED					= 12.0f;
//	�X�e�[�W�̓��ꂷ��ۂ̃h�A�̉E���̍��W
const DirectX::SimpleMath::Vector2 ChangeEffectStageSelect::STAGE_TO_RIGHT_DOOR_POSITION	= DirectX::SimpleMath::Vector2(200.0f, 0.0);
//	�X�e�[�W�̓��ꂷ��ۂ̃h�A�̍����̍��W
const DirectX::SimpleMath::Vector2 ChangeEffectStageSelect::STAGE_TO_LEFT_DOOR_POSITION		= DirectX::SimpleMath::Vector2(-200.0f, 0.0);
//	�X�e�[�W�̑ޏꂷ��ۂ̃h�A�̉E���̍��W
const DirectX::SimpleMath::Vector2 ChangeEffectStageSelect::STAGE_OUT_RIGHT_DOOR_POSITION	= DirectX::SimpleMath::Vector2(1200.0f, 0.0);
//	�X�e�[�W�̑ޏꂷ��ۂ̃h�A�̍����̍��W
const DirectX::SimpleMath::Vector2 ChangeEffectStageSelect::STAGE_OUT_LEFT_DOOR_POSITION	= DirectX::SimpleMath::Vector2(-1200.0f, 0.0);

/// <summary>
/// �R���X�g���N�^
/// </summary>
ChangeEffectStageSelect::ChangeEffectStageSelect()
	:ChangeEffect(ChangeEffect::ChangeSceneType::Select)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ChangeEffectStageSelect::~ChangeEffectStageSelect()
{
}

/// <summary>
/// ����������
/// </summary>
void ChangeEffectStageSelect::Initialize()
{
	//	�摜�̐ݒ�
	ChangeEffect::SetTexure(MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"BlackTexture"));

	//	���W�̏�����
	m_blackRightPos = STAGE_TO_RIGHT_DOOR_POSITION;
	m_blackLeftPos  = STAGE_TO_LEFT_DOOR_POSITION;
}

/// <summary>
/// ���̃V�[���ɑJ�ڂ���
/// </summary>
void ChangeEffectStageSelect::ToChange()
{
	//	�E���������ɉ�ʊO�Ƀt�F�[�h�A�E�g����悤��
	m_blackLeftPos.x  -= DOOR_MOVE_SPEED;
	m_blackRightPos.x += DOOR_MOVE_SPEED;

	if (GetElapsedTime() >= STAGE_FADE_TIME)
	{
		FinishedChangeScene();
	}
}

/// <summary>
/// �V�[���𔲂���
/// </summary>
void ChangeEffectStageSelect::OutChange()
{
	if (GetElapsedTime() >= STAGE_FADE_TIME)
	{
		FinishedChangeScene();
	}
}

/// <summary>
/// �G�t�F�N�g�̕`��
/// </summary>
void ChangeEffectStageSelect::Draw()
{
	//	�h�A�̍�����\��
	MyLib::ScreenResources::GetInstance()->GetSpriteBatch()->Draw
	(
		GetTexture(),
		m_blackLeftPos
	);
	//	�h�A�̉E����\��
	MyLib::ScreenResources::GetInstance()->GetSpriteBatch()->Draw
	(
		GetTexture(),
		m_blackRightPos
	);
}

/// <summary>
/// ���O�̏��������s��
/// </summary>
void ChangeEffectStageSelect::PreInitialize()
{
	//	����̏ꍇ
	if (GetChangeFadeType() == ChangeEffect::ChangeSceneFadeType::To)
	{
		//	���W�̏�����
		m_blackRightPos = STAGE_TO_RIGHT_DOOR_POSITION;
		m_blackLeftPos  = STAGE_TO_LEFT_DOOR_POSITION;
	}
	//	�ޏ�̏ꍇ
	//if (GetChangeFadeType() == ChangeEffect::ChangeSceneFadeType::Out)
	//{
	//	//	���W�̏�����
	//	m_blackRightPos = STAGE_OUT_RIGHT_DOOR_POSITION;
	//	m_blackLeftPos = STAGE_OUT_LEFT_DOOR_POSITION;
	//}
}
