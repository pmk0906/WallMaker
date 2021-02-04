/*!
@file GameStage9.cpp
@brief ゲームステージ実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス実体
	//--------------------------------------------------------------------------------------
	void GameStage9::CreateViewLight()
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
		m_CameraSelect = CameraSelect_Stage9::openingCamera;
		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();
	}

	void GameStage9::CreateWall()
	{
		int mapRows = 24;
		int mapCols = 28;

		auto map = new int[mapRows * mapCols];

		const int mapData[] =
		{
			001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,
			001,000,000,000,000,000,000,000,001,047, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 49,001,
			001,000,000,000,002,000,000,000,000,000,000,000,000,000,000,000,005,000,000,000,000,000,  9,000,000,000,046,001,
			001,000,000,000,000,000,000,000,001,044,000,000,000,000,000,000,000,000,000,000,042,000,000,000,000,000,046,001,
			001,001,000,001,001,001,001,001,001,044,000,000,000,005,000,000,000,000,000,046,001,044,000,000,005,000,046,001,
			001,047,000, 48, 48, 48, 48, 49,001,044,000,000,000,000,042,000,000,000,  9,000, 48,000,000,000,000,000,046,001,
			001,044,000,000,000,000,000,046,001,044,000,000,000,046,001,044,000,000,000,000,000,000,000,042,042,000,043,001,
			001,044,000,000,000,000,000,046,001,044,000,000,000,000, 48,000,000,000,042,000,000,005,046,001,001,000,001,001,
			001,044,000,003,000,042,000,046,001,044,000,005,000,000,000,000,000,046,001,044,000,000,046,001,000,000,000,001,
			001,044,042,000,046,001,044,046,001,044,000,000,000,000,000,000,  9,000, 48,000,000,000,046,001,000,006,000,001,
			001,442,001,044,000, 48,000,046,001,041,042,042,042,042,042,042,042,042,042,042,042,042,043,001,000,000,000,001,
			001,044, 48,000,000,000,003,046,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,000,001,001,
			001,044,000,000,000,000,000,046,001,047, 48, 48, 48, 48, 48, 48, 48, 48, 49,001,047, 48, 48, 48, 48,000, 49,001,
			001,044,005,042,000,000,000,046,001,044,000,000,000,000,000,000,000,000,046,001,044,000,000,000,000,005,046,001,
			001,044,046,001,044,000,000,046,001,044,000,  9,000,000,000,000,000,000,046,001,044,003,000,000,000,000,046,001,
			001,044,000, 48,000,000,000,074,001,044,000,000,000,042,000,000,005,000,046,001,044,000,003,000,000,000,046,001,
			001,044,000,000,000,000,000,046,001,044,000,000,046,001,044,000,000,000,  8,001,044,000,000,042,000,000,046,001,
			001,044,000,000,000,042,042,043,001,044,003,000,000, 48,000,000,000,  8,046,001,044,000,046,001,044,000,046,001,
			001,  8,  8,  8,  8,001,001,001,001,044,000,000,000,000,003,000,  8,042,042,000,000,000,046,001,044,  9,046,001,
			001,  8,  8,  8,  8,001,001,001,001,044,000,000,000,000,000,046,001,001,001,001,044,000,046,001,044,000,046,001,
			001,044,000,000,000, 48, 48, 49,001,044,000,000,000,000,000,000, 48,074, 49,001,044,000,000, 48,000,000,046,001,
			001,044,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,046,001,044,000,000,000,000,000,046,001,
			001,041,042,042,042,042,042,043,001,041,042,042,042,042,042,042,042,042,043,001,041,042,042,042,042,042,043,001,
			001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,001,
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
				case StageObjectNum::ObjNum_StageWall: // 普通の壁
					AddGameObject<StageWall>(Vec3(3.0f, 6.0f, 3.0f), Vec3(0.0f), Vec3(pos.x, 3.0f, pos.z)); // 二段
					break;
				case StageObjectNum::ObjNum_Player: // プレイヤー生成
					CreatePlayer(pos);
					AddGameObject<WarpMagicSircle>(Vec3(0.0f), Vec3(0.0f), Vec3(pos.x, 4.0f, pos.z));
					break;
				case StageObjectNum::ObjNum_EnemyFirst: // 通常の敵
					AddGameObject<EnemyFirst>(Vec3(2.0f, 1.0f, 3.5f), Vec3(0.0f), Vec3(pos));
					break;
				case StageObjectNum::ObjNum_RapidFireEnemy: // 連射的
					AddGameObject<RapidFireEnemy>(Vec3(2.0f, 1.0f, 3.5f), Vec3(0.0f), Vec3(pos.x, 1.5f, pos.z));
					break;
					// 反射壁(テンキーの配置参照)
				case StageObjectNum::ObjNum_ReflectWall_1:
					AddGameObject<StageRefrectWall>(Vec3(scale), Vec3(0.0f, XMConvertToRadians(90.0f), 0.0f), Vec3(pos.x - 1.3f, 1.5f, pos.z));
					AddGameObject<StageRefrectWall>(Vec3(scale), Vec3(0.0f), Vec3(pos.x, 1.5f, pos.z - 1.3f));
					break;
				case StageObjectNum::ObjNum_RefrectWall_2:
					AddGameObject<StageRefrectWall>(Vec3(scale), Vec3(0.0f), Vec3(pos.x, 1.5f, pos.z - 1.3f));
					break;
				case StageObjectNum::ObjNum_ReflectWall_3:
					AddGameObject<StageRefrectWall>(Vec3(scale), Vec3(0.0f, XMConvertToRadians(90.0f), 0.0f), Vec3(pos.x + 1.3f, 1.5f, pos.z));
					AddGameObject<StageRefrectWall>(Vec3(scale), Vec3(0.0f), Vec3(pos.x, 1.5f, pos.z - 1.3f));
					break;
				case StageObjectNum::ObjNum_RefrectWall_4:
					AddGameObject<StageRefrectWall>(Vec3(scale), Vec3(0.0f, XMConvertToRadians(90.0f), 0.0f), Vec3(pos.x - 1.3f, 1.5f, pos.z));
					break;
				case StageObjectNum::ObjNum_RefrectWall_6:
					AddGameObject<StageRefrectWall>(Vec3(scale), Vec3(0.0f, XMConvertToRadians(90.0f), 0.0f), Vec3(pos.x + 1.3f, 1.5f, pos.z));
					break;
				case StageObjectNum::ObjNum_ReflectWall_7:
					AddGameObject<StageRefrectWall>(Vec3(scale), Vec3(0.0f, XMConvertToRadians(90.0f), 0.0f), Vec3(pos.x - 1.3f, 1.5f, pos.z));
					AddGameObject<StageRefrectWall>(Vec3(scale), Vec3(0.0f), Vec3(pos.x, 1.5f, pos.z + 1.3f));
					break;
				case StageObjectNum::ObjNum_RefrectWall_8:
					AddGameObject<StageRefrectWall>(Vec3(scale), Vec3(0.0f), Vec3(pos.x, 1.5f, pos.z + 1.3f));
					break;
				case StageObjectNum::ObjNum_ReflectWall_9:
					AddGameObject<StageRefrectWall>(Vec3(scale), Vec3(0.0f, XMConvertToRadians(90.0f), 0.0f), Vec3(pos.x + 1.3f, 1.5f, pos.z));
					AddGameObject<StageRefrectWall>(Vec3(scale), Vec3(0.0f), Vec3(pos.x, 1.5f, pos.z + 1.3f));
					break;
				case StageObjectNum::ObjNum_ReflectWall_28:
					AddGameObject<StageRefrectWall>(Vec3(scale), Vec3(0.0f), Vec3(pos.x, 1.5f, pos.z - 1.3f));
					AddGameObject<StageRefrectWall>(Vec3(scale), Vec3(0.0f), Vec3(pos.x, 1.5f, pos.z + 1.3f));
					break;
				case StageObjectNum::ObjNum_RefrectWall_46:
					AddGameObject<StageRefrectWall>(Vec3(scale), Vec3(0.0f, XMConvertToRadians(90.0f), 0.0f), Vec3(pos.x - 1.3f, 1.5f, pos.z));
					AddGameObject<StageRefrectWall>(Vec3(scale), Vec3(0.0f, XMConvertToRadians(90.0f), 0.0f), Vec3(pos.x + 1.3f, 1.5f, pos.z));
					break;
				case StageObjectNum::ObjNum_Cannon_2:
					AddGameObject<Cannon>(Vec3(2.0f, 3.0f, 2.0f), Vec3(0.0f, XMConvertToRadians(180.0f), 0.0f), Vec3(pos.x, 1.5f, pos.z));
					break;
				case StageObjectNum::ObjNum_Cannon_4:
					AddGameObject<Cannon>(Vec3(2.0f, 3.0f, 2.0f), Vec3(0.0f, XMConvertToRadians(270.0f), 0.0f), Vec3(pos.x, 1.5f, pos.z));
					break;
				case StageObjectNum::ObjNum_Cannon_6:
					AddGameObject<Cannon>(Vec3(2.0f, 3.0f, 2.0f), Vec3(0.0f, XMConvertToRadians(90.0f), 0.0f), Vec3(pos.x, 1.5f, pos.z));
					break;
				case StageObjectNum::ObjNum_Cannon_8:
					AddGameObject<Cannon>(Vec3(2.0f, 3.0f, 2.0f), Vec3(0.0f), Vec3(pos.x, 1.5f, pos.z));
					break;
				case StageObjectNum::ObjNum_BreakWall:
					AddGameObject<BreakWall>(Vec3(3.0f), Vec3(0.0f), Vec3(pos.x, 1.5f, pos.z));
					break;
				case StageObjectNum::ObjNum_DangerEnemy:
					AddGameObject<DangerEnemy>(Vec3(2.0f, 1.0f, 3.5f), Vec3(0.0f), Vec3(pos.x, 1.5f, pos.z));
					break;
				case StageObjectNum::ObjNum_PatrolEnemy_down:
					AddGameObject<PatrolEnemy>(Vec3(2.0f, 1.0f, 3.5f), Vec3(0.0f, XMConvertToRadians(180), 0.0f),
						Vec3(pos.x, 1.5f, pos.z));
					break;
				case StageObjectNum::ObjNum_PatrolEnemy_6:
					AddGameObject<PatrolEnemyUPDown>(Vec3(2.0f, 1.0f, 3.5f), Vec3(0.0f, XMConvertToRadians(90), 0.0f),
						Vec3(pos.x, 1.5f, pos.z));
					break;
				case StageObjectNum::ObjNum_PatrolEnemy_4:
					AddGameObject<PatrolEnemyUPDown>(Vec3(2.0f, 1.0f, 3.5f), Vec3(0.0f, XMConvertToRadians(270), 0.0f),
						Vec3(pos.x, 1.5f, pos.z));
					break;
				default:
					break;
				}
				if (map[r * mapCols + c] == StageObjectNum::ObjNum_Treasure)
				{
					auto treasureBox = AddGameObject<TreasureBox>(Vec3(1.0f), Vec3(0.0f), Vec3(pos.x, 1.5f, pos.z));
					SetSharedGameObject(WstringKey::ShareObj_TreasureBox, treasureBox);
				}
			}
		}
	}

	void GameStage9::DrawStrings()
	{

	}

	void GameStage9::OnCreate()
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

		auto gameManagement = AddGameObject<ManagerObject>(Vec3(0.0f), Vec3(0.0f), Vec3(0.0f));
		SetSharedGameObject(WstringKey::ShareObj_GameManagement, gameManagement);

		auto gm = GameManager::GetInstance();
		gm->InitGameManager();
		gm->SetSceneNum(SceneNum::GameStage_9);

		//BGM
		auto ptrXA = App::GetApp()->GetXAudio2Manager();
		m_BGM = ptrXA->Start(WstringKey::BGM_MainBGM, XAUDIO2_LOOP_INFINITE, 0.5f);

		CreateSpriteAndButton();

		auto testObj = AddGameObject<TestObject>();
		SetSharedGameObject(WstringKey::ShareObj_TestObject, testObj);
	}

	void GameStage9::OnUpdate()
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

	void GameStage9::OnUpdate2()
	{
		auto testObj = GetSharedGameObject<TestObject>(WstringKey::ShareObj_TestObject);
		testObj->SetCamName(GetCameraSelectName());
	}

	void GameStage9::CreateStage()
	{
		// 床
		float posX = 0.0f;
		float posZ = 0.0f;
		Vec3 stagePos = Vec3(posX, 0, posZ);
		for (int l = 0; l < STAGE_LENGTH / 4; l++) {
			for (int w = 0; w < STAGE_WIDTH / 4; w++) {
				AddGameObject<Floor>(Vec3(12.0f, 1.0f, 12.0f), Vec3(0.0f), Vec3(w * 12 - STAGE_WIDTH + 4.5f, -0.5f, l * 12 - STAGE_LENGTH - 16.0f));
			}
		}
		//床一枚のみ
		//AddGameObject<Floor>(Vec3(32.0f * 3.0f, 1.0f, 16.0f * 3.0f), Vec3(0.0f), Vec3(32.0f * 1.5f - 32.0f - 1.5f, 0.0f, -16.0f * 1.5f + 16.0f + 1.5f));

		CreateWall();

	}

	void GameStage9::CreateEnemy()
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

	void GameStage9::CreatePlayer(Vec3 pos)
	{
		auto player = AddGameObject<Player>(Vec3(1.5f), Vec3(0.0f), Vec3(pos.x, 2.0f, pos.z));
		SetSharedGameObject(WstringKey::ShareObj_Player, player);

	}

	void GameStage9::CreateUI()
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
	void GameStage9::CreateCameraman()
	{
		// オープニングカメラを登録
		auto ptrOpeningCameraman = AddGameObject<OpeningCameraman>();
		//シェア配列にOpeningCameramanを追加
		SetSharedGameObject(WstringKey::ShareObj_OpeningCameraman, ptrOpeningCameraman);

		//// ゴールカメラを登録
		//auto ptrGoalCameraman = AddGameObject<GoalCameraman>();
		////シェア配列にOpeningCameramanを追加
		//SetSharedGameObject(WstringKey::ShareObj_GoalCameraman, ptrGoalCameraman);

		auto ptrOpeningCamera = dynamic_pointer_cast<OpeningCamera>(m_OpeningCameraView->GetCamera());
		if (ptrOpeningCamera) {
			ptrOpeningCamera->SetCameraObject(ptrOpeningCameraman);
			SetView(m_OpeningCameraView);
			m_CameraSelect = CameraSelect_Stage9::openingCamera;
		}

		// ゴールカメラを登録
		auto ptrPlayerCameraman = AddGameObject<PlayerCameraman>();
		//シェア配列にOpeningCameramanを追加
		SetSharedGameObject(WstringKey::ShareObj_PlayerCameraman, ptrPlayerCameraman);
	}

	void GameStage9::CreateClearButton()
	{
		auto gm = GameManager::GetInstance();

		auto whiteSprite = dynamic_pointer_cast<FadeSprite>(WhiteSprite);
		whiteSprite->SetColor(Col4(1.0f, 1.0f, 1.0f, 0.5f));
		whiteSprite->SetFadeFlgChanged(false);
		whiteSprite->SetDrawActive(true);

		//gm->SetClearFlgChanged(true);

		auto clearSprite = AddGameObject<FadeSprite>(true, Vec2(800, 300), Vec2(0, 150), true, 1.0f, 0.0f, L"GAMECLEAR_TX", 1, Col4(1, 1, 1, 0.1f));
		clearSprite->SetFadeFlgChanged(false);

		auto buttonSprite = AddGameObject<ButtonSprite>(true, Vec2(600, 100), Vec2(0, -70.0f), true, 1.0f, L"NEXTSTAGE_BUTTON_TX", 0, 2, Col4(1, 1, 1, 0.5f));
		auto buttonSprite2 = AddGameObject<ButtonSprite>(true, Vec2(600, 100), Vec2(0, -220.0f), true, 1.0f, L"STAGESELECT_BUTTON_TX", 1, 2, Col4(1, 1, 1, 0.5f));
		gm->SetMaxButtonNum(1);
		gm->SetSelectingButton(0);
	}

	void GameStage9::CreateGameOverButton()
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
		gm->SetSelectingButton(0);
	}

	void GameStage9::CreateSpriteAndButton()
	{
		WhiteSprite = AddGameObject<FadeSprite>(true, Vec2(1120, 630), Vec2(0, 0), true, 0.5f, 0.0f, L"WHITE_TX", 1, Col4(1, 1, 1, 0.5f));
		WhiteSprite->SetDrawActive(false);

		ResultSprite = AddGameObject<Sprite>(true, Vec2(800, 200), Vec2(0, 150), L"POSE_TX", 1, Col4(1, 1, 1, 1.0f));
		ResultSprite->SetDrawActive(false);

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

	void GameStage9::SwitchPoseButton(bool poseFlg)
	{
		auto gm = GameManager::GetInstance();

		auto whiteSprite = dynamic_pointer_cast<FadeSprite>(WhiteSprite);
		whiteSprite->SetDrawActive(poseFlg);
		whiteSprite->SetUpdateActive(poseFlg);

		auto resultSprite = dynamic_pointer_cast<Sprite>(ResultSprite);
		resultSprite->SetDrawActive(poseFlg);
		resultSprite->SetUpdateActive(poseFlg);

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
			gm->SetSelectingButton(2);
			gm->SetMoveEnabledFlg(false);
		}
		else
		{
			gm->SetSelectingButton(0);
			gm->SetMoveEnabledFlg(true);
		}

		gm->SetMaxButtonNum(2);
	}

	void GameStage9::StopBGM()
	{
		auto ptrXA = App::GetApp()->GetXAudio2Manager();
		ptrXA->Stop(m_BGM);
	}

	void GameStage9::ChangeBGM(wstring bgmKey)
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

	void GameStage9::SetBgmName(wstring bgmName)
	{
		m_BgmName = bgmName;
	}

	wstring GameStage9::GetBgmName()
	{
		return m_BgmName;
	}

	void GameStage9::ToMyCamera() {
		auto gm = GameManager::GetInstance();

		//MyCameraに変更
		if (m_CameraSelect == CameraSelect_Stage9::openingCamera)
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
				m_CameraSelect = CameraSelect_Stage9::myCamera;
			}
		}
	}

	void GameStage9::ToPlayerCamera() {
		auto gm = GameManager::GetInstance();

		//MyCameraに変更
		if (m_CameraSelect == CameraSelect_Stage9::openingCamera)
		{
			auto ptrPlayer = GetSharedGameObject<Player>(WstringKey::ShareObj_Player);
			auto ptrPlayerCamera = dynamic_pointer_cast<PlayerCamera>(m_PlayerCameraView->GetCamera());
			if (ptrPlayerCamera) {

				//m_MyCameraViewを使う
				SetView(m_PlayerCameraView);
				m_CameraSelect = CameraSelect_Stage9::playerCamera;
			}
		}
	}

	void GameStage9::ToGoalCamera() {
		//GoalCameraに変更
		if (m_CameraSelect == CameraSelect_Stage9::myCamera)
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
				m_CameraSelect = CameraSelect_Stage9::goalCamera;
			}
		}
	}

	wstring GameStage9::GetCameraSelectName()
	{
		wstring camName = L"";
		if (m_CameraSelect == CameraSelect_Stage9::openingCamera)
		{
			camName = L"OpeningCamera\n";
		}
		else if (m_CameraSelect == CameraSelect_Stage9::myCamera)
		{
			camName = L"MyCamera\n";
		}
		else if (m_CameraSelect == CameraSelect_Stage9::goalCamera)
		{
			camName = L"GoalCamera\n";
		}
		else if (m_CameraSelect == CameraSelect_Stage9::playerCamera)
		{
			camName = L"PlayerCamera\n";
		}
		return camName;
	}

}
//end basecross
