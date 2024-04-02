//
//		File Name �F IBulletFactroy.h
//		Production�F 2023/7/02
//		Author�@�@�F �Γc ����
// 
#pragma once

class Bullet;

//	�C���^�[�t�F�C�X�̎������s��
__interface IBulletFactory
{
public:
	// �w�肳�ꂽ�C�e�z��𐶐�����
	std::vector<std::unique_ptr<Bullet>> CreateBullets(
		int ownerID,
		const int& number,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& rotate,
		const DirectX::SimpleMath::Color&,
		int power,
		float scale,
		bool used
	);
};