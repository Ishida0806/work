//
//		File Name ： Pause.cpp
//		Production： 2023/10/1
//		Author　　： 石田 恭一
// 
#include "pch.h"
#include "Pause.h"

#include "Game/MyLib/Scenes/PlayScene/PlayScene.h"

//	移動量
const float						   Pause::VELOCITY		= 190.0f;
//	座標のXの最大値
const float						   Pause::X_MAX			= 1020.0f;
//	状態による増加量
const float						   Pause::X_INCREMENT	= 190.0f;
//	画像の大きさ
const DirectX::SimpleMath::Vector2 Pause::BASE_SCALE	= DirectX::SimpleMath::Vector2(0.7f, 0.7f);
//	選択された時の大きさ
const DirectX::SimpleMath::Vector2 Pause::SELECT_SCALE  = DirectX::SimpleMath::Vector2::One;
/// <summary>
/// コンストラクタ
/// </summary>
Pause::Pause(PlayScene* playScene) 
	:m_playScene(playScene),
	m_audio(nullptr),
	m_button(nullptr),
	m_bar(nullptr),
	m_black(nullptr),
	m_guideKey(nullptr),
	m_guideSE(nullptr),
	m_guideBGM(nullptr),
	m_esc(nullptr),
	m_sprite(nullptr),
	m_stateSound(STATE_SOUND::SE),
	m_isPause(false),
	m_seAlfa(0.0f),
	m_bgmAlfa(0.0f),
	m_titleAlfa(0.0f),
	m_endAlfa(0.0f)

{
	CreateDeviceDependentResources();
}

/// <summary>
/// デストラクタ
/// </summary>
Pause::~Pause()
{
}

/// <summary>
/// 初期化処理
/// </summary>
void Pause::Initialize()
{
	//	位置をSEにする
	m_stateSound = STATE_SOUND::SE;
	//　状態を確認する
	CheckState();
}

/// <summary>
/// 更新処理
/// </summary>
void Pause::Update()
{
	//	状態を設定する
	UpdateKey();
	//	アルファの値を変える
	UpdateAlfa();
}

/// <summary>
/// 描画処理
/// </summary>
void Pause::Render()
{
	//	UIを描画する
	RenderUI();
}

/// <summary>
/// 終了処理
/// </summary>
void Pause::Finalize()
{
}

/// <summary>
/// デバイス依存のリソースの初期化
/// </summary>
void Pause::CreateDeviceDependentResources()
{
	//	オーディオマネージャを取得する
	m_audio = AudioManager::GetInstance();
	//	スプライトバッチを取得する
	m_sprite = MyLib::ScreenResources::GetInstance()->GetSpriteBatch();
	//	バーの画像を取得する
	m_bar = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"Bar");
	//	ボタンの画像を取得する
	m_button = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"Button");
	//	黒の画像取得する
	m_black = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"BlackTexture");
	//	ガイドキーの画像を取得する
	m_guideKey = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"GuideKey");
	//	ガイドSEの画像を取得する
	m_guideSE = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"PauseUITextureSE");
	//	ガイドBGMの画像を取得する
	m_guideBGM = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"PauseUITextureBGM");
	//	ESCのUIを所得する
	m_esc = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"EscapeUI");
	//	エンド
	m_end = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"PauseUITextureEndGame");
	//	タイトル
	m_title = MyLib::ResourcesData::GetInstance()->GatShaderResourceView(L"PauseUITextureTitle");
	//	画面の高さ・横幅
	int width, height;
	//	スクリーンサイズを取得する
	MyLib::ScreenResources::GetInstance()->GetScreenSize(width, height);
	//	座標の場所を初期化
	m_barTopPos	   = DirectX::SimpleMath::Vector2(width / 2.0f, height / 3.0f);
	m_buttonTopPos = DirectX::SimpleMath::Vector2(X_MAX, height / 3.0f);
	m_barUnderPos = DirectX::SimpleMath::Vector2(width / 2.0f, height / 2.0f);
	m_buttonUnderPos = DirectX::SimpleMath::Vector2(X_MAX, height / 2.0f);
	m_blackPos	   = DirectX::SimpleMath::Vector2(width / 2.0f, height / 2.0f);
	//	ガイドキーの座標
	m_guidePos  = DirectX::SimpleMath::Vector2(950.0f, 500.0f);
	m_bgmPos	= DirectX::SimpleMath::Vector2(200.0f, m_barUnderPos.y + 30.0f);
	m_sePos		= DirectX::SimpleMath::Vector2(200.0f, m_buttonTopPos.y + 30.0f);
	m_titlePos	= DirectX::SimpleMath::Vector2(640.0f, 520.0f);
	m_endGamePos= DirectX::SimpleMath::Vector2(640.0f, 580.0f);
	//	透明度を初期化する
	m_seAlfa  = 1.0f;
	m_bgmAlfa = 1.0f;
	m_endAlfa = 1.0f;
	m_titleAlfa = 1.0f;
	//	画像の大きさ
	m_seScale	   = BASE_SCALE;
	m_bgmScale	   = BASE_SCALE;
	m_titleScale   = BASE_SCALE;
	m_endGameScale = BASE_SCALE;
}

