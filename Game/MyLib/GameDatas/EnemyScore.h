//
//		File Name �F EnemyScore.h
//		Production�F 2024/4/02
//		Author�@�@�F �Γc ����	
// 
//		JSON�t�@�C����ǂݍ��ލۂ̏���w�b�_�[
//
#pragma once

struct EnemyScore
{
	
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	EnemyScore()
	{

	}

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~EnemyScore() = default;

	//	�ϐ�
public:

	//	�v���C���[�̗̑�
	int							 normalScore;
	//	�ˌ��̗̑�
	int							 tacleScore;
	//	�{�X�̗̑�
	int							 bossScore;
};