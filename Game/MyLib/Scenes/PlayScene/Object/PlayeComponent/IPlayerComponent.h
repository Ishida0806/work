//
//		File Name �F IPlayerComponent.h
//		Production�F 2023/12/25
//		Author�@�@�F �Γc ����	
// 
//		�v���C���[�̊e�p�[�c�����̃C���^�[�t�F�C�X
//	
#pragma once

class Player;
class Object;

__interface IPlayerComponent
{
	//	����������
	void Initialize();
	//	���i���X�V����
	void UpdateParts(const DX::StepTimer& timer);
	//	���S�A�j���[�V����
	void DeathAnimation(const DX::StepTimer& timer);
	// �����A�j���[�V����
	void WinAnimation(const DX::StepTimer& timer);
	//	���f���̕`��
	void DrawModel(DirectX::Model* model, const DirectX::SimpleMath::Matrix& world, const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj);
};