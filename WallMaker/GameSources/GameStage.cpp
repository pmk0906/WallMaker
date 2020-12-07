/*!
@file GameStage.cpp
@brief ゲームステージ実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス実体
	//--------------------------------------------------------------------------------------
	void GameStage::CreateViewLight() 
	{
		const Vec3 eye(0.0f, 30.0f, -20.0f);
		const Vec3 at(0.0f);
		auto PtrView = CreateView<SingleView>();
		//ビューのカメラの設定
		auto PtrCamera = ObjectFactory::Create<MyCamera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);
		PtrCamera->SetAt(at);
		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();
	}

	void GameStage::CreateWall()
	{
		int mapRows = 16;
		int mapCols = 32;
		
		auto map = new int[mapRows * mapCols];

		const int mapData[] = 
		{
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ,1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1,47,48,48,48,48,48,48,48,48,48,48,48,48,49, 1, 1, 1,47,48,48,48,48,48,48,48,48,48,48,48,49, 1,
			1,44, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,49, 1,47 ,3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3,46, 1,
			1,44, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0,46, 1,44, 0, 0, 0,42,42,42,42, 0, 0, 0, 0, 0,46, 1,
			1,41,42,42,42,42,42, 0, 0, 0, 0, 0, 0, 0, 0,46, 1,44, 0, 0,46, 1, 1, 1, 1,41, 0, 0, 0, 0,46, 1,
			1, 1, 1, 1, 1, 1, 1,44, 0, 0, 0, 0, 0, 0, 0,46, 1,44, 0, 0, 0,48,48,48,49, 1,44, 0, 0, 0,46, 1,
			1,47,48,48,48,48,48, 0, 0, 0, 0, 0, 0, 0, 0,46, 1,44, 0, 0, 0, 0, 0, 0,46, 1,41, 0, 0, 0,46, 1,
			1,44, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,46, 1,44, 0, 0, 0, 0, 3, 0, 0,49, 1,44, 0, 0,46, 1,
			1,44, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,46, 1,41, 0, 0, 0, 0, 0, 0, 0,46, 1,44, 0, 3,46, 1,
			1,44, 0, 0, 0, 0, 0, 0, 0,42,42,42,42,42,42,43, 1, 1,41,42,42,42, 0, 0, 0,46, 1,44, 0, 0,46, 1,
			1,44, 0, 0, 0, 0, 0, 0,46, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,44, 0, 0,46, 1,44, 0, 0,46, 1,
			1,44, 0, 0, 0, 0, 0, 0, 0,48,48,48,48,48,48,48,48,48,48,48,48,48, 0, 0, 0,46, 1,44, 0, 0,46, 1,
			1,44, 0, 5, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0,46, 1,44, 0, 0,46, 1,
			1,44, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,46, 1,44, 0, 2,46, 1,
			1,41,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,43, 1,41,42,42,43, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1


			//1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ,1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			//1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
			//1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 ,3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 1,
			//1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
			//1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1,
			//1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1,
			//1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1,
			//1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 3, 0, 0, 1, 0, 0, 0, 0, 1,
			//1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 3, 0, 1,
			//1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1,
			//1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1,
			//1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1,
			//1, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 6, 0, 0, 0, 1,
			//1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 2, 0, 1,
			//1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 1 ,0 ,0 ,0, 0, 1,
			//1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
		};

		memcpy(map, mapData, sizeof(int) * mapRows * mapCols);

		// ブロック
		for (int r = 0; r < mapRows; r++) {
			for (int c = 0; c < mapCols; c++) {
				auto pos = Vec3((c * 3.0f) - mapCols, 1.0f, -(r * 3.0f) + mapRows);
				auto scale = Vec3(3.0f, 3.0f, 0.5f);
				switch (map[r * mapCols + c]) {
				case 0:
					break;
				case 1:
					AddGameObject<StageWall>(Vec3(3.0f), Vec3(0.0f), Vec3(pos));
					break;
				case 2:
					CreatePlayer(pos);
					break;
				case 3:
					AddGameObject<EnemyFirst>(Vec3(2.0f, 1.0f, 3.5f), Vec3(0.0f), Vec3(pos));
					break;
				case 5:
					AddGameObject<RapidFireEnemy>(Vec3(2.0f, 1.0f, 3.5f), Vec3(0.0f), Vec3(pos.x, 1.5f, pos.z));
					break;
				case 41:
					AddGameObject<StageRefrectWall>(Vec3(scale), Vec3(0.0f, XMConvertToRadians(90.0f), 0.0f), Vec3(pos.x - 1.3f, 1.5f, pos.z));
					AddGameObject<StageRefrectWall>(Vec3(scale), Vec3(0.0f), Vec3(pos.x, 1.5f, pos.z - 1.3f));
					break;
				case 42:
					AddGameObject<StageRefrectWall>(Vec3(scale), Vec3(0.0f), Vec3(pos.x, 1.5f, pos.z - 1.3f));
					break;
				case 43:
					AddGameObject<StageRefrectWall>(Vec3(scale), Vec3(0.0f, XMConvertToRadians(90.0f), 0.0f), Vec3(pos.x + 1.3f, 1.5f, pos.z));
					AddGameObject<StageRefrectWall>(Vec3(scale), Vec3(0.0f), Vec3(pos.x, 1.5f, pos.z - 1.3f));
					break;
				case 44:
					AddGameObject<StageRefrectWall>(Vec3(scale), Vec3(0.0f, XMConvertToRadians(90.0f), 0.0f), Vec3(pos.x - 1.3f, 1.5f, pos.z));
					break;
				case 46:
					AddGameObject<StageRefrectWall>(Vec3(scale), Vec3(0.0f, XMConvertToRadians(90.0f), 0.0f), Vec3(pos.x + 1.3f, 1.5f, pos.z));
					break;
				case 47:
					AddGameObject<StageRefrectWall>(Vec3(scale), Vec3(0.0f, XMConvertToRadians(90.0f), 0.0f), Vec3(pos.x - 1.3f, 1.5f, pos.z));
					AddGameObject<StageRefrectWall>(Vec3(scale), Vec3(0.0f), Vec3(pos.x, 1.5f, pos.z + 1.3f));
					break;
				case 48:
					AddGameObject<StageRefrectWall>(Vec3(scale), Vec3(0.0f), Vec3(pos.x, 1.5f, pos.z + 1.3f));
					break;
				case 49:
					AddGameObject<StageRefrectWall>(Vec3(scale), Vec3(0.0f, XMConvertToRadians(90.0f), 0.0f), Vec3(pos.x + 1.3f, 1.5f, pos.z));
					AddGameObject<StageRefrectWall>(Vec3(scale), Vec3(0.0f), Vec3(pos.x, 1.5f, pos.z + 1.3f));
					break;
				case 6:
					AddGameObject<Treasure>(Vec3(1.0f), Vec3(0.0f), Vec3(pos.x, 1.5f, pos.z));

				}
			}
		}
	}

	void GameStage::DrawStrings()
	{
		auto gm = GameManager::GetInstance();


	}

	void GameStage::OnCreate() 
	{
		try {
			//ビューとライトの作成
			CreateViewLight();
		}
		catch (...) {
			throw;
		}

		CreateStage();
		CreateEnemy();
		CreateUI();
		//CreatePlayer(Vec3(0.0f, 1.0f, 0.0f));

		AddGameObject<GameManagement>(Vec3(0.0f), Vec3(0.0f), Vec3(0.0f));

		auto gm = GameManager::GetInstance();
		gm->InitGameManager();
		gm->SetSceneNum(SceneNum::GameStage1);

		//BGM
		auto ptrXA = App::GetApp()->GetXAudio2Manager();
		m_BGM = ptrXA->Start(WstringKey::SE_MainBGM, 0, 1.0f);

		auto startSprite = AddGameObject<FadeSprite>(true, Vec2(800, 300), Vec2(0, 150), false, 0.0f, 3.0f, L"START_TX", 1, Col4(1, 1, 1, 1.0f));

	}

	void GameStage::OnUpdate() 
	{
		auto gm = GameManager::GetInstance();

		gm->ClearCheck(GetThis<Stage>());

		if (gm->GetClearFlg() == true && gm->GetClearFlgChanged() == false)
		{
			auto whiteSprite = AddGameObject<FadeSprite>(true, Vec2(1120, 630), Vec2(0, 0), true, 0.5f, 0.0f, L"WHITE_TX", 1, Col4(1, 1, 1, 0.5f));
			whiteSprite->SetFadeFlgChanged(false);
			gm->SetClearFlg(false);
			gm->SetClearFlgChanged(true);

			auto clearSprite = AddGameObject<FadeSprite>(true, Vec2(800, 300), Vec2(0, 150), true, 1.0f, 0.0f, L"GAMECLEAR_TX", 1, Col4(1, 1, 1, 0.1f));
			clearSprite->SetFadeFlgChanged(false);

			auto buttonSprite = AddGameObject<ButtonSprite>(true, Vec2(600, 100), Vec2(0, -70.0f), true, 1.0f, L"NEXTSTAGE_BUTTON_TX", 0, 2, Col4(1, 1, 1, 0.5f));
			auto buttonSprite2 = AddGameObject<ButtonSprite>(true, Vec2(600, 100), Vec2(0, -220.0f), true, 1.0f, L"STAGESELECT_BUTTON_TX", 1, 2, Col4(1, 1, 1, 0.5f));
			gm->SetMaxButtonNum(1);
		}
		if (gm->GetDeathFlg() == true && gm->GetDeathFlgChanged() == false)
		{
			auto whiteSprite = AddGameObject<FadeSprite>(true, Vec2(1120, 630), Vec2(0, 0), true, 0.5f, 0.0f, L"WHITE_TX", 1, Col4(0, 0, 0, 0.5f));
			whiteSprite->SetFadeFlgChanged(false);
			gm->SetDeathFlg(false);
			gm->SetDeathFlgChanged(true);

			auto clearSprite = AddGameObject<FadeSprite>(true, Vec2(800, 300), Vec2(0, 150), true, 1.0f, 0.0f, L"GAMEOVER_TX", 1, Col4(1, 1, 1, 0.1f));
			clearSprite->SetFadeFlgChanged(false);

			auto buttonSprite = AddGameObject<ButtonSprite>(true, Vec2(600, 100), Vec2(0, -70.0f), true, 1.0f, L"RETRY_BUTTON_TX", 0, 2, Col4(1, 1, 1, 0.5f));
			auto buttonSprite2 = AddGameObject<ButtonSprite>(true, Vec2(600, 100), Vec2(0, -220.0f), true, 1.0f, L"STAGESELECT_BUTTON_TX", 1, 2, Col4(1, 1, 1, 0.5f));
			gm->SetMaxButtonNum(1);
		}

	}

	void GameStage::CreateStage()
	{
		// 床
		//AddGameObject<FixedBox>(Vec3(50.0f, 1.0f, 50.0f), Vec3(0.0f), Vec3(0.0f, -0.5f, 0.0f));
		int posX = 0;
		int posZ = 0;
		Vec3 stagePos = Vec3(posX, 0, posZ);
		for (int l = 0; l < STAGE_LENGTH; l++) {
			for (int w = 0; w < STAGE_WIDTH; w++) {
				//AddGameObject<Floor>(Vec3(3.0f, 1.0f, 3.0f), Vec3(0.0f), Vec3(w * 3 - STAGE_LENGTH, -0.5f, l * 3 - STAGE_WIDTH));
			}
		}
		AddGameObject<Floor>(Vec3(32.0f * 3.0f, 1.0f, 16.0f * 3.0f), Vec3(0.0f), Vec3(32.0f * 1.5f - 32.0f - 1.5f, 0.0f, -16.0f * 1.5f + 16.0f + 1.5f));

		CreateWall();

	}

	void GameStage::CreateEnemy()
	{
		////敵①
		//AddGameObject<EnemyFirst>(Vec3(2.0f, 1.0f, 3.5f), Vec3(0.0f), Vec3(-5.0f, 1.5f, 0.0f));

		////往復敵（横）
		//AddGameObject<PatrolEnemy>(Vec3(3.0f, 1.0f, 2.0f), Vec3(0.0f, XMConvertToRadians(180), 0.0f),
		//	Vec3(-3.0f, 1.5f, 5.0f));

		////往復敵（縦）
		//AddGameObject<PatrolEnemyUPDown>(Vec3(3.0f, 1.0f, 2.0f), Vec3(0.0f, XMConvertToRadians(270), 0.0f),
		//	Vec3(10.0f, 1.5f, -5.0f));

		////連射する敵
		//AddGameObject<RapidFireEnemy>(Vec3(2.0f, 1.0f, 3.5f), Vec3(0.0f), Vec3(0.0f, 1.5f, -5.0f));

		//強い球を撃つ敵
		//AddGameObject<DangerEnemy>(Vec3(2.0f, 1.0f, 3.5f), Vec3(0.0f), Vec3(-5.0f, 1.5f, -3.0f));

		//大砲
		//AddGameObject<Cannon>(Vec3(2.0f, 1.0f, 3.5f), Vec3(0.0f), Vec3(-5.0f, 1.5f, -3.0f));
	}

	void GameStage::CreatePlayer(Vec3 pos)
	{
		auto player = AddGameObject<Player>(Vec3(1.5f), Vec3(0.0f), Vec3(pos.x, 2.0f, pos.z));
		SetSharedGameObject(WstringKey::ShareObj_Player, player);
		SetSharedGameObject(L"Player", player);

	}

	void GameStage::CreateUI()
	{
		//プレイヤーのライフ表示
		AddGameObject<PlayerLife>(true, Vec2(100.0f), Vec3(-590.0f, 350.0f, 0.1f), 1.0f);
		AddGameObject<PlayerLife>(true, Vec2(100.0f), Vec3(-490.0f, 350.0f, 0.1f), 2.0f);
		AddGameObject<PlayerLife>(true, Vec2(100.0f), Vec3(-390.0f, 350.0f, 0.1f), 3.0f);
		//壁のストック表示
		AddGameObject<WallStock>(true, Vec2(100.0f), Vec3(+590.0f, 350.0f, 0.1f), 1.0f);
		AddGameObject<WallStock>(true, Vec2(100.0f), Vec3(+490.0f, 350.0f, 0.1f), 2.0f);
		AddGameObject<WallStock>(true, Vec2(100.0f), Vec3(+390.0f, 350.0f, 0.1f), 3.0f);
	}

	void GameStage::StopBGM()
	{
		auto ptrXA = App::GetApp()->GetXAudio2Manager();

		ptrXA->Stop(m_BGM);
	}
}
//end basecross
