#include "pch.h"
#include "LevelCard.h"

#include "../Object/Player.h"
#include "../PlayScene.h"

//	�w�i�摜�̒��S�_
const DirectX::SimpleMath::Vector2 LevelCard::BACKGROUND_ORIGIN_POSITION = { 699.0f,370.0f };
//	�ҋ@����
const float						   LevelCard::WAIT_SECONDS               = 0.82f;
//	�I������鐔
const int						   LevelCard::SELECT_NUMBER              = 2;


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
    m_finRandom(false),
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
        //  
        m_randomCards.push_back(index);
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
    if (m_playerLevel >= playerMaxLevel)                return false;

    //	�v���C���[�̃��x�����オ�������H
    if (m_player->GetPlayerLevel() == m_playerLevel)    return false;

    //	�ҋ@���͏������s��Ȃ� && �o�ߎ��Ԃ𑫂�
    if (m_standbyTime <= WAIT_SECONDS) { m_standbyTime += static_cast<float>(timer.GetElapsedSeconds()); } else { m_finStand = true; }

    //  �����_���őI�o�����ԍ���I��
    CreateRandomNumber(timer);

    //	�L�[�̍X�V
    KeyUpdate();

    //	�}�E�X�̍X�V
    if (MouseUpdate())    return true;

    //	�N���b�N���ꂽ
    if (ClickedCard())    return true;

    return false;
}

/// <summary>
/// �`�悷��
/// </summary>
void LevelCard::Draw()
{
    //	�w�i�摜�̕`��
    m_backGround->Draw();

    //  �퓬�̓�Ԃ����`��
    for (int index = 0; index < SELECT_NUMBER; ++index)
    {
        m_cards[m_randomCards[index]]->Draw();
    }
}

/// <summary>
/// �L�[�{�[�h�̍X�V
/// </summary>
/// <returns></returns>
bool LevelCard::KeyUpdate()
{
    // �L�[���͂̎擾
    auto input = MyLib::InputSystem::GetInstance()->GetKeyTracer();

    // �N���b�N�ł��Ȃ��J�[�h�̐����J�E���g
    int unClickableCardCount = std::count_if
    (
        m_cards.begin(), m_cards.end(),
        [&](const std::unique_ptr<LevelCardEffect>& card)
        {
            return !card->IsClickAble();
        }
    );

    int overID = static_cast<int>(LevelCard::CardType::OverID);

    // �N���b�N����Ă��Ȃ��ꍇ�A���N���b�N�ł��Ȃ��J�[�h�̐����ő�l�Ɠ����ꍇ
    if (!m_isClick && unClickableCardCount == overID)
    {
        // �ҋ@���ԂłȂ���Ώ������s��Ȃ�
        if (!m_finStand) return false;

        // D�L�[�������ꂽ
        if (input->pressed.D) 
        {
            // �I���J�[�h��1�E�ɐi�߂�
            m_selectCard = (m_selectCard + 1) % overID;
            //  �I�o�J�[�h�̐擪������
            std::vector<int> randomCards = { m_randomCards[0],m_randomCards[1] };

            // �����_���Ŕz��ꂽ�J�[�h�̒��ɑ��݂��Ȃ��ꍇ�A���̃C���f�b�N�X��
            while (std::find(randomCards.begin(), randomCards.end(), m_selectCard) == randomCards.end())
            {
                m_selectCard = (m_selectCard + 1) % overID;
            }
            // ���ʉ���炷
            AudioManager::GetInstance()->PlaySoundEffectSE(L"inCard");
        }
        // A�L�[�������ꂽ
        else if (input->pressed.A) 
        {
            // �I���J�[�h��1���ɐi�߂�
            m_selectCard = (m_selectCard - 1 + overID) % overID;

            std::vector<int> randomCards = { m_randomCards[0],m_randomCards[1] };

            // �����_���Ŕz��ꂽ�J�[�h�̒��ɑ��݂��Ȃ��ꍇ�A���̃C���f�b�N�X��
            while (std::find(randomCards.begin(), randomCards.end(), m_selectCard) == randomCards.end())
            {
                m_selectCard = (m_selectCard - 1 + overID) % overID;
            }
            // ���ʉ���炷
            AudioManager::GetInstance()->PlaySoundEffectSE(L"inCard");
        }

        // �I������Ă���J�[�h�����I���\�ɂ���
        for (int index = 0; index < m_cards.size(); ++index)
        {
            if (index == m_selectCard) 
            {
                m_cards[index]->SelectKey();
            }
            else 
            {
                m_cards[index]->SelectNotKey();
            }
        }

        // Space�L�[�������ꂽ
        if (input->pressed.Space)
        {
            // �I������Ă���J�[�h���N���b�N
            m_cards[m_selectCard]->Click();
            // �N���b�N�t���O�𗧂Ă�
            m_isClick = true;
            // �S�ẴJ�[�h���N���b�N��Ԃɂ���
            for (const auto& card : m_cards)
            {
                card->SetClick();
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
        for (int index = 0; index < SELECT_NUMBER; ++index)
        {
            //	�������Ȃ��߂�
            if (m_cards[m_randomCards[index]]->IsReady())    continue;

            //	�X�V����
            m_cards[m_randomCards[index]]->Update();

            //	�}�E�X�����ɓ����Ă��Ȃ��Ȃ�A��
            if (!m_cards[m_randomCards[index]]->InMouseCarsor(GetMousePosition()))    continue;

            //	�ҋ@���ԂȂ�A��
            if (!m_finStand)    continue;

            //	�Z���N�g�\�Ȕԍ�������Ȃ����Ă�����
            if (m_cards[m_randomCards[index]]->IsClickAble())    m_selectCard = m_randomCards[index];

            //	�N���b�N�\���H
            if (m_cards[m_randomCards[index]]->IsClickAble() && mouse->leftButton == mouse->PRESSED ||
                m_cards[m_randomCards[index]]->IsClickAble() && input->pressed.Space)
            {
                //	�J�[�h�N���b�N���̏���
                m_cards[m_randomCards[index]]->Click();
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
            if (!card->IsReady())    continue;

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
            //  �ҋ@���Ԃ�
            m_finStand = false;
            //  �����_����������x����������
            m_finRandom = false;
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

/// <summary>
/// �����_���őI�o�����ԍ���I��
/// </summary>
/// <param name="timer">�^�C�}�[</param>
void LevelCard::CreateRandomNumber(const DX::StepTimer& timer)
{
    if (m_finRandom)    return;

  //  int table[9] = { 0, 0, 0, 1, 1, 1, 2, 2, 2 };

    //	�ő�l�l
    int maxCount = static_cast<__int64>(CardType::OverID);

    //  �V���b�t��
    for (int i = 0; i < m_randomCards.size(); i++)
    {
        int shuffle = rand() % m_randomCards.size();
        std::swap(m_randomCards[i], m_randomCards[shuffle]);
    }
    //  �I�����ꂽ�ԍ��͖ڕW���W��ݒ肷��
    for (int index = 0; index < SELECT_NUMBER; ++index)
    {
        m_cards[m_randomCards[index]]->SetTargetPosition(DirectX::SimpleMath::Vector2(LevelCardEffect::OFFSET_POSITION + LevelCardEffect::OFFSET_POSITION * index, LevelCardEffect::OFFSET_POSITION));
    }
    //  �擪�擾
    m_selectCard = m_randomCards[0];
    //  �����_���͏I��
    m_finRandom = true;
}