/// <summary>
/// アルファの値を弄る
/// </summary>
void Pause::UpdateAlfa()
{
	//	ステートの状態によってアルファ値を変える
	switch (m_stateSound)
	{
	case Pause::STATE_SOUND::SE:
		//	色を変える
		m_seAlfa    = 1.0f;
		m_bgmAlfa   = 0.2f;
		m_endAlfa   = 0.2f;
		m_titleAlfa = 0.2f;
		//	大きさを変える
		m_seScale = SELECT_SCALE;
		m_bgmScale = BASE_SCALE;
		m_titleScale = BASE_SCALE;
		m_endGameScale = BASE_SCALE;
		break;
	case Pause::STATE_SOUND::BGM:
		//	色を変える
		m_seAlfa    = 0.2f;
		m_bgmAlfa   = 1.0f;
		m_endAlfa   = 0.2f;
		m_titleAlfa = 0.2f;
		//	大きさを変える
		m_seScale = BASE_SCALE;
		m_bgmScale = SELECT_SCALE;
		m_titleScale = BASE_SCALE;
		m_endGameScale = BASE_SCALE;
		break;

	case Pause::STATE_SOUND::TITLE:
		//	色を変える
		m_seAlfa	= 0.2f;
		m_bgmAlfa	= 0.2f;
		m_endAlfa	= 0.2f;
		m_titleAlfa = 1.0f;
		//	大きさを変える
		m_seScale = BASE_SCALE;
		m_bgmScale = BASE_SCALE;
		m_titleScale = SELECT_SCALE;
		m_endGameScale = BASE_SCALE;

		break;

	case Pause::STATE_SOUND::END:
		//	色を変える
		m_seAlfa    = 0.2f;
		m_bgmAlfa   = 0.2f;
		m_endAlfa   = 1.0f;
		m_titleAlfa = 0.2f;
		//	大きさを変える
		m_seScale	   = BASE_SCALE;
		m_bgmScale	   = BASE_SCALE;
		m_titleScale   = BASE_SCALE;
		m_endGameScale = SELECT_SCALE;
		break;


	default:
		break;
	}
}


/// <summary>
/// ポーズを設定する
/// </summary>
/// <param name="flag"></param>
void Pause::SetPause(bool flag)
{
	m_isPause = flag;
}

