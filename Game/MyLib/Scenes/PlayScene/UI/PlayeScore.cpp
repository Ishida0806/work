//
//		File Name �F PlayeScore.cpp
//		Production�F 2023/11/27
//		Author�@�@�F �Γc ����
// 
#include "pch.h"
#include "PlayeScore.h"

#include "Game/MyLib/GameDatas/Number.h"
#include "Game/MyLib/GameDatas/PlayInfo.h"

//	�����̍��W
static const DirectX::SimpleMath::Vector2 NUM_POSITION;
//	�X�R�A�̍��W
static const DirectX::SimpleMath::Vector2 SCORE_POSITION;

/// <summary>
/// �R���X�g���N�^
/// </summary>
PlayeScore::PlayeScore()
	:m_playInfo(nullptr),
	m_scoreBackGround(nullptr)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayeScore::~PlayeScore()
{
}

/// <summary>
/// ����������
/// </summary>
void PlayeScore::Initialize()
{
	// �f�o�C�X�ˑ��̃��\�[�X�̏�����
	CreateDeviceDependentResources();
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void PlayeScore::Update(const DX::StepTimer& timer)
{
	timer;

	//	�X�R�A�\�����X�V����
	m_scoreDisplay->Update(m_playInfo->GetScore());
}

/// <summary>
/// �`�揈��
/// </summary>
void PlayeScore::Draw()
{
	//	�X�v���C�g�o�b�`
	DirectX::SpriteBatch* spriteBatch = MyLib::ScreenResources::GetInstance()->GetSpriteBatch();
	//	�`�悷��
	spriteBatch->Draw
	(
		m_scoreBackGround,
		DirectX::SimpleMath::Vector2(153.0f,0.0f)
	);

	//	�X�R�A�\��
	m_scoreDisplay->Draw();
}

/// <summary>
/// �o�ߎ��Ԃ��~�߂�
/// </summary>
void PlayeScore::StopElapsedTimer()
{
	//	�o�ߎ��Ԃ�ݒ肷��
	m_playInfo->SetElapsedTime(MyLib::ElapsedTime::GetInstance()->GetElapsedTime());
}

/// <summary>
/// �f�o�C�X�ˑ��̃��\�[�X�̏�����
/// </summary>
void PlayeScore::CreateDeviceDependentResources()
{
	//	�v���C�C���t�H���[�V�������쐬����
	m_playInfo = PlayInfo::GetInstance();
	//	���������s��
	m_playInfo->Initialize();
	//	�X�R�A�\��
	m_scoreDisplay = std::make_unique<Number>
		(
			MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"number"),
			DirectX::SimpleMath::Vector2(315.0f, 12.5f)
		);

	//	�X�R�A�̉摜
	m_scoreBackGround = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"PlayScoreBackGround");
}
