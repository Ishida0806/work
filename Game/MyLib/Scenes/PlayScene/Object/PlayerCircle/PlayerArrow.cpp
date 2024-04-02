//
//		File Name �F PlayerArrow.cpp
//		Production�F 2023/11/03
//		Author�@�@�F �Γc ����	
// 
//		�J�[�\���̂������\�����̏���
//	
#include "pch.h"
#include "PlayerArrow.h"

//	���̈ړ����x
const float PlayerArrow::MOVE_ARROW_SPEED = 0.2f;
//	���̉�]�p��Z
const float PlayerArrow::ARROW_ROTATE_Z   = 2.0f;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="parent">�e</param>
/// <param name="arrowModel">��󃂃f��</param>
/// <param name="cursolPosition">�J�[�\���̍��W</param>
/// <param name="cursolRotate">�J�[�\���̉�]�p</param>
PlayerArrow::PlayerArrow(
	Object* parent,
	DirectX::Model* arrowModel,
	DirectX::SimpleMath::Vector3* cursolPosition,
	DirectX::SimpleMath::Quaternion* cursolRotate
) 
	:m_parent(parent),
	m_arrowModel(arrowModel),
	m_cursolPosition(cursolPosition),
	m_cursolRotate(cursolRotate),
	m_circleAngle(0.0f),
	m_arrowAngle(0.0f)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayerArrow::~PlayerArrow()
{
}

/// <summary>
/// ����������
/// </summary>
void PlayerArrow::Initialize()
{
	m_arrowModel->UpdateEffects
	(
		[&](DirectX::IEffect* effect)
		{
			//	�x�[�V�b�N�G�t�F�N�g
			auto basicEffect = dynamic_cast<DirectX::BasicEffect*>(effect);
			//	�|�C���^�͑��݂��邩�H
			if (basicEffect)
			{
				//	����
				basicEffect->SetAmbientLightColor(DirectX::Colors::White);
			}
		}
	);
}

/// <summary>
/// �X�V����
/// </summary>
void PlayerArrow::Update(const DX::StepTimer& timer)
{
	timer;
	//	���t���[����
	m_arrowAngle  -= DirectX::XMConvertToRadians(ARROW_ROTATE_Z);
	//	
	m_circleAngle -= DirectX::XMConvertToRadians(ARROW_ROTATE_Z);
	//	�ړ���
	DirectX::SimpleMath::Vector3 vel;
	//	�e�N���X����擾����
	m_position = m_parent->GetPosition();
	//	�������Z�o����
	DirectX::SimpleMath::Vector3 dir = m_parent->GetPosition() - *m_cursolPosition;
	//	���W����p�x�ɕϊ����� �f�O���[�p���90�x����Ă���̂ŕ␳
	float  cursolAngle = -atan2(dir.z, dir.x) - DirectX::XMConvertToRadians(90.0f);
	//	�����W���W
	vel.x = m_parent->GetPosition().x + 4.0f * sinf(cursolAngle);
	vel.z = m_parent->GetPosition().z + 4.0f * cosf(cursolAngle);
	//	�����W�ɂ������ړ�
	m_arrowPosition = DirectX::SimpleMath::Vector3::Lerp(m_arrowPosition, vel, MOVE_ARROW_SPEED);
}

/// <summary>
/// �`�悷��
/// </summary>
/// <param name="view">�r���[</param>
/// <param name="proj">�v���W�F�N�V����</param>
void PlayerArrow::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	using namespace DirectX::SimpleMath;

	//	�X�N���[�����\�[�X
	MyLib::ScreenResources* screen = MyLib::ScreenResources::GetInstance();

	//	�ړ��s��
	//Matrix trans = Matrix::CreateTranslation(m_position);
	////	��]
	//Matrix roate = Matrix::CreateRotationY(m_circleAngle);
	////	���[���h�s��
	//Matrix world = roate * trans;
	////	���f���̕`��
	//m_circleModel->Draw
	//(
	//	screen->GetDeviceContext(),
	//	*screen->GetCommonState(),
	//	world,
	//	view,
	//	proj
	//);

	//	���̍s��
	Matrix arrowWorld = Matrix::CreateRotationZ(m_arrowAngle) * Matrix::CreateFromQuaternion(*m_cursolRotate) * Matrix::CreateTranslation(m_arrowPosition);
	//	���f���̕`�悷��
	m_arrowModel->Draw
	(
		screen->GetDeviceContext(),
		*screen->GetCommonState(),
		arrowWorld,
		view,
		proj
	);
}

/// <summary>
/// �I������
/// </summary>
void PlayerArrow::Finalize()
{
}
