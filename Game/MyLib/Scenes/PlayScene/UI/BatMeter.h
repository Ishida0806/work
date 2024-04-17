//
//		File Name �F PlayerUI.h
//		Production�F 2023/10/2
//		Author�@�@�F �Γc ����
// 
#pragma once
#include "Game/MyLib/GameDatas/IUI.h"

interface IUI;
class Sord;

class BatMeter : public IUI
{
	//	�A�N�Z�T
public:

	//	�\�[�h�̃|�C���^�[��ݒ肷��
	void SetSord(Sord* sord);

	//	�萔
public:

	//	�o�b�g���[�^�[�̐^��
	static const DirectX::SimpleMath::Vector2 ORIGIN_BAT_METER;
	//	�o�b�g���[�^�[�̑��̐^��
	static const DirectX::SimpleMath::Vector2 ORIGIN_BAT_SIDE_METER;
	//	�o�b�g���[�^�[�̍��W
	static const DirectX::SimpleMath::Vector2 BAT_METER_POSITION;
	//	�o�b�g���[�^�[���̂̍��W
	static const DirectX::SimpleMath::Vector2 BAT_SIDE_METER_POSITION;

	//	�ϐ�
private:

	//	�\�[�h
	Sord*							m_sord;
	//	�X�N���[�����\�[�X
	MyLib::ScreenResources*			m_screen;
	//	���\�[�V�[�Y�f�[�^
	MyLib::ResourcesData*			m_resources;
	//	���q�̏��������v���C���[�̉摜
	ID3D11ShaderResourceView*		m_batMeter;
	//	���񂾂Ƃ��̉摜
	ID3D11ShaderResourceView*		m_batSideMeter;
	//	�o�b�g���[�^�[���W
	DirectX::SimpleMath::Vector2    m_batMeterPosition;
	//	�o�b�g�T�C�h���[�^�[���W
	DirectX::SimpleMath::Vector2	m_batMeterSidePosition;

	//	�֐�
public:

	//	�R���X�g���N�^
	BatMeter();
	//	�f�X�g���N�^
	~BatMeter();

	//	����������
	void Initialize() override;
	//	�X�V����
	void Update(const DX::StepTimer& timer) override;
	//	�`�悷��
	void Draw() override;

	//	���ߍ��݊֐�
private:
	//	�f�o�C�X�ˑ��̃��\�[�X�̏�����
	void CreateDeviceDependentResources();
};