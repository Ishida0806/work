//
//		File Name ： SkyDome.h
//		Production： 2023/6/12
//		Author　　： 石田 恭一	
//	
#pragma once

class SkyDome final
{
	//	enum
public:

	enum class STAGE_STATE
	{
		stage1 = 0,
		stage2 = 1,
		stage3 = 2,
		stage4 = 3,
	};

	//	変数
private:
	//	スクリーンリソース
	MyLib::ScreenResources*		m_screens;
	//	画像
	ID3D11ShaderResourceView*	m_texture;
	//	スカイドーム
	DirectX::Model*				m_skyModel;
	//	ステージの番号
	int							m_stageNum;
	//	ステージのステート
	STAGE_STATE					m_stageState;

	//	関数
public:

	SkyDome(int stageNum);
	~SkyDome();

	//	描画
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj);
};

