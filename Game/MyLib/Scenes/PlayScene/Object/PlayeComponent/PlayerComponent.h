//
//		File Name �F PlayerComponent.h
//		Production�F 2023/12/25
//		Author�@�@�F �Γc ����	
// 
//		�v���C���[�̊e�p�[�c�����̊��N���X
//	
#pragma once
#include "../Object.h"
#include "../Player.h"
#include "IPlayerComponent.h"

class Player;
class Object;

class PlayerComponent : public Object, public IPlayerComponent
{
	//	�A�N�Z�T
public:

	//	��ԏ�̐e���擾����
	Player* GetRoot()	{ return m_root; }
	//	�e���擾����
	Object* GetParent() { return m_parent; }

	//	�ϐ�
private:

	//	��ԏ�̐e
	Player* m_root;
	//	�e
	Object* m_parent;

	//	�֐�
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="root">���[�g</param>
	/// <param name="paren">�e</param>
	PlayerComponent(Player* root, Object* parent)
		:m_root(root),
		m_parent(parent)
	{
	}

	//	�f�X�g���N�^
	~PlayerComponent() override {};

	/// <summary>
	/// ����������
	/// </summary>
	void Initialize() override {};
	
	/// <summary>
	/// ���i���X�V����
	/// </summary>
	/// <param name="timer">�^�C�}�[</param>
	void UpdateParts(const DX::StepTimer& timer) override { UNREFERENCED_PARAMETER(timer); }

	/// <summary>
	/// ���S�A�j���[�V����
	/// </summary>
	/// <param name="timer">�^�C�}�[</param>
	void DeathAnimation(const DX::StepTimer& timer) override { UNREFERENCED_PARAMETER(timer); }

	/// <summary>
	/// �����A�j���[�V����
	/// </summary>
	/// <param name="timer">�^�C�}�[</param>
	void WinAnimation(const DX::StepTimer& timer) override { UNREFERENCED_PARAMETER(timer); }
	
	/// <summary>
	/// ���f���̕`��
	/// </summary>
	/// <param name="model">���f��</param>
	/// <param name="world">���[���h</param>
	/// <param name="view">�r���[</param>
	/// <param name="proj">�v���W�F�N�V����</param>
	void DrawModel(DirectX::Model* model, const DirectX::SimpleMath::Matrix& world, const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj) override
	{
		model->Draw
		(
			MyLib::ScreenResources::GetInstance()->GetDeviceContext(),
			*MyLib::ScreenResources::GetInstance()->GetCommonState(),
			world,
			view,
			proj
		);
	}
};