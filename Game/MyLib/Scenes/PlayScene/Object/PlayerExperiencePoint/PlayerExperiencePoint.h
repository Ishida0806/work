//
//		File Name �F PlayerExperiencePoint.h
//		Production�F 2023/11/30
//		Author�@�@�F �Γc ����	
//	
#pragma once

class Player;

class PlayerExperiencePoint final
{
	//	�A�N�Z�T
public:

	//	�K�v�Ȍo���l���擾����
	inline int GetExperiencePoint()		const { return m_experiencePoint; }
	//	���ɕK�v�Ȍo���l���擾����
	inline int GetNeedExperiencePoint() const { return m_needExperiencePoint; }

	//	�o���l���擾����
	void SetExperiencePoint(const int& exPoint);

	//	�萔
public:

	//	�v���C���[�̍ő僌�x��
	static const int MAX_PLAYER_LEVEL;
	//	�ŏ��̌o���l
	static const int FIRST_LEVEL_EXP;
	//	�o���l�̑�����
	static const int INCREASE_EXP;

	//	�ϐ�
private:
	//	�v���C���[
	Player* m_player;
	//	�o���l
	int m_experiencePoint;
	//	���̃��x���A�b�v�ɕK�v�Ȍo���l
	int m_needExperiencePoint;
	//	�]��̌o���l
	int m_surplusExperiencePoint;

	//	�֐�
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="player">�v���C���[<</param>
	PlayerExperiencePoint(Player* player);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~PlayerExperiencePoint();

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="timer">�^�C�}�[</param>
	void Update(const DX::StepTimer& timer);

	//	���ߍ��݊֐�
private:

	//	�o���l��␳����
	void ClampEXP();
};