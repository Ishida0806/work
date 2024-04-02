
#pragma once

class LevelCardBackGround
{
	//	�萔
public:

	//	�w�i�摜�̒��S�_
	static const DirectX::SimpleMath::Vector2 BACKGROUND_ORIGIN_POSITION;
	//	�w�i�摜�̏�����Y���W
	static const float						  BACKGROUND_RESTART_POSITION_Y;
	//	����̑���
	static const float						  IN_SPEED;
	//	�ޏ�̑���
	static const float						  EXIT_SPEED;
	//	��ɏオ�鑬��
	static const float						  EXIT_SPEED_POSITION_Y;


	//	�ϐ�
private:

	//	�w�i�摜�̍��W
	DirectX::SimpleMath::Vector2				  m_backGroundPosition;
	//	�w�i�摜�̖ڕW���W
	DirectX::SimpleMath::Vector2				  m_backGroundTargetPosition;
	//	�w�i�摜�̑傫��
	DirectX::SimpleMath::Vector2				  m_backGroundScale;
	//	�w�i�摜
	ID3D11ShaderResourceView*					  m_backGroundTexture;
	//	�N���b�N���ꂽ
	bool										  m_isClick;

	//	�֐�
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="player">�v���C���[</param>
	LevelCardBackGround();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~LevelCardBackGround();

	/// <summary>
	/// ����������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// �ޏo����
	/// </summary>
	void Exit();

	/// <summary>
	/// �`�悷��
	/// </summary>
	void Draw();

	//	���ߍ��݊֐�
private:

	//	���W�̏�����
	void ResetPosition();
};