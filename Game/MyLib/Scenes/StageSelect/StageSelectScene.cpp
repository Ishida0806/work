//
//		File Name �F StageSelectScene.cpp
//		Production�F 2023/9/14
//		Author�@�@�F �Γc ����
// 
//		�X�e�[�W���Z���N�g������ꏊ
//
#include "pch.h"
#include "Game/Game.h"

////////////////////////Scene//////////////////////////////////
#include "Game/MyLib/Scenes/TitleScene/TitleScene.h"
#include "Game/MyLib/Scenes/StageSelect/StageSelectScene.h"
#include "Game/MyLib/Scenes/PlayScene/PlayScene.h"
#include "Game/MyLib/Scenes/ResultScene/ResultScene.h"
////////////////////////////////////////////////////////////////


//	�A�j���[�V���������s���Ȃ瑀����s��Ȃ�
const float StageSelectScene::COOL_TIME										= 0.55f;
//	�ʏ펞�̑傫��
const float StageSelectScene::BASE_SCALE									= 0.5f;
//	�t�F�[�h���̖ڕW�傫��
const float StageSelectScene::FADE_TARGET_SCALE								= 0.75f;
//	�摜�̊��o
const float StageSelectScene::DISTANCE										= 1000.0f;
//	���[�v�̑��x
const float StageSelectScene::LERP_SPEED									= 0.08f;
//	���[�v���̑傫���̑��x
const float StageSelectScene::LERP_SCALE_SPEED								= 0.1f;
//	�I���^�C��
const float StageSelectScene::FIN_TIME										= 1.6f;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="game">�Q�[��</param>
StageSelectScene::StageSelectScene(Game* game)
	:m_game(game),
	m_screen(nullptr),
	m_resorces(nullptr),
	m_escTexture(nullptr),
	m_stageSelectBackGroundStageFrameworkTexture(nullptr),
	m_stageState(CHOOSE_STAGE::STAGE_1),
	m_elapsedTime(0.0f),
	m_moveCoolTime(0.0f),
	m_preMove(false),
	m_isChanegeScene(false),
	m_isMoveDirection(MOVE_DIRECTION::CENTER)
{
	
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
StageSelectScene::~StageSelectScene()
{
	//	�X�e�[�W�Z���N�g�I�����ɉ��y���~�߂�
	AudioManager::GetInstance()->StopSoundEffect(L"PlayStageBGM");
}

/// <summary>
/// ����������
/// </summary>
void StageSelectScene::Initialize()
{
	//	�f�o�C�X�ˑ��̃��\�[�X�̏���������
	CreateDeviceDependentResources();
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="timer"></param>
void StageSelectScene::Update(const DX::StepTimer& timer)
{
	//	�X�e�[�W
	int stageNum = static_cast<int>(m_stageState);
	//	�o�ߎ��Ԃ𑫂�
	m_elapsedTime += static_cast<float>(timer.GetElapsedSeconds());
	//	�w�i�摜���X�V����
	m_stageBackGround->Update(static_cast<int>(m_stageState));
	// UI�B���X�V����
	UpdateUIs(timer);
	//	�L�[�������ꂽ��
	InputKey();
	//	�V�[���؂�ւ��m�F
	if (m_isChanegeScene)	return;
	//	�X�e�[�g�̏�Ԃ��m�F����
	CheckState();
	//	�h�A���X�V����
	UpdateDoor(timer);
	//	�v���C���[���X�V����
	UpdatePlayer();
	//	���̍X�V
	m_bird->Update(timer, stageNum);
	//	���z�̍X�V
	m_sun->Update(timer, stageNum);
	//	�G�����̍X�V
	for (auto& enemy2d : m_enemies2D)			enemy2d->Update(timer);
	//	�X�e�[�W�T�[�N���̍X�V
	for (const auto& circle : m_stageCircles)	circle->Update(timer, stageNum);
	//	�v���C���[���X�V����
	m_player2D->Update(timer);
	//	���}�l�[�W���̍X�V
	m_starManeger->Update(timer, stageNum);
	//	2�b�o�߂�����V�[���J��
	if (m_player2D->GetFinAnimationTime() >= FIN_TIME)
	{
		m_game->GetSceneManager()->ChangeScene<PlayScene>(m_game, m_screen, stageNum);
	}
}

/// <summary>
/// �`�揈��
/// </summary>
void StageSelectScene::Render()
{	
	//	�w�i�摜�̕`��
	m_stageBackGround->Draw();

	//	�`����n�߂�
	m_screen->GetSpriteBatch()->Begin();

	//	���}�l�[�W���̍X�V
	m_starManeger->Draw();

	//	���̕`��
	m_bird->Draw();

	//	���z�̕`��
	//m_sun->Draw();

	//	�G�̕`�悷��
	for (auto& enemy2d : m_enemies2D)	enemy2d->Draw();

	//	�w�i�摜�̕`��
	m_screen->GetSpriteBatch()->Draw
	(
		m_stageSelectBackGroundStageFrameworkTexture,
		DirectX::SimpleMath::Vector2(-10.0f, -5.0f)
	);
	//	�h�A��`�悷��
	RenderDoor();
	//	�L�[��`�悷��
	RenderKey();
	//	�v���C���[�̕`��
	m_player2D->Draw();
	//	�X�e�[�W�T�[�N���̕`��
	for (const auto& circle : m_stageCircles)		circle->Draw();
	//	�G�X�P�[�v�L�[�̕`��
	m_screen->GetSpriteBatch()->Draw
	(
		m_escTexture,
		DirectX::SimpleMath::Vector2::Zero
	);
	//	�`����I����
	m_screen->GetSpriteBatch()->End();
}

/// <summary>
/// �I������
/// </summary>
void StageSelectScene::Finalize()
{
}

/// <summary>
/// �f�o�C�X�ˑ��̃��\�[�X
/// </summary>
void StageSelectScene::CreateDeviceDependentResources()
{
	//	�X�N���[�����\�[�X
	m_screen		  = MyLib::ScreenResources::GetInstance();
	//	���\�[�V�[�Y
	m_resorces		  = MyLib::ResourcesData::GetInstance();
	//	�w�i�摜�̃t���[�����[�N
	m_stageSelectBackGroundStageFrameworkTexture = m_resorces->GatShaderResourceView(L"StageFramework");
	//	�G�X�P�[�v�L�[
	m_escTexture = m_resorces->GatShaderResourceView(L"EscapeUI");
	//	��ʂ̍����E����
	int s_height, s_weight;
	//	�X�N���[���T�C�Y���擾����
	m_screen->GetScreenSize(s_weight, s_height);
	//	��ʃT�C�Y�̔���
	DirectX::SimpleMath::Vector2 half_screen = DirectX::SimpleMath::Vector2(static_cast<float>(s_weight) / 2.0f, static_cast<float>(s_height) / 2.0f);
	//	�h�A�ɓn���v�f
	std::initializer_list<ID3D11ShaderResourceView*> doorResources
	{
		m_resorces->GatShaderResourceView(L"Door_Easy"),
		m_resorces->GatShaderResourceView(L"EasyFont"),
		m_resorces->GatShaderResourceView(L"Door_Normal"),
		m_resorces->GatShaderResourceView(L"NormalFont"),
		m_resorces->GatShaderResourceView(L"Door_Hard"),
		m_resorces->GatShaderResourceView(L"HardFont"),
		m_resorces->GatShaderResourceView(L"Door_Extra"),
		m_resorces->GatShaderResourceView(L"EndresFont"),
	};
	//	�����쐬����
	m_starManeger = std::make_unique<StarManager>(m_resorces->GatShaderResourceView(L"star"));
	m_starManeger->Initialize();
	int num = 0;
	//	2d�h�A�̍쐬
	for (auto itr = doorResources.begin(); itr != doorResources.end(); itr += 2)
	{
		m_doors2D.push_back
		(
			std::make_unique<Door2D>
			(
				*(itr),
				*(itr + 1),
				half_screen + (DirectX::SimpleMath::Vector2(DISTANCE * static_cast<float>(num),-30.0f)),
				DISTANCE
			)
		);
		num++;
	}
	//	�G��2D�摜���쐬����
	for (int i = 0; i < Enemy2D::GENERATION_ENEMY2D; i++)
	{
		if (i % 2 == 0)
		{
			m_enemies2D.push_back
			(
				std::make_unique<Enemy2D>
				(
					m_resorces->GatShaderResourceView(L"NormalEnemyTexure"),
					DirectX::SimpleMath::Vector2(Utility::CreateRandom(25.0f, 1255.0f), Utility::CreateRandom(25.0f, 680.0f))
				)
			);
		}
		else
		{
			m_enemies2D.push_back
			(
				std::make_unique<Enemy2D>
				(
					m_resorces->GatShaderResourceView(L"TackleEnemyTexure"),
					DirectX::SimpleMath::Vector2(Utility::CreateRandom(25.0f, 1255.0f), Utility::CreateRandom(25.0f, 680.0f))
				)
			);
		}
	}
	//	�ő�l���擾����
	int maxSize = static_cast<int>(KeyFont::FONT_TYPE::OverID);
	//	�L�[�t�H���g�̍쐬
	for (int index = 0; index < maxSize; index++)
	{
		//	���݂̔ԍ����t�H���g�^�C�v�^�ɕϊ�����
		KeyFont::FONT_TYPE nowType = static_cast<KeyFont::FONT_TYPE>(index);
		//	�v�f��ǉ�
		m_keys2D.push_back
		(
			std::make_unique<KeyFont>
			(
				nowType,
				DirectX::SimpleMath::Vector2(350.0f + 580.0f * index, 420.0f)
			)
		);
		//	����������
		m_keys2D[index]->Initialize();
	}
	//	�X�e�[�W�̍ő吔
	size_t stageMax = static_cast<size_t>(CHOOSE_STAGE::OverID);
	//	�X�e�[�W�T�[�N���̍쐬
	for (int i = 0; i < stageMax; i++) 
	{
		m_stageCircles.push_back(std::make_unique<StageCircle>
			(
				MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"Stage_Circle"),
				DirectX::SimpleMath::Vector2(525.0f +( 60.0f * i), 660.0f ),
				i
			)
		);
	}
	//	��
	m_bird = std::make_unique<Bird>();
	//	����������
	m_bird->Initialize();
	//	���z
	m_sun = std::make_unique<Sun>();
	//	����������
	m_sun->Initialize();
	//	�X�e�[�W�̔w�i
	m_stageBackGround = std::make_unique<StageBackGround>(m_resorces->GatShaderResourceView(L"StageSelect_BackGround"), static_cast<int>(CHOOSE_STAGE::OverID));
	//	����������
	m_stageBackGround->Initialize();
	//	�v���C���[�̈ʒu������������
	m_player2D = std::make_unique<Player2D>(m_resorces->GatShaderResourceView(L"player2d"), DirectX::SimpleMath::Vector2(350.0f, static_cast<float>(s_height) / 1.5f));
	//	���������s��
	m_player2D->Initialize();
	//	�I�[�f�B�I�}�l�[�W���̉����Đ�
	AudioManager::GetInstance()->PlaySoundEffectBGM(L"PlayStageBGM");
	//	�G�t�F�N�g�̓��ꏈ���̊J�n
	m_game->GetChangeEffect()->RequestChangeEffect(ChangeEffect::ChangeSceneType::Select, ChangeEffect::ChangeSceneFadeType::To);
}

/// <summary>
/// UI�B���X�V����
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void StageSelectScene::UpdateUIs(const DX::StepTimer& timer)
{
	//	�v���C���[�̃A�j���[�V������Ԃ��A�C�h�����O�ȊO�Ȃ�A��
	if (m_player2D->GetState() != Player2D::PLAYER_STATE::IDLE) return;

	//	�ړ����Ȃ�A��
	if (m_isMoveDirection != MOVE_DIRECTION::CENTER)		return;

	//	�摜���g���������
	m_doorScale.x = 0.35f * (2.0f + cosf(m_elapsedTime * 2.5f));
	m_doorScale.y = 0.35f * (2.0f + cosf(m_elapsedTime * 2.5f));

	//	������x�̑傫���܂ł�������␳��������
	if (m_doorScale.x >= 0.70f)
	{
		//	�N�����v��������
		m_doorScale.x = Utility::Clamp(m_doorScale.x, 0.0f, 0.70f);
		//	�o�ߎ��Ԃ������i�߂�
		m_elapsedTime += 0.071f;
	}
	if (m_doorScale.y >= 0.70f)
	{
		//	�N�����v��������
		m_doorScale.y = Utility::Clamp(m_doorScale.y, 0.0f, 0.70f);
		//	�o�ߎ��Ԃ������i�߂�
		m_elapsedTime += 0.071f;
	}

	//	�L�[�������X�V����
	for (const auto& key2D : m_keys2D)
		key2D->Update(timer);
}

/// <summary>
/// �L�[�������ꂽ��
/// </summary>
void StageSelectScene::InputKey()
{
	//	�v���C���[�̃A�j���[�V������Ԃ��A�C�h�����O�ȊO�Ȃ�A��
	if (m_player2D->GetState() != Player2D::PLAYER_STATE::IDLE) return;

	//	�ړ����Ȃ�A��
	if(m_isMoveDirection	  != MOVE_DIRECTION::CENTER)		return;

	//	�L�[�{�[�h�̏��ƃ}�E�X�̓��͏����󂯎��
	auto input = MyLib::InputSystem::GetInstance()->GetKeyTracer();
	auto mouse = MyLib::InputSystem::GetInstance()->GetStateTracker();
	//	D�L�[����� && �ړ�������Ȃ��Ȃ瑀����󂯎��
	if (input->pressed.D && m_stageState != CHOOSE_STAGE::STAGE_4)
	{
		m_elapsedTime = 0.0f;
		m_doorScale.x = BASE_SCALE;
		m_doorScale.y = BASE_SCALE;
		m_isMoveDirection = MOVE_DIRECTION::RIGHT;
		for (const auto& door2d : m_doors2D)
			door2d->TargetPosDecision(static_cast<int>(m_isMoveDirection));
		//	�����Đ�����
		AudioManager::GetInstance()->PlaySoundEffectSE(L"PlaySE02_MoveTitle");
	}
	//	A�L�[����� && �ړ�������Ȃ��Ȃ瑀����󂯎��
	if (input->pressed.A && m_stageState != CHOOSE_STAGE::STAGE_1)
	{
		m_elapsedTime = 0.0f;
		m_doorScale.x = BASE_SCALE;
		m_doorScale.y = BASE_SCALE;
		m_isMoveDirection = MOVE_DIRECTION::LEFT;
		for (const auto& door2d : m_doors2D)
			door2d->TargetPosDecision(static_cast<int>(m_isMoveDirection));
		//	�����Đ�����
		AudioManager::GetInstance()->PlaySoundEffectSE(L"PlaySE02_MoveTitle");
	}
	//	�V�[����؂�ւ���
	if (input->pressed.Escape)
	{
		//	�V�[����؂�ւ���
		m_game->GetSceneManager()->ChangeScene<TitleScene>(m_game);
		//	SE���Đ�����
		AudioManager::GetInstance()->PlaySoundEffectSE(L"Close_SE01");
		//	�t���O���s��
		m_isChanegeScene = true;
	}

	//	�X�y�[�X����� || �}�E�X���͂Ł@&& �ړ�������Ȃ��Ȃ瑀����󂯎�� && �v���C���[���A�j���[�V����������Ȃ��Ȃ�
	if (input->pressed.Space  ||	
		mouse->leftButton == mouse->PRESSED)
	{
		//	�A�j���[�V�������J�n����
		m_player2D->BeginChangeSceneAnimation();
		//	SE���Đ�����
		AudioManager::GetInstance()->PlaySoundEffectSE(L"PlaySE01_Accept");
	}
}

/// <summary>
/// �v���C���[�̏����X�V����
/// </summary>
void StageSelectScene::UpdatePlayer()
{
	//	�v���C���[�̃A�j���[�V�����󋵂��A�C�h�����O�Ȃ�A��
	if (m_player2D->GetState() == Player2D::PLAYER_STATE::IDLE)	return;
	
	if (m_player2D->GetState() == Player2D::PLAYER_STATE::FIRST)
	{
		//	�傫��������������
		m_doorScale.x = Utility::Lerp(m_doorScale.x, BASE_SCALE / 2.0f, LERP_SCALE_SPEED);
		m_doorScale.y = Utility::Lerp(m_doorScale.y, BASE_SCALE / 2.0f, LERP_SCALE_SPEED);
	}
	if (m_player2D->GetState() == Player2D::PLAYER_STATE::SECOND)
	{
		//	�傫����傫������
		m_doorScale.x = Utility::Lerp(m_doorScale.x, FADE_TARGET_SCALE, LERP_SCALE_SPEED);
		m_doorScale.y = Utility::Lerp(m_doorScale.y, FADE_TARGET_SCALE, LERP_SCALE_SPEED);
	}
}

/// <summary>
/// �h�A�̍X�V���󂯎������X�V���s��
/// </summary>
void StageSelectScene::UpdateDoor(const DX::StepTimer& timer)
{
	//	���ݑI�𒆂̃X�e�[�W�ԍ�
	int stageNum = static_cast<int>(m_stageState);
	//	�Z���N�g�t���O
	bool selectFLag = false;
	//	
	for (size_t i = 0; i < m_doors2D.size(); i++)
	{
		if (i == stageNum)
		{
			//	���̔ԍ����I�����ꂽ�I
			selectFLag = true;
			m_doors2D[i]->Update(selectFLag);
		}
		else
		{
			//	���̔ԍ����I������Ȃ�����
			m_doors2D[i]->Update(selectFLag);
		}
	}

	//	�A�j���[�V�������s���Ȃ烉�[�v���s��
	if (m_isMoveDirection == MOVE_DIRECTION::RIGHT)
	{
		//	�o�ߎ��Ԃ𑫂�
		m_moveCoolTime += static_cast<float>(timer.GetElapsedSeconds());
		//	�ړ����I�������l������������
		if (m_moveCoolTime >= COOL_TIME)
		{
			m_isMoveDirection = MOVE_DIRECTION::CENTER;
			m_preMove = false;
			m_moveCoolTime = 0.0f;
			m_elapsedTime = 0.0f;
			m_doorScale.x = BASE_SCALE;
			m_doorScale.y = BASE_SCALE;
		}
	}
	//	�A�j���[�V�������s���Ȃ烉�[�v���s��
	if (m_isMoveDirection == MOVE_DIRECTION::LEFT)
	{
		//	�o�ߎ��Ԃ𑫂�
		m_moveCoolTime += static_cast<float>(timer.GetElapsedSeconds());
		//	�ړ����I�������l������������
		if (m_moveCoolTime >= COOL_TIME)
		{
			m_isMoveDirection = MOVE_DIRECTION::CENTER;
			m_preMove		= false;
			m_moveCoolTime	= 0.0f;
			m_elapsedTime = 0.0f;
			m_doorScale.x = BASE_SCALE;
			m_doorScale.y = BASE_SCALE;
		}
	}
}

/// <summary>
/// ���݂̃X�e�[�g�ɑ΂��ď������s��
/// </summary>
void StageSelectScene::CheckState()
{
	if (m_isMoveDirection == MOVE_DIRECTION::CENTER )	return;

	if (m_preMove == true)							return;

	int nowStageNum  = static_cast<int>(m_stageState);
	int nextStageNum = static_cast<int>(m_stageState);

	int maxStageNum = static_cast<int>(CHOOSE_STAGE::OverID);

	//	���������ꂽ��
	if (m_isMoveDirection == MOVE_DIRECTION::RIGHT)
	{
		//	�X�e�[�W�ԍ����C���N�������g
		nextStageNum++;

		if (nextStageNum < maxStageNum)
			nowStageNum++;
	}
	else
	{
		//	�X�e�[�W�ԍ����f�N�������g
		nextStageNum--;

		//	�X�e�[�W�ԍ���0���傫�Ȃ�
		if (nextStageNum >= 0)
			nowStageNum--;
	}

	m_stageState = static_cast<CHOOSE_STAGE>(nowStageNum);
	m_preMove = true;
}

/// <summary>
/// �L�[��`�悷��
/// </summary>
void StageSelectScene::RenderKey()
{
	//	�v���C���[�̃A�j���[�V������Ԃ��A�C�h�����O�ȊO�Ȃ�A��
	if (m_player2D->GetState() != Player2D::PLAYER_STATE::IDLE)	return;

	//	�ő�l
	int size = static_cast<int>(KeyFont::FONT_TYPE::OverID);
	//	�E��
	int right = static_cast<int>(KeyFont::FONT_TYPE::RIGHT);
	//	����
	int left = static_cast<int>(KeyFont::FONT_TYPE::LEFT);

	for (int i = 0; i < size; i++)
	{
		//	���݂̔ԍ�
		int nowSize = static_cast<int>(m_keys2D[i]->GetType());
		//	�E���̒l�Ȃ�\��
		if (nowSize == left)
		{
			if (m_stageState != CHOOSE_STAGE::STAGE_1 && m_isMoveDirection == MOVE_DIRECTION::CENTER)
			{
				m_keys2D[nowSize]->Draw();
			}
		}
		//	�����̒l�Ȃ�\��
		else if(nowSize == right)
		{
			if (m_stageState != CHOOSE_STAGE::STAGE_4 && m_isMoveDirection == MOVE_DIRECTION::CENTER)
			{
				m_keys2D[nowSize]->Draw();
			}
		}
	}
}

/// <summary>
/// �h�A��`�悷��
/// </summary>
void StageSelectScene::RenderDoor()
{
	unsigned int stageState = static_cast<int>(m_stageState);

	for (size_t i = 0; i < m_doors2D.size(); i++)
	{
		if (i == stageState)
		{
			m_doors2D[i]->Draw(m_doorScale);
		}
		else
		{
			m_doors2D[i]->Draw(DirectX::SimpleMath::Vector2(BASE_SCALE, BASE_SCALE));
		}
	}
}