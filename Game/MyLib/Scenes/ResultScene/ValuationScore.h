//
//		File Name �F ValuationScore.h
//		Production�F 2023/11/12
//		Author�@�@�F �Γc ����	
//
#pragma once

class ValuationScore
{
	//	�萔
public:

	//	�����̑�����
	static const double						  INCREASE_BOTTOM;
	//	�]���̏ꏊ
	static const DirectX::SimpleMath::Vector2 VALUCATION_POSITION;
	//	�]���̐^�񒆂̏ꏊ
	static const DirectX::SimpleMath::Vector2 VALUCATION_ORIGIN_POSITION;
	//	�]���摜�̑傫��
	static const DirectX::SimpleMath::Vector2 VALUCATION_BASE_SCALE;
	//	�Ȃ���p�x
	static const float						  TARGET_ANGLE;
	//	�C�[�W�[�X�e�[�W���Z���N�g���ꂽ
	static const int						  SELECT_EASY;
	//	�m�[�}���X�e�[�W���Z���N�g���ꂽ
	static const int						  SELECT_NORMAL;
	//	�n�[�h�X�e�[�W���Z���N�g���ꂽ
	static const int						  SELECT_HARD;
	//	�G���h���X�X�e�[�W���Z���N�g���ꂽ
	static const int						  SELECT_ENDRES;


	//	�ϐ�
private:

	//	���q�̉摜
	ID3D11ShaderResourceView* m_valutationTex;
	//	���\�[�X�}�l�[�W��
	MyLib::ResourcesData*	  m_res;
	//	�`�悵�Ă��������H
	bool					  m_isDraw;

	//	�֐�
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	ValuationScore();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~ValuationScore();

	/// <summary>
	/// ����������
	/// </summary>
	/// <param name="selectStage">�Z���N�g���ꂽ�X�e�[�W�ԍ�</param>
	/// <param name="score">�X�R�A</param>
	void Initialize(const int& selectStage, const int& score);
	
	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="isTop">��ɏオ�������H</param>
	void Update(const bool& isTop);

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw();

	/// <summary>
	/// �I������
	/// </summary>
	void FInalize();
};