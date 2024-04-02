
#include "pch.h"
#include "Wall.h"

//	壁の大きさ
const DirectX::SimpleMath::Vector3 Wall::WALL_SCALE = DirectX::SimpleMath::Vector3(17.0f, 7.f, 30.0f);

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="wallPos">座標</param>
/// <param name="scale">大きさ</param>
/// <param name="wallAngle">壁の角度</param>
Wall::Wall(const DirectX::SimpleMath::Vector3& wallPos, const DirectX::SimpleMath::Vector3& scale, const float& wallAngle)
	:m_wallPos(wallPos),
	m_wallScale(scale),
	m_wallAngle(wallAngle),
	m_wallModel(nullptr),
	m_screen(nullptr),
	m_wallBox()
{
	//	スクリーンリソース
	m_screen = MyLib::ScreenResources::GetInstance();
	//	モデルを取得する
	m_wallModel = MyLib::ResourcesData::GetInstance()->GatModel(L"wall");
	//	場所と範囲を設定する
	m_wallBox.center  = m_wallPos;
	m_wallBox.extents = m_wallScale;	
}

/// <summary>
/// デストラクタ
/// </summary>
Wall::~Wall()
{
}

/// <summary>
/// 初期化処理
/// </summary>
void Wall::Initialize()
{
}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="view">ビュー</param>
/// <param name="proj">プロジェクション</param>
void Wall::Draw(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	using namespace DirectX::SimpleMath;
	//	拡大行列を作成する
	Matrix scale = Matrix::CreateScale(WALL_SCALE);
	//	移動行列を作成
	Matrix trans = Matrix::CreateTranslation(m_wallPos);
	//	回転行列を作成
	Matrix rotate = Matrix::CreateRotationY(m_wallAngle);
	//	ワールド行列を作成
	Matrix world = scale * rotate * trans;
	//	モデルの描画
	m_wallModel->Draw(m_screen->GetDeviceContext(),*m_screen->GetCommonState(), world, view, proj);
}
