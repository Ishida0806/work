
#include "pch.h"
#include "Number.h"
#include "PlayInfo.h"

//  �X�R�A�̑�����
const float Number::INCREMENT_SCORE_SPEED = 0.06f;
//	�������Ƃ̋���
const float Number::DISTANCE_NUMBER       = 25.0f;
//	�ڕW�l
const int   Number::TARGET_INCREMENT_SCORE= 125;
//	�ő包��
const int	Number::MAX_DIGIT             = 4;
//	�����̐^��
const DirectX::SimpleMath::Vector2 Number::NUMBER_TEXTURE_ORIGIN = DirectX::SimpleMath::Vector2(75.0, 41.0);

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="texture">�摜</param>
/// <param name="position">���W</param>
Number::Number(ID3D11ShaderResourceView* texture, const DirectX::SimpleMath::Vector2& position)
	:m_numTexture(texture),
    m_numPosition(position),
	m_spriteBatch(nullptr),
	m_scoreTexture(nullptr),
	m_score(0)
{
	// �f�o�C�X�ˑ��̃��\�[�X
	CreateDeviceDependentResources();
}


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="texture">�摜</param>
/// <param name="position">�\�����W</param>
/// <param name="score">�X�R�A</param>
Number::Number(ID3D11ShaderResourceView* texture, const DirectX::SimpleMath::Vector2& position, const int& score)
    :m_numTexture(texture),
    m_numPosition(position),
    m_score(score),
    m_spriteBatch(nullptr),
    m_scoreTexture(nullptr)
{
    // �f�o�C�X�ˑ��̃��\�[�X
    CreateDeviceDependentResources();
}

/// <summary>
/// �I������
/// </summary>
Number::~Number()
{
}

/// <summary>
/// ����������
/// </summary>
void Number::Initialize()
{

}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="score">�X�R�A</param>
void Number::Update(int score)
{
    if (m_score == score)    return;

    m_score = Utility::Clamp(m_score, 0, PlayInfo::MAX_SCORE);

    //  �ő�l��������A��
    if (m_score >= PlayInfo::MAX_SCORE)  return;

    int targetscore = score - m_score;
    
    if (TARGET_INCREMENT_SCORE < targetscore)
    {
        m_score = static_cast<int>(Utility::Lerp(static_cast<float>(m_score), static_cast<float>(score), INCREMENT_SCORE_SPEED));
    }
    else
    {
        m_score++;
    }
}

/// <summary>
/// �`�悷��
/// </summary>
void Number::Draw()
{
    //  String�^�ɕϊ�����
    std::string s_score = GetString(m_score);

    //  ������}��
    int digitCount = static_cast<int>(s_score.size());

    //  �����ɕ\�����s�������̂ŃX�R�A���t������
    std::reverse(s_score.begin(), s_score.end());

    //  int�^�ɂ���
    int r_score = std::stoi(s_score);

    //  SCORE:�̕\���̕`����s��
    m_spriteBatch->Draw
    (
        m_scoreTexture,
        m_scorePosition
    );

	//	�X�R�A�̌���������
	for (int i = 0; i < digitCount; i++)
	{
        // �e���̐������擾
        int digit = GetDigitAt(r_score, i);

        // �Ή�����RECT���擾
        RECT rect = JudDigit(digit);

        //  �I�t�Z�b�g
        DirectX::SimpleMath::Vector2 offset_pos = DirectX::SimpleMath::Vector2(DISTANCE_NUMBER * i, 0.0f);

		//	�����̕`����s��
        m_spriteBatch->Draw
        (
            m_numTexture,
            m_numPosition + offset_pos,
			&rect
		);
	}
}


