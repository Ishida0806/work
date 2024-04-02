//
//		File Name �F StartSignal.cpp
//		Production�F 2023/10/17
//		Author�@�@�F �Γc ����	
// 
//		�X�^�[�g�̍��}
//	
#include "pch.h"
#include "StartSignal.h"

//	GO�摜�̐^�񒆂̍��W
const DirectX::SimpleMath::Vector2 StartSignal::ORIGIN_GO_POSITION	  = DirectX::SimpleMath::Vector2(62.5f, 37.5f);
//	READY�摜�̐^�񒆂̍��W
const DirectX::SimpleMath::Vector2 StartSignal::ORIGIN_READY_POSITION = DirectX::SimpleMath::Vector2(137.5f, 46.0f);
//	�摜�̃f�t�H���g�̑傫��
const DirectX::SimpleMath::Vector2 StartSignal::BASE_SCALE			  = DirectX::SimpleMath::Vector2(2.0f, 2.0f);
//	GO���o���Ƃ��ɏ����h���
const float						   StartSignal::SHAKE_GO_POSITION	  = 1.0f;

/// <summary>
/// �R���X�g���N�^
/// </summary>
StartSignal::StartSignal()
	:m_readyUi(nullptr),
	m_goUi(nullptr),
	m_renderState(STATE::IDLE)
{
	
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
StartSignal::~StartSignal()
{
}

/// <summary>
/// ����������
/// </summary>
void StartSignal::Initialize()
{
	// �f�o�C�X�ˑ��̃��\�[�X�̏�����
	CreateDeviceDependentResources();
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void StartSignal::Update(const DX::StepTimer& timer)
{
	timer;

	switch (m_renderState)
	{
	case StartSignal::STATE::IDLE:
	{
		if (m_maxFadeCount - 1.6f <= *m_pNextCount)
		{
			//	�w�肳�ꂽSE�𗬂�
			AudioManager::GetInstance()->PlaySoundEffectSE(L"PlayStartSE01");
			m_renderState = STATE::READY;			
		}
		break;
	}
	case StartSignal::STATE::READY:
	{
		if (m_maxFadeCount - 0.4f <= *m_pNextCount)
		{
			//	�w�肳�ꂽSE�𗬂�
			AudioManager::GetInstance()->PlaySoundEffectSE(L"PlayStartSE02");
			m_renderState = STATE::GO;
		}
		break;
	}
	case StartSignal::STATE::GO:
	{
		//m_goPosition.x += Utility::CreateRandom(-5.0f, 5.0f);
		//m_goPosition.y += Utility::CreateRandom(-SHAKE_GO_POSITION, SHAKE_GO_POSITION);

		if (m_maxFadeCount <= *m_pNextCount)
		{
			m_renderState = STATE::FINISH;
		}
		break;
	}
	case StartSignal::STATE::FINISH:	return;		break;
	
	default:	break;
	}
}

/// <summary>
/// �`�悷��
/// </summary>
void StartSignal::Draw()
{
	using namespace DirectX::SimpleMath;

	//	�X�v���C�g�o�b�`���擾����
	DirectX::SpriteBatch* spriteBatch = MyLib::ScreenResources::GetInstance()->GetSpriteBatch();

	//	READY�̎��̂ݕ`�悷��
	if (m_renderState == STATE::READY)
	{
		spriteBatch->Draw
		(
			m_readyUi,
			m_readyPosition,
			nullptr,
			DirectX::Colors::White,
			0.0f,
			ORIGIN_READY_POSITION,
			BASE_SCALE
		);
	}
	//	GO�̎��̂ݕ`�悷��
	else if (m_renderState == STATE::GO)
	{
		spriteBatch->Draw
		(
			m_goUi,
			m_goPosition,
			nullptr,
			DirectX::Colors::White,
			0.0f,
			ORIGIN_GO_POSITION,
			BASE_SCALE
		);
	}
}

/// <summary>
/// �f�o�C�X�ˑ��̃��\�[�X�̏�����
/// </summary>
void StartSignal::CreateDeviceDependentResources()
{
	using namespace DirectX::SimpleMath;

	//	Ready��UI�摜
	m_readyUi = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"Ready_UI");
	//	GO��UI�摜
	m_goUi	  = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"Go_UI");
	//	READY���W
	m_readyPosition = Vector2(640.0f, 360.0f);
	m_goPosition	= Vector2(640.0f, 360.0f);
}

/// <summary>
/// �t�F�[�h�ɕK�v�Ȏ��Ԃ�ݒ肷��
/// </summary>
/// <param name="pFadeTimer">�t�F�[�h�^�C���̃|�C���^�[</param>
/// <param name="fadeMaxTime">�}�b�N�X����</param>
void StartSignal::SetFadeTime(float* pFadeTimer, float fadeMaxTime)
{
	m_pNextCount = pFadeTimer;
	m_maxFadeCount = fadeMaxTime;
}