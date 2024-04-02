
#include "pch.h"
#include "Door2D.h"

//	画像の真ん中の位置の初期化する
const DirectX::SimpleMath::Vector2 Door2D::ORIGIN_TEXTURE = DirectX::SimpleMath::Vector2(259.0f, 259.0f);
const float						   Door2D::MOVE_SPEED	  = 0.08f;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="doorTexture">ドアの画像</param>
/// <param name="fontTexture">フォントの画像</param>
/// <param name="position">座標</param>
Door2D::Door2D(ID3D11ShaderResourceView* doorTexture, ID3D11ShaderResourceView* fontTexture, const DirectX::SimpleMath::Vector2& position, const float& distance)
	:m_doorTexture(doorTexture),
	m_fontTexture(fontTexture),
	m_doorPos(position),
	m_distance(distance),
	m_moveState(MOVE_DIRECTION::CENTER)
{
	m_fontPos = m_doorPos + DirectX::SimpleMath::Vector2(-0.0f, -250.0f);
}

/// <summary>
/// デストラクタ
/// </summary>
Door2D::~Door2D()
{
}

/// <summary>
/// 更新する
/// </summary>
void Door2D::Update(bool used)
{
	m_used = used;

	if(m_used)							


	if (m_moveState == MOVE_DIRECTION::CENTER)	return;

	m_doorPos.x = Utility::Lerp(m_doorPos.x, m_doorTargetPos.x, MOVE_SPEED);

	m_fontPos = m_doorPos + DirectX::SimpleMath::Vector2(0.0f, -250.0f);
}
	

/// <summary>
/// 描画する
/// </summary>
/// <param name="scale">大きさ</param>
void Door2D::Draw(const DirectX::SimpleMath::Vector2& scale)
{
	DirectX::SpriteBatch* spriteBatch = MyLib::ScreenResources::GetInstance()->GetSpriteBatch();

	spriteBatch->Draw
	(
		m_fontTexture,
		m_fontPos,
		nullptr,
		DirectX::Colors::White,
		0.0f,
		DirectX::SimpleMath::Vector2(277.5f, 62.0f)
	);

	spriteBatch->Draw
	(
		m_doorTexture,
		m_doorPos,
		nullptr,
		DirectX::Colors::White,
		0.0f,
		ORIGIN_TEXTURE,
		scale
	);
}

/// <summary>
/// 座標を決定する
/// </summary>
void Door2D::TargetPosDecision(int state)
{
	m_moveState = static_cast<MOVE_DIRECTION>(state);

	if (m_moveState == MOVE_DIRECTION::CENTER)	return;

	if (m_moveState == MOVE_DIRECTION::LEFT)
	{
		m_doorTargetPos.x = m_doorPos.x + m_distance;
	}
	else
	{
		m_doorTargetPos.x = m_doorPos.x - m_distance;
	}
}