/// <summary>
/// �����̂ݕ`����s��
/// </summary>
void Number::DrawNumber(float size, float interval)
{
    //  String�^�ɕϊ�����
    std::string s_score = GetString(m_score);
    //  ������}��
    int digitCount = static_cast<int>(s_score.size());
    //  X�̌덷�͈�
    float calValueX = 80.0f * interval;
    //  Y�̌덷�͈�
    float calValueY = 15.0f * interval;
    //  ��
    int num = MAX_DIGIT - digitCount;

    //  4������Ȃ�������0������
    if (digitCount < MAX_DIGIT)
    {
        for (int i = 0; i < num; i++)
        {
            s_score.insert(0, "0");
        }
    }

    //  �C���^�[�o��
    int i = 0;

    for (const auto& c : s_score)
    {
        //  int�^�ɂ���
        int value = c - '0';

        if (value == 0 && num != 0)
        {
            i++;
            num--;
            continue;
        }

        // �Ή�����RECT���擾
        RECT rect = JudDigit(value);

        //  �I�t�Z�b�g
        DirectX::SimpleMath::Vector2 offset_pos = DirectX::SimpleMath::Vector2(calValueX * i, calValueY * i);

        //	�����̕`����s��
        m_spriteBatch->Draw
        (
            m_numTexture,
            m_numPosition + offset_pos,
            &rect,
            DirectX::Colors::White,
            DirectX::XMConvertToRadians(25.0f),
            NUMBER_TEXTURE_ORIGIN,
            DirectX::SimpleMath::Vector2(size, size)
        );   

        i++;
    }
}

/// <summary>
/// ������`�悷��
/// </summary>
void Number::DrawWaveNumber()
{
    //  String�^�ɕϊ�����
    std::string s_score = GetString(m_score);

    for (const auto& c : s_score)
    {
        //  int�^�ɂ���
        int value = c - '0';

        // �Ή�����RECT���擾
        RECT rect = JudDigit(value);

        //	�����̕`����s��
        m_spriteBatch->Draw
        (
            m_numTexture,
            m_numPosition,
            &rect,
            DirectX::Colors::White,
            DirectX::XMConvertToRadians(25.0f),
            NUMBER_TEXTURE_ORIGIN
        );
    }
}

/// <summary>
/// �`����s���E�T�C�Y��ύX����
/// </summary>
/// <param name="interval">�摜�̊Ԋu</param>
void Number::Draw(float interval)
{
    //  String�^�ɕϊ�����
    std::string s_score = GetString(m_score);

    //  ������}��
    int digitCount = static_cast<int>(s_score.size());

    //  �����ɕ\�����s�������̂ŃX�R�A���t������
    std::reverse(s_score.begin(), s_score.end());

    //  int�^�ɂ���
    int r_score = std::stoi(s_score);

    //  X�̌덷�͈�
    float calValueX = 60.0f * interval;

    //  SCORE:�̕\���̕`����s��
    m_spriteBatch->Draw
    (
        m_scoreTexture,
        m_scorePosition - DirectX::SimpleMath::Vector2(calValueX, 0.0f),
        nullptr,
        DirectX::Colors::White,
        0.0f,
        DirectX::SimpleMath::Vector2(99.0f, 50.5f)         //  �摜�̒����l
    );

    //	�X�R�A�̌���������
    for (int i = 0; i < digitCount; i++)
    {
        // �e���̐������擾
        int digit = GetDigitAt(r_score, i);

        // �Ή�����RECT���擾
        RECT rect = JudDigit(digit);

        //  �I�t�Z�b�g
        DirectX::SimpleMath::Vector2 offset_pos = DirectX::SimpleMath::Vector2((DISTANCE_NUMBER * interval) * i, 0.0f);

        //	�����̕`����s��
        m_spriteBatch->Draw
        (
            m_numTexture,
            m_numPosition + offset_pos,
            &rect,
            DirectX::Colors::White,
            0.0f,
            DirectX::SimpleMath::Vector2(75.0f, 41.0f),     //  �摜�̒����l
            DirectX::SimpleMath::Vector2(interval, interval)        //  �傫��
        );
    }
}

