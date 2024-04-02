//
//		File Name ： CursorBottom.h
//		Production： 2023/7/02
//		Author　　： 石田 恭一
//
#pragma once
#include "ICursorComponent.h"

interface ICursorComponent;

class CursorBottom : public ICursorComponent
{
public:

	static const float							FRICTION_SCALE;
	static const float							CURSOR_SCALE;
	static const DirectX::SimpleMath::Vector3	BASE_SCALE;

private:
	// 親
	ICursorComponent*							   m_parent;
	//	座標
	DirectX::SimpleMath::Vector3				   m_cursorBottomPosition;
	//大きさ
	DirectX::SimpleMath::Vector3				   m_cursorBottomScale;
	//	回転角
	DirectX::SimpleMath::Quaternion				   m_cursorBottomRotate;
	//	角度
	float										   m_cursorBottomAngle;
	//	時間
	float										   m_second;
	//	モデル
	DirectX::Model*								   m_cursorBottomModel;
	//	カーソルのパーツ
	std::vector<std::unique_ptr<ICursorComponent>> m_curorParts;


public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parent">親</param>
	/// <param name="position">座標</param>
	/// <param name="rotate">回転角</param>
	CursorBottom(
		ICursorComponent* parent,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& rotate
	);
	~CursorBottom();

	// 親を取得する
	ICursorComponent* GetParent()	override { return m_parent; }
	// 位置を取得する
	DirectX::SimpleMath::Vector3	GetPosition() override { return m_cursorBottomPosition; }
	//	回転角を取得する
	DirectX::SimpleMath::Quaternion GetRotate()   override { return m_cursorBottomRotate; }
	// 回転角を取得する
	float GetAngle()  override { return m_cursorBottomAngle;}
	// モデルを取得する
	DirectX::Model* GetModel() override { return m_cursorBottomModel; }
public:
	//	初期化処理
	void Initialize() override;
	//	更新処理
	void Update(const DX::StepTimer& timer) override;
	//	描画処理
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj) override;
	//	終了処理	
	void Finalize() override;
	// 砲塔部品を追加する
	void AddCurortPart(std::unique_ptr<ICursorComponent> turretParts);
};
