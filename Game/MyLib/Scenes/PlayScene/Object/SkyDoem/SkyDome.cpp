//
//		File Name �F SkyDome.cpp
//		Production�F 2023/6/12
//		Author�@�@�F �Γc ����	
// 
//		�X�J�C�h�[���̕`����s��
//	
#include "pch.h"
#include "SkyDome.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
SkyDome::SkyDome(int stageNum)
	:m_stageNum(stageNum),
	m_screens(nullptr),
	m_texture(nullptr),
	m_skyModel(nullptr)
{
	//	�X�N���[�����\�[�X
	m_screens = MyLib::ScreenResources::GetInstance();
	//	�X�J�C���f��
	m_skyModel = MyLib::ResourcesData::GetInstance()->GatModel(L"skydoam");
	//	�X�e�[�W�X�e�[�g�^�ɃL���X�g
	m_stageState = static_cast<STAGE_STATE>(m_stageNum);

	//	�摜��ς���
	switch (m_stageState)
	{
	case SkyDome::STAGE_STATE::stage1:	m_texture = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"Sky_Fine");		break;
	case SkyDome::STAGE_STATE::stage2:	m_texture = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"Sky_Cloudy");		break;
	case SkyDome::STAGE_STATE::stage3:	m_texture = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"Sky_Evening");		break;
	case SkyDome::STAGE_STATE::stage4:	m_texture = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"Sky_Night");		break;
	default:																														break;
	}

	//	�����_���Ŋ֐��I�u�W�F�N�g��������
	m_skyModel->UpdateEffects
	(
		[&](DirectX::IEffect* effect)
		{
			//	���C�g�^
			auto lights = dynamic_cast<DirectX::IEffectLights*>(effect);
			//	�|�C���^�͑��݂��邩�H
			if (lights)
			{
				//	���C�g��؂�
				lights->SetLightEnabled(0, false);
				lights->SetLightEnabled(1, false);
				lights->SetLightEnabled(2, false);
				//	����
				lights->SetAmbientLightColor(DirectX::Colors::Black);
			}
			
			auto basicEffect = dynamic_cast<DirectX::BasicEffect*>(effect);
			//	�|�C���^�͑��݂��邩�H
			if (basicEffect)
			{
				//	���Ȕ���������
				basicEffect->SetEmissiveColor(DirectX::Colors::White);

				basicEffect->SetTexture(m_texture);
			}
		}
	);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
SkyDome::~SkyDome()
{
	
}

/// <summary>
///	�`�揈��
/// </summary>
/// <param name="view">�r���[</param>
/// <param name="proj">�v���W�F�N�V����</param>
void SkyDome::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	//	�����_���Ŋ֐��I�u�W�F�N�g��������
	m_skyModel->UpdateEffects
	(
		[&](DirectX::IEffect* effect)
		{
			auto basicEffect = dynamic_cast<DirectX::BasicEffect*>(effect);
			//	�|�C���^�͑��݂��邩�H
			if (basicEffect)
			{
				//	���C�g��؂�
				basicEffect->SetLightEnabled(0, false);
				basicEffect->SetLightEnabled(1, false);
				basicEffect->SetLightEnabled(2, false);
				//	����
				basicEffect->SetAmbientLightColor(DirectX::Colors::Black);
				//	���Ȕ���������
				basicEffect->SetEmissiveColor(DirectX::Colors::White);
				//	�摜��ς���
				basicEffect->SetTexture(m_texture);
			}
		}
	);


    // �X�J�C�h�[���̕`��
    m_skyModel->Draw(m_screens->GetDeviceContext(), *m_screens->GetCommonState(), DirectX::SimpleMath::Matrix::CreateScale(1.2f), view, proj);

	//	�����_���Ŋ֐��I�u�W�F�N�g��������
	m_skyModel->UpdateEffects
	(
		[&](DirectX::IEffect* effect)
		{
			auto basicEffect = dynamic_cast<DirectX::BasicEffect*>(effect);
			//	�L���X�g�ł������H
			if (basicEffect)
			{
				//	���C�g��؂�
				basicEffect->SetLightEnabled(0, true);
				basicEffect->SetLightEnabled(1, true);
				basicEffect->SetLightEnabled(2, true);
				//	����
				basicEffect->SetAmbientLightColor(DirectX::Colors::White);
				//	���Ȕ���������
				basicEffect->SetEmissiveColor(DirectX::Colors::White);
				//	�摜��ς���
				basicEffect->SetTexture(m_texture);
			}
		}
	);
}
