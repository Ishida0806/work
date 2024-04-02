//
//		File Name �F EnemyHeart.h
//		Production�F 2023/8/02
//		Author�@�@�F �Γc ����
//
#pragma once
class Enemy;

class EnemyHeart
{
	//	�萔
public:
	// �G�t�F�N�g�\������
	static const float RENDER_TIME;

	//	�ϐ�
private:
	//	�X�N���[�����\�[�X
	MyLib::ScreenResources*														  m_screen;
	//	�o�b�`�G�t�F�N�g
	DirectX::BasicEffect*														  m_batchEffect;	
	//	�C���v�b�g���C�A�E�g
	ID3D11InputLayout*															  m_inputLayout;
	//	�n�[�g�摜
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>							  m_heartTexture;
	//	�n�[�g�̔w�i�摜
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>							  m_coverHeartTexture;
	//	�v���~�e�B�u�o�b�`
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_primitiveBatch;
	//	�G
	Enemy*																		  m_enemy;
	// �o�ߎ���
	float m_elapsedTime;		
	//	�摜�̑傫��
	float m_size;

public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="enemy">�G</param>
	EnemyHeart(Enemy* enemy);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~EnemyHeart();

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
};