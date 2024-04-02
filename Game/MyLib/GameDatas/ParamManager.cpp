//	
//		File Name �F ParamManager.cpp
//		Production�F 2023/4/02
//		Author�@�@�F �Γc ����	
// 
//		�p�����[�^�}�l�[�W���[
//	
#include "pch.h"
#include "ParamManager.h"

std::unique_ptr<MyLib::ParamManager> MyLib::ParamManager::m_paramManager = nullptr;

/// <summary>
/// ParamManager�̎擾
/// </summary>
/// <returns>���g�̃|�C���^�[</returns>
MyLib::ParamManager* MyLib::ParamManager::GetInstane()
{
	//	�k���|�Ȃ琶��
	if (m_paramManager == nullptr)
	{
		//	�X�N���[���N���X�̃C���X�^���X�𐶐�����
		m_paramManager.reset(new ParamManager());
	}
	//	�X�N���[�����\�[�X�N���X�̃C���X�^���X���擾����
	return m_paramManager.get();
}
