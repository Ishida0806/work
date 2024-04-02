//
//		File Name �F ButtleWave.h
//		Production�F 2024/1/23
//		Author�@�@�F �Γc ����	
//
#pragma once
#include "Game/MyLib/GameDatas/EnemyData.h"

class PlayScene;

class ButtleWave
{
	//	�A�N�Z�T
public:

	//	�ő�E�F�[�u�����擾����
	inline int GetMaxWave() const { return m_maxWave; }

	//	�ϐ�
private:

	//	�v���C�V�[��
	PlayScene*									m_playScene;
	//	�ő�E�F�[�u
	int											m_maxWave;

	//	�֐�
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="playScene">�v���C�V�[��</param>
	ButtleWave(PlayScene* playScene);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~ButtleWave();

	std::vector<EnemyData> OpenMap();
};