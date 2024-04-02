//
//		File Name �F StageCircle.cpp
//		Production�F 2023/11/02
//		Author�@�@�F �Γc ����	
// 
#include "pch.h"
#include "StageCircle.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="texture">�摜</param>
/// <param name="position">���W</param>
StageCircle::StageCircle(ID3D11ShaderResourceView* texture, const DirectX::SimpleMath::Vector2& position, const int& ID)
	:m_texture(texture),
	m_position(position),
	m_ID(ID)
{
	m_color = DirectX::SimpleMath::Vector4::One;
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
StageCircle::~StageCircle()
{
}

/// <summary>
/// ����������
/// </summary>
void StageCircle::Initialize()
{

}

/// <summary>
/// �X�V����
/// </summary>
void StageCircle::Update(const DX::StepTimer& timer, const int& stageNum)
{
	timer;

	if (stageNum == m_ID)		m_color = DirectX::Colors::Black;
	else						m_color = DirectX::Colors::White;

}

/// <summary>
/// �`�悷��
/// </summary>
void StageCircle::Draw()
{
	//	�X�v���C�g�o�b�`
	DirectX::SpriteBatch* spriteBatch = MyLib::ScreenResources::GetInstance()->GetSpriteBatch();
	//	�`�悷��
	spriteBatch->Draw
	(
		m_texture,
		m_position,
		m_color
	);
}

/// <summary>
/// �I������
/// </summary>
void StageCircle::Finalize()
{
}
