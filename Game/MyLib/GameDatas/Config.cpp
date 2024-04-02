//
//		File Name �F Config.cpp
//		Production�F 2023/10/1
//		Author�@�@�F �Γc ����
// 
#include "pch.h"
#include "Config.h"

//	�ړ���
const float Config::VELOCITY = 190.0f;
//	���W��X�̍ő�l
const float Config::X_MAX = 1020.0f;
//	��Ԃɂ�鑝����
const float Config::X_INCREMENT = 190.0f;
//	�摜�̑傫��
const DirectX::SimpleMath::Vector2 Config::BASE_SCALE  = DirectX::SimpleMath::Vector2(0.7f, 0.7f);
//	�I�����ꂽ���̑傫��
const DirectX::SimpleMath::Vector2 Config::SELECT_SCALE = DirectX::SimpleMath::Vector2::One;

/// <summary>
/// �R���X�g���N�^
/// </summary>
Config::Config():
	m_audio(nullptr),
	m_button(nullptr),
	m_bar(nullptr),
	m_black(nullptr),
	m_guideKey(nullptr),
	m_guideSE(nullptr),
	m_guideBGM(nullptr),
	m_esc(nullptr),
	m_sprite(nullptr),
	m_stateSound(STATE_SOUND::SE),
	m_isPause(false),
	m_seAlfa(0.0f),
	m_bgmAlfa(0.0f)

{
	CreateDeviceDependentResources();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Config::~Config()
{
}

/// <summary>
/// ����������
/// </summary>
void Config::Initialize()
{
	m_stateSound = STATE_SOUND::SE;
	//	SE�̉摜�̑傫��
	m_seScale = BASE_SCALE;
	//�@BGM�̉摜�̂�������
	m_bgmScale = BASE_SCALE;

	//�@��Ԃ��m�F����
	CheckState();
}

/// <summary>
/// �X�V����
/// </summary>
void Config::Update()
{
	//	��Ԃ�ݒ肷��
	UpdateKey();
	//	�A���t�@�̒l��ς���
	UpdateAlfa();
}

/// <summary>
/// �`�揈��
/// </summary>
void Config::Render()
{
	//	UI��`�悷��
	RenderUI();
}

/// <summary>
/// �I������
/// </summary>
void Config::Finalize()
{
}

/// <summary>
/// �f�o�C�X�ˑ��̃��\�[�X�̏�����
/// </summary>
void Config::CreateDeviceDependentResources()
{
	//	�I�[�f�B�I�}�l�[�W�����擾����
	m_audio = AudioManager::GetInstance();
	//	�X�v���C�g�o�b�`���擾����
	m_sprite = MyLib::ScreenResources::GetInstance()->GetSpriteBatch();
	//	�o�[�̉摜���擾����
	m_bar	 = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"Bar");
	//	�{�^���̉摜���擾����
	m_button = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"Button");
	//	���̉摜�擾����
	m_black  = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"BlackTexture");
	//	�K�C�h�L�[�̉摜���擾����
	m_guideKey = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"GuideKey");
	//	�K�C�hSE�̉摜���擾����
	m_guideSE = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"PauseUITextureSE");
	//	�K�C�hBGM�̉摜���擾����
	m_guideBGM = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"PauseUITextureBGM");
	//	ESC��UI����������
	m_esc = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"EscapeUI");
	//	��ʂ̍����E����
	int width, height;
	//	�X�N���[���T�C�Y���擾����
	MyLib::ScreenResources::GetInstance()->GetScreenSize(width, height);
	//	���W�̏ꏊ��������
	m_barTopPos	   = DirectX::SimpleMath::Vector2(width / 2.0f, height / 3.0f);
	m_buttonTopPos = DirectX::SimpleMath::Vector2(X_MAX, height / 3.0f);
	m_barUnderPos = DirectX::SimpleMath::Vector2(width / 2.0f, height / 2.0f);
	m_buttonUnderPos = DirectX::SimpleMath::Vector2(X_MAX, height / 2.0f);
	m_blackPos	   = DirectX::SimpleMath::Vector2(width / 2.0f, height / 2.0f);
	//	�K�C�h�L�[�̍��W
	m_guidePos  = DirectX::SimpleMath::Vector2(950.0f, 500.0f);
	m_bgmPos	= DirectX::SimpleMath::Vector2(200.0f, m_barUnderPos.y + 30.0f);
	m_sePos		= DirectX::SimpleMath::Vector2(200.0f, m_buttonTopPos.y + 30.0f);
	//	�����x������������
	m_seAlfa  = 1.0f;
	m_bgmAlfa = 1.0f;
}

