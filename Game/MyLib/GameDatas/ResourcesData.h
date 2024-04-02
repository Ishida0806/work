//
//		File Name �F ResourcesData.h
//		Production�F 2023/6/12�i�������F10/25�j
//		Author�@�@�F �Γc ����	
//	
#pragma once
#include <unordered_map>

// Resources�N���X���`����
namespace MyLib
{
	class ResourcesData
	{
		//	�A�N�Z�T
	public:

		/// <summary>
		/// �摜���擾����
		/// </summary>
		/// <param name="path">�p�X</param>
		/// <returns>ID3D11ShaderResourceView</returns>
		inline ID3D11ShaderResourceView* GatShaderResourceView(const std::wstring& path) const { return m_texturesData.at(path).Get(); }

		/// <summary>
		/// ���f�����擾����
		/// </summary>
		/// <param name="path">�p�X</param>
		/// <returns>Model</returns>
		inline DirectX::Model* GatModel(const std::wstring& path)						 const { return m_modelsData.at(path).get(); }
			
		/// <summary>
		/// �摜�̗v�f��ǉ�����
		/// </summary>
		/// <param name="path">�p�X</param>
		void AddShaderResourceView(std::wstring path);

		/// <summary>
		/// ���f����ǉ�����
		/// </summary>
		/// <param name="path">�p�X</param>
		void AddModel(std::wstring path);


	public:
		// Resouces�N���X�̃C���X�^���X���擾����
		static ResourcesData* const GetInstance();
		//	����������
		void Initialize();

	private:
		// �R���X�g���N�^
		ResourcesData();
		// ����͋��e���Ȃ�
		void operator=(const ResourcesData& object) = delete;
		// �R�s�[�R���X�g���N�^�͋��e���Ȃ�
		ResourcesData(const ResourcesData& object) = delete;

	private:
		// Resources�N���X�̃C���X�^���X�ւ̃|�C���^
		static std::unique_ptr<ResourcesData> m_resources;
		// �O���t�B�b�N�X
		MyLib::ScreenResources*															   m_screen;
		// �f�o�C�X
		//Microsoft::WRL::ComPtr<ID3D11Device>											   m_device;
		ID3D11Device* m_device;
		//	�摜�̃f�[�^
		std::unordered_map<std::wstring, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> m_texturesData;
		//	���f���̃f�[�^
		std::unordered_map<std::wstring, std::unique_ptr<DirectX::Model>>				   m_modelsData;
	};
}