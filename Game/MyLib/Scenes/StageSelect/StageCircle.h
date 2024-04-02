//
//		File Name �F StageCircle.h
//		Production�F 2023/11/02
//		Author�@�@�F �Γc ����	
// 
#pragma once

class StageCircle
{
private:


	//	�摜
	ID3D11ShaderResourceView*						 m_texture;
	//	���W
	DirectX::SimpleMath::Vector2					 m_position;
	//	�F
	DirectX::SimpleMath::Color						 m_color;
	//	���ʎq
	int												 m_ID;

public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="texture">�摜</param>
	/// <param name="position">���W</param>
	/// <param name="ID">���ʎq</param>
	StageCircle(ID3D11ShaderResourceView* texture,const DirectX::SimpleMath::Vector2& position,const int& ID);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~StageCircle();

	/// <summary>
	/// ����������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="timer">�^�C�}�[</param>
	/// <param name="stageNum">�X�e�[�W�ԍ�</param>
	void Update(const DX::StepTimer& timer, const int& stageNum);

	/// <summary>
	/// �`�悷��
	/// </summary>
	void Draw();

	/// <summary>
	/// �I������
	/// </summary>
	void Finalize();
};