//
//		File Name �F PlayScene.cpp
//		Production�F 2023/6/19
//		Author�@�@�F �Γc ����	
// 
//		�v���C�V�[��
//	
#include "pch.h"

////////////////////////Scene//////////////////////////////////
#include "Game/MyLib/Scenes/TitleScene/TitleScene.h"
#include "Game/MyLib/Scenes/PlayScene/PlayScene.h"
#include "Game/MyLib/Scenes/StageSelect/StageSelectScene.h"
#include "Game/MyLib/Scenes/ResultScene/ResultScene.h"
////////////////////////////////////////////////////////////////

#include "Game/MyLib/GameDatas/EdditPlayData.h"

//	�������ۂ̕�����
const std::string				   PlayScene::WIN_STRING			 = "win";
//	�������ۂ̕�����
const std::string				   PlayScene::LOSE_STRING			 = "lose";
//	�E���̕ǂ̂����蔻��̑傫���E�ǂ̈ʒu
const DirectX::SimpleMath::Vector3 PlayScene::RIGHT_WALL_SCALE		 = DirectX::SimpleMath::Vector3(1.5f, 5.5f, 26.0f);
const DirectX::SimpleMath::Vector3 PlayScene::RIGHT_WALL_POSITION 	 = DirectX::SimpleMath::Vector3(27.5f, 0.0f, 0.0f);
//	�����̕ǂ̂����蔻��̑傫���E�ǂ̈ʒu
const DirectX::SimpleMath::Vector3 PlayScene::UNDER_WALL_SCALE		 = DirectX::SimpleMath::Vector3(26.0f, 5.0f, 1.5f);
const DirectX::SimpleMath::Vector3 PlayScene::UNDER_WALL_POSITION	 = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 27.5f);
//	�����̕ǂ̂����蔻��̑傫���E�ǂ̈ʒu
const DirectX::SimpleMath::Vector3 PlayScene::LEFT_WALL_SCALE		 = DirectX::SimpleMath::Vector3(1.5f, 5.0f, 26.0f);
const DirectX::SimpleMath::Vector3 PlayScene::LEFT_WALL_POSITION	 = DirectX::SimpleMath::Vector3(-27.5f, 0.0f, 0.0f);
//	�㑤�̕ǂ̂����蔻��̑傫���E�ǂ̈ʒu
const DirectX::SimpleMath::Vector3 PlayScene::TOP_WALL_SCALE		 = DirectX::SimpleMath::Vector3(26.0f, 5.0f, 1.5f);
const DirectX::SimpleMath::Vector3 PlayScene::TOP_WALL_POSITION		 = DirectX::SimpleMath::Vector3(0.0f, 0.0f, -27.5f);
//	�J�����̕␳���W
const DirectX::SimpleMath::Vector3 PlayScene::CAMERA_OFFSET_POSITION = DirectX::SimpleMath::Vector3(0.0f, 20.0f, 10.0f);
//	�ˌ��G�̂������������̃m�b�N�o�b�N
const DirectX::SimpleMath::Vector3 PlayScene::TACLE_ENEMY_REACTION   = DirectX::SimpleMath::Vector3(2.4f, 12.5f, 5.4f);
//	���������G�t�F�N�g�̕\���ł��鐔
const int PlayScene::HIT_RENDER_RESTRICTION							 = 30;
//	�Ԑ���̐�����
const int PlayScene::FALLING_CHERRY_BLOSSOMS_GENERATED				 = 100;
//	�ǂ̑傫��
const int PlayScene::WALL_SCLAE										 = 6;
//	�G�t�F�N�g�̉摜�̑傫��
const float PlayScene::EFFECT_SIZE									 = 2.0f;
//	���̑��̓G�̃��A�N�V����
const float PlayScene::OTHER_ENEMY_REACTION							 = 1.4f;
//	�t�F�[�h�^�C��
const float PlayScene::FADE_TIME									 = 5.4f;
//	�I������
const float PlayScene::FINISHED_TIME								 = 2.8f;


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="game">�Q�[��</param>
/// <param name="screen">�X�N���[�����\�[�X</param>
PlayScene::PlayScene(Game* game, MyLib::ScreenResources* screen, int stagelevel)
	:
	m_game(game),
	m_screen(screen),
	m_worldLevel(stagelevel),
	m_isFinish(false),
	m_isFadeOutTask(false),
	m_isFirstOpen(false),
	m_IsFade(true),
	m_gameResultString(),
	m_fadeTime(0.0f),
	m_finishedTime(0.0f)
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayScene::~PlayScene()
{
	Finalize();
}

/// <summary>
/// ������
/// </summary>
void PlayScene::Initialize()
{
	CreateDeviceDependentResources();
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void PlayScene::Update(const DX::StepTimer& timer)
{
	//	�|�[�Y����
	if (NowPause())	return;
	//	�t�F�[�h����
	if (NowFade(timer))	return;
	//	�v���C���[�͐����Ă邩
	IsAlivePlayer();
	//	�v���C���[�̃A�j���[�V����
	m_player->PlayerAnimation(timer);
	//	�Ԃ̍X�V
	if (m_fallingCherryBlossoms.size() != 0) { for (const auto& flower : m_fallingCherryBlossoms)		flower->Update(timer); }
	//	�Q�[�����I���������H
	if(IsFinished(timer))	return;
	//	�J�������X�V����
	UpdateCamera(timer);
	//	�Q�[�����I�����Ă���Ȃ�߂�
	if (m_isFinish)	return;
	//	���x���A�b�v�̃J�[�h�̍X�V
	if (m_levelCard->Update(timer))	return;
	//	�|�X�g�G�t�F�N�g�̍X�V
	m_postEffect->Update(timer);
	//	�v���C���[�̃A�b�v�f�[�g
	m_player->Update(timer);
	//	�v���C���[��UI�X�V
	m_playerUI->Update(timer);
	//	�v���C���[�̗̑̓o�[UI�X�V
	m_playerBarUI->SetHPState(m_playerUI->GetState());
	//	�v���C���[�̗̑̓o�[UI�X�V
	m_playerBarUI->Update(timer);
	//	�X�V��������
	m_playScore->Update(timer);
	//	�o���l���X�V����
	m_expBar->Update(timer);
	//	�A�j���[�V�������͏������s��Ȃ�
	if (m_player->IsAnimation())	return;
	//	�G�̃}�l�[�W���[���X�V����
	m_enemyManager->Update(timer);
	//	�A�C�e���̃}�l�[�W���[���X�V����
	m_itemManager->Update(timer);
	//	�e�̃}�l�[�W���[���X�V����
	m_bulletManager->Update(timer);
	//	�Z�\�̔���̍X�V
	m_colisionObjects->UpdateAbility();
	//	�����蔻��̍X�V
	m_colisionObjects->UpdateColision();
	//	�~�j�}�b�v���X�V����
	UpdateMiniMap(timer);
	//	�`���[�g���A�������H && 	�v���C�V�[���̃E�F�[�u�̍X�V����
	if (m_isFirstOpen) { m_tutorialSystem->Update(timer); }	else { m_playSceneWave->Update(); }
	//	�q�b�g�G�t�F�N�g���X�V
	for (const auto& hitRender : m_hitRenders)				hitRender->Update();
	//	�q�b�g�G�t�F�N�g���X�V
	for (const auto& hitRender : m_hitBulletRenders)		hitRender->Update();
	//	�q�b�g�G�t�F�N�g���X�V
	for (const auto& particle : m_hitBulletPatricles)		particle->Update(timer);
	//	�X�e�[�W�̌^�ɃL���X�g
	StageSelectScene::CHOOSE_STAGE stage = static_cast<StageSelectScene::CHOOSE_STAGE>(GetWordLevel());
	//	�X�e�[�W4�ȊO�͏I�����������݂��Ă��邽�ߏ������s��
	if (stage != StageSelectScene::CHOOSE_STAGE::STAGE_4)
	{
		if (m_playSceneWave->IsFinalWave() && m_enemyManager->GetEnemy().size() == 0)
		{
			//	������
			m_gameResultString = WIN_STRING;
			//	�Ԑ���̍쐬
			for (size_t index = 0; index < FALLING_CHERRY_BLOSSOMS_GENERATED; index++)	m_fallingCherryBlossoms.push_back(std::make_unique<FallingCherryBlossoms>(m_player.get()));
			//	�Ԃ�����������
			for (const auto& flower : m_fallingCherryBlossoms)							flower->Initialize();
			//	���y���~�߂�
			AudioManager::GetInstance()->StopSoundEffect(L"PlayGameBgm01");
			//	�������y�̍Đ�
			AudioManager::GetInstance()->PlaySoundEffectSE(L"PlayWinBGM");
		}
	}
	//	�T�C�Y��0����Ȃ��Ȃ�
	if (m_gameResultString.size() != 0 && !m_isFirstOpen)
	{
		//	�Q�[���̏��s���v���C���[�ɋ�����
		m_player->WhyGameResult(m_gameResultString);
		//	�Q�[���I��
		m_isFinish = true;
	}
}

/// <summary>
/// �`��
/// </summary>
void PlayScene::Render()
{
	//	�R���e�L�X�g�̐錾
	auto context = m_screen->GetDeviceResources()->GetD3DDeviceContext();
	//�@�e�s���錾
	DirectX::SimpleMath::Matrix proj  = m_screen->GetProjectionMatrix();
	//�@�r���[���쐬
	DirectX::SimpleMath::Matrix view = DirectX::SimpleMath::Matrix::CreateLookAt
	(
		m_camera->GetEyePosition() + CAMERA_OFFSET_POSITION,
		m_camera->GetTargetPosition(),
		DirectX::SimpleMath::Vector3::UnitY
	);
	//	�r���[��ݒ�
	m_screen->SetViewMatrix(view);
	//	�ǂ�v�f���Ƃɕ`��
	for (const auto& wall : m_walls)	wall->Draw(view, proj);
	//	�v���C���[�`��
	m_player->Render(view, proj);
	//�@���̕`��
	m_floor_Model->Render(context, view, proj, WALL_SCLAE);
	//	�X�J�C�h�[���̕`��
	m_skyDome->Render(view, proj);	
	//	�e�̃}�l�[�W���[��`�悷��
	m_bulletManager->Render(view, proj);
	//	�A�C�e���̃}�l�[�W���[��`�悷��
	m_itemManager->Render(view, proj);
	//	�G�̃}�l�[�W����`�悷��
	m_enemyManager->Render(view, proj);
	//	�Ԃ�`�悷��
	if (m_fallingCherryBlossoms.size() != 0) { for (const auto& flower : m_fallingCherryBlossoms)	flower->Render(view, proj); }
	//	�A�j���[�V��������UI������
	if (m_player->IsDeathAnimation() || m_player->IsWinAnimation())	return;
	//	�G�t�F�N�g��`�悷��
	for (const auto& hitRender : m_hitRenders)			hitRender->Render(view, proj);
	//	�G�t�F�N�g��`�悷��
	for (const auto& hitRender : m_hitBulletRenders)	hitRender->RenderBillBoard(view, proj, m_camera->GetEyePosition(), DirectX::SimpleMath::Vector3(0.0f, 1.0f, 1.0f));
	//	�G�t�F�N�g��`�悷��
	for (const auto& particle : m_hitBulletPatricles)	particle->Render(view, proj, m_camera->GetEyePosition(), DirectX::SimpleMath::Vector3::Up);
	//	UI��`�悷��
	UIRender();


#ifdef _DEBUG

	std::wostringstream health;
	health << "HP : " << m_player->GetHealth() << " / " << m_player->GetMaxHealth();
	m_screen->RenderDebugFont(health.str().c_str(), DirectX::SimpleMath::Vector2(0.0f, 260.0f));
	std::wostringstream power;
	power << "POW : " << m_player->GetPower();
	m_screen->RenderDebugFont(power.str().c_str(), DirectX::SimpleMath::Vector2(0.0f, 300.0f));
	std::wostringstream position;
	position << "X : " << m_player->GetPosition().x << "Y : " << m_player->GetPosition().y << "Z : " << m_player->GetPosition().z;
	m_screen->RenderDebugFont(position.str().c_str(), DirectX::SimpleMath::Vector2(0.0f, 340.0f));

#endif // _DEBUG
}

/// <summary>
/// �I������
/// </summary>
void PlayScene::Finalize()
{
	m_player->Finalize();
	//
	m_enemyManager->Finalize();
	//	���y���~�߂�
	AudioManager::GetInstance()->StopSoundEffect(L"PlayGameBgm01");
}

/// <summary>
/// �f�o�C�X�ˑ��̃��\�[�X���쐬����
/// </summary>
void PlayScene::CreateDeviceDependentResources()
{
	//	�v���C���[�̌Ăяo��
	m_player = std::make_unique<Player>(&MyLib::ParamManager::GetInstane()->GetPlayerData());
	//	�v���C���[�̏�����
	m_player->Initialize();
	//	�v���C�V�[���̃E�F�[�u���쐬
	m_playSceneWave = std::make_unique<PlaySceneWave>(this);
	//	���������s��
	m_playSceneWave->Initialize();
	//	�G�̃}�l�[�W���[���쐬
	m_enemyManager = std::make_unique<EnemyManager>(this, m_player.get() , m_playSceneWave.get());
	//	�G�̃}�l�[�W���[������������
	m_enemyManager->Initialize();
	//	�A�C�e���̃}�l�[�W���[���쐬
	m_itemManager = std::make_unique<ItemManager>();
	//	�A�C�e���̃}�l�[�W���[������������
	m_itemManager->Initialize();
	//	�q�b�g�G�t�F�N�g�̐ݒ�
	for (size_t index = 0; index < HIT_RENDER_RESTRICTION; ++index)
		m_hitRenders.push_back(std::make_unique<HitRenderer>(MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"HitTextures"), EFFECT_SIZE));
	//	�q�b�g�G�t�F�N�g�̐ݒ�@�@
	for (size_t index = 0; index < HIT_RENDER_RESTRICTION; ++index)
		m_hitBulletRenders.push_back(
			std::make_unique<HitRenderer>(
				MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"HitBulletTextures"),
				EFFECT_SIZE
			)
		);
	//	�e�q�b�g���̃G�t�F�N�g�`�悷��
	for (size_t i = 0; i < HIT_RENDER_RESTRICTION; i++)	m_hitBulletPatricles.push_back(std::make_unique<BulletHitParticle>());
	//	�o���b�g�}�l�[�W���̍쐬
	m_bulletManager = std::make_unique<BulletManager>(m_enemyManager->GetEnemy());
	//	�o���b�g�}�l�[�W���̏�����
	m_bulletManager->Initialize();
	// �ŏ��̃r���[�s��̈ʒu�����߂�
	DirectX::SimpleMath::Vector3 eye(50.0f, 430.0f, 15.0f);
	DirectX::SimpleMath::Vector3 target(0.0f, 0.0f, 0.0f);
	DirectX::SimpleMath::Vector3 up(0.0f, 1.0f, 0.0f);
	//	�J�����̏�����
	m_camera = std::make_unique<Camera>(eye, target, up, m_player.get());
	//������
	m_camera->Initialize();
	//	�~�j�}�b�v�̍쐬
	m_miniMap = std::make_unique<MiniMap>(m_player.get(),m_itemManager->GetItem());
	//�����f���̍쐬
	m_floor_Model = std::make_unique<Floor_Model>();
	//	�X�J�C�h�[��
	m_skyDome = std::make_unique<SkyDome>(m_worldLevel);
	//	�v���C���[��UI���쐬
	m_playerUI = std::make_unique<PlayerUI>();
	//	�v���C���[�̃|�C���^�[��ݒ肷��
	m_playerUI->SetPlayer(m_player.get());
	//	����������
	m_playerUI->Initialize();
	//	�v���C���[�̗̑̓o�[UI���쐬
	m_playerBarUI = std::make_unique<PlayerHPBar>();
	//	�v���C���[�̃|�C���^�[��ݒ肷��
	m_playerBarUI->SetPlayer(m_player.get());
	//	�v���C�X�R�A
	m_playScore = std::make_unique<PlayeScore>();
	//	����������
	m_playScore->Initialize();
	//	����������
	m_playerBarUI->Initialize();
	//	�v���C���[�̃X�^�[�g�V�O�i�����쐬
	m_startSignal = std::make_unique<StartSignal>();
	//	�t�F�[�h�^�C���̃|�C���^���擾����
	m_startSignal->SetFadeTime(&m_fadeTime, FADE_TIME);
	//	����������
	m_startSignal->Initialize();
	//	�|�[�Y��ʂ̍쐬
	m_pause = std::make_unique<Pause>(this);
	//	����������
	m_pause->Initialize();
	//	��
	m_walls.push_back(WallFactory::CreateWall(RIGHT_WALL_POSITION, RIGHT_WALL_SCALE, DirectX::XMConvertToRadians(0.0f)));
	m_walls.push_back(WallFactory::CreateWall(UNDER_WALL_POSITION, UNDER_WALL_SCALE, DirectX::XMConvertToRadians(90.0f)));
	m_walls.push_back(WallFactory::CreateWall(LEFT_WALL_POSITION,  LEFT_WALL_SCALE,  DirectX::XMConvertToRadians(180.0f)));
	m_walls.push_back(WallFactory::CreateWall(TOP_WALL_POSITION,   TOP_WALL_SCALE,	 DirectX::XMConvertToRadians(270.0f)));
	//	�����蔻��̓o�^���s��
	m_colisionObjects = std::make_unique<ColisionObjects>(this, m_player.get(), &m_enemyManager->GetEnemy(), &m_bulletManager->GetBullet(), &m_walls, &m_itemManager->GetItem());
	//	�o���l�o�[���쐬����
	m_expBar = std::make_unique<PlayerExperiencePointUI>(m_player.get());
	//	���x���A�b�v�̍쐬
	m_levelCard = std::make_unique<LevelCard>(this, m_player.get());
	//	���x���A�b�v�̏���������
	m_levelCard->Initialize();
	//	�|�X�g�G�t�F�N�g�̍쐬
	m_postEffect = std::make_unique<PlayPostEffect>(m_playerBarUI.get(), m_player.get());
	//	����������
	m_postEffect->Initialize();
	//	�I�[�f�B�I�}�l�[�W���̉����Đ�
	AudioManager::GetInstance()->PlaySoundEffectBGM(L"PlayGameBgm01");
	//	�G�t�F�N�g�̓��ꏈ���̊J�n
	m_game->GetChangeEffect()->RequestChangeEffect(ChangeEffect::ChangeSceneType::Play, ChangeEffect::ChangeSceneFadeType::To);
	//	�}�E�X
	ShowMouse(true);
	//	�ꉞ����ɂ��Ă���
	m_gameResultString = {};
	//	�`���[�g���A�����쐬����
	m_tutorialSystem = std::make_unique<TutorialSystem>(this , m_enemyManager.get());
	//	����N����
	EdditPlayData playData;
	playData.OpenPlayData();
	m_isFirstOpen = playData.IsFirstOpen();
}

