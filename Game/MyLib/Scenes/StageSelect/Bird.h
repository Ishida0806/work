//
//		File Name ： Bird.h
//		Production： 2023/11/25
//		Author　　： 石田 恭一	
//
#pragma once


class Bird final
{
	//	アクセサ
public:

	//	画像の真ん中
	static const DirectX::SimpleMath::Vector2  ORIGIN_BIRD_TEXTURE;
	//	座標の許容範囲
	static const DirectX::SimpleMath::Vector2  BIRD_POSITION_RANGE;
	//	目標座標
	static const DirectX::SimpleMath::Vector2  TARGET_POSITION;
	//	始まる座標
	static const DirectX::SimpleMath::Vector2  START_POSITION;
	//	鳥の右側
	static const RECT						   BIRD_TEXTURE_RIGHT;
	//	鳥の左側
	static const RECT						   BIRD_TEXTURE_LEFT;
	//	ランダムな大きさMIN
	static const float						   RANDOM_SCALE_MIN;
	//	ランダムな大きさMAX
	static const float						   RANDOM_SCALE_MAX;

	//	構造体
private:

	//	向きの処理をまとめた構造体
	struct isMove
	{
		//	右向き
		bool isRight;
		//	左向き
		bool isLeft;

		/// <summary>
		/// 向きを逆に変える
		/// </summary>
		void ReverseDirection()
		{
			if (isRight)
			{
				isLeft  = true;
				isRight = false;
			}
			else
			{
				isLeft  = false;
				isRight = true;
			}
		}

		/// <summary>
		/// 向きをリセットする
		/// </summary>
		void ResetDirection()
		{
			isLeft = false;
			isRight = false;
		}

		/// <summary>
		/// コンストラクタ
		/// </summary>
		isMove()
			:isRight(false),
			isLeft(false)
		{

		}
	};

	//	変数
private:

	//	座標
	DirectX::SimpleMath::Vector2	m_position;
	//	目標座標
	DirectX::SimpleMath::Vector2	m_targetPosition;
	//	おおきさ
	DirectX::SimpleMath::Vector2	m_scale;
	//	画像
	ID3D11ShaderResourceView*		m_birdTexture;
	//	向き
	isMove							m_isDirection;
	//	切り取り範囲
	RECT							m_birdRange;
	//	現在のステージ
	int								m_stage;
	//	角度
	float							m_angle;
	//	アルファ値
	float							m_alfa;
	//	次に移動するための時間
	float							m_startTime;
	//	移動が終了
	bool							m_isMoveFinished;
	//	活動範囲外ステートへいった
	bool							m_isOutsideState;

	//	関数
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Bird();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Bird();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="timer">タイマー</param>
	/// <param name="stageNum">ステージ番号/param>
	void Update(const DX::StepTimer& timer, const int& stageNum);

	/// <summary>
	/// 描画する
	/// </summary>
	void Draw();

	//	埋め込み関数
private:

	/// <summary>
	/// デバイス依存のリソースの初期化
	/// </summary>
	void CreateDeviceDependentResources();

	/// <summary>
	/// 飛ぶ準備を始める
	/// </summary>
	void GettingStartedBird();

	/// <summary>
	/// 向きをランダムに決める
	/// </summary>
	void RandomDiretion();

	/// <summary>
	/// 目標座標に到達したか確認する
	/// </summary>
	void CheckArriveTargetPosition();
	
	/// <summary>
	///  鳥が飛ぶのを始める
	/// </summary>
	/// <param name="timer">タイマー</param>
	void BeginFlyBird(const DX::StepTimer& timer);
};

