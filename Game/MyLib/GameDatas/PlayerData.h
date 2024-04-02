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
	/// <param name="health">�̗�</param>
	/// <param name="position">���W</param>
	/// <param name="modelScale">���f���̑傫��</param>
	/// <param name="turnSpeed">�U��������x</param>
	/// <param name="winAnimationTime">�������̃A�j���[�V����</param>
	/// <param name="deathAnimationTime">���S���̃A�j���[�V����</param>
	/// <param name="gravity">�d��</param>
	PlayerData(
		const int& health , 
		const DirectX::SimpleMath::Vector3& position, 
		const DirectX::SimpleMath::Vector3& modelScale, 
		const float& turnSpeed,
		const float& winAnimationTime,
		const float& deathAnimationTime,
		const float& gravity
	)
		:
		playerHealth(health),
		position(position),
		modelScale(modelScale),
		winAnimationTime(winAnimationTime),
		deathAnimationTime(deathAnimationTime),
		gravity(gravity)
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