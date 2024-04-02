//
//		File Name �F ScoreOutPut.h
//		Production�F 2023/11/12
//		Author�@�@�F �Γc ����	
//
#pragma once

class Number;
class PlayInfo;

class ScoreOutPut
{
	//	�萔
public:

	//	�X�R�A�̍��W
	static const DirectX::SimpleMath::Vector2 SCORE_POSITION;
	//	�X�R�A�̐^�񒆂̍��W
	static const DirectX::SimpleMath::Vector2 SCORE_ORIGIN_POSITION;

	//	�ϐ�
private:

	//	�v���C�C���t�H���[�V����
	PlayInfo* m_pPlayInfo;
	//	�X�R�A��\������
	std::unique_ptr<Number>		m_pScore;
	//	�@�m�[�}���X�R�A��\������
	std::unique_ptr<Number>		m_pNormalKnock;
	//	�@�ˌ��X�R�A��\������
	std::unique_ptr<Number>		m_pTackleKnock;
	//	�@�{�X�X�R�A��\������
	std::unique_ptr<Number>		m_pBossKnock;

	//	�֐�
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	ScoreOutPut();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~ScoreOutPut();

	/// <summary>
	/// ����������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <returns></returns>
	bool Update();

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw();
};