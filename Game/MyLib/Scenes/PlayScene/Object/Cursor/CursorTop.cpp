//
//		File Name �F CursorTop.cpp
//		Production�F 2023/7/02
//		Author�@�@�F �Γc ����
// 
//		�J�[�\���̏㕔�̋@�\�܂Ƃ߂��N���X
// 
//
#include "pch.h"
#include "CursorTop.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="parent">�e</param>
/// <param name="position">���W</param>
/// <param name="angle">�p�x</param>
CursorTop::CursorTop(ICursorComponent* parent, const DirectX::SimpleMath::Vector3& position, const float& angle)
	:m_parent(parent),
	m_cursorTopPosition(position),
	m_cursorTopAngle(angle),
	m_cursorTopModel{},
	m_second(0.0f)
{
	using namespace DirectX::SimpleMath;

	m_cursorTopRotate = Quaternion::FromToRotation(Vector3(Vector3::UnitY), -Vector3::UnitY);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
CursorTop::~CursorTop()
{
}

/// <summary>
/// ����������
/// </summary>
void CursorTop::Initialize()
{
	//	���f�����擾����
	m_cursorTopModel = MyLib::ResourcesData::GetInstance()->GatModel(L"cursorTop");
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="timer">�^�C�}�[</param>
/// <param name="position">���W</param>
/// <param name="rotate">��]�p</param>
void CursorTop::Update(const DX::StepTimer& timer)
{
	using namespace DirectX::SimpleMath;
	//	�o�ߎ��Ԃ𑫂�
	m_second += static_cast<float>(timer.GetElapsedSeconds());
	//	���W�󂯎��
	m_cursorTopPosition = m_parent->GetPosition();
	//	Y�����T�C���g�ŗh�炷
	m_cursorTopPosition.y += 1.0f + sinf(m_second * 4.0f);
	//	�p�x����
	m_cursorTopRotate	   *= Quaternion::CreateFromAxisAngle(Vector3::UnitY, DirectX::XMConvertToRadians(3.f)) * m_parent->GetRotate();
}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="view">�r���[</param>
/// <param name="proj">�v���W�F�N�V����</param>
void CursorTop::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	// �I�t�Z�b�g��]�s��̍쐬�iZ���𒆐S��180�x��]�j
	DirectX::SimpleMath::Matrix offsetRotation = DirectX::SimpleMath::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(180.0f));
	// �ړ��s��̍쐬
	DirectX::SimpleMath::Matrix trans = DirectX::SimpleMath::Matrix::CreateTranslation(m_cursorTopPosition);
	// ��]�s��̍쐬
	DirectX::SimpleMath::Matrix rotate = DirectX::SimpleMath::Matrix::CreateFromQuaternion(m_cursorTopRotate) * offsetRotation;
	// ���[���h�s��̍쐬�i�X�P�[���A��]�A�ړ���K�p�j
	DirectX::SimpleMath::Matrix world = rotate * trans;

	// ���f���̕`��
	m_cursorTopModel->Draw
	(
		MyLib::ScreenResources::GetInstance()->GetDeviceContext(),
		*MyLib::ScreenResources::GetInstance()->GetCommonState(),
		world,
		view,
		proj
	);
}

/// <summary>
/// �I������
/// </summary>
void CursorTop::Finalize()
{
}

/// <summary>
/// �J�[�\���̎q����ǉ�
/// </summary>
/// <param name="cursorParts"></param>
void CursorTop::AddCurortPart(std::unique_ptr<ICursorComponent> cursorParts)
{
	m_curorParts.push_back(std::move(cursorParts));
}
