//
//		File Name ： InputSystem.cpp
//		Production： 2023/6/1
//		Author　　： 石田 恭一	
// 
//		入力情報をまとめたクラス
//	

#include "pch.h"
#include "Game/MyLib/GameDatas/InputSystem.h"

//	定数
std::unique_ptr<MyLib::InputSystem> MyLib::InputSystem::m_inputSystem = nullptr;

/// <summary>
/// InputSystemを取得する
/// </summary>
/// <returns>アドレス</returns>
MyLib::InputSystem* const MyLib::InputSystem::GetInstance()
{
	//	ヌルポなら生成
	if (m_inputSystem == nullptr)
	{
		//	スクリーンクラスのインスタンスを生成する
		m_inputSystem.reset(new MyLib::InputSystem());
	}
	//	スクリーンリソースクラスのインスタンスを取得する
	return m_inputSystem.get();
}

/// <summary>
/// コンストラクタ
/// </summary>
MyLib::InputSystem::InputSystem()
{
	//	デバイスリソーシーズ
	DX::DeviceResources* DR = DX::DeviceResources::GetInstance();

	//	キーボード
	m_keyboard = std::make_unique<DirectX::Keyboard>();
	m_keyTracker = std::make_unique <DirectX::Keyboard::KeyboardStateTracker>();

	//	マウス
	m_mouse = std::make_unique<DirectX::Mouse>();
	//	ウインドサイズ取得
	m_mouse->SetWindow(DR->GetWindow());
	//	マウストラッカー初期化
	m_mouseTracker = std::make_unique<DirectX::Mouse::ButtonStateTracker>();
	//	マウスを絶対座標に
	m_mouse->SetMode(DirectX::Mouse::Mode::MODE_ABSOLUTE);

	//	マウスを相対座標に
	m_mouse->SetMode(DirectX::Mouse::Mode::MODE_ABSOLUTE);
}

/// <summary>
/// 更新処理
/// </summary>
void MyLib::InputSystem::Update()
{
	//	マウス状態取得
	m_mouseState = m_mouse->GetState();
	m_mouseTracker->Update(m_mouseState);
	//	キーボード状態取得
	m_keyTracker->Update(m_keyboard->GetState());
}