/// <summary>
/// �v���C���[���������Ă��邩�m�F
/// </summary>
/// <param name="timer"></param>
void PlayScene::IsAlivePlayer()
{
	//	����ł��Ȃ��Ȃ�A��
	if (!m_player->HealthCheck()) return;
	//	0����Ȃ��Ȃ�����Ă邩��A��
	if (m_gameResultString.size() != 0)	return;
	//	�Q�[���N���A���s
	m_gameResultString = LOSE_STRING;
	//	���y���~�߂�
	AudioManager::GetInstance()->StopSoundEffect(L"PlayGameBgm01");
	//	�s�k���y�̍Đ�
	AudioManager::GetInstance()->PlaySoundEffectSE(L"PlayLoseBGM");
}

/// <summary>
/// �Q�[�����I�������H
/// </summary>
/// <param name="timer">�^�C�}�[</param>
bool PlayScene::IsFinished(const DX::StepTimer& timer)
{
	//	�Q�[�����I����ĂȂ��Ȃ�߂�
	if (!m_isFinish)				return false;
	//	�A�j���[�V�������Ȃ�A��
	if (m_player->IsAnimation())	return false;
	//	�o�ߎ��Ԃ𑫂��@
	m_finishedTime += static_cast<float>(timer.GetElapsedSeconds());
	//	�o�ߎ��ԂŃV�[���ψ�
	if (m_finishedTime >= FINISHED_TIME)
	{
		//	�o�ߎ��Ԃ��~�߂�
		m_playScore->StopElapsedTimer();
		//	���U���g�V�[��
		m_game->GetSceneManager()->ChangeScene<ResultScene>(m_game, m_worldLevel);

		return true;
	}	

	return false;
}

