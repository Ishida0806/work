#include "pch.h"
#include "Cursor.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="position">座標</param>
/// <param name="rotate">回転角</param>
/// <param name="angle">角度</param>
Cursor::Cursor(const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& rotate, const float angle)
	:m_cursorPosition(position)
	,m_cursorRotate(rotate)
	,m_cursorAngle(angle)
{
}

/// <summary>
/// デストラクタ
/// </summary>
Cursor::~Cursor()
{

}

/// <summary>
/// 初期化処理
/// </summary>
void Cursor::Initialize()
{
	//	カーソルにカーソル下を追加
	AddCurortPart(CursorFactory::CreateCursorBottom(this, m_cursorPosition, m_cursorRotate));

	//	三角ポリゴンを設定
	DirectX::SimpleMath::Vector3 V0(-50.f, 0, -50.f);

	DirectX::SimpleMath::Vector3 V1(-50.f, 0, 50.f);
	DirectX::SimpleMath::Vector3 V2(50.f, 0, 50.f);
	DirectX::SimpleMath::Vector3 V3(50.f, 0, -50.f);

	m_tri1.Set(V0, V2, V1);
	m_tri2.Set(V0, V3, V2);
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="timer">タイマー</param>
void Cursor::Update(const DX::StepTimer& timer)
{
	//	カーソルの作成
	CreatePosCursor();

	//	カーソルたちのいける座標を制限する
	m_cursorPosition.x = Utility::Clamp(m_cursorPosition.x, -24.0f, 24.0f);
	m_cursorPosition.z = Utility::Clamp(m_cursorPosition.z, -24.0f, 24.0f);

	//　カーソルたちを更新する
	m_curorParts->Update(timer);
}

/// <summary>
/// 角度回転計算
/// </summary>
/// <param name="position">座標</param>
/// <param name="angle">角度</param>
void Cursor::CalculateAngleRotate(const DirectX::SimpleMath::Vector3& position, float& angle)
{
	DirectX::SimpleMath::Vector3 vec = position - m_cursorPosition;

	// ベクトルの X 軸と Y 軸の成分から角度を計算する
	angle = -std::atan2(vec.y, vec.x) + DirectX::XMConvertToRadians(180.f);
}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="view">ビュー</param>
/// <param name="proj">プロジェクション</param>
void Cursor::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	m_curorParts->Render(view, proj);
}

/// <summary>
/// 終了処理
/// </summary>
void Cursor::Finalize()
{

}

/// <summary>
/// カーソルの作成
/// </summary>
void Cursor::CreatePosCursor()
{
	//	マウスの状態を取得
	auto state = DirectX::Mouse::Get().GetState();
	//	スクリーンリソース
	auto ScreenResource = MyLib::ScreenResources::GetInstance();
	//	画面サイズの取得
	RECT size = ScreenResource->GetDeviceResources()->GetOutputSize();
	//	スクリーンからワールドに変換
	DirectX::SimpleMath::Matrix screen = CreateMatrixScreen2WorldPos(
		size.right,
		size.bottom,
		ScreenResource->GetViewMatrix(),
		ScreenResource->GetProjectionMatrix()
	);
	//	マウスの座標情報を
	DirectX::SimpleMath::Vector3 mouse_pos_start = DirectX::SimpleMath::Vector3(static_cast<float>(state.x), static_cast<float>(state.y), 0.0f);
	DirectX::SimpleMath::Vector3 mouse_pos_end = DirectX::SimpleMath::Vector3(static_cast<float>(state.x), static_cast<float>(state.y), 1.0f);
	//	Vecter３型の線分情報に変換する
	mouse_pos_start = DirectX::SimpleMath::Vector3::Transform(mouse_pos_start, screen);
	mouse_pos_end = DirectX::SimpleMath::Vector3::Transform(mouse_pos_end, screen);

	m_mouseSegementPos.start = mouse_pos_start;
	m_mouseSegementPos.end   = mouse_pos_end;

	if (!IntersectSegmentAndTriangle(m_mouseSegementPos.start, m_mouseSegementPos.end, m_tri1, &m_cursorPosition))
	{
		IntersectSegmentAndTriangle(m_mouseSegementPos.start, m_mouseSegementPos.end, m_tri2, &m_cursorPosition);
	}
}

/// <summary>
/// ローカル座標からワールド座標に変換する
/// </summary>
/// <param name="screen_w">スクリーンの横</param>
/// <param name="screen_h">スクリーンの高さ</param>
/// <param name="view">ビュー</param>
/// <param name="projection">プロジェクション</param>
/// <returns>戻り値：ワールド行列</returns>
DirectX::SimpleMath::Matrix Cursor::CreateMatrixScreen2WorldPos(
	int screen_w, 
	int screen_h,
	const DirectX::SimpleMath::Matrix& view, 
	const DirectX::SimpleMath::Matrix& proj
)
{
	// ビューポートスケーリング行列を作成
	DirectX::SimpleMath::Matrix viewport;
	viewport._11 = screen_w / 2.0f;
	viewport._22 = -screen_h / 2.0f;
	viewport._41 = screen_w / 2.0f;
	viewport._42 = screen_h / 2.0f;
	// 逆行列を作成
	DirectX::SimpleMath::Matrix invertScale = viewport.Invert();
	DirectX::SimpleMath::Matrix invertVProj = proj.Invert();
	DirectX::SimpleMath::Matrix invertView = view.Invert();
	// ビューポートスケーリング行列の逆行列 × 射影行列の逆行列 × ビュー行列の逆行列
	return invertScale * invertVProj * invertView;
}

/// <summary>
// 線分と三角形の交差判定
/// </summary>
/// <param name="p">線分始点</param>
/// <param name="q">線分終点</param>
/// <param name="tri">三角形</param>
/// <param name="s">線分と三角形の交差点</param>
bool Cursor::IntersectSegmentAndTriangle(DirectX::SimpleMath::Vector3 p, DirectX::SimpleMath::Vector3 q, Collision::Shape::Triangle tri, DirectX::SimpleMath::Vector3* s)
{
	// 点pと三角形の面との距離を計算
	float distp = p.Dot(tri.p.Normal()) + tri.p.D();
	if (distp < 0.0f) return false;
	// 点qと三角形の面との距離を計算
	float distq = q.Dot(tri.p.Normal()) + tri.p.D();
	if (distq >= 0.0f) return false;
	// 距離の差を計算
	float denom = distp - distq;
	// 線分上の交点を計算
	float t = distp / denom;
	*s = p + t * (q - p);
	// 交点と辺BCの平面との内積を計算
	float u = s->Dot(tri.edgePlaneBC.Normal()) + tri.edgePlaneBC.D();
	if (fabsf(u) < FLT_EPSILON) u = 0.0f;
	if (u < 0.0f || u > 1.0f) return false;
	// 交点と辺CAの平面との内積を計算
	float v = s->Dot(tri.edgePlaneCA.Normal()) + tri.edgePlaneCA.D();
	if (fabsf(v) < FLT_EPSILON) v = 0.0f;
	if (v < 0.0f) return false;
	// 交点と辺ABの平面との内積から残りの重みを計算
	float w = 1.0f - u - v;
	if (fabsf(w) < FLT_EPSILON) w = 0.0f;
	if (w < 0.0f) return false;
	// すべての条件を満たす場合、線分と三角形は交差している
	return true;
}

/// <summary>
/// パーツを追加
/// </summary>
/// <param name="cursorParts">子供</param>
void Cursor::AddCurortPart(std::unique_ptr<ICursorComponent> cursorParts)
{
	m_curorParts = std::move(cursorParts);
}