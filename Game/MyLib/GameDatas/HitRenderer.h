//
//		File Name �F HitRenderer.h
//		Production�F 2023/8/02
//		Author�@�@�F �Γc ����
//
#pragma once

class HitRenderer
{
	//	�萔
public:
	// �G�t�F�N�g�\������
	static const float RENDER_TIME;
private:

	MyLib::ScreenResources*														  m_screen;

	DirectX::BasicEffect*														  m_batchEffect;											
	ID3D11InputLayout*															  m_inputLayout;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>							  m_texture;
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_primitiveBatch;
private:

	// ���W
	DirectX::SimpleMath::Vector3 m_pos;		
	// �\������
	float m_timer;		
	//	�g�p���
	bool m_used;
	//	�摜�̑傫��
	float m_size;
	//	�傫�����L������
	float m_memorySize;

	//	�A�N�Z�T
public:

	inline bool IsUsed()	const { return m_used; }

public:
	HitRenderer(Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture, float size);
	~HitRenderer();

	void Update();
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj,float size = 1.0f);
	void RenderBillBoard(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj, const DirectX::SimpleMath::Vector3& eye,const DirectX::SimpleMath::Vector3& unit);

	void HitEffect(DirectX::SimpleMath::Vector3 position, const bool& scaleFlag);
};