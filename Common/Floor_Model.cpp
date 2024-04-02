//-------------------------------------------------------------------------------------
// File: Floor_Model.cpp
//
// ���f���ɂ��n�ʂ̕`��
//
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "Floor_Model.h"

using namespace DirectX;

/// <summary>
/// �R���X�g���N�^
/// </summary>
Floor_Model::Floor_Model()
{   
    //  ���f�����擾����
    m_floorModel = MyLib::ResourcesData::GetInstance()->GatModel(L"floor");

    //	�����_���Ŋ֐��I�u�W�F�N�g��������
    m_floorModel->UpdateEffects
    (
        [](DirectX::IEffect* effect)
        {
            //	�e�N�X�`����ς���
            auto basicEffect = dynamic_cast<DirectX::BasicEffect*>(effect);
            if (basicEffect)
            {
                //  �摜��ݒ肷��
                basicEffect->SetTexture(MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"FloorTexture"));
            }
        }
    );
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Floor_Model::~Floor_Model()
{
    
}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="context">�R���e�L�X�g</param>
/// <param name="view">�r���[</param>
/// <param name="proj">�v���W�F�N�V����</param>
/// <param name="value">�傫��</param>
void Floor_Model::Render(ID3D11DeviceContext1* context,SimpleMath::Matrix view, SimpleMath::Matrix proj, const float& value)
{
    //  �g��s��
    SimpleMath::Matrix scale = SimpleMath::Matrix::CreateScale(value);
    SimpleMath::Matrix world = scale;

    // ���̕`��
    m_floorModel->Draw
    (
        context,
        *MyLib::ScreenResources::GetInstance()->GetCommonState(),
        world,
        view,
        proj,
        false,
        [&]() 
        {
            ID3D11SamplerState* samplers[] =
            { 
                //  �g�傷��
                MyLib::ScreenResources::GetInstance()->GetCommonState()->PointWrap()
            };
            //  �T���v���[��ݒ肷��
            context->PSSetSamplers(0, 1, samplers);            
        }
    );
}
