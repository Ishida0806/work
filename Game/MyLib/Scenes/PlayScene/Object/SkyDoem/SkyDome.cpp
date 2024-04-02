//
//		File Name ： SkyDome.cpp
//		Production： 2023/6/12
//		Author　　： 石田 恭一	
// 
//		スカイドームの描画を行う
//	
#include "pch.h"
#include "SkyDome.h"

/// <summary>
/// コンストラクタ
/// </summary>
SkyDome::SkyDome(int stageNum)
	:m_stageNum(stageNum),
	m_screens(nullptr),
	m_texture(nullptr),
	m_skyModel(nullptr)
{
	//	スクリーンリソース
	m_screens = MyLib::ScreenResources::GetInstance();
	//	スカイモデル
	m_skyModel = MyLib::ResourcesData::GetInstance()->GatModel(L"skydoam");
	//	ステージステート型にキャスト
	m_stageState = static_cast<STAGE_STATE>(m_stageNum);

	//	画像を変える
	switch (m_stageState)
	{
	case SkyDome::STAGE_STATE::stage1:	m_texture = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"Sky_Fine");		break;
	case SkyDome::STAGE_STATE::stage2:	m_texture = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"Sky_Cloudy");		break;
	case SkyDome::STAGE_STATE::stage3:	m_texture = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"Sky_Evening");		break;
	case SkyDome::STAGE_STATE::stage4:	m_texture = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"Sky_Night");		break;
	default:																														break;
	}

	//	ラムダ式で関数オブジェクトを引数に
	m_skyModel->UpdateEffects
	(
		[&](DirectX::IEffect* effect)
		{
			//	ライト型
			auto lights = dynamic_cast<DirectX::IEffectLights*>(effect);
			//	ポインタは存在するか？
			if (lights)
			{
				//	ライトを切る
				lights->SetLightEnabled(0, false);
				lights->SetLightEnabled(1, false);
				lights->SetLightEnabled(2, false);
				//	環境光
				lights->SetAmbientLightColor(DirectX::Colors::Black);
			}
			
			auto basicEffect = dynamic_cast<DirectX::BasicEffect*>(effect);
			//	ポインタは存在するか？
			if (basicEffect)
			{
				//	自己発光させる
				basicEffect->SetEmissiveColor(DirectX::Colors::White);

				basicEffect->SetTexture(m_texture);
			}
		}
	);
}

/// <summary>
/// デストラクタ
/// </summary>
SkyDome::~SkyDome()
{
	
}

/// <summary>
///	描画処理
/// </summary>
/// <param name="view">ビュー</param>
/// <param name="proj">プロジェクション</param>
void SkyDome::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	//	ラムダ式で関数オブジェクトを引数に
	m_skyModel->UpdateEffects
	(
		[&](DirectX::IEffect* effect)
		{
			auto basicEffect = dynamic_cast<DirectX::BasicEffect*>(effect);
			//	ポインタは存在するか？
			if (basicEffect)
			{
				//	ライトを切る
				basicEffect->SetLightEnabled(0, false);
				basicEffect->SetLightEnabled(1, false);
				basicEffect->SetLightEnabled(2, false);
				//	環境光
				basicEffect->SetAmbientLightColor(DirectX::Colors::Black);
				//	自己発光させる
				basicEffect->SetEmissiveColor(DirectX::Colors::White);
				//	画像を変える
				basicEffect->SetTexture(m_texture);
			}
		}
	);


    // スカイドームの描画
    m_skyModel->Draw(m_screens->GetDeviceContext(), *m_screens->GetCommonState(), DirectX::SimpleMath::Matrix::CreateScale(1.2f), view, proj);

	//	ラムダ式で関数オブジェクトを引数に
	m_skyModel->UpdateEffects
	(
		[&](DirectX::IEffect* effect)
		{
			auto basicEffect = dynamic_cast<DirectX::BasicEffect*>(effect);
			//	キャストできたか？
			if (basicEffect)
			{
				//	ライトを切る
				basicEffect->SetLightEnabled(0, true);
				basicEffect->SetLightEnabled(1, true);
				basicEffect->SetLightEnabled(2, true);
				//	環境光
				basicEffect->SetAmbientLightColor(DirectX::Colors::White);
				//	自己発光させる
				basicEffect->SetEmissiveColor(DirectX::Colors::White);
				//	画像を変える
				basicEffect->SetTexture(m_texture);
			}
		}
	);
}
