//
//		File Name �F WinCamera.cpp
//		Production�F 2023/6/09
//		Author�@�@�F �Γc ����	
// 
//		�Q�[���J�����̎������s�����N���X
//
//////////////////////////////////////////////////////////////////////////
//						Camera�̃N���X									// 
//////////////////////////////////////////////////////////////////////////
#include "pch.h"
#include "WinCamera.h"

//	�J�����̈ʒu�ւ̋����ɑ΂��銄��
const float WinCamera::EYE_RATE = 0.03f;
//	�����_�ւ̋����ɑ΂��銄��
const float WinCamera::TARGET_RATE = 0.1f;

/// <summary>
/// �R���X�g���N�^
/// </summary>
WinCamera::WinCamera()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
WinCamera::~WinCamera()
{
    using namespace DirectX::SimpleMath;

    // �E�B���h�E�T�C�Y���擾����
    RECT size = MyLib::ScreenResources::GetInstance()->GetDeviceResources()->GetOutputSize();

    float Near = 0.1f;
    float Far = 1200.0f;

    // �v���W�F�N�V�����𐶐�����
    MyLib::ScreenResources::GetInstance()->SetProjectionMatrix
    (
        Matrix::CreatePerspectiveFieldOfView
        (
            DirectX::XMConvertToRadians(45.0f),
            static_cast<float>(size.right) / static_cast<float>(size.bottom),
            Near,
            Far
        )
    );
}

/// <summary>
/// ����ւ��O�ɌĂяo��
/// </summary>
/// <param name="finiteStateMachine">�I�[�i�[</param>
void WinCamera::Enter(Camera::CAMERASTATE* finiteStateMachine)
{
	UNREFERENCED_PARAMETER(finiteStateMachine);

    using namespace DirectX::SimpleMath;

    // �E�B���h�E�T�C�Y���擾����
    RECT size = MyLib::ScreenResources::GetInstance()->GetDeviceResources()->GetOutputSize();

    float Near = 0.1f;
    float Far = 1200.0f;

    // �v���W�F�N�V�����𐶐�����
    MyLib::ScreenResources::GetInstance()->SetProjectionMatrix
    (
        Matrix::CreatePerspectiveFieldOfView
        (
            DirectX::XMConvertToRadians(100.0f),
            static_cast<float>(size.right) / static_cast<float>(size.bottom),
            Near,
            Far
        )
    );
}

/// <summary>
/// ���s����
/// </summary>
/// <param name="finiteStateMachine">�I�[�i�[<</param>
/// <param name="elapsedTime">�o�ߎ���</param>
void WinCamera::Execute(Camera::CAMERASTATE* finiteStateMachine, const DX::StepTimer& timer)
{
	UNREFERENCED_PARAMETER(timer);
	//	�J�������擾����
	Camera* camera = finiteStateMachine->GetOwner();
	//	�Ǐ]�^�[�Q�b�g
	DirectX::SimpleMath::Vector3 target = finiteStateMachine->GetOwner()->GetOrijinalTargetPosition();

    //  �J�������v���C���[�ɂǃA�b�v������
	target.z = target.z - 7.0f;
	target.y = target.y - 16.0f;
	target.x = target.x - 0.0f;

	//	�^�[�Q�b�g�̒Ǐ]
	camera->SetTargetPosition(DirectX::SimpleMath::Vector3::Lerp(camera->GetTargetPosition(), target, TARGET_RATE));
	camera->SetEyePosition(DirectX::SimpleMath::Vector3::Lerp(camera->GetEyePosition(),		  target, EYE_RATE));
}

/// <summary>
/// �ޏo���̏���
/// </summary>
/// <param name="finiteStateMachine">�I�[�i�[</param>
void WinCamera::Exit(Camera::CAMERASTATE* finiteStateMachine)
{
	UNREFERENCED_PARAMETER(finiteStateMachine);
}
