
#include"pch.h"
#include"BatMeter.h"

//	�o�b�g���[�^�[�̐^��
const DirectX::SimpleMath::Vector2 BatMeter::ORIGIN_BAT_METER		 = DirectX::SimpleMath::Vector2(50.5f, 75.1f);
//	�o�b�g���[�^�[�̑��̐^��
const DirectX::SimpleMath::Vector2 BatMeter::ORIGIN_BAT_SIDE_METER   = DirectX::SimpleMath::Vector2(69.0f, 104.0f);
//	�o�b�g���[�^�[�̐^�񒆍��W
const DirectX::SimpleMath::Vector2 BatMeter::BAT_METER_POSITION		 = DirectX::SimpleMath::Vector2(1186.0f, 575.0f);
//	�o�b�g���[�^�[�̑��̐^�񒆍��W
const DirectX::SimpleMath::Vector2 BatMeter::BAT_SIDE_METER_POSITION = DirectX::SimpleMath::Vector2(1200.0f, 600.0f);

/// <summary>
/// �R���X�g���N�^
/// </summary>
BatMeter::BatMeter()
{
}

BatMeter::~BatMeter()
{
}

/// <summary>
/// ����������
/// </summary>
void BatMeter::Initialize()
{
	//	���\�[�X�f�[�^
	m_resources			= MyLib::ResourcesData::GetInstance();
	//	�X�N���[�����\�[�X
	m_screen			= MyLib::ScreenResources::GetInstance();
	//	�o�b�g���[�^�[
	m_batMeter		    = m_resources->GatShaderResourceView(L"BatMeter");
	//	�o�b�g�̑����[�^�[
	m_batSideMeter	    = m_resources->GatShaderResourceView(L"BatSide");
	//	�o�b�g���[�^�[�̐^�񒆍��W
	m_batMeterPosition  = BAT_METER_POSITION;
	//	�o�b�g���[�^�[�̑��̐^�񒆍��W
	m_batMeterSidePosition  = BAT_SIDE_METER_POSITION;
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void BatMeter::Update(const DX::StepTimer& timer)
{

}

void BatMeter::Draw()
{
	//	�o�b�g���[�^�[�̕`��
	m_screen->GetSpriteBatch()->Draw
	(
		m_batSideMeter,
		m_batMeterSidePosition,
		nullptr,
		DirectX::Colors::White,
		0.0f,
		ORIGIN_BAT_SIDE_METER
	);

	// �o�b�g���[�^�[�̑��̕`��
	m_screen->GetSpriteBatch()->Draw
	(
		m_batMeter,
		m_batMeterPosition,
		nullptr,
		DirectX::Colors::White,
		0.0f,
		ORIGIN_BAT_METER
	);
}

/// <summary>
/// �f�o�C�X�ˑ��̃��\�[�X�̏�����
/// </summary>
void BatMeter::CreateDeviceDependentResources()
{
}

/// <summary>
/// �\�[�h�̐ݒ�
/// </summary>
/// <param name="sord">�\�[�h</param>
void BatMeter::SetSord(Sord* sord)
{
	m_sord = sord;
}