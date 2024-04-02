//
//		File Name �F PlayerExperiencePointUI.cpp
//		Production�F 2023/11/30
//		Author�@�@�F �Γc ����	
// 
//		�o���l���Ǘ��擾����
//	
#include "pch.h"
#include "PlayerExperiencePointUI.h"

#include "Game/MyLib/Scenes/PlayScene/Object/Player.h"

//	MAX�摜�̍��W
const  DirectX::SimpleMath::Vector2  PlayerExperiencePointUI::MAX_POSITION = { 300.0f,80.0f };
//	�̗̓o�[�p�̍��W
const float							 PlayerExperiencePointUI::EXP_POS	   = 418.0f;
//	�̗̓o�[��X���W
const int							 PlayerExperiencePointUI::EXP_IX	   = 153;
//	�̗̓o�[��Y���W
const int							 PlayerExperiencePointUI::EXP_IY	   = 95;
//	�̗̓o�[�̍���
const int							 PlayerExperiencePointUI::EXP_IH	   = 15;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="player">�v���C���[</param>
PlayerExperiencePointUI::PlayerExperiencePointUI(Player* player)
	:m_player(player),
	m_barTexture(nullptr),
	m_maxTexture(nullptr),
	m_exBar(0.0f)
{
	//	�o�[�摜
	m_barTexture = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"HPBar");
	//	�o���lMAX�摜
	m_maxTexture = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"EXPmax");
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayerExperiencePointUI::~PlayerExperiencePointUI()
{
}

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void PlayerExperiencePointUI::Update(const DX::StepTimer& timer)
{
	UNREFERENCED_PARAMETER(timer);

	//	�o���l
	int exp		= m_player->GetPlayerEXPoint()->GetExperiencePoint();
	//	�o���l�K�v�ȏ��
	int needEXP = m_player->GetPlayerEXPoint()->GetNeedExperiencePoint();
	//	�ǂ̂��炢�̊����H
	float decimal = 0.0f;

	//	���x�����ő�l�𒴂��Ă�����A��
	if (m_player->GetPlayerLevel() >= m_player->GetPlayerEXPoint()->MAX_PLAYER_LEVEL)	
	{
		//	���W�������
		m_exBar = EXP_POS;
		return;
	}

	//	�o���l��0�Ȃ�s��Ȃ�
	if (exp <= 0.0f)
	{
		m_exBar = 0.0f;	
	}
	else
	{
		//	�̗͂ɂ���ďꏊ�����炷
		decimal = static_cast<float>(exp) / static_cast<float>(needEXP);
	}

	//	���X�Ɉړ�
	m_exBar = Utility::Lerp(0.0f, static_cast<float>(EXP_POS), decimal);
}

/// <summary>
/// �`�悷��
/// </summary>
void PlayerExperiencePointUI::Draw()
{	
	DirectX::SpriteBatch* spriteBatch = MyLib::ScreenResources::GetInstance()->GetSpriteBatch();

	//	�o�[�摜�̕`��
	spriteBatch->Draw
	(
		m_barTexture,
		DirectX::SimpleMath::Rectangle(EXP_IX, EXP_IY, static_cast<int>(m_exBar), EXP_IH),
		DirectX::Colors::Blue
	);
	
	//	���x�����ő�l�Ɠ����Ȃ�`��
	if (m_player->GetPlayerLevel() == m_player->GetPlayerEXPoint()->MAX_PLAYER_LEVEL)
	{
		//	MAX�摜�̕`��
		spriteBatch->Draw
		(
			m_maxTexture,
			MAX_POSITION
		);
	}
}
