//
//		File Name ： AudioManager.h
//		Production： 2023/9/24
//		Author　　： 石田 恭一
// 
#pragma once
#include <unordered_map>

class AudioManager
{
	//	ステート
public:
	//	音量状態
	enum class VOLUME_STATE
	{
		MAX = 0,
		MAX_MIDDLE = 1,
		MIDDLE = 2,
		MINI_MIDDLE = 3,
		MINI = 4
	};

	//	アクセサ
public:

	//	ボリュームSEを取得する
	inline float GetSEVolume()				const { return m_volumeSE; }
	//	ボリュームSE状態を取得する
	inline VOLUME_STATE GetSEVolumeState()	const { return m_volumeStateSE; }
	//	ボリュームBGM取得する
	inline float GetBGMVolume()				const { return m_volumeBGM; }
	//	ボリュームBGM状態を取得する
	inline VOLUME_STATE GetBGMVolumeState() const { return m_volumeStateBGM; }
	//	ボリュームSEを設定する
	void SetVolumeSE(VOLUME_STATE volume);
	//	ボリュームBGMを設定する
	void SetVolumeBGM(VOLUME_STATE volume);

	//	コンストラクタ
private:

	// コンストラクタ
	AudioManager();
	// 代入は許容しない
	void operator=(const AudioManager& object) = delete;
	// コピーコンストラクタは許容しない
	AudioManager(const AudioManager& object) = delete;

	//	変数
private:
	//	ボリュームのステートSE
	VOLUME_STATE																    m_volumeStateSE;
	//	ボリュームのステートSE	
	VOLUME_STATE																    m_volumeStateBGM;
	//	SEのボリューム
	float																		    m_volumeSE;
	//	BGMのボリューム
	float																		    m_volumeBGM;
	//  音を再生する
	std::unique_ptr<DirectX::AudioEngine>										    m_audioEngine;
	//	サウンドエフェクト
	std::unordered_map<std::wstring, std::unique_ptr<DirectX::SoundEffect>>		    m_soundEffects;
	//	サウンドのインスタンス
	std::unordered_map<std::wstring, std::unique_ptr<DirectX::SoundEffectInstance>> m_soundInstances;

	//	ポインタ
public:

	// AudioManagerクラスのインスタンスへのポインタ
	static std::unique_ptr<AudioManager>	m_audio;

	//	関数
public:
	//	デストラクタ
	~AudioManager();
	//	インスタンスを取得する
	static AudioManager* const GetInstance();
	//	初期化する
	void Initialize();
	//	更新する
	void Update();
	// 新しい音楽ファイルを追加する
	void AddSoundEffect(const std::wstring& path);
	// 名前で指定したBGMを再生する
	void PlaySoundEffectBGM(const std::wstring& path);
	// 名前で指定したSEを再生する
	void PlaySoundEffectSE(const std::wstring& path);
	// 名前で指定したSEをループ再生する
	void PlaySoundEffectRoopSE(const std::wstring& path);
	//	音楽を止める
	void StopSoundEffect(const std::wstring& path);

	//	プライベート関数
private:
	//	オーディオ状態を確認する
	void CheckState();
};

