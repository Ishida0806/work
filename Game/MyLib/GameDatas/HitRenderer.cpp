//
//		File Name �F HitRenderer.cpp
//		Production�F 2023/8/02
//		Author�@�@�F �Γc ����
// 
//		���������ۂ̃G�t�F�N�g�̕`����s���N���X
//
#include "pch.h"
#include "HitRenderer.h"

const float HitRenderer::RENDER_TIME = 22.0f;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="texture">�摜</param>
/// <param name="size">�T�C�Y</param>
HitRenderer::HitRenderer(Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture, float size)
	:m_texture(texture),
	m_size(size),
	m_memorySize(size),
	m_used(false)
{
	m_screen = MyLib::ScreenResources::GetInstance();
	m_batchEffect = m_screen->GetBasicEffect();
	m_inputLayout = m_screen->GetInputLayout();
	// �v���~�e�B�u�o�b�`�̍쐬
	m_primitiveBatch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>>(m_screen->GetDeviceContext());
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
HitRenderer::~HitRenderer()
{
}

/// <summary>
/// �X�V����
/// </summary>
void HitRenderer::Update()
{
	if (!m_used)	return;
	
	m_timer--;
	if (m_timer <= 0)
		m_used = false;
}

/// <summary>
/// �`�悷��
/// </summary>
/// <param name="view">�r���[</param>
/// <param name="proj">�v���W�F�N�V����</param>
/// <param name="size">������� || ������鐔</param>
void HitRenderer::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj, float size)
{
	if (!m_used)	return;

	auto context = m_screen->GetDeviceContext();

	float alpha = (m_timer / RENDER_TIME * 200.0f) * 0.01f;
	m_size *= size;

	// ���_���
	DirectX::VertexPositionColorTexture vertex[4] =
	{
		DirectX::VertexPositionColorTexture(DirectX::SimpleMath::Vector3(  m_size,  0.5f,  m_size),DirectX::SimpleMath::Vector4(1.0f, 1.0f, 1.0f,  alpha), DirectX::SimpleMath::Vector2(0.0f, 0.0f)),
		DirectX::VertexPositionColorTexture(DirectX::SimpleMath::Vector3( -m_size, 0.5f,   m_size),DirectX::SimpleMath::Vector4(1.0f, 1.0f, 1.0f,  alpha), DirectX::SimpleMath::Vector2(1.0f, 0.0f)),
		DirectX::VertexPositionColorTexture(DirectX::SimpleMath::Vector3( -m_size, 0.5f,  -m_size),DirectX::SimpleMath::Vector4(1.0f, 1.0f, 1.0f,  alpha), DirectX::SimpleMath::Vector2(1.0f, 1.0f)),
		DirectX::VertexPositionColorTexture(DirectX::SimpleMath::Vector3(  m_size,  0.5f, -m_size),DirectX::SimpleMath::Vector4(1.0f, 1.0f, 1.0f,  alpha), DirectX::SimpleMath::Vector2(0.0f, 1.0f)),
	};

	// ���Z����
	context->OMSetBlendState(m_screen->GetCommonState()->Additive(), nullptr, 0xFFFFFFFF);
	// �[�x�o�b�t�@�͂Ȃ�
	context->OMSetDepthStencilState(m_screen->GetCommonState()->DepthNone(), 0);
	// �J�����O�͍�����
	context->RSSetState(m_screen->GetCommonState()->CullCounterClockwise());

	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::CreateTranslation(m_pos);

	m_batchEffect->SetWorld(world);
	m_batchEffect->SetView(view);
	m_batchEffect->SetProjection(proj);
	m_batchEffect->SetTexture(m_texture.Get());
	m_batchEffect->Apply(context);
	context->IASetInputLayout(m_inputLayout);

	m_primitiveBatch->Begin();
	m_primitiveBatch->DrawQuad(vertex[0], vertex[1], vertex[2], vertex[3]);
	m_primitiveBatch->End();
}

