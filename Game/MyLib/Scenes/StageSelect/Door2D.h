//
//		File Name ： Door2D.h
//		Production： 2023/10/25
//		Author　　： 石田 恭一	
//
#pragma once


class Door2D
{
	//	アクセサ
public:

	/// <summary>
	/// ドア座標を取得する
	/// </summary>
	/// <returns>座標</returns>
	inline DirectX::SimpleMath::Vector2 GetDoorPosition()	const { return m_doorPos; }

	//	定数
public:

	//	画像の真ん中の位置
	static const DirectX::SimpleMath::Vector2 ORIGIN_TEXTURE;
	//	移動速度
	static const float						  MOVE_SPEED;

	//	enum
public:

	//	どちらに動いた？
	enum class MOVE_DIRECTION
	{
		CENTER = 0,
		RIGHT = 1,
		LEFT = 2,
	};

	//	変数
private:

	//	ドアの写真
	ID3D11ShaderResourceView*		m_doorTexture;
	//	フォントの写真
	ID3D11ShaderResourceView*		m_fontTexture;
	//	画像の写真
	DirectX::SimpleMath::Vector2	m_doorPos;
	//	フォントの座標
	DirectX::SimpleMath::Vector2	m_fontPos;
	//	移動する際の目標値
	DirectX::SimpleMath::Vector2	m_doorTargetPos;
	//	移動距離
	float							m_distance;
	//	使用状態
	bool							m_used;
	//	どちらに移動したか
	MOVE_DIRECTION					m_moveState;

	//	関数
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="doorTexture">ドアの画像</param>
	/// <param name="fontTexture">フォントの画像</param>
	/// <param name="position">座標</param>
	/// <param name="distance">離れている距離</param>
	Door2D(ID3D11ShaderResourceView* doorTexture, ID3D11ShaderResourceView* fontTexture, const DirectX::SimpleMath::Vector2& position, const float& distance);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Door2D();

	/// <summary>
	/// 更新する
	/// </summary>
	void Update(bool used);

	/// <summary>
	/// 描画する
	/// </summary>
	/// <param name="scale">大きさ</param>
	void Draw(const DirectX::SimpleMath::Vector2& scale);

	/// <summary>
	/// 座標を決定する
	/// </summary>
	void TargetPosDecision(int state);

private:


};
