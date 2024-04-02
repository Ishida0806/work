//
//		File Name �F SkyDome.h
//		Production�F 2023/6/12
//		Author�@�@�F �Γc ����	
//	
#pragma once

class SkyDome final
{
	//	enum
public:

	enum class STAGE_STATE
	{
		stage1 = 0,
		stage2 = 1,
		stage3 = 2,
		stage4 = 3,
	};

	//	�ϐ�
private:
	//	�X�N���[�����\�[�X
	MyLib::ScreenResources*		m_screens;
	//	�摜
	ID3D11ShaderResourceView*	m_texture;
	//	�X�J�C�h�[��
	DirectX::Model*				m_skyModel;
	//	�X�e�[�W�̔ԍ�
	int							m_stageNum;
	//	�X�e�[�W�̃X�e�[�g
	STAGE_STATE					m_stageState;

	//	�֐�
public:

	SkyDome(int stageNum);
	~SkyDome();

	//	�`��
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj);
};

