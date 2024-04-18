
#pragma once
#include "LevelCardEffect.h"
#include "LevelCardBackGround.h"

class PlayScene;
class Player;

class LevelCard
{
	//	�萔
public:

	//	�w�i�摜�̒��S�_
	static const DirectX::SimpleMath::Vector2 BACKGROUND_ORIGIN_POSITION;
	//	�ҋ@����
	static const float						  WAIT_SECONDS;
	//	�I������鐔
	static const int						  SELECT_NUMBER;


	//	�񋓌^
public:

	//	�J�[�h�̃^�C�v
	enum class CardType
	{
		PowerUP	= 0,
		HealthUP	= 1,
		SpeedUP	= 2,

		OverID = 3
	};

	//	�ϐ�
private:

	//	�v���C�V�[��
	PlayScene*									  m_playScene;
	//	�v���C���[
	Player*										  m_player;
	//	�J�[�h�B
	std::vector<std::unique_ptr<LevelCardEffect>> m_cards;
	//	�w�i�摜�N���X
	std::unique_ptr<LevelCardBackGround>		  m_backGround;
	//	�����_���J�[�h�ԍ�
	std::vector<int>							  m_randomCards;
	//	�N���b�N���ꂽ
	bool										  m_isClick;
	//	�ҋ@���Ԃ��I��
	bool										  m_finStand;
	//	�����_���I�o���I�������
	bool										  m_finRandom;
	//	�ҋ@����
	float										  m_standbyTime;
	//	�v���C���[�̃��x��
	int											  m_playerLevel;
	//	�I�΂�Ă���ԍ�
	int											  m_selectCard;

	//	�֐�
public:

	/// <summary>
	///	�R���X�g���N�^
	/// </summary>
	/// <param name="playScene">�v���C�V�[��</param>
	/// <param name="player">�v���C���[</param>
	LevelCard(PlayScene* playScene ,  Player* player);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~LevelCard();

	/// <summary>
	/// ����������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="timer">�^�C�}�[</param>
	/// <returns>�g�p���</returns>
	bool Update(const DX::StepTimer& timer);

	/// <summary>
	/// �`�悷��
	/// </summary>
	void Draw();

	//	���ߍ��݊֐�
private:

	//	�����_���őI�o�����ԍ���I��
	void CreateRandomNumber(const DX::StepTimer& timer);
	//	�L�[�̑���
	bool KeyUpdate();
	//	�}�E�X�̍X�V
	bool MouseUpdate();
	//	�N���b�N���ꂽ
	bool ClickedCard();
	//	�}�E�X���W���擾����
	DirectX::SimpleMath::Vector2 GetMousePosition();
};