
#include "pch.h"
#include "Fade.h"

//	���[�v�^�C��
const float Fade::LERP_TIME = 0.07f;
//	�I���^�C��
const float Fade::FIN_TIME  = 0.03f;

/// <summary>
/// �R���X�g���N�^
/// </summary>
Fade::Fade()
	:m_second(0.0f),
	//m_alfa(0.0f),
	m_startFlag(false),
	m_finFlag(false)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Fade::~Fade()
{
}

/// <summary>
/// ����������
/// </summary>
void Fade::Initialize()
{
	//	�X�N���[�����\�[�X���擾����
	m_screen = MyLib::ScreenResources::GetInstance();
	//	���\�[�V�[�Y�f�[�^���擾����
	m_resources = MyLib::ResourcesData::GetInstance();
	//	�摜�̃e�N�X�`�����擾����

	//	�ϐ���������
	/*m_second	= 0.0f;
	m_alfa		= 0.0f;
	m_startFlag = false;
	m_finFlag	= false;*/
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="timer"></param>
void Fade::Update(const DX::StepTimer& timer)
{

}

/// <summary>
/// �`�揈��
/// </summary>
void Fade::Render()
{

}

/// <summary>
/// ����������
/// </summary>
void Fade::Finalize()
{
}

/// <summary>
/// �t�F�C�h�C�����s��
/// </summary>
void Fade::StartFade()
{
	m_startFlag = true;
}