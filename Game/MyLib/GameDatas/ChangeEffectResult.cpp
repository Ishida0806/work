//
//		File Name �F ChangeEffectResult.cpp
//		Production�F 2023/1/17
//		Author�@�@�F �Γc ����	
//
#include "pch.h"
#include "ChangeEffectResult.h"

//	�t�F�[�h�̎���
const float						   ChangeEffectResult::RESULT_FADE_TIME = 5.6f;
//	�ޏo�t�F�[�h���̕␳�l
const float						   ChangeEffectResult::CORRECTION_OUT_FADE	= 0.6f;


/// <summary>
/// �R���X�g���N�^
/// </summary>
ChangeEffectResult::ChangeEffectResult()
	:ChangeEffect(ChangeEffect::ChangeSceneType::Result)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ChangeEffectResult::~ChangeEffectResult()
{
}

/// <summary>
/// ����������
/// </summary>
void ChangeEffectResult::Initialize()
{
	//	�摜�̐ݒ�
	ChangeEffect::SetTexure(MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"BlackTexture"));
}

/// <summary>
/// ���̃V�[���ɑJ�ڂ���
/// </summary>
void ChangeEffectResult::ToChange()
{
	if (GetElapsedTime() >= RESULT_FADE_TIME)
	{
		FinishedChangeScene();
	}
}

/// <summary>
/// �V�[���𔲂���
/// </summary>
void ChangeEffectResult::OutChange()
{
	DirectX::SimpleMath::Color color = GetColor();

	//	�A���t�@�l���ӂ�ӂ⓮����
	color.w = sinf(GetElapsedTime() * CORRECTION_OUT_FADE);

	SetColor(color);

	if (GetElapsedTime() >= RESULT_FADE_TIME)
	{
		FinishedChangeScene();
	}
}

/// <summary>
/// �G�t�F�N�g�̕`��
/// </summary>
void ChangeEffectResult::Draw()
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
void ChangeEffectResult::PreInitialize()
{

}