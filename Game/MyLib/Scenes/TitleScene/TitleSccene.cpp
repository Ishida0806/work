//
//		File Name �F TitleScene.cpp
//		Production�F 2023/9/14
//		Author�@�@�F �Γc ����
//
#include "pch.h"
#include "Game/Game.h"

////////////////////////Scene//////////////////////////////////
#include "TitleScene.h"
#include "Game/MyLib/Scenes/StageSelect/StageSelectScene.h"
#include "Game/MyLib/Scenes/PlayScene/PlayScene.h"
#include "Game/MyLib/Scenes/ResultScene/ResultScene.h"
////////////////////////////////////////////////////////////////

//  �^�C�g���̃t�F�[�h����
const float TitleScene::TITLE_FADE_ARRIVE_TIME = 1.6f;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="game"></param>
TitleScene::TitleScene(Game* game)
	:m_game(game),
	m_uiAlfa(0.0f),
	m_elapsedTime(0.0f),
	m_fadeTime(0.0f),
	m_finTime(0.0f),
	m_state(STATE::IDLE),
	m_backGroundTexture(nullptr),
	m_uiTexture(nullptr),
	m_resources(nullptr),
	m_screen(nullptr),
	m_fadeStart(false),
	m_isFin(false),
	m_alfaValue(false)
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
TitleScene::~TitleScene()
{

}

/// <summary>
/// ����������
/// </summary>
void TitleScene::Initialize()
{		
	CreateDeviceDependentResources();
}	

/// <summary>
/// �X�V����
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void TitleScene::Update(const DX::StepTimer& timer)
{
	//	�o�ߎ��Ԃ𑫂�
	m_elapsedTime += static_cast<float>(timer.GetElapsedSeconds());
	//	int�^�ɂ���
	int state = static_cast<int>(m_state);

	//	�|�[�Y���͏������s��Ȃ�
	if (m_config->IsPause())
	{
		m_config->Update();
		return;
	}

	//	�^�C�g�����S�̍X�V
	m_titleLogo->Update(state);
	//	�e�M�A�̍X�V
	for (const auto& gear : m_gears)				gear->Update(state);
	//	�^�C�g�������̍X�V
	for (const auto& titleUI : m_titleStringUIs)	titleUI->Update(state);

	//	�e�X�e�[�g���X�V����
	UpdateState(timer);

	//	�I���R�}���h�����͂��ꂽ����s����
	if (!m_isFin)	return;
	
	//	�o�ߎ��Ԃ𑫂�
	m_finTime += static_cast<float>(timer.GetElapsedSeconds());

	//	����ʂ܂ł�������s����
	if (m_finTime >= 0.5f)
	{
		PostQuitMessage(0);
	}
}

/// <summary>
/// �`�揈��
/// </summary>
void TitleScene::Render()
{
	//	�`����J�n����
	m_screen->GetSpriteBatch()->Begin();

	//	���̔w�i�̉摜��`�悷��
	m_screen->GetSpriteBatch()->Draw(m_backGroundTexture, m_backPos);
	//	�^�C�g�����S�̕`��
	m_titleLogo->Draw();

	// UI��`�悷��
	RenderUI();
	//	�e�M�A�̕`��
	for (const auto& gear	 : m_gears)				gear->Draw();
	//	�^�C�g�������̕`��
	for (const auto& titleUI : m_titleStringUIs)	titleUI->Draw();

	//	�|�[�Y��ʂ�`�悷��
	if (m_config->IsPause())
		m_config->Render();

	//	�`����I������
	m_screen->GetSpriteBatch()->End();
}

/// <summary>
/// �I������
/// </summary>
void TitleScene::Finalize()
{
	
}

/// <summary>
/// �e�X�e�[�g���X�V����
/// </summary>
void TitleScene::UpdateState(const DX::StepTimer& timer)
{
	//	�X�e�[�g�̏�Ԃɂ�菈����ς���
	switch (m_state)
	{
		//	�������
	case TitleScene::STATE::IDLE:	UpdateIdle();		break;
	//	�v���C�V�[���ɍs��
	case TitleScene::STATE::PLAY:	UpdatePlay(timer);	break;
	//	�R���t�B�O
	case TitleScene::STATE::CONFIG:	UpdateConfig();		break;
	//	�Q�[�����I������
	case TitleScene::STATE::END:	UpdateEnd();		break;
	//	�m�[��
	case TitleScene::STATE::NONE:						break;
	default:											break;
	}
}