/// <summary>
/// �J�������X�V����
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void PlayScene::UpdateCamera(const DX::StepTimer& timer)
{
	//	�J�������X�V����
	m_camera->Update(timer, m_IsFade);
	//	�G�t�F�N�g�̑ޏꏈ���̊J�n
	if (m_camera->IsDeathCamera() && !m_isFadeOutTask)
	{
		//	�^�X�N�����s���ꂽ
		m_isFadeOutTask = true;
		//	�ޏo�t�F�[�h���J�n����
		m_game->GetChangeEffect()->RequestChangeEffect(ChangeEffect::ChangeSceneType::Play, ChangeEffect::ChangeSceneFadeType::Out);
	}

	//	�_���[�W��ԂȂ�߂�
	if (m_player->IsDamege())	m_player->SetDamegeCondition(false);
}

/// <summary>
/// �t�F�[�h����
/// </summary>
/// <returns></returns>
bool PlayScene::NowFade(const DX::StepTimer& timer)
{
	//	�J���Ƀt�F�[�h������
	if (m_IsFade)
	{
		//	�J�����̈ʒu���ړ�����
		m_camera->Update(timer, m_IsFade);
		//	�o�ߎ��Ԃ𑫂��Ă���
		m_fadeTime += static_cast<float>(timer.GetElapsedSeconds());
		//	�X�^�[�g�̍��}���X�V����
		m_startSignal->Update(timer);
		//	���Ԍo�߂Ńt�F�[�h���Ԃ��I����
		if (m_fadeTime >= FADE_TIME)
		{
			m_IsFade = false;
			//	�o�ߎ��Ԃ�0�ɂ���
			MyLib::ElapsedTime::GetInstance()->RestElapsedTime();

			return false;
		}

		return true;
	}

	return false;
}

