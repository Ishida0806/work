//
//		File Name ： ResultBackGround.cpp
//		Production： 2023/11/12
//		Author　　： 石田 恭一	
// 
//		背景画像の描画処理
//
#include "pch.h"
#include "ResultBackGround.h"
#include <math.h>

//	背景画像の座標
const DirectX::SimpleMath::Vector2 ResultBackGround::BACKGROUND_POSITION		= DirectX::SimpleMath::Vector2(670.0f, 450.0f); 
//	背景画像の真ん中の座標
const DirectX::SimpleMath::Vector2 ResultBackGround::BACKGROUND_ORIGIN_POSITION = DirectX::SimpleMath::Vector2(384.5f, 465.0f);
//	大きくなる速度
const float						   ResultBackGround::SCLAE_UP_SPEED				= 0.002f;
//	規定値を超えた後の大きくなる速度
const float						   ResultBackGround::SCLAE_AFTER_SPEED			= 0.05f;
//	目標の大きさ
const float						   ResultBackGround::TARGET_SCALE				= 0.125f;
//	回る速度
const float						   ResultBackGround::TURN_SPEED					= 10.0f;
//	座標の移動速度
const float						   ResultBackGround::POSITION_SPEED				= 0.03f;
//	大きさの誤差範囲
const float						   ResultBackGround::ERROR_RANGE_SCALE			= 0.005f;
//	目標の角度
const float						   ResultBackGround::TARGET_ANGLE				= 10.0f;
//	目標の最終大きさ
const float						   ResultBackGround::TARGET_FINAL_SCALE			= 0.95f;


/// <summary>
/// 更新処理
/// </summary>
ResultBackGround::ResultBackGround()
	:m_texture(nullptr),
	m_angle(0.0f),
	m_targetAngle(0.0f)
{
}

/// <summary>
/// デストラクタ
/// </summary>
ResultBackGround::~ResultBackGround()
{
}

/// <summary>
/// 初期化処理
/// </summary>
void ResultBackGround::Initialize()
{
	m_texture = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"Result_ScoreBackGround");

	m_position = { 1050.0f,0.0f };
}

/// <summary>
/// 更新処理
/// </summary>
/// <returns>使用</returns>
bool ResultBackGround::Update()
{
	using namespace DirectX::SimpleMath;


	//	大きさが一定の値を超えるまで遅くし、そのあとは早く
	if (m_sacle.x <= TARGET_SCALE && m_sacle.y <= TARGET_SCALE)
	{
		//	徐々に拡大
		m_sacle = Vector2::Lerp(m_sacle, Vector2::One, SCLAE_UP_SPEED);
		//	徐々に回す
		m_angle += DirectX::XMConvertToRadians(TURN_SPEED);
		//	座標を徐々に移動
		m_position = Vector2::Lerp(m_position, BACKGROUND_POSITION, 0.01f);
	}
	else
	{	
		if (m_sacle.x >= TARGET_FINAL_SCALE && m_sacle.y >= TARGET_FINAL_SCALE)
		{
			m_angle = Utility::Lerp(m_angle , m_targetAngle, 0.05f);

			if (m_angle >= m_targetAngle - ERROR_RANGE_SCALE)
			{
				return true;
			}
		}
		else
		{
			//	徐々に戻す
			m_angle += DirectX::XMConvertToRadians(TURN_SPEED);
			// 補完後の角度を更新
			m_targetAngle = ConvartTargetAngle(DirectX::XMConvertToRadians(TARGET_ANGLE)) + m_angle;
			//	座標を徐々に移動
			m_position = Vector2::Lerp(m_position, BACKGROUND_POSITION, POSITION_SPEED);
			//	徐々に拡大
			m_sacle = Vector2::Lerp(m_sacle, Vector2::One, SCLAE_AFTER_SPEED);
		}
	}	
	
	return false;
}

/// <summary>
/// 描画処理
/// </summary>
void ResultBackGround::Draw()
{
	//	スプライトバッチ
	DirectX::SpriteBatch* spriteBath = MyLib::ScreenResources::GetInstance()->GetSpriteBatch();

	//	背景画像の描画
	spriteBath->Draw
	(
		m_texture,
		m_position,
		nullptr,
		DirectX::Colors::White,
		m_angle,
		BACKGROUND_ORIGIN_POSITION,
		m_sacle
	);
}

/// <summary>
/// 目標角度までの距離を算出する
/// </summary>
/// <param name="targetAngle">目標角度</param>
/// <returns>目標角度</returns>
float ResultBackGround::ConvartTargetAngle(const float& targetAngle)
{
	//	一周分のデータにする
	float rad = fmod(m_angle, DirectX::XMConvertToRadians(360.0f));
	//	一周分のデータのどのくらいの角度にいるか計算
	float ans = DirectX::XMConvertToRadians(360.0f) - rad;
	//	目標値と計算
	return targetAngle + ans;
}
