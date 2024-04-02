//
//		File Name �F PlayerUI.h
//		Production�F 2023/10/2
//		Author�@�@�F �Γc ����
// 
#pragma once
#include "Game/MyLib/GameDatas/IUI.h"

interface IUI;
class Player;

class PlayerUI : public IUI
{
	//	�A�N�Z�T
public:

	//	�̗͂̏�Ԃ��擾����
	int GetState()	const { return static_cast<int>(m_hpState); }
	//	�v���C���[�̃|�C���^�[��ݒ肷��
	void SetPlayer(Player* player);

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
	//	�v���C���[
	Player*					m_pPlayer;
	//	�X�N���[�����\�[�X
	MyLib::ScreenResources* m_screen;
	//	���\�[�V�[�Y�f�[�^
	MyLib::ResourcesData*   m_resources;
	//	���q�̗ǂ��v���C���[�̉摜
	ID3D11ShaderResourceView* m_goodPlayer;
	//	���q�̈����v���C���[�̉摜
	ID3D11ShaderResourceView* m_badPlayer;
	//	���q�̏��������v���C���[�̉摜
	ID3D11ShaderResourceView* m_littleBadPlayer;
	//	���񂾂Ƃ��̉摜
	ID3D11ShaderResourceView* m_deathPlayer;
	//	�̗͂̏��
	HP_RENDER_STATE			 m_hpState;

	//	�֐�
public:

	PlayerUI();
	~PlayerUI();

	//	����������
	void Initialize() override;
	//	�X�V����
	void Update(const DX::StepTimer& timer) override;
	//	�`�悷��
	void Draw() override;

	//	�v���C�x�[�g�֐�
private:
	//	�f�o�C�X�ˑ��̃��\�[�X�̏�����
	void CreateDeviceDependentResources();
	//	�̗͂̏�Ԃɂ���ĕ`���ς���
	void RenderHPState();
};