/// <summary>
/// �X�V����
/// </summary>
void TitleScene::UpdateIdle()
{
	//	�L�[�{�[�h�̏��ƃ}�E�X�̓��͏����󂯎��
	auto input = MyLib::InputSystem::GetInstance()->GetKeyTracer();
	auto mouse = MyLib::InputSystem::GetInstance()->GetStateTracker();

	//	�ʒu������������
	m_uiPos.y += 0.1f * sinf(m_elapsedTime);
	//	SPACE�L�[����������̂𑣂����߂ɃA���t�@�l��ς���
	m_uiAlfa = sinf(m_elapsedTime * 2.0f) + 1.0f;
	//	�v���C�X�e�[�g�֑J�ڂ���
	if (input->pressed.Space || mouse->leftButton == mouse->PRESSED)
	{
		//	�����Đ�����
		AudioManager::GetInstance()->PlaySoundEffectSE(L"PlaySE01_Accept");
		//	�A���t�@�l��������
		m_uiAlfa = 0.0f;
		//	�v���C�X�e�[�g�ɍs��
		m_state = STATE::PLAY;
	}
}

/// <summary>
/// �v���C�X�e�[�g���X�V����
/// </summary>
void TitleScene::UpdatePlay(const DX::StepTimer& timer)
{
	//	�L�[�{�[�h�̏��ƃ}�E�X�̓��͏����󂯎��
	auto input = MyLib::InputSystem::GetInstance()->GetKeyTracer();
	auto mouse = MyLib::InputSystem::GetInstance()->GetStateTracker();

	//	�X�y�[�X�L�[���}�E�X�̍��N���b�N�ŃV�[���J�ڂ���
	if (input->pressed.W && !m_fadeStart)
	{
		//	�I�[�f�B�I�}�l�[�W���̉����Đ�
		AudioManager::GetInstance()->PlaySoundEffectSE(L"PlaySE02_MoveTitle");
		m_state = STATE::END;
	}

	if (input->pressed.S && !m_fadeStart)
	{
		//	�I�[�f�B�I�}�l�[�W���̉����Đ�
		AudioManager::GetInstance()->PlaySoundEffectSE(L"PlaySE02_MoveTitle");
		m_state = STATE::CONFIG;
	}

	//	�X�y�[�X�L�[���}�E�X�̍��N���b�N�ŃV�[���J�ڂ���
	if (input->pressed.Space && !m_fadeStart || mouse->leftButton == mouse->PRESSED && !m_fadeStart)
	{
		//	�I�[�f�B�I�}�l�[�W���̉����Đ�
		AudioManager::GetInstance()->PlaySoundEffectSE(L"PlaySE01_Accept");
		//	�t�F�[�h���X�^�[�g	
		m_fadeStart = true;
		//	�G�t�F�N�g�̑ޏo�����̊J�n
		m_game->GetChangeEffect()->RequestChangeEffect(ChangeEffect::ChangeSceneType::Title, ChangeEffect::ChangeSceneFadeType::Out);
	}

	//	�V�[���J�ڂ��J�n���ꂽ�珈�����s��
	if (!m_fadeStart)	return;
	
	//	�o�ߎ��Ԃ𑫂�
	m_fadeTime += static_cast<float>(timer.GetElapsedSeconds());

	if (m_fadeTime >= TITLE_FADE_ARRIVE_TIME)
	{
		//	BGM�����y���~�߂�
		AudioManager::GetInstance()->StopSoundEffect(L"PlayTitleBGM");
		//	�X�e�[�W�Z���N�g�ւ���
		m_game->GetSceneManager()->ChangeScene<StageSelectScene>(m_game);
	}	
}

/// <summary>
/// �R���t�B�O�X�e�[�g���X�V����
/// </summary>
void TitleScene::UpdateConfig()
{
	//	�L�[�{�[�h�̏��ƃ}�E�X�̓��͏����󂯎��
	auto input = MyLib::InputSystem::GetInstance()->GetKeyTracer();
	auto mouse = MyLib::InputSystem::GetInstance()->GetStateTracker();

	//	�X�y�[�X�L�[���}�E�X�̍��N���b�N�ŃV�[���J�ڂ���
	if (input->pressed.W)
	{
		//	�I�[�f�B�I�}�l�[�W���̉����Đ�
		AudioManager::GetInstance()->PlaySoundEffectSE(L"PlaySE02_MoveTitle");
		m_state = STATE::PLAY;
	}

	if (input->pressed.S)
	{
		//	�I�[�f�B�I�}�l�[�W���̉����Đ�
		AudioManager::GetInstance()->PlaySoundEffectSE(L"PlaySE02_MoveTitle");
		m_state = STATE::END;
	}

	//	�X�y�[�X�L�[���}�E�X�̍��N���b�N�ŃR���t�B�O���J��
	if (input->pressed.Space || mouse->leftButton == mouse->PRESSED)
	{
		m_config->SetPause(true);
		m_config->Initialize();
		//	se���Đ�����
		AudioManager::GetInstance()->PlaySoundEffectSE(L"Open_SE01");
	}
}

