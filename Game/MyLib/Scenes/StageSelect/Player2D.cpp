
#include "pch.h"
#include "Player2D.h"

//	プレイヤー画像の真ん中の座標
const DirectX::SimpleMath::Vector2 Player2D::PLAYER_ORIGIN_TEXTURE = DirectX::SimpleMath::Vector2(110.0f, 172.5f);
//	プレイヤーのデフォルトの大きさ
const float						   Player2D::PLAYER_BASE_SCALE	   = 0.75f;
//	動く速さ
const float						   Player2D::MOVE_PLAYER_SPEED	   = 0.08f;



/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="texture">画像</param>
/// <param name="position">座標</param>
Player2D::Player2D(ID3D11ShaderResourceView* texture, const DirectX::SimpleMath::Vector2 position)
	:m_texture(texture),
	m_position(position),
	m_playerState(PLAYER_STATE::IDLE),
	m_playerAnimationTime(0.0f)
{
}

/// <summary>
/// デストラクタ
/// </summary>
Player2D::~Player2D()
{
}

/// <summary>
/// 初期化処理
/// </summary>
void Player2D::Initialize()
{
	m_scale = DirectX::SimpleMath::Vector2(0.75f);
}			

/// <summary>
/// 更新処理
/// </summary>
/// <param name="timer">タイマー</param>
void Player2D::Update(const DX::StepTimer& timer)
{
	UpdatePlayerState(timer);
}

/// <summary>
/// 描画処理
/// </summary>
void Player2D::Draw()
{
	//	スプライトバッチ
	DirectX::SpriteBatch* spriteBatch = MyLib::ScreenResources::GetInstance()->GetSpriteBatch();

	float angle = 0.0f;

	//	描画を行う
	spriteBatch->Draw
	(
		m_texture,
		m_position,
		nullptr,
		DirectX::Colors::White,
		angle,
		PLAYER_ORIGIN_TEXTURE,
		m_scale
	);
}

/// <summary>
/// プレイヤーのアニメーションを開始する
/// </summary>
void Player2D::BeginChangeSceneAnimation()
{
	m_playerState = PLAYER_STATE::FIRST;
}

void Player2D::UpdatePlayerState(const DX::StepTimer& timer)
{
	//	プレイヤーのステート
	switch (m_playerState)
	{
	case Player2D::PLAYER_STATE::IDLE:
	{
		//	少し早く
		float secnd = static_cast<float>(timer.GetTotalSeconds() * 3.0f);
		//	プレイヤーを上下に移動させる
		m_position.y += 2.0f * sinf(secnd * 2.5f);
		break;
	}
	//	最初のアニメーション
	case Player2D::PLAYER_STATE::FIRST:
	{
		//	後ろに下がらせる
		m_position.x -= sinf(1.0f);
		m_position.y -= sinf(2.0f);

		//	既定のところまで行ったら次の遷移へ
		if (m_position.x <= 260.0f)
		{
			m_playerState = PLAYER_STATE::SECOND;
		}

		break;
	}
	//	扉に向かってプレイヤーが突撃
	case Player2D::PLAYER_STATE::SECOND:
	{
		//	座標を少しづつずらす
		m_position = DirectX::SimpleMath::Vector2::Lerp(m_position, DirectX::SimpleMath::Vector2(700.0f, 300.0f), MOVE_PLAYER_SPEED);
		//	経過時間を時間を足す
		m_playerAnimationTime += static_cast<float>(timer.GetElapsedSeconds());

		//	プレイヤーの大きさをだんだんと小さく
		m_scale.x = Utility::Lerp(m_scale.x, 0.0f, MOVE_PLAYER_SPEED / 2.0f);
		m_scale.y = Utility::Lerp(m_scale.y, 0.0f, MOVE_PLAYER_SPEED / 2.0f);

		break;
	}
	case Player2D::PLAYER_STATE::OverID:	break;
	default:								break;
	}
}


