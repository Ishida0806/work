//
//		File Name �F CursorBottom.cpp
//		Production�F 2023/7/02
//		Author�@�@�F �Γc ����
// 
//		�J�[�\�������̏������܂Ƃ߂��N���X
//
#include "pch.h"
#include "CursorBottom.h"
#include "CursorFactory.h"

//	�g�嗦
const float CursorBottom::FRICTION_SCALE = 5.0f;
//	�J�[�\���̑傫��
const float CursorBottom::CURSOR_SCALE = 0.5f;
//	�W���̑傫��
const DirectX::SimpleMath::Vector3 CursorBottom::BASE_SCALE = DirectX::SimpleMath::Vector3(0.5f);

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="parent">�e</param>
/// <param name="position">���W</param>
/// <param name="rotate">��]�p</param>
CursorBottom::CursorBottom(ICursorComponent* parent, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& rotate)
	:
	m_parent(parent),
	m_cursorBottomPosition(position),
	m_cursorBottomRotate(rotate),
	m_cursorBottomScale(CURSOR_SCALE),
	m_cursorBottomAngle(0.0f),
	m_second(0.0f),
	m_cursorBottomModel{},
	m_curorParts{}
{
	m_cursorBottomModel = MyLib::ResourcesData::GetInstance()->GatModel(L"cursorBottom");
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
CursorBottom::~CursorBottom()
{
	

}

/// <summary>
/// ����������
/// </summary>
void CursorBottom::Initialize()
{
	//	�J�[�\���ɃJ�[�\���̉���ǉ�
	AddCurortPart(CursorFactory::CreateCursorTop(this, m_cursorBottomPosition, m_cursorBottomAngle));
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="timer">�^�C�}�[</param>
/// <param name="position">���W</param>
/// <param name="rotate">��]�p</param>
void CursorBottom::Update(const DX::StepTimer& timer)
{
	//	���W / ��]�p���󂯎��
	m_cursorBottomPosition = m_parent->GetPosition();
	m_cursorBottomRotate = m_parent->GetRotate();

	//	�o�ߎ��Ԃ𑫂�
	m_second += static_cast<float>(timer.GetElapsedSeconds());

	//	�J�[�\���ɑ΂��đ傫������������
	m_cursorBottomScale = DirectX::SimpleMath::Vector3::Lerp(BASE_SCALE, DirectX::SimpleMath::Vector3(0.1f), sin(FRICTION_SCALE * m_second));

	//	�q�������𓮂���
	for (const auto& turretPart : m_curorParts)
	{
		turretPart->Update(timer);
	}
}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="view">�r���[</param>
/// <param name="proj">�v���W�F�N�V����</param>
void CursorBottom::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{

	DirectX::SimpleMath::Matrix scale = DirectX::SimpleMath::Matrix::CreateScale(m_cursorBottomScale);
	DirectX::SimpleMath::Matrix trans = DirectX::SimpleMath::Matrix::CreateTranslation(m_cursorBottomPosition);
	DirectX::SimpleMath::Matrix rotate = DirectX::SimpleMath::Matrix::CreateRotationZ(m_cursorBottomAngle);
	DirectX::SimpleMath::Matrix world =  scale * trans;

	//	���f���̕`��
	m_cursorBottomModel->Draw(
		MyLib::ScreenResources::GetInstance()->GetDeviceContext(),
		*MyLib::ScreenResources::GetInstance()->GetCommonState(),
		world,
		view,
		proj
	);
	//	�q���������`��
	for (const auto& turretPart : m_curorParts)
	{
		turretPart->Render(view, proj);
	}
}

/// <summary>
/// �I������
/// </summary>
void CursorBottom::Finalize()
{
}

/// <summary>
/// �p�[�c��ǉ�
/// </summary>
/// <param name="cursorParts">�q��</param>
void CursorBottom::AddCurortPart(std::unique_ptr<ICursorComponent> cursorParts)
{
	m_curorParts.push_back(std::move(cursorParts));
}
