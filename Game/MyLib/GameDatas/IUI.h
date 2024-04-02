//
//		File Name ： IUI.h
//		Production： 2023/10/2
//		Author　　： 石田 恭一
// 
//		UIのインターフェイス
//
#pragma once
#include "pch.h"

interface IUI
{
	//	デファクトデストラクタ
	virtual ~IUI() = default;
	//	初期化処理
	virtual void Initialize() = 0;
	//	更新処理
	virtual void Update(const DX::StepTimer& timer) = 0;
	//	描画する
	virtual void Draw() = 0;
};