//
//		File Name �F ChangeEffectPlay.cpp
//		Production�F 2023/1/17
//		Author�@�@�F �Γc ����	
//
#include "pch.h"
#include "ChangeEffectPlay.h"

//	�t�F�[�h�̎���
const float						   ChangeEffectPlay::PLAY_FADE_TIME			= 2.8f;
//	�A���t�@�̒l�̌���l
const float						   ChangeEffectPlay::DIMINISH_ALFA_VALUE	= 0.005f;
//	�ޏo�t�F�[�h���̕␳�l
const float						   ChangeEffectPlay::CORRECTION_OUT_FADE	= 0.42f;


/// <summary>
///�R���X�g���N�^
/// </summary>
ChangeEffectPlay::ChangeEffectPlay()
	:ChangeEffect(ChangeEffect::ChangeSceneType::Play)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ChangeEffectPlay::~ChangeEffectPlay()
{
}

/// <summary>
/// ����������
/// </summary>
void ChangeEffectPlay::Initialize()
{
	//	�摜�̐ݒ�
	ChangeEffect::SetTexure(MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"BlackTexture"));
}

/// <summary>
/// ���̃V�[���ɑJ�ڂ���
/// </summary>
void ChangeEffectPlay::ToChange()
{
	DirectX::SimpleMath::Color color = GetColor();

	//	�A���t�@�l���������Âւ炷
	color.w -= DIMINISH_ALFA_VALUE;

	SetColor(color);

	if (GetColor().w < 0.0f)
	{
		FinishedChangeScene();
	}
}

/// <summary>
/// �V�[���𔲂���
/// </summary>
void ChangeEffectPlay::OutChange()
{
	DirectX::SimpleMath::Color color = GetColor();

	//	�A���t�@�l���ӂ�ӂ⓮����
	color.w = sinf(GetElapsedTime() * CORRECTION_OUT_FADE);

	SetColor(color);

	if (GetElapsedTime() >= PLAY_FADE_TIME)
	{
		FinishedChangeScene();
	}
}

/// <summary>
/// �G�t�F�N�g�̕`��
/// </summary>
void ChangeEffectPlay::Draw()
{
	//	�h�A�̍�����\��
	MyLib::ScreenResources::GetInstance()->GetSpriteBatch()->Draw
	(
		GetTexture(),
		DirectX::SimpleMath::Vector2::Zero,
		GetColor()
	);
}

/// <summary>
/// ���O�̏��������s��
/// </summary>
void ChangeEffectPlay::PreInitialize()
{
	if (GetChangeFadeType() == ChangeEffect::ChangeSceneFadeType::To)
	{
		DirectX::SimpleMath::Color color = GetColor();

		//	�F�̔Z�������߂�
		color.x = 1.0f;
		color.y = 1.0f;
		color.z = 1.0f;
		color.w = 0.8f;

		SetColor(color);
	}
}