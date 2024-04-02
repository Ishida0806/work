//
//		File Name �F StageBackGround.cpp
//		Production�F 2023/11/01
//		Author�@�@�F �Γc ����	
// 
//		�w�i�摜�̍X�V�`����s��
// 
#include "pch.h"
#include "StageBackGround.h"

#include "Common/ReadData.h"
#include "StageSelectScene.h"

//	�閾���O�̐F
const DirectX::SimpleMath::Vector4 StageBackGround::DAWN_COLOR		= { -0.0f, -0.0f, -0.3f, -0.3f };
//	���̐F
const DirectX::SimpleMath::Vector4 StageBackGround::MORNING_COLOR	= { 0.50f, 0.50f, 0.50f,  0.50f };
//	������̐F
const DirectX::SimpleMath::Vector4 StageBackGround::DAYTIME_COLOR	= { 0.8f,   0.0f,  0.05f,  1.0f };
//	��̐F
const DirectX::SimpleMath::Vector4 StageBackGround::NIGHT_COLOR		= { -1.0f, -1.0f, -0.25f, 1.0f };

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="backGroundTexture">�摜</param>
StageBackGround::StageBackGround(ID3D11ShaderResourceView* backGroundTexture, const int& maxStage)
	:m_backGroundTexture(backGroundTexture),
	m_maxStageNum(maxStage),
	m_stageBackGroundConstBuffer{}
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
StageBackGround::~StageBackGround()
{
}

/// <summary>
/// ����������
/// </summary>
void StageBackGround::Initialize()
{
	//	�R���e�L�X�g
	auto context = MyLib::ScreenResources::GetInstance()->GetDevice();
	//	�f�o�C�X
	auto device = MyLib::ScreenResources::GetInstance()->GetDevice();
	// �s�N�Z���V�F�[�_�[�̍쐬
	std::vector<uint8_t> psData = DX::ReadData(L"Resources/CSO/StageBackGroundPS.cso");
	//	�s�N�Z���V�F�[�_���쐬
	DX::ThrowIfFailed
	(
		//	
		context->CreatePixelShader
		(
			psData.data(),
			psData.size(),
			nullptr, 
			m_PS_Stage.ReleaseAndGetAddressOf()
		)
	);

	//	����������
	m_stageBackGroundConstBuffer.Diffuse = DirectX::SimpleMath::Vector4(0.0f,0.0f,0.0f,0.0f);
	//�V�F�[�_�[�Ƀf�[�^��n�����߂̃R���X�^���g�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	//	�������̃u���b�N���[���Ŗ��߂�
	ZeroMemory(&bd, sizeof(bd));
	//	�o�b�t�@�[�̓ǂݎ��Ə������ݕ��@�����
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ConstBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	device->CreateBuffer(&bd, nullptr, &m_cBuffer);
}

/// <summary>
/// �X�V����
/// </summary>
void StageBackGround::Update(const int& selectStage)
{	
	//	�Z���N�g���ꂽ���
	StageSelectScene::CHOOSE_STAGE  stageState = static_cast<StageSelectScene::CHOOSE_STAGE>(selectStage);

	//	�X�e�[�W��Ԃɂ���ĐF��ς���
	switch (stageState)
	{
	case StageSelectScene::CHOOSE_STAGE::STAGE_1:	m_targetColor = DAWN_COLOR;		break;
	case StageSelectScene::CHOOSE_STAGE::STAGE_2:	m_targetColor = MORNING_COLOR;  break;
	case StageSelectScene::CHOOSE_STAGE::STAGE_3:	m_targetColor = DAYTIME_COLOR;	break;
	case StageSelectScene::CHOOSE_STAGE::STAGE_4:	m_targetColor = NIGHT_COLOR;	break;
	case StageSelectScene::CHOOSE_STAGE::OverID:									break;
	default:																		break;
	}

	//	�f�B�t���[�Y�ɐF�𔽉f������
	m_stageBackGroundConstBuffer.Diffuse = 
		DirectX::SimpleMath::Vector4::Lerp
		(
			m_stageBackGroundConstBuffer.Diffuse, 
			m_targetColor, 
			0.05f
		);
}


/// <summary>
/// �`�悷��
/// </summary>
void StageBackGround::Draw()
{
	//	�X�v���C�g�o�b�`
	DirectX::SpriteBatch* spriteBatch = MyLib::ScreenResources::GetInstance()->GetSpriteBatch();
	//	�R���e�L�X�g
	auto context = MyLib::ScreenResources::GetInstance()->GetDeviceContext();
	//	�J�n����O�ɃV�F�[�_���Z�b�g����
	spriteBatch->Begin
	(
		DirectX::SpriteSortMode_Immediate,
		nullptr,
		nullptr,
		nullptr,
		nullptr,
		[&]()
		{
			//	�R���X�g�o�b�t�@���X�V����
			context->UpdateSubresource(m_cBuffer.Get(), 0, NULL, &m_stageBackGroundConstBuffer, 0, 0);
			// �s�N�Z���V�F�[�_�g�p����萔�o�b�t�@��ݒ�
			ID3D11Buffer* cbuf_ps[] = { m_cBuffer.Get() };
			// �X���b�g0��DirectXTK���g�p���Ă���̂ŃX���b�g�P���g�p����
			context->PSSetConstantBuffers(1, 1, cbuf_ps);	
			//	�摜��ݒ肷��
			context->PSSetShaderResources(1, 1, &m_backGroundTexture);
			//	�s�N�Z���V�F�[�_��ݒ肷��
			context->PSSetShader(m_PS_Stage.Get(), nullptr, 0);
		}
	);

	//	�`����s��
	spriteBatch->Draw
	(
		m_backGroundTexture,
		DirectX::SimpleMath::Vector2::Zero
	);

	//	�`����I������
	spriteBatch->End();
}

/// <summary>
/// �I������
/// </summary>
void StageBackGround::Finalize()
{
	
}
