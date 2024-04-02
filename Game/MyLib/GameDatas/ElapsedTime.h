//
//		File Name ： ElapsedTime.h
//		Production： 2023/9/07
//		Author　　： 石田 恭一	
//
#pragma once

namespace MyLib
{
	//	経過時間を取得するクラス
	class ElapsedTime final
	{
		//	アクセサ
	public:

		// ElapsedTimeクラスのインスタンスを取得する
		static ElapsedTime* const GetInstance()
		{
			//	ヌルポなら生成
			if (m_elapsed == nullptr)
			{
				//	スクリーンクラスのインスタンスを生成する
				m_elapsed.reset(new ElapsedTime());
			}
			//	経過時間クラスのインスタンスを取得する
			return m_elapsed.get();
		}

		/// <summary>
		/// 経過時間を設定する
		/// </summary>
		/// <param name="elapsedTime">経過時間</param>
		inline void SetElapsedTime(float elapsedTime)
		{
			m_elapsedTime += elapsedTime;
		}

		//	経過時間を取得する
		inline float GetElapsedTime() const { return m_elapsedTime; }

		//	関数
	public:

		/// <summary>
		/// 経過時間を空にする
		/// </summary>
		void RestElapsedTime()
		{
			m_elapsedTime = 0.0f;
		}

		//	コンストラクタ
	private:

		ElapsedTime()
			:m_elapsedTime(0.0f)
		{

		}

		// 代入は許容しない
		void operator=(const ElapsedTime& object) = delete;
		// コピーコンストラクタは許容しない
		ElapsedTime(const ElapsedTime& object) = delete;

		//	変数
	private:

		// ElapsedTimeクラスのインスタンスへのポインタ
		static std::unique_ptr<ElapsedTime> m_elapsed;

		float m_elapsedTime;
	};
}

