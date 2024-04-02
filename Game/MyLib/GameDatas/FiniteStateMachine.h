//
//		File Name �F FiniteStateMachine.h
//		Production�F 2023/12/25
//		Author�@�@�F �Γc ����	
// 
//		�L���X�e�[�g�}�V�[��
//	
#pragma once
#include <unordered_map>

template<typename Owner, typename StateID>
class FiniteStateMachine final
{
	// �����N���X
public:
	class IState;    

	//	�ϐ�
private:
	//	���L��
	Owner*								 m_owner;        
	//	�o�^�X�e�[�g
	std::unordered_map<StateID, IState*> m_states;
	//	���݂̃X�e�[�g
	IState*								 m_currentState;    
	//	�J�ڐ�̃X�e�[�g
	IState*								 m_nextState;       

	// �R���X�g���N�^ 
public:
	// �R���X�g���N�^
	FiniteStateMachine(Owner* owner);
	// �f�X�g���N�^
	~FiniteStateMachine();

	// ����
public:
	// �X�e�[�g�̓o�^
	void RegisterState(StateID stateID, IState* state);
	// �X�e�[�g�}�V���̋N��
	void Start(StateID initialStateID);
	// �J�ڂ�v��
	void RequestTransition(StateID nextStateID);
	// �X�V
	void Update(const DX::StepTimer& timer);

	//	�A�N�Z�T
public:

	//	�I�[�i�[���擾����
	Owner*  GetOwner()						  const { return m_owner; }

	// ���ߍ��݊֐�
private:
	// �X�e�[�g�̑J��
	void Transition();
	void Transition(IState* state);
};


template<typename Owner, typename StateID>
class FiniteStateMachine<Owner, StateID>::IState
{
	// �֐�
public:
	// �f�X�g���N�^
	virtual ~IState() = default;

	//	�֐�
public:
	virtual void Enter(FiniteStateMachine* finiteStateMachine) = 0;
	virtual void Execute(FiniteStateMachine* finiteStateMachine, const DX::StepTimer& timer) = 0;
	virtual void Exit(FiniteStateMachine* finiteStateMachine) = 0;
};

//	�R���X�g���N�^
template<typename Owner, typename StateID>
FiniteStateMachine<Owner, StateID>::FiniteStateMachine(Owner* owner)
	:m_owner(owner),
	m_currentState(nullptr),
	m_nextState(nullptr),
	m_states{}
{
}

//	�f�X�g���N�^
template<typename Owner, typename StateID>
inline FiniteStateMachine<Owner, StateID>::~FiniteStateMachine()
{
	for (auto deleteState : m_states)
	{
		delete deleteState.second;
	}
}

//	�X�e�[�g�̒ǉ�
template<typename Owner, typename StateID>
inline void FiniteStateMachine<Owner, StateID>::RegisterState(StateID stateID, IState* state)
{
	//	�ǉ�
	m_states.emplace(stateID, state);
}

//	�J�n�̃X�e�[�g
template<typename Owner, typename StateID>
inline void FiniteStateMachine<Owner, StateID>::Start(StateID stateID)
{
	//�@�J�n�X�e�[�g�֑J��
	Transition(m_states.at(stateID));
}

// �J�ڂ�v��
template<typename Owner, typename StateID>
inline void FiniteStateMachine<Owner, StateID>::RequestTransition(StateID nextStateID)
{
	// �J�ڐ�X�e�[�g�̐ݒ�
	m_nextState = m_states.at(nextStateID);
}

//	�X�V����
template<typename Owner, typename StateID>
inline void FiniteStateMachine<Owner, StateID>::Update(const DX::StepTimer& timer)
{
	//	���̃X�e�[�g�������Ă�Ȃ�ς���
	if (m_nextState)
	{
		Transition();
	}

	// �X�e�[�g�̎��s
	m_currentState->Execute(this, timer);
}

//	�X�e�[�g��ς���
template<typename Owner, typename StateID>
inline void FiniteStateMachine<Owner, StateID>::Transition()
{
	 // ���݂̃X�e�[�g�̑ޏꎞ�A�N�V����
	if (m_currentState)
	{
		m_currentState->Exit(this);
	}

	// �J�ڐ�̃X�e�[�g�̓��ꎞ�A�N�V����
	if (m_nextState)
	{
		//	���͂���
		m_nextState->Enter(this);
		//	���݂̃X�e�[�g�Ɠ���ւ���
		m_currentState = m_nextState;
		//	����������
		m_nextState = nullptr;
	}
}

//	�X�e�[�g��J�ڂ���
template<typename Owner, typename StateID>
inline void FiniteStateMachine<Owner, StateID>::Transition(IState* state)
{
	m_nextState = state;
	Transition();
}