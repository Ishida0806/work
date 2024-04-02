//
//		File Name �F AudioManager.h
//		Production�F 2023/9/24
//		Author�@�@�F �Γc ����
// 
#pragma once
#include <unordered_map>

class AudioManager
{
	//	�X�e�[�g
public:
	//	���ʏ��
	enum class VOLUME_STATE
	{
		MAX = 0,
		MAX_MIDDLE = 1,
		MIDDLE = 2,
		MINI_MIDDLE = 3,
		MINI = 4
	};

	//	�A�N�Z�T
public:

	//	�{�����[��SE���擾����
	inline float GetSEVolume()				const { return m_volumeSE; }
	//	�{�����[��SE��Ԃ��擾����
	inline VOLUME_STATE GetSEVolumeState()	const { return m_volumeStateSE; }
	//	�{�����[��BGM�擾����
	inline float GetBGMVolume()				const { return m_volumeBGM; }
	//	�{�����[��BGM��Ԃ��擾����
	inline VOLUME_STATE GetBGMVolumeState() const { return m_volumeStateBGM; }
	//	�{�����[��SE��ݒ肷��
	void SetVolumeSE(VOLUME_STATE volume);
	//	�{�����[��BGM��ݒ肷��
	void SetVolumeBGM(VOLUME_STATE volume);

	//	�R���X�g���N�^
private:

	// �R���X�g���N�^
	AudioManager();
	// ����͋��e���Ȃ�
	void operator=(const AudioManager& object) = delete;
	// �R�s�[�R���X�g���N�^�͋��e���Ȃ�
	AudioManager(const AudioManager& object) = delete;

	//	�ϐ�
private:
	//	�{�����[���̃X�e�[�gSE
	VOLUME_STATE																    m_volumeStateSE;
	//	�{�����[���̃X�e�[�gSE	
	VOLUME_STATE																    m_volumeStateBGM;
	//	SE�̃{�����[��
	float																		    m_volumeSE;
	//	BGM�̃{�����[��
	float																		    m_volumeBGM;
	//  �����Đ�����
	std::unique_ptr<DirectX::AudioEngine>										    m_audioEngine;
	//	�T�E���h�G�t�F�N�g
	std::unordered_map<std::wstring, std::unique_ptr<DirectX::SoundEffect>>		    m_soundEffects;
	//	�T�E���h�̃C���X�^���X
	std::unordered_map<std::wstring, std::unique_ptr<DirectX::SoundEffectInstance>> m_soundInstances;

	//	�|�C���^
public:

	// AudioManager�N���X�̃C���X�^���X�ւ̃|�C���^
	static std::unique_ptr<AudioManager>	m_audio;

	//	�֐�
public:
	//	�f�X�g���N�^
	~AudioManager();
	//	�C���X�^���X���擾����
	static AudioManager* const GetInstance();
	//	����������
	void Initialize();
	//	�X�V����
	void Update();
	// �V�������y�t�@�C����ǉ�����
	void AddSoundEffect(const std::wstring& path);
	// ���O�Ŏw�肵��BGM���Đ�����
	void PlaySoundEffectBGM(const std::wstring& path);
	// ���O�Ŏw�肵��SE���Đ�����
	void PlaySoundEffectSE(const std::wstring& path);
	// ���O�Ŏw�肵��SE�����[�v�Đ�����
	void PlaySoundEffectRoopSE(const std::wstring& path);
	//	���y���~�߂�
	void StopSoundEffect(const std::wstring& path);

	//	�v���C�x�[�g�֐�
private:
	//	�I�[�f�B�I��Ԃ��m�F����
	void CheckState();
};

