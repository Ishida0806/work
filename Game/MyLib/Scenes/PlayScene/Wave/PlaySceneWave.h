//
//		File Name �F PlaySceneWave.h
//		Production�F 2024/1/23
//		Author�@�@�F �Γc ����	
//
#pragma once
#include "Game/MyLib/GameDatas/Number.h"
#include "Game/MyLib/Scenes/PlayScene/Wave/ButtleWave.h"

class PlayScene;

class PlaySceneWave
{
	//	�萔
public:

	//	�E�F�[�u�̐F���
	static const DirectX::SimpleMath::Color WAVE_COLOR;

	//	�A�N�Z�T
public:

	//	���݂̃E�F�[�u�����擾����
	inline int GetCurrentWave()						const		{ return m_currentWave; }
	//	�ő�E�F�[�u�����擾����
	inline int GetMaxWave()							const		{ return m_maxWave; }
	//	�ŏI�E�F�[�u���H
	inline bool IsFinalWave()						const		{ return m_isFinalWave; }
	//	�G�̃f�[�^���擾����
	inline std::vector<EnemyData> GetEnemyData()	const		{ return m_enemyDatas; }

	//	�ϐ�
private:

	//	�v���C�V�[��
	PlayScene*										 m_playScene;
	//	�X�R�A�̉摜
	ID3D11ShaderResourceView*						 m_waveDisplayTexture;
	//	�G�̃f�[�^	
	std::vector<EnemyData>							 m_enemyDatas;
	//	�ő�X�e�[�W�̐���
	std::unique_ptr<Number>							 m_maxNumber;
	//	���݃X�e�[�W�̐���
	std::unique_ptr<Number>							 m_currentNumber;
	//	�ŏI�E�F�[�u��
	bool											 m_isFinalWave;
	//	���݂̃E�F�[�u
	int												 m_currentWave;
	//	�ő�E�F�[�u��
	int												 m_maxWave;


	//	�֐�
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="playScene">�v���C�V�[��</param>
	PlaySceneWave(PlayScene* playScene);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~PlaySceneWave();

	/// <summary>
	///	����������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// �`�悷��
	/// </summary>
	void Draw();

	/// <summary>
	/// ���̃E�F�[�u�֍s��
	/// </summary>
	void NextWave();

	/// <summary>
	/// �X�|�[�������G�I�u�W�F�N�g�̃f�[�^���폜����
	/// </summary>
	void DeleteSpawnedEnemyData();
};

