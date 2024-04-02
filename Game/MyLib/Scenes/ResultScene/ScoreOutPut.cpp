

#include "pch.h"
#include "ScoreOutPut.h"

#include "Common/ReadData.h"

#include "Game/MyLib/GameDatas/Number.h"
#include "Game/MyLib/GameDatas/PlayInfo.h"

//	�X�R�A�̍��W
const DirectX::SimpleMath::Vector2 ScoreOutPut::SCORE_POSITION		  = DirectX::SimpleMath::Vector2(670.0f, 320.0f);
//	�X�R�A�̐^�񒆂̍��W
const DirectX::SimpleMath::Vector2 ScoreOutPut::SCORE_ORIGIN_POSITION = DirectX::SimpleMath::Vector2(383.0f, 390.0f);

/// <summary>
/// �R���X�g���N�^
/// </summary>
ScoreOutPut::ScoreOutPut()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ScoreOutPut::~ScoreOutPut()
{
	AudioManager::GetInstance()->StopSoundEffect(L"Result_NumberChange");
}

/// <summary>
/// ����������
/// </summary>
void ScoreOutPut::Initialize()
{
	//	�ԍ��摜
	//m_numTexture = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"number");

	//	�X�R�A�\���̍쐬
	m_pScore = std::make_unique<Number>
		(
			MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"number"),
			DirectX::SimpleMath::Vector2(740.0f, 275.0f)
		);

	////	�ʏ�G
	//m_pNormalKnock = std::make_unique<Number>(DirectX::SimpleMath::Vector2(800.0f, 300.0f));
	////	�ˌ��G
	//m_pTackleKnock = std::make_unique<Number>(DirectX::SimpleMath::Vector2(800.0f, 350.0f));
	////	�{�X�G
	//m_pBossKnock   = std::make_unique<Number>(DirectX::SimpleMath::Vector2(800.0f, 400.0f));
	
	//	�v���C�C���t�H
	m_pPlayInfo = PlayInfo::GetInstance();

	//for (int i = 0; i < 3; i++)
	//{
	//	if(i / 3 ==0)
	//	m_pPlayInfo->KnockNormal();
	//	if(i / 2 == 0)
	//	m_pPlayInfo->KnockTackle();
	//	if(i / 5 == 0)
	//	m_pPlayInfo->KnockBoss();

	//	m_pPlayInfo->UpScore(3500);
	//}
}

/// <summary>
/// �X�V����
/// </summary>
bool ScoreOutPut::Update()
{
	m_pScore->Update(m_pPlayInfo->GetScore());
	//m_pNormalKnock->Update(m_pPlayInfo->GetNormalKnockNum());
	//m_pTackleKnock->Update(m_pPlayInfo->GetTackleKnockNum());
	//m_pBossKnock->Update(m_pPlayInfo->GetBossKnockNum());

	//	�X�R�A���ꏏ�Ȃ�`����\�ɂ���
	if (m_pScore->GetScore() == m_pPlayInfo->GetScore())
	{
		AudioManager::GetInstance()->StopSoundEffect(L"Result_NumberChange");
		return true;
	}

	//	SE���Đ�����
	AudioManager::GetInstance()->PlaySoundEffectRoopSE(L"Result_NumberChange");

	return false;
}

/// <summary>
/// �`�悷��
/// </summary>
void ScoreOutPut::Draw()
{
	//	�ē��L�[�̕`��



	//	�`����s��
	m_pScore->DrawNumber(2.0f, 0.8f);

	//	�`����s��
	//m_pNormalKnock->DrawNumber();
	//m_pTackleKnock->DrawNumber();
	//m_pBossKnock->DrawNumber();

#pragma region DEBUG

	//std::wostringstream oss;
	//oss << "score:" << m_pPlayInfo->GetScore();
	//MyLib::ScreenResources::GetInstance()->RenderDebugFont(oss.str().c_str(), DirectX::SimpleMath::Vector2(500.0f, 220.0f));

	//std::wostringstream oss2;
	//oss2 << "normal:" << m_pPlayInfo->GetNormalKnockNum();
	//MyLib::ScreenResources::GetInstance()->RenderDebugFont(oss2.str().c_str(), DirectX::SimpleMath::Vector2(500.0f, 320.0f));
	//
	//std::wostringstream oss3;
	//oss3 << "tackle:" << m_pPlayInfo->GetTackleKnockNum();
	//MyLib::ScreenResources::GetInstance()->RenderDebugFont(oss3.str().c_str(), DirectX::SimpleMath::Vector2(500.0f, 350.0f));
	//
	//std::wostringstream oss4;
	//oss4 << "boss:" << m_pPlayInfo->GetBossKnockNum();
	//MyLib::ScreenResources::GetInstance()->RenderDebugFont(oss4.str().c_str(), DirectX::SimpleMath::Vector2(500.0f, 380.0f));
	//
	//std::wostringstream oss5;
	//oss5 << "time:" << m_pPlayInfo->GetElapseedTime();
	//MyLib::ScreenResources::GetInstance()->RenderDebugFont(oss5.str().c_str(), DirectX::SimpleMath::Vector2(500.0f, 400.0f));
#pragma endregion
}