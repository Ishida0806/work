
#include "pch.h"
#include "TutorialMovingMethod.h"

/// <summary>
/// コンストラクタ
/// </summary>
TutorialMovingMethod::TutorialMovingMethod()
{
}

/// <summary>
/// デストラクタ
/// </summary>
TutorialMovingMethod::~TutorialMovingMethod()
{
}

/// <summary>
/// 入れ替わる前に呼び出す
/// </summary>
/// <param name="finiteStateMachine">オーナー</param>
void TutorialMovingMethod::Enter(TutorialSystem::TUTORIALSTATE* finiteStateMachine)
{
	m_beforeMousePosition.x = static_cast<float>(MyLib::InputSystem::GetInstance()->GetMouse()->GetState().x);
	m_beforeMousePosition.y = static_cast<float>(MyLib::InputSystem::GetInstance()->GetMouse()->GetState().y);
}

/// <summary>
/// 実行する
/// </summary>
/// <param name="finiteStateMachine">オーナー<</param>
/// <param name="elapsedTime">経過時間</param>
void TutorialMovingMethod::Execute(TutorialSystem::TUTORIALSTATE* finiteStateMachine, const DX::StepTimer& timer)
{
	//	現在のマウス座標
	DirectX::SimpleMath::Vector2 mousePosition;

	//	更新
	mousePosition.x = static_cast<float>(MyLib::InputSystem::GetInstance()->GetMouse()->GetState().x);
	mousePosition.y = static_cast<float>(MyLib::InputSystem::GetInstance()->GetMouse()->GetState().y);

	auto input = MyLib::InputSystem::GetInstance()->GetKeyboard()->GetState();

	if ((mousePosition.x != m_beforeMousePosition.x || mousePosition.y != m_beforeMousePosition.y) && (input.A || input.D || input.W || input.S))
	{
		//	次の画像ガイドを設定する
		finiteStateMachine->GetOwner()->SetGuideTexture(MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"TutorialGuide02"));
		//	次の状態を決める
		finiteStateMachine->RequestTransition(TutorialSystem::TutorialState::WeponMethod);
	}	
}

/// <summary>
/// 退出時の処理
/// </summary>
/// <param name="finiteStateMachine">オーナー</param>
void TutorialMovingMethod::Exit(TutorialSystem::TUTORIALSTATE* finiteStateMachine)
{
}