/// <summary>
/// �A���t�@�̒l��M��
/// </summary>
void Config::UpdateAlfa()
{
	//	�X�e�[�g�̏�Ԃɂ���ăA���t�@�l��ς���
	switch (m_stateSound)
	{
	case Config::STATE_SOUND::SE:
		m_seAlfa = 1.0f;
		m_bgmAlfa = 0.2f;

		m_seScale  = SELECT_SCALE;
		m_bgmScale = BASE_SCALE;
		break;
	case Config::STATE_SOUND::BGM:
		m_seAlfa = 0.2f;
		m_bgmAlfa = 1.0f;

		m_seScale = BASE_SCALE;
		m_bgmScale = SELECT_SCALE;
		break;
	default:
		break;
	}
}


/// <summary>
/// �|�[�Y��ݒ肷��
/// </summary>
/// <param name="flag"></param>
void Config::SetPause(bool flag)
{
	m_isPause = flag;
}

/// <summary>
/// UI��`�悷��
/// </summary>
void Config::RenderUI()
{
	//	���̉摜��`�悷��
	m_sprite->Draw(
		m_black,																//	�摜
		m_blackPos,																//	�摜�̍��W
		nullptr,																//	�摜�͈͓̔�
		DirectX::SimpleMath::Color(0.0f, 0.0f, 0.0f, 0.5f),						//	�F
		0.0f,																	//	�p�x
		DirectX::SimpleMath::Vector2(640.0f, 360.0f),							//	�摜�̐^�񒆂�ݒ肷��
		DirectX::SimpleMath::Vector2(0.8f, 0.8f)								//	�摜�̑傫��
	);

	//	ESC�̕`�悷��
	m_sprite->Draw(
		m_esc,													//	�摜
		DirectX::SimpleMath::Vector2(70.0f, 55.0f)			//	�摜�̍��W
	);

	//	�o�[�̏㕔�`�悷��
	m_sprite->Draw(
		m_bar,											//	�摜
		m_barTopPos,										//	�摜�̍��W
		nullptr,										//	�摜�͈͓̔�
		DirectX::Colors::White,							//	�F
		0.0f,											//	�p�x
		DirectX::SimpleMath::Vector2(740.0f, 29.0f),	//	�摜�̐^�񒆂�ݒ肷��
		DirectX::SimpleMath::Vector2(0.5f, 0.5f)		//	�摜�̑傫��
	);
	//	�{�^���̏㕔�`�悷��
	m_sprite->Draw(
		m_button,											//	�摜
		m_buttonTopPos,										//	�摜�̍��W
		nullptr,											//	�摜�͈͓̔�
		DirectX::Colors::White,								//	�F
		0.0f,												//	�p�x
		DirectX::SimpleMath::Vector2(19.5f, 51.5f)			//	�摜�̐^�񒆂�ݒ肷��
	);

	//	�o�[�̉����`�悷��
	m_sprite->Draw(
		m_bar,											//	�摜
		m_barUnderPos,										//	�摜�̍��W
		nullptr,										//	�摜�͈͓̔�
		DirectX::Colors::White,							//	�F
		0.0f,											//	�p�x
		DirectX::SimpleMath::Vector2(740.0f, 29.0f),	//	�摜�̐^�񒆂�ݒ肷��
		DirectX::SimpleMath::Vector2(0.5f, 0.5f)		//	�摜�̑傫��
	);
	//	�{�^���̉����`�悷��
	m_sprite->Draw(
		m_button,											//	�摜
		m_buttonUnderPos,										//	�摜�̍��W
		nullptr,											//	�摜�͈͓̔�
		DirectX::Colors::White,								//	�F
		0.0f,												//	�p�x
		DirectX::SimpleMath::Vector2(19.5f, 51.5f)			//	�摜�̐^�񒆂�ݒ肷��
	);

	//	�ē��L�[��`�悷��
	m_sprite->Draw(
		m_guideKey,											//	�摜
		m_guidePos,										//	�摜�̍��W
		nullptr,											//	�摜�͈͓̔�
		DirectX::Colors::White,								//	�F
		0.0f,												//	�p�x
		DirectX::SimpleMath::Vector2(19.5f, 51.5f)			//	�摜�̐^�񒆂�ݒ肷��
	);
	//	SE�̕`�悷��
	m_sprite->Draw(
		m_guideSE,												//	�摜
		m_sePos,												//	�摜�̍��W
		nullptr,												//	�摜�͈͓̔�
		DirectX::SimpleMath::Color(m_seAlfa, m_seAlfa, m_seAlfa, m_seAlfa),	//	�F
		0.0f,													//	�p�x
		DirectX::SimpleMath::Vector2(19.5f, 51.5f),					//	�摜�̐^�񒆂�ݒ肷��
		m_seScale
	);
	//	BGM�̕`�悷��
	m_sprite->Draw(
		m_guideBGM,												//	�摜
		m_bgmPos,												//	�摜�̍��W
		nullptr,												//	�摜�͈͓̔�
		DirectX::SimpleMath::Color(m_bgmAlfa, m_bgmAlfa, m_bgmAlfa, m_bgmAlfa),//	�F
		0.0f,													//	�p�x
		DirectX::SimpleMath::Vector2(19.5f, 51.5f),				//	�摜�̐^�񒆂�ݒ肷��
		m_bgmScale
	);
}