/// <summary>
/// UIを描画する
/// </summary>
void Pause::RenderUI()
{
	//	黒の画像を描画する
	m_sprite->Draw(
		m_black,																//	画像
		m_blackPos,																//	画像の座標
		nullptr,																//	画像の範囲内
		DirectX::SimpleMath::Color(0.0f, 0.0f, 0.0f, 0.5f),						//	色
		0.0f,																	//	角度
		DirectX::SimpleMath::Vector2(640.0f, 360.0f),							//	画像の真ん中を設定する
		DirectX::SimpleMath::Vector2(0.8f, 0.8f)								//	画像の大きさ
	);

	//	ESCの描画する
	m_sprite->Draw(
		m_esc,													//	画像
		DirectX::SimpleMath::Vector2(70.0f, 55.0f)			//	画像の座標
	);

	//	バーの上部描画する
	m_sprite->Draw(
		m_bar,											//	画像
		m_barTopPos,										//	画像の座標
		nullptr,										//	画像の範囲内
		DirectX::Colors::White,							//	色
		0.0f,											//	角度
		DirectX::SimpleMath::Vector2(740.0f, 29.0f),	//	画像の真ん中を設定する
		DirectX::SimpleMath::Vector2(0.5f, 0.5f)		//	画像の大きさ
	);
	//	ボタンの上部描画する
	m_sprite->Draw(
		m_button,											//	画像
		m_buttonTopPos,										//	画像の座標
		nullptr,											//	画像の範囲内
		DirectX::Colors::White,								//	色
		0.0f,												//	角度
		DirectX::SimpleMath::Vector2(19.5f, 51.5f)			//	画像の真ん中を設定する
	);

	//	バーの下部描画する
	m_sprite->Draw(
		m_bar,											//	画像
		m_barUnderPos,										//	画像の座標
		nullptr,										//	画像の範囲内
		DirectX::Colors::White,							//	色
		0.0f,											//	角度
		DirectX::SimpleMath::Vector2(740.0f, 29.0f),	//	画像の真ん中を設定する
		DirectX::SimpleMath::Vector2(0.5f, 0.5f)		//	画像の大きさ
	);
	//	ボタンの下部描画する
	m_sprite->Draw(
		m_button,										//	画像
		m_buttonUnderPos,									//	画像の座標
		nullptr,											//	画像の範囲内
		DirectX::Colors::White,							//	色
		0.0f,											//	角度
		DirectX::SimpleMath::Vector2(19.5f, 51.5f)			//	画像の真ん中を設定する
	);

	//	案内キーを描画する
	m_sprite->Draw(
		m_guideKey,											//	画像
		m_guidePos,										//	画像の座標
		nullptr,											//	画像の範囲内
		DirectX::Colors::White,								//	色
		0.0f,												//	角度
		DirectX::SimpleMath::Vector2(19.5f, 51.5f)			//	画像の真ん中を設定する
	);
	//	SEの描画する
	m_sprite->Draw(
		m_guideSE,												//	画像
		m_sePos,												//	画像の座標
		nullptr,												//	画像の範囲内
		DirectX::SimpleMath::Color(m_seAlfa, m_seAlfa, m_seAlfa, m_seAlfa),	//	色
		0.0f,													//	角度
		DirectX::SimpleMath::Vector2(19.5f, 51.5f),				//	画像の真ん中を設定する
		m_seScale
	);
	//	BGMの描画する
	m_sprite->Draw(
		m_guideBGM,																//	画像
		m_bgmPos,																//	画像の座標
		nullptr,																//	画像の範囲内
		DirectX::SimpleMath::Color(m_bgmAlfa, m_bgmAlfa, m_bgmAlfa, m_bgmAlfa), //	色
		0.0f,																	//	角度
		DirectX::SimpleMath::Vector2(19.5f, 51.5f),								//	画像の真ん中を設定する
		m_bgmScale
	);
	//	タイトルの描画する
	m_sprite->Draw(
		m_title,																		//	画像
		m_titlePos,																		//	画像の座標
		nullptr,																		//	画像の範囲内
		DirectX::SimpleMath::Color(m_titleAlfa, m_titleAlfa, m_titleAlfa, m_titleAlfa), //	色
		0.0f,																			//	角度
		DirectX::SimpleMath::Vector2(68.0f, 45.0f),										//	画像の真ん中を設定する
		m_titleScale
	);

	//	ENDの描画する
	m_sprite->Draw(
		m_end,																		//	画像
		m_endGamePos,								//	画像の座標
		nullptr,																	//	画像の範囲内
		DirectX::SimpleMath::Color(m_endAlfa, m_endAlfa, m_endAlfa, m_endAlfa),		//	色
		0.0f,																		//	角度
		DirectX::SimpleMath::Vector2(97.0f, 45.0f),									//	画像の真ん中を設定する
		m_endGameScale
	);
}

/// <summary>
/// 現在の状態にそぐった座標にする
/// </summary>
void Pause::CheckState()
{
	//	SEの状態によりステート変える
	switch (m_audio->GetSEVolumeState())
	{
	case AudioManager::VOLUME_STATE::MAX:
		m_buttonTopPos.x = X_MAX;
		break;
	case AudioManager::VOLUME_STATE::MAX_MIDDLE:
		m_buttonTopPos.x = X_MAX - X_INCREMENT;
		break;
	case AudioManager::VOLUME_STATE::MIDDLE:
		m_buttonTopPos.x = X_MAX - X_INCREMENT * 2.0f;
		break;
	case AudioManager::VOLUME_STATE::MINI_MIDDLE:
		m_buttonTopPos.x = X_MAX - X_INCREMENT * 3.0f;
		break;
	case AudioManager::VOLUME_STATE::MINI:
		m_buttonTopPos.x = X_MAX - X_INCREMENT * 4.0f;
		break;
	default:
		break;
	}
	//	BGMの状態によりステート変える
	switch (m_audio->GetBGMVolumeState())
	{
	case AudioManager::VOLUME_STATE::MAX:
		m_buttonUnderPos.x = X_MAX;
		break;
	case AudioManager::VOLUME_STATE::MAX_MIDDLE:
		m_buttonUnderPos.x = X_MAX - X_INCREMENT;
		break;
	case AudioManager::VOLUME_STATE::MIDDLE:
		m_buttonUnderPos.x = X_MAX - X_INCREMENT * 2.0f;
		break;
	case AudioManager::VOLUME_STATE::MINI_MIDDLE:
		m_buttonUnderPos.x = X_MAX - X_INCREMENT * 3.0f;
		break;
	case AudioManager::VOLUME_STATE::MINI:
		m_buttonUnderPos.x = X_MAX - X_INCREMENT * 4.0f;
		break;
	default:
		break;
	}
}