/// <summary>
///	�G���h�X�e�[�g���X�V����
/// </summary>
void TitleScene::UpdateEnd()
{
	//	�L�[�{�[�h�̏��ƃ}�E�X�̓��͏����󂯎��
	auto input = MyLib::InputSystem::GetInstance()->GetKeyTracer();
	auto mouse = MyLib::InputSystem::GetInstance()->GetStateTracker();

	//	�X�e�[�g����ړ�����
	if (input->pressed.W )
	{
		AudioManager::GetInstance()->PlaySoundEffectSE(L"PlaySE02_MoveTitle");
		m_state = STATE::CONFIG;
	}
	//	�X�e�[�g����ړ�����
	if (input->pressed.S)
	{
		AudioManager::GetInstance()->PlaySoundEffectSE(L"PlaySE02_MoveTitle");
		m_state = STATE::PLAY;
	}

	//	�X�y�[�X�L�[���}�E�X�̍��N���b�N�ŃQ�[���I��
	if (input->pressed.Space || mouse->leftButton == mouse->PRESSED)
	{
		//	�I�[�f�B�I�}�l�[�W���̉����Đ�
		AudioManager::GetInstance()->PlaySoundEffectSE(L"PlaySE01_Accept");

		m_isFin = true;
	}
}

/// <summary>
/// UI��`�悷��
/// </summary>
void TitleScene::RenderUI()
{
	//	�A�C�h�����O��ԈȊO�͋A��
	if (m_state != STATE::IDLE)	return;


	//	UI�̉摜��`�悷��
	m_screen->GetSpriteBatch()->Draw
	(
		m_uiTexture,
		m_uiPos,
		nullptr,
		DirectX::SimpleMath::Color(m_uiAlfa, m_uiAlfa, m_uiAlfa, m_uiAlfa),
		0.0f,
		DirectX::SimpleMath::Vector2(156.5f, 40.5f),
		DirectX::SimpleMath::Vector2(1.2f, 1.2f)
	);
}

/// <summary>
/// �f�o�C�X�ˑ��̃��\�[�X�̏�����
/// </summary>
void TitleScene::CreateDeviceDependentResources()
{
	//	�X�N���[�����\�[�X���擾����
	m_screen = MyLib::ScreenResources::GetInstance();
	//	���\�[�V�[�Y�f�[�^���擾����
	m_resources = MyLib::ResourcesData::GetInstance();
	//	�|�[�Y��ʂ��쐬
	m_config = std::make_unique<Config>();

	m_uiTexture = m_resources->GatShaderResourceView(L"title_UI"),

	//	�w�i�̃e�N�X�`�����擾����
	m_backGroundTexture = m_resources->GatShaderResourceView(L"title_back");
	//	�^�C�g�����S�̍쐬
	m_titleLogo = std::make_unique<TitleLogo>
	(
		m_resources->GatShaderResourceView(L"titleLogo"),
		DirectX::SimpleMath::Vector2(580.0f, 300.0f),
		DirectX::SimpleMath::Vector2(500.0f, 100.0f)
	);

	//	�ő�̐�
	int maxDirection = static_cast<int>(Gear::Direction::OverID);
	//	�M�A���쐬
	for (int i = 0; i < maxDirection; i++)
	{
		m_gears.push_back
		(
			std::make_unique<Gear>
			(
				m_resources->GatShaderResourceView(L"gear"),
				DirectX::SimpleMath::Vector2(1250.0f - (1230.0f * i), 800.0f),
				DirectX::SimpleMath::Vector2(361.5f, 358.0f),
				static_cast<Gear::Direction>(i)
			)
		);
	}

	//	�h�A�ɓn���v�f
	std::initializer_list<ID3D11ShaderResourceView*> stringUIResources
	{
		m_resources->GatShaderResourceView(L"title_UI_PlayGame_Off"),
		m_resources->GatShaderResourceView(L"title_UI_PlayGame"),
		m_resources->GatShaderResourceView(L"title_UI_Config_Off"),
		m_resources->GatShaderResourceView(L"title_UI_Config"),
		m_resources->GatShaderResourceView(L"title_UI_EndGame_Off"),
		m_resources->GatShaderResourceView(L"title_UI_EndGame")
	};

	//	�ŏ��̔ԍ�
	int index = static_cast<int>(TitleScene::STATE::PLAY);
	//	���炷���߂̒l
	int range = 0;

	for (auto itr = stringUIResources.begin(); itr != stringUIResources.end(); itr += 2)
	{
		m_titleStringUIs.push_back
		(
			std::make_unique<TitleStringUI>
			(
				*(itr),
				*(itr + 1),
				DirectX::SimpleMath::Vector2(640.0f, 550.0f + (40.0f * range)),
				index
			)
		);

		range++;
		index++;
	}

	//	UI�̉摜��������
	m_uiPos		= DirectX::SimpleMath::Vector2(640.0f, 600.0f);
	//	�t�F�C�h�t���O�̏�����
	m_fadeStart = false;

	m_alfaValue = false;
	//	�X�e�[�g���A�C�h�����[�h��
	m_state = STATE::IDLE;
	//	�A���t�@�l������������
	m_uiAlfa = 1.0f;
	//	�I�[�f�B�I�}�l�[�W���̉����Đ�
	AudioManager::GetInstance()->PlaySoundEffectBGM(L"PlayTitleBGM");
}
