//
//		File Name �F PlayerSwingSpeedEffect.h
//		Production�F 2023/1/15
//		Author�@�@�F �Γc ����	
//
#pragma once
#include "PostEffect.h"

class PlayerSwingSpeedEffect : public PostEffect
{
	//	�萔
public:

	//	�^�C�}�[�̉���
	static const float						  TIMER_SPEED;
	//	�|�X�g�G�t�F�N�g�̐^��
	static const DirectX::SimpleMath::Vector2 CRISIS_ORIGIN_POSITION;

	//	�ϐ�
private:

	//	�摜
	ID3D11ShaderResourceView*	 m_texture;
	
	//	�֐�
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	PlayerSwingSpeedEffect();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~PlayerSwingSpeedEffect() override;

	/// <summary>
	///	����������
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="timer">�^�C�}�[</param>
	void Update(const DX::StepTimer& timer) override;

	/// <summary>
	/// �`��̃^�C�v
	/// </summary>
	void Draw() override;
};