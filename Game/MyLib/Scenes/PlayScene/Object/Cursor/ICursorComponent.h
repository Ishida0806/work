#pragma once

//	インターフェイスを宣言する
interface ICursorComponent
{
	// 親を取得する
	virtual ICursorComponent* GetParent() = 0;
	// 位置を取得する
	virtual DirectX::SimpleMath::Vector3	GetPosition() = 0;
	//	回転角を設定する
	virtual DirectX::SimpleMath::Quaternion GetRotate() = 0;
	// 回転角を取得する
	virtual float GetAngle() = 0;
	// モデルを取得する
	virtual DirectX::Model* GetModel() = 0;
	//	仮想デストラクタ
	virtual ~ICursorComponent() = default;
	//	初期化処理
	virtual void Initialize() = 0;
	//	更新処理
	virtual void Update(const DX::StepTimer& timer) = 0;
	//	描画処理
	virtual void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj) = 0;
	//	終了処理	
	virtual void Finalize() = 0;
};