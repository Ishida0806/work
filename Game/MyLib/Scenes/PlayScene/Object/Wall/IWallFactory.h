#pragma once

class Wall;

// �C���^�t�F�[�X���`����
__interface IWallFactory
{
	// �u�ǁv�𐶐�����
	std::unique_ptr<Wall> CreateWall(
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Vector3& scale,
		const float& angle
	);
};
