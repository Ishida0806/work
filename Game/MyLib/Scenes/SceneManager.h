#pragma once
#include "pch.h"
#include "Game/MyLib/Scenes/IScene.h"

//	シーンマネージャー
class SceneManager final
{
	//	変数
private:
	//	各シーン
	IScene* m_scenes;

public:
	SceneManager()
		:
		m_scenes(nullptr)
	{
	};

	~SceneManager()
	{
		if (m_scenes)
		{
			m_scenes->Finalize();
			delete m_scenes;
		}
	};

	//	シーンを変更する
	template<class NewScene, class ...Argument>
	void ChangeScene(Argument ...argument)
	{
		if (m_scenes)
		{
			m_scenes->Finalize();
			delete m_scenes;
		}
		//	新しいシーンを生成する
		m_scenes = new NewScene(argument...);
		m_scenes->Initialize();
		//	シーンが切り替わる毎に経過時間をリセットする
		MyLib::ElapsedTime::GetInstance()->RestElapsedTime();
	}

	/// <summary>
	/// 後進処理を行う
	/// </summary>
	/// <param name="timer"></param>
	void Update(const DX::StepTimer& timer)
	{
		m_scenes->Update(timer);
	}

	/// <summary>
	/// 描画する
	/// </summary>
	void Render()
	{
		m_scenes->Render();
	}
};