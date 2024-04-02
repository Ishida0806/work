//
//		File Name �F FallingCherryBlossoms.h
//		Production�F 2023/11/12
//		Author�@�@�F �Γc ����	
//	
#pragma once
#include "../Object.h"
#include "../Player.h"

class FallingCherryBlossoms : public Object
{
	//	�萔
public:

	//	���g�̃����_���ȍ��W
	static const float RANDOM_MINE_POSITION;

	//	�ϐ�
private:
	//	�v���~�e�B�u�o�b�`
	std::unique_ptr<DirectX::GeometricPrimitive>	m_primitive;
	//	�F
	DirectX::SimpleMath::Color						m_colors;
	//	�v���C���[
	Player*											m_player;
	//	���������ŏo������Y���W
	float											m_randamSpawnYPosition;
	//	�����_���Ȍ���
	float											m_randamDirection;

	//	�֐�
public:
	//	�R���X�g���N�^
	FallingCherryBlossoms(Player* player);
	//	�f�X�g���N�^
	~FallingCherryBlossoms();
	//	������
	void Initialize() override;
	//	�X�V
	void Update(const DX::StepTimer& timer) override;
	//	�`��
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj) override;
	//	�I������
	void Finalize() override;
};