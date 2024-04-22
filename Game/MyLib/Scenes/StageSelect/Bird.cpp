//
//		File Name ： Bird.cpp
//		Production： 2023/11/25
//		Author　　： 石田 恭一	
//
#include "pch.h"
#include "Bird.h"

#include "StageSelectScene.h"

//	画像の真ん中
const DirectX::SimpleMath::Vector2 Bird::ORIGIN_BIRD_TEXTURE = DirectX::SimpleMath::Vector2(170.5f, 45.5f);
//	目標座標
const DirectX::SimpleMath::Vector2 Bird::TARGET_POSITION	 = DirectX::SimpleMath::Vector2(2500.0f, 560.0f);
//	始まる座標
const DirectX::SimpleMath::Vector2 Bird::START_POSITION		 = DirectX::SimpleMath::Vector2(-500.0f, 0.0f);
//	座標の許容範囲
const DirectX::SimpleMath::Vector2 Bird::BIRD_POSITION_RANGE = DirectX::SimpleMath::Vector2(10.0f, 3.0f);
//	鳥の右側
const RECT						   Bird::BIRD_TEXTURE_RIGHT = { 170, 0, 341, 91 };
//	鳥の左側
const RECT						   Bird::BIRD_TEXTURE_LEFT  = { 0,   0, 170, 91 };
//	ランダムな大きさMIN
const float						   Bird::RANDOM_SCALE_MIN = 0.3f;
//	ランダムな大きさMAX
const float						   Bird::RANDOM_SCALE_MAX = 0.8f;
/// <summary>
/// コンストラクタ
/// </summary>
Bird::Bird()
	:m_birdTexture(nullptr),
	m_angle(0.0f),
	m_alfa(1.0f),
	m_startTime(0.0f),
	m_isDirection{},
	m_birdRange{},
	m_isMoveFinished(false),
	m_isOutsideState(false)
{
}

/// <summary>
/// デストラクタ
/// </summary>
Bird::~Bird()
{
}

/// <summary>
/// 初期化処理
/// </summary>
void Bird::Initialize()
{
	CreateDeviceDependentResources();
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="timer">タイマー</param>
/// <param name="stageNum">ステージ番号/param>
void Bird::Update(const DX::StepTimer& timer, const int& stageNum)
{
	m_stage = stageNum;

	//	ステージ型にキャスト
	StageSelectScene::CHOOSE_STAGE stageSelect = static_cast<StageSelectScene::CHOOSE_STAGE>(m_stage);
	//	ステージは　3　||　4　か?
	if (stageSelect == StageSelectScene::CHOOSE_STAGE::STAGE_4 || stageSelect == StageSelectScene::CHOOSE_STAGE::STAGE_3)
	{
		//	活動範囲外へいった
		m_isOutsideState = true;
		//	アルファ値もさげる
		m_alfa = Utility::Lerp(m_alfa, 0.0f, 0.1f);
		//	ステージ3以降は帰れ  
		return;
	}
	else
	{
		//	範囲外から戻った時の準備
		if (m_isOutsideState)	GettingStartedBird();
		//	それ以外は1に戻す
		m_alfa = Utility::Lerp(m_alfa, 1.0f, 0.1f);
	}

	//	座標に移動する
	m_position = DirectX::SimpleMath::Vector2::Lerp(m_position, m_targetPosition, 0.003f);

	// 目標座標に到達したか確認する
	CheckArriveTargetPosition();
	//  鳥が飛ぶのを始める
	BeginFlyBird(timer);
}

/// <summary>
/// 描画する
/// </summary>
void Bird::Draw()
{
	//	スプライトバッチ
	DirectX::SpriteBatch* spriteBatch = MyLib::ScreenResources::GetInstance()->GetSpriteBatch();
	//	描画を行う
	spriteBatch->Draw
	(
		m_birdTexture,
		m_position,
		&m_birdRange,
		DirectX::SimpleMath::Color(m_alfa, m_alfa, m_alfa, m_alfa),
		DirectX::XMConvertToRadians(00.0f),
		ORIGIN_BIRD_TEXTURE,
		m_scale
	);
}

/// <summary>
/// デバイス依存のリソースの初期化
/// </summary>
void Bird::CreateDeviceDependentResources()
{
	//	画像
	m_birdTexture = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"Bird");

	// 向きをランダムに決める
	RandomDiretion();

	//	大きさをランダムで決める
	float random = Utility::CreateRandom(RANDOM_SCALE_MIN, RANDOM_SCALE_MAX);
	m_scale = DirectX::SimpleMath::Vector2(random, random);
}

