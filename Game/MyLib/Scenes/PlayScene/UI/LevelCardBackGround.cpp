
#include "pch.h"
#include "LevelCardBackGround.h"

//	�w�i�摜�̒��S�_
const DirectX::SimpleMath::Vector2 LevelCardBackGround::BACKGROUND_ORIGIN_POSITION	  = { 699.0f,370.0f };
//	�w�i�摜�̏�����Y���W
const float						   LevelCardBackGround::BACKGROUND_RESTART_POSITION_Y = -360.0f;
//	��ɏオ�鑬��
const float						   LevelCardBackGround::EXIT_SPEED_POSITION_Y		  = 15.0f;
//	����̑���
const float						   LevelCardBackGround::IN_SPEED					  = 0.2f;
//	�ޏ�̑���
const float						   LevelCardBackGround::EXIT_SPEED					  = 0.1f;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="player">�v���C���[</param>
LevelCardBackGround::LevelCardBackGround()
	:
	m_isClick(false),
	m_backGroundTexture(nullptr)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
LevelCardBackGround::~LevelCardBackGround()
{
}

/// <summary>
/// ����������
/// </summary>
void LevelCardBackGround::Initialize()
{
	//	�摜���擾
	m_backGroundTexture = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"leverUpCardBackGround");
	//	���A����
	int w, h;
	//	��ʂ̃T�C�Y���擾����
	MyLib::ScreenResources::GetInstance()->GetScreenSize(w, h);
	//	��ʂ̐^�񒆂ɏo��
	m_backGroundTargetPosition = DirectX::SimpleMath::Vector2(static_cast<float>(w / 2.0f), static_cast<float>(h / 2.0f));
	// ���W�̏�����
	ResetPosition();
	//	�ŏ��̓[��
	m_backGroundScale = DirectX::SimpleMath::Vector2::Zero;
}

/// <summary>
/// �X�V����
/// </summary>
void LevelCardBackGround::Update()
{
	//	�ǂ�ǂ�傫������
	m_backGroundScale = DirectX::SimpleMath::Vector2::Lerp(m_backGroundScale, DirectX::SimpleMath::Vector2::One, IN_SPEED);

	m_backGroundPosition = DirectX::SimpleMath::Vector2::Lerp(m_backGroundPosition, m_backGroundTargetPosition, IN_SPEED);
}


/// <summary>
/// �ޏo����
/// </summary>
void LevelCardBackGround::Exit()
{
	//	�ǂ�ǂ񏬂�������
	m_backGroundScale = DirectX::SimpleMath::Vector2::Lerp(m_backGroundScale, DirectX::SimpleMath::Vector2::Zero, EXIT_SPEED);

	m_backGroundPosition.y -= EXIT_SPEED_POSITION_Y;

	if (m_backGroundPosition.y <= BACKGROUND_RESTART_POSITION_Y)
	{
		// ���W�̏�����
		ResetPosition();
	}
}

/// <summary>
/// �`�悷��
/// </summary>
void LevelCardBackGround::Draw()
{
	DirectX::SpriteBatch* spriteBatch = MyLib::ScreenResources::GetInstance()->GetSpriteBatch();

	spriteBatch->Draw
	(
		m_backGroundTexture,
		m_backGroundPosition,
		nullptr,
		DirectX::Colors::White,
		0.0f,
		BACKGROUND_ORIGIN_POSITION,
		m_backGroundScale
	);
}

/// <summary>
/// ���W�̏�����
/// </summary>
void LevelCardBackGround::ResetPosition()
{
	//	X���W�͓���
	m_backGroundPosition.x = m_backGroundTargetPosition.x;
	//	Y���W�̏�����
	m_backGroundPosition.y = BACKGROUND_RESTART_POSITION_Y;
}