/// <summary>
/// ���݂̏�Ԃɂ����������W�ɂ���
/// </summary>
void Config::CheckState()
{
	//	SE�̏�Ԃɂ��X�e�[�g�ς���
	switch (m_audio->GetSEVolumeState())
	{
	case AudioManager::VOLUME_STATE::MAX:
		m_buttonTopPos.x = X_MAX;
		break;
	case AudioManager::VOLUME_STATE::MAX_MIDDLE:
		m_buttonTopPos.x = X_MAX - X_INCREMENT;
		break;
	case AudioManager::VOLUME_STATE::MIDDLE:
		m_buttonTopPos.x = X_MAX - X_INCREMENT * 2.0f;
		break;
	case AudioManager::VOLUME_STATE::MINI_MIDDLE:
		m_buttonTopPos.x = X_MAX - X_INCREMENT * 3.0f;
		break;
	case AudioManager::VOLUME_STATE::MINI:
		m_buttonTopPos.x = X_MAX - X_INCREMENT * 4.0f;
		break;
	default:
		break;
	}
	//	BGM�̏�Ԃɂ��X�e�[�g�ς���
	switch (m_audio->GetBGMVolumeState())
	{
	case AudioManager::VOLUME_STATE::MAX:
		m_buttonUnderPos.x = X_MAX;
		break;
	case AudioManager::VOLUME_STATE::MAX_MIDDLE:
		m_buttonUnderPos.x = X_MAX - X_INCREMENT;
		break;
	case AudioManager::VOLUME_STATE::MIDDLE:
		m_buttonUnderPos.x = X_MAX - X_INCREMENT * 2.0f;
		break;
	case AudioManager::VOLUME_STATE::MINI_MIDDLE:
		m_buttonUnderPos.x = X_MAX - X_INCREMENT * 3.0f;
		break;
	case AudioManager::VOLUME_STATE::MINI:
		m_buttonUnderPos.x = X_MAX - X_INCREMENT * 4.0f;
		break;
	default:
		break;
	}
}

