
/*!
@file Scene.cpp
@brief シーン実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
	//-----------------------------------------------------------------
	//ゲームマネージャー
	//選択されているステージを把握しておく
	//-----------------------------------------------------------------
	GameManager* GameManager::GM = nullptr;
	GameManager* GameManager::GetInstance() {
		if (GM == nullptr) {
			GM = new GameManager();
		}
		return GM;
	}

	//--------------------------------------------------------------------------------------
	///	ゲームシーン
	//--------------------------------------------------------------------------------------
	
	void Scene::CreateResources() {
		// データディレクトリの取得
		wstring dataDir;
		App::GetApp()->GetDataDirectory(dataDir);
		// テクスチャ
		wstring texturesDir = dataDir + L"Textures\\";
		// アニメーション
		wstring animDir = dataDir + L"Animations\\";
		// オーディオ
		wstring audioDir = dataDir + L"Audios\\";
		// BGM
		wstring bgmDir = audioDir + L"BGM\\";
		// SE
		wstring seDir = audioDir + L"SE\\";

		struct Pairs
		{
			wstring Key;
			wstring FileName;
		};

		// テクスチャ
		Pairs txPairs[] =
		{
			//タイトル
			{L"TITLEL_LOGO_TX", L"Title_Ver2.png"},
			{L"TITLE_BACK", L"Title_Back.png"},
			// ステージのテクスチャ
			{L"TRACE_TX", L"trace.png"},
			{L"FLOOR_TX", L"Floor.png"},
			{L"FLOOR_4x4_TX", L"Floor_4x4.png"},
			{L"WALL_TX", L"BlockWall.tga"},
			{L"REFLECTWALL_TX", L"ReflectWall.tga"},
			{L"REFLECTWALL_BLUE_TX", L"Reflect_Wall_0003.png"},
			{L"BREAKWALL_TX", L"BreakWall.png"},
			// ステージのUI
			{L"HEART_UI_TX", L"HP_Life.png"},
			{L"HP_FRONT_UI_TX", L"HP_UI_ver2.png"},
			{L"HP_BACK_UI_TX", L"HP_UI_Back.png"},
			{L"WALLSTOCK_UI_TX", L"UI_MagicWall.png"},
			{L"WALLSTICK_UI_TX", L"MagicStick_UI.png"},
			{L"WALLSTOCKFRONT_UI_TX", L"MagicShield_UI_ver2.png"},
			{L"WALLSTOCKBACK_UI_TX", L"MagicShield_UI_Back_ver2.png"},
			{L"GAMESELECT_BG_TX", L"Select_BackGround.png"},
			{L"WHITE_TX", L"White.png"},
			//エフェクト
			{L"FIRE_TX", L"fire.png"},
			{L"BLUEFIRE_TX", L"BlueFire.png"},
			{L"BREAK_TX", L"Break.png"},
			{L"REFLECT_TX", L"Reflect0005.png"},
			{L"RED_BULLET_TX",L"fire_Red.png"},
			{L"ORANGE_BULLET_TX",L"fire_Orange.png"},
			{L"YELLOW_BULLET_TX",L"fire_Yellow.png"},
			{L"GREEN_BULLET_TX",L"fire_LightBlue.png"},
			{L"BLUE_BULLET_TX",L"fire_Blue.png"},
			{L"ENEMY_BULLET_TX",L"fire_Black.png"},
			//ボタン
			{L"NEXTSTAGE_BUTTON_TX", L"Tx_NextStageButton.png"},
			{L"STAGESELECT_BUTTON_TX", L"Tx_StageSelectButton.png"},
			{L"RETRY_BUTTON_TX", L"Tx_Retry.png"},
			{L"GAMEBACK_BUTTON_TX", L"Tx_GameBack.png"},
			//ステージ番号
			{L"STAGE_1_TX", L"Select_1.png"},
			{L"STAGE_2_TX", L"Select_2.png"},
			{L"STAGE_2_LOCK_TX", L"LockSelect_2.png"},
			{L"STAGE_3_TX", L"Select_3.png"},
			{L"STAGE_3_LOCK_TX", L"LockSelect_3.png"},
			{L"STAGE_4_TX", L"Select_4.png"},
			{L"STAGE_4_LOCK_TX", L"LockSelect_4.png"},
			{L"STAGE_5_TX", L"Select_5.png"},
			{L"STAGE_5_LOCK_TX", L"LockSelect_5.png"},
			//文字
			{L"GAMECLEAR_TX", L"Tx_GameClear.png"},
			{L"GAMEOVER_TX", L"Tx_GameOver.png"},
			{L"POSE_TX", L"Tx_Paused.png"},
			{L"STAGESELECT_TX", L"Tx_StageSelect_ver2.png"},
			{L"A_START_TX", L"Tx_Start.png"}, // Aボタンでスタート
			{L"START_TX", L"Tx_GameStart.png"} // ゲーム開始
		};
		// アニメーション
		Pairs animPairs[] = 
		{
			//{WstringKey::Anim_Player, L"PL_Stand.bmf"},
			{WstringKey::Anim_Player, L"PL_Stand_Walk.bmf"},
			{WstringKey::Anim_Player_Ver2, L"PL_Animation_ver3.bmf"},
			{WstringKey::Anim_Enemy, L"Enemy_ver2.bmf"},
			{WstringKey::Anim_EnemyBlue, L"Enemy_Blue_ver2.bmf"},
			{WstringKey::Anim_EnemyBlack, L"Enemy_Black_ver2.bmf"},
			{WstringKey::Anim_EnemyYellow, L"Enemy_Yellow_ver2.bmf"},
			{WstringKey::Anim_TreasureBox,L"TreasureBox.bmf"}
		};
		//スタティック
		Pairs staticPairs[] =
		{
			{L"TREASURE_MESH", L"Treasure.bmf"},
			{L"SHELD_MESH", L"Shield.bmf"},
			{L"ENEMY_MESH", L"Enemy.bmf"},
			{L"STOPENEMY_MESH", L"StopEnemy.bmf"},
			{L"CANNON_MESH", L"Cannon.bmf"},
			{L"COLORENEMY_MESH", L"StopEnemy0002.bmf"},
			{L"BULLET_MESH", L"Bullet_Green.bmf"},
			{L"RED_BULLET", L"Bullet_Red.bmf"},
			{L"ORANGE_BULLET",L"Bullet_Orange.bmf"},
			{L"YELLOW_BULLET",L"Bullet_Yellow.bmf"},
			{L"GREEN_BULLET",L"Bullet_LightBlue.bmf"},
			{L"BLUE_BULLET", L"Bullet_Blue.bmf"},
			{L"THORN_BULLET_MESH", L"Bullet_Red_thorn.bmf"},
			{L"PURPLE_BULLET_MESH", L"Bullet_Purple.bmf"},
			{L"BLUE_BULLET_MESH", L"Bullet_Blue.bmf"},
			{L"RED_SHIELD", L"Shield_Red.bmf"},
			{L"ORANGE_SHIELD", L"Shield_Orange.bmf"},
			{L"YELLOW_SHIELD", L"Shield_Yellow.bmf"},
			{L"GREEN_SHIELD", L"Shield_LightBlue.bmf"},
			{L"BLUE_SHIELD", L"Shield_Blue.bmf"},
			{L"ENEMY_BULLET",L"Enemy_Bullet.bmf"},
			{L"ENEMY_BULLET_DANGER",L"Enemy_Bullet_Thorn.bmf"}

		};
		//タンジェント有りスタティック
		Pairs staticTangentPairs[] =
		{
			{L"MAGICWALL_MESH", L"MagicWall.bmf"},
			{L"MAGICWALL_RED_MESH", L"MagicWall_R.bmf"}
		};

		Pairs bgmPairs[] =
		{
			{L"SE_CraeteMagicWall", L"magicwall.wav"}
		};

		Pairs sePairs[] =
		{
			{L"SE_CraeteMagicWall", L"magicwall.wav"},
			{L"SE_Bullet", L"Bullet.wav"},
			{L"SE_Reflection", L"Reflection.wav"},
			{L"SE_EnemyDamage", L"EnemyDamage.wav"},
			{L"SE_SheildUnbreak", L"SheildUnbreak.wav"},
			{L"SE_BreakWall", L"BreakWall.wav"},
			{L"SE_PlayerDamage", L"PlayerDamage.wav"},
			{L"BGM_MAINBGM", L"MainBGM.wav"},
			{L"BGM_GameClear", L"GameClear.wav"},
			{L"BGM_GameOver", L"GameOverBGM.wav"},
			{L"SE_GameTitle", L"GameTitle.wav"},
			{L"SE_GameSelect", L"GameSelect.wav"},
			{WstringKey::SE_BreakStageWall, L"BreakStageWall2.wav"},
			{L"SE_ENTER", L"Enter.wav"},
			{L"SE_CANCEL", L"Cancel.wav"},
			{L"SE_CURSOL", L"Cursol.wav"},
			{L"SE_BULLET_RED",L"power1.wav"},
			{L"SE_BULLET_ORANGE",L"power2.wav"},
			{L"SE_BULLET_YELLOW",L"power3.wav"},
			{L"SE_BULLET_GREEN",L"power4.wav"},
			{L"SE_BULLET_BLUE",L"power5.wav"}
		};

		// テクスチャ
		for (auto pair : txPairs)
		{
			wstring strTexture = texturesDir + pair.FileName;
			App::GetApp()->RegisterTexture(pair.Key, strTexture);
		}

		// アニメーション
		for (auto pair : animPairs)
		{
			auto modelMesh = MeshResource::CreateBoneModelMesh(animDir, pair.FileName);
			App::GetApp()->RegisterResource(pair.Key, modelMesh);
		}
		//スタティック
		for (auto pair : staticPairs)
		{
			auto staticModelMesh = MeshResource::CreateStaticModelMesh(animDir, pair.FileName);
			App::GetApp()->RegisterResource(pair.Key, staticModelMesh);
		}
		//タンジェント有りスタティック
		for (auto pair : staticTangentPairs)
		{
			auto staticModelMesh = MeshResource::CreateStaticModelMeshWithTangent(animDir, pair.FileName);
			App::GetApp()->RegisterResource(pair.Key, staticModelMesh);
		}

		//BGM
		for (auto pair : sePairs)
		{
			wstring strBGM = bgmDir + pair.FileName;
			App::GetApp()->RegisterWav(pair.Key, strBGM);
		}

		//SE
		for (auto pair : sePairs)
		{
			wstring strSE = seDir + pair.FileName;
			App::GetApp()->RegisterWav(pair.Key, strSE);
		}
	}

	void Scene::OnCreate(){
		try {
			// リソースの作成
			CreateResources();

			//クリアする色を設定
			Col4 Col;
			Col.set(0.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f, 255.0f / 255.0f);
			//Col.set(31.0f / 255.0f, 30.0f / 255.0f, 71.0f / 255.0f, 255.0f / 255.0f);
			SetClearColor(Col);
			//自分自身にイベントを送る
			//これにより各ステージやオブジェクトがCreate時にシーンにアクセスできる
			PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), WstringKey::ToGameTitle);
			//PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), WstringKey::ToGameTestStage);
		}
		catch (...) {
			throw;
		}
	}

	Scene::~Scene() {
	}

	void Scene::OnEvent(const shared_ptr<Event>& event) {
		if (event->m_MsgStr == WstringKey::ToGameTitle) {
			//最初のアクティブステージの設定
			ResetActiveStage<GameTitle>();
		}
		else if (event->m_MsgStr == WstringKey::ToGameStageSelect) {
			ResetActiveStage<GameStageSelect>();
		}
		else if (event->m_MsgStr == WstringKey::ToGameStage1) {
			ResetActiveStage<GameStage>();
		}
		else if (event->m_MsgStr == WstringKey::ToGameStage2) {
			ResetActiveStage<GameStage2>();
		}
		else if (event->m_MsgStr == WstringKey::ToGameStage3) {
			ResetActiveStage<GameStage3>();
		}
		else if (event->m_MsgStr == WstringKey::ToGameStage4) {
			ResetActiveStage<GameStage4>();
		}
		else if (event->m_MsgStr == WstringKey::ToGameStage5) {
			ResetActiveStage<GameStage5>();
		}
		else if (event->m_MsgStr == WstringKey::ToGameTestStage) {
			ResetActiveStage<TestStage>();
		}
	}
}
//end basecross
