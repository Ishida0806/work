//
//		File Name �F Bird.cpp
//		Production�F 2023/11/25
//		Author�@�@�F �Γc ����	
//
#include "pch.h"
#include "Bird.h"

#include "StageSelectScene.h"

//	�摜�̐^��
const DirectX::SimpleMath::Vector2 Bird::ORIGIN_BIRD_TEXTURE = DirectX::SimpleMath::Vector2(170.5f, 45.5f);
//	�ڕW���W
const DirectX::SimpleMath::Vector2 Bird::TARGET_POSITION	 = DirectX::SimpleMath::Vector2(2500.0f, 560.0f);
//	�n�܂���W
const DirectX::SimpleMath::Vector2 Bird::START_POSITION		 = DirectX::SimpleMath::Vector2(-500.0f, 0.0f);
//	���W�̋��e�͈�
const DirectX::SimpleMath::Vector2 Bird::BIRD_POSITION_RANGE = DirectX::SimpleMath::Vector2(10.0f, 3.0f);
//	���̉E��
const RECT						   Bird::BIRD_TEXTURE_RIGHT = { 170, 0, 341, 91 };
//	���̍���
const RECT						   Bird::BIRD_TEXTURE_LEFT  = { 0,   0, 170, 91 };
//	�����_���ȑ傫��MIN
const float						   Bird::RANDOM_SCALE_MIN = 0.3f;
//	�����_���ȑ傫��MAX
const float						   Bird::RANDOM_SCALE_MAX = 0.8f;
/// <summary>
/// �R���X�g���N�^
/// </summary>
Bird::Bird()
	:m_birdTexture(nullptr),
	m_angle(0.0f),
	m_alfa(1.0f),
	m_startTime(0.0f),
	m_isDirection{},
	m_birdRange{},
	m_isMoveFinished(false),
	m_isOutsideState(false)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Bird::~Bird()
{
}

/// <summary>
/// ����������
/// </summary>
void Bird::Initialize()
{
	CreateDeviceDependentResources();
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="timer">�^�C�}�[</param>
/// <param name="stageNum">�X�e�[�W�ԍ�/param>
void Bird::Update(const DX::StepTimer& timer, const int& stageNum)
{
	m_stage = stageNum;

	//	�X�e�[�W�^�ɃL���X�g
	StageSelectScene::CHOOSE_STAGE stageSelect = static_cast<StageSelectScene::CHOOSE_STAGE>(m_stage);
	//	�X�e�[�W�́@3�@||�@4�@��?
	if (stageSelect == StageSelectScene::CHOOSE_STAGE::STAGE_4 || stageSelect == StageSelectScene::CHOOSE_STAGE::STAGE_3)
	{
		//	�����͈͊O�ւ�����
		m_isOutsideState = true;
		//	�A���t�@�l��������
		m_alfa = Utility::Lerp(m_alfa, 0.0f, 0.1f);
		//	�X�e�[�W3�ȍ~�͋A��  
		return;
	}
	else
	{
		//	�͈͊O����߂������̏���
		if (m_isOutsideState)	GettingStartedBird();
		//	����ȊO��1�ɖ߂�
		m_alfa = Utility::Lerp(m_alfa, 1.0f, 0.1f);
	}

	//	���W�Ɉړ�����
	m_position = DirectX::SimpleMath::Vector2::Lerp(m_position, m_targetPosition, 0.003f);

	// �ڕW���W�ɓ��B�������m�F����
	CheckArriveTargetPosition();
	//  ������Ԃ̂��n�߂�
	BeginFlyBird(timer);
}

/// <summary>
/// �`�悷��
/// </summary>
void Bird::Draw()
{
	//	�X�v���C�g�o�b�`
	DirectX::SpriteBatch* spriteBatch = MyLib::ScreenResources::GetInstance()->GetSpriteBatch();
	//	�`����s��
	spriteBatch->Draw
	(
		m_birdTexture,
		m_position,
		&m_birdRange,
		DirectX::SimpleMath::Color(m_alfa, m_alfa, m_alfa, m_alfa),
		DirectX::XMConvertToRadians(00.0f),
		ORIGIN_BIRD_TEXTURE,
		m_scale
	);
}

/// <summary>
/// �f�o�C�X�ˑ��̃��\�[�X�̏�����
/// </summary>
void Bird::CreateDeviceDependentResources()
{
	//	�摜
	m_birdTexture = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"Bird");

	// �����������_���Ɍ��߂�
	RandomDiretion();

	//	�傫���������_���Ō��߂�
	float random = Utility::CreateRandom(RANDOM_SCALE_MIN, RANDOM_SCALE_MAX);
	m_scale = DirectX::SimpleMath::Vector2(random, random);
}

