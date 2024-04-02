//
//		File Name �F Item.h
//		Production�F 2023/12/1
//		Author�@�@�F �Γc ����	
//
#pragma once
#include "../Object.h"
#include "../ItemCapsule/ItemCapsule.h"

class Object;

class Item : public Object
{
	//	�񋓌^
public:

	//	�A�C�e���̎��
	enum class ItemType
	{
		None = 0,

		Recovery,
		Reflect,
		PowUp,

		OverID
	};

	//	�A�N�Z�T
public:	


	//	�����蔻��̎擾
	Collision::Shape::Sphere GetSpere()			const { return m_sphere; }
	//	�A�C�e�����^�C�v���擾����
	ItemType				 GetItemType()		const { return m_itemType; }
	//	�A�C�e�����擾����	
	bool					 IsTookItem()		const { return m_isTookItem; }
	//	�擾�A�j���[�V���������H
	bool					 IsTookAnimation()	const { return m_isTookAnimation; }
	//	�����蔻���ݒ肷��
	void SetSphere(const Collision::Shape::Sphere& sphere);

	//	�萔
public:

	//	�o�ߎ��Ԃ𑁂߂�
	static const float INCREASE_TIMER;
	//	�T�C���g������������
	static const float LIMITS_VALUE;
	//	�傫��������������l
	static const float SCALE_SMALLER_VALUE;

	//	�ϐ�
private:

	//�A�C�e���̎��
	ItemType									 m_itemType;
	//	�����蔻��
	Collision::Shape::Sphere					 m_sphere;
	//	�A�C�e���̃J�v�Z��
	std::unique_ptr<ItemCapsule>				 m_itemCapsule;
	//	�o�ߎ���
	float									  	 m_elapsedTime;
	//	�v���C���[���A�C�e�����擾����
	bool										 m_isTookItem;
	//	�擾���̃A�j���[�V����
	bool										 m_isTookAnimation;

	//	�֐�
public:
	
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="position">���W</param>
	/// <param name="itemType">�A�C�e���̎��</param>
	Item(const DirectX::SimpleMath::Vector3& position, const ItemType& itemType = ItemType::None);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Item();

	/// <summary>
	/// ����������
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="timer">�^�C�}�[</param>
	void Update(const DX::StepTimer& timer) override;

	/// <summary>
	/// �`�揈��
	/// </summary>
	/// <param name="view">�r���[�v���W�F�N�V����</param>
	/// <param name="proj">�r���[</param>
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj) override;

	/// <summary>
	/// �I������
	/// </summary>
	void Finalize() override;

	/// <summary>
	/// �A�C�e�����擾���ꂽ
	/// </summary>
	void TookItem();
};