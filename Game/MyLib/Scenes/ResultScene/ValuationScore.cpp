//
//		File Name ： ValuationScore.cpp
//		Production： 2023/11/12
//		Author　　： 石田 恭一	
// 
//		クリア時の評価値を決める
//
#include "pch.h"
#include "ValuationScore.h"

#include "Game/MyLib/Scenes/StageSelect/StageSelectScene.h"

//	下幅の増加量
const double					   ValuationScore::INCREASE_BOTTOM			  = 12.0;
//	評価の場所
const DirectX::SimpleMath::Vector2 ValuationScore::VALUCATION_POSITION		  = DirectX::SimpleMath::Vector2(740.0f, 500.0f);
//	評価の真ん中の場所
const DirectX::SimpleMath::Vector2 ValuationScore::VALUCATION_ORIGIN_POSITION = DirectX::SimpleMath::Vector2(281.0f, 193.5f);
//	評価画像の大きさ
const DirectX::SimpleMath::Vector2 ValuationScore::VALUCATION_BASE_SCALE	  = DirectX::SimpleMath::Vector2(0.7f, 0.7f);
//	曲げる角度
const float						   ValuationScore::TARGET_ANGLE				  = 15.0f;
//	イージーステージがセレクトされた
const int						   ValuationScore::SELECT_EASY			 	  = 100;
//	ノーマルステージがセレクトされた
const int						   ValuationScore::SELECT_NORMAL			  = 200;
//	ハードステージがセレクトされた
const int						   ValuationScore::SELECT_HARD				  = 300;
//	エンドレスステージがセレクトされた
const int						   ValuationScore::SELECT_ENDRES			  = 1000;

/// <summary>
/// コンストラクタ
/// </summary>
ValuationScore::ValuationScore()
	:m_valutationTex(nullptr),
	m_res(nullptr),
	m_isDraw(false)
{
}

/// <summary>
/// デストラクタ
/// </summary>
ValuationScore::~ValuationScore()
{
}

/// <summary>
/// 初期化処理
/// </summary>
/// <param name="selectStage">セレクトされたステージ番号</param>
/// <param name="score">スコア</param>
void ValuationScore::Initialize(const int& selectStage, const int& score)
{
	//	ステージ情報型にする
	StageSelectScene::CHOOSE_STAGE stage = static_cast<StageSelectScene::CHOOSE_STAGE>(selectStage);

	//	評価スコア
	int valuationScore = 0;

	//	リソースデータ
	m_res = MyLib::ResourcesData::GetInstance();

	//	ステージによって評価基準を変える
	switch (stage)
	{
	case StageSelectScene::CHOOSE_STAGE::STAGE_1:valuationScore = SELECT_EASY;		break;
	case StageSelectScene::CHOOSE_STAGE::STAGE_2:valuationScore = SELECT_NORMAL;	break;
	case StageSelectScene::CHOOSE_STAGE::STAGE_3:valuationScore = SELECT_HARD;		break;
	case StageSelectScene::CHOOSE_STAGE::STAGE_4:valuationScore = SELECT_ENDRES;	break;
	case StageSelectScene::CHOOSE_STAGE::OverID:									break;
	default:																		break;
	}

	//	評価によって画像を変える
	if (score >= valuationScore)
	{
		m_valutationTex = m_res->GatShaderResourceView(L"valuationS");
	}
	else if (score >= valuationScore / 2 && score < valuationScore)
	{
		m_valutationTex = m_res->GatShaderResourceView(L"valuationA");
	}
	else if (score >= valuationScore / 3 && score < valuationScore / 2)
	{
		m_valutationTex = m_res->GatShaderResourceView(L"valuationB");
	}
	else if (score < valuationScore / 3)
	{
		m_valutationTex = m_res->GatShaderResourceView(L"valuationC");
	}	
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="isTop">上に上がったか？</param>
void ValuationScore::Update(const bool& isTop)
{
	m_isDraw = isTop;
}

/// <summary>
/// 描画処理
/// </summary>
void ValuationScore::Draw()
{
	//	上側に上がっていないなら帰れ
	if (!m_isDraw)	return;

	MyLib::ScreenResources::GetInstance()->GetSpriteBatch()->Draw
	(
		m_valutationTex,
		VALUCATION_POSITION,
		nullptr,
		DirectX::Colors::White,
		DirectX::XMConvertToRadians(TARGET_ANGLE),
		VALUCATION_ORIGIN_POSITION,
		VALUCATION_BASE_SCALE 
	);
}

/// <summary>
/// 終了処理
/// </summary>
void ValuationScore::FInalize()
{
}
