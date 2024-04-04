//
//		File Name ： TutorialSystem.h
//		Production： 2024/4/04
//		Author　　： 石田 恭一	
//	
#pragma once

class TutorialSystem
{

	/// <summary>
	/// コンストラクタ
	/// </summary>
	TutorialSystem();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~TutorialSystem();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize();
	
	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="timer">タイマー</param>
	void Update(const DX::StepTimer& timer);

	/// <summary>
	/// 描画処理
	/// </summary>
	void Render();

	/// <summary>
	/// 終了処理
	/// </summary>
	void Finalize();
};