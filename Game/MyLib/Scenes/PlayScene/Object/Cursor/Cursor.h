#pragma once

//	以下カーソル呼び出し
#include "ICursorComponent.h"
#include "ICursorFactory.h"
#include "CursorFactory.h"
#include "CursorBottom.h"
#include "CursorTop.h"

interface ICursorComponent;

class Cursor : public  ICursorComponent 
{
	//	アクセサ
public:

	// 親を取得する
	inline ICursorComponent* GetParent()				 override { return nullptr; }
	// 位置を取得する
	inline DirectX::SimpleMath::Vector3 GetPosition()	 override { return m_cursorPosition; }
	//	回転角を取得する
	inline DirectX::SimpleMath::Quaternion GetRotate()   override { return m_cursorRotate; }
	// 回転角を取得する
	inline float GetAngle()								 override { return m_cursorAngle; }
	// モデルを取得する
	inline DirectX::Model* GetModel()					 override { return nullptr; }

	//	変数
private:
	//	カーソルの座標
	DirectX::SimpleMath::Vector3	 m_cursorPosition;
	//	カーソルの回転
	DirectX::SimpleMath::Quaternion	 m_cursorRotate;
	//	カーソルの角度
	float m_cursorAngle;

	//	部品君たち
	std::unique_ptr<ICursorComponent> m_curorParts;

	//	当たり判定よう	
	Collision::Shape::Segment m_mouseSegementPos;
	Collision::Shape::Triangle m_tri1;
	Collision::Shape::Triangle m_tri2;

	//	関数
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="position">座標</param>
	/// <param name="rotate">回転角</param>
	/// <param name="angle">角度</param>
	Cursor(
		const DirectX::SimpleMath::Vector3&      position,
		const DirectX::SimpleMath::Quaternion&	 rotate,
		const float angle
	);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Cursor();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="timer">タイマー</param>
	void Update(const DX::StepTimer& timer) override;

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

	//	参照した角度に割り当てる
	void CalculateAngleRotate(const DirectX::SimpleMath::Vector3& position, float& angle);

	// 砲塔部品を追加する
	void AddCurortPart(std::unique_ptr<ICursorComponent> turretParts);

private:

	void CreatePosCursor();

	DirectX::SimpleMath::Matrix CreateMatrixScreen2WorldPos(int screen_w,int screen_h,const DirectX::SimpleMath::Matrix& view,const DirectX::SimpleMath::Matrix& proj);
	// 三角平面との交点入れてくれる
	bool IntersectSegmentAndTriangle(DirectX::SimpleMath::Vector3 p, DirectX::SimpleMath::Vector3 q, Collision::Shape::Triangle tri, DirectX::SimpleMath::Vector3* s);
};

