//
//		File Name �F Utility.h
//		Production�F 2023/8/22
//		Author�@�@�F �Γc ����
// 
//		�֗��֐����W�߂��N���X
//
#pragma once

class Utility final
{
public:

	/// <summary>
	/// �����_���𐶐�����
	/// </summary>
	/// <param name="min">�ŏ��l</param>
	/// <param name="max">�ő�l</param>
	/// <returns>�����_���Ȓl</returns>
	inline static float CreateRandom(float min , float max)
	{
		std::random_device rd;
		std::default_random_engine eng(rd());
		std::uniform_real_distribution<float> distribution(min, max);

		return distribution(eng);
	}

	template <class T>
	/// <summary>
	/// �N�����v
	/// </summary>
	/// <param name="num">�l</param>
	/// <param name="min">�ŏ��l</param>
	/// <param name="max">�ő�l</param>
	/// <returns>�l</returns>
	inline static T Clamp(T num, T min, T max)
	{
		return std::max(min, std::min(num, max));
	}

	/// <summary>
	/// ���`��Ԃ���
	/// </summary>
	/// <param name="start">�ŏ�</param>
	/// <param name="end">�Ō�</param>
	/// <param name="t">�ǂ̒��x�̎��Ԃ�</param>
	/// <returns>�l</returns>
	inline static float Lerp(const float& start, const float& end, const float& t)
	{
		return (1.0f - t) * start + t * end;
	}
};