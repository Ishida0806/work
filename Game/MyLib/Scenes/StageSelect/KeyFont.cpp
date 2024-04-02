//
//		File Name �F KeyFont.cpp
//		Production�F 2023/11/01
//		Author�@�@�F �Γc ����	
// 
//		�L�[�̕`��E�X�V���s��
// 
#include "pch.h"
#include "KeyFont.h"

//	�摜�̐^�񒆂̈ʒu�̏���������
const DirectX::SimpleMath::Vector2 KeyFont::ORIGIN_KEY_TEXTURE = DirectX::SimpleMath::Vector2(250.0f, 300.0f);
//	�L�[�̑傫��
const DirectX::SimpleMath::Vector2 KeyFont::SCALE_KEY_TEXTURE = DirectX::SimpleMath::Vector2(0.3f, 0.3f);
//	��������
const float						   KeyFont::MOVE_KEY_SPEED = 0.5f;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="type">�^�C�v</param>
/// <param name="position">���W</param>
KeyFont::KeyFont(const FONT_TYPE type,DirectX::SimpleMath::Vector2 position)
	:m_fontType(type),
	m_keyPosition(position),
	m_keyFontTexture(nullptr),
	m_elapsedTime(0.0f)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
KeyFont::~KeyFont()
{
}

/// <summary>
/// ����������
/// </summary>
void KeyFont::Initialize()
{
	//	�t�H���g�̃^�C�v��ς���
	switch (m_fontType)
	{
	case KeyFont::FONT_TYPE::LEFT:	m_keyFontTexture = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"Key_Holding_A");	break;
	case KeyFont::FONT_TYPE::RIGHT:	m_keyFontTexture = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"Key_Holding_D");	break;
	default:																															break;
	}
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void KeyFont::Update(const DX::StepTimer& timer)
{
	//	��������
	m_elapsedTime = static_cast<float>(timer.GetElapsedSeconds() * 3.0f);

	//	���W�L�[���ړ�����
	//	
	switch (m_fontType)
	{
	case KeyFont::FONT_TYPE::LEFT:	 m_keyPosition.x -= MOVE_KEY_SPEED * sinf(m_elapsedTime);		break;
	case KeyFont::FONT_TYPE::RIGHT:	 m_keyPosition.x += MOVE_KEY_SPEED * sinf(m_elapsedTime);		break;
	default:																						break;
	}
}

/// <summary>
/// �`�揈��
/// </summary>
void KeyFont::Draw()
{
	//	�X�v���C�g�o�b�`
	DirectX::SpriteBatch* spriteBatch = MyLib::ScreenResources::GetInstance()->GetSpriteBatch();

	float angle = 0.0f;

	//	�`����s��
	spriteBatch->Draw
	(
		m_keyFontTexture,
		m_keyPosition,
		nullptr,
		DirectX::Colors::White,
		angle,
		ORIGIN_KEY_TEXTURE,
		SCALE_KEY_TEXTURE
	);	
}
