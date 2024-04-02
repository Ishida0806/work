//
//		File Name �F ResultScene.cpp
//		Production�F 2023/9/14
//		Author�@�@�F �Γc ����
// 
//		���U���g�V�[��
//
#include "pch.h"

#include "Game/Game.h"
////////////////////////Scene//////////////////////////////////
#include "Game/MyLib/Scenes/TitleScene/TitleScene.h"
#include "Game/MyLib/Scenes/StageSelect/StageSelectScene.h"
#include "Game/MyLib/Scenes/PlayScene/PlayScene.h"
#include "Game/MyLib/Scenes/ResultScene/ResultScene.h"
////////////////////////////////////////////////////////////////


//	�ȒP�ȓ�Փx�̉��Z����
const float ResultScene::EASY_ADDITION	 = 1.0f;
//	�ʏ�̓�Փx�̉��Z����
const float ResultScene::NORMAL_ADDITION = 1.2f;
//	�����Փx�̉��Z����
const float ResultScene::HARD_ADDITION	 = 1.4f;
//	�G���h���X��Փx�̉��Z����
const float ResultScene::ENDRES_ADDITION = 1.5f;
//	PUSHUI�̍��W
const DirectX::SimpleMath::Vector2 ResultScene::PUSH_SPACE_POSITION		   = DirectX::SimpleMath::Vector2(665.0f, 640.0f);
//	PUSHUI�̐^�񒆍��W
const DirectX::SimpleMath::Vector2 ResultScene::PUSH_SPACE_ORIGIN_POSITION = DirectX::SimpleMath::Vector2(175.5, 53.5f);


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="game"></param>
/// <param name="score"></param>
ResultScene::ResultScene(Game* game, int stageSelect)
	:m_game(game),
	m_stageNum(stageSelect),
	m_screen(nullptr),
	m_resorces(nullptr),
	m_backGroundTexture(nullptr),
	m_tableBackGroundTexture(nullptr),
	m_judScore(false),
	m_isFinished(false),
	m_finishedTime(0.0f)
{
	
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ResultScene::~ResultScene()
{
	AudioManager::GetInstance()->StopSoundEffect(L"ResultBGM");
}

/// <summary>
/// ����������
/// </summary>
void ResultScene::Initialize()
{
	//	�f�o�C�X�ˑ��̃��\�[�X
	CreateDeviceDependentResources();
}

/// <summary>
/// ��i����
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void ResultScene::Update(const DX::StepTimer& timer)
{
	auto input = MyLib::InputSystem::GetInstance()->GetKeyTracer();
	auto mouse = MyLib::InputSystem::GetInstance()->GetStateTracker();

	if (!m_resultBackGround->Update())	return;

	//	�X�R�A�X�V���I�������TRUE��
	if (m_scoreOutPut->Update())
	{
		//	����̂�SE���Đ�����
		if (!m_judScore)
		{
			m_judScore = true;
		}
		//	���q���X�V
		m_pushSeal->Update();
		//	�X�R�A�̕]���l���X�V����
		m_valucationScore->Update(m_pushSeal->IsTop());
		//	UI�L�[���X�V����
		m_pushSpase->Update();
	}

	if (!m_scoreOutPut->Update())	return;

	//	�A�N�V�������N������������𖞂���
	if (input->pressed.Space && !m_isFinished ||
		mouse->leftButton && !m_isFinished)
	{
		//	�I�������𖞂�����
		m_isFinished = true;
		//	����炷
		AudioManager::GetInstance()->PlaySoundEffectSE(L"PlaySE01_Accept");
		//	�G�t�F�N�g�̑ޏꏈ���̊J�n
		m_game->GetChangeEffect()->RequestChangeEffect(ChangeEffect::ChangeSceneType::Result, ChangeEffect::ChangeSceneFadeType::Out);
	}

	//	�I�������𖞂����Ă��Ȃ��Ȃ�A��
	if (!m_isFinished)	return;

	m_finishedTime += static_cast<float>(timer.GetElapsedSeconds());

	if (m_finishedTime > 3.2f)
	{
		//	�V�[����؂�ւ���
		m_game->GetSceneManager()->ChangeScene<TitleScene>(m_game);
	}
}

/// <summary>
/// �`�揈��
/// </summary>
void ResultScene::Render()
{
	//	�X�v���C�g�o�b�`
	DirectX::SpriteBatch* spriteBath = m_screen->GetSpriteBatch();

	//	�`����J�n����
	spriteBath->Begin();

	//	�w�i�摜�̕`��
	spriteBath->Draw
	(
		m_backGroundTexture,
		DirectX::SimpleMath::Vector2::Zero
	);

	//	�w�i�摜�̕`��
	spriteBath->Draw
	(
		m_tableBackGroundTexture,
		DirectX::SimpleMath::Vector2(-130.0f,-100.0f)
	);

	//	�w�i�摜�̕`��
	m_resultBackGround->Draw();

	if (m_resultBackGround->Update())
	{
		//	�X�R�A��`�悷��
		m_scoreOutPut->Draw();

		//	�X�R�A���ꏏ�ɂȂ�����`�悷��
		if (m_judScore)
		{
			//	�]����`��
			m_valucationScore->Draw();
			//	�X�R�A���ꏏ�ɂȂ�����`�悷��
			m_pushSpase->Draw();
			//	���q��`�悷��
			m_pushSeal->Draw();
		}
	}

	//	�`����I������
	spriteBath->End();
}

/// <summary>
/// �I������
/// </summary>
void ResultScene::Finalize()
{

}

/// <summary>
///	�f�o�C�X�ˑ��̃��\�[�X
/// </summary>
void ResultScene::CreateDeviceDependentResources()
{
	//	�X�N���[�����\�[�X
	m_screen = MyLib::ScreenResources::GetInstance();
	//	���\�[�V�[�Y
	m_resorces = MyLib::ResourcesData::GetInstance();
	//	�w�i�摜
	m_backGroundTexture = m_resorces->GatShaderResourceView(L"Result_table");
	//	�w�i�摜
	m_tableBackGroundTexture = m_resorces->GatShaderResourceView(L"tableBackGround");
	//	�X�R�A�A�E�g�v�b�g
	m_scoreOutPut	  =	 std::make_unique<ScoreOutPut>();
	//	�X�R�A�̏�����
	m_scoreOutPut->Initialize();
	//	�]���X�R�A
	m_valucationScore = std::make_unique<ValuationScore>();
	//	�X�R�A�̕]���l������������
	m_valucationScore->Initialize(m_stageNum, PlayInfo::GetInstance()->GetScore());

	//	PUSHUI�L�[�̍쐬
	m_pushSpase = std::make_unique<OutPutResultUI>
		(
			m_resorces->GatShaderResourceView(L"ResultUISpaceKey"),
			PUSH_SPACE_POSITION,
			PUSH_SPACE_ORIGIN_POSITION
		);

	m_pushSeal = std::make_unique<PushSeal>
		(
			DirectX::SimpleMath::Vector2(640.0f, -200.0f),
			DirectX::SimpleMath::Vector2(135.0f, 201.0f)
		);
		
	//	�w�i�摜
	m_resultBackGround = std::make_unique<ResultBackGround>();
	//	����������
	m_resultBackGround->Initialize();
	
	//	�Ȃ��Đ�����
	AudioManager::GetInstance()->PlaySoundEffectBGM(L"ResultBGM");
}
