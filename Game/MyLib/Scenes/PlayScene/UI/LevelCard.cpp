
#include "pch.h"
#include "LevelCard.h"

#include "../Object/Player.h"
#include "../PlayScene.h"

//	背景画像の中心点
const DirectX::SimpleMath::Vector2 LevelCard::BACKGROUND_ORIGIN_POSITION = { 699.0f,370.0f };
//	待機時間
const float						   LevelCard::WAIT_SECONDS				 = 0.82f;


/// <summary>
///	コンストラクタ
/// </summary>
/// <param name="playScene">プレイシーン</param>
/// <param name="player">プレイヤー</param>
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
/// デストラクタ
/// </summary>
LevelCard::~LevelCard()
{
}

/// <summary>
/// 初期化処理
/// </summary>
void LevelCard::Initialize()
{
	int maxNum = static_cast<int>(CardType::OverID);

	//	カードを3枚作る
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
		//	初期化を行う
		m_cards[index]->Initialize();
	}
	//	背景画像の作成
	m_backGround = std::make_unique<LevelCardBackGround>();
	//	背景画像の初期化
	m_backGround->Initialize();
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="timer">タイマー</param>
/// <returns>使用状態</returns>
bool LevelCard::Update(const DX::StepTimer& timer)
{
	//	プレイヤーのレベル最大値
	int playerMaxLevel = m_player->GetPlayerEXPoint()->MAX_PLAYER_LEVEL;

	//	プレイヤーのレベルの最大値を超えていたら帰れ
	if (m_playerLevel >= playerMaxLevel)	return false;

	//	プレイヤーのレベルが上がったか？
	if (m_player->GetPlayerLevel() == m_playerLevel)	return false;
	
	//	待機中は処理を行わない
	//	経過時間を足す
	if (m_standbyTime <= WAIT_SECONDS) { m_standbyTime += static_cast<float>(timer.GetElapsedSeconds()); }else { m_finStand = true; }

	//	キーの更新
	KeyUpdate();

	//	マウスの更新
	if (MouseUpdate())	return true;

	//	クリックされた
	if (ClickedCard())	return true;

	return false;
}

/// <summary>
/// 描画する
/// </summary>
void LevelCard::Draw()
{
	//	背景画像の描画
	m_backGround->Draw();

	for (const auto& card : m_cards)
	{
		card->Draw();
	}	
}

/// <summary>
/// キーの操作
/// </summary>
bool LevelCard::KeyUpdate()
{
	//	キー入力
	auto input = MyLib::InputSystem::GetInstance()->GetKeyTracer();

	//	条件を満たしたオブジェクトの数を数える
	__int64 redyCount = std::count_if
	(
		m_cards.begin(), m_cards.end(),
		[&](const std::unique_ptr<LevelCardEffect>& card)
		{
			return !card->IsClickAble();
		}
	);

	//	最大値を取得
	int overID = static_cast<int>(LevelCard::CardType::OverID);

	//	クリックされたら処理を行わない
	if (!m_isClick && redyCount == overID)
	{
		//	待機時間なら帰れ
		if (!m_finStand)	return false;

		//	Dキーが押された
		if (input->pressed.D)
		{
			//	右に一個進む
			m_selectCard++;
			//	超えてたら0にする
			m_selectCard %= overID;
			//	最初だけ音を鳴らす
			AudioManager::GetInstance()->PlaySoundEffectSE(L"inCard");
		}
		//	Aキーが押された
		if (input->pressed.A)
		{
			m_selectCard--;

			//	最初だけ音を鳴らす
			AudioManager::GetInstance()->PlaySoundEffectSE(L"inCard");

			if (m_selectCard < 0)
			{
				//	一番右にする
				m_selectCard = overID - 1;
			}
		}

		for (int index = 0; index < m_cards.size(); ++index)
		{
			//	選択されているカードだけ選択可能にする
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
			//	カードクリック時の処理
			m_cards[m_selectCard]->Click();
			//	クリックされた
			m_isClick = true;
			//	全部クリック状態に
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
/// マウスの更新
/// </summary>
/// <returns>使用状態</returns>
bool LevelCard::MouseUpdate()
{
	//	プレイヤーのレベルが上がったか？ && クリックされたら処理を行わない
	if (!m_isClick)
	{
		//	マウス
		auto mouse = MyLib::InputSystem::GetInstance()->GetStateTracker();
		//	キー入力
		auto input = MyLib::InputSystem::GetInstance()->GetKeyTracer();

		//	背景画像の更新
		m_backGround->Update();

		//	カード
		for (int index = 0; index < m_cards.size(); ++index)
		{
			//	準備中ならやめる
			if (m_cards[index]->IsReady())	continue;

			//	更新処理
			m_cards[index]->Update();

			//	マウスが中に入っていないなら帰れ
			if (!m_cards[index]->InMouseCarsor(GetMousePosition()))	continue;

			//	待機時間なら帰れ
			if (!m_finStand)	continue;

			//	セレクト可能な番号があるなら入れていいよ
			if (m_cards[index]->IsClickAble())	m_selectCard = index;

			//	クリック可能か？
			if (m_cards[index]->IsClickAble() && mouse->leftButton == mouse->PRESSED ||
				m_cards[index]->IsClickAble() && input->pressed.Space)
			{
				//	カードクリック時の処理
				m_cards[index]->Click();
				//	クリックされた
				m_isClick = true;
				//	全部クリック状態に
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
/// クリックされた
/// </summary>
/// <returns>使用状態</returns>
bool LevelCard::ClickedCard()
{
	//	クリック押されたら下へフェードアウトする
	if (m_isClick)
	{
		//	背景画像も下へ
		m_backGround->Exit();

		for (const auto& card : m_cards)
		{
			//	準備中じゃないならやめる
			if (!card->IsReady())	continue;

			card->Exit();
		}

		//	条件を満たしたオブジェクトの数を数える
		__int64 redyCount = std::count_if
		(
			m_cards.begin(), m_cards.end(),
			[&](const std::unique_ptr<LevelCardEffect>& card)
			{
				return !card->IsReady();
			}
		);

		//	最大値値
		int maxCount = static_cast<__int64>(CardType::OverID);

		//	最大数と同じなら終わる
		if (redyCount == maxCount)
		{
			m_isClick = false;
			//	レベルが上がった
			m_playerLevel++;
			//	待機時間もリセット
			m_standbyTime = 0.0f;
			m_finStand = false;
		}
	}

	return false;
}

/// <summary>
/// マウス座標を取得する
/// </summary>
/// <returns>マウス座標</returns>
DirectX::SimpleMath::Vector2 LevelCard::GetMousePosition()
{
	//	マウスの状態を取得
	auto state = DirectX::Mouse::Get().GetState();
	//	マウスカーソルの座標
	return DirectX::SimpleMath::Vector2(static_cast<float>(state.x), static_cast<float>(state.y));
}
