#pragma once

//	�C���^�[�t�F�C�X��錾����
interface ICursorComponent
{
	// �e���擾����
	virtual ICursorComponent* GetParent() = 0;
	// �ʒu���擾����
	virtual DirectX::SimpleMath::Vector3	GetPosition() = 0;
	//	��]�p��ݒ肷��
	virtual DirectX::SimpleMath::Quaternion GetRotate() = 0;
	// ��]�p���擾����
	virtual float GetAngle() = 0;
	// ���f�����擾����
	virtual DirectX::Model* GetModel() = 0;
	//	���z�f�X�g���N�^
	virtual ~ICursorComponent() = default;
	//	����������
	virtual void Initialize() = 0;
	//	�X�V����
	virtual void Update(const DX::StepTimer& timer) = 0;
	//	�`�揈��
	virtual void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj) = 0;
	//	�I������	
	virtual void Finalize() = 0;
};