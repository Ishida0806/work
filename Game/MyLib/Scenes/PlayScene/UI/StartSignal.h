//
//		File Name �F StartSignal.h
//		Production�F 2023/10/17
//		Author�@�@�F �Γc ����	
//	
#pragma once

#include "Game/MyLib/GameDatas/IUI.h"

interface IUI;

class StartSignal : public IUI
{
	//	�萔
public:

	//	GO�摜�̐^�񒆂̍��W
	static const DirectX::SimpleMath::Vector2 ORIGIN_GO_POSITION;
	//	READY�摜�̐^�񒆂̍��W
	static const DirectX::SimpleMath::Vector2 ORIGIN_READY_POSITION;
	//	�摜�̃f�t�H���g�̑傫��
	static const DirectX::SimpleMath::Vector2 BASE_SCALE;
	//	GO���o���Ƃ��ɏ����h���
	static const float						  SHAKE_GO_POSITION;

	//	�A�N�Z�T
public:

	/// <summary>
	/// �t�F�[�h�ɕK�v�Ȏ��Ԃ�ݒ肷��
	/// </summary>
	/// <param name="pFadeTimer">:�t�F�[�h�^�C���̃|�C���^�[</param>
	/// <param name="fadeMaxTime">:�}�b�N�X����</param>
	void SetFadeTime(float* pFadeTimer,float fadeMaxTime);

	//	�X�e�[�g���
private:

	enum class STATE
	{
		IDLE = 0,
		READY = 1,
		GO = 2,
		FINISH = 3
	};

	//	�ϐ�
private:
	//	�X�N���[�����\�[�X
	MyLib::ScreenResources*   m_screen;
	//	���\�[�V�[�Y�f�[�^
	MyLib::ResourcesData*	  m_resources;
	//	READY�摜�̍��W
	DirectX::SimpleMath::Vector2 m_readyPosition;
	//	GO�摜�̍��W
	DirectX::SimpleMath::Vector2 m_goPosition;
	//	READY�摜
	ID3D11ShaderResourceView* m_readyUi;
	//	GO�摜
	ID3D11ShaderResourceView* m_goUi;
	//	���ɍs���|�C���^�[�̃J�E���g
	float*					  m_pNextCount;
	//	���ɍs���J�E���g�̃}�b�N�X�l
	float					  m_maxFadeCount;
	//	�`�悷��X�e�[�g
	STATE					  m_renderState;

	//	�֐�
public:

	StartSignal();
	~StartSignal();

	//	����������
	void Initialize() override;
	//	�X�V����
	void Update(const DX::StepTimer& timer) override;
	//	�`�悷��
	void Draw() override;

	//	�v���C�x�[�g�֐�
private:
	//	�f�o�C�X�ˑ��̃��\�[�X�̏�����
	void CreateDeviceDependentResources();
};