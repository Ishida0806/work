//
//		File Name ： CursorTop.h
//		Production： 2023/7/02
//		Author　　： 石田 恭一
//
#pragma once
#include "ICursorComponent.h"

interface ICursorComponent;

class CursorTop final : public ICursorComponent
{
	//	変数
private:
	// 親
	ICursorComponent* m_parent;
	//	カーソル上部の座標
	DirectX::SimpleMath::Vector3				   m_cursorTopPosition;
	//	カーソル上部の回転
	DirectX::SimpleMath::Quaternion				   m_cursorTopRotate;
	float										   m_cursorTopAngle;
	//	カーソル上部のモデル
	DirectX::Model*								   m_cursorTopModel;
	//	カーソルのパーツ
	std::vector<std::unique_ptr<ICursorComponent>> m_curorParts;
	//	経過時間
	float m_second;

	//	関数
public:
	CursorTop(ICursorComponent* parent, const DirectX::SimpleMath::Vector3& position, const float& angle);
	~CursorTop();

	//	アクセサ
public:

	// 親を取得する
	inline ICursorComponent* GetParent() override { return m_parent; }
	// 位置を取得する
	inline DirectX::SimpleMath::Vector3 GetPosition()  override { return m_cursorTopPosition; }
	//	回転角を取得する
	DirectX::SimpleMath::Quaternion GetRotate()   override { return m_cursorTopRotate; }
	// 回転角を取得する
	inline float GetAngle()   override { return m_cursorTopAngle; }
	// モデルを取得する
	inline DirectX::Model* GetModel()  override { return m_cursorTopModel; }
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
