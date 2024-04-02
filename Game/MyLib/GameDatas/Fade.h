//
//		File Name ： Fade.h
//		Production： 2023/9/11
//		Author　　： 石田 恭一
// 
#pragma once

class Fade
{
	//	定数
public:
	//	ラープタイム
	static const float LERP_TIME;
	//	終わるタイム
	static const float FIN_TIME;

	//	アクセサ
public:

	inline bool GetFinFlag()	const { return m_finFlag; }

	//	変数
private:
	//	リソースデータ
	MyLib::ResourcesData* m_resources;
	//  スクリーンリソース
	MyLib::ScreenResources* m_screen;
	//	黒の画像
	ID3D11ShaderResourceView* m_blackTexture;
	//	スタートフラグ
	bool	m_startFlag;
	//	終了フラグ
	bool	m_finFlag;
	//	秒数
	float	m_second;


	//	関数
public:

	Fade();
	~Fade();

	void Initialize();
	void Update(const DX::StepTimer& timer);
	void Render();
	void Finalize();

	void StartFade();
};