/// <summary>
/// キーの状態を設定する
/// </summary>
void Pause::UpdateKey()
{
	//	キーボードの入力を取得する
	auto input = MyLib::InputSystem::GetInstance()->GetKeyTracer();
	//	SEを取得する
	int se = static_cast<int>(m_audio->GetSEVolumeState());
	//	BGMを取得する
	int bgm = static_cast<int>(m_audio->GetBGMVolumeState());

	//	Wを押した場合
	if (input->pressed.W)
	{
		if (m_stateSound == STATE_SOUND::SE)
		{
			m_stateSound = STATE_SOUND::END;
		}
		else if (m_stateSound == STATE_SOUND::BGM)
		{
			m_stateSound = STATE_SOUND::SE;
		}
		else if (m_stateSound == STATE_SOUND::TITLE)
		{
			m_stateSound = STATE_SOUND::BGM;
		}
		else if(m_stateSound == STATE_SOUND::END)
		{
			m_stateSound = STATE_SOUND::TITLE;
		}

		//	SEを再生する
		m_audio->PlaySoundEffectSE(L"PlaySE02_MoveTitle");
	}
	//	Sを押した場合
	if (input->pressed.S)
	{
		if (m_stateSound == STATE_SOUND::SE)
		{
			m_stateSound = STATE_SOUND::BGM;
		}
		else if (m_stateSound == STATE_SOUND::BGM)
		{
			m_stateSound = STATE_SOUND::TITLE;
		}
		else if (m_stateSound == STATE_SOUND::TITLE)
		{
			m_stateSound = STATE_SOUND::END;
		}
		else if (m_stateSound == STATE_SOUND::END)
		{
			m_stateSound = STATE_SOUND::SE;
		}
		//	SEを再生する
		m_audio->PlaySoundEffectSE(L"PlaySE02_MoveTitle");
	}

	if (m_stateSound == STATE_SOUND::SE)
	{
		if (input->pressed.A && m_audio->GetSEVolumeState() != AudioManager::VOLUME_STATE::MINI)
		{
			m_buttonTopPos.x -= VELOCITY;
			se++;
			m_audio->SetVolumeSE(static_cast<AudioManager::VOLUME_STATE>(se));
			//	SEを再生する
			m_audio->PlaySoundEffectSE(L"PlaySE02_MoveTitle");
		}
		if (input->pressed.D && m_audio->GetSEVolumeState() != AudioManager::VOLUME_STATE::MAX)
		{
			m_buttonTopPos.x += VELOCITY;
			se--;
			m_audio->SetVolumeSE(static_cast<AudioManager::VOLUME_STATE>(se));
			//	SEを再生する
			m_audio->PlaySoundEffectSE(L"PlaySE02_MoveTitle");
		}
	}
	else if (m_stateSound == STATE_SOUND::BGM)
	{
		if (input->pressed.A && m_audio->GetBGMVolumeState() != AudioManager::VOLUME_STATE::MINI)
		{
			m_buttonUnderPos.x -= VELOCITY;
			bgm++;
			//	SEを再生する
			m_audio->PlaySoundEffectSE(L"PlaySE02_MoveTitle");
		}
		if (input->pressed.D && m_audio->GetBGMVolumeState() != AudioManager::VOLUME_STATE::MAX)
		{
			m_buttonUnderPos.x += VELOCITY;
			bgm--;
			//	SEを再生する
			m_audio->PlaySoundEffectSE(L"PlaySE02_MoveTitle");
		}
	}
	//	Escapeキーが押されたらポーズを終了する
	if (input->pressed.Escape)
	{
		//	SEを再生する
		m_audio->PlaySoundEffectSE(L"Close_SE01");
		//	ポーズをオフにする
		m_isPause = false;
	}
	//	スペースを押された　&&　タイトルシーンだったら
	if (input->pressed.Space && m_stateSound == STATE_SOUND::TITLE)
	{
		//	オーディオマネージャの音を再生
		AudioManager::GetInstance()->PlaySoundEffectSE(L"PlaySE01_Accept");
		m_playScene->ChangeSceneTitle();
		return;
	}
	///	ステートがエンド状態のみゲームを終了する
	if (input->pressed.Space && m_stateSound == STATE_SOUND::END)
	{
		PostQuitMessage(0);
	}
	//	キャストした状態でBGMを設定する
	m_audio->SetVolumeBGM(static_cast<AudioManager::VOLUME_STATE>(bgm));	
}