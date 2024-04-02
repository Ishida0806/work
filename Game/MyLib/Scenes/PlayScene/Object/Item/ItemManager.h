//
//		File Name �F ItemManager.h
//		Production�F 2023/12/1
//		Author�@�@�F �Γc ����	
//
#pragma once
#include "../Item/Item.h"

class Item;

class ItemManager
{
	//	�A�N�Z�T
public:

	//	�A�C�e�����擾����
	inline std::vector<std::shared_ptr<Item>>& GetItem()		noexcept { return m_items; };

	//	�萔
public:

	//	�o������ꏊ
	static const float SPAWN_PLACE;
	//	�o�����鎞��
	static const float SPAWN_TIME;
	//	�������E��
	static const int   SPAWN_ITEM;

	//	�ϐ�
private:

	//	�A�C�e���B
	std::vector<std::shared_ptr<Item>> m_items;
	//	�o������
	float							   m_spwanItemTime;

	//	�֐�
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	ItemManager();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~ItemManager();

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
	/// <param name="view">�r���[�v���W�F�N�V����</param>
	/// <param name="proj">�r���[</param>
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj);

	/// <summary>
	/// �I������
	/// </summary>
	void Finalize();

	//	���ߍ��݊֐�
private:

	/// <summary>
	/// �A�C�e�����o������
	/// </summary>
	void SpawnItem(const DX::StepTimer& timer);

	/// <summary>
	/// �擾�����A�C�e���������
	/// </summary>
	void TookItems();
};