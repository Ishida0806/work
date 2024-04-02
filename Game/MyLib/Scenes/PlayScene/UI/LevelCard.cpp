
#include "pch.h"
#include "LevelCard.h"

#include "../Object/Player.h"
#include "../PlayScene.h"

//	�w�i�摜�̒��S�_
const DirectX::SimpleMath::Vector2 LevelCard::BACKGROUND_ORIGIN_POSITION = { 699.0f,370.0f };
//	�ҋ@����
const float						   LevelCard::WAIT_SECONDS				 = 0.82f;


/// <summary>
///	�R���X�g���N�^
/// </summary>
/// <param name="playScene">�v���C�V�[��</param>
/// <param name="player">�v���C���[</param>
LevelCard::LevelCard(PlayScene* playScene, Player* player)
	:m_playScene(playScene),
	m_player(player),
	m_playerLevel(1),
	m_selectCard(0),
	m_standbyTime(0.0f),
	m_isClick(false),
	m_finStand(false)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
LevelCard::~LevelCard()
{
}

/// <summary>
/// ����������
/// </summary>
void LevelCard::Initialize()
{
	int maxNum = static_cast<int>(CardType::OverID);

	//	�J�[�h��3�����
	for (int index = 0; index < maxNum; index++)
	{
		m_cards.push_back
		(
			std::make_unique<LevelCardEffect>
			(
				m_player, 
				index
			)
		);
		//	���������s��
		m_cards[index]->Initialize();
	}
	//	�w�i�摜�̍쐬
	m_backGround = std::make_unique<LevelCardBackGround>();
	//	�w�i�摜�̏�����
	m_backGround->Initialize();
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="timer">�^�C�}�[</param>
/// <returns>�g�p���</returns>
bool LevelCard::Update(const DX::StepTimer& timer)
{
	//	�v���C���[�̃��x���ő�l
	int playerMaxLevel = m_player->GetPlayerEXPoint()->MAX_PLAYER_LEVEL;

	//	�v���C���[�̃��x���̍ő�l�𒴂��Ă�����A��
	if (m_playerLevel >= playerMaxLevel)	return false;

	//	�v���C���[�̃��x�����オ�������H
	if (m_player->GetPlayerLevel() == m_playerLevel)	return false;
	
	//	�ҋ@���͏������s��Ȃ�
	//	�o�ߎ��Ԃ𑫂�
	if (m_standbyTime <= WAIT_SECONDS) { m_standbyTime += static_cast<float>(timer.GetElapsedSeconds()); }else { m_finStand = true; }

	//	�L�[�̍X�V
	KeyUpdate();

	//	�}�E�X�̍X�V
	if (MouseUpdate())	return true;

	//	�N���b�N���ꂽ
	if (ClickedCard())	return true;

	return false;
}

/// <summary>
/// �`�悷��
/// </summary>
void LevelCard::Draw()
{
	//	�w�i�摜�̕`��
	m_backGround->Draw();

	for (const auto& card : m_cards)
	{
		card->Draw();
	}	
}

/// <summary>
/// �L�[�̑���
/// </summary>
bool LevelCard::KeyUpdate()
{
	//	�L�[����
	auto input = MyLib::InputSystem::GetInstance()->GetKeyTracer();

	//	�����𖞂������I�u�W�F�N�g�̐��𐔂���
	__int64 redyCount = std::count_if
	(
		m_cards.begin(), m_cards.end(),
		[&](const std::unique_ptr<LevelCardEffect>& card)
		{
			return !card->IsClickAble();
		}
	);

	//	�ő�l���擾
	int overID = static_cast<int>(LevelCard::CardType::OverID);

	//	�N���b�N���ꂽ�珈�����s��Ȃ�
	if (!m_isClick && redyCount == overID)
	{
		//	�ҋ@���ԂȂ�A��
		if (!m_finStand)	return false;

		//	D�L�[�������ꂽ
		if (input->pressed.D)
		{
			//	�E�Ɉ�i��
			m_selectCard++;
			//	�����Ă���0�ɂ���
			m_selectCard %= overID;
			//	�ŏ���������炷
			AudioManager::GetInstance()->PlaySoundEffectSE(L"inCard");
		}
		//	A�L�[�������ꂽ
		if (input->pressed.A)
		{
			m_selectCard--;

			//	�ŏ���������炷
			AudioManager::GetInstance()->PlaySoundEffectSE(L"inCard");

			if (m_selectCard < 0)
			{
				//	��ԉE�ɂ���
				m_selectCard = overID - 1;
			}
		}

		for (int index = 0; index < m_cards.size(); ++index)
		{
			//	�I������Ă���J�[�h�����I���\�ɂ���
			if (index == m_selectCard)
			{
				m_cards[index]->SelectKey();
			}
			else
			{
				m_cards[index]->SelectNotKey();
			}
		}

		if (input->pressed.Space)
		{
			//	�J�[�h�N���b�N���̏���
			m_cards[m_selectCard]->Click();
			//	�N���b�N���ꂽ
			m_isClick = true;
			//	�S���N���b�N��Ԃ�
			for (const auto& card2 : m_cards)
			{
				card2->SetClick();
			}

			return true;
		}
	}

	return false;
}

/// <summary>
/// �}�E�X�̍X�V
/// </summary>
/// <returns>�g�p���</returns>
bool LevelCard::MouseUpdate()
{
	//	�v���C���[�̃��x�����オ�������H && �N���b�N���ꂽ�珈�����s��Ȃ�
	if (!m_isClick)
	{
		//	�}�E�X
		auto mouse = MyLib::InputSystem::GetInstance()->GetStateTracker();
		//	�L�[����
		auto input = MyLib::InputSystem::GetInstance()->GetKeyTracer();

		//	�w�i�摜�̍X�V
		m_backGround->Update();

		//	�J�[�h
		for (int index = 0; index < m_cards.size(); ++index)
		{
			//	�������Ȃ��߂�
			if (m_cards[index]->IsReady())	continue;

			//	�X�V����
			m_cards[index]->Update();

			//	�}�E�X�����ɓ����Ă��Ȃ��Ȃ�A��
			if (!m_cards[index]->InMouseCarsor(GetMousePosition()))	continue;

			//	�ҋ@���ԂȂ�A��
			if (!m_finStand)	continue;

			//	�Z���N�g�\�Ȕԍ�������Ȃ����Ă�����
			if (m_cards[index]->IsClickAble())	m_selectCard = index;

			//	�N���b�N�\���H
			if (m_cards[index]->IsClickAble() && mouse->leftButton == mouse->PRESSED ||
				m_cards[index]->IsClickAble() && input->pressed.Space)
			{
				//	�J�[�h�N���b�N���̏���
				m_cards[index]->Click();
				//	�N���b�N���ꂽ
				m_isClick = true;
				//	�S���N���b�N��Ԃ�
				for (const auto& card2 : m_cards)
				{
					card2->SetClick();
				}

				return true;
			}			
		}

		return true;
	}

	return false;
}

/// <summary>
/// �N���b�N���ꂽ
/// </summary>
/// <returns>�g�p���</returns>
bool LevelCard::ClickedCard()
{
	//	�N���b�N�����ꂽ�牺�փt�F�[�h�A�E�g����
	if (m_isClick)
	{
		//	�w�i�摜������
		m_backGround->Exit();

		for (const auto& card : m_cards)
		{
			//	����������Ȃ��Ȃ��߂�
			if (!card->IsReady())	continue;

			card->Exit();
		}

		//	�����𖞂������I�u�W�F�N�g�̐��𐔂���
		__int64 redyCount = std::count_if
		(
			m_cards.begin(), m_cards.end(),
			[&](const std::unique_ptr<LevelCardEffect>& card)
			{
				return !card->IsReady();
			}
		);

		//	�ő�l�l
		int maxCount = static_cast<__int64>(CardType::OverID);

		//	�ő吔�Ɠ����Ȃ�I���
		if (redyCount == maxCount)
		{
			m_isClick = false;
			//	���x�����オ����
			m_playerLevel++;
			//	�ҋ@���Ԃ����Z�b�g
			m_standbyTime = 0.0f;
			m_finStand = false;
		}
	}

	return false;
}

/// <summary>
/// �}�E�X���W���擾����
/// </summary>
/// <returns>�}�E�X���W</returns>
DirectX::SimpleMath::Vector2 LevelCard::GetMousePosition()
{
	//	�}�E�X�̏�Ԃ��擾
	auto state = DirectX::Mouse::Get().GetState();
	//	�}�E�X�J�[�\���̍��W
	return DirectX::SimpleMath::Vector2(static_cast<float>(state.x), static_cast<float>(state.y));
}
