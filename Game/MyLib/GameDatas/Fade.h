//
//		File Name �F Fade.h
//		Production�F 2023/9/11
//		Author�@�@�F �Γc ����
// 
#pragma once

class Fade
{
	//	�萔
public:
	//	���[�v�^�C��
	static const float LERP_TIME;
	//	�I���^�C��
	static const float FIN_TIME;

	//	�A�N�Z�T
public:

	inline bool GetFinFlag()	const { return m_finFlag; }

	//	�ϐ�
private:
	//	���\�[�X�f�[�^
	MyLib::ResourcesData* m_resources;
	//  �X�N���[�����\�[�X
	MyLib::ScreenResources* m_screen;
	//	���̉摜
	ID3D11ShaderResourceView* m_blackTexture;
	//	�X�^�[�g�t���O
	bool	m_startFlag;
	//	�I���t���O
	bool	m_finFlag;
	//	�b��
	float	m_second;


	//	�֐�
public:

	Fade();
	~Fade();

	void Initialize();
	void Update(const DX::StepTimer& timer);
	void Render();
	void Finalize();

	void StartFade();
};