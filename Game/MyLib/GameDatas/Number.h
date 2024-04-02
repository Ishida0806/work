
#pragma once

class Number
{
	//	�A�N�Z�T
public:

	/// <summary>
	/// ���������̍��W���擾����
	/// </summary>
	/// <returns>/ ���������̍��W</returns>
	inline DirectX::SimpleMath::Vector2 GetNumberPos()	const	{ return m_numPosition; }

	/// <summary>
	/// �X�R�A�̍��W���擾����
	/// </summary>
	/// <returns>�X�R�A�̍��W</returns>
	inline DirectX::SimpleMath::Vector2 GetScorePos()	const	{ return m_scorePosition; }


	/// <summary>
	/// �X�R�A���擾����
	/// </summary>
	/// <returns>�X�R�A</returns>
	inline int GetScore()								const	{ return m_score; }

	/// <summary>
	/// �ԍ��̍��W��ݒ肷��
	/// </summary>
	/// <param name="pos">���W</param>
	void SetNumberPos(const DirectX::SimpleMath::Vector2& pos);

	/// <summary>
	/// �X�R�A�̍��W��ݒ肷��
	/// </summary>
	/// <param name="pos">���W</param>
	void SetScorePos(const DirectX::SimpleMath::Vector2& pos);

	/// <summary>
	/// �X�R�A��ݒ肷��
	/// </summary>
	/// <param name="score">�X�R�A</param>
	void SetScore(const int& score);

	//	�萔
public:

	//  �X�R�A�̑�����
	static const float						  INCREMENT_SCORE_SPEED;
	//	�������Ƃ̋���
	static const float						  DISTANCE_NUMBER;
	//	�ڕW�l
	static const int						  TARGET_INCREMENT_SCORE;
	//	�ő包��
	static const int						  MAX_DIGIT;
	//	�����̐^��
	static const DirectX::SimpleMath::Vector2 NUMBER_TEXTURE_ORIGIN;

	//	�񋓌^
public:

	//	����
	enum class OrdinalNumber
	{
		ZEROTH	= 0,
		FIRST	= 1,
		SECOND  = 2,
		THIRD	= 3,
		FOURTH	= 4,
		FIFTH	= 5,
		SIXTH	= 6,
		SEVENTH	= 7,
		EIGHTH	= 8,
		NINTH	= 9
	};

	//	�ϐ�
private:

	//	�����摜
	ID3D11ShaderResourceView*		m_numTexture;
	//	�X�R�A�̉摜
	ID3D11ShaderResourceView*		m_scoreTexture;
	//	�����̍��W
	DirectX::SimpleMath::Vector2	m_numPosition;
	//	�X�R�A�̍��W
	DirectX::SimpleMath::Vector2	m_scorePosition;
	//	�X�v���C�g�o�b�`
	DirectX::SpriteBatch*			m_spriteBatch;
	//	�X�R�A
	int								m_score;

	//	�֐�
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="texture">�摜</param>
	/// <param name="position">�\�����W</param>
	Number(ID3D11ShaderResourceView* texture,const DirectX::SimpleMath::Vector2& position);

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="texture">�摜</param>
	/// <param name="position">�\�����W</param>
	/// <param name="score">�X�R�A</param>
	Number(ID3D11ShaderResourceView* texture, const DirectX::SimpleMath::Vector2& position,const int& score);

	///
	~Number();

	/// <summary>
	/// ����������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="score"></param>
	void Update(int score);

	/// <summary>
	/// �`����s��
	/// </summary>
	void Draw();

	/// <summary>
	/// �����̂ݕ`����s��
	/// </summary>
	void DrawNumber(float size = 1.0f, float interval = 1.0f);

	/// <summary>
	/// ������`�悷��
	/// </summary>
	void DrawWaveNumber();

	/// <summary>
	/// �`����s���E�T�C�Y��ύX����
	/// </summary>
	/// <param name="interval">�摜�̊Ԋu</param>
	void Draw(float interval);

	//	�v���C�x�[�g�֐�
private:
	//	�f�o�C�X�ˑ��̃��\�[�X
	void CreateDeviceDependentResources();


	/// <summary>
	/// �\������摜�͈͂����߂�
	/// </summary>
	/// <param name="score">�X�R�A�u�ꌅ�v</param>
	/// <returns>�摜�͈͓̔�</returns>
	RECT JudDigit(int score);

	/// <summary>
	/// �e���̐������擾
	/// </summary>
	/// <param name="number">����</param>
	/// <param name="digitPosition">�����ڂ�</param>
	/// <returns>���̌������ڂ�</returns>
	int GetDigitAt(int number, int digitPosition);


	/// <summary>
	/// �X�g�����O�^��
	/// </summary>
	/// <param name="value">�X�R�A�̒l</param>
	/// <returns>string</returns>
	std::string GetString(int value);
};