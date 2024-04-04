//
//		File Name �F TutorialSystem.h
//		Production�F 2024/4/04
//		Author�@�@�F �Γc ����	
//	
#pragma once
#include "Game/MyLib/GameDatas/FiniteStateMachine.h"

class EnemyManager;
class PlayScene;

class TutorialSystem
{
	//	�񋓌^
public:

	//	�`���[�g���A���V�X�e��
	enum class TutorialState
	{
		MovingMethod		= 0,
		WeponMethod			= 1,
		KillEnemyMethod		= 2,
		FinishMethod		= 3,

		OverID				= 4
	};

	//	�A�N�Z�T
public:

	//	�G�̃}�l�[�W���[���擾����
	inline EnemyManager* GetEnemyManager()	const					{ return m_enemyManager; }
	//	�v���C�V�[�����擾����
	inline PlayScene*	GetPlayScene ()		const					{ return m_playScene; }

	//	�`���[�g���A���ē��摜�̐ݒ�
	inline void SetGuideTexture(ID3D11ShaderResourceView* texture);

	//	�G�C���A�X�錾
public:

	using TUTORIALSTATE  = FiniteStateMachine<TutorialSystem, TutorialSystem::TutorialState>;
	using ITUTORIALSTATE = TUTORIALSTATE::IState;

	//	�ϐ�
private:

	//	�L���X�e�[�g�}�V�[��
	std::unique_ptr<TUTORIALSTATE>	m_fsm;
	//	�摜
	ID3D11ShaderResourceView*		m_guideTutorialTexture;
	//	�G�̃}�l�[�W���[
	EnemyManager*					m_enemyManager;
	//	�v���C�V�[��
	PlayScene*						m_playScene;
	

	//	�֐�
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="playScene">�v���C�V�[��</param>
	/// <param name="enemyManager">�G�}�l�[�W��</param>
	TutorialSystem(PlayScene* playScene , EnemyManager* enemyManager);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~TutorialSystem();

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
	/// �`�揈��
	/// </summary>
	void Render();

	/// <summary>
	/// �I������
	/// </summary>
	void Finalize();
};