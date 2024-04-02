
#include "pch.h"
#include "BulletHitParticle.h"

#include <VertexTypes.h>
#include "BinaryFile.h"
#include "Common/ReadData.h"

#define PARTICLE_NUM 12

const std::vector<D3D11_INPUT_ELEMENT_DESC> BulletHitParticle::INPUT_LAYOUT =
{
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0,	0,																			 D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0,	sizeof(DirectX::SimpleMath::Vector3),										 D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,		0,  sizeof(DirectX::SimpleMath::Vector3) + sizeof(DirectX::SimpleMath::Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 },
};


/// <summary>
/// �R���X�g���N�^
/// </summary>
BulletHitParticle::BulletHitParticle()
	:m_particleTexture(nullptr),
	m_isUsed(false),
	m_elapsedTime(0.0f)
{
	//	�V�F�[�_�[���쐬
	CreateSharder();

	m_particleTexture = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"HitBulletTextures");
	// �v���~�e�B�u�o�b�`�̍쐬
	m_primitevBatch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>>(MyLib::ScreenResources::GetInstance()->GetDeviceContext());

	//	�v�f�̍쐬
	for (size_t i = 0; i < PARTICLE_NUM; ++i)
	{
		float pos = Utility::CreateRandom(-2.0f, 2.0f);
		float x	  = Utility::CreateRandom(-3.0f, 3.0f);
		float y	  = Utility::CreateRandom(-3.0f, 3.0f);

		float scale = 0.5f;

		m_particles.push_back(
			std::make_unique<HitParticle>(
				0.0f,
				DirectX::SimpleMath::Vector3(pos),																									// ����W
				DirectX::SimpleMath::Vector3(x, 5.0f, y), 																							// ���x
				DirectX::SimpleMath::Vector3(0.1f, 0.1f, 0.1f),																						// �����x
				DirectX::SimpleMath::Vector3(scale), DirectX::SimpleMath::Vector3::Zero,															// �����X�P�[���A�ŏI�X�P�[��
				DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f), DirectX::SimpleMath::Color(0.0f, 0.0f, 0.0f, 0.0f)								// �����J���[�A�ŏI�J���[
			)
		);
	}
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BulletHitParticle::~BulletHitParticle()
{
}

/// <summary>
/// �X�V
/// </summary>
void BulletHitParticle::Update(const DX::StepTimer& timer)
{
	using namespace DirectX;

	//	�g�p��Ԃ���Ȃ��Ȃ珈�����s��Ȃ�
	if (!m_isUsed)	return;

	//	�o�ߎ��Ԃ𑫂�
	m_elapsedTime += static_cast<float>(timer.GetElapsedSeconds());
	
	//	�p�[�e�B�N�����X�V����
	for (auto& particle : m_particles)
		particle->Update(timer);

	//	���Ԍo�߂Ŏg�p��Ԃ��I�t�ɂ���
	if (m_elapsedTime >= 1.7f)
		m_isUsed = false;
}

/// <summary>
/// �`�悷��
/// </summary>
/// <param name="view">�r���[</param>
/// <param name="proj">�v���W�F�N�V����</param>
void BulletHitParticle::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	//	�g�p��Ԃ���Ȃ��Ȃ珈�����s��Ȃ�
	if (!m_isUsed)	return;

	//	�R���e�L�X�g
	auto context = MyLib::ScreenResources::GetInstance()->GetDeviceContext();
	//	�o�^����Ă��钸�_�����Z�b�g
	m_vertices.clear();

	//	�v�f���̍��W�E�F�E�傫��������
	for (auto& particle : m_particles)
	{
		DirectX::VertexPositionColorTexture	 vPCT{};

		vPCT.position = particle->GetPosition();
		vPCT.color = particle->GetNowColor();
		vPCT.textureCoordinate = DirectX::SimpleMath::Vector2(particle->GetNowScale().x, 0.0f);

		m_vertices.push_back(vPCT);
	}

	//	�\������_���Ȃ��ꍇ�͕`����I���
	if (m_vertices.empty())		return;
	
	//	�V�F�[�_�[�ɓn���ǉ��̃o�b�t�@���쐬����B(ConstBuffer�j
	ConstBuffer cbuff{};
	cbuff.matView = view.Transpose();
	cbuff.matProj = proj.Transpose();
	cbuff.matWorld = DirectX::SimpleMath::Matrix::Identity.Transpose();
	cbuff.Diffuse = DirectX::SimpleMath::Vector4::One;

	//	�󂯓n���p�o�b�t�@�̓��e�X�V(ConstBuffer����ID3D11Buffer�ւ̕ϊ��j
	context->UpdateSubresource(m_constantBuffer.Get(), 0, NULL, &cbuff, 0, 0);

	//	�V�F�[�_�Ƀo�b�t�@��n��
	ID3D11Buffer* cbuffer[1] = { m_constantBuffer.Get() };
	context->VSSetConstantBuffers(0, 1, cbuffer);
	context->GSSetConstantBuffers(0, 1, cbuffer);
	context->PSSetConstantBuffers(0, 1, cbuffer);

	//	�R�����X�e�[�g���Ăяo��
	DirectX::CommonStates* state = MyLib::ScreenResources::GetInstance()->GetCommonState();

	//	�摜�p�T���v���[(�摜���̂̐F)�̓o�^
	ID3D11SamplerState* sampler[1] = { state->LinearWrap()};
	context->PSSetSamplers(0, 1, sampler);

	//	�������`��w��
	ID3D11BlendState* blendstate = state->NonPremultiplied();

	// �������菈��
	context->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);

	// �[�x�o�b�t�@�ɏ������ݎQ�Ƃ���
	context->OMSetDepthStencilState(state->DepthDefault(), 0);

	// �J�����O�͍�����
	context->RSSetState(state->CullNone());

	//	�V�F�[�_���Z�b�g����
	context->VSSetShader(m_vertexShader.Get(),	 nullptr, 0);
	context->GSSetShader(m_geometryShader.Get(), nullptr, 0);
	context->PSSetShader(m_pixelShader.Get(),	 nullptr, 0);

	//	�s�N�Z���V�F�[�_�Ƀe�N�X�`����o�^����B
	context->PSSetShaderResources(0, 1, &m_particleTexture);

	//	�C���v�b�g���C�A�E�g�̓o�^
	context->IASetInputLayout(m_inputLayout.Get());

	//	�`����J�n����
	m_primitevBatch->Begin();

	//	�`�揈��
	m_primitevBatch->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &m_vertices[0], m_vertices.size());

	///	�`����I������
	m_primitevBatch->End();

	//	�V�F�[�_�̓o�^���������Ă���
	context->VSSetShader(nullptr, nullptr, 0);
	context->GSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);
}

