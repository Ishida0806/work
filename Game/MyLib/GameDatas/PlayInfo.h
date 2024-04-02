//
//		File Name �F PlayInfo.h
//		Production�F 2023/10/17
//		Author�@�@�F �Γc ����
//
#pragma once

class PlayInfo final
{
	//	�萔
public:

	//	�X�R�A�̍ő�l
	static const int MAX_SCORE;

	//	�A�N�Z�T
public:

	//	�X�N���[���̃C���X�^���X���擾����
	static PlayInfo*				const GetInstance();
	//	���x�����擾����
	inline int GetLevel()			const { return m_level;  }
	//	�X�R�A���擾����
	inline int GetScore()			const { return m_score;  }
	//	�o�ߎ��Ԃ��擾����
	inline float GetElapseedTime()	const { return m_elapsedTime;  }
	//	�ʏ�̓G�̎擾����
	inline int GetNormalKnockNum()  const { return m_normalEnemyKnockNum;  }
	//	�ˌ��̓G�̐����擾����
	inline int GetTackleKnockNum()  const { return m_tackleEnemyKnockNum;  }
	//	�{�X�̓G�̐����擾����
	inline int GetBossKnockNum()	const { return m_bossEnemyKnockNum;  }

	/// <summary>
	/// �X�R�A���グ��
	/// </summary>
	/// <param name="score">:���X�R�A�H</param>
	void UpScore(const int& score);


	/// <summary>
	/// �o�ߎ��Ԃ�ݒ肷��
	/// </summary>
	/// <param name="elapsedTime">�o�ߎ���</param>
	void SetElapsedTime(const float& elapsedTime);

	//	�֐�
public:
	
	~PlayInfo();

	// ����͋��e���Ȃ�
	void operator=(const PlayInfo& object) = delete;
	// �R�s�[�R���X�g���N�^�͋��e���Ȃ�
	PlayInfo(const PlayInfo& object) = delete;

	//	����������
	void Initialize();
	// �ʏ�G�̌��j�����v���X����
	void KnockNormal();
	// �ˌ��G�̌��j�����v���X����
	void KnockTackle();
	// �{�X�G�̌��j�����v���X����
	void KnockBoss();

	//	�R���X�g���N�^
private:

	//	�R���X�g���N�^->�C���X�^���X���쐬�����Ȃ�
	PlayInfo();

	//	�ϐ�
private:

	// �X�N���[�����\�[�V�[�Y�N���X�̃C���X�^���X�ւ̃|�C���^
	static std::unique_ptr<PlayInfo>		 m_playInfo;
	//	���x��
	unsigned int							 m_level;
	//	�ʏ�G�̓|������
	unsigned int							 m_normalEnemyKnockNum;
	//	�ˌ��G�̓|������
	unsigned int							 m_tackleEnemyKnockNum;
	//	�{�X�̓|������
	unsigned int							 m_bossEnemyKnockNum;
	//	�X�R�A
	int										 m_score;
	//	�o�ߎ���
	float									 m_elapsedTime;
};

