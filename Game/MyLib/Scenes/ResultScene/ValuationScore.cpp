//
//		File Name �F ValuationScore.cpp
//		Production�F 2023/11/12
//		Author�@�@�F �Γc ����	
// 
//		�N���A���̕]���l�����߂�
//
#include "pch.h"
#include "ValuationScore.h"

#include "Game/MyLib/Scenes/StageSelect/StageSelectScene.h"

//	�����̑�����
const double					   ValuationScore::INCREASE_BOTTOM			  = 12.0;
//	�]���̏ꏊ
const DirectX::SimpleMath::Vector2 ValuationScore::VALUCATION_POSITION		  = DirectX::SimpleMath::Vector2(740.0f, 500.0f);
//	�]���̐^�񒆂̏ꏊ
const DirectX::SimpleMath::Vector2 ValuationScore::VALUCATION_ORIGIN_POSITION = DirectX::SimpleMath::Vector2(281.0f, 193.5f);
//	�]���摜�̑傫��
const DirectX::SimpleMath::Vector2 ValuationScore::VALUCATION_BASE_SCALE	  = DirectX::SimpleMath::Vector2(0.7f, 0.7f);
//	�Ȃ���p�x
const float						   ValuationScore::TARGET_ANGLE				  = 15.0f;
//	�C�[�W�[�X�e�[�W���Z���N�g���ꂽ
const int						   ValuationScore::SELECT_EASY			 	  = 100;
//	�m�[�}���X�e�[�W���Z���N�g���ꂽ
const int						   ValuationScore::SELECT_NORMAL			  = 200;
//	�n�[�h�X�e�[�W���Z���N�g���ꂽ
const int						   ValuationScore::SELECT_HARD				  = 300;
//	�G���h���X�X�e�[�W���Z���N�g���ꂽ
const int						   ValuationScore::SELECT_ENDRES			  = 1000;

/// <summary>
/// �R���X�g���N�^
/// </summary>
ValuationScore::ValuationScore()
	:m_valutationTex(nullptr),
	m_res(nullptr),
	m_isDraw(false)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ValuationScore::~ValuationScore()
{
}

/// <summary>
/// ����������
/// </summary>
/// <param name="selectStage">�Z���N�g���ꂽ�X�e�[�W�ԍ�</param>
/// <param name="score">�X�R�A</param>
void ValuationScore::Initialize(const int& selectStage, const int& score)
{
	//	�X�e�[�W���^�ɂ���
	StageSelectScene::CHOOSE_STAGE stage = static_cast<StageSelectScene::CHOOSE_STAGE>(selectStage);

	//	�]���X�R�A
	int valuationScore = 0;

	//	���\�[�X�f�[�^
	m_res = MyLib::ResourcesData::GetInstance();

	//	�X�e�[�W�ɂ���ĕ]�����ς���
	switch (stage)
	{
	case StageSelectScene::CHOOSE_STAGE::STAGE_1:valuationScore = SELECT_EASY;		break;
	case StageSelectScene::CHOOSE_STAGE::STAGE_2:valuationScore = SELECT_NORMAL;	break;
	case StageSelectScene::CHOOSE_STAGE::STAGE_3:valuationScore = SELECT_HARD;		break;
	case StageSelectScene::CHOOSE_STAGE::STAGE_4:valuationScore = SELECT_ENDRES;	break;
	case StageSelectScene::CHOOSE_STAGE::OverID:									break;
	default:																		break;
	}

	//	�]���ɂ���ĉ摜��ς���
	if (score >= valuationScore)
	{
		m_valutationTex = m_res->GatShaderResourceView(L"valuationS");
	}
	else if (score >= valuationScore / 2 && score < valuationScore)
	{
		m_valutationTex = m_res->GatShaderResourceView(L"valuationA");
	}
	else if (score >= valuationScore / 3 && score < valuationScore / 2)
	{
		m_valutationTex = m_res->GatShaderResourceView(L"valuationB");
	}
	else if (score < valuationScore / 3)
	{
		m_valutationTex = m_res->GatShaderResourceView(L"valuationC");
	}	
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="isTop">��ɏオ�������H</param>
void ValuationScore::Update(const bool& isTop)
{
	m_isDraw = isTop;
}

/// <summary>
/// �`�揈��
/// </summary>
void ValuationScore::Draw()
{
	//	�㑤�ɏオ���Ă��Ȃ��Ȃ�A��
	if (!m_isDraw)	return;

	MyLib::ScreenResources::GetInstance()->GetSpriteBatch()->Draw
	(
		m_valutationTex,
		VALUCATION_POSITION,
		nullptr,
		DirectX::Colors::White,
		DirectX::XMConvertToRadians(TARGET_ANGLE),
		VALUCATION_ORIGIN_POSITION,
		VALUCATION_BASE_SCALE 
	);
}

/// <summary>
/// �I������
/// </summary>
void ValuationScore::FInalize()
{
}