/// <summary>
/// �L�[�̏�Ԃ�ݒ肷��
/// </summary>
void Config::UpdateKey()
{
	//	�L�[�{�[�h�̓��͂��擾����
	auto input = MyLib::InputSystem::GetInstance()->GetKeyTracer();
	//	SE���擾����
	int se = static_cast<int>(m_audio->GetSEVolumeState());
	//	BGM���擾����
	int bgm = static_cast<int>(m_audio->GetBGMVolumeState());

	//	W���������ꍇ
	if (input->pressed.W)
	{
		if (m_stateSound == STATE_SOUND::SE)
		{
			m_stateSound = STATE_SOUND::BGM;
		}
		else if (m_stateSound == STATE_SOUND::BGM)
		{
			m_stateSound = STATE_SOUND::SE;
		}
		//	SE���Đ�����
		m_audio->PlaySoundEffectSE(L"PlaySE02_MoveTitle");
	}
	//	S���������ꍇ
	if (input->pressed.S)
	{
		if (m_stateSound == STATE_SOUND::SE)
		{
			m_stateSound = STATE_SOUND::BGM;
		}
		else if (m_stateSound == STATE_SOUND::BGM)
		{
			m_stateSound = STATE_SOUND::SE;
		}
		//	SE���Đ�����
		m_audio->PlaySoundEffectSE(L"PlaySE02_MoveTitle");
	}

	if (m_stateSound == STATE_SOUND::SE)
	{
		if (input->pressed.A && m_audio->GetSEVolumeState() != AudioManager::VOLUME_STATE::MINI)
		{
			m_buttonTopPos.x -= VELOCITY;
			se++;
			m_audio->SetVolumeSE(static_cast<AudioManager::VOLUME_STATE>(se));
			//	SE���Đ�����
			m_audio->PlaySoundEffectSE(L"PlaySE02_MoveTitle");
		}
		if (input->pressed.D && m_audio->GetSEVolumeState() != AudioManager::VOLUME_STATE::MAX)
		{
			m_buttonTopPos.x += VELOCITY;
			se--;
			m_audio->SetVolumeSE(static_cast<AudioManager::VOLUME_STATE>(se));
			//	SE���Đ�����
			m_audio->PlaySoundEffectSE(L"PlaySE02_MoveTitle");
		}
	}
	else if (m_stateSound == STATE_SOUND::BGM)
	{
		if (input->pressed.A && m_audio->GetBGMVolumeState() != AudioManager::VOLUME_STATE::MINI)
		{
			m_buttonUnderPos.x -= VELOCITY;
			bgm++; 
			//	SE���Đ�����
			m_audio->PlaySoundEffectSE(L"PlaySE02_MoveTitle");
		}
		if (input->pressed.D && m_audio->GetBGMVolumeState() != AudioManager::VOLUME_STATE::MAX)
		{
			m_buttonUnderPos.x += VELOCITY;
			bgm--;
			//	SE���Đ�����
			m_audio->PlaySoundEffectSE(L"PlaySE02_MoveTitle");
		}
	}

	//	Escape�L�[�������ꂽ��|�[�Y���I������
	if (input->pressed.Escape)
	{
		m_audio->PlaySoundEffectSE(L"Close_SE01");
		//	�|�[�Y���I�t�ɂ���
		m_isPause = false;
	}
	//	�L���X�g������Ԃ�BGM��ݒ肷��
	m_audio->SetVolumeBGM(static_cast<AudioManager::VOLUME_STATE>(bgm));
}