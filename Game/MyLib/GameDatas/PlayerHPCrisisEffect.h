//
//		File Name �F PlayerHPCrisisEffect.h
//		Production�F 2023/1/10
//		Author�@�@�F �Γc ����	
//
#pragma once
#include "PostEffect.h"

class PlayerHPCrisisEffect : public PostEffect
{
	//	�萔
public:

	//	�^�C�}�[�̉���
	static const float						  TIMER_SPEED;
	//	�ԐF�̔Z�x
	static const float						  RED_DENSITY;
	//	�ʏ�̑傫��X
	static const float						  DEFAULT_SCALE_X;
	//	�ʏ�̑傫��Y
	static const float						  DEFAULT_SCALE_Y;
	//	�g��̕␳�l
	static const float						  CORRECTION_EXPANSION;
	//	�|�X�g�G�t�F�N�g�̐^��
	static const DirectX::SimpleMath::Vector2 CRISIS_ORIGIN_POSITION;

	//	�ϐ�
private:

	//	�摜
	ID3D11ShaderResourceView*	 m_texture;
	//	��������
	DirectX::SimpleMath::Vector2 m_scale;
	
	//	�֐�
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	PlayerHPCrisisEffect();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~PlayerHPCrisisEffect() override;

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