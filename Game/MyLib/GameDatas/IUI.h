//
//		File Name �F IUI.h
//		Production�F 2023/10/2
//		Author�@�@�F �Γc ����
// 
//		UI�̃C���^�[�t�F�C�X
//
#pragma once
#include "pch.h"

interface IUI
{
	//	�f�t�@�N�g�f�X�g���N�^
	virtual ~IUI() = default;
	//	����������
	virtual void Initialize() = 0;
	//	�X�V����
	virtual void Update(const DX::StepTimer& timer) = 0;
	//	�`�悷��
	virtual void Draw() = 0;
};