/// <summary>
/// ��ԏ������n�߂�
/// </summary>
void Bird::GettingStartedBird()
{
	//	�͈͓��ɖ߂���
	m_isOutsideState = false;
	//	���������Z�b�g����
	m_isDirection.ResetDirection();
	//	�傫���������_���Ō��߂�
	float random = Utility::CreateRandom(RANDOM_SCALE_MIN, RANDOM_SCALE_MAX);
	m_scale = DirectX::SimpleMath::Vector2(random, random);
	// �����������_���Ɍ��߂�
	RandomDiretion();
}

/// <summary>
/// �����������_���Ɍ��߂�
/// </summary>
void Bird::RandomDiretion()
{
	//	�����_���łǂ��炩��n�߂邩���߂�
	if (rand() % 2 == 0)
	{
		m_targetPosition = START_POSITION;
		m_position = TARGET_POSITION;
		m_birdRange = BIRD_TEXTURE_LEFT;
		m_isDirection.isLeft = true;
	}
	else
	{
		m_position = START_POSITION;
		m_targetPosition = TARGET_POSITION;
		m_birdRange = BIRD_TEXTURE_RIGHT;
		m_isDirection.isRight = true;
	}
}

/// <summary>
/// �ڕW���W�ɓ��B�������m�F����
/// </summary>
void Bird::CheckArriveTargetPosition()
{
	//	���������s���Ȃ̂ŋA��
	if (m_isMoveFinished)	return;

	int w,h;

	MyLib::ScreenResources::GetInstance()->GetScreenSize(w, h);

	//	�����͂ǂ���
	if (m_isDirection.isRight)
	{
		if (m_position.x >= w)
		{
			m_isMoveFinished = true;
			//	���s���鎞�Ԃ̓����_���Ō��߂�
			m_startTime = Utility::CreateRandom(1.0f, 3.0f);
		}
	}
	else
	{
		if (m_position.x <= BIRD_POSITION_RANGE.x)
		{
			m_isMoveFinished = true;
			//	���s���鎞�Ԃ̓����_���Ō��߂�
			m_startTime = Utility::CreateRandom(1.0f, 3.0f);
		}
	}
}

/// <summary>
///  ������Ԃ̂��n�߂�
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void Bird::BeginFlyBird(const DX::StepTimer& timer)
{
	//	�ړ����I�����Ă��Ȃ��Ȃ�A��
	if (!m_isMoveFinished)	return;

	//	�o�ߎ��Ԃ������Ă���
	m_startTime -= static_cast<float>(timer.GetElapsedSeconds());

	//	0����Ȃ�A��
	if (m_startTime > 0)	return;

	//	�t�����ɂ���
	m_isDirection.ReverseDirection();

	//	�O�Ƃ͋t�̌����ɂ���
	if (m_isDirection.isRight)
	{
		m_position = START_POSITION;
		m_targetPosition = TARGET_POSITION;
		m_birdRange = BIRD_TEXTURE_RIGHT;
	}
	else
	{
		m_targetPosition = START_POSITION;
		m_position = TARGET_POSITION;
		m_birdRange = BIRD_TEXTURE_LEFT;
	}

	m_isMoveFinished = false;

	//	�傫���������_���Ō��߂�
	float random = Utility::CreateRandom(RANDOM_SCALE_MIN, RANDOM_SCALE_MAX);
	m_scale = DirectX::SimpleMath::Vector2(random, random);
}