#include "pch.h"
#include "Cursor.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="position">���W</param>
/// <param name="rotate">��]�p</param>
/// <param name="angle">�p�x</param>
Cursor::Cursor(const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& rotate, const float angle)
	:m_cursorPosition(position)
	,m_cursorRotate(rotate)
	,m_cursorAngle(angle)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Cursor::~Cursor()
{

}

/// <summary>
/// ����������
/// </summary>
void Cursor::Initialize()
{
	//	�J�[�\���ɃJ�[�\������ǉ�
	AddCurortPart(CursorFactory::CreateCursorBottom(this, m_cursorPosition, m_cursorRotate));

	//	�O�p�|���S����ݒ�
	DirectX::SimpleMath::Vector3 V0(-50.f, 0, -50.f);

	DirectX::SimpleMath::Vector3 V1(-50.f, 0, 50.f);
	DirectX::SimpleMath::Vector3 V2(50.f, 0, 50.f);
	DirectX::SimpleMath::Vector3 V3(50.f, 0, -50.f);

	m_tri1.Set(V0, V2, V1);
	m_tri2.Set(V0, V3, V2);
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void Cursor::Update(const DX::StepTimer& timer)
{
	//	�J�[�\���̍쐬
	CreatePosCursor();

	//	�J�[�\�������̂�������W�𐧌�����
	m_cursorPosition.x = Utility::Clamp(m_cursorPosition.x, -24.0f, 24.0f);
	m_cursorPosition.z = Utility::Clamp(m_cursorPosition.z, -24.0f, 24.0f);

	//�@�J�[�\���������X�V����
	m_curorParts->Update(timer);
}

/// <summary>
/// �p�x��]�v�Z
/// </summary>
/// <param name="position">���W</param>
/// <param name="angle">�p�x</param>
void Cursor::CalculateAngleRotate(const DirectX::SimpleMath::Vector3& position, float& angle)
{
	DirectX::SimpleMath::Vector3 vec = position - m_cursorPosition;

	// �x�N�g���� X ���� Y ���̐�������p�x���v�Z����
	angle = -std::atan2(vec.y, vec.x) + DirectX::XMConvertToRadians(180.f);
}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="view">�r���[</param>
/// <param name="proj">�v���W�F�N�V����</param>
void Cursor::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	m_curorParts->Render(view, proj);
}

/// <summary>
/// �I������
/// </summary>
void Cursor::Finalize()
{

}

/// <summary>
/// �J�[�\���̍쐬
/// </summary>
void Cursor::CreatePosCursor()
{
	//	�}�E�X�̏�Ԃ��擾
	auto state = DirectX::Mouse::Get().GetState();
	//	�X�N���[�����\�[�X
	auto ScreenResource = MyLib::ScreenResources::GetInstance();
	//	��ʃT�C�Y�̎擾
	RECT size = ScreenResource->GetDeviceResources()->GetOutputSize();
	//	�X�N���[�����烏�[���h�ɕϊ�
	DirectX::SimpleMath::Matrix screen = CreateMatrixScreen2WorldPos(
		size.right,
		size.bottom,
		ScreenResource->GetViewMatrix(),
		ScreenResource->GetProjectionMatrix()
	);
	//	�}�E�X�̍��W����
	DirectX::SimpleMath::Vector3 mouse_pos_start = DirectX::SimpleMath::Vector3(static_cast<float>(state.x), static_cast<float>(state.y), 0.0f);
	DirectX::SimpleMath::Vector3 mouse_pos_end = DirectX::SimpleMath::Vector3(static_cast<float>(state.x), static_cast<float>(state.y), 1.0f);
	//	Vecter�R�^�̐������ɕϊ�����
	mouse_pos_start = DirectX::SimpleMath::Vector3::Transform(mouse_pos_start, screen);
	mouse_pos_end = DirectX::SimpleMath::Vector3::Transform(mouse_pos_end, screen);

	m_mouseSegementPos.start = mouse_pos_start;
	m_mouseSegementPos.end   = mouse_pos_end;

	if (!IntersectSegmentAndTriangle(m_mouseSegementPos.start, m_mouseSegementPos.end, m_tri1, &m_cursorPosition))
	{
		IntersectSegmentAndTriangle(m_mouseSegementPos.start, m_mouseSegementPos.end, m_tri2, &m_cursorPosition);
	}
}

/// <summary>
/// ���[�J�����W���烏�[���h���W�ɕϊ�����
/// </summary>
/// <param name="screen_w">�X�N���[���̉�</param>
/// <param name="screen_h">�X�N���[���̍���</param>
/// <param name="view">�r���[</param>
/// <param name="projection">�v���W�F�N�V����</param>
/// <returns>�߂�l�F���[���h�s��</returns>
DirectX::SimpleMath::Matrix Cursor::CreateMatrixScreen2WorldPos(
	int screen_w, 
	int screen_h,
	const DirectX::SimpleMath::Matrix& view, 
	const DirectX::SimpleMath::Matrix& proj
)
{
	// �r���[�|�[�g�X�P�[�����O�s����쐬
	DirectX::SimpleMath::Matrix viewport;
	viewport._11 = screen_w / 2.0f;
	viewport._22 = -screen_h / 2.0f;
	viewport._41 = screen_w / 2.0f;
	viewport._42 = screen_h / 2.0f;
	// �t�s����쐬
	DirectX::SimpleMath::Matrix invertScale = viewport.Invert();
	DirectX::SimpleMath::Matrix invertVProj = proj.Invert();
	DirectX::SimpleMath::Matrix invertView = view.Invert();
	// �r���[�|�[�g�X�P�[�����O�s��̋t�s�� �~ �ˉe�s��̋t�s�� �~ �r���[�s��̋t�s��
	return invertScale * invertVProj * invertView;
}

/// <summary>
// �����ƎO�p�`�̌�������
/// </summary>
/// <param name="p">�����n�_</param>
/// <param name="q">�����I�_</param>
/// <param name="tri">�O�p�`</param>
/// <param name="s">�����ƎO�p�`�̌����_</param>
bool Cursor::IntersectSegmentAndTriangle(DirectX::SimpleMath::Vector3 p, DirectX::SimpleMath::Vector3 q, Collision::Shape::Triangle tri, DirectX::SimpleMath::Vector3* s)
{
	// �_p�ƎO�p�`�̖ʂƂ̋������v�Z
	float distp = p.Dot(tri.p.Normal()) + tri.p.D();
	if (distp < 0.0f) return false;
	// �_q�ƎO�p�`�̖ʂƂ̋������v�Z
	float distq = q.Dot(tri.p.Normal()) + tri.p.D();
	if (distq >= 0.0f) return false;
	// �����̍����v�Z
	float denom = distp - distq;
	// ������̌�_���v�Z
	float t = distp / denom;
	*s = p + t * (q - p);
	// ��_�ƕ�BC�̕��ʂƂ̓��ς��v�Z
	float u = s->Dot(tri.edgePlaneBC.Normal()) + tri.edgePlaneBC.D();
	if (fabsf(u) < FLT_EPSILON) u = 0.0f;
	if (u < 0.0f || u > 1.0f) return false;
	// ��_�ƕ�CA�̕��ʂƂ̓��ς��v�Z
	float v = s->Dot(tri.edgePlaneCA.Normal()) + tri.edgePlaneCA.D();
	if (fabsf(v) < FLT_EPSILON) v = 0.0f;
	if (v < 0.0f) return false;
	// ��_�ƕ�AB�̕��ʂƂ̓��ς���c��̏d�݂��v�Z
	float w = 1.0f - u - v;
	if (fabsf(w) < FLT_EPSILON) w = 0.0f;
	if (w < 0.0f) return false;
	// ���ׂĂ̏����𖞂����ꍇ�A�����ƎO�p�`�͌������Ă���
	return true;
}

/// <summary>
/// �p�[�c��ǉ�
/// </summary>
/// <param name="cursorParts">�q��</param>
void Cursor::AddCurortPart(std::unique_ptr<ICursorComponent> cursorParts)
{
	m_curorParts = std::move(cursorParts);
}