#pragma once

#include "WallFactory.h"
#include "IWallFactory.h"

class WallFactory;
__interface IWallFactory;

class Wall final
{
	//	定数
public:
	static const DirectX::SimpleMath::Vector3 WALL_SCALE;

	//	変数
private:
	//	座標
	DirectX::SimpleMath::Vector3	m_wallPos;
	//	大きさ
	DirectX::SimpleMath::Vector3	m_wallScale;
	//	モデル
	DirectX::Model*				m_wallModel;
	//	スクリーンリソース
	MyLib::ScreenResources*		m_screen;
	//	壁のあたり判定
	Collision::Shape::Box			m_wallBox;
	//	角度
	float						m_wallAngle;

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="wallPos">座標</param>
	/// <param name="scale">大きさ</param>
	/// <param name="wallAngle">壁の角度</param>
	Wall(const DirectX::SimpleMath::Vector3& wallPos, const DirectX::SimpleMath::Vector3& scale, const float& wallAngle);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Wall();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize();

	/// <summary>
	/// 描画を行う
	/// </summary>
	/// <param name="view"></param>
	/// <param name="proj"></param>
	void Draw(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj);

	/// <summary>
	/// 壁の当たり判定を取得する
	/// </summary>
	/// <returns>四角</returns>
	Collision::Shape::Box GetWallBox() { return m_wallBox; }
};
