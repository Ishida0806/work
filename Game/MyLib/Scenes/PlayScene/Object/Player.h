//
//		File Name �F Player.h
//		Production�F 2023/6/12
//		Author�@�@�F �Γc ����	
//	
#pragma once

#include "Object.h"
#include "Game/MyLib/Scenes/PlayScene/Object/PlayerCircle/PlayerArrow.h"
#include "Game/MyLib/Scenes/PlayScene/Object/Cursor/Cursor.h"
#include "Game/MyLib/Scenes/PlayScene/Object/Wepons/Sord.h"
#include "Game/MyLib/GameDatas/PlayerStatus.h"
#include "Game/MyLib/GameDatas/PlayerMove.h"


class Sord;
class Cursor;
class PlayerCircle;
class PlayerComponent;

class Player : public Object , public PlayerStatus , public PlayerMove
{
	//	�A�N�Z�T
public:

	//	�U����Ԃ��擾
	inline bool								 IsAttack()					const { return m_sord->IsAttack(); }
	//	�������Ă��邩�H
	inline bool								 IsAlive()					const { return m_isAlive; }
	//	���S�A�j���[�V���������H
	inline bool								 IsDeathAnimation()			const { return m_isDeathAnimation; }
	//	�A�j���[�V���������H
	inline bool								 IsAnimation()				const { return m_isAnimation; }
	//	�����A�j���[�V���������H
	inline bool								 IsWinAnimation()			const { return m_isWinAnimation; }
	//	�L�����N�^�[�̋��̓����蔻��
	inline Collision::Shape::Sphere			 GetSphere()				const { return m_playerSphere; }
	//	�\�[�h�̎擾
	inline Sord*							 GetSord()					const { return m_sord.get(); }
	//	���̃J�v�Z���̓����蔻��
	inline Collision::Shape::Capsule		 GetSordCapuselColision()	const { return m_sord->GetWeponCapsule(); }
	//	���̍��W
	inline DirectX::SimpleMath::Vector3		 GetSordPosition()			const { return m_sord->GetPosition(); }
	//	�J�[�\���̍��W�擾����
	inline DirectX::SimpleMath::Vector3		 GetCursorPosition()		const { return m_cursorPosition; }
	//	��]�p
	inline DirectX::SimpleMath::Quaternion	 GetCursorRotate()			const { return m_cursorRotate; }
	//	�������ʂɂ���ăA�j���[�V������������
	void WhyGameResult(const std::string& resultString);

	//�萔
public:


	//	�Փˎ��̃m�b�N�o�b�N
	static const float						  REACTION;
	//	�ǂ̏ꏊ
	static const float						  WALL_PLACE;

	//	�񋓌^
public:

	//	�v���C���[�X�e�[�g
	enum class PlayerParts
	{
		None = 0,

		Head = 1,
		RightArm = 2,
		LeftArm = 3,
		RightLeg = 4,
		LeftLeg = 5,

		OverID
	};

	//	�֐�
public: 
	
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="playerParam">�v���C���[�p�����[�^</param>
	Player(PlayerData* playerParam);
	//	�f�X�g���N�^
	~Player();

	/// <summary>
	/// ����������
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="timer">�^�C�}�[</param>
	void Update(const DX::StepTimer& timer) override;

	/// <summary>
	/// �`�揈��
	/// </summary>
	/// <param name="view">�r���[</param>
	/// <param name="proj">�v���W�F�N�V����</param>
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj) override;

	/// <summary>
	/// �I������
	/// </summary>
	void Finalize() override;

	/// <summary>
	/// �_���[�W��^����
	/// </summary>
	/// <param name="damege">�_���[�W��</param>
	void Damege(const int& damege);

	/// <summary>
	/// �_���[�W��^����
	/// </summary>
	/// <param name="damege">�_���[�W��</param>
	/// <param name="direction">����</param>
	/// <param name="reaction">�ӂ��Ƃ΂���</param>
	void Damege(const int& damege,DirectX::SimpleMath::Vector3 direction, float reaction = Player::REACTION);

	/// <summary>
	/// �_���[�W��^����
	/// </summary>
	/// <param name="damege">�_���[�W��</param>
	/// <param name="direction">����</param>
	/// <param name="reaction">�ӂ��Ƃ΂���</param>
	void Damege(const int& damege, DirectX::SimpleMath::Vector3 direction, const DirectX::SimpleMath::Vector3& reaction);

	/// <summary>
	/// ���S���̃A�j���[�V����
	/// </summary>
	/// <param name="timer">�^�C�}�[</param>
	void DethAnimation(const DX::StepTimer& timer);

	/// <summary>
	/// �������̃A�j���[�V����
	/// </summary>
	/// <param name="timer">�^�C�}�[</param>
	void WinAnimation(const DX::StepTimer& timer);

	/// <summary>
	/// �����Ă��邩�m�F����
	/// </summary>
	/// <returns>���S���</returns>
	bool HealthCheck();

	/// <summary>
	/// �v���C���[�̃A�j���[�V����
	/// </summary>
	/// <param name="timer">�^�C�}�[</param>
	void PlayerAnimation(const DX::StepTimer& timer);

	//	���ߍ��݊֐�
private:

	//	�����蔻��̍X�V
	void UpdateColison();
	//	�v���C���[�ƌ��̍X�V
	void UpdatePlayerAndSordLerp();
	//	�e�I�u�W�F�N�g���̍쐬
	void CreateDeviceDependentResources();
	//	�v���C���[���X�e�[�W�ɗ��܂点��
	void ArriveStage();

	//	�ϐ�
private:
	//	�v���C���[�̃��f��
	DirectX::Model*									 m_playerModel;
	//	�v���C���[�p�����[�^
	PlayerData*										 m_playerParam;
	//	�p�[�c�B
	std::vector<std::unique_ptr<PlayerComponent>>	 m_playerParts;
	//	�v���~�e�B�u�o�b�`
	std::unique_ptr<DirectX::GeometricPrimitive>	 m_primitive;
	//	�J�[�\��
	std::unique_ptr<Cursor>							 m_cursol;
	//	��
	std::unique_ptr<Sord>							 m_sord;
	//	�v���C���[�T�[�N��
	std::unique_ptr<PlayerArrow>					 m_playerArrow;
	//	�J�[�\�����W
	DirectX::SimpleMath::Vector3					 m_cursorPosition;
	//	�J�[�\����]�p
	DirectX::SimpleMath::Quaternion					 m_cursorRotate;
	//	�d��
	float											 m_gravity;
	//	�A�j���[�V��������
	float											 m_animationTime;
	//	���S�A�j���[�V����
	bool											 m_isDeathAnimation;
	//	�����A�j���[�V����
	bool											 m_isWinAnimation;
	//	�A�j���[�V������
	bool											 m_isAnimation;
	//	����ł��邩�H
	bool											 m_isAlive;
	//	��
	Collision::Shape::Sphere						 m_playerSphere;
	//	���̃J�v�Z��	
	Collision::Shape::Capsule						 m_sordCapsule;

};