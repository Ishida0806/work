//
//		File Name �F ChageSceneEffect.cpp
//		Production�F 2023/1/17
//		Author�@�@�F �Γc ����	
// 
//		�V�[���J�ڂ̍ۂ̃G�t�F�N�g�̍X�V�E�`��
//
#include "pch.h"
#include "ChageSceneEffect.h"
#include "Game/Game.h"

#include "ChangeEffectPlay.h"
#include "ChangeEffectTitle.h"
#include "ChangeEffectResult.h"
#include "ChangeEffectStageSelect.h"

/// <summary>
/// ����������
/// </summary>
/// <param name="game">�Q�[��</param>
ChageSceneEffect::ChageSceneEffect(Game* game)
	:m_game(game)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ChageSceneEffect::~ChageSceneEffect()
{
}

/// <summary>
/// ����������
/// </summary>
void ChageSceneEffect::Initialize()
{
	//	
	m_fadeEffects.push_back(std::make_unique<ChangeEffectTitle>());
	m_fadeEffects.push_back(std::make_unique<ChangeEffectStageSelect>());
	m_fadeEffects.push_back(std::make_unique<ChangeEffectPlay>());
	m_fadeEffects.push_back(std::make_unique<ChangeEffectResult>());

	//	���������s��
	for (const auto& fadeEffect : m_fadeEffects)
	{
		fadeEffect->Initialize();
	}
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void ChageSceneEffect::Update(const DX::StepTimer& timer)
{
	for (const auto& fadeEffect : m_fadeEffects)
	{
		//	�t���O���Ȃ���΋A��
		if (fadeEffect->GetChangeFadeType() == ChangeEffect::ChangeSceneFadeType::None)	continue;

		//	�o�ߎ��Ԃ��X�V����
		fadeEffect->UpdateElapsedTime(timer);

		//	�V�[���̃t�F�[�h�̓��ꏈ�����s��
		if (fadeEffect->GetChangeFadeType() == ChangeEffect::ChangeSceneFadeType::To)
		{
			fadeEffect->ToChange();
		}
		//	�V�[���̃t�F�[�h�̑ޏo�������s��
		if (fadeEffect->GetChangeFadeType() == ChangeEffect::ChangeSceneFadeType::Out)
		{
			fadeEffect->OutChange();
		}
	}
}

/// <summary>
/// �G�t�F�N�g�̕`��
/// </summary>
void ChageSceneEffect::DrawEffect()
{
	//	�`����J�n����
	MyLib::ScreenResources::GetInstance()->GetSpriteBatch()->Begin();

	for (const auto& fadeEffect : m_fadeEffects)
	{
		if (fadeEffect->GetChangeFadeType() != ChangeEffect::ChangeSceneFadeType::None)
		{
			fadeEffect->Draw();
		}
	}
	//	�`����I������
	MyLib::ScreenResources::GetInstance()->GetSpriteBatch()->End();
}

/// <summary>
/// �V�[���J�ڂ̃G�t�F�N�g�̗v����ݒ�
/// </summary>
/// <param name="requestType">���N�G�X�g�^�C�v</param>
/// <param name="fadeType">�t�@�[�h�^�C�v</param>
void ChageSceneEffect::RequestChangeEffect(const ChangeEffect::ChangeSceneType& requestType, const ChangeEffect::ChangeSceneFadeType& fadeType)
{
	for (const auto& fadeEffect : m_fadeEffects)
	{
		//	�Ώۂ̃t�F�[�h�Ώۂ�T�� 
		if (fadeEffect->GetChangeType() == requestType)
		{
			//	�t�F�[�h�^�C�v�����Z�b�g����
			fadeEffect->SetSceneFadeType(fadeType);
			//	���ԂƐF���̓��Z�b�g����
			fadeEffect->ResetColorAndTime();
			//	���O�ɏ�����������̂�����Ώ��������s��
			fadeEffect->PreInitialize();
		}
	}
}