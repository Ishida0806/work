//
//		File Name �F PlayerHPBar.h
//		Production�F 2023/10/3
//		Author�@�@�F �Γc ����
// 
#pragma once

#include "Game/MyLib/GameDatas/IUI.h"

class Player;
interface IUI;

class PlayerHPBar : public IUI
{
	//	�萔
public:
	//	��
	static const DirectX::SimpleMath::Color RED;
	//	���F
	static const DirectX::SimpleMath::Color YELLOW;
	//	��
	static const DirectX::SimpleMath::Color GREEN;
	//	�̗̓o�[�p�̍��W
	static const int						HP_POS;
	//	�̗̓o�[��X���W
	static const int						HP_IX;
	//	�̗̓o�[��Y���W
	static const int						HP_IY;
	//	�̗̓o�[�̍���
	static const int						HP_IH;
	//	�덷�͈̔�
	static const int						HP_RANGE_VALUE;


	//	�A�N�Z�T
public:

	//	�v���C���[��BAD��ԂɂȂ���
	inline bool IsBad() const { return m_isBad; }

	//	�v���C���[�̃|�C���^�[��ݒ肷��
	void SetPlayer(Player* player);
	//	�̗͂̃X�e�[�g��Ԃ��擾����
	void SetHPState(int state);

	//	�X�e�[�g
private:

	//	HP��Ԃɂ��X�e�[�g
	enum class HP_RENDER_STATE
	{
		FINE = 0,
		LITTLE_BAD = 1,
		BAD = 2,
		DEAD = 3
	};

	//	�ϐ�
private:

	Player*						m_pPlayer;
	//	�X�N���[�����\�[�X
	MyLib::ScreenResources*		m_screen;
	//	���\�[�V�[�Y�f�[�^
	MyLib::ResourcesData*		m_resources;
	//	�v���C���[�̗̑̓o�[
	ID3D11ShaderResourceView*	m_hpPlayerBarUI;
	//	BAD��Ԃ�
	bool						m_isBad;
	//	�v���C���[�̗̑͂��o�[�ŕ\����������
	int							m_hpBar;
	//	�v���C���[�̗̑͂��o�[�ŕ\���������̂̌���
	int							m_nowHpBar;
	//	�̗͏�Ԃ̃X�e�[�g
	HP_RENDER_STATE				m_hpState;

public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	PlayerHPBar();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~PlayerHPBar();

	/// <summary>
	/// ����������
	/// </summary>
	void Initialize()						override;

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="timer">�^�C�}�[</param>
	void Update(const DX::StepTimer& timer)	override;

	/// <summary>
	/// �`�悷��
	/// </summary>
	void Draw()								override;

	//	�v���C�x�[�g�֐�
private:

	//	�f�o�C�X�ˑ��̃��\�[�X�̏�����
	void CreateDeviceDependentResources();
	//	�o�[�̕`��
	void RenderBar();
};