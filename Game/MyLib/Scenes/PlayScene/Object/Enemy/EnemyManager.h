//
//		File Name �F EnemyManager.h
//		Production�F 2023/11/12
//		Author�@�@�F �Γc ����	
//	
#pragma once

class Object;
class Player;
class PlayScene;
class PlaySceneWave;
class PlayInfo;
class Enemy;

class EnemyManager
{
	//	�񋓌^
public:

	// �G�^�C�v
	enum class EnemyType
	{
		NormalEnemy = 0,
		TackleEnemy = 1,
		BossEnemy = 2,

		OverID
	};
	//	�A�N�Z�T
public:

	//	�{�X���擾����
	inline std::vector<std::shared_ptr<Enemy>>&   GetEnemy()		noexcept { return m_enemys; }

	/// <summary>
	/// �G���쐬����
	/// </summary>
	/// <param name="enemy">�G�̃^�C�v</param>
	/// <param name="health">�̗�</param>
	/// <param name="power">��</param>
	/// <param name="level">���x��</param>
	/// <param name="position">���W</param>
	void CreateEnemy
	(
		const EnemyType& enemy,
		const int& health,
		const int& power, 
		const int& level,
		const DirectX::SimpleMath::Vector3& position = DirectX::SimpleMath::Vector3::Zero
	);

	//	�萔
public:

	//	�ʏ�̓G�̗̑�
	static const int						  NORMAL_ENEMY_HELATH;
	//	�ˌ��G�̗̑�
	static const int						  TACLE_ENEMY_HELATH;
	//	�{�X�̗̑�
	static const int						  BOSS_ENEMY_HELATH;
	//	�{�X�̐����̌��E��			 
	static const int						  BOSS_ENEMY_RESTRICTION;
	//	���ʂ̓G�̐������E��
	static const int						  NORMAL_ENEMY_RESTRICTION;
	//	�ˌ��̓G�̐������E��
	static const int						  TACLE_ENEMY_RESTRICTION;
	//	�{�X�̔������x
	static const float						  BOSS_ENEMY_POP_SPEED;
	//	�ʏ�̓G�̔������x
	static const float						  NORMAL_ENEMY_POP_SPEED;
	//	�ˌ��̓G�̔������x
	static const float						  TACLE_ENEMY_POP_SPEED;
	//	�ǔ����[�h�̌��E��
	static const int						  HATE_ENEMY_NUM;
	//	��Փx�ɂ���đ����鐔
	static const int						  INCREASE_WORLD_LEVEL;
	//	�G�̗�
	static const int						  ENEMY_POWER;



	//	�\����
private:

	//	�G�̐����
	struct EnemyInformation
	{
		//	���ݐ�
		int		existence;
		//	��������
		float	popTime;

		/// <summary>
		/// �T�C�Y���u1�v���₷
		/// </summary>
		void IncrementSize()
		{
			existence++;
		}

		/// <summary>
		/// �傫��
		/// </summary>
		/// <returns></returns>
		int size()
		{
			return existence;
		}

		/// <summary>
		/// �o���J�E���g�����Z�b�g����
		/// </summary>
		void ResetCount()
		{
			existence = 0;
		}

		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		EnemyInformation()
			:existence(0),
			popTime(0.0f)
		{

		}
	};	


	//	�ϐ�
private:

	//	�v���C�V�[��
	PlayScene*										 m_playScene;
	//	�v���C���
	PlayInfo*										 m_playInfo;
	//	�v���C�V�[���̃E�F�[�u
	PlaySceneWave*									 m_playSceneWave;
	//	�v���C���[
	Player*											 m_player;
	//	�ʏ�G
	EnemyInformation								 m_normalEnemyInformation;
	//	�ˌ��G
	EnemyInformation								 m_tackleEnemyInformation;
	//	�{�X
	EnemyInformation								 m_bossEnemyInformation;
	//	�{�X�G
	std::vector<std::shared_ptr<Enemy>>				 m_enemys;
	//	�ǔ���Ԃ̌��E��
	int												 m_hateReaction;
	//	�ʏ�G�̌��E������
	int												 m_normalReaction;
	//	�ˌ��G�̌��E������
	int												 m_tackleReaction;

	//	�֐�
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="playScene">�v���C�V�[��</param>
	/// <param name="player">�v���C���[</param>
	/// <param name="playSceneWave">�v���C�V�[���̃E�F�[�u</param>
	EnemyManager(PlayScene* playScene, Player* player , PlaySceneWave* playSceneWave);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~EnemyManager();

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
	/// <param name="view">�r���[</param>
	/// <param name="proj">�v���W�F�N�V����</param>
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj);


	/// <summary>
	/// �I������
	/// </summary>
	void Finalize();


private:

	/// <summary>
	/// �{�X�������X�V
	/// </summary>
	/// <param name="timer">�^�C�}�[</param>
	void UpdateBosses(const DX::StepTimer& timer);

	/// <summary>
	/// �ʏ�G�������X�V
	/// </summary>
	/// <param name="timer">�^�C�}�[<</param
	void UpdateNormalEnemies(const DX::StepTimer& timer);

	/// <summary>
	/// �ˌ��G�������X�V
	/// </summary>
	/// <param name="timer">�^�C�}�[<</param>
	void UpdateTackleEnemies(const DX::StepTimer& timer);	

	/// <summary>
	/// �G�����񂾂�폜
	/// </summary>
	void DeadObject();	

	/// <summary>
	/// �ǔ����[�h�̓G�̐���T��
	/// </summary>
	void FindHateEnemy();	

	/// <summary>
	///	�X�|�[������G��I��
	/// </summary>
	void SelectSpawnEnemy();
};