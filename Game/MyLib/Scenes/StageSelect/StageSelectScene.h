//
//		File Name �F StageSelectScene.h
//		Production�F 2023/9/14
//		Author�@�@�F �Γc ����
//
#pragma once
#include "Game/MyLib/Scenes/IScene.h"

#include "Game/MyLib/Scenes/StageSelect/Bird.h"
#include "Game/MyLib/Scenes/StageSelect/Enemy2D.h"
#include "Game/MyLib/Scenes/StageSelect/Door2D.h"
#include "Game/MyLib/Scenes/StageSelect/KeyFont.h"
#include "Game/MyLib/Scenes/StageSelect/Player2D.h"
#include "Game/MyLib/Scenes/StageSelect/StageCircle.h"
#include "Game/MyLib/Scenes/StageSelect/StarManager.h"
#include "Game/MyLib/Scenes/StageSelect/StageBackGround.h"

class Game;
class Door2D;
class Enemy2D;
class KeyFont;


interface IScene;

class StageSelectScene : public IScene
{
	//	�萔
public:
	//	�N�[���^�C��
	static const float						  COOL_TIME;
	//	�f�t�H���g�̑傫��
	static const float						  BASE_SCALE;
	//	�t�F�[�h���̖ڕW�傫��
	static const float						  FADE_TARGET_SCALE;
	//	����
	static const float						  DISTANCE;
	//	���[�v���̑��x
	static const float						  LERP_SPEED;
	//	���[�v���̑傫���̑��x
	static const float						  LERP_SCALE_SPEED;
	//	�A�j���[�V�����^�C��
	static const float						  FIN_TIME;


	//	enum
public:
	//	�X�e�[�W��
	enum class CHOOSE_STAGE
	{
		STAGE_1 = 0,
		STAGE_2 = 1,
		STAGE_3 = 2,
		STAGE_4 = 3,

		OverID
	};
	//	KEY���͂łǂ���ɓ�������
	enum class MOVE_DIRECTION
	{
		CENTER = 0,
		RIGHT = 1,
		LEFT = 2,
	};

	//	�ϐ�
private:
	//	�Q�[��
	Game*										m_game;
	//	�G��2D�摜
	std::vector<std::unique_ptr<Enemy2D>>		m_enemies2D;
	//	�h�A��2D�摜
	std::vector<std::unique_ptr<Door2D>>		m_doors2D;
	//	�X�e�[�W�~
	std::vector<std::unique_ptr<StageCircle>>   m_stageCircles;
	//	�L�[�摜
	std::vector<std::unique_ptr<KeyFont>>		m_keys2D;
	//	�w�i�摜�̃N���X
	std::unique_ptr<StageBackGround>		    m_stageBackGround;
	//	���X
	std::unique_ptr<StarManager>			    m_starManeger;
	//	��
	std::unique_ptr<Bird>						m_bird;
	//	�v���C���[��2D
	std::unique_ptr<Player2D>					m_player2D;
	//	�X�N���[�����\�[�X
	MyLib::ScreenResources*						m_screen;
	//	���\�[�X
	MyLib::ResourcesData*					    m_resorces;
	//	�o�b�N�O���E���h�̘g
	ID3D11ShaderResourceView*				    m_stageSelectBackGroundStageFrameworkTexture;
	//	�G�X�P�[�v�L�[
	ID3D11ShaderResourceView*				    m_escTexture;
	//	�摜�̑傫��
	DirectX::SimpleMath::Vector2				m_doorScale;
	//	�X�e�[�g���I�������
	bool									    m_preMove;
	//	
	bool									    m_isChanegeScene;
	//	�o�ߎ���
	float									    m_elapsedTime;
	//	�A�j���[�V�����̃N�[���^�C��
	float									    m_moveCoolTime;
	//	�`�F���W�X�e�[�g 
	CHOOSE_STAGE							    m_stageState;
	//	�ǂ���ɓ�������
	MOVE_DIRECTION							    m_isMoveDirection;

	//	�֐�
public:
	StageSelectScene(Game* game);
	~StageSelectScene();

	//	����������
	void Initialize() override;
	//	�X�V����
	void Update(const DX::StepTimer& timer) override;
	//	�`�揈��
	void Render() override;
	//	�I������	
	void Finalize() override;

	//	�v���C�x�[�g�֐�
private:
	//	�f�o�C�X�ˑ��̃��\�[�X
	void CreateDeviceDependentResources();
	//	UI���X�V����
	void UpdateUIs(const DX::StepTimer& timer);
	//	�L�[�������ꂽ��
	void InputKey();
	//	�v���C���[�̏����X�V����
	void UpdatePlayer();
	//	�v���C�V�[���ɂ������߂̃h�A���X�V����
	void UpdateDoor(const DX::StepTimer& timer);
	//	�X�e�[�g��Ԃ��X�V
	void CheckState();
	//	�L�[�̎w����`�悷��
	void RenderKey();
	//	�h�A��`�悷��
	void RenderDoor();
};