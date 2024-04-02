//
//		File Name �F Bird.h
//		Production�F 2023/11/25
//		Author�@�@�F �Γc ����	
//
#pragma once


class Bird final
{
	//	�A�N�Z�T
public:

	//	�摜�̐^��
	static const DirectX::SimpleMath::Vector2  ORIGIN_BIRD_TEXTURE;
	//	���W�̋��e�͈�
	static const DirectX::SimpleMath::Vector2  BIRD_POSITION_RANGE;
	//	�ڕW���W
	static const DirectX::SimpleMath::Vector2  TARGET_POSITION;
	//	�n�܂���W
	static const DirectX::SimpleMath::Vector2  START_POSITION;
	//	���̉E��
	static const RECT						   BIRD_TEXTURE_RIGHT;
	//	���̍���
	static const RECT						   BIRD_TEXTURE_LEFT;
	//	�����_���ȑ傫��MIN
	static const float						   RANDOM_SCALE_MIN;
	//	�����_���ȑ傫��MAX
	static const float						   RANDOM_SCALE_MAX;

	//	�\����
private:

	//	�����̏������܂Ƃ߂��\����
	struct isMove
	{
		//	�E����
		bool isRight;
		//	������
		bool isLeft;

		/// <summary>
		/// �������t�ɕς���
		/// </summary>
		void ReverseDirection()
		{
			if (isRight)
			{
				isLeft  = true;
				isRight = false;
			}
			else
			{
				isLeft  = false;
				isRight = true;
			}
		}

		/// <summary>
		/// ���������Z�b�g����
		/// </summary>
		void ResetDirection()
		{
			isLeft = false;
			isRight = false;
		}

		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		isMove()
			:isRight(false),
			isLeft(false)
		{

		}
	};

	//	�ϐ�
private:

	//	���W
	DirectX::SimpleMath::Vector2	m_position;
	//	�ڕW���W
	DirectX::SimpleMath::Vector2	m_targetPosition;
	//	��������
	DirectX::SimpleMath::Vector2	m_scale;
	//	�摜
	ID3D11ShaderResourceView*		m_birdTexture;
	//	����
	isMove							m_isDirection;
	//	�؂���͈�
	RECT							m_birdRange;
	//	���݂̃X�e�[�W
	int								m_stage;
	//	�p�x
	float							m_angle;
	//	�A���t�@�l
	float							m_alfa;
	//	���Ɉړ����邽�߂̎���
	float							m_startTime;
	//	�ړ����I��
	bool							m_isMoveFinished;
	//	�����͈͊O�X�e�[�g�ւ�����
	bool							m_isOutsideState;

	//	�֐�
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Bird();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Bird();

	/// <summary>
	/// ����������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="timer">�^�C�}�[</param>
	/// <param name="stageNum">�X�e�[�W�ԍ�/param>
	void Update(const DX::StepTimer& timer, const int& stageNum);

	/// <summary>
	/// �`�悷��
	/// </summary>
	void Draw();

	//	���ߍ��݊֐�
private:

	/// <summary>
	/// �f�o�C�X�ˑ��̃��\�[�X�̏�����
	/// </summary>
	void CreateDeviceDependentResources();

	/// <summary>
	/// ��ԏ������n�߂�
	/// </summary>
	void GettingStartedBird();

	/// <summary>
	/// �����������_���Ɍ��߂�
	/// </summary>
	void RandomDiretion();

	/// <summary>
	/// �ڕW���W�ɓ��B�������m�F����
	/// </summary>
	void CheckArriveTargetPosition();
	
	/// <summary>
	///  ������Ԃ̂��n�߂�
	/// </summary>
	/// <param name="timer">�^�C�}�[</param>
	void BeginFlyBird(const DX::StepTimer& timer);
};

