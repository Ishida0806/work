//
//		File Name �F InputSystem.cpp
//		Production�F 2023/6/1
//		Author�@�@�F �Γc ����	
// 
//		���͏����܂Ƃ߂��N���X
//	

#include "pch.h"
#include "Game/MyLib/GameDatas/InputSystem.h"

//	�萔
std::unique_ptr<MyLib::InputSystem> MyLib::InputSystem::m_inputSystem = nullptr;

/// <summary>
/// InputSystem���擾����
/// </summary>
/// <returns>�A�h���X</returns>
MyLib::InputSystem* const MyLib::InputSystem::GetInstance()
{
	//	�k���|�Ȃ琶��
	if (m_inputSystem == nullptr)
	{
		//	�X�N���[���N���X�̃C���X�^���X�𐶐�����
		m_inputSystem.reset(new MyLib::InputSystem());
	}
	//	�X�N���[�����\�[�X�N���X�̃C���X�^���X���擾����
	return m_inputSystem.get();
}

/// <summary>
/// �R���X�g���N�^
/// </summary>
MyLib::InputSystem::InputSystem()
{
	//	�f�o�C�X���\�[�V�[�Y
	DX::DeviceResources* DR = DX::DeviceResources::GetInstance();

	//	�L�[�{�[�h
	m_keyboard = std::make_unique<DirectX::Keyboard>();
	m_keyTracker = std::make_unique <DirectX::Keyboard::KeyboardStateTracker>();

	//	�}�E�X
	m_mouse = std::make_unique<DirectX::Mouse>();
	//	�E�C���h�T�C�Y�擾
	m_mouse->SetWindow(DR->GetWindow());
	//	�}�E�X�g���b�J�[������
	m_mouseTracker = std::make_unique<DirectX::Mouse::ButtonStateTracker>();
	//	�}�E�X���΍��W��
	m_mouse->SetMode(DirectX::Mouse::Mode::MODE_ABSOLUTE);

	//	�}�E�X�𑊑΍��W��
	m_mouse->SetMode(DirectX::Mouse::Mode::MODE_ABSOLUTE);
}

/// <summary>
/// �X�V����
/// </summary>
void MyLib::InputSystem::Update()
{
	//	�}�E�X��Ԏ擾
	m_mouseState = m_mouse->GetState();
	m_mouseTracker->Update(m_mouseState);
	//	�L�[�{�[�h��Ԏ擾
	m_keyTracker->Update(m_keyboard->GetState());
}
