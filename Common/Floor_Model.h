//--------------------------------------------------------------------------------------
// File: Floor_Model.h
//
// モデルによる地面の描画
//
//-------------------------------------------------------------------------------------
#pragma once

class Floor_Model
{
public:

    /// <summary>
    /// コンテキスト
    /// </summary>
    Floor_Model();

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~Floor_Model();

    /// <summary>
    /// 描画処理
    /// </summary>
    /// <param name="context">コンテキスト</param>
    /// <param name="view">ビュー</param>
    /// <param name="proj">プロジェクション</param>
    /// <param name="value">大きさ</param>
    void Render(ID3D11DeviceContext1* context, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj,const float& value = 3.0f);

private:

    //  モデル
    DirectX::Model* m_floorModel;
};


