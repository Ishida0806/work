//
//		File Name ： AudioManager.cpp
//		Production： 2023/9/24
//		Author　　： 石田 恭一
// 
//		オーディオ再生する物をまとめたクラス
// 
#include "pch.h"
#include "AudioManager.h"

//	インスタンス聖性のために初期化
std::unique_ptr<AudioManager> AudioManager::m_audio = nullptr;

/// <summary>
/// コンストラクタ
/// </summary>
AudioManager::AudioManager()
	:m_volumeSE(0.0f),
	m_volumeBGM(0.0f),
	m_volumeStateBGM(VOLUME_STATE::MINI_MIDDLE),
	m_volumeStateSE(VOLUME_STATE::MIDDLE)
{
	//	音楽エンジンを生成する------------------------------------------
	m_audioEngine = std::make_unique<DirectX::AudioEngine>();
}

/// <summary>
/// デストラクタ
/// </summary>
AudioManager::~AudioManager()
{
	
}

/// <summary>
/// インスタンスを取得する
/// </summary>
/// <returns></returns>
AudioManager* const AudioManager::GetInstance()
{
	//	オーディオが作成されてないなら作成する
	if (m_audio == nullptr)
	{
		m_audio.reset(new AudioManager());
	}

	return m_audio.get();
}

/// <summary>
/// 初期化する
/// </summary>
void AudioManager::Initialize()
{
	CheckState();
}

/// <summary>
/// 更新する
/// </summary>
void AudioManager::Update()
{
	CheckState();
}

/// <summary>
/// ボリュームSEを設定する
/// </summary>
/// <param name="volumeState">ヴォリュームの</param>
void AudioManager::SetVolumeSE(VOLUME_STATE volumeState)
{
	//	万が一「マイナス」なら治す
	if (static_cast<int>(volumeState) < 0)
		volumeState = VOLUME_STATE::MINI;

	m_volumeStateSE = volumeState;

	//	設定を反映
	CheckState();
}

/// <summary>
/// ボリュームBGMを設定する
/// </summary>
/// <param name="volumeState">ヴォリュームの状態</param>
void AudioManager::SetVolumeBGM(VOLUME_STATE volumeState)
{
	m_volumeStateBGM = volumeState;
}

/// <summary>
/// サウンドエフェクトを追加する
/// </summary>
/// <param name="path">パス</param>
void AudioManager::AddSoundEffect(const std::wstring& path)
{
	std::wstring fliepath = L"Resources/Audios/" + path + L".wav";

	// 新しい音楽ファイルの SoundEffect オブジェクトを作成
	std::unique_ptr<DirectX::SoundEffect> soundEffect = std::make_unique<DirectX::SoundEffect>(m_audioEngine.get(), fliepath.c_str());

	// SoundEffect オブジェクトをマップに追加
	m_soundEffects[path] = std::move(soundEffect);

	// 対応する SoundEffectInstance を作成
	std::unique_ptr<DirectX::SoundEffectInstance> soundInstance = m_soundEffects[path]->CreateInstance();

	// SoundEffectInstance オブジェクトをマップに追加
	m_soundInstances[path] = std::move(soundInstance);
}


/// <summary>
/// 指定したサウンドを再生
/// </summary>
/// <param name="path">ファイルパス</param>
void AudioManager::PlaySoundEffectBGM(const std::wstring& path)
{
	auto soundInstance = m_soundInstances.find(path);

	//	あるなら再生
	if (soundInstance != m_soundInstances.end())
	{
		soundInstance->second->SetVolume(m_volumeBGM);
		soundInstance->second->Play(true);
	}
}

/// <summary>
/// 音楽をループで再生させる
/// </summary>
/// <param name="path">ファイルパス</param>
void AudioManager::PlaySoundEffectSE(const std::wstring& path)
{
	auto soundInstance = m_soundInstances.find(path);

	//	あるなら再生
	if (soundInstance != m_soundInstances.end())
	{
		//	音を止める
		soundInstance->second->Stop();
		//	音量を調整する
		soundInstance->second->SetVolume(m_volumeSE);
		//	音を再生する
		soundInstance->second->Play();
	}
}


/// <summary>
/// 名前で指定したSEをループ再生する
/// </summary>
/// <param name="path">ファイルパス</param>
void AudioManager::PlaySoundEffectRoopSE(const std::wstring& path)
{
	auto soundInstance = m_soundInstances.find(path);

	//	あるなら再生
	if (soundInstance != m_soundInstances.end())
	{
		soundInstance->second->SetVolume(m_volumeSE);
		soundInstance->second->Play(true);
	}
}

/// <summary>
/// 音楽をストップする
/// </summary>
/// <param name="path">ファイルパス</param>
void AudioManager::StopSoundEffect(const std::wstring& path)
{
	auto soundInstance = m_soundInstances.find(path);

	//	あるなら止める
	if (soundInstance != m_soundInstances.end())
	{
		soundInstance->second->Stop();
	}
}

/// <summary>
/// 現在の状態にそぐった音量にする
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
