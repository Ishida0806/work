
//
//		File Name �F PushSeal.h
//		Production�F 2023/11/11
//		Author�@�@�F �Γc ����
//
#pragma once

class PushSeal
{
	//	�A�N�Z�T
public:

	inline bool IsTop() const { return m_isTop; }

	//	�萔
public:

	//	���ʂ̌덷�͈�
	static const float						   ERROR_RANGE;
	//	���ʂ̑��x
	static const float						   SEAL_SPEED;
	//	�^�[�Q�b�g��Y���W
	static const DirectX::SimpleMath::Vector2  MOVE_TARGET_POSITION;
	//	�ڕW�̔��q���������W
	static const DirectX::SimpleMath::Vector2  TARGET_PUSH_POSITION;
	//	�ڕW�̉�ʊO�̍��W
	static const DirectX::SimpleMath::Vector2  TARGET_FAR_POSITION;

	//	�񋓌^
private:

	//	�X�^���v�̋���
	enum class PUSHSEAL_STATE
	{
		MoveTarget,
		Push,
		MoveOut,
		Finish,

		OverID
	};


	//	�ϐ�
private:

	//	�摜
	ID3D11ShaderResourceView*		 m_texture;
	//	���W
	DirectX::SimpleMath::Vector2	 m_position;
	//	�^�񒆂̍��W
	DirectX::SimpleMath::Vector2	 m_originPosition;
	//	�傫��
	DirectX::SimpleMath::Vector2	 m_scale;
	//	�p�x
	float							 m_angle;
	//	�㑤���s���Ă��邩�H
	bool							 m_isTop;
	//	�㑤�ɂ��������H
	bool							 m_moveTop;
	//	�����ɂ��������H
	bool							 m_moveDown;
	//	�X�^���v����������
	PUSHSEAL_STATE					 m_stateSeal;


	//	�֐�
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="texture">�摜</param>
	/// <param name="position">���W</param>
	/// <param name="originPosition">�^�񒆂̍��W</param>
	PushSeal(
		const DirectX::SimpleMath::Vector2& position,
		const DirectX::SimpleMath::Vector2& originPosition
	);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~PushSeal();

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw();

	//	���ߍ��݊֐�
private:

	/// <summary>
	/// �^�[�Q�b�g�̏ꏊ�Ɉړ����s��
	/// </summary>
	void MoveTarget();

	/// <summary>
	/// �X�^���v������
	/// </summary>
	void Push();

	/// <summary>
	/// �O�֌�����
	/// </summary>
	void MoveOut();

};