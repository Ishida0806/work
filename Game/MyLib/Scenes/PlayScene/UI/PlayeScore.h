//
//		File Name �F PlayeScore.h
//		Production�F 2023/11/27
//		Author�@�@�F �Γc ����
// 
#pragma once

#include "Game/MyLib/GameDatas/IUI.h"

class Number;
class PlayInfo;
interface IUI;

class PlayeScore : public IUI
{
	//	�萔
public:
	//	�����̍��W
	static const DirectX::SimpleMath::Vector2 NUM_POSITION;
	//	�X�R�A�̍��W
	static const DirectX::SimpleMath::Vector2 SCORE_POSITION;

	//	�ϐ�
private:

	//	�v���C�C���t�H���[�V����
	PlayInfo*					m_playInfo;
	//	�X�R�A�\��
	std::unique_ptr<Number>		m_scoreDisplay;
	//	�v���C���[�̗̑̓o�[
	ID3D11ShaderResourceView*	m_scoreBackGround;

	//	�֐�
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	PlayeScore();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~PlayeScore();

	/// <summary>
	/// ����������
	/// </summary>
	void Initialize()						override;

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="timer">�^�C�}�[</param>
	void Update(const DX::StepTimer& timer)	override;

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw()								override;

	/// <summary>
	/// �o�ߎ��Ԃ��~�߂�
	/// </summary>
	void StopElapsedTimer();

	//	���ߍ��݊֐�
private:

	//	�f�o�C�X�ˑ��̃��\�[�X�̏�����
	void CreateDeviceDependentResources();
};