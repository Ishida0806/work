//
//		File Name ： Utility.h
//		Production： 2023/8/22
//		Author　　： 石田 恭一
// 
//		便利関数を集めたクラス
//
#pragma once

class Utility final
{
public:

	/// <summary>
	/// ランダムを生成する
	/// </summary>
	/// <param name="min">最小値</param>
	/// <param name="max">最大値</param>
	/// <returns>ランダムな値</returns>
	inline static float CreateRandom(float min , float max)
	{
		std::random_device rd;
		std::default_random_engine eng(rd());
		std::uniform_real_distribution<float> distribution(min, max);

		return distribution(eng);
	}

	template <class T>
	/// <summary>
	/// クランプ
	/// </summary>
	/// <param name="num">値</param>
	/// <param name="min">最小値</param>
	/// <param name="max">最大値</param>
	/// <returns>値</returns>
	inline static T Clamp(T num, T min, T max)
	{
		return std::max(min, std::min(num, max));
	}

	/// <summary>
	/// 線形補間する
	/// </summary>
	/// <param name="start">最初</param>
	/// <param name="end">最後</param>
	/// <param name="t">どの程度の時間か</param>
	/// <returns>値</returns>
	inline static float Lerp(const float& start, const float& end, const float& t)
	{
		return (1.0f - t) * start + t * end;
	}
};