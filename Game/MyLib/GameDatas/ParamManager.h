//	
//		File Name �F ParamManager.h
//		Production�F 2023/4/02
//		Author�@�@�F �Γc ����	
// 
//		�p�����[�^�}�l�[�W���[
//	
#pragma once

namespace MyLib
{
	class ParamManager
	{
	public:

		//	�擾
		static ParamManager* GetInstane();

	private:

		//	���g�̃|�C���^�[�̊i�[��
		static std::unique_ptr<ParamManager> m_paramManager;
	};
}