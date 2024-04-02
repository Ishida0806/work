//
//		File Name �F BulletFactroy.h
//		Production�F 2023/7/02
//		Author�@�@�F �Γc ����
// 
#pragma once

#include "Game/MyLib/Scenes/PlayScene/Object/Bullet/IBulletFactroy.h"

class BulletFactory : public IBulletFactory
{
public:
	//	�v���C���[�̒e�F
	static const DirectX::SimpleMath::Color PLAYER_BULLETS_COLOR;
	static const DirectX::SimpleMath::Color ENEMY_BULLETS_COLOR;
	static const DirectX::SimpleMath::Color BOSS_BULLETS_COLOR;

public:
	//	�N���������Ă��邩
	enum class OwnerID
	{
		ENEMY = 0,
		BOSS  = 1,

		OVER
	};

public:

	/// <summary>
	/// �w�肳�ꂽ�C�e�z��𐶐�����
	/// </summary>
	/// <param name="ownerID">�I�[�i�[</param>
	/// <param name="position">���W</param>
	/// <param name="rotate">��]�p</param>
	/// <param name="color">�F</param>
	/// <param name="power">��</param>
	/// <param name="scale">�傫��</param>
	/// <param name="used">�g�p���</param>
	/// <returns>�쐬���ꂽ�A�h���X�E���L��</returns>
	static std::unique_ptr<Bullet> CreateBullets(
		OwnerID ownerID,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& rotate,
		const DirectX::SimpleMath::Color& color,
		int power,
		float scale,
		bool  used = false
	);
};