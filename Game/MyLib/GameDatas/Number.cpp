
#include "pch.h"
#include "Number.h"
#include "PlayInfo.h"

//  スコアの増加量
const float Number::INCREMENT_SCORE_SPEED = 0.06f;
//	数字ごとの距離
const float Number::DISTANCE_NUMBER       = 25.0f;
//	目標値
const int   Number::TARGET_INCREMENT_SCORE= 125;
//	最大桁数
const int	Number::MAX_DIGIT             = 4;
//	数字の真ん中
const DirectX::SimpleMath::Vector2 Number::NUMBER_TEXTURE_ORIGIN = DirectX::SimpleMath::Vector2(75.0, 41.0);

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="texture">画像</param>
/// <param name="position">座標</param>
Number::Number(ID3D11ShaderResourceView* texture, const DirectX::SimpleMath::Vector2& position)
	:m_numTexture(texture),
    m_numPosition(position),
	m_spriteBatch(nullptr),
	m_scoreTexture(nullptr),
	m_score(0)
{
	// デバイス依存のリソース
	CreateDeviceDependentResources();
}


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="texture">画像</param>
/// <param name="position">表示座標</param>
/// <param name="score">スコア</param>
Number::Number(ID3D11ShaderResourceView* texture, const DirectX::SimpleMath::Vector2& position, const int& score)
    :m_numTexture(texture),
    m_numPosition(position),
    m_score(score),
    m_spriteBatch(nullptr),
    m_scoreTexture(nullptr)
{
    // デバイス依存のリソース
    CreateDeviceDependentResources();
}

/// <summary>
/// 終了処理
/// </summary>
Number::~Number()
{
}

