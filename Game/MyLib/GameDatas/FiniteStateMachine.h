//
//		File Name ： FiniteStateMachine.h
//		Production： 2023/12/25
//		Author　　： 石田 恭一	
// 
//		有限ステートマシーン
//	
#pragma once
#include <unordered_map>

template<typename Owner, typename StateID>
class FiniteStateMachine final
{
	// 内部クラス
public:
	class IState;    

	//	変数
private:
	//	所有者
	Owner*								 m_owner;        
	//	登録ステート
	std::unordered_map<StateID, IState*> m_states;
	//	現在のステート
	IState*								 m_currentState;    
	//	遷移先のステート
	IState*								 m_nextState;       

	// コンストラクタ 
public:
	// コンストラクタ
	FiniteStateMachine(Owner* owner);
	// デストラクタ
	~FiniteStateMachine();

	// 操作
public:
	// ステートの登録
	void RegisterState(StateID stateID, IState* state);
	// ステートマシンの起動
	void Start(StateID initialStateID);
	// 遷移を要求
	void RequestTransition(StateID nextStateID);
	// 更新
	void Update(const DX::StepTimer& timer);

	//	アクセサ
public:

	//	オーナーを取得する
	Owner*  GetOwner()						  const { return m_owner; }

	// 埋め込み関数
private:
	// ステートの遷移
	void Transition();
	void Transition(IState* state);
};


template<typename Owner, typename StateID>
class FiniteStateMachine<Owner, StateID>::IState
{
	// 関数
public:
	// デストラクタ
	virtual ~IState() = default;

	//	関数
public:
	virtual void Enter(FiniteStateMachine* finiteStateMachine) = 0;
	virtual void Execute(FiniteStateMachine* finiteStateMachine, const DX::StepTimer& timer) = 0;
	virtual void Exit(FiniteStateMachine* finiteStateMachine) = 0;
};

//	コンストラクタ
template<typename Owner, typename StateID>
FiniteStateMachine<Owner, StateID>::FiniteStateMachine(Owner* owner)
	:m_owner(owner),
	m_currentState(nullptr),
	m_nextState(nullptr),
	m_states{}
{
}

//	デストラクタ
template<typename Owner, typename StateID>
inline FiniteStateMachine<Owner, StateID>::~FiniteStateMachine()
{
	for (auto deleteState : m_states)
	{
		delete deleteState.second;
	}
}

//	ステートの追加
template<typename Owner, typename StateID>
inline void FiniteStateMachine<Owner, StateID>::RegisterState(StateID stateID, IState* state)
{
	//	追加
	m_states.emplace(stateID, state);
}

//	開始のステート
template<typename Owner, typename StateID>
inline void FiniteStateMachine<Owner, StateID>::Start(StateID stateID)
{
	//　開始ステートへ遷移
	Transition(m_states.at(stateID));
}

// 遷移を要求
template<typename Owner, typename StateID>
inline void FiniteStateMachine<Owner, StateID>::RequestTransition(StateID nextStateID)
{
	// 遷移先ステートの設定
	m_nextState = m_states.at(nextStateID);
}

//	更新処理
template<typename Owner, typename StateID>
inline void FiniteStateMachine<Owner, StateID>::Update(const DX::StepTimer& timer)
{
	//	次のステートが入ってるなら変える
	if (m_nextState)
	{
		Transition();
	}

	// ステートの実行
	m_currentState->Execute(this, timer);
}

//	ステートを変える
template<typename Owner, typename StateID>
inline void FiniteStateMachine<Owner, StateID>::Transition()
{
	 // 現在のステートの退場時アクション
	if (m_currentState)
	{
		m_currentState->Exit(this);
	}

	// 遷移先のステートの入場時アクション
	if (m_nextState)
	{
		//	入力する
		m_nextState->Enter(this);
		//	現在のステートと入れ替える
		m_currentState = m_nextState;
		//	初期化する
		m_nextState = nullptr;
	}
}

//	ステートを遷移する
template<typename Owner, typename StateID>
inline void FiniteStateMachine<Owner, StateID>::Transition(IState* state)
{
	m_nextState = state;
	Transition();
}