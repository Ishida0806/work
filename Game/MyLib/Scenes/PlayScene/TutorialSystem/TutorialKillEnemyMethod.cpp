
#include "pch.h"
#include "TutorialKillEnemyMethod.h"
#include "Game/MyLib/Scenes/PlayScene/Object/Object.h"
#include "Game/MyLib/Scenes/PlayScene/Object/Enemy/EnemyManager.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
TutorialKillEnemyMethod::TutorialKillEnemyMethod()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
TutorialKillEnemyMethod::~TutorialKillEnemyMethod()
{
}

/// <summary>
/// ����ւ��O�ɌĂяo��
/// </summary>
/// <param name="finiteStateMachine">�I�[�i�[</param>
void TutorialKillEnemyMethod::Enter(TutorialSystem::TUTORIALSTATE* finiteStateMachine)
{
	//	�ʏ�G�̍쐬
	finiteStateMachine->GetOwner()->GetEnemyManager()->CreateEnemy(EnemyManager::EnemyType::NormalEnemy, 4, 1, 1);
}

/// <summary>
/// ���s����
/// </summary>
/// <param name="finiteStateMachine">�I�[�i�[<</param>
/// <param name="elapsedTime">�o�ߎ���</param>
void TutorialKillEnemyMethod::Execute(TutorialSystem::TUTORIALSTATE* finiteStateMachine, const DX::StepTimer& timer)
{
	UNREFERENCED_PARAMETER(timer);

	//	�G��|�����玟�̃X�e�[�g
	if (finiteStateMachine->GetOwner()->GetEnemyManager()->GetEnemy().size() == 0)
	{
		//	���̉摜�K�C�h��ݒ肷��
		finiteStateMachine->GetOwner()->SetGuideTexture(MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"TutorialGuide04"));
		//	���̏�Ԃ����߂�
		finiteStateMachine->RequestTransition(TutorialSystem::TutorialState::FinishMethod);
	}
}

/// <summary>
/// �ޏo���̏���
/// </summary>
/// <param name="finiteStateMachine">�I�[�i�[</param>
void TutorialKillEnemyMethod::Exit(TutorialSystem::TUTORIALSTATE* finiteStateMachine)
{
	UNREFERENCED_PARAMETER(finiteStateMachine);
}
