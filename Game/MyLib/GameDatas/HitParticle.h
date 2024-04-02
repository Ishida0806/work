
#pragma once

class HitParticle
{
	//	アクセサ
public:

	//	座標を取得する
	inline  DirectX::SimpleMath::Vector3 GetPosition()	const { return m_position; }
	//	移動量を取得する
	inline  DirectX::SimpleMath::Vector3 GetVelocity()	const { return m_velocity; }
	//	加速度を取得する
	inline  DirectX::SimpleMath::Vector3 GetAccele()	const { return m_accele; }
	//	現在の大きさを取得する
	inline  DirectX::SimpleMath::Vector3 GetNowScale()	const { return m_nowScale; }
	//	スタート時の大きさを所得する
	inline  DirectX::SimpleMath::Vector3 GetStartScale()const { return m_startScale; }
	//	エンド時の大きさを所得する
	inline  DirectX::SimpleMath::Vector3 GetEndScale()	const { return m_endScale; }
	//	生存時間を取得する
	inline  float GetLife()								const { return m_life; }
	//	スタート時の生存時間を取得する
	inline  float GetStartLife()						const { return m_startLife; }
	//	現在の色を取得する
	inline  DirectX::SimpleMath::Color GetNowColor()	const { return m_nowColor; }
	//	スタート時の色を取得する
	inline  DirectX::SimpleMath::Color GetStartColor()	const { return m_startColor; }
	//	エンド時の色を取得する
	inline  DirectX::SimpleMath::Color GetEndColor()	const { return m_endColor; }

private:
	//	座標
	DirectX::SimpleMath::Vector3	m_position;

	//	速度
	DirectX::SimpleMath::Vector3	m_velocity;
	DirectX::SimpleMath::Vector3	m_memorryVelocity;
	//	加速度
	DirectX::SimpleMath::Vector3	m_accele;
	DirectX::SimpleMath::Vector3	m_memorryAcccele;

	//	スケール
	DirectX::SimpleMath::Vector3	m_nowScale;
	DirectX::SimpleMath::Vector3	m_startScale;
	DirectX::SimpleMath::Vector3	m_endScale;

	//	カラー
	DirectX::SimpleMath::Color		m_nowColor;
	DirectX::SimpleMath::Color		m_startColor;
	DirectX::SimpleMath::Color		m_endColor;

	//	生存時間
	float							m_life;
	float							m_startLife;

public:

	/// <summary>
	/// コンストラクタ
	/// 引数は初期設定用の数値
	/// </summary>
	/// <param name="life">生存時間</param>
	/// <param name="pos">座標</param>
	/// <param name="velocity">速度</param>
	/// <param name="accele">加速度</param>
	/// <param name="startScale">初期サイズ</param>
	/// <param name="endScale">最終サイズ</param>
	/// <param name="startColor">初期色</param>
	/// <param name="endColor">最終色</param>
	HitParticle(
		float life,
		DirectX::SimpleMath::Vector3 pos,
		DirectX::SimpleMath::Vector3 velocity,
		DirectX::SimpleMath::Vector3 accele,
		DirectX::SimpleMath::Vector3 startScale, DirectX::SimpleMath::Vector3 endScale,
		DirectX::SimpleMath::Color startColor, DirectX::SimpleMath::Color endColor
	);
	~HitParticle();

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="timer">タイマー</param>
	void Update(const DX::StepTimer& timer);


	/// <summary>
	///  エフェクトを開始する
	/// </summary>
	/// <param name="position">座標</param>
	void StartEffect(DirectX::SimpleMath::Vector3 position);
};