/// <summary>
/// �r���{�[�h�ŕ`����s��
/// </summary>
/// <param name="view">�r���[</param>
/// <param name="proj">�v���W�F�N�V����</param>
/// <param name="eye">�J�����̈ʒu</param>
/// <param name="up">��</param>
void BulletHitParticle::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj, const DirectX::SimpleMath::Vector3& eye, const DirectX::SimpleMath::Vector3& unit)
{
	if (!m_isUsed)	return;

	//	�R���e�L�X�g
	auto context = MyLib::ScreenResources::GetInstance()->GetDeviceContext();
	//	�������Z�o
	DirectX::SimpleMath::Vector3 cameraDirection = m_tagetPosition - eye;
	//	�r���{�[�h�s��̍쐬
	DirectX::SimpleMath::Matrix bilboard = DirectX::SimpleMath::Matrix::CreateBillboard(DirectX::SimpleMath::Vector3::Zero, cameraDirection, unit);
	//	180��]������ׂ̍s��(�E����W�n���獶����W�n�ւ̕ϊ�)
	DirectX::SimpleMath::Matrix rotY = DirectX::SimpleMath::Matrix::Identity;
	rotY._11 *= -1;
	rotY._33 *= -1;
	//	�r�[���{�[�h�s���180�ŉ�]���Ă�����
	bilboard = rotY * bilboard;
	//	�o�^����Ă��钸�_�����Z�b�g
	m_vertices.clear();

	//	���K��
	cameraDirection.Normalize();
	
	//	�\�[�g���s��
	m_particles.sort(
		[&](const std::unique_ptr<HitParticle>& lhs, const std::unique_ptr<HitParticle>& rhs)
		{
			return cameraDirection.Dot(lhs->GetPosition() - eye) < cameraDirection.Dot(rhs->GetPosition() - eye);
		}
	);

	//	�v�f���̍��W�E�F�E�傫��������
	for (const auto& particle : m_particles)
	{
		DirectX::VertexPositionColorTexture	vPCT{};

		vPCT.position		   = static_cast<DirectX::XMFLOAT3>(particle->GetPosition());
		vPCT.color			   = static_cast<DirectX::XMFLOAT4>(particle->GetNowColor());
		vPCT.textureCoordinate = static_cast<DirectX::XMFLOAT2>(DirectX::SimpleMath::Vector2(particle->GetNowScale().x, particle->GetNowScale().y));

		m_vertices.push_back(vPCT);
	}

	//	�\������_���Ȃ��ꍇ�͕`����I���
	if (m_vertices.empty())		return;

	//	�V�F�[�_�[�ɓn���ǉ��̃o�b�t�@���쐬����B(ConstBuffer�j
	ConstBuffer cbuff{};
	cbuff.matView	= view.Transpose();
	cbuff.matProj	= proj.Transpose();
	cbuff.matWorld	= DirectX::SimpleMath::Matrix::Identity.Transpose();
	cbuff.Diffuse	= DirectX::SimpleMath::Vector4::One;

	//	�󂯓n���p�o�b�t�@�̓��e�X�V(ConstBuffer����ID3D11Buffer�ւ̕ϊ��j
	context->UpdateSubresource(m_constantBuffer.Get(), 0, NULL, &cbuff, 0, 0);

	//	�V�F�[�_�Ƀo�b�t�@��n��
	ID3D11Buffer* cbuffer[1] = { m_constantBuffer.Get() };
	context->VSSetConstantBuffers(0, 1, cbuffer);
	context->GSSetConstantBuffers(0, 1, cbuffer);
	context->PSSetConstantBuffers(0, 1, cbuffer);

	//	�R�����X�e�[�g���Ăяo��
	DirectX::CommonStates* state = MyLib::ScreenResources::GetInstance()->GetCommonState();

	//	�摜�p�T���v���[(�摜���̂̐F)�̓o�^
	ID3D11SamplerState* sampler[1] = { state->LinearWrap() };
	context->PSSetSamplers(0, 1, sampler);

	//	�������`��w��
	ID3D11BlendState* blendstate = state->NonPremultiplied();

	// �������菈��
	context->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);

	// �[�x�o�b�t�@�ɓǂݎ���p�Q�Ƃ���
	context->OMSetDepthStencilState(state->DepthRead(), 0);

	// �J�����O�͍�����
	context->RSSetState(state->CullNone());

	//	�V�F�[�_���Z�b�g����
	context->VSSetShader(m_vertexShader.Get(),	 nullptr, 0);
	context->GSSetShader(m_geometryShader.Get(), nullptr, 0);
	context->PSSetShader(m_pixelShader.Get(),	 nullptr, 0);

	//	�s�N�Z���V�F�[�_�Ƀe�N�X�`����o�^����B
	context->VSSetShaderResources(0, 1, &m_particleTexture);
	context->GSSetShaderResources(0, 1, &m_particleTexture);
	context->PSSetShaderResources(0, 1, &m_particleTexture);

	//	�C���v�b�g���C�A�E�g�̓o�^
	context->IASetInputLayout(m_inputLayout.Get());

	//	�`����J�n����
	m_primitevBatch->Begin();

	//	�`�揈��
	m_primitevBatch->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &m_vertices[0], m_vertices.size());

	///	�`����I������
	m_primitevBatch->End();

	//	�V�F�[�_�̓o�^���������Ă���
	context->VSSetShader(nullptr, nullptr, 0);
	context->GSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);
}

