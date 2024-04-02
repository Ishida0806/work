//
//		File Name ： FallingCherryBlossoms.h
//		Production： 2023/11/12
//		Author　　： 石田 恭一	
//	
#pragma once
#include "../Object.h"
#include "../Player.h"

class FallingCherryBlossoms : public Object
{
	//	定数
public:

	//	自身のランダムな座標
	static const float RANDOM_MINE_POSITION;

	//	変数
private:
	//	プリミティブバッチ
	std::unique_ptr<DirectX::GeometricPrimitive>	m_primitive;
	//	色
	DirectX::SimpleMath::Color						m_colors;
	//	プレイヤー
	Player*											m_player;
	//	ランラムで出現するY座標
	float											m_randamSpawnYPosition;
	//	ランダムな向き
	float											m_randamDirection;

	//	関数
public:
	//	コンストラクタ
	FallingCherryBlossoms(Player* player);
	//	デストラクタ
	~FallingCherryBlossoms();
	//	初期化
	void Initialize() override;
	//	更新
	void Update(const DX::StepTimer& timer) override;
	//	描画
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj) override;
	//	終了処理
	void Finalize() override;
};