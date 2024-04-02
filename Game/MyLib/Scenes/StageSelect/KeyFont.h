//
//		File Name �F KeyFont.h
//		Production�F 2023/11/01
//		Author�@�@�F �Γc ����	
// 
#pragma once

class KeyFont
{
	//	�萔
public:

	//	�摜�̐^�񒆂̈ʒu�̏���������	
	static const DirectX::SimpleMath::Vector2 ORIGIN_KEY_TEXTURE;
	//	�L�[�̑傫��
	static const DirectX::SimpleMath::Vector2 SCALE_KEY_TEXTURE;
	//	��������
	static const float						  MOVE_KEY_SPEED;

	//	�񋓌^
public:

	enum class FONT_TYPE
	{
		LEFT  = 0,
		RIGHT = 1,

		OverID = 2
	};

	//		�A�N�Z�T
public:

	inline FONT_TYPE GetType()	const { return m_fontType; }

	//	�ϐ�
private:

	//	�L�[�摜
	ID3D11ShaderResourceView*		m_keyFontTexture;
	//	�L�[���W
	DirectX::SimpleMath::Vector2	m_keyPosition;
	//	�ǂ����̌������ȁH
	FONT_TYPE						m_fontType;
	//	�o�ߎ���
	float							m_elapsedTime;
			
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="type">�^�C�v</param>
	/// <param name="position">���W</param>
	KeyFont(const FONT_TYPE type, const DirectX::SimpleMath::Vector2 position);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~KeyFont();

	/// <summary>
	/// ����������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="timer">�^�C�}�[</param>
	void Update(const DX::StepTimer& timer);

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw();
};