/// <summary>
/// �|�[�Y����
/// </summary>
/// <returns></returns>
bool PlayScene::NowPause()
{
	//	���͏������󂯎��
	auto input = MyLib::InputSystem::GetInstance()->GetKeyTracer();

	//	�|�[�Y���Ȃ�~�߂�
	if (m_pause->IsPause())
	{
		m_pause->Update();
		//	�|�[�Y���Ȃ炱��ȏ㏈�����s��Ȃ�
		return true;
	}

	//	Escape�������ꂽ��|�[�Y��
	if (input->pressed.Escape)
	{
		//	�|�[�Y�ɂ���
		m_pause->SetPause(true);
		//	����������
		m_pause->Initialize();
		//	se���Đ�����
		AudioManager::GetInstance()->PlaySoundEffectSE(L"Open_SE01");

		return true;
	}

	return false;
}

/// <summary>
/// �~�j�}�b�v���X�V����
/// </summary>
/// <param name="timer"></param>
void PlayScene::UpdateMiniMap(const DX::StepTimer& timer)
{
	for (const auto& enemy : m_enemyManager->GetEnemy())	m_miniMap->UpdateMap(timer, enemy.get());
}

/// <summary>
/// �G�t�F�N�g��`�悷�邵�傫����ς���
/// </summary>
/// <param name="position">���W</param>
void PlayScene::HitRnder(const DirectX::SimpleMath::Vector3& position)
{
	bool scaleFlag = false;

	for (const auto& hitRender : m_hitRenders)
	{
		//	�g�p���Ȃ玟��T��
		if (hitRender->IsUsed())	continue;

		//	�G�t�F�N�g��`��
		hitRender->HitEffect(position, scaleFlag);
		break;
	}
}

