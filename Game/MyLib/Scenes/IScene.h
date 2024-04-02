//
//		File Name �F IScene.h
//		Production�F 2023/9/14
//		Author�@�@�F �Γc ����
//
#pragma once

//	�C���^�[�t�F�C�X��錾����
interface IScene
{
	//	���z�f�X�g���N�^
	virtual ~IScene() = default;
	//	����������
	virtual void Initialize() = 0;
	//	�X�V����
	virtual void Update(const DX::StepTimer& timer) = 0;
	//	�`�揈��
	virtual void Render() = 0;
	//	�I������	
	virtual void Finalize() = 0;
};

