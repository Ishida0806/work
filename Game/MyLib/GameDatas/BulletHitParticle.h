
#pragma once

#include <list>
#include "HitParticle.h"


class BulletHitParticle
{
	//	�A�N�Z�T
public:

	//	�g�p��Ԃ��擾����
	inline bool IsUsed()	const { return m_isUsed; }

	//	�\����
public:

	//�f�[�^�󂯓n���p�R���X�^���g�o�b�t�@���M
	struct ConstBuffer
	{
		DirectX::SimpleMath::Matrix		matWorld;
		DirectX::SimpleMath::Matrix		matView;
		DirectX::SimpleMath::Matrix		matProj;
		DirectX::SimpleMath::Vector4	Diffuse;
	};

	//	�萔
public:

	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;

	//	�ϐ�
private:
	//	�p�[�e�B�N��
	std::list<std::unique_ptr<HitParticle>>										  m_particles;
	// ���̓��C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout>									  m_inputLayout;
	// ���_�V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11VertexShader>									  m_vertexShader;
	// �s�N�Z���V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11PixelShader>									  m_pixelShader;
	// �W�I���g���V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11GeometryShader>								  m_geometryShader;
	//	�R���X�^���g�o�b�t�@�[
	Microsoft::WRL::ComPtr<ID3D11Buffer>										  m_constantBuffer;
	// �v���~�e�B�u�o�b�`
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_primitevBatch;
	//	���_���
	std::vector<DirectX::VertexPositionColorTexture>							  m_vertices;
	//	�G�t�F�N�g
	ID3D11ShaderResourceView*													  m_particleTexture;
	//	�ڕW���W
	DirectX::SimpleMath::Vector3												  m_tagetPosition;
	//	�g�p���
	bool																		  m_isUsed;
	//	�o�ߎ���
	float																		  m_elapsedTime;

	//	�֐�
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	BulletHitParticle();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~BulletHitParticle();

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="timer">�^�C�}�[</param>
	void Update(const DX::StepTimer& timer);

	/// <summary>
	/// �`�揈��
	/// </summary>
	/// <param name="view">�r���[</param>
	/// <param name="proj">�v���W�F�N�V����</param>
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj);

	/// <summary>
	/// �r���{�[�h�ŕ`����s��
	/// </summary>
	/// <param name="view">�r���[</param>
	/// <param name="proj">�v���W�F�N�V����</param>
	/// <param name="eye">�J�����̈ʒu</param>
	/// <param name="up">��</param>
	void Render(
		const DirectX::SimpleMath::Matrix& view, 
		const DirectX::SimpleMath::Matrix& proj,
		const DirectX::SimpleMath::Vector3& eye, 
		const DirectX::SimpleMath::Vector3& unit
	);


	/// <summary>
	/// �Փˎ��ɌĂяo��
	/// </summary>
	/// <param name="position"���W</param>
	void Hit(DirectX::SimpleMath::Vector3 position);

private:

	/// <summary>
	/// �V�F�[�_�[���쐬
	/// </summary>
	void CreateSharder();

};