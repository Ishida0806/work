
#pragma once

class Player;

class LevelCardEffect
{
	//	�A�N�Z�T
public:

	//	�N���b�N�\���H
	inline bool IsClickAble()	const { return m_clickAble; }
	//	�����ł������H
	inline bool IsReady()		const { return m_isReady; }
	//	�N���b�N�������ꂽ
	void SetClick();

	//	�萔
public:

	//	�J�[�h�̐^�񒆂̍��W
	static const DirectX::SimpleMath::Vector2 CARD_ORIGIN_POSITION;
	//	�J�[�h�̍��W
	static const DirectX::SimpleMath::Vector2 CARD_POSITION;
	//	�}�E�X�J�[�\���ڐG��̃X�P�[��
	static const DirectX::SimpleMath::Vector2 CARD_SCALE;
	//	�J�[�h�̂��炷���W	
	static const float						  OFFSET_POSITION;

	//	�ϐ�
private:

	//	�v���C���[
	Player*							m_player;
	//	�ڕW���W
	DirectX::SimpleMath::Vector2	m_targetPosition;
	//	���݂̍��W
	DirectX::SimpleMath::Vector2	m_position;
	//	�傫��
	DirectX::SimpleMath::Vector2	m_scale;
	//	�摜
	ID3D11ShaderResourceView*		m_texture;
	//	�J�[�h�̃^�C�v
	int								m_type;
	//	�N���b�N�\��
	bool							m_clickAble;
	//	�����\OK��
	bool							m_isReady;

	//	�֐�
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="player">�v���C���[</param>
	/// <param name="type">�^�C�v/param>
	LevelCardEffect(Player* player, const int& type);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~LevelCardEffect();

	/// <summary>
	/// ����������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// �L�[�őI������Ă���
	/// </summary>
	void SelectKey();

	/// <summary>
	/// �L�[�őI������Ă��Ȃ�
	/// </summary>
	void SelectNotKey();

	/// <summary>
	/// �ޏo����
	/// </summary>
	void Exit();

	/// <summary>
	/// �`�悷��
	/// </summary>
	void Draw();

	/// <summary>
	/// �J�[�h�̒��Ƀ}�E�X�J�[�\���������ė���
	/// </summary>
	/// <param name="mousePosition">�}�E�X�J�[�\���̍��W</param>
	bool InMouseCarsor(const DirectX::SimpleMath::Vector2& mousePosition);

	/// <summary>
	/// �N���b�N���ꂽ
	/// </summary>
	void Click();

	//	���ߍ��݊֐�
private:

	//	���W���w��n��
	void ResetPosition();
	//	�傫����������
	void ResizeScale();
};