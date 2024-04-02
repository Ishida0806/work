//
//		File Name ： IScene.h
//		Production： 2023/9/14
//		Author　　： 石田 恭一
//
#pragma once

//	インターフェイスを宣言する
interface IScene
{
	//	仮想デストラクタ
	virtual ~IScene() = default;
	//	初期化処理
	virtual void Initialize() = 0;
	//	更新処理
	virtual void Update(const DX::StepTimer& timer) = 0;
	//	描画処理
	virtual void Render() = 0;
	//	終了処理	
	virtual void Finalize() = 0;
};

