//
//		File Name �F PlaySceneWave.h
//		Production�F 2024/1/23
//		Author�@�@�F �Γc ����	
// 
//		�v���C�V�[���̃E�F�[�u�����Ǘ�����N���X
//
#include "pch.h"
#include "PlaySceneWave.h"
#include "../PlayScene.h"
#include "Game/MyLib/Scenes/StageSelect/StageSelectScene.h"


	//	�E�F�[�u�̐F���
const DirectX::SimpleMath::Color PlaySceneWave::WAVE_COLOR	= DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 0.7f);

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="playScene">�v���C�V�[��</param>
PlaySceneWave::PlaySceneWave(PlayScene* playScene)
	:
	m_playScene(playScene),
	m_waveDisplayTexture(nullptr),
	m_isFinalWave(false),
	m_currentWave(1),
	m_maxWave(0)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlaySceneWave::~PlaySceneWave()
{
}

/// <summary>
///	����������
/// </summary>
void PlaySceneWave::Initialize()
{
	//	�G�̃f�[�^�̍쐬
	std::unique_ptr<ButtleWave> enemyData = std::make_unique<ButtleWave>(m_playScene);
	//	�G�̃f�[�^���擾����
	m_enemyDatas = enemyData->OpenMap();
	//	�ő�X�e�[�W�����擾����
	m_maxWave = enemyData->GetMaxWave();
	//	�E�F�[�u�̉��摜
	m_waveDisplayTexture = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"WaveDisplay");
	//	���݂̃E�F�[�u���̐������쐬
	m_currentNumber = std::make_unique<Number>
	(
		MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"number"),
		DirectX::SimpleMath::Vector2(705.0f, 112.5f),
		m_currentWave
	);
	//	�ő�E�F�[�u���̐������쐬
	m_maxNumber		= std::make_unique<Number>
	(
		MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"number"),
		DirectX::SimpleMath::Vector2(746.0f, 152.5f),
		m_maxWave
	);
}

/// <summary>
/// �X�V����
/// </summary>
void PlaySceneWave::Update()
{
	//	�X�e�[�W�̌^�ɃL���X�g
	StageSelectScene::CHOOSE_STAGE stage = static_cast<StageSelectScene::CHOOSE_STAGE>(m_playScene->GetWordLevel());
	//	�ő�X�e�[�W�̏ꍇ�͋A��
	if (stage == StageSelectScene::CHOOSE_STAGE::STAGE_4)	return;
	//	�ő�E�F�[�u���̍X�V
	m_maxNumber->Update(m_maxWave);
	//	���݂̃E�F�[�u�̍X�V
	m_currentNumber->Update(m_currentWave);

	if (m_maxWave == m_currentWave)
	{
		//	�ŏI�E�F�[�u�ɂȂ���
		m_isFinalWave = true;
	}

#ifdef _DEBUG
	if(MyLib::InputSystem::GetInstance()->GetKeyTracer()->pressed.F2){ m_isFinalWave = true; }
#endif // _DEBUG

}

/// <summary>
/// �`�悷��
/// </summary>
void PlaySceneWave::Draw()
{
	//	�X�e�[�W�̌^�ɃL���X�g
	StageSelectScene::CHOOSE_STAGE stage = static_cast<StageSelectScene::CHOOSE_STAGE>(m_playScene->GetWordLevel());
	//	�ő�X�e�[�W�̏ꍇ�͋A��
	if (stage == StageSelectScene::CHOOSE_STAGE::STAGE_4)	return;

	//	�`�悷��
	MyLib::ScreenResources::GetInstance()->GetSpriteBatch()->Draw
	(
		m_waveDisplayTexture,
		DirectX::SimpleMath::Vector2(680.0f, 68.0f),
		nullptr,
		WAVE_COLOR,
		0.0f,
		DirectX::SimpleMath::Vector2(74.5f, 76.0f)
	);
	//	�ő吔����`�悷��
	m_maxNumber->DrawWaveNumber();
	//	���݂̃E�F�[�u��`�悷��
	m_currentNumber->DrawWaveNumber();
}

/// <summary>
/// ���̃E�F�[�u�֍s��
/// </summary>
void PlaySceneWave::NextWave()
{
	m_currentWave++;
}

/// <summary>
/// �X�|�[�������G�I�u�W�F�N�g�̃f�[�^���폜����
/// </summary>
void PlaySceneWave::DeleteSpawnedEnemyData()
{
	// �����𖞂����G�I�u�W�F�N�g���폜
	m_enemyDatas.erase
	(
		std::remove_if
		(
			m_enemyDatas.begin(), m_enemyDatas.end(),
			[&](const EnemyData& enemyData)
			{
				return enemyData.spawnWave == m_currentWave;
			}
		),
		m_enemyDatas.end()
	);
}
