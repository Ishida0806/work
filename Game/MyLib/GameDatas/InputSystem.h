//
//		File Name ： InputSystem.h
//		Production： 2023/6/1
//		Author　　： 石田 恭一	
//	
#pragma once
#include "pch.h"

namespace MyLib
{
	class InputSystem final
	{
	public:
		//	インプットのインスタンスを取得する
		static InputSystem* const GetInstance();

	private:

		//	キーボード
		std::unique_ptr<DirectX::Keyboard>								m_keyboard;
		std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker>		m_keyTracker;

		//	マウス
		DirectX::Mouse::State											m_mouseState;
		std::unique_ptr<DirectX::Mouse>									m_mouse;
		std::unique_ptr<DirectX::Mouse::ButtonStateTracker>				m_mouseTracker;

		//コンストラクタやデストラクタは外部からアクセスできないように
		InputSystem();

	public:
		// スクリーンリソーシーズクラスのインスタンスへのポインタ
		static std::unique_ptr<MyLib::InputSystem> m_inputSystem;

	public:

		void Update();

		DirectX::Keyboard::KeyboardStateTracker* GetKeyTracer()		{ return m_keyTracker.get(); }		//	キーボード
		DirectX::Keyboard*						 GetKeyboard()		{ return m_keyboard.get(); }		//	キーボード
		DirectX::Mouse*							 GetMouse()			{ return m_mouse.get(); }		//	マウス
		DirectX::Mouse::ButtonStateTracker*		 GetStateTracker()	{ return m_mouseTracker.get(); }	//	マウス
	};
}