/// <summary>
/// 飛ぶ準備を始める
/// </summary>
void Bird::GettingStartedBird()
{
	//	範囲内に戻った
	m_isOutsideState = false;
	//	向きをリセットする
	m_isDirection.ResetDirection();
	//	大きさをランダムで決める
	float random = Utility::CreateRandom(RANDOM_SCALE_MIN, RANDOM_SCALE_MAX);
	m_scale = DirectX::SimpleMath::Vector2(random, random);
	// 向きをランダムに決める
	RandomDiretion();
}

/// <summary>
/// 向きをランダムに決める
/// </summary>
void Bird::RandomDiretion()
{
	//	ランダムでどちらから始めるか決める
	if (rand() % 2 == 0)
	{
		m_targetPosition = START_POSITION;
		m_position = TARGET_POSITION;
		m_birdRange = BIRD_TEXTURE_LEFT;
		m_isDirection.isLeft = true;
	}
	else
	{
		m_position = START_POSITION;
		m_targetPosition = TARGET_POSITION;
		m_birdRange = BIRD_TEXTURE_RIGHT;
		m_isDirection.isRight = true;
	}
}

/// <summary>
/// 目標座標に到達したか確認する
/// </summary>
void Bird::CheckArriveTargetPosition()
{
	//	処理を実行中なので帰れ
	if (m_isMoveFinished)	return;

	int w,h;

	MyLib::ScreenResources::GetInstance()->GetScreenSize(w, h);

	//	向きはどちら
	if (m_isDirection.isRight)
	{
		if (m_position.x >= w)
		{
			m_isMoveFinished = true;
			//	次行ける時間はランダムで決める
			m_startTime = Utility::CreateRandom(1.0f, 3.0f);
		}
	}
	else
	{
		if (m_position.x <= BIRD_POSITION_RANGE.x)
		{
			m_isMoveFinished = true;
			//	次行ける時間はランダムで決める
			m_startTime = Utility::CreateRandom(1.0f, 3.0f);
		}
	}
}

/// <summary>
///  鳥が飛ぶのを始める
/// </summary>
/// <param name="timer">タイマー</param>
void Bird::BeginFlyBird(const DX::StepTimer& timer)
{
	//	移動が終了していないなら帰れ
	if (!m_isMoveFinished)	return;

	//	経過時間を引いていく
	m_startTime -= static_cast<float>(timer.GetElapsedSeconds());

	//	0より上なら帰れ
	if (m_startTime > 0)	return;

	//	逆向きにする
	m_isDirection.ReverseDirection();

	//	前とは逆の向きにする
	if (m_isDirection.isRight)
	{
		m_position = START_POSITION;
		m_targetPosition = TARGET_POSITION;
		m_birdRange = BIRD_TEXTURE_RIGHT;
	}
	else
	{
		m_targetPosition = START_POSITION;
		m_position = TARGET_POSITION;
		m_birdRange = BIRD_TEXTURE_LEFT;
	}

	m_isMoveFinished = false;

	//	大きさをランダムで決める
	float random = Utility::CreateRandom(RANDOM_SCALE_MIN, RANDOM_SCALE_MAX);
	m_scale = DirectX::SimpleMath::Vector2(random, random);
}