//
//		File Name �F PlayerMove.h
//		Production�F 2023/1/30
//		Author�@�@�F �Γc ����	
//
#pragma once
class Player;

class PlayerMove
{
	//	�A�N�Z�T
public:

	//	�_�b�V�������H
	inline bool								 IsDash()					const { return m_isDash; }
	//	�����Ă��邩�H
	inline bool								 IsWalk()					const { return m_isWalk; }

	//	�ϐ�
private:

	//	�v���C���[
	Player*											 m_player;
	//	�_�b�V�������H
	bool											 m_isDash;
	//	�����Ă��邩�H
	bool											 m_isWalk;

	//	�֐�
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="player">�v���C���[</param>
	PlayerMove(Player* player);

	//	�f�X�g���N�^
	~PlayerMove() = default;

	//	�v���C���[�������g����
protected:

	/// <summary>
	/// �v���C���[�̈ړ�����
	/// </summary>
	void MovePlayer();
};