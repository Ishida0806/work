//
//		File Name �F AudioManager.cpp
//		Production�F 2023/9/24
//		Author�@�@�F �Γc ����
// 
//		�I�[�f�B�I�Đ����镨���܂Ƃ߂��N���X
// 
#include "pch.h"
#include "AudioManager.h"

//	�C���X�^���X�����̂��߂ɏ�����
std::unique_ptr<AudioManager> AudioManager::m_audio = nullptr;

/// <summary>
/// �R���X�g���N�^
/// </summary>
AudioManager::AudioManager()
	:m_volumeSE(0.0f),
	m_volumeBGM(0.0f),
	m_volumeStateBGM(VOLUME_STATE::MINI_MIDDLE),
	m_volumeStateSE(VOLUME_STATE::MIDDLE)
{
	//	���y�G���W���𐶐�����------------------------------------------
	m_audioEngine = std::make_unique<DirectX::AudioEngine>();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
AudioManager::~AudioManager()
{
	
}

/// <summary>
/// �C���X�^���X���擾����
/// </summary>
/// <returns></returns>
AudioManager* const AudioManager::GetInstance()
{
	//	�I�[�f�B�I���쐬����ĂȂ��Ȃ�쐬����
	if (m_audio == nullptr)
	{
		m_audio.reset(new AudioManager());
	}

	return m_audio.get();
}

/// <summary>
/// ����������
/// </summary>
void AudioManager::Initialize()
{
	CheckState();
}

/// <summary>
/// �X�V����
/// </summary>
void AudioManager::Update()
{
	CheckState();
}

/// <summary>
/// �{�����[��SE��ݒ肷��
/// </summary>
/// <param name="volumeState">���H�����[����</param>
void AudioManager::SetVolumeSE(VOLUME_STATE volumeState)
{
	//	������u�}�C�i�X�v�Ȃ玡��
	if (static_cast<int>(volumeState) < 0)
		volumeState = VOLUME_STATE::MINI;

	m_volumeStateSE = volumeState;

	//	�ݒ�𔽉f
	CheckState();
}

/// <summary>
/// �{�����[��BGM��ݒ肷��
/// </summary>
/// <param name="volumeState">���H�����[���̏��</param>
void AudioManager::SetVolumeBGM(VOLUME_STATE volumeState)
{
	m_volumeStateBGM = volumeState;
}

/// <summary>
/// �T�E���h�G�t�F�N�g��ǉ�����
/// </summary>
/// <param name="path">�p�X</param>
void AudioManager::AddSoundEffect(const std::wstring& path)
{
	std::wstring fliepath = L"Resources/Audios/" + path + L".wav";

	// �V�������y�t�@�C���� SoundEffect �I�u�W�F�N�g���쐬
	std::unique_ptr<DirectX::SoundEffect> soundEffect = std::make_unique<DirectX::SoundEffect>(m_audioEngine.get(), fliepath.c_str());

	// SoundEffect �I�u�W�F�N�g���}�b�v�ɒǉ�
	m_soundEffects[path] = std::move(soundEffect);

	// �Ή����� SoundEffectInstance ���쐬
	std::unique_ptr<DirectX::SoundEffectInstance> soundInstance = m_soundEffects[path]->CreateInstance();

	// SoundEffectInstance �I�u�W�F�N�g���}�b�v�ɒǉ�
	m_soundInstances[path] = std::move(soundInstance);
}


/// <summary>
/// �w�肵���T�E���h���Đ�
/// </summary>
/// <param name="path">�t�@�C���p�X</param>
void AudioManager::PlaySoundEffectBGM(const std::wstring& path)
{
	auto soundInstance = m_soundInstances.find(path);

	//	����Ȃ�Đ�
	if (soundInstance != m_soundInstances.end())
	{
		soundInstance->second->SetVolume(m_volumeBGM);
		soundInstance->second->Play(true);
	}
}

/// <summary>
/// ���y�����[�v�ōĐ�������
/// </summary>
/// <param name="path">�t�@�C���p�X</param>
void AudioManager::PlaySoundEffectSE(const std::wstring& path)
{
	auto soundInstance = m_soundInstances.find(path);

	//	����Ȃ�Đ�
	if (soundInstance != m_soundInstances.end())
	{
		//	�����~�߂�
		soundInstance->second->Stop();
		//	���ʂ𒲐�����
		soundInstance->second->SetVolume(m_volumeSE);
		//	�����Đ�����
		soundInstance->second->Play();
	}
}


/// <summary>
/// ���O�Ŏw�肵��SE�����[�v�Đ�����
/// </summary>
/// <param name="path">�t�@�C���p�X</param>
void AudioManager::PlaySoundEffectRoopSE(const std::wstring& path)
{
	auto soundInstance = m_soundInstances.find(path);

	//	����Ȃ�Đ�
	if (soundInstance != m_soundInstances.end())
	{
		soundInstance->second->SetVolume(m_volumeSE);
		soundInstance->second->Play(true);
	}
}

/// <summary>
/// ���y���X�g�b�v����
/// </summary>
/// <param name="path">�t�@�C���p�X</param>
void AudioManager::StopSoundEffect(const std::wstring& path)
{
	auto soundInstance = m_soundInstances.find(path);

	//	����Ȃ�~�߂�
	if (soundInstance != m_soundInstances.end())
	{
		soundInstance->second->Stop();
	}
}

/// <summary>
/// ���݂̏�Ԃɂ����������ʂɂ���
/// </summary>
void AudioManager::CheckState()
{
	switch (m_volumeStateSE)
	{
	case AudioManager::VOLUME_STATE::MAX:			m_volumeSE = 1.0f;	break;
	case AudioManager::VOLUME_STATE::MAX_MIDDLE:	m_volumeSE = 0.75f;	break;
	case AudioManager::VOLUME_STATE::MIDDLE:		m_volumeSE = 0.5f;	break;
	case AudioManager::VOLUME_STATE::MINI_MIDDLE:	m_volumeSE = 0.25f;	break;
	case AudioManager::VOLUME_STATE::MINI:			m_volumeSE = 0.0f;	break;
	default:															break;
	}

	switch (m_volumeStateBGM)
	{
	case AudioManager::VOLUME_STATE::MAX:			m_volumeBGM = 1.0f;		break;
	case AudioManager::VOLUME_STATE::MAX_MIDDLE:	m_volumeBGM = 0.75f;	break;
	case AudioManager::VOLUME_STATE::MIDDLE:		m_volumeBGM = 0.50f;	break;
	case AudioManager::VOLUME_STATE::MINI_MIDDLE:	m_volumeBGM = 0.25f;	break;
	case AudioManager::VOLUME_STATE::MINI:			m_volumeBGM = 0.0f;		break;
	default:																break;
	}
}
