//
//		File Name �F Sun.cpp
//		Production�F 2023/11/25
//		Author�@�@�F �Γc ����	
//
#include "pch.h"
#include "Sun.h"

#include "StageSelectScene.h"

//	�摜�̐^��
const DirectX::SimpleMath::Vector2  Sun::ORIGIN_SUN_TEXTURE = DirectX::SimpleMath::Vector2(205.0f, 205.0f);

/// <summary>
/// �R���X�g���N�^
/// </summary>
Sun::Sun()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Sun::~Sun()
{
}

/// <summary>
/// ����������
/// </summary>
void Sun::Initialize()
{
	// �f�o�C�X�ˑ��̃��\�[�X�̏�����
	CreateDeviceDependentResources();
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="timer">�^�C�}�[</param>
/// <param name="stageNum">�X�e�[�W�ԍ�/param>
void Sun::Update(const DX::StepTimer& timer, const int& stageNum)
{
	UNREFERENCED_PARAMETER(timer);

	m_stage = stageNum;

	//	�X�e�[�W�^�ɃL���X�g
	StageSelectScene::CHOOSE_STAGE stageSelect = static_cast<StageSelectScene::CHOOSE_STAGE>(m_stage);
	//	�X�e�[�W�́@3 || 4�@��?
	if (stageSelect != StageSelectScene::CHOOSE_STAGE::STAGE_3)		return;
}

/// <summary>
/// �`�悷��
/// </summary>
void Sun::Draw()
{
	//	�X�e�[�W�^�ɃL���X�g
	StageSelectScene::CHOOSE_STAGE stageSelect = static_cast<StageSelectScene::CHOOSE_STAGE>(m_stage);
	//	�X�e�[�W�́@3�@��?
	if (stageSelect != StageSelectScene::CHOOSE_STAGE::STAGE_3)		return;

	//	�X�v���C�g�o�b�`
	DirectX::SpriteBatch* spriteBatch = MyLib::ScreenResources::GetInstance()->GetSpriteBatch();
	//	�`����s��
	spriteBatch->Draw
	(
		m_sunTexture,
		m_position,
		nullptr,
		DirectX::Colors::White,
		0.0f,
		ORIGIN_SUN_TEXTURE,
		m_scale
	);
}

/// <summary>
/// �f�o�C�X�ˑ��̃��\�[�X�̏�����
/// </summary>
void Sun::CreateDeviceDependentResources()
{
	//	�摜
	m_sunTexture = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"sun");

	m_position = { 1200.0f, 0.0 };

	m_scale = { 1.5f, 1.5f };
}
