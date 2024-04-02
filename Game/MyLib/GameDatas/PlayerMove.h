//
//		File Name ： PlayerMove.h
//		Production： 2023/1/30
//		Author　　： 石田 恭一	
//
#pragma once
class Player;

class PlayerMove
{
	//	アクセサ
public:

	//	ダッシュ中か？
	inline bool								 IsDash()					const { return m_isDash; }
	//	歩いているか？
	inline bool								 IsWalk()					const { return m_isWalk; }

	//	変数
private:

	//	プレイヤー
	Player*											 m_player;
	//	ダッシュ中か？
	bool											 m_isDash;
	//	歩いているか？
	bool											 m_isWalk;

	//	関数
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="player">プレイヤー</param>
	PlayerMove(Player* player);

	//	デストラクタ
	~PlayerMove() = default;

	//	プレイヤーだけが使える
protected:

	/// <summary>
	/// プレイヤーの移動処理
	/// </summary>
	void MovePlayer();
};