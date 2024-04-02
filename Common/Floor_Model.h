//--------------------------------------------------------------------------------------
// File: Floor_Model.h
//
// ���f���ɂ��n�ʂ̕`��
//
//-------------------------------------------------------------------------------------
#pragma once

class Floor_Model
{
public:

    /// <summary>
    /// �R���e�L�X�g
    /// </summary>
    Floor_Model();

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~Floor_Model();

    /// <summary>
    /// �`�揈��
    /// </summary>
    /// <param name="context">�R���e�L�X�g</param>
    /// <param name="view">�r���[</param>
    /// <param name="proj">�v���W�F�N�V����</param>
    /// <param name="value">�傫��</param>
    void Render(ID3D11DeviceContext1* context, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj,const float& value = 3.0f);

private:

    //  ���f��
    DirectX::Model* m_floorModel;
};


