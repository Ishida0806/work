//
//		File Name �F ScreenResources.h
//		Production�F 2023/6/01
//		Author�@�@�F �Γc ����	
//
#pragma once

#include "Common/DeviceResources.h"

namespace MyLib
{
	class ScreenResources final
	{
	private:
		// �X�N���[�����\�[�V�[�Y�N���X�̃C���X�^���X�ւ̃|�C���^
		static std::unique_ptr<ScreenResources>		 m_screenResources;
		// �G�t�F�N�g�t�@�N�g���[					  
		std::unique_ptr<DirectX::EffectFactory>		 m_effectFactory;
		//	�X�v���C�g�G�t�F�N�g					   
		std::unique_ptr<DirectX::BasicEffect>		 m_batchEffect;
		//	�X�v���C�g�o�b�`						 
		std::unique_ptr<DirectX::SpriteBatch>		 m_spriteBatch;
		//	�X�v���C�g�t�H���g					    
		std::unique_ptr<DirectX::SpriteFont>		 m_spriteFont;
		// ���ʃX�e�[�g�I�u�W�F�N�g�ւ̃|�C���^	   
		std::unique_ptr<DirectX::CommonStates>		 m_states;
		//	�C���v�b�g���C�A�E�g���쐬
		Microsoft::WRL::ComPtr<ID3D11InputLayout>	 m_inputLayout;

		//�X�N���[���T�C�Y(�����A�c��)
		int m_screen_W;
		int m_screen_H;

		// �r���[�s��
		DirectX::SimpleMath::Matrix m_view;
		// �ˉe�s��
		DirectX::SimpleMath::Matrix m_projection;

		// �f�o�C�X
		ID3D11Device* m_device;
		// �f�o�C�X�R���e�L�X�g
		ID3D11DeviceContext* m_context;

		//	�A�N�Z�T
	public:
		//	�X�N���[���̃C���X�^���X���擾����
		static ScreenResources*											const GetInstance();
		//	�f�o�C�X���\�[�X���擾����
		inline DX::DeviceResources* GetDeviceResources()				const { return DX::DeviceResources::GetInstance(); }
		//	�R�����X�e�[�g���擾����
		inline DirectX::CommonStates* GetCommonState()					const { return m_states.get(); }
		//	�G�t�F�N�g���t�@�N�g���N���X�̃C���X�^���X���擾����
		inline DirectX::EffectFactory* GetFX()							const { return m_effectFactory.get(); }
		//	�x�[�V�b�N�G�t�F�N�g���擾����
		inline DirectX::BasicEffect* GetBasicEffect()					const { return m_batchEffect.get(); }
		//	�X�v���C�g�o�b�`���擾����
		inline DirectX::SpriteBatch* GetSpriteBatch()					const { return m_spriteBatch.get(); }
		//	�C���v�b�g���C�A�E�g�̍쐬
		inline ID3D11InputLayout* GetInputLayout()						const { return m_inputLayout.Get(); }
		// �r���[�s����擾����
		inline const DirectX::SimpleMath::Matrix& GetViewMatrix()		const { return m_view; };
		// �ˉe�s����擾����
		inline const DirectX::SimpleMath::Matrix& GetProjectionMatrix()	const { return m_projection; }
		//	�R���e�L�X�g���擾����
		inline ID3D11DeviceContext* GetDeviceContext()					const { return m_context; }
		// �f�o�C�X���擾����
		inline ID3D11Device* GetDevice()								const { return m_device; }
		//	�X�N���[���T�C�Y���擾����
		void GetScreenSize(int& screenWeight, int& screenHeight);
		//	�X�N���[���T�C�Y��ݒ肷��
		void SetScreenSize(const int& width, const int& height);
		// �r���[�s���ݒ肷��
		void SetViewMatrix(const DirectX::SimpleMath::Matrix& view);
		// �ˉe�s���ݒ肷��
		void SetProjectionMatrix(const DirectX::SimpleMath::Matrix& projection);

	private:

		//	�R���X�g���N�^
		ScreenResources();

	public:

		void Initialize();
		void RenderDebugFont(const wchar_t* character , const DirectX::SimpleMath::Vector2 position );
	};
}
