//
//		File Name ： CursorTop.cpp
//		Production： 2023/7/02
//		Author　　： 石田 恭一
// 
//		カーソルの上部の機能まとめたクラス
// 
//
#include "pch.h"
#include "CursorTop.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="parent">親</param>
/// <param name="position">座標</param>
/// <param name="angle">角度</param>
CursorTop::CursorTop(ICursorComponent* parent, const DirectX::SimpleMath::Vector3& position, const float& angle)
	:m_parent(parent),
	m_cursorTopPosition(position),
	m_cursorTopAngle(angle),
	m_cursorTopModel{},
	m_second(0.0f)
{
	using namespace DirectX::SimpleMath;

	m_cursorTopRotate = Quaternion::FromToRotation(Vector3(Vector3::UnitY), -Vector3::UnitY);
}

/// <summary>
/// デストラクタ
/// </summary>
CursorTop::~CursorTop()
{
}

/// <summary>
/// 初期化処理
/// </summary>
void CursorTop::Initialize()
{
	//	モデルを取得する
	m_cursorTopModel = MyLib::ResourcesData::GetInstance()->GatModel(L"cursorTop");
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="timer">タイマー</param>
/// <param name="position">座標</param>
/// <param name="rotate">回転角</param>
void CursorTop::Update(const DX::StepTimer& timer)
{
	using namespace DirectX::SimpleMath;
	//	経過時間を足す
	m_second += static_cast<float>(timer.GetElapsedSeconds());
	//	座標受け取り
	m_cursorTopPosition = m_parent->GetPosition();
	//	Y軸をサイン波で揺らす
	m_cursorTopPosition.y += 1.0f + sinf(m_second * 4.0f);
	//	角度を回す
	m_cursorTopRotate	   *= Quaternion::CreateFromAxisAngle(Vector3::UnitY, DirectX::XMConvertToRadians(3.f)) * m_parent->GetRotate();
}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="view">ビュー</param>
/// <param name="proj">プロジェクション</param>
void CursorTop::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	// オフセット回転行列の作成（Z軸を中心に180度回転）
	DirectX::SimpleMath::Matrix offsetRotation = DirectX::SimpleMath::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(180.0f));
	// 移動行列の作成
	DirectX::SimpleMath::Matrix trans = DirectX::SimpleMath::Matrix::CreateTranslation(m_cursorTopPosition);
	// 回転行列の作成
	DirectX::SimpleMath::Matrix rotate = DirectX::SimpleMath::Matrix::CreateFromQuaternion(m_cursorTopRotate) * offsetRotation;
	// ワールド行列の作成（スケール、回転、移動を適用）
	DirectX::SimpleMath::Matrix world = rotate * trans;

	// モデルの描画
	m_cursorTopModel->Draw
	(
		MyLib::ScreenResources::GetInstance()->GetDeviceContext(),
		*MyLib::ScreenResources::GetInstance()->GetCommonState(),
		world,
		view,
		proj
	);
}

/// <summary>
/// 終了処理
/// </summary>
void CursorTop::Finalize()
{
}

/// <summary>
/// カーソルの子供を追加
/// </summary>
/// <param name="cursorParts"></param>
void CursorTop::AddCurortPart(std::unique_ptr<ICursorComponent> cursorParts)
{
	m_curorParts.push_back(std::move(cursorParts));
}
