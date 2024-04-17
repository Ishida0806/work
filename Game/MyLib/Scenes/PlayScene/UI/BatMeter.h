//
//		File Name ： PlayerUI.h
//		Production： 2023/10/2
//		Author　　： 石田 恭一
// 
#pragma once
#include "Game/MyLib/GameDatas/IUI.h"

interface IUI;
class Sord;

class BatMeter : public IUI
{
	//	アクセサ
public:

	//	ソードのポインターを設定する
	void SetSord(Sord* sord);

	//	定数
public:

	//	バットメーターの真ん中
	static const DirectX::SimpleMath::Vector2 ORIGIN_BAT_METER;
	//	バットメーターの側の真ん中
	static const DirectX::SimpleMath::Vector2 ORIGIN_BAT_SIDE_METER;
	//	バットメーターの座標
	static const DirectX::SimpleMath::Vector2 BAT_METER_POSITION;
	//	バットメーター側のの座標
	static const DirectX::SimpleMath::Vector2 BAT_SIDE_METER_POSITION;

	//	変数
private:

	//	ソード
	Sord*							m_sord;
	//	スクリーンリソース
	MyLib::ScreenResources*			m_screen;
	//	リソーシーズデータ
	MyLib::ResourcesData*			m_resources;
	//	調子の少し悪いプレイヤーの画像
	ID3D11ShaderResourceView*		m_batMeter;
	//	死んだときの画像
	ID3D11ShaderResourceView*		m_batSideMeter;
	//	バットメーター座標
	DirectX::SimpleMath::Vector2    m_batMeterPosition;
	//	バットサイドメーター座標
	DirectX::SimpleMath::Vector2	m_batMeterSidePosition;

	//	関数
public:

	//	コンストラクタ
	BatMeter();
	//	デストラクタ
	~BatMeter();

	//	初期化処理
	void Initialize() override;
	//	更新処理
	void Update(const DX::StepTimer& timer) override;
	//	描画する
	void Draw() override;

	//	埋め込み関数
private:
	//	デバイス依存のリソースの初期化
	void CreateDeviceDependentResources();
};