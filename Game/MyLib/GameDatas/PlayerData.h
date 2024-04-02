//
//		File Name �F PlayerData.h
//		Production�F 2024/4/02
//		Author�@�@�F �Γc ����	
// 
//		JSON�t�@�C����ǂݍ��ލۂ̏���w�b�_�[
//
#pragma once

struct PlayerData
{
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	PlayerData()
	{

	}

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~PlayerData() = default;

	//	�ϐ�
public:

	//	�v���C���[�̗̑�
	int							 playerHealth;
	//	�v���C���[�̍��W
	DirectX::SimpleMath::Vector3 position;
	//	�v���C���[�̃��f���̑傫��
	DirectX::SimpleMath::Vector3 modelScale;
	//	�U��������x
	float						 turnSpeed;
	//	�������̃A�j���[�V��������
	float						 winAnimationTime;
	//	���S���̃A�j���[�V��������
	float						 deathAnimationTime;
	//	�d��
	float						 gravity;	
};