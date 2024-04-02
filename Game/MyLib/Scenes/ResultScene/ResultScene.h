//
//		File Name �F ResultScene.h
//		Production�F 2023/9/14
//		Author�@�@�F �Γc ����
//
#pragma once
#include "Game/MyLib/Scenes/IScene.h"
#include "Game/MyLib/Scenes/ResultScene/PushSeal.h"
#include "Game/MyLib/Scenes/ResultScene/ScoreOutPut.h"
#include "Game/MyLib/Scenes/ResultScene/OutPutResultUI.h"
#include "Game/MyLib/Scenes/ResultScene/ValuationScore.h"
#include "Game/MyLib/Scenes/ResultScene/ResultBackGround.h"

interface IScene;

class ResultScene : public IScene
{
	//	�萔
public:

	//	�ȒP�ȓ�Փx�̉��Z����
	static const float EASY_ADDITION;
	//	�ʏ�̓�Փx�̉��Z����
	static const float NORMAL_ADDITION;
	//	�����Փx�̉��Z����
	static const float HARD_ADDITION;
	//	�G���h���X��Փx�̉��Z����
	static const float ENDRES_ADDITION;
	//	PUSHUI�̍��W
	static const DirectX::SimpleMath::Vector2 PUSH_SPACE_POSITION;
	//	PUSHUI�̐^�񒆍��W
	static const DirectX::SimpleMath::Vector2 PUSH_SPACE_ORIGIN_POSITION;


	//	�ϐ�
private:
	//	�Q�[��
	Game*								m_game;
	//	�X�N���[�����\�[�X
	MyLib::ScreenResources*				m_screen;
	//	���\�[�V�[�Y�f�[�^
	MyLib::ResourcesData*				m_resorces;
	//  �w�i�摜
	ID3D11ShaderResourceView*			m_backGroundTexture;
	//	�w�i�̃e�[�u��
	ID3D11ShaderResourceView*			m_tableBackGroundTexture;
	//	���q
	std::unique_ptr<PushSeal>			m_pushSeal;
	//	�X�R�A�A�E�g�v�b�g
	std::unique_ptr<ScoreOutPut>		m_scoreOutPut;
	//	�X�R�A��]������
	std::unique_ptr<ValuationScore>		m_valucationScore;
	//	�w���L�[
	std::unique_ptr<OutPutResultUI>		m_pushSpase;
	//	�w�i�摜
	std::unique_ptr<ResultBackGround>	m_resultBackGround;
	//	�I������
	float								m_finishedTime;
	//	�Z���N�g���ꂽ�X�e�[�W
	int									m_stageNum;
	//	�t���O�����߂�
	bool								m_judScore;
	//	�I���t���O
	bool								m_isFinished;

	//	�֐�
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="game">�Q�[��</param>
	ResultScene(Game* game, int stageSelect = 0);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~ResultScene();

	//	����������
	void Initialize() override;
	//	�X�V����
	void Update(const DX::StepTimer& timer) override;
	//	�`�揈��
	void Render() override;
	//	�I������	
	void Finalize() override;

private:

	//	�f�o�C�X�ˑ��̃��\�[�X
	void CreateDeviceDependentResources();
};