/// <summary>
/// �Փˎ��ɌĂ�
/// </summary>
/// <param name="position"></param>
void BulletHitParticle::Hit(DirectX::SimpleMath::Vector3 position)
{
	m_elapsedTime = 0.0f;

	m_isUsed = true;
	m_tagetPosition = position;

	for (const auto& particle : m_particles)
		particle->StartEffect(m_tagetPosition);
}

/// <summary>
/// �V�F�[�_�[���쐬
/// </summary>
void BulletHitParticle::CreateSharder()
{
	//	�f�o�C�X
	auto device = MyLib::ScreenResources::GetInstance()->GetDevice();

	// �s�N�Z���V�F�[�_�[�̍쐬
	std::vector<uint8_t> vsData = DX::ReadData(L"Resources/CSO/ParticleVS.cso");
	std::vector<uint8_t> gsData = DX::ReadData(L"Resources/CSO/ParticleGS.cso");
	std::vector<uint8_t> psData = DX::ReadData(L"Resources/CSO/ParticlePS.cso");

	//�C���v�b�g���C�A�E�g�̍쐬
	device->CreateInputLayout(
		&INPUT_LAYOUT[0],
		static_cast<UINT>(INPUT_LAYOUT.size()),
		vsData.data(),
		vsData.size(),
		m_inputLayout.GetAddressOf()
	);

	// ���_�V�F�[�_�쐬
	if (FAILED(device->CreateVertexShader(vsData.data(), vsData.size(), NULL, m_vertexShader.ReleaseAndGetAddressOf())))
	{
		// �G���[
		MessageBox(0, L"CreateVertexShader Failed.", NULL, MB_OK);
		return;
	}

	// �W�I���g���V�F�[�_�쐬
	if (FAILED(device->CreateGeometryShader(gsData.data(), gsData.size(), NULL, m_geometryShader.ReleaseAndGetAddressOf())))
	{
		// �G���[
		MessageBox(0, L"CreateGeometryShader Failed.", NULL, MB_OK);
		return;
	}
	// �s�N�Z���V�F�[�_�쐬
	if (FAILED(device->CreatePixelShader(psData.data(), psData.size(), NULL, m_pixelShader.ReleaseAndGetAddressOf())))
	{
		// �G���[
		MessageBox(0, L"CreatePixelShader Failed.", NULL, MB_OK);
		return;
	}

	//�V�F�[�_�[�Ƀf�[�^��n�����߂̃R���X�^���g�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ConstBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	device->CreateBuffer(&bd, nullptr, &m_constantBuffer);
}
