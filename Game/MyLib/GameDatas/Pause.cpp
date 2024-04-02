//
//		File Name �F Pause.cpp
//		Production�F 2023/10/1
//		Author�@�@�F �Γc ����
// 
#include "pch.h"
#include "Pause.h"

#include "Game/MyLib/Scenes/PlayScene/PlayScene.h"

//	�ړ���
const float						   Pause::VELOCITY		= 190.0f;
//	���W��X�̍ő�l
const float						   Pause::X_MAX			= 1020.0f;
//	��Ԃɂ�鑝����
const float						   Pause::X_INCREMENT	= 190.0f;
//	�摜�̑傫��
const DirectX::SimpleMath::Vector2 Pause::BASE_SCALE	= DirectX::SimpleMath::Vector2(0.7f, 0.7f);
//	�I�����ꂽ���̑傫��
const DirectX::SimpleMath::Vector2 Pause::SELECT_SCALE  = DirectX::SimpleMath::Vector2::One;
/// <summary>
/// �R���X�g���N�^
/// </summary>
Pause::Pause(PlayScene* playScene) 
	:m_playScene(playScene),
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
	m_bgmAlfa(0.0f),
	m_titleAlfa(0.0f),
	m_endAlfa(0.0f)

{
	CreateDeviceDependentResources();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Pause::~Pause()
{
}

/// <summary>
/// ����������
/// </summary>
void Pause::Initialize()
{
	//	�ʒu��SE�ɂ���
	m_stateSound = STATE_SOUND::SE;
	//�@��Ԃ��m�F����
	CheckState();
}

/// <summary>
/// �X�V����
/// </summary>
void Pause::Update()
{
	//	��Ԃ�ݒ肷��
	UpdateKey();
	//	�A���t�@�̒l��ς���
	UpdateAlfa();
}

/// <summary>
/// �`�揈��
/// </summary>
void Pause::Render()
{
	//	UI��`�悷��
	RenderUI();
}

/// <summary>
/// �I������
/// </summary>
void Pause::Finalize()
{
}

/// <summary>
/// �f�o�C�X�ˑ��̃��\�[�X�̏�����
/// </summary>
void Pause::CreateDeviceDependentResources()
{
	//	�I�[�f�B�I�}�l�[�W�����擾����
	m_audio = AudioManager::GetInstance();
	//	�X�v���C�g�o�b�`���擾����
	m_sprite = MyLib::ScreenResources::GetInstance()->GetSpriteBatch();
	//	�o�[�̉摜���擾����
	m_bar = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"Bar");
	//	�{�^���̉摜���擾����
	m_button = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"Button");
	//	���̉摜�擾����
	m_black = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"BlackTexture");
	//	�K�C�h�L�[�̉摜���擾����
	m_guideKey = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"GuideKey");
	//	�K�C�hSE�̉摜���擾����
	m_guideSE = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"PauseUITextureSE");
	//	�K�C�hBGM�̉摜���擾����
	m_guideBGM = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"PauseUITextureBGM");
	//	ESC��UI����������
	m_esc = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"EscapeUI");
	//	�G���h
	m_end = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"PauseUITextureEndGame");
	//	�^�C�g��
	m_title = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"PauseUITextureTitle");
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
	m_titlePos	= DirectX::SimpleMath::Vector2(640.0f, 520.0f);
	m_endGamePos= DirectX::SimpleMath::Vector2(640.0f, 580.0f);
	//	�����x������������
	m_seAlfa  = 1.0f;
	m_bgmAlfa = 1.0f;
	m_endAlfa = 1.0f;
	m_titleAlfa = 1.0f;
	//	�摜�̑傫��
	m_seScale	   = BASE_SCALE;
	m_bgmScale	   = BASE_SCALE;
	m_titleScale   = BASE_SCALE;
	m_endGameScale = BASE_SCALE;
}

/// <summary>
/// �A���t�@�̒l��M��
/// </summary>
void Pause::UpdateAlfa()
{
	//	�X�e�[�g�̏�Ԃɂ���ăA���t�@�l��ς���
	switch (m_stateSound)
	{
	case Pause::STATE_SOUND::SE:
		//	�F��ς���
		m_seAlfa    = 1.0f;
		m_bgmAlfa   = 0.2f;
		m_endAlfa   = 0.2f;
		m_titleAlfa = 0.2f;
		//	�傫����ς���
		m_seScale = SELECT_SCALE;
		m_bgmScale = BASE_SCALE;
		m_titleScale = BASE_SCALE;
		m_endGameScale = BASE_SCALE;
		break;
	case Pause::STATE_SOUND::BGM:
		//	�F��ς���
		m_seAlfa    = 0.2f;
		m_bgmAlfa   = 1.0f;
		m_endAlfa   = 0.2f;
		m_titleAlfa = 0.2f;
		//	�傫����ς���
		m_seScale = BASE_SCALE;
		m_bgmScale = SELECT_SCALE;
		m_titleScale = BASE_SCALE;
		m_endGameScale = BASE_SCALE;
		break;

	case Pause::STATE_SOUND::TITLE:
		//	�F��ς���
		m_seAlfa	= 0.2f;
		m_bgmAlfa	= 0.2f;
		m_endAlfa	= 0.2f;
		m_titleAlfa = 1.0f;
		//	�傫����ς���
		m_seScale = BASE_SCALE;
		m_bgmScale = BASE_SCALE;
		m_titleScale = SELECT_SCALE;
		m_endGameScale = BASE_SCALE;

		break;

	case Pause::STATE_SOUND::END:
		//	�F��ς���
		m_seAlfa    = 0.2f;
		m_bgmAlfa   = 0.2f;
		m_endAlfa   = 1.0f;
		m_titleAlfa = 0.2f;
		//	�傫����ς���
		m_seScale	   = BASE_SCALE;
		m_bgmScale	   = BASE_SCALE;
		m_titleScale   = BASE_SCALE;
		m_endGameScale = SELECT_SCALE;
		break;


	default:
		break;
	}
}


