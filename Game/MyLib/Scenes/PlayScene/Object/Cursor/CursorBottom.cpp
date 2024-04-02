//
//		File Name ： CursorBottom.cpp
//		Production： 2023/7/02
//		Author　　： 石田 恭一
// 
//		カーソル下部の処理をまとめたクラス
//
#include "pch.h"
#include "CursorBottom.h"
#include "CursorFactory.h"

//	拡大率
const float CursorBottom::FRICTION_SCALE = 5.0f;
//	カーソルの大きさ
const float CursorBottom::CURSOR_SCALE = 0.5f;
//	標準の大きさ
const DirectX::SimpleMath::Vector3 CursorBottom::BASE_SCALE = DirectX::SimpleMath::Vector3(0.5f);

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="parent">親</param>
/// <param name="position">座標</param>
/// <param name="rotate">回転角</param>
CursorBottom::CursorBottom(ICursorComponent* parent, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& rotate)
	:
	m_parent(parent),
	m_cursorBottomPosition(position),
	m_cursorBottomRotate(rotate),
	m_cursorBottomScale(CURSOR_SCALE),
	m_cursorBottomAngle(0.0f),
	m_second(0.0f),
	m_cursorBottomModel{},
	m_curorParts{}
{
	m_cursorBottomModel = MyLib::ResourcesData::GetInstance()->GatModel(L"cursorBottom");
}

/// <summary>
/// デストラクタ
/// </summary>
CursorBottom::~CursorBottom()
{
	

}

/// <summary>
/// 初期化処理
/// </summary>
void CursorBottom::Initialize()
{
	//	カーソルにカーソルの下を追加
	AddCurortPart(CursorFactory::CreateCursorTop(this, m_cursorBottomPosition, m_cursorBottomAngle));
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="timer">タイマー</param>
/// <param name="position">座標</param>
/// <param name="rotate">回転角</param>
void CursorBottom::Update(const DX::StepTimer& timer)
{
	//	座標 / 回転角を受け取る
	m_cursorBottomPosition = m_parent->GetPosition();
	m_cursorBottomRotate = m_parent->GetRotate();

	//	経過時間を足す
	m_second += static_cast<float>(timer.GetElapsedSeconds());

	//	カーソルに対して大きさをうごかす
	m_cursorBottomScale = DirectX::SimpleMath::Vector3::Lerp(BASE_SCALE, DirectX::SimpleMath::Vector3(0.1f), sin(FRICTION_SCALE * m_second));

	//	子供たちを動かす
	for (const auto& turretPart : m_curorParts)
	{
		turretPart->Update(timer);
	}
}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="view">ビュー</param>
/// <param name="proj">プロジェクション</param>
void CursorBottom::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{

	DirectX::SimpleMath::Matrix scale = DirectX::SimpleMath::Matrix::CreateScale(m_cursorBottomScale);
	DirectX::SimpleMath::Matrix trans = DirectX::SimpleMath::Matrix::CreateTranslation(m_cursorBottomPosition);
	DirectX::SimpleMath::Matrix rotate = DirectX::SimpleMath::Matrix::CreateRotationZ(m_cursorBottomAngle);
	DirectX::SimpleMath::Matrix world =  scale * trans;

	//	モデルの描画
	m_cursorBottomModel->Draw(
		MyLib::ScreenResources::GetInstance()->GetDeviceContext(),
		*MyLib::ScreenResources::GetInstance()->GetCommonState(),
		world,
		view,
		proj
	);
	//	子供たちも描画
	for (const auto& turretPart : m_curorParts)
	{
		turretPart->Render(view, proj);
	}
}

/// <summary>
/// 終了処理
/// </summary>
void CursorBottom::Finalize()
{
}

/// <summary>
/// パーツを追加
/// </summary>
/// <param name="cursorParts">子供</param>
void CursorBottom::AddCurortPart(std::unique_ptr<ICursorComponent> cursorParts)
{
	m_curorParts.push_back(std::move(cursorParts));
}
