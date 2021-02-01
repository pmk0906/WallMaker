/*!
@file GameStage5.cpp
@brief ゲームステージ実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス実体
	//--------------------------------------------------------------------------------------
	void GameStage5::CreateViewLight()
	{
		const Vec3 eye(0.0f, 30.0f, -20.0f);
		const Vec3 at(0.0f);
		//OpeningCameraView用のビュー
		m_OpeningCameraView = ObjectFactory::Create<SingleView>(GetThis<Stage>());
		auto ptrOpeningCamera = ObjectFactory::Create<OpeningCamera>();
		m_OpeningCameraView->SetCamera(ptrOpeningCamera);
		m_PlayerCameraView = ObjectFactory::Create<SingleView>(GetThis<Stage>());
		auto ptrPlayerCamera = ObjectFactory::Create<PlayerCamera>();
		m_PlayerCameraView->SetCamera(ptrPlayerCamera);

		//初期状態ではm_OpeningCameraViewを使う
		SetView(m_OpeningCameraView);
		m_CameraSelect = CameraSelect_Stage5::openingCamera;
		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();
	}

	void GameStage5::CreateWall()
	{
		int mapRows = 20;
		int mapCols = 32;
		
		auto map = new int[mapRows * mapCols];

		const int mapData[] = 
		{
			01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,
			01,00,00,00,00,01,47,48,48, 8,48, 8,48, 8,48, 8,48,48,72,01,47,48,48,48,48,48,48,48,48,48,49,01,
			01,00,00,06,00,01,44,00,00, 8,00, 8,00, 8,00, 8,00,00,46,01,44,00,00,00,00,00,00,00,00,05,46,01,
			01,00,00,00,00,01,44,00,00, 8,00, 8,00, 8,00, 8,00,00,46,01,44,03,00,00,00,00,00,00,00,00,46,01,
			01,00,00,00,00,01,44,00,00, 8,00, 8,00, 8,00, 8,00,00,46,01,41,00,42,42,42,42,42,42,00,00,46,01,
			01,01,00,01,01,01,41,00,42, 8,42, 8,42, 8,42, 8,42,00,43,01,01,00,01,01,01,01,01,01,44,00,46,01,
			01,47,00,49,01,01,01,00,01,01,01,01,01,01,01,01,01,00,01,01,47,00,48,48,48,48,49,01,44,00,46,01,
			01,44, 9,46,01,47,48,00,48,48,48,49,01,47,48,48,48,00,49,01,44,00,00,00,00,00,46,01,44,00,46,01,
			01,44,00,46,01,44,00,00,00,00,03,46,01,44,00,00, 9,00,46,01,44,00,00,42,00,03,46,01,44,03,46,01,
			01,44,00,46,01,44,00,00,42,00,00,46,01,44,00,00,00,00,46,01,44,00,46,01,44,00,46,01,44,00,46,01,
			01, 8, 8, 8,01,44,00,46,01,44,00,46,01,44,00,00,00,00,46,01,44,00,00,48,00,00,46,01,44,00,46,01,
			01,44,00,46,01,44,00,00,48,00,00,46,01,44,00,00,00,03,46,01,44,00,03,00,00,00,46,01,44,00,46,01,
			01, 8, 8, 8,01,44,03,00,00,00,03,46,01,41,00,42,42,42,43,01,41,42,42,42,00,42,43,01,44,00,46,01,
			01,44,00,46,01,41,42,42,42,42,00,43,01,01,00,01,01,01,01,01,01,01,01,01,00,01,01,01,41,00,43,01,
			01, 8, 8, 8,01,01,01,01,01,01,00,01,01,47,00,48, 8,48, 8,48, 8,48, 8,48,00,49,01,01,01,00,01,01,
			01,44,00,00,48,48, 8,48, 8,48,00,49,01,44,00,00, 8,00, 8,00, 8,00, 8,00,00,46,01,00,00,00,00,01,
			01,44,00,00,00,00, 8,00, 8,00,00,46,01,44,00,00, 8,00, 8,00, 8,00, 8,00,00,46,01,00,00,00,00,01,
			01,44,00,00,00,00, 8,00, 8,00,00,46,01,44,00,00, 8,00, 8,00, 8,00, 8,00,00,46,01,00,02,00,00,01,
			01,76,42,42,42,42, 8,42, 8,42,42,78,01,41,42,42, 8,42, 8,42, 8,42, 8,42,42,78,01,00,00,00,00,01,
			01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,
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
				case 1: // 普通の壁
					AddGameObject<StageWall>(Vec3(3.0f, 6.0f, 3.0f), Vec3(0.0f), Vec3(pos.x, 3.0f, pos.z)); // 二段
					break;
				case 2: // プレイヤー生成
					CreatePlayer(pos);
					AddGameObject<WarpMagicSircle>(Vec3(0.0f), Vec3(0.0f), Vec3(pos.x, 4.0f, pos.z));
					break;
				case 3: // 通常の敵
					AddGameObject<EnemyFirst>(Vec3(2.0f, 1.0f, 3.5f), Vec3(0.0f), Vec3(pos));
					break;
				case 5: // 連射的
					AddGameObject<RapidFireEnemy>(Vec3(2.0f, 1.0f, 3.5f), Vec3(0.0f), Vec3(pos.x, 1.5f, pos.z));
					break;
				// 反射壁(テンキーの配置参照)
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
				case 72:
					AddGameObject<Cannon>(Vec3(2.0f, 3.0f, 2.0f), Vec3(0.0f, XMConvertToRadians(180.0f), 0.0f), Vec3(pos.x, 1.5f, pos.z));
					break;
				case 74:
					AddGameObject<Cannon>(Vec3(2.0f, 3.0f, 2.0f), Vec3(0.0f, XMConvertToRadians(270.0f), 0.0f), Vec3(pos.x, 1.5f, pos.z));
					break;
				case 76:
					AddGameObject<Cannon>(Vec3(2.0f, 3.0f, 2.0f), Vec3(0.0f, XMConvertToRadians(90.0f), 0.0f), Vec3(pos.x, 1.5f, pos.z));
					break;
				case 78:
					AddGameObject<Cannon>(Vec3(2.0f, 3.0f, 2.0f), Vec3(0.0f), Vec3(pos.x, 1.5f, pos.z));
					break;
				case 8:
					AddGameObject<BreakWall>(Vec3(3.0f), Vec3(0.0f), Vec3(pos.x, 1.5f, pos.z));
					break;
				case 9:
					AddGameObject<DangerEnemy>(Vec3(2.0f, 1.0f, 3.5f), Vec3(0.0f), Vec3(pos.x, 1.5f, pos.z));
					break;
				case 10:
					AddGameObject<PatrolEnemy>(Vec3(2.0f, 1.0f, 3.5f), Vec3(0.0f, XMConvertToRadians(180), 0.0f),
						Vec3(pos.x, 1.5f, pos.z));
					break;
				case 11:
					AddGameObject<PatrolEnemyUPDown>(Vec3(2.0f, 1.0f, 3.5f), Vec3(0.0f, XMConvertToRadians(90), 0.0f),
						Vec3(pos.x, 1.5f, pos.z));
					break;
				case 12:
					AddGameObject<PatrolEnemyUPDown>(Vec3(2.0f, 1.0f, 3.5f), Vec3(0.0f, XMConvertToRadians(270), 0.0f),
						Vec3(pos.x, 1.5f, pos.z));
					break;
				default:
					break;
				}
				if (map[r * mapCols + c] == 6)
				{
					auto treasureBox = AddGameObject<TreasureBox>(Vec3(1.0f), Vec3(0.0f), Vec3(pos.x, 1.5f, pos.z));
					SetSharedGameObject(WstringKey::ShareObj_TreasureBox, treasureBox);
				}
			}
		}
	}

	void GameStage5::DrawStrings()
	{

	}

	void GameStage5::OnCreate() 
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
		CreateCameraman();

		auto gameManagement = AddGameObject<GameManagement>(Vec3(0.0f), Vec3(0.0f), Vec3(0.0f));
		SetSharedGameObject(WstringKey::ShareObj_GameManagement, gameManagement);

		auto gm = GameManager::GetInstance();
		gm->InitGameManager();
		gm->SetSceneNum(SceneNum::GameStage_5);

		//BGM
		auto ptrXA = App::GetApp()->GetXAudio2Manager();
		m_BGM = ptrXA->Start(WstringKey::BGM_MainBGM, XAUDIO2_LOOP_INFINITE, 0.5f);

		CreateSpriteAndButton();

		auto testObj = AddGameObject<TestObject>();
		SetSharedGameObject(WstringKey::ShareObj_TestObject, testObj);
	}

	void GameStage5::OnUpdate() 
	{
		auto gm = GameManager::GetInstance();
		gm->ClearCheck(GetThis<Stage>());

		if (gm->GetClearFlg() == true && gm->GetClearFlgChanged() == false)
		{
			if (gm->GetTreasureBoxOpen() == true)
			{
				ChangeBGM(L"BGM_GameClear");
			}
			if (gm->GetGoalMotionEnd() == true)
			{
				CreateClearButton();
				gm->SetClearFlgChanged(true);
			}
		}
		else if (gm->GetDeathFlg() == true && gm->GetDeathFlgChanged() == false)
		{
			if (gm->GetCameraZoomEnd() == true)
			{
				ChangeBGM(L"BGM_GameOver");
			}
			if (gm->GetDeathMotionEnd() == true)
			{
				CreateGameOverButton();
				gm->SetDeathFlgChanged(true);
			}
		}
		else if (gm->GetMagicSircleMoved() == true)
		{
			if (gm->GetPoseFlgChanged() == false)
			{
				if (gm->GetPoseFlg() == true)
				{
					SwitchPoseButton(true);
					gm->SetPoseFlgChanged(true);
				}
				else
				{
					SwitchPoseButton(false);
					gm->SetPoseFlgChanged(true);
				}
			}
		}

		gm->SetCameraName(GetCameraSelectName());
	}

	void GameStage5::OnUpdate2()
	{
		auto testObj = GetSharedGameObject<TestObject>(WstringKey::ShareObj_TestObject);
		testObj->SetCamName(GetCameraSelectName());
	}

	void GameStage5::CreateStage()
	{
		float posX = 0.0f;
		float posZ = 0.0f;
		Vec3 stagePos = Vec3(posX, 0, posZ);
		for (int l = 0; l < STAGE_LENGTH / 4; l++) {
			for (int w = 0; w < STAGE_WIDTH / 4; w++) {
				AddGameObject<Floor>(Vec3(12.0f, 1.0f, 12.0f), Vec3(0.0f), Vec3(w * 12 - STAGE_LENGTH - 7.5f, -0.5f, l * 12 - STAGE_WIDTH - 0.5f));
			}
		}
		//床一枚のみ
		//AddGameObject<Floor>(Vec3(32.0f * 3.0f, 1.0f, 16.0f * 3.0f), Vec3(0.0f), Vec3(32.0f * 1.5f - 32.0f - 1.5f, 0.0f, -16.0f * 1.5f + 16.0f + 1.5f));

		CreateWall();


	}

	void GameStage5::CreateEnemy()
	{
		////敵�@
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

	void GameStage5::CreatePlayer(Vec3 pos)
	{
		auto player = AddGameObject<Player>(Vec3(1.5f), Vec3(0.0f), Vec3(pos.x, 2.0f, pos.z));
		SetSharedGameObject(WstringKey::ShareObj_Player, player);

	}

	void GameStage5::CreateUI()
	{
		//プレイヤーのライフ表示
		AddGameObject<PlayerLife>(true, Vec2(70.0f), Vec3(-469.0f, 336.0f, 0.1f), 1.0f);
		AddGameObject<PlayerLife>(true, Vec2(70.0f), Vec3(-385.0f, 336.0f, 0.1f), 2.0f);
		AddGameObject<PlayerLife>(true, Vec2(70.0f), Vec3(-299.0f, 336.0f, 0.1f), 3.0f);

		AddGameObject<Sprite>(true, Vec2(400.0f, 200.0f), Vec2(-440.0f, 345.0f), L"HP_FRONT_UI_TX", 1.0f, Col4(1.0f));
		AddGameObject<Sprite>(true, Vec2(300.0f, 150.0f), Vec2(-390.0f, 340.0f), L"HP_BACK_UI_TX", -1.0f, Col4(1.0f));

		//壁のストック表示
		AddGameObject<WallStock>(true, Vec2(70.0f), Vec3(+468.0f, 340.0f, 0.1f), 1.0f);
		AddGameObject<WallStock>(true, Vec2(70.0f), Vec3(+384.0f, 340.0f, 0.1f), 2.0f);
		AddGameObject<WallStock>(true, Vec2(70.0f), Vec3(+297.0f, 340.0f, 0.1f), 3.0f);

		AddGameObject<Sprite>(true, Vec2(400.0f, 200.0f), Vec2(430.0f, 345.0f), L"WALLSTOCKFRONT_UI_TX", 1.0f, Col4(1.0f));
		AddGameObject<Sprite>(true, Vec2(400.0f, 200.0f), Vec2(430.0f, 345.0f), L"WALLSTOCKBACK_UI_TX", -1.0f, Col4(1.0f));
	}

	//カメラマンの作成
	void GameStage5::CreateCameraman() 
	{
		// オープニングカメラを登録
		auto ptrOpeningCameraman = AddGameObject<OpeningCameraman>();
		//シェア配列にOpeningCameramanを追加
		SetSharedGameObject(WstringKey::ShareObj_OpeningCameraman, ptrOpeningCameraman);

		auto ptrOpeningCamera = dynamic_pointer_cast<OpeningCamera>(m_OpeningCameraView->GetCamera());
		if (ptrOpeningCamera) {
			ptrOpeningCamera->SetCameraObject(ptrOpeningCameraman);
			SetView(m_OpeningCameraView);
			m_CameraSelect = CameraSelect_Stage5::openingCamera;
		}

		// ゴールカメラを登録
		auto ptrPlayerCameraman = AddGameObject<PlayerCameraman>();
		//シェア配列にOpeningCameramanを追加
		SetSharedGameObject(WstringKey::ShareObj_PlayerCameraman, ptrPlayerCameraman);
	}

	void GameStage5::CreateClearButton()
	{
		auto gm = GameManager::GetInstance();

		auto whiteSprite = dynamic_pointer_cast<FadeSprite>(WhiteSprite);
		whiteSprite->SetColor(Col4(1.0f, 1.0f, 1.0f, 0.5f));
		whiteSprite->SetFadeFlgChanged(false);
		whiteSprite->SetDrawActive(true);

		auto clearSprite = AddGameObject<FadeSprite>(true, Vec2(800, 300), Vec2(0, 150), true, 1.0f, 0.0f, L"GAMECLEAR_TX", 1, Col4(1, 1, 1, 0.1f));
		clearSprite->SetFadeFlgChanged(false);

		auto buttonSprite = AddGameObject<ButtonSprite>(true, Vec2(600, 100), Vec2(0, -70.0f), true, 1.0f, L"NEXTSTAGE_BUTTON_TX", 0, 2, Col4(1, 1, 1, 0.5f));
		auto buttonSprite2 = AddGameObject<ButtonSprite>(true, Vec2(600, 100), Vec2(0, -220.0f), true, 1.0f, L"STAGESELECT_BUTTON_TX", 1, 2, Col4(1, 1, 1, 0.5f));
		gm->SetMaxButtonNum(1);
	}

	void GameStage5::CreateGameOverButton()
	{
		auto gm = GameManager::GetInstance();

		auto whiteSprite = dynamic_pointer_cast<FadeSprite>(WhiteSprite);
		whiteSprite->SetColor(Col4(0.0f, 0.0f, 0.0f, 0.5f));
		whiteSprite->SetFadeFlgChanged(false);
		whiteSprite->SetDrawActive(true);

		gm->SetDeathFlgChanged(true);

		auto clearSprite = AddGameObject<FadeSprite>(true, Vec2(800, 300), Vec2(0, 150), true, 1.0f, 0.0f, L"GAMEOVER_TX", 1, Col4(1, 1, 1, 0.1f));
		clearSprite->SetFadeFlgChanged(false);

		auto buttonSprite = AddGameObject<ButtonSprite>(true, Vec2(600, 100), Vec2(0, -70.0f), true, 1.0f, L"RETRY_BUTTON_TX", 0, 2, Col4(1, 1, 1, 0.5f));
		auto buttonSprite2 = AddGameObject<ButtonSprite>(true, Vec2(600, 100), Vec2(0, -220.0f), true, 1.0f, L"STAGESELECT_BUTTON_TX", 1, 2, Col4(1, 1, 1, 0.5f));
		gm->SetMaxButtonNum(1);
	}

	void GameStage5::CreateSpriteAndButton()
	{
		WhiteSprite = AddGameObject<FadeSprite>(true, Vec2(1120, 630), Vec2(0, 0), true, 0.5f, 0.0f, L"WHITE_TX", 1, Col4(1, 1, 1, 0.5f));
		WhiteSprite->SetDrawActive(false);

		m_Button1 = AddGameObject<ButtonSprite>(true, Vec2(600, 100), Vec2(0, -60.0f), true, 1.0f, L"RETRY_BUTTON_TX", 0, 2, Col4(1, 1, 1, 0.5f));
		m_Button1->SetDrawActive(false);
		m_Button1->SetUpdateActive(false);
		m_Button2 = AddGameObject<ButtonSprite>(true, Vec2(600, 100), Vec2(0, -150.0f), true, 1.0f, L"STAGESELECT_BUTTON_TX", 1, 2, Col4(1, 1, 1, 0.5f));
		m_Button2->SetDrawActive(false);
		m_Button2->SetUpdateActive(false);
		m_Button3 = AddGameObject<ButtonSprite>(true, Vec2(600, 100), Vec2(0, -240.0f), true, 1.0f, L"GAMEBACK_BUTTON_TX", 2, 2, Col4(1, 1, 1, 0.5f));
		m_Button3->SetDrawActive(false);
		m_Button3->SetUpdateActive(false);
	}

	void GameStage5::SwitchPoseButton(bool poseFlg)
	{
		auto gm = GameManager::GetInstance();

		auto whiteSprite = dynamic_pointer_cast<FadeSprite>(WhiteSprite);
		whiteSprite->SetDrawActive(poseFlg);
		whiteSprite->SetUpdateActive(poseFlg);

		m_Button1->SetDrawActive(poseFlg);
		m_Button1->SetUpdateActive(poseFlg);
		m_Button2->SetDrawActive(poseFlg);
		m_Button2->SetUpdateActive(poseFlg);
		m_Button3->SetDrawActive(poseFlg);
		m_Button3->SetUpdateActive(poseFlg);

		gm->SetPoseFlg(poseFlg);
		gm->SetPoseFlgChanged(true);

		if (poseFlg == true)
		{
			gm->SetMoveEnabledFlg(false);
		}
		else
		{
			gm->SetMoveEnabledFlg(true);
		}

		gm->SetMaxButtonNum(2);
	}

	void GameStage5::StopBGM()
	{
		auto ptrXA = App::GetApp()->GetXAudio2Manager();

		ptrXA->Stop(m_BGM);
	}

	void GameStage5::ChangeBGM(wstring bgmKey)
	{
		if (GetBgmName() != bgmKey)
		{
			StopBGM();
			//BGM
			auto ptrXA = App::GetApp()->GetXAudio2Manager();
			m_BGM = ptrXA->Start(bgmKey, XAUDIO2_LOOP_INFINITE, 0.5f);
			SetBgmName(bgmKey);
		}
	}

	void GameStage5::SetBgmName(wstring bgmName)
	{
		m_BgmName = bgmName;
	}

	wstring GameStage5::GetBgmName()
	{
		return m_BgmName;
	}

	void GameStage5::ToMyCamera() {
		auto gm = GameManager::GetInstance();

		//MyCameraに変更
		if (m_CameraSelect == CameraSelect_Stage5::openingCamera)
		{
			auto ptrPlayer = GetSharedGameObject<Player>(WstringKey::ShareObj_Player);
			auto ptrMyCamera = dynamic_pointer_cast<MyCamera>(m_MyCameraView->GetCamera());
			if (ptrMyCamera) {
				ptrMyCamera->SetTargetObject(ptrPlayer);
				auto playerPos = ptrPlayer->GetComponent<Transform>()->GetPosition();
				auto eyePos = playerPos + gm->GetMyCameraOffset();
				ptrMyCamera->SetEye(eyePos);

				//m_MyCameraViewを使う
				SetView(m_MyCameraView);
				m_CameraSelect = CameraSelect_Stage5::myCamera;
			}
		}
	}

	void GameStage5::ToPlayerCamera() {
		auto gm = GameManager::GetInstance();

		//MyCameraに変更
		if (m_CameraSelect == CameraSelect_Stage5::openingCamera)
		{
			auto ptrPlayer = GetSharedGameObject<Player>(WstringKey::ShareObj_Player);
			auto ptrPlayerCamera = dynamic_pointer_cast<PlayerCamera>(m_PlayerCameraView->GetCamera());
			if (ptrPlayerCamera) {

				//m_MyCameraViewを使う
				SetView(m_PlayerCameraView);
				m_CameraSelect = CameraSelect_Stage5::playerCamera;
			}
		}
	}

	void GameStage5::ToGoalCamera() {
		//GoalCameraに変更
		if (m_CameraSelect == CameraSelect_Stage5::myCamera)
		{
			auto ptrGoalCam = GetSharedGameObject<GoalCameraman>(WstringKey::ShareObj_GoalCameraman);
			auto ptrGoalCamera = dynamic_pointer_cast<GoalCamera>(m_GoalCameraView->GetCamera());
			if (ptrGoalCamera) {
				ptrGoalCamera->SetCameraObject(ptrGoalCam);

				auto gm = GameManager::GetInstance();
				//ステージの取得
				auto scene = App::GetApp()->GetScene<Scene>();
				auto stage = scene->GetActiveStage();
				//プレイヤーの取得
				auto share_player = stage->GetSharedGameObject<Player>(WstringKey::ShareObj_Player);
				auto playerPos = share_player->GetPosition();
				auto myCamPos = gm->GetMyCameraOffset();
				Vec3 myPos = playerPos + myCamPos;
				ptrGoalCamera->SetEye(myPos);
				auto at = ptrGoalCamera->GetAt();
				at = playerPos;
				ptrGoalCamera->SetAt(playerPos);

				ptrGoalCamera->SetUp(0, 1, 0); // カメラの上方向を示す単位ベクトル

				//m_GoalCameraViewを使う
				SetView(m_GoalCameraView);
				m_CameraSelect = CameraSelect_Stage5::goalCamera;
			}
		}
	}

	wstring GameStage5::GetCameraSelectName()
	{
		wstring camName = L"";
		if (m_CameraSelect == CameraSelect_Stage5::openingCamera)
		{
			camName = L"OpeningCamera\n";
		}
		else if (m_CameraSelect == CameraSelect_Stage5::myCamera)
		{
			camName = L"MyCamera\n";
		}
		else if (m_CameraSelect == CameraSelect_Stage5::goalCamera)
		{
			camName = L"GoalCamera\n";
		}
		else if (m_CameraSelect == CameraSelect_Stage5::playerCamera)
		{
			camName = L"PlayerCamera\n";
		}
		return camName;
	}
}
//end basecross