/// <summary>
/// �G�t�F�N�g�̂̐ݒ���I���ɂ���
/// </summary>
/// <param name="position">���W</param>
/// <param name="enemy">�G�̃|�C���^�[</param>
void PlayScene::HitRnder(const DirectX::SimpleMath::Vector3& position, const Enemy* enemy)
{
	bool scaleFlag = false;

	for (const auto& hitRender : m_hitRenders)
	{
		//	�g�p���Ȃ玟��T��
		if (hitRender->IsUsed())	continue;

		//	�{�X�̎������傫������
		if (enemy->GetType() == Object::ObjectType::BossEnemy) scaleFlag = true;

		//	�G�t�F�N�g��`��
		hitRender->HitEffect(position, scaleFlag);
		break;
	}
}

/// <summary>
/// �G�t�F�N�g�̂̐ݒ���I���ɂ���
/// </summary>
/// <param name="position">���W</param>
void PlayScene::HitBulletRnder(const DirectX::SimpleMath::Vector3& position)
{
	for (const auto& hitRender : m_hitBulletPatricles)
	{
		//	�g�p���Ȃ玟��T��
		if (hitRender->IsUsed())	continue;
		//	�G�t�F�N�g��`��
		hitRender->Hit(position);
		break;
	}
}

/// <summary>
/// �^�C�g���V�[���ɐ؂�ς���
/// </summary>
void PlayScene::ChangeSceneTitle()
{
	//	���U���g�V�[��
	m_game->GetSceneManager()->ChangeScene<TitleScene>(m_game);
}

