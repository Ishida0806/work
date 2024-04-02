//
//		File Name ： ChangeEffectStageSelect.cpp
//		Production： 2023/1/17
//		Author　　： 石田 恭一	
//
#include "pch.h"
#include "ChangeEffectStageSelect.h"

//	フェードの時間
const float						   ChangeEffectStageSelect::STAGE_FADE_TIME					= 7.2f;
//	ドアの動く速度
const float						   ChangeEffectStageSelect::DOOR_MOVE_SPEED					= 12.0f;
//	ステージの入場する際のドアの右側の座標
const DirectX::SimpleMath::Vector2 ChangeEffectStageSelect::STAGE_TO_RIGHT_DOOR_POSITION	= DirectX::SimpleMath::Vector2(200.0f, 0.0);
//	ステージの入場する際のドアの左側の座標
const DirectX::SimpleMath::Vector2 ChangeEffectStageSelect::STAGE_TO_LEFT_DOOR_POSITION		= DirectX::SimpleMath::Vector2(-200.0f, 0.0);
//	ステージの退場する際のドアの右側の座標
const DirectX::SimpleMath::Vector2 ChangeEffectStageSelect::STAGE_OUT_RIGHT_DOOR_POSITION	= DirectX::SimpleMath::Vector2(1200.0f, 0.0);
//	ステージの退場する際のドアの左側の座標
const DirectX::SimpleMath::Vector2 ChangeEffectStageSelect::STAGE_OUT_LEFT_DOOR_POSITION	= DirectX::SimpleMath::Vector2(-1200.0f, 0.0);

/// <summary>
/// コンストラクタ
/// </summary>
ChangeEffectStageSelect::ChangeEffectStageSelect()
	:ChangeEffect(ChangeEffect::ChangeSceneType::Select)
{
}

/// <summary>
/// デストラクタ
/// </summary>
ChangeEffectStageSelect::~ChangeEffectStageSelect()
{
}

/// <summary>
/// 初期化処理
/// </summary>
void ChangeEffectStageSelect::Initialize()
{
	//	画像の設定
	ChangeEffect::SetTexure(MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"BlackTexture"));

	//	座標の初期化
	m_blackRightPos = STAGE_TO_RIGHT_DOOR_POSITION;
	m_blackLeftPos  = STAGE_TO_LEFT_DOOR_POSITION;
}

/// <summary>
/// そのシーンに遷移する
/// </summary>
void ChangeEffectStageSelect::ToChange()
{
	//	右側左側共に画面外にフェードアウトするように
	m_blackLeftPos.x  -= DOOR_MOVE_SPEED;
	m_blackRightPos.x += DOOR_MOVE_SPEED;

	if (GetElapsedTime() >= STAGE_FADE_TIME)
	{
		FinishedChangeScene();
	}
}

/// <summary>
/// シーンを抜ける
/// </summary>
void ChangeEffectStageSelect::OutChange()
{
	if (GetElapsedTime() >= STAGE_FADE_TIME)
	{
		FinishedChangeScene();
	}
}

/// <summary>
/// エフェクトの描画
/// </summary>
void ChangeEffectStageSelect::Draw()
{
	//	ドアの左側を表示
	MyLib::ScreenResources::GetInstance()->GetSpriteBatch()->Draw
	(
		GetTexture(),
		m_blackLeftPos
	);
	//	ドアの右側を表示
	MyLib::ScreenResources::GetInstance()->GetSpriteBatch()->Draw
	(
		GetTexture(),
		m_blackRightPos
	);
}

/// <summary>
/// 事前の初期化を行う
/// </summary>
void ChangeEffectStageSelect::PreInitialize()
{
	//	入場の場合
	if (GetChangeFadeType() == ChangeEffect::ChangeSceneFadeType::To)
	{
		//	座標の初期化
		m_blackRightPos = STAGE_TO_RIGHT_DOOR_POSITION;
		m_blackLeftPos  = STAGE_TO_LEFT_DOOR_POSITION;
	}
	//	退場の場合
	//if (GetChangeFadeType() == ChangeEffect::ChangeSceneFadeType::Out)
	//{
	//	//	座標の初期化
	//	m_blackRightPos = STAGE_OUT_RIGHT_DOOR_POSITION;
	//	m_blackLeftPos = STAGE_OUT_LEFT_DOOR_POSITION;
	//}
}
