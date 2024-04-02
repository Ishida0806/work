//
//		File Name �F TitleStringUI.cpp
//		Production�F 2023/11/11
//		Author�@�@�F �Γc ����
// 
//		�^�C�g���̈ē��̕`��E�X�V
//
#include "pch.h"
#include "TitleStringUI.h"

#include "TitleScene.h"


//	�h�炷�傫��
const float					      TitleStringUI::SHAKE_TEXTURE					= 0.1f;
//	�h�炷����
const float					      TitleStringUI::SHAKE_SPEED					= 2.5f;
//	�p�x��߂����x
const float						  TitleStringUI::MOVE_BACKANGLE_SPEED			= 0.1f;
//	�v���C�Q�[���̐^�񒆍��W
const DirectX::SimpleMath::Vector2 TitleStringUI::PLAYGAME_ORIGIN_POSITION		= DirectX::SimpleMath::Vector2(137.5f, 40.5f);
//	�R���t�B�O�̐^�񒆍��W
const DirectX::SimpleMath::Vector2 TitleStringUI::CONFIG_ORIGIN_POSITION		= DirectX::SimpleMath::Vector2(100.5f, 40.5f);
//	�G���h�Q�[���̐^�񒆍��W
const DirectX::SimpleMath::Vector2 TitleStringUI::ENDGAME_ORIGIN_POSITION		= DirectX::SimpleMath::Vector2(123.0f, 40.5f);

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="texture">�摜</param>
/// <param name="texture">OFF���̉摜</param>
/// <param name="position">���W</param>
/// <param name="index">�ԍ�</param>
TitleStringUI::TitleStringUI(
	ID3D11ShaderResourceView* texture, 
	ID3D11ShaderResourceView* offTexture, 
	const DirectX::SimpleMath::Vector2& position,
	const int& index
)
	:m_texture(texture),
	m_offTexture(offTexture),
	m_position(position),
	m_type(index),
	m_angle(0.0f),
	m_offsetX(0.0f),
	m_state(0)
{
	//	�^
	TitleScene::STATE type = static_cast<TitleScene::STATE>(index);

	//	��ނɂ���ĕς���
	switch (type)
	{
	case TitleScene::STATE::IDLE:													break;
	case TitleScene::STATE::PLAY:	m_originPosition = PLAYGAME_ORIGIN_POSITION;	break;
	case TitleScene::STATE::CONFIG:	m_originPosition = CONFIG_ORIGIN_POSITION;		break;
	case TitleScene::STATE::END:	m_originPosition = ENDGAME_ORIGIN_POSITION;		break;
	case TitleScene::STATE::NONE:													break;
	default:																		break;
	}

	//	�傫��������������
	m_scale = TitleUI::BASE_SCALE;
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
TitleStringUI::~TitleStringUI()
{
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="state">�Z���N�g���ꂽ�ԍ�</param>
void TitleStringUI::Update(const int& state)
{
	m_state = state;

	SelectUI();
}

/// <summary>
/// �`�揈��
/// </summary>
void TitleStringUI::Draw()
{	
	TitleScene::STATE state = static_cast<TitleScene::STATE>(m_state);

	//	�A�C�h�����O��ԂȂ�A��
	if (state == TitleScene::STATE::IDLE)	return;

	//	�^
	TitleScene::STATE Istate = static_cast<TitleScene::STATE>(m_type);

	if (state == Istate)
	{
		//	�`���C����
		TitleUI::Draw
		(
			m_texture,
			m_position,
			DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f),
			m_angle,
			m_originPosition,
			m_scale
		);
	}
	else
	{
		//	�`���C����
		TitleUI::Draw
		(
			m_offTexture,
			m_position,
			DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f),
			m_angle,
			m_originPosition,
			m_scale
		);
	}
}

/// <summary>
/// �Z���N�g���ꂽ���̍X�V����
/// </summary>
void TitleStringUI::SelectUI()
{
	//	���݂̌^
	TitleScene::STATE state = static_cast<TitleScene::STATE>(m_state);
	//	�^
	TitleScene::STATE Istate = static_cast<TitleScene::STATE>(m_type);

	//	�A�C�h�����O��ԂȂ�A��
	if (state == TitleScene::STATE::IDLE)	return;

	if (state == Istate)
	{
		//	�o�ߎ��Ԃ��擾����
		float elapsedTime = MyLib::ElapsedTime::GetInstance()->GetElapsedTime();

		//	�p�x���㉺�^��������
		m_angle = SHAKE_TEXTURE * sinf(elapsedTime * SHAKE_SPEED);
	}
	else
	{
		//	�������߂�
		m_angle = Utility::Lerp(m_angle, 0.0f, MOVE_BACKANGLE_SPEED);
	}
}