/// <summary>
/// �}�E�X�J�[�\���������邩
/// </summary>
/// <param name="isShow">�����邩�ǂ���</param>
void PlayScene::ShowMouse(const bool& isShow)
{
	m_game->ShowMouseCursor(isShow);
}

/// <summary>
/// �`���[�g���A���I��
/// </summary>
void PlayScene::FinishTutorial()
{
	//	�G�t�F�N�g�̓��ꏈ���̊J�n
	m_game->GetChangeEffect()->RequestChangeEffect(ChangeEffect::ChangeSceneType::Play, ChangeEffect::ChangeSceneFadeType::To);
	//	����N���I��
	m_isFirstOpen = false;
}

/// <summary>
/// UI��`�悷��
/// </summary>
void PlayScene::UIRender()
{
	//	�`����J�n����
	m_screen->GetSpriteBatch()->Begin();
	//	�|�X�g�G�t�F�N�g�̕`��
	if(!m_isFinish)	m_postEffect->Draw();
	//	�E�F�[�u���̕`��
	m_playSceneWave->Draw();
	//	�v���C���[�̗̑̓o�[UI��`�悷��
	m_playerBarUI->Draw();
	//	�v���C���[��UI��`�悷��
	m_playerUI->Draw();
	//	�o���l�o�[��`�悷��
	m_expBar->Draw();
	//	�`�悷��
	m_playScore->Draw();
	//�t�F�[�h���Ȃ�`�悷��
	if (m_IsFade)	m_startSignal->Draw();
	//	�~�j�}�b�v�̕`�悷��
	m_miniMap->Draw();
	//	���x���A�b�v�̃J�[�h�̕`��
	m_levelCard->Draw();
	//	�|�[�Y���Ȃ�`�悷��
	if (m_pause->IsPause())	m_pause->Render();
	//	�`���[�g���A���̕`��
	m_tutorialSystem->Render();
	//	�`����I������
	m_screen->GetSpriteBatch()->End();
}