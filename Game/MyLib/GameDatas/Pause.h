//
//		File Name �F Pause.h
//		Production�F 2023/10/1
//		Author�@�@�F �Γc ����
// 
#pragma once

class PlayScene;

class Pause
{
	//	�A�N�Z�T
public:
	//	�|�[�Y�����H
	inline bool IsPause()	const { return m_isPause; }
	//	�|�[�Y����ݒ肷��
	void SetPause(bool flag);

	//	�萔
public:

	//	�ړ���
	static const float						  VELOCITY;
	//	���W��X�̍ő�l
	static const float						  X_MAX;
	//	��Ԃɂ�鑝����
	static const float						  X_INCREMENT;
	//	�摜�̑傫��
	static const DirectX::SimpleMath::Vector2 BASE_SCALE;
	//	�I������Ă���Ƃ��̑傫��
	static const DirectX::SimpleMath::Vector2 SELECT_SCALE;

	//	�X�e�[�g
public:

	enum class STATE_SOUND
	{
		SE = 0,
		BGM = 1,
		TITLE = 2,
		END = 3,

		OverID = 4
	};

	//	�ϐ�
private:
	//	�v���C�V�[��
	PlayScene*						m_playScene;
	//	�I�[�f�B�I�}�l�[�W��
	AudioManager*					m_audio;
	//	�X�v���C�g�o�b�`
	DirectX::SpriteBatch*			m_sprite;
	//	�{�^���̉摜
	ID3D11ShaderResourceView*		m_button;
	//	�o�[�̉摜
	ID3D11ShaderResourceView*		m_bar;
	//	���̉摜
	ID3D11ShaderResourceView*		m_black;
	//	�ē��L�[�̉摜
	ID3D11ShaderResourceView*		m_guideKey;
	//	SE�̉摜
	ID3D11ShaderResourceView*		m_guideSE;
	//	BGM�̉摜
	ID3D11ShaderResourceView*		m_guideBGM;
	//	�^�C�g��
	ID3D11ShaderResourceView*		m_title;
	//	END�̉摜
	ID3D11ShaderResourceView*		m_end;
	//	ESCAPE���[��UI
	ID3D11ShaderResourceView*		m_esc;
	//	�{�^���̍��W�㕔
	DirectX::SimpleMath::Vector2	m_buttonTopPos;
	//	�{�^���̍��W����
	DirectX::SimpleMath::Vector2	m_buttonUnderPos;
	//	�o�[�̍��W�㕔
	DirectX::SimpleMath::Vector2	m_barTopPos;
	//	�o�[�̍��W����
	DirectX::SimpleMath::Vector2	m_barUnderPos;
	//	���̉摜�̍��W
	DirectX::SimpleMath::Vector2	m_blackPos;
	//	�ē��L�[�̉摜�ʒu
	DirectX::SimpleMath::Vector2	m_guidePos;
	//	SE�̉摜�ʒu
	DirectX::SimpleMath::Vector2	m_sePos;
	//	BGM�̉摜�ʒu
	DirectX::SimpleMath::Vector2	m_bgmPos;
	//	Title�̈ʒu
	DirectX::SimpleMath::Vector2	m_titlePos;
	// ENDGAME�̈ʒu
	DirectX::SimpleMath::Vector2	m_endGamePos;
	//	SE�̑傫��
	DirectX::SimpleMath::Vector2	m_seScale;
	//	BGM�̑傫��
	DirectX::SimpleMath::Vector2	m_bgmScale;
	//	Title�̑傫��
	DirectX::SimpleMath::Vector2	m_titleScale;
	//	ENDGAME�̑傫��
	DirectX::SimpleMath::Vector2	m_endGameScale;
	//	�|�[�Y�����H
	bool							m_isPause;
	//	se�̓����x
	float							m_seAlfa;
	//	bgm�̓����x
	float							m_bgmAlfa;
	//	end�̓����x
	float							m_endAlfa;
	//	title�̓����x
	float							m_titleAlfa;
	//	�X�e�[�g
	STATE_SOUND						m_stateSound;

	//	�֐�
public:

	Pause(PlayScene* playScene);
	~Pause();

	//	����������
	void Initialize();
	//	�X�V����
	void Update();
	//	�`�揈��
	void Render();
	//	�I������
	void Finalize();

	//	�g�ݍ��݊֐��֐�
private:

	//	�f�o�C�X�ˑ��̃��\�[�X�̏�����
	void CreateDeviceDependentResources();
	//	�A���t�@�n��ω�������
	void UpdateAlfa();
	//	�L�[�����X�V����
	void UpdateKey();
	//	UI�̕`��
	void RenderUI();
	//	�X�e�[�g��Ԃ�ω�������
	void CheckState();
};