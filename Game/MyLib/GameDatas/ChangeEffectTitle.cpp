//
//		File Name �F ChangeEffectTitle.cpp
//		Production�F 2023/1/17
//		Author�@�@�F �Γc ����	
//
#include "pch.h"
#include "ChangeEffectTitle.h"


//	�t�F�[�h�̎���
const float ChangeEffectTitle::TITLE_FADE_TIME = 3.2f;

/// <summary>
/// �R���X�g���N�^
/// </summary>
ChangeEffectTitle::ChangeEffectTitle()
	:ChangeEffect(ChangeEffect::ChangeSceneType::Title)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ChangeEffectTitle::~ChangeEffectTitle()
{
}

/// <summary>
/// ����������
/// </summary>
void ChangeEffectTitle::Initialize()
{
	//	�摜�̐ݒ�
	ChangeEffect::SetTexure(MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"BlackTexture"));
}

/// <summary>
/// ���̃V�[���ɑJ�ڂ���
/// </summary>
void ChangeEffectTitle::ToChange()
{
	DirectX::SimpleMath::Color color = GetColor();

	color.x = 1.0f;
	color.y = 1.0f;
	color.z = 1.0f;
	color.w = sinf(GetElapsedTime());

	SetColor(color);

	if (GetElapsedTime() >= TITLE_FADE_TIME)
	{
		FinishedChangeScene();
	}
}

/// <summary>
/// �V�[���𔲂���
/// </summary>
void ChangeEffectTitle::OutChange()
{
	DirectX::SimpleMath::Color color = GetColor();

	color.x = 1.0f;
	color.y = 1.0f;
	color.z = 1.0f;
	color.w = sinf(GetElapsedTime());

	SetColor(color);

	if (GetElapsedTime() >= TITLE_FADE_TIME)
	{
		FinishedChangeScene();
	}
}

/// <summary>
/// �G�t�F�N�g�̕`��
/// </summary>
void ChangeEffectTitle::Draw()
{
	MyLib::ScreenResources::GetInstance()->GetSpriteBatch()->Draw
	(
		GetTexture(),
		DirectX::SimpleMath::Vector2::Zero,
		GetColor()
	);
}
