//
//		File Name �F PlayScene.h
//		Production�F 2023/6/19
//		Author�@�@�F �Γc ����	
//
#pragma once

//	�C���N�[���h�t�@�C���@	-----------------------------------------
#include "Game/MyLib/Scenes/IScene.h"

#include "Game/Game.h"
#include "Common/Floor_Model.h"
#include "Game/MyLib/Scenes/PlayScene/Object/FallingCherryBlossoms/FallingCherryBlossoms.h"
#include "Game/MyLib/Scenes/PlayScene/TutorialSystem/TutorialSystem.h"
#include "Game/MyLib/Scenes/PlayScene/Object/Bullet/BulletManager.h"
#include "Game/MyLib/Scenes/PlayScene/UI/PlayerExperiencePointUI.h"
#include "Game/MyLib/Scenes/PlayScene/Object/Enemy/EnemyManager.h"
#include "Game/MyLib/Scenes/PlayScene/Object/Enemy/EnemyFactory.h"
#include "Game/MyLib/Scenes/PlayScene/Object/Wall/WallFactory.h"
#include "Game/MyLib/Scenes/PlayScene/Object/Item/ItemManager.h"
#include "Game/MyLib/Scenes/PlayScene/Object/SkyDoem/SkyDome.h"
#include "Game/MyLib/Scenes/PlayScene/Wave/PlaySceneWave.h"
#include "Game/MyLib/Scenes/PlayScene/Object/Wall/Wall.h"
#include "Game/MyLib/Scenes/PlayScene/UI/PlayerHPBar.h"
#include "Game/MyLib/Scenes/PlayScene/UI/StartSignal.h"
#include "Game/MyLib/Scenes/PlayScene/Object/Player.h"
#include "Game/MyLib/Scenes/PlayScene/UI/PlayeScore.h"
#include "Game/MyLib/Scenes/PlayScene/UI/LevelCard.h"
#include "Game/MyLib/Scenes/PlayScene/UI/BatMeter.h"
#include "Game/MyLib/Scenes/PlayScene/UI/PlayerUI.h"
#include "Game/MyLib/Scenes/PlayScene/UI/MiniMap.h"
#include "Game/MyLib/GameDatas/BulletHitParticle.h"
#include "Game/MyLib/GameDatas/ColisionObjects.h"
#include "Game/MyLib/GameDatas/PlayPostEffect.h"
#include "Game/MyLib/GameDatas/HitRenderer.h"
#include "Game/MyLib/GameDatas/PlayInfo.h"
#include "Game/MyLib/GameDatas/Number.h"
#include "Game/MyLib/GameDatas/Pause.h"
#include "Game/MyLib/Camera/Camera.h"

//	�O���錾	-----------------------------------------
class Game;
class Player;
class NormalEnemy;
class TackleEnemy;
class BossEnemy;
class Bullet;
class Camera;
class SkyDome;
class Wall;


class PlayScene : public IScene
{
	//	�A�N�Z�T
public:

	/// <summary>
	/// ���x�����擾����
	/// </summary>
	/// <returns>���x��</returns>
	inline int GetWordLevel()	const { return m_worldLevel; }

	/// <summary>
	/// ����N�����H
	/// </summary>
	/// <returns>����N����</returns>
	inline bool IsFirstOpen()	const { return m_isFirstOpen; }

	//	�萔
public:
	//	�㑤�̕Ǐ��
	static const DirectX::SimpleMath::Vector3 TOP_WALL_SCALE;
	static const DirectX::SimpleMath::Vector3 TOP_WALL_POSITION;
	//	�E���̕Ǐ��
	static const DirectX::SimpleMath::Vector3 RIGHT_WALL_SCALE;
	static const DirectX::SimpleMath::Vector3 RIGHT_WALL_POSITION;
	//	�����̕Ǐ��
	static const DirectX::SimpleMath::Vector3 UNDER_WALL_SCALE;
	static const DirectX::SimpleMath::Vector3 UNDER_WALL_POSITION;
	//	�����̕Ǐ��
	static const DirectX::SimpleMath::Vector3 LEFT_WALL_SCALE;
	static const DirectX::SimpleMath::Vector3 LEFT_WALL_POSITION;
	//	�J�����̕␳���W
	static const DirectX::SimpleMath::Vector3 CAMERA_OFFSET_POSITION;
	//	�������ۂ̕�����
	static const std::string				  WIN_STRING;
	//	�������ۂ̕�����
	static const std::string				  LOSE_STRING;
	//	�ǂ̑傫��
	static const int						  WALL_SCLAE;
	//	�q�b�g���̃G�t�F�N�g�̐������E��
	static const int						  HIT_RENDER_RESTRICTION;
	//	�Ԑ���̐�����
	static const int						  FALLING_CHERRY_BLOSSOMS_GENERATED;
	//	�G�t�F�N�g�̃T�C�Y
	static const float						  EFFECT_SIZE;
	//	�ˌ��G�̃��A�N�V����
	static const DirectX::SimpleMath::Vector3 TACLE_ENEMY_REACTION;
	//	���̑��̓G�̃��A�N�V����
	static const float						  OTHER_ENEMY_REACTION;
	//	�t�F�[�h�^�C��
	static const float						  FADE_TIME;
	//	�I������
	static const float						  FINISHED_TIME;

