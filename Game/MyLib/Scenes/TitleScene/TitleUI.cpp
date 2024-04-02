//
//		File Name �F TitleUI.cpp
//		Production�F 2023/11/11
//		Author�@�@�F �Γc ����
// 
//		�^�C�g���ŕ`�悷����̂̊��N���X
//
#include "pch.h"
#include "TitleUI.h"

//	�摜�̃f�t�H���g�̑傫��
const DirectX::SimpleMath::Vector2 TitleUI::BASE_SCALE = DirectX::SimpleMath::Vector2(0.9f, 0.9f);

/// <summary>
/// �R���X�g���N�^
/// </summary>
TitleUI::TitleUI() 
{
}

/// <summary>
/// �`�悷��
/// </summary>
/// <param name="texture">�摜</param>
/// <param name="position">���W</param>
/// <param name="color">�F</param>
/// <param name="angele">�p�x</param>
/// <param name="originPosition">���S���W</param>
/// <param name="scale">�傫��</param>
void TitleUI::Draw(ID3D11ShaderResourceView* texture, DirectX::SimpleMath::Vector2 position, DirectX::SimpleMath::Color	 color, float angle, DirectX::SimpleMath::Vector2 originPosition, DirectX::SimpleMath::Vector2 scale)
{
	DirectX::SpriteBatch* spriteBatch = MyLib::ScreenResources::GetInstance()->GetSpriteBatch();

	spriteBatch->Draw
	(
		texture,
		position,
		nullptr,
		color,
		angle,
		originPosition,
		scale
	);
}