//
//		File Name ： PlayerArrow.h
//		Production： 2023/11/03
//		Author　　： 石田 恭一	
//	
#pragma once

#include "Game/MyLib/Scenes/PlayScene/Object/Object.h"

class Object;

class PlayerArrow : public Object
{
	//	定数
public:

	//	矢印の移動速度
	static const float MOVE_ARROW_SPEED;
	//	矢印の回転角のZ
	static const float ARROW_ROTATE_Z;


	//	変数
private:

	//	矢印モデル
	DirectX::Model*									 m_arrowModel;
	//	親
	Object*											 m_parent;
	//	円の角度
	float											 m_circleAngle;
	//	矢印の角度
	float											 m_arrowAngle;
	//	親座標
	DirectX::SimpleMath::Vector3					 m_position;
	//	カーソルの座標
	DirectX::SimpleMath::Vector3*					 m_cursolPosition;
	//	矢印の座標
	DirectX::SimpleMath::Vector3					 m_arrowPosition;
	//	カーソルの回転角
	DirectX::SimpleMath::Quaternion*				 m_cursolRotate;

	//	関数
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parent">親</param>
	/// <param name="arrowModel">矢印モデル</param>
	/// <param name="cursolPosition">カーソルの座標</param>
	/// <param name="cursolRotate">カーソルの回転角</param>
	PlayerArrow(
		Object* parent,
		DirectX::Model* arrowModel, 
		DirectX::SimpleMath::Vector3* cursolPosition,
		DirectX::SimpleMath::Quaternion* cursolRotate
	);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~PlayerArrow();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update(const DX::StepTimer& timer) override;
	
	/// <summary>
	/// 描画する
	/// </summary>
	/// <param name="view">ビュー</param>
	/// <param name="proj">プロジェクション</param>
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj) override;

	/// <summary>
	/// 終了処理
	/// </summary>
	void Finalize() override;
};