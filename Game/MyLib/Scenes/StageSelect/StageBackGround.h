//
//		File Name �F StageBackGround.h
//		Production�F 2023/11/01
//		Author�@�@�F �Γc ����	
// 
#pragma once

class StageBackGround final
{
	//	�萔
public:
	//	�閾���O�̐F
	static const DirectX::SimpleMath::Vector4 DAWN_COLOR;
	//	���̐F
	static const DirectX::SimpleMath::Vector4 MORNING_COLOR;
	//	������̐F
	static const DirectX::SimpleMath::Vector4 DAYTIME_COLOR;
	//	��̐F
	static const DirectX::SimpleMath::Vector4 NIGHT_COLOR;

	//	�\����
public:
	//	�R���X�g�o�b�t�@�[
	struct ConstBuffer
	{
		DirectX::SimpleMath::Vector4	Diffuse;
	};

	//	�ϐ�
private:
	//	�s�N�Z���V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_PS_Stage;
	//	�R���X�g�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D11Buffer>	  m_cBuffer;
	//	�摜
	ID3D11ShaderResourceView*				  m_backGroundTexture;
	//	�X�e�[�W�p�̃R���X�g�o�b�t�@�[
	ConstBuffer								  m_stageBackGroundConstBuffer;
	//	�ڕW�F
	DirectX::SimpleMath::Vector4			  m_targetColor;
	//	�X�e�[�W�V�[���̍ő�X�e�[�W��
	int										  m_maxStageNum;

	//	�֐�
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="backGroundTexture">�摜</param>
	StageBackGround(ID3D11ShaderResourceView* backGroundTexture, const int& maxStage);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~StageBackGround();

	/// <summary>
	/// ����������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update(const int& selectStage);

	/// <summary>
	/// �`�悷��
	/// </summary>
	void Draw();

	/// <summary>
	/// �I������
	/// </summary>
	void Finalize();
};