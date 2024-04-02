//
//		File Name ： ItemCapsule.cpp
//		Production： 2023/12/06
//		Author　　： 石田 恭一	
//
#include "pch.h"
#include "ItemCapsule.h"
#include "ItemCapsuleFactory.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="parent">親</param>
ItemCapsule::ItemCapsule(Object* parent)
	:m_parent(parent)
{
}

/// <summary>
/// デストラクタ
/// </summary>
ItemCapsule::~ItemCapsule()
{
}

/// <summary>
/// 初期化処理
/// </summary>
void ItemCapsule::Initialize()
{
	//	パーツを追加
	m_parts.push_back(ItemCapsuleFactory::CreateItemCapsuleBottom(m_parent));
	m_parts.push_back(ItemCapsuleFactory::CreateItemCapsuleTop(m_parent));
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="timer">タイマー</param>
void ItemCapsule::Update(const DX::StepTimer& timer)
{
	for (const auto& part : m_parts) part->Update(timer);
}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="view">ビュー</param>
/// <param name="proj">プロジェクション</param>
void ItemCapsule::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	for (const auto& part : m_parts) part->Render(view, proj);
}

/// <summary>
/// 終了処理
/// </summary>
void ItemCapsule::Finalize()
{
	for (const auto& part : m_parts) part->Finalize();
}
