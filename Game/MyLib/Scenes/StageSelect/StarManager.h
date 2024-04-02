//
//		File Name �F StarManager.h
//		Production�F 2023/11/02
//		Author�@�@�F �Γc ����	
// 
#pragma once

#include "Star.h"

class StarManager final
{
private:

	//	�摜
	ID3D11ShaderResourceView*		   m_starTexture;
	//	���������܂Ƃ߂�
	std::vector<std::unique_ptr<Star>> m_stars;
	//	���݂̃X�e�[�W
	int								   m_stage;


public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="backGroundTexture">�摜</param>
	StarManager(ID3D11ShaderResourceView* starTexture);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~StarManager();

	/// <summary>
	/// ����������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="timer">�^�C�}�[</param>
	/// <param name="selectStage">�X�e�[�W�Z���N�g�i���o�[</param>
	void Update(const DX::StepTimer& timer, const int& selectStage);

	/// <summary>
	/// �`�悷��
	/// </summary>
	void Draw();

	/// <summary>
	/// �I������
	/// </summary>
	void Finalize();
};