/// <summary>
/// �|�[�Y��ݒ肷��
/// </summary>
/// <param name="flag"></param>
void Pause::SetPause(bool flag)
{
	m_isPause = flag;
}

/// <summary>
/// UI��`�悷��
/// </summary>
void Pause::RenderUI()
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
		m_button,										//	�摜
		m_buttonUnderPos,									//	�摜�̍��W
		nullptr,											//	�摜�͈͓̔�
		DirectX::Colors::White,							//	�F
		0.0f,											//	�p�x
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
		DirectX::SimpleMath::Vector2(19.5f, 51.5f),				//	�摜�̐^�񒆂�ݒ肷��
		m_seScale
	);
	//	BGM�̕`�悷��
	m_sprite->Draw(
		m_guideBGM,																//	�摜
		m_bgmPos,																//	�摜�̍��W
		nullptr,																//	�摜�͈͓̔�
		DirectX::SimpleMath::Color(m_bgmAlfa, m_bgmAlfa, m_bgmAlfa, m_bgmAlfa), //	�F
		0.0f,																	//	�p�x
		DirectX::SimpleMath::Vector2(19.5f, 51.5f),								//	�摜�̐^�񒆂�ݒ肷��
		m_bgmScale
	);
	//	�^�C�g���̕`�悷��
	m_sprite->Draw(
		m_title,																		//	�摜
		m_titlePos,																		//	�摜�̍��W
		nullptr,																		//	�摜�͈͓̔�
		DirectX::SimpleMath::Color(m_titleAlfa, m_titleAlfa, m_titleAlfa, m_titleAlfa), //	�F
		0.0f,																			//	�p�x
		DirectX::SimpleMath::Vector2(68.0f, 45.0f),										//	�摜�̐^�񒆂�ݒ肷��
		m_titleScale
	);

	//	END�̕`�悷��
	m_sprite->Draw(
		m_end,																		//	�摜
		m_endGamePos,								//	�摜�̍��W
		nullptr,																	//	�摜�͈͓̔�
		DirectX::SimpleMath::Color(m_endAlfa, m_endAlfa, m_endAlfa, m_endAlfa),		//	�F
		0.0f,																		//	�p�x
		DirectX::SimpleMath::Vector2(97.0f, 45.0f),									//	�摜�̐^�񒆂�ݒ肷��
		m_endGameScale
	);
}

/// <summary>
/// ���݂̏�Ԃɂ����������W�ɂ���
/// </summary>
void Pause::CheckState()
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
void Pause::UpdateKey()
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
			m_stateSound = STATE_SOUND::END;
		}
		else if (m_stateSound == STATE_SOUND::BGM)
		{
			m_stateSound = STATE_SOUND::SE;
		}
		else if (m_stateSound == STATE_SOUND::TITLE)
		{
			m_stateSound = STATE_SOUND::BGM;
		}
		else if(m_stateSound == STATE_SOUND::END)
		{
			m_stateSound = STATE_SOUND::TITLE;
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
			m_stateSound = STATE_SOUND::TITLE;
		}
		else if (m_stateSound == STATE_SOUND::TITLE)
		{
			m_stateSound = STATE_SOUND::END;
		}
		else if (m_stateSound == STATE_SOUND::END)
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
		//	SE���Đ�����
		m_audio->PlaySoundEffectSE(L"Close_SE01");
		//	�|�[�Y���I�t�ɂ���
		m_isPause = false;
	}
	//	�X�y�[�X�������ꂽ�@&&�@�^�C�g���V�[����������
	if (input->pressed.Space && m_stateSound == STATE_SOUND::TITLE)
	{
		//	�I�[�f�B�I�}�l�[�W���̉����Đ�
		AudioManager::GetInstance()->PlaySoundEffectSE(L"PlaySE01_Accept");
		m_playScene->ChangeSceneTitle();
		return;
	}
	///	�X�e�[�g���G���h��Ԃ̂݃Q�[�����I������
	if (input->pressed.Space && m_stateSound == STATE_SOUND::END)
	{
		PostQuitMessage(0);
	}
	//	�L���X�g������Ԃ�BGM��ݒ肷��
	m_audio->SetVolumeBGM(static_cast<AudioManager::VOLUME_STATE>(bgm));	
}