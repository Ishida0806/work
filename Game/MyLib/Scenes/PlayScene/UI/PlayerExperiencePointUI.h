//
//		File Name �F PlayerExperiencePointUI.h
//		Production�F 2023/11/30
//		Author�@�@�F �Γc ����	
//	
#pragma once

class Player;

class PlayerExperiencePointUI final
{
	//	�萔
public:

	//	MAX�摜�̍��W
	static const DirectX::SimpleMath::Vector2	MAX_POSITION;
	//	�̗̓o�[�p�̍��W
	static const float							EXP_POS;
	//	�̗̓o�[��X���W
	static const int							EXP_IX;
	//	�̗̓o�[��Y���W
	static const int							EXP_IY;
	//	�̗̓o�[�̍���
	static const int							EXP_IH;


	//	�ϐ�
private:
	//	�v���C���[
	Player*					  m_player;
	//	�o�[�摜
	ID3D11ShaderResourceView* m_barTexture;
	//	MAX�摜
	ID3D11ShaderResourceView* m_maxTexture;
	//	�o���l�o�[
	float						  m_exBar;

	//	�֐�
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="player">�v���C���[<</param>
	PlayerExperiencePointUI(Player* player);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~PlayerExperiencePointUI();

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="timer">�^�C�}�[</param>
	void Update(const DX::StepTimer& timer);

	/// <summary>
	/// �`�悷��
	/// </summary>
	void Draw();
};