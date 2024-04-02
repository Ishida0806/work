#pragma once

#include "WallFactory.h"
#include "IWallFactory.h"

class WallFactory;
__interface IWallFactory;

class Wall final
{
	//	�萔
public:
	static const DirectX::SimpleMath::Vector3 WALL_SCALE;

	//	�ϐ�
private:
	//	���W
	DirectX::SimpleMath::Vector3	m_wallPos;
	//	�傫��
	DirectX::SimpleMath::Vector3	m_wallScale;
	//	���f��
	DirectX::Model*				m_wallModel;
	//	�X�N���[�����\�[�X
	MyLib::ScreenResources*		m_screen;
	//	�ǂ̂����蔻��
	Collision::Shape::Box			m_wallBox;
	//	�p�x
	float						m_wallAngle;

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="wallPos">���W</param>
	/// <param name="scale">�傫��</param>
	/// <param name="wallAngle">�ǂ̊p�x</param>
	Wall(const DirectX::SimpleMath::Vector3& wallPos, const DirectX::SimpleMath::Vector3& scale, const float& wallAngle);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Wall();

	/// <summary>
	/// ����������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �`����s��
	/// </summary>
	/// <param name="view"></param>
	/// <param name="proj"></param>
	void Draw(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj);

	/// <summary>
	/// �ǂ̓����蔻����擾����
	/// </summary>
	/// <returns>�l�p</returns>
	Collision::Shape::Box GetWallBox() { return m_wallBox; }
};