/// <summary>
/// �f�o�C�X�ˑ��̃��\�[�X
/// </summary>
void Number::CreateDeviceDependentResources()
{
	//	�X�v���C�g�o�b�`
	m_spriteBatch = MyLib::ScreenResources::GetInstance()->GetSpriteBatch();
    //  �X�R�A�̎ʐ^
    m_scoreTexture = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"score");
    //  �X�R�A���W
    m_scorePosition = DirectX::SimpleMath::Vector2(m_numPosition.x - 165.0f, m_numPosition.y - 20.0f);
}

/// <summary>
/// �\������摜�͈͂����߂�
/// </summary>
/// <param name="score">�X�R�A�u�ꌅ�v</param>
/// <returns>�摜�͈͓̔�</returns>
RECT Number::JudDigit(int score)
{
    RECT rect{};

    OrdinalNumber odlNum = static_cast<OrdinalNumber>(score);

    switch (odlNum)
    {
    case Number::OrdinalNumber::ZEROTH:
        rect.top = 0;
        rect.left = 0;
        rect.bottom = 45;
        rect.right = 27;
        break;
    case Number::OrdinalNumber::FIRST:
        rect.top = 0;
        rect.left = 25;
        rect.bottom = 45;
        rect.right = 50;
        break;
    case Number::OrdinalNumber::SECOND:
        rect.top = 0;
        rect.left = 60;
        rect.bottom = 45;
        rect.right = 85;
        break;
    case Number::OrdinalNumber::THIRD:
        rect.top = 0;
        rect.left = 92;
        rect.bottom = 45;
        rect.right = 114;
        break;
    case Number::OrdinalNumber::FOURTH:
        rect.top = 0;
        rect.left = 122;
        rect.bottom = 45;
        rect.right = 150;
        break;
    case Number::OrdinalNumber::FIFTH:
        rect.top = 45;
        rect.left = 0;
        rect.bottom = 90;
        rect.right = 25;
        break;
    case Number::OrdinalNumber::SIXTH:
        rect.top = 45;
        rect.left = 30;
        rect.bottom = 90;
        rect.right = 50;
        break;
    case Number::OrdinalNumber::SEVENTH:
        rect.top = 45;
        rect.left = 60;
        rect.bottom = 90;
        rect.right = 90;
        break;
    case Number::OrdinalNumber::EIGHTH:
        rect.top = 45;
        rect.left = 90;
        rect.bottom = 90;
        rect.right = 120;
        break;
    case Number::OrdinalNumber::NINTH:
        rect.top = 45;
        rect.left = 120;
        rect.bottom = 90;
        rect.right = 150;
        break;

    default:     break;
    }

    return rect;
}

/// <summary>
/// �e���̐������擾
/// </summary>
/// <param name="number">����</param>
/// <param name="digitPosition">�����ڂ�</param>
/// <returns>���̌������ڂ�</returns>
int Number::GetDigitAt(int number, int digitPosition)
{
    // �w�肳�ꂽ���̐������擾
    int divider = static_cast<int>(std::pow(10, digitPosition));
    int digit = (number / divider) % 10;

    return digit;
}

/// <summary>
/// �X�g�����O�^��
/// </summary>
/// <param name="value">�X�R�A�̒l</param>
/// <returns>string</returns>
std::string Number::GetString(int value)
{
    return  std::to_string(value);
}

/// <summary>
/// �ԍ��̍��W��ݒ肷��
/// </summary>
/// <param name="pos">���W</param>
inline void Number::SetNumberPos(const DirectX::SimpleMath::Vector2& pos)
{
    m_numPosition = pos;
}

/// <summary>
/// �X�R�A�̍��W��ݒ肷��
/// </summary>
/// <param name="pos">���W</param>
inline void Number::SetScorePos(const DirectX::SimpleMath::Vector2& pos)
{
    m_scorePosition = pos;
}

/// <summary>
/// �X�R�A��ݒ肷��
/// </summary>
/// <param name="score">�X�R�A</param>
void Number::SetScore(const int& score)
{
    m_score = score;
}