//
//		File Name ： ItemCapsuleTop.cpp
//		Production： 2023/12/06
//		Author　　： 石田 恭一	
//
#include "pch.h"
#include "ItemCapsuleTop.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="Object">親</param>
ItemCapsuleTop::ItemCapsuleTop(Object* parent)
	:m_parent(parent),
	m_model(nullptr)
{
}

/// <summary>
/// デストラクタ
/// </summary>
ItemCapsuleTop::~ItemCapsuleTop()
{
}

/// <summary>
/// 初期化処理
/// </summary>
void ItemCapsuleTop::Initialize()
{
	m_model = MyLib::ResourcesData::GetInstance()->GatModel(L"capsuleTop");
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="timer">タイマー</param>
void ItemCapsuleTop::Update(const DX::StepTimer& timer)
{
	UNREFERENCED_PARAMETER(timer);
}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="view">ビュー</param>
/// <param name="proj">プロジェクション</param>
void ItemCapsuleTop::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	MyLib::ScreenResources* scren = MyLib::ScreenResources::GetInstance();
	//	スケーリング行列を作成する
	DirectX::SimpleMath::Matrix scale = DirectX::SimpleMath::Matrix::CreateScale(m_parent->GetScale());
	//	移動行列を作成	
	DirectX::SimpleMath::Matrix trans = DirectX::SimpleMath::Matrix::CreateTranslation(m_parent->GetPosition());
	//	回転行列を作成
	DirectX::SimpleMath::Matrix roate = DirectX::SimpleMath::Matrix::CreateFromQuaternion(m_parent->GetRotate());
	//	ワールド行列を作成
	DirectX::SimpleMath::Matrix world = scale * roate * trans;

	//	描画を行う
	m_model->Draw
	(
		scren->GetDeviceContext(),
		*scren->GetCommonState(),
		world,
		view,
		proj
	);
}

/// <summary>
/// 終了処理
/// </summary>
void ItemCapsuleTop::Finalize()
{
}
