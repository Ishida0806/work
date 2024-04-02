//-------------------------------------------------------------------------------------
// File: Floor_Model.cpp
//
// モデルによる地面の描画
//
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "Floor_Model.h"

using namespace DirectX;

/// <summary>
/// コンストラクタ
/// </summary>
Floor_Model::Floor_Model()
{   
    //  モデルを取得する
    m_floorModel = MyLib::ResourcesData::GetInstance()->GatModel(L"floor");

    //	ラムダ式で関数オブジェクトを引数に
    m_floorModel->UpdateEffects
    (
        [](DirectX::IEffect* effect)
        {
            //	テクスチャを変える
            auto basicEffect = dynamic_cast<DirectX::BasicEffect*>(effect);
            if (basicEffect)
            {
                //  画像を設定する
                basicEffect->SetTexture(MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"FloorTexture"));
            }
        }
    );
}

/// <summary>
/// デストラクタ
/// </summary>
Floor_Model::~Floor_Model()
{
    
}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="context">コンテキスト</param>
/// <param name="view">ビュー</param>
/// <param name="proj">プロジェクション</param>
/// <param name="value">大きさ</param>
void Floor_Model::Render(ID3D11DeviceContext1* context,SimpleMath::Matrix view, SimpleMath::Matrix proj, const float& value)
{
    //  拡大行列
    SimpleMath::Matrix scale = SimpleMath::Matrix::CreateScale(value);
    SimpleMath::Matrix world = scale;

    // 床の描画
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
                //  拡大する
                MyLib::ScreenResources::GetInstance()->GetCommonState()->PointWrap()
            };
            //  サンプラーを設定する
            context->PSSetSamplers(0, 1, samplers);            
        }
    );
}
