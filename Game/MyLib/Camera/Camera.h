//
//		File Name �F Camera.h
//		Production�F 2023/9/07
//		Author�@�@�F �Γc ����	
//
#pragma once
#include "Game/MyLib/GameDatas/FiniteStateMachine.h"

class Player;

class Camera
{
	//	�萔
public:

	//	���������̃I�t�Z�b�g
	static const DirectX::SimpleMath::Vector3 DASH_OFFSET_POSITION;

	//	�񋓌^
public:

	//	�J�����̃X�e�[�g
	enum class CameraState
	{
		Idle  = 0,
		Shake = 1,
		Fade  = 2,
		Death = 3,
		Win	  = 4,

		OverID
	};

	//	�G�C���A�X�錾
public:

	using CAMERASTATE  = FiniteStateMachine<Camera, Camera::CameraState>;
	using ICAMERASTATE = CAMERASTATE::IState;

	// �A�N�Z�T
public:

	inline  CAMERASTATE*				GetFSM()					 const { return m_fsm.get(); }
	// �J�����̈ʒu���擾
	inline DirectX::SimpleMath::Vector3 GetEyePosition()			 const { return m_eye; }
	// �J�����̒����_���擾
	inline DirectX::SimpleMath::Vector3 GetTargetPosition()			 const { return m_target; }

	inline DirectX::SimpleMath::Vector3 GetOrijinalTargetPosition()  const { return m_originalTarget; }
	//	�h��Ă��邩
	inline bool							IsShake()					 const { return m_isShake; }
	//	�t�F�[�h����
	inline bool							IsFade()					 const { return m_isFade; }
	//	�f�X�J��������
	inline bool							IsDeathCamera()				 const { return m_isDeathCamera; }

	//	�^�[�Q�b�g��ݒ肷��
	void SetOrijinalTargetPosition(const DirectX::SimpleMath::Vector3& position);
	//	�Ǐ]�^�[�Q�b�g��ݒ肷��
	void SetTargetPosition(const DirectX::SimpleMath::Vector3& position);
	//	�A�C��ݒ肷��
	void SetEyePosition(const DirectX::SimpleMath::Vector3& position);
	//	�h�炷���[�h��߂�
	void CompletedShake();
	//	�f�X�J�������擾
	void InDeathCamera();

	//	�ϐ�
private:

	//	�L���X�e�[�g�}�V�[��
	std::unique_ptr<CAMERASTATE> m_fsm;
	// �^�[�Q�b�g
	DirectX::SimpleMath::Vector3 m_originalTarget;
	// ���_
	DirectX::SimpleMath::Vector3 m_eye;
	// �����_
	DirectX::SimpleMath::Vector3 m_target;
	// �����
	DirectX::SimpleMath::Vector3 m_up;
	//	�v���C���[
	Player*						 m_player;
	//	�V�F�C�N����
	bool						 m_isShake;
	//	�f�X�J��������
	bool						 m_isDeathCamera;
	//	�t�F�[�h����
	bool						 m_isFade;

	//	�֐�
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="eye">�J�����ʒu</param>
	/// <param name="target">���_���W</param>
	/// <param name="up">������x�N�g��</param>
	/// <param name="player">�v���C���[</param>
	Camera
	(
		const DirectX::SimpleMath::Vector3& eye,
		const DirectX::SimpleMath::Vector3& target,
	    const DirectX::SimpleMath::Vector3& up,
		Player*								player
	);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Camera();

	/// <summary>
	/// ����������
	/// </summary>
	void Initialize();
	
	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="timer">�^�C�}�[</param>
	/// <param name="isFade">�t�F�[�h�����H</param>
	void Update(const DX::StepTimer& timer, const bool& isFade);
};