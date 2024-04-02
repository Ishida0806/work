//
//		File Name �F ResourcesData.cpp
//		Production�F 2023/6/12
//		Author�@�@�F �Γc ����	
// 
//		���\�[�X�f�[�^�ւ̃|�C���^���쐬����N���X
//	
#include "pch.h"
#include "ResourcesData.h"

//	�A�h���X
std::unique_ptr<MyLib::ResourcesData> MyLib::ResourcesData::m_resources = nullptr;

/// <summary>
///  Resources�N���X�̃C���X�^���X���擾����
/// </summary>
/// <returns>�|�C���^�[</returns>
MyLib::ResourcesData* const MyLib::ResourcesData::GetInstance()
{
	if (m_resources == nullptr)
	{
		// Resources�N���X�̃C���X�^���X�𐶐�����
		m_resources.reset(new ResourcesData());
	}
	// Resources�N���X�̃C���X�^���X��Ԃ�
	return m_resources.get();
}

/// <summary>
/// �R���X�g���N�^
/// </summary>
MyLib::ResourcesData::ResourcesData()
	:
	m_device(nullptr),
	m_screen(nullptr)
{
}

/// <summary>
/// ����������
/// </summary>
void MyLib::ResourcesData::Initialize()
{
	//	�f�o�C�X
	m_device = m_screen->GetDeviceResources()->GetD3DDevice();
	//	�X�N���[�����\�[�X
	m_screen = MyLib::ScreenResources::GetInstance();
	// ���\�[�X�f�B���N�g����ݒ肷��
	m_screen->GetFX()->SetDirectory(L"Resources/CMO");
} 

/// <summary>
/// �摜��ǉ�����
/// </summary>
/// <param name="path">�摜�̖��O</param>
void MyLib::ResourcesData::AddShaderResourceView(std::wstring path)
{
	std::wstring fliepath = L"Resources/Textures/" + path + L".png";

	DirectX::CreateWICTextureFromFile
	(
		m_device,
		fliepath.c_str(),
		nullptr,
		m_texturesData[path].ReleaseAndGetAddressOf()
	);
}

/// <summary>
/// ���f����ǉ�����
/// </summary>
/// <param name="path">���f���̖��O</param>
void MyLib::ResourcesData::AddModel(std::wstring path)
{
	std::wstring fliepath = L"Resources/CMO/" + path + L".cmo";

	m_modelsData[path] = DirectX::Model::CreateFromCMO
	(
		m_device,
		fliepath.c_str(),
		*m_screen->GetFX()
	);
}
