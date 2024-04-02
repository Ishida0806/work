#include "pch.h"
#include "WallFactory.h"
#include "Wall.h"

/// <summary>
/// �ǂ��쐬����
/// </summary>
/// <param name="position">���W</param>
/// <param name="angle">�p�x</param>
/// <returns>���L��</returns>
std::unique_ptr<Wall>WallFactory::CreateWall(
	const DirectX::SimpleMath::Vector3& position,
	const DirectX::SimpleMath::Vector3& scale,
	const float& angle
)
{
	//	�ǂ̏�����
	std::unique_ptr<Wall> walls;
	//	�v�f�̏�����
	walls.reset(new Wall(position, scale , angle));
	//	�v�f�̏�����
	walls->Initialize();
	// �ǃN���X�̃C���X�^���X��Ԃ�
	return std::move(walls);
}
