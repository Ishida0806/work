#pragma once
#include "pch.h"
#include "Game/MyLib/Scenes/IScene.h"

//	�V�[���}�l�[�W���[
class SceneManager final
{
	//	�ϐ�
private:
	//	�e�V�[��
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

	//	�V�[����ύX����
	template<class NewScene, class ...Argument>
	void ChangeScene(Argument ...argument)
	{
		if (m_scenes)
		{
			m_scenes->Finalize();
			delete m_scenes;
		}
		//	�V�����V�[���𐶐�����
		m_scenes = new NewScene(argument...);
		m_scenes->Initialize();
		//	�V�[�����؂�ւ�閈�Ɍo�ߎ��Ԃ����Z�b�g����
		MyLib::ElapsedTime::GetInstance()->RestElapsedTime();
	}

	/// <summary>
	/// ��i�������s��
	/// </summary>
	/// <param name="timer"></param>
	void Update(const DX::StepTimer& timer)
	{
		m_scenes->Update(timer);
	}

	/// <summary>
	/// �`�悷��
	/// </summary>
	void Render()
	{
		m_scenes->Render();
	}
};