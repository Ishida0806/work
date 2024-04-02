
#include "pch.h"
#include "Wall.h"

//	�ǂ̑傫��
const DirectX::SimpleMath::Vector3 Wall::WALL_SCALE = DirectX::SimpleMath::Vector3(17.0f, 7.f, 30.0f);

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="wallPos">���W</param>
/// <param name="scale">�傫��</param>
/// <param name="wallAngle">�ǂ̊p�x</param>
Wall::Wall(const DirectX::SimpleMath::Vector3& wallPos, const DirectX::SimpleMath::Vector3& scale, const float& wallAngle)
	:m_wallPos(wallPos),
	m_wallScale(scale),
	m_wallAngle(wallAngle),
	m_wallModel(nullptr),
	m_screen(nullptr),
	m_wallBox()
{
	//	�X�N���[�����\�[�X
	m_screen = MyLib::ScreenResources::GetInstance();
	//	���f�����擾����
	m_wallModel = MyLib::ResourcesData::GetInstance()->GatModel(L"wall");
	//	�ꏊ�Ɣ͈͂�ݒ肷��
	m_wallBox.center  = m_wallPos;
	m_wallBox.extents = m_wallScale;	
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Wall::~Wall()
{
}

/// <summary>
/// ����������
/// </summary>
void Wall::Initialize()
{
}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="view">�r���[</param>
/// <param name="proj">�v���W�F�N�V����</param>
void Wall::Draw(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	using namespace DirectX::SimpleMath;
	//	�g��s����쐬����
	Matrix scale = Matrix::CreateScale(WALL_SCALE);
	//	�ړ��s����쐬
	Matrix trans = Matrix::CreateTranslation(m_wallPos);
	//	��]�s����쐬
	Matrix rotate = Matrix::CreateRotationY(m_wallAngle);
	//	���[���h�s����쐬
	Matrix world = scale * rotate * trans;
	//	���f���̕`��
	m_wallModel->Draw(m_screen->GetDeviceContext(),*m_screen->GetCommonState(), world, view, proj);
}
