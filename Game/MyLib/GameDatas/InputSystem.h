//
//		File Name �F InputSystem.h
//		Production�F 2023/6/1
//		Author�@�@�F �Γc ����	
//	
#pragma once
#include "pch.h"

namespace MyLib
{
	class InputSystem final
	{
	public:
		//	�C���v�b�g�̃C���X�^���X���擾����
		static InputSystem* const GetInstance();

	private:

		//	�L�[�{�[�h
		std::unique_ptr<DirectX::Keyboard>								m_keyboard;
		std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker>		m_keyTracker;

		//	�}�E�X
		DirectX::Mouse::State											m_mouseState;
		std::unique_ptr<DirectX::Mouse>									m_mouse;
		std::unique_ptr<DirectX::Mouse::ButtonStateTracker>				m_mouseTracker;

		//�R���X�g���N�^��f�X�g���N�^�͊O������A�N�Z�X�ł��Ȃ��悤��
		InputSystem();

	public:
		// �X�N���[�����\�[�V�[�Y�N���X�̃C���X�^���X�ւ̃|�C���^
		static std::unique_ptr<MyLib::InputSystem> m_inputSystem;

	public:

		void Update();

		DirectX::Keyboard::KeyboardStateTracker* GetKeyTracer()		{ return m_keyTracker.get(); }		//	�L�[�{�[�h
		DirectX::Keyboard*						 GetKeyboard()		{ return m_keyboard.get(); }		//	�L�[�{�[�h
		DirectX::Mouse*							 GetMouse()			{ return m_mouse.get(); }		//	�}�E�X
		DirectX::Mouse::ButtonStateTracker*		 GetStateTracker()	{ return m_mouseTracker.get(); }	//	�}�E�X
	};
}