/// <summary>
/// 初期化処理
/// </summary>
void Number::Initialize()
{

}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="score">スコア</param>
void Number::Update(int score)
{
    if (m_score == score)    return;

    m_score = Utility::Clamp(m_score, 0, PlayInfo::MAX_SCORE);

    //  最大値だったら帰れ
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
/// 描画する
/// </summary>
void Number::Draw()
{
    //  String型に変換する
    std::string s_score = GetString(m_score);

    //  長さを図る
    int digitCount = static_cast<int>(s_score.size());

    //  左順に表示を行いたいのでスコアを逆向きに
    std::reverse(s_score.begin(), s_score.end());

    //  int型にする
    int r_score = std::stoi(s_score);

    //  SCORE:の表示の描画を行う
    m_spriteBatch->Draw
    (
        m_scoreTexture,
        m_scorePosition
    );

	//	スコアの桁数分周す
	for (int i = 0; i < digitCount; i++)
	{
        // 各桁の数字を取得
        int digit = GetDigitAt(r_score, i);

        // 対応するRECTを取得
        RECT rect = JudDigit(digit);

        //  オフセット
        DirectX::SimpleMath::Vector2 offset_pos = DirectX::SimpleMath::Vector2(DISTANCE_NUMBER * i, 0.0f);

		//	数字の描画を行う
        m_spriteBatch->Draw
        (
            m_numTexture,
            m_numPosition + offset_pos,
			&rect
		);
	}
}


/// <summary>
/// 数字のみ描画を行う
/// </summary>
void Number::DrawNumber(float size, float interval)
{
    //  String型に変換する
    std::string s_score = GetString(m_score);
    //  長さを図る
    int digitCount = static_cast<int>(s_score.size());
    //  Xの誤差範囲
    float calValueX = 80.0f * interval;
    //  Yの誤差範囲
    float calValueY = 15.0f * interval;
    //  数
    int num = MAX_DIGIT - digitCount;

    //  4桁じゃなかったら0を入れる
    if (digitCount < MAX_DIGIT)
    {
        for (int i = 0; i < num; i++)
        {
            s_score.insert(0, "0");
        }
    }

    //  インターバル
    int i = 0;

    for (const auto& c : s_score)
    {
        //  int型にする
        int value = c - '0';

        if (value == 0 && num != 0)
        {
            i++;
            num--;
            continue;
        }

        // 対応するRECTを取得
        RECT rect = JudDigit(value);

        //  オフセット
        DirectX::SimpleMath::Vector2 offset_pos = DirectX::SimpleMath::Vector2(calValueX * i, calValueY * i);

        //	数字の描画を行う
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
/// 数字を描画する
/// </summary>
void Number::DrawWaveNumber()
{
    //  String型に変換する
    std::string s_score = GetString(m_score);

    for (const auto& c : s_score)
    {
        //  int型にする
        int value = c - '0';

        // 対応するRECTを取得
        RECT rect = JudDigit(value);

        //	数字の描画を行う
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
/// 描画を行う・サイズを変更する
/// </summary>
/// <param name="interval">画像の間隔</param>
void Number::Draw(float interval)
{
    //  String型に変換する
    std::string s_score = GetString(m_score);

    //  長さを図る
    int digitCount = static_cast<int>(s_score.size());

    //  左順に表示を行いたいのでスコアを逆向きに
    std::reverse(s_score.begin(), s_score.end());

    //  int型にする
    int r_score = std::stoi(s_score);

    //  Xの誤差範囲
    float calValueX = 60.0f * interval;

    //  SCORE:の表示の描画を行う
    m_spriteBatch->Draw
    (
        m_scoreTexture,
        m_scorePosition - DirectX::SimpleMath::Vector2(calValueX, 0.0f),
        nullptr,
        DirectX::Colors::White,
        0.0f,
        DirectX::SimpleMath::Vector2(99.0f, 50.5f)         //  画像の中央値
    );

    //	スコアの桁数分周す
    for (int i = 0; i < digitCount; i++)
    {
        // 各桁の数字を取得
        int digit = GetDigitAt(r_score, i);

        // 対応するRECTを取得
        RECT rect = JudDigit(digit);

        //  オフセット
        DirectX::SimpleMath::Vector2 offset_pos = DirectX::SimpleMath::Vector2((DISTANCE_NUMBER * interval) * i, 0.0f);

        //	数字の描画を行う
        m_spriteBatch->Draw
        (
            m_numTexture,
            m_numPosition + offset_pos,
            &rect,
            DirectX::Colors::White,
            0.0f,
            DirectX::SimpleMath::Vector2(75.0f, 41.0f),     //  画像の中央値
            DirectX::SimpleMath::Vector2(interval, interval)        //  大きさ
        );
    }
}

/// <summary>
/// デバイス依存のリソース
/// </summary>
void Number::CreateDeviceDependentResources()
{
	//	スプライトバッチ
	m_spriteBatch = MyLib::ScreenResources::GetInstance()->GetSpriteBatch();
    //  スコアの写真
    m_scoreTexture = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"score");
    //  スコア座標
    m_scorePosition = DirectX::SimpleMath::Vector2(m_numPosition.x - 165.0f, m_numPosition.y - 20.0f);
}

/// <summary>
/// 表示する画像範囲を決める
/// </summary>
/// <param name="score">スコア「一桁」</param>
/// <returns>画像の範囲内</returns>
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
/// 各桁の数字を取得
/// </summary>
/// <param name="number">数字</param>
/// <param name="digitPosition">桁何個目か</param>
/// <returns>その桁が何個目か</returns>
int Number::GetDigitAt(int number, int digitPosition)
{
    // 指定された桁の数字を取得
    int divider = static_cast<int>(std::pow(10, digitPosition));
    int digit = (number / divider) % 10;

    return digit;
}

/// <summary>
/// ストリング型に
/// </summary>
/// <param name="value">スコアの値</param>
/// <returns>string</returns>
std::string Number::GetString(int value)
{
    return  std::to_string(value);
}

/// <summary>
/// 番号の座標を設定する
/// </summary>
/// <param name="pos">座標</param>
inline void Number::SetNumberPos(const DirectX::SimpleMath::Vector2& pos)
{
    m_numPosition = pos;
}

/// <summary>
/// スコアの座標を設定する
/// </summary>
/// <param name="pos">座標</param>
inline void Number::SetScorePos(const DirectX::SimpleMath::Vector2& pos)
{
    m_scorePosition = pos;
}

/// <summary>
/// スコアを設定する
/// </summary>
/// <param name="score">スコア</param>
void Number::SetScore(const int& score)
{
    m_score = score;
}