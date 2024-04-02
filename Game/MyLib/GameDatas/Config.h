//
//		File Name �F Config.h
//		Production�F 2023/10/1
//		Author�@�@�F �Γc ����
// 
#pragma once

class Config
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
	static const float VELOCITY;
	//	���W��X�̍ő�l
	static const float X_MAX;
	//	��Ԃɂ�鑝����
	static const float X_INCREMENT;
	//	�摜�̑傫��
	static const DirectX::SimpleMath::Vector2 BASE_SCALE;
	//	�I������Ă���Ƃ��̑傫��
	static const DirectX::SimpleMath::Vector2 SELECT_SCALE;

	//	�X�e�[�g
public:

	enum class STATE_SOUND
	{
		SE = 0,
		BGM = 1
	};

	//	�ϐ�
private:
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
	//	SE�̉摜�̑傫��
	DirectX::SimpleMath::Vector2	m_seScale;
	//	BGM	�̉摜�̑傫��
	DirectX::SimpleMath::Vector2	m_bgmScale;
	//	�|�[�Y�����H
	bool							m_isPause;
	//	se�̓����x
	float							m_seAlfa;
	//	bgm�̓����x
	float							m_bgmAlfa;
	//	�X�e�[�g
	STATE_SOUND						m_stateSound;

	//	�֐�
public:

	Config();
	~Config();

	//	����������
	void Initialize();
	//	�X�V����
	void Update();
	//	�`�揈��
	void Render();
	//	�I������
	void Finalize();

	//	�v���C�x�[�g�֐�
private:

	//	�f�o�C�X�ˑ��̃��\�[�X�̏�����
	void CreateDeviceDependentResources();
	void UpdateAlfa();
	void UpdateKey();
	void RenderUI();
	void CheckState();
};