/// <summary>
/// �r���{�[�h��`�悷��
/// </summary>
/// <param name="view">�r���[</param>
/// <param name="proj">�v���W�F�N�V����</param>
/// <param name="eye">�A�C</param>
/// <param name="unit">��</param>
void HitRenderer::RenderBillBoard(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj, const DirectX::SimpleMath::Vector3& eye, const DirectX::SimpleMath::Vector3& unit)
{
	if (!m_used)	return;

	//	�r���{�[�h�s��̍쐬
	DirectX::SimpleMath::Matrix bilboard = DirectX::SimpleMath::Matrix::CreateBillboard(DirectX::SimpleMath::Vector3::Zero, m_pos - eye, unit);
	//	180��]������ׂ̍s��(�E����W�n���獶����W�n�ւ̕ϊ�)
	DirectX::SimpleMath::Matrix rotY = DirectX::SimpleMath::Matrix::Identity;
	rotY._11 = -1;
	rotY._33 = -1;

	//	�r�[���{�[�h�s���180�ŉ�]���Ă�����
	bilboard = rotY * bilboard;

	auto context = m_screen->GetDeviceContext();

	float alpha = (m_timer / RENDER_TIME * 200.0f) * 0.01f;
	m_size -= 0.03f;

	// ���_���
	DirectX::VertexPositionColorTexture vertex[4] =
	{
		DirectX::VertexPositionColorTexture(DirectX::SimpleMath::Vector3( m_size,  0.5f, m_size), DirectX::SimpleMath::Vector4(1.0f, 1.0f, 1.0f,  alpha), DirectX::SimpleMath::Vector2(0.0f, 0.0f)),
		DirectX::VertexPositionColorTexture(DirectX::SimpleMath::Vector3(-m_size,  0.5f, m_size),DirectX::SimpleMath::Vector4(1.0f, 1.0f, 1.0f,  alpha), DirectX::SimpleMath::Vector2(1.0f, 0.0f)),
		DirectX::VertexPositionColorTexture(DirectX::SimpleMath::Vector3(-m_size,  0.5f, -m_size),DirectX::SimpleMath::Vector4(1.0f, 1.0f, 1.0f,  alpha), DirectX::SimpleMath::Vector2(1.0f, 1.0f)),
		DirectX::VertexPositionColorTexture(DirectX::SimpleMath::Vector3( m_size,  0.5f, -m_size), DirectX::SimpleMath::Vector4(1.0f, 1.0f, 1.0f,  alpha), DirectX::SimpleMath::Vector2(0.0f, 1.0f)),
	};

	// ���Z����
	context->OMSetBlendState(m_screen->GetCommonState()->Additive(), nullptr, 0xFFFFFFFF);
	// �[�x�o�b�t�@�͂Ȃ�
	context->OMSetDepthStencilState(m_screen->GetCommonState()->DepthNone(), 0);
	// �J�����O�͍�����
	context->RSSetState(m_screen->GetCommonState()->CullCounterClockwise());

	bilboard *= DirectX::SimpleMath::Matrix::CreateTranslation(m_pos);

	m_batchEffect->SetWorld(bilboard);
	m_batchEffect->SetView(view);
	m_batchEffect->SetProjection(proj);
	m_batchEffect->SetTexture(m_texture.Get());
	m_batchEffect->Apply(context);
	context->IASetInputLayout(m_inputLayout);

	m_primitiveBatch->Begin();
	m_primitiveBatch->DrawQuad(vertex[0], vertex[1], vertex[2], vertex[3]);
	m_primitiveBatch->End();
}


/// <summary>
/// �G�t�F�N�g�q�b�g���̏���
/// </summary>
/// <param name="position">���W</param>
/// <param name="scaleFlag">�傫��</param>
void HitRenderer::HitEffect(DirectX::SimpleMath::Vector3 position, const bool& scaleFlag)
{
	m_used = true;
	m_pos  = position;
	m_timer= RENDER_TIME;

	//	�傫����ς���t���O��ON�Ȃ�ς���
	if(scaleFlag)			m_size = m_memorySize * 2.0f;
	else 					m_size = m_memorySize;
}
