//
//		File Name ： EnemyLeg.h
//		Production： 2023/11/12
//		Author　　： 石田 恭一	
//	
#pragma 
#include "../Object.h"

class Enemy;

class EnemyLeg final : public Object
{
	//	変数
private:
	//	敵モデル
	DirectX::Model*								 m_enemyModel;
	//	親
	Enemy*										 m_parent;

	//	関数
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="enemy">座標</param>
	/// <param name="model">モデル</param>
	EnemyLeg(Enemy* enemy, DirectX::Model* model);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~EnemyLeg();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="timer">タイマー</param>
	/// <param name="rollAngleSpeed">脚が回る速度/param>
	void RollLeg(const DX::StepTimer& timer, const float& rollAngleSpeed);

	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="view">ビュー</param>
	/// <param name="proj">プロジェクション</param>
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj) override;

	/// <summary>
	/// 終了処理
	/// </summary>
	void Finalize() override;
};