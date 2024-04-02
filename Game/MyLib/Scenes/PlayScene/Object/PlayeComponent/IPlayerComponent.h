//
//		File Name ： IPlayerComponent.h
//		Production： 2023/12/25
//		Author　　： 石田 恭一	
// 
//		プレイヤーの各パーツたちのインターフェイス
//	
#pragma once

class Player;
class Object;

__interface IPlayerComponent
{
	//	初期化する
	void Initialize();
	//	部品を更新する
	void UpdateParts(const DX::StepTimer& timer);
	//	死亡アニメーション
	void DeathAnimation(const DX::StepTimer& timer);
	// 勝利アニメーション
	void WinAnimation(const DX::StepTimer& timer);
	//	モデルの描画
	void DrawModel(DirectX::Model* model, const DirectX::SimpleMath::Matrix& world, const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj);
};