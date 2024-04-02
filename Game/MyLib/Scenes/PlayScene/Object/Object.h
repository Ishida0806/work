//
//		File Name ： Object.h
//		Production： 2023/6/03
//		Author　　： 石田 恭一	
//	
#pragma once

//	インターフェイスを宣言する
interface IObject
{
	//	仮想デストラクタ
	virtual ~IObject() = default;
	//	初期化処理
	virtual void Initialize() = 0;
	//	更新処理
	virtual void Update(const DX::StepTimer& timer) = 0;
	//	描画処理
	virtual void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj) = 0;
	//	終了処理	
	virtual void Finalize() = 0;
};

class Object : public IObject
{
	//	列挙型
public:

	// オブジェクトの種類
	enum class ObjectType
	{
		NormalEnemy,
		TackleEnemy,
		BossEnemy,
		Bullet,
		Player,
		Sord,
		Item
	};

	// コリジョンの形状
	enum class ColisionShape
	{
		Sphere,
		Box,
		Capsule
	};

	//	当たり判定の種類
	enum class ColisionType
	{
		NormalColision,
		AbilityColision,
		SearchColision,		
	};

	//	変数
private:
	//	座標
	DirectX::SimpleMath::Vector3									m_position;
	//	大きさ
	DirectX::SimpleMath::Vector3									m_scale;
	//	回転角
	DirectX::SimpleMath::Quaternion								    m_rotate;
	//	角度
	float															m_angle;
	//	識別子	
	ObjectType														m_objType;
	//	判定情報
	std::unordered_map<ColisionType, Collision::CollisionBehavior*> m_shapeColision;
		
	//	アクセサ
public:

	//	座標を取得する
	inline DirectX::SimpleMath::Vector3		GetPosition()   const { return m_position; }
	//	大きさを取得する
	inline DirectX::SimpleMath::Vector3		GetScale()		const { return m_scale; }
	//	回転角を取得する
	inline DirectX::SimpleMath::Quaternion  GetRotate()	    const { return m_rotate; }
	//	角度を取得する
	inline float							GetAngle()	    const { return m_angle; }
	//	IDを取得する
	inline ObjectType						GetType()	    const { return m_objType; }

	/// <summary>
	/// 通常の当たり判定を取得する
	/// </summary>
	/// <param name="type">当たり判定の種類</param>
	/// <param name="size">大きさ</param>
	/// <returns>ポインター<</returns>
	Collision::CollisionBehavior* GetColision(ColisionType type, unsigned int& size)	const;


	//	座標を設定する
	void SetPosition(const DirectX::SimpleMath::Vector3& position);
	//	移動量を設定する
	void SetVelocity(const DirectX::SimpleMath::Vector3& velocity);
	//	大きさを設定する
	void SetScale(const DirectX::SimpleMath::Vector3& scale);
	//	回転角を設定する
	void SetRotate(const DirectX::SimpleMath::Quaternion& rotate);
	//	角度を設定する
	void SetAngle(const float& angle);
	//	識別子を登録する
	void SetType(const Object::ObjectType& obj);

	//	関数
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Object();

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="position">座標</param>
	Object(const DirectX::SimpleMath::Vector3& position);

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="position">座標</param>
	/// <param name="rotate">回転角</param>
	Object(const DirectX::SimpleMath::Vector3& position , const DirectX::SimpleMath::Quaternion rotate);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Object() override;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="timer">タイマー</param>
	void Update(const DX::StepTimer& timer) override;

	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="view">ビュー</param>
	/// <param name="proj">プロジェクション</param>
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj) override;

	/// <summary>
	/// 終了処理
	/// </summary>
	void Finalize() override;

	/// <summary>
	/// 当たり判定を追加する
	/// </summary>
	/// <param name="behavior">当たり判定のポインター</param>
	/// <param name="type">当たり判定の種類</param>
	void AddColision(Collision::CollisionBehavior* behavior, ColisionType type)
	{
		m_shapeColision[type] = behavior;
	}
};