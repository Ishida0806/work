//
//		File Name �F StarManager.cpp
//		Production�F 2023/11/02
//		Author�@�@�F �Γc ����
// 
//		���ɕ����Ԑ������̍X�V���s��
// 
#include "pch.h"
#include "StarManager.h"

#include "StageSelectScene.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="backGroundTexture">�摜</param>
StarManager::StarManager(ID3D11ShaderResourceView* starTexture)
	:m_starTexture(starTexture),
	m_stage(0)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
StarManager::~StarManager()
{
}

/// <summary>
/// ����������
/// </summary>
void StarManager::Initialize()
{
	for (int i = 0; i < 50; i++)
	{
		//	�����_���ȍ��W
		DirectX::SimpleMath::Vector2 randomPosition = DirectX::SimpleMath::Vector2(Utility::CreateRandom(100.0f, 1155.0f), Utility::CreateRandom(100.0f, 175.0f));
		//	�����_���ȑ傫��
		DirectX::SimpleMath::Vector2 randomScale	= DirectX::SimpleMath::Vector2(Utility::CreateRandom(0.05f, 0.1f), Utility::CreateRandom(0.05f, 0.1f));
		//	��������
		float randomLifeCount							= Utility::CreateRandom(1.3f, 12.2f);
		//	���x
		float speed = Utility::CreateRandom(0.03f, 0.05f);
					
		//	���̗v�f��ǉ�����
		m_stars.push_back
		(
			std::make_unique<Star>
			(
				m_starTexture,
				randomPosition,
				DirectX::SimpleMath::Vector4::One,
				randomScale,
				speed,
				randomLifeCount
			)
		);
		//	����������
		m_stars[i]->Initialize();
	}
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="timer">�^�C�}�[</param>
/// <param name="selectStage">�X�e�[�W�Z���N�g�i���o�[</param>
void StarManager::Update(const DX::StepTimer& timer, const int& selectStage)
{
	m_stage = selectStage;

	//	�X�e�[�W�^�ɃL���X�g
	StageSelectScene::CHOOSE_STAGE stageSelect = static_cast<StageSelectScene::CHOOSE_STAGE>(m_stage);

	//	�X�e�[�W4�ȍ~�͋A��
	if (stageSelect != StageSelectScene::CHOOSE_STAGE::STAGE_4)	return;

	//	�����X�V����
	for (const auto& star : m_stars) star->Update(timer);
}

/// <summary>
/// �`�悷��
/// </summary>
void StarManager::Draw()
{
	//	�X�e�[�W�^�ɃL���X�g
	StageSelectScene::CHOOSE_STAGE stageSelect = static_cast<StageSelectScene::CHOOSE_STAGE>(m_stage);

	//	�X�e�[�W4�ȍ~�͋A��
	if (stageSelect != StageSelectScene::CHOOSE_STAGE::STAGE_4)	return;

	//	����`�悷��
	for (const auto& star : m_stars)	star->Draw();
}

/// <summary>
/// �I������
/// </summary>
void StarManager::Finalize()
{
	//	�����I���������s��
	for (const auto& star : m_stars)		star->Finalize();
}
