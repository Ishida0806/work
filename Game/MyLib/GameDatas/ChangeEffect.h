//
//		File Name ： ChangeEffect.h
//		Production： 2023/1/10
//		Author　　： 石田 恭一	
//
#pragma once
#include "pch.h"

class ChangeEffect
{
	//	列挙型
public:

	//	シーン遷移のタイプ
	enum class ChangeSceneFadeType
	{
		None = 0,

		To	= 1,
		Out	= 2,

		OverID
	};

	//	シーンタイプ
	enum class ChangeSceneType
	{
		None = 0,

		Title   = 1,
		Select  = 2,
		Play	= 3,
		Result  = 4,

		OverID
	};

	//	アクセサ
public:

	//	切り替えるタイプ
	inline ChangeSceneType			  GetChangeType()		const	{ return m_changeType; }
	//	シーンのフェードタイプを取得する
	inline ChangeSceneFadeType		  GetChangeFadeType()	const	{ return m_fadeType; }
	//	画像の取得する
	inline ID3D11ShaderResourceView*  GetTexture()			const	{ return m_texture; }
	//	カラーを取得する
	inline DirectX::SimpleMath::Color GetColor()			const	{ return m_color; }
	//	経過時間を取得
	inline float					  GetElapsedTime()		const	{ return m_elapsedTime; }
	//	カラーを設定する
	void SetColor(const DirectX::SimpleMath::Color& color)			{ m_color = color; }
	//	シーンのフェードタイプを設定する
	void SetSceneFadeType(const ChangeSceneFadeType& fadeType)		{ m_fadeType = fadeType; }
	//	カラーをラープで設定する
	void SetLerpColor(const DirectX::SimpleMath::Color& color)		{ m_color = DirectX::SimpleMath::Color::Lerp(m_color, color, 0.1f); }
	//	画像を設定する
	void SetTexure(ID3D11ShaderResourceView* texture)				{ m_texture = texture; }
	//	経過時間をリセット
	void ResetElapseTime()											{ m_elapsedTime = 0.0f; }


	//	変数
private:

	//	画像
	ID3D11ShaderResourceView*	m_texture;
	//	シーン遷移の際のタイプ
	ChangeSceneType				m_changeType;
	//	シーンを変えるタイプ
	ChangeSceneFadeType			m_fadeType;
	//	カラー
	DirectX::SimpleMath::Color	m_color;
	//	経過時間
	float						m_elapsedTime;

	//	関数
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="changeType">切り替えのタイプ</param>
	ChangeEffect(const ChangeSceneType& changeType)
		:m_changeType(changeType),
		m_fadeType(ChangeSceneFadeType::None),
		m_elapsedTime(0.0f),
		m_texture(nullptr)
	{
		m_color = DirectX::SimpleMath::Color(0.0f, 0.0f, 0.0f, 0.0f);
	}

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~ChangeEffect() = default;

	/// <summary>
	///	初期化処理
	/// </summary>
	virtual void Initialize()
	{

	}

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="timer">タイマー</param>
	void UpdateElapsedTime(const DX::StepTimer& timer)
	{
		m_elapsedTime += static_cast<float>(timer.GetElapsedSeconds());
	}

	/// <summary>
	/// そのシーンに遷移する
	/// </summary>
	virtual void ToChange() = 0;

	/// <summary>
	/// シーンを抜ける
	/// </summary>
	virtual void OutChange()= 0;

	/// <summary>
	/// 描画のタイプ
	/// </summary>
	virtual void Draw()
	{

	};

	/// <summary>
	/// 事前の初期化を行う
	/// </summary>
	virtual void PreInitialize() {};

	/// <summary>
	/// カラーと時間をリセットする
	/// </summary>
	void ResetColorAndTime()
	{
		m_color = DirectX::SimpleMath::Color(0.0f, 0.0f, 0.0f, 0.0f);

		m_elapsedTime = 0.0f;
	}

	/// <summary>
	/// カラーをラープでリセットする
	/// </summary>
	void ResetLerpColor()
	{
		m_color = DirectX::SimpleMath::Color::Lerp(m_color, DirectX::SimpleMath::Color(0.0f, 0.0f, 0.0f, 0.0f), 0.03f);
	}

protected:

	/// <summary>
	/// シーンのフェードを終了する
	/// </summary>
	void FinishedChangeScene()
	{
		//	時間と色はリセット
		ResetColorAndTime();
		//	終了する
		m_fadeType = ChangeSceneFadeType::None;
	}
};