
#include "pch.h"
#include "OutPutResultUI.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="texture">�摜</param>
/// <param name="position">���W</param>
/// <param name="originPosition">�摜�̐^�񒆍��W</param>
OutPutResultUI::OutPutResultUI(
	ID3D11ShaderResourceView* texture, 
	const DirectX::SimpleMath::Vector2& position,
	const DirectX::SimpleMath::Vector2& originPosition
)
	:m_texture(texture),
	m_position(position),
	m_originPosition(originPosition),
	m_angle(0.0f),
	m_alfa(1.0f)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
OutPutResultUI::~OutPutResultUI()
{
}

/// <summary>
/// �X�V����
/// </summary>
void OutPutResultUI::Update()
{
	m_alfa = sinf(MyLib::ElapsedTime::GetInstance()->GetElapsedTime() * 2.5f);
}

/// <summary>
/// �`�揈��
/// </summary>
void OutPutResultUI::Draw()
{
	//	�ē��L�[�̕`��
	MyLib::ScreenResources::GetInstance()->GetSpriteBatch()->Draw
	(
		m_texture,
		m_position,
		nullptr,
		DirectX::SimpleMath::Color(m_alfa, m_alfa, m_alfa, m_alfa),
		0.0f,
		m_originPosition
	);
}