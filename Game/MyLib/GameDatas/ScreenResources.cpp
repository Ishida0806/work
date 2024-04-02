//
//		File Name �F ScreenResources.cpp
//		Production�F 2023/6/01
//		Author�@�@�F �Γc ����	
// 
//		DirectXTK�ł悭�g���N���X�܂Ƃ߂��N���X
//
#include "pch.h"
#include "ScreenResources.h"

std::unique_ptr<MyLib::ScreenResources> MyLib::ScreenResources::m_screenResources = nullptr;

/// <summary>
/// ScreenResources���擾����
/// </summary>
/// <returns></returns>
MyLib::ScreenResources* const MyLib::ScreenResources::GetInstance()
{
	//	�k���|�Ȃ琶��
	if (m_screenResources == nullptr)
	{
		//	�X�N���[���N���X�̃C���X�^���X�𐶐�����
		m_screenResources.reset(new MyLib::ScreenResources());
	}
	//	�X�N���[�����\�[�X�N���X�̃C���X�^���X���擾����
	return m_screenResources.get();
}

/// <summary>
/// �R���X�g���N�^
/// </summary>
MyLib::ScreenResources::ScreenResources()
	:
	m_effectFactory(nullptr),					// �f�o�C�X���\�[�X
	m_screen_W(1280),								// �X�N���[����
	m_screen_H(720),								// �X�N���[����
	m_view{},									// �r���[�s��
	m_projection{},								// �ˉe�s��
	m_device(nullptr),							// �f�o�C�X
	m_context(nullptr)							// �f�o�C�X�R���e�L�X�g
{
}

/// <summary>
/// ����������
/// </summary>
void MyLib::ScreenResources::Initialize()
{
	// �f�o�C�X���\�[�X
	DX::DeviceResources* DR = DX::DeviceResources::GetInstance();

	//�@�f�o�C�X���擾����
	m_device = DR->GetD3DDevice();
	//�@�f�o�C�X�R���e�L�X�g���擾����
	m_context = DR->GetD3DDeviceContext();
	//�@�G�t�F�N�g���t�@�N�g�̍쐬
	m_effectFactory = std::make_unique<DirectX::EffectFactory>(m_device);
	//�@���ʃX�e�[�g�I�u�W�F�N�g�̍쐬
	m_states = std::make_unique<DirectX::CommonStates>(m_device);
	//	�X�v���C�g�o�b�`�̍쐬
	m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(m_context);
	//	�X�v���C�g�t�H���g�̍쐬
	m_spriteFont = std::make_unique<DirectX::SpriteFont>(m_device, L"Resources/Font/SegoeUI_18.spritefont");

	//	�o�b�`�G�t�F�N�g�̍쐬
	m_batchEffect = std::make_unique<DirectX::BasicEffect>(m_device);
	m_batchEffect->SetTextureEnabled(true);
	m_batchEffect->SetVertexColorEnabled(true);

	void const* shaderByteCode;
	size_t byteCodeLength;
	m_batchEffect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);

	// �C���v�b�g���C�A�E�g���쐬
	m_device->CreateInputLayout(
		DirectX::VertexPositionColorTexture::InputElements,
			DirectX::VertexPositionColorTexture::InputElementCount,
			shaderByteCode,
			byteCodeLength,
			m_inputLayout.GetAddressOf()
	);
}

/// <summary>
/// �f�o�b�N�t�H���g
/// </summary>
void MyLib::ScreenResources::RenderDebugFont(const wchar_t* character, const DirectX::SimpleMath::Vector2 position)
{
	// �X�v���C�g�o�b�`���J�n
	m_spriteBatch->Begin();
	// �f�o�b�O�e�L�X�g��`��
	m_spriteFont->DrawString(m_spriteBatch.get(), character, position, DirectX::Colors::White);
	// �X�v���C�g�o�b�`���I��
	m_spriteBatch->End();
}

/// <summary>
/// �X�N���[���T�C�Y���擾����
/// </summary>
/// <param name="width">��ʂ̉�</param>
/// <param name="height">��ʂ̍���</param>
void MyLib::ScreenResources::GetScreenSize(int& screenWeight, int& screenHeight)
{
	screenWeight = m_screen_W;
	screenHeight = m_screen_H;
}

/// <summary>
/// �X�N���[���T�C�Y��ݒ肷��
/// </summary>
/// <param name="width">��ʂ̉�</param>
/// <param name="height">��ʂ̍���</param>
void MyLib::ScreenResources::SetScreenSize(const int& width, const int& height)
{
	m_screen_W = width;
	m_screen_H = height;
}

/// <summary>
/// �r���[�}�g���b�N�X��ݒ肷��
/// </summary>
/// <param name="view">�r���[�}�g���b�N�X</param>
void MyLib::ScreenResources::SetViewMatrix(const DirectX::SimpleMath::Matrix& view)
{
	m_view = view; 
}


/// <summary>
/// �v���W�F�N�V�����}�g���b�N�X��ݒ肷��
/// </summary>
/// <param name="projection">�v���W�F�N�V����</param>
void MyLib::ScreenResources::SetProjectionMatrix(const DirectX::SimpleMath::Matrix& projection)
{
	m_projection = projection; 
}