	//	�ϐ�
private:
	//	�Q�[��
	Game*												m_game;
	//	�X�N���[�����\�[�X
	MyLib::ScreenResources*								m_screen;
	//	�|�[�Y
	std::unique_ptr<Pause>								m_pause;
	//	�J����
	std::unique_ptr<Camera>								m_camera;	
	//	�����f��	
	std::unique_ptr<Floor_Model>						m_floor_Model;
	//	�v���C���[
	std::unique_ptr<Player>								m_player;
	//	�v���C���[��UI
	std::unique_ptr<PlayerUI>							m_playerUI;
	//	�Q�[���X�^�[�g�̍��}
	std::unique_ptr<StartSignal>						m_startSignal;
	//	�p�[�e�B����G�t�F�N�g
	std::vector<std::unique_ptr<BulletHitParticle>>		m_hitBulletPatricles;
	//	�v���C���[�̗̑̓o�[UI
	std::unique_ptr<PlayerHPBar>						m_playerBarUI;
	//	�v���C�X�R�A
	std::unique_ptr<PlayeScore>							m_playScore;
	//	�~�j�}�b�v
	std::unique_ptr<MiniMap>							m_miniMap;
	//	��
	std::vector<std::unique_ptr<Wall>>					m_walls;
	//	�q�b�g�����_�[
	std::vector<std::unique_ptr<HitRenderer>>			m_hitRenders;
	//	�e�q�b�g���̃G�t�F�N�g
	std::vector<std::unique_ptr<HitRenderer>>			m_hitBulletRenders;
	//	�Ԑ���
	std::vector<std::unique_ptr<FallingCherryBlossoms>>	m_fallingCherryBlossoms;
	//	�X�J�C�h�[��
	std::unique_ptr<SkyDome>							m_skyDome;
	//	�G�̃}�l�[�W���[
	std::unique_ptr<EnemyManager>						m_enemyManager;
	//	�A�C�e���̃}�l�[�W���[
	std::unique_ptr<ItemManager>						m_itemManager;
	//	�e�̃}�l�[�W��
	std::unique_ptr<BulletManager>						m_bulletManager;
	//	�����蔻����s��
	std::unique_ptr<ColisionObjects>					m_colisionObjects;
	//	�o���l�̃o�[
	std::unique_ptr<PlayerExperiencePointUI>			m_expBar;
	//	���x���A�b�v���̃J�[�h
	std::unique_ptr<LevelCard>							m_levelCard;
	//	�v���C�V�[���Ŏg���|�X�g�G�t�F�N�g	
	std::unique_ptr<PlayPostEffect>						m_postEffect;
	//	�v���C�V�[���̃E�F�[�u
	std::unique_ptr<PlaySceneWave>						m_playSceneWave;
	//	�`���[�g���A��
	std::unique_ptr<TutorialSystem>						m_tutorialSystem;
	//	�Q�[������
	std::string											m_gameResultString;
	//	�t�F�[�h���̎���
	float												m_fadeTime;
	//	�I������
	float												m_finishedTime;
	//	�G�S�̂̃��x��
	int													m_worldLevel;
	//	�J�n�̃t�F�[�h�����H
	bool												m_IsFade;
	//	�I������
	bool												m_isFinish;
	//	�t�F�[�h�A�E�g�̃^�X�N
	bool												m_isFadeOutTask;
	//	����N����
	bool												m_isFirstOpen;

public:
	//	�R���X�g���N�^
	PlayScene(Game* game, MyLib::ScreenResources* screen, int stagelevel = 0);
	//	�f�X�g���N�^
	~PlayScene();

	//	����������
	void Initialize() override;
	//	�X�V����
	void Update(const DX::StepTimer& timer) override;
	//	�`�揈��
	void Render() override;
	//	�I������	
	void Finalize() override;
	//	�G�t�F�N�g��`�悷�邵�傫����ς���
	void HitRnder(const DirectX::SimpleMath::Vector3& position);
	//	�G�t�F�N�g��`�悷�邵�傫����ς���
	void HitRnder(const DirectX::SimpleMath::Vector3& position, const Enemy* enemy);
	//	�G�t�F�N�g�𔻒�`�悷��
	void HitBulletRnder(const DirectX::SimpleMath::Vector3& position);
	//  �^�C�g���V�[���ɐ؂�ς���
	void ChangeSceneTitle();
	//	�}�E�X�J�[�\���������邩
	void ShowMouse(const bool& isShow);
	//	�`���[�g���A���I��
	void FinishTutorial();


	//	���ߍ��݊֐�
private:
	//	�f�o�C�X�ˑ��̃��\�[�X�̏�����
	void CreateDeviceDependentResources();
	//	�Q�[���̏I�������𖞂��������m�F����
	bool IsFinished(const DX::StepTimer& timer);
	//	�J�������X�V����
	void UpdateCamera(const DX::StepTimer& timer);
	//	�~�j�}�b�v���X�V����
	void UpdateMiniMap(const DX::StepTimer& timer);
	//	�v���C���[�͐����Ă邩
	void IsAlivePlayer();
	//	UI��`�悷��
	void UIRender(); 
	//	�t�F�[�h����
	bool NowFade(const DX::StepTimer& timer);
	//	�|�[�Y����
	bool NowPause();
};
