//
//		File Name �F ElapsedTime.h
//		Production�F 2023/9/07
//		Author�@�@�F �Γc ����	
//
#pragma once

namespace MyLib
{
	//	�o�ߎ��Ԃ��擾����N���X
	class ElapsedTime final
	{
		//	�A�N�Z�T
	public:

		// ElapsedTime�N���X�̃C���X�^���X���擾����
		static ElapsedTime* const GetInstance()
		{
			//	�k���|�Ȃ琶��
			if (m_elapsed == nullptr)
			{
				//	�X�N���[���N���X�̃C���X�^���X�𐶐�����
				m_elapsed.reset(new ElapsedTime());
			}
			//	�o�ߎ��ԃN���X�̃C���X�^���X���擾����
			return m_elapsed.get();
		}

		/// <summary>
		/// �o�ߎ��Ԃ�ݒ肷��
		/// </summary>
		/// <param name="elapsedTime">�o�ߎ���</param>
		inline void SetElapsedTime(float elapsedTime)
		{
			m_elapsedTime += elapsedTime;
		}

		//	�o�ߎ��Ԃ��擾����
		inline float GetElapsedTime() const { return m_elapsedTime; }

		//	�֐�
	public:

		/// <summary>
		/// �o�ߎ��Ԃ���ɂ���
		/// </summary>
		void RestElapsedTime()
		{
			m_elapsedTime = 0.0f;
		}

		//	�R���X�g���N�^
	private:

		ElapsedTime()
			:m_elapsedTime(0.0f)
		{

		}

		// ����͋��e���Ȃ�
		void operator=(const ElapsedTime& object) = delete;
		// �R�s�[�R���X�g���N�^�͋��e���Ȃ�
		ElapsedTime(const ElapsedTime& object) = delete;

		//	�ϐ�
	private:

		// ElapsedTime�N���X�̃C���X�^���X�ւ̃|�C���^
		static std::unique_ptr<ElapsedTime> m_elapsed;

		float m_elapsedTime;
	};
}

