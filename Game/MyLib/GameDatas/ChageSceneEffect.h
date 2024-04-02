//
//		File Name �F ChageSceneEffect.h
//		Production�F 2023/1/17
//		Author�@�@�F �Γc ����	
//
#pragma once
#include "ChangeEffect.h"
class Game;

class ChageSceneEffect final
{
	//	�񋓌^
public:


	//	�A�N�Z�T
public:	

	/// <summary>
	/// �V�[���J�ڂ̃G�t�F�N�g�̗v����ݒ�
	/// </summary>
	/// <param name="requestType">���N�G�X�g�^�C�v</param>
	/// <param name="fadeType">�t�@�[�h�^�C�v</param>
	void RequestChangeEffect(const ChangeEffect::ChangeSceneType& requestType, const ChangeEffect::ChangeSceneFadeType& fadeType);

	//	�ϐ�
private:

	//	�Q�[��
	Game*									   m_game;
	//	�V�[���J�ڂ̃G�t�F�N�g�B
	std::vector<std::unique_ptr<ChangeEffect>> m_fadeEffects;

	//�֐�
public:

	/// <summary>
	/// ����������
	/// </summary>
	/// <param name="game">�Q�[��</param>
	ChageSceneEffect(Game* game);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~ChageSceneEffect();

	/// <summary>
	/// ����������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="timer">�^�C�}�[</param>
	void Update(const DX::StepTimer& timer);

	/// <summary>
	/// �G�t�F�N�g�̕`��
	/// </summary>
	void DrawEffect();
};