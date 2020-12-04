
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
			{L"TRACE_TX", L"trace.png"},
			{L"FLOOR_TX", L"Floor.png"},
			{L"MAGICWALL_TX", L"MagicWall.jpg"},
			{L"WALL_TX", L"BlockWall.tga"},
			{L"HEART_TX", L"Heart.png"},
			{L"WALLSTOCK_TX", L"UI_MagicWall.png"},
			{L"GAMETITLE_TX", L"Title.png"},
			{L"GAMESELECT_BG_TX", L"Select_BackGround.png"},
			{L"WHITE_TX", L"White.png"},
			{L"TO_NEXTSTAGE_TX", L"ToNextStage.png"},
			{L"TO_STAGESELECT_TX", L"ToStageSelect.png"},
			{L"TO_RETRY_TX", L"ToRetry.png"},
			{L"STAGE_1_TX", L"StageNum1.png"},
			{L"STAGE_2_TX", L"StageNum2.png"},
			{L"STAGE_3_TX", L"StageNum3.png"},
			{L"STAGE_4_TX", L"StageNum4.png"},
			{L"STAGE_5_TX", L"StageNum5.png"}
		};
		// アニメーション
		Pairs animPairs[] = 
		{
			//{WstringKey::Anim_Player, L"PL_Stand.bmf"},
			{WstringKey::Anim_Player, L"PL_Stand_Walk.bmf"}
		};
		//スタティック
		Pairs staticPairs[] =
		{
			{L"TREASURE_MESH", L"Treasure.bmf"},
			{L"SHELD_MESH", L"Shield.bmf"},
			{L"ENEMY_MESH", L"Enemy.bmf"},
			{L"STOPENEMY_MESH", L"StopEnemy.bmf"}

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
			{L"SE_BreakWall", L"BreakWall.wav"},
			{L"SE_PlayerDamage", L"PlayerDamage.wav"},
			{L"SE_MainBGM", L"MainBGM.wav"},
			{L"SE_GameClear", L"GameClear.wav"},
			{L"SE_GameTitle", L"GameTitle.wav"},
			{L"SE_GameSelect", L"GameSelect.wav"}
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
			Col.set(31.0f / 255.0f, 30.0f / 255.0f, 71.0f / 255.0f, 255.0f / 255.0f);
			SetClearColor(Col);
			//自分自身にイベントを送る
			//これにより各ステージやオブジェクトがCreate時にシーンにアクセスできる
			PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), WstringKey::ToGameTitle);
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
		else if (event->m_MsgStr == WstringKey::ToGameStage) {
			//最初のアクティブステージの設定
			ResetActiveStage<GameStage>();
		}
	}
}
//end basecross
