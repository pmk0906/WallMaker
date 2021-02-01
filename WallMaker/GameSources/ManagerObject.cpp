/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
	///--------------------------------------------------
	/// GameManagement
	///--------------------------------------------------
	GameManagement::GameManagement(
		const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position)
	{}
	GameManagement::~GameManagement() {}

	//シーンを読み込む
	void GameManagement::LoadScene(int stageNum)
	{
		auto gm = GameManager::GetInstance();

		wstring sceneKey;
		switch (stageNum)
		{
		case (int)SceneNum::Title:
			sceneKey = WstringKey::ToGameTitle;
			gm->SetSceneNum(SceneNum::Title);
			break;
		case (int)SceneNum::StageSelect:
			sceneKey = WstringKey::ToGameStageSelect;
			gm->SetSceneNum(SceneNum::StageSelect);
			break;
		case (int)SceneNum::GameStage_1:
			sceneKey = WstringKey::ToGameStage1;
			gm->SetSceneNum(SceneNum::GameStage_1);
			break;
		case SceneNum::GameStage_2:
			sceneKey = WstringKey::ToGameStage2;
			gm->SetSceneNum(SceneNum::GameStage_2);
			break;
		case SceneNum::GameStage_3:
			sceneKey = WstringKey::ToGameStage3;
			gm->SetSceneNum(SceneNum::GameStage_3);
			break;
		case SceneNum::GameStage_4:
			sceneKey = WstringKey::ToGameStage4;
			gm->SetSceneNum(SceneNum::GameStage_4);
			break;
		case SceneNum::GameStage_5:
			sceneKey = WstringKey::ToGameStage5;
			gm->SetSceneNum(SceneNum::GameStage_5);
			break;
		case SceneNum::GameStage_6:
			sceneKey = WstringKey::ToGameStage6;
			gm->SetSceneNum(SceneNum::GameStage_6);
			break;
		case SceneNum::GameStage_7:
			sceneKey = WstringKey::ToGameStage7;
			gm->SetSceneNum(SceneNum::GameStage_7);
			break;
		case SceneNum::GameStage_8:
			sceneKey = WstringKey::ToGameStage8;
			gm->SetSceneNum(SceneNum::GameStage_8);
			break;
		case SceneNum::GameStage_9:
			sceneKey = WstringKey::ToGameStage9;
			gm->SetSceneNum(SceneNum::GameStage_9);
			break;
		case SceneNum::GameStage_10:
			sceneKey = WstringKey::ToGameStage10;
			gm->SetSceneNum(SceneNum::GameStage_10);
			break;
		case SceneNum::GameStage_Test:
			sceneKey = WstringKey::ToGameTestStage;
			gm->SetSceneNum(SceneNum::GameStage_Test);
			break;
		}
		PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), sceneKey);

	}

	//シーンに入った時のフェードイン
	void GameManagement::EnterScene()
	{
		auto gm = GameManager::GetInstance();

		wstring sceneKey;
		switch (gm->GetSceneNum())
		{
		case SceneNum::Title:
		case SceneNum::StageSelect:
		case SceneNum::GameStage_1:
		case SceneNum::GameStage_2:
		case SceneNum::GameStage_3:
		case SceneNum::GameStage_4:
		case SceneNum::GameStage_5:
		case SceneNum::GameStage_6:
		case SceneNum::GameStage_7:
		case SceneNum::GameStage_8:
		case SceneNum::GameStage_9:
		case SceneNum::GameStage_10:
		case SceneNum::GameStage_Test:
			CreateFadeIn(L"WHITE_TX", Col4(1.0f, 1.0f, 1.0f, 1.0f));
			break;
		default:
			break;
		}
	}

	//シーンを読み込む
	void GameManagement::ExitScene()
	{
		auto gm = GameManager::GetInstance();

		wstring sceneKey;
		switch (gm->GetSceneNum())
		{
		case SceneNum::Title:
		case SceneNum::StageSelect:
		case SceneNum::GameStage_1:
		case SceneNum::GameStage_2:
		case SceneNum::GameStage_3:
		case SceneNum::GameStage_4:
		case SceneNum::GameStage_5:
		case SceneNum::GameStage_6:
		case SceneNum::GameStage_7:
		case SceneNum::GameStage_8:
		case SceneNum::GameStage_9:
		case SceneNum::GameStage_10:
		case SceneNum::GameStage_Test:
			CreateFadeOut(L"WHITE_TX", Col4(1.0f, 1.0f, 1.0f, 0.0f));
			break;
		default:
			break;
		}
	}

	void GameManagement::PlayerMoveEnabled()
	{
		auto gm = GameManager::GetInstance();
		if (gm->GetOpeningCameraMoveEnd())
		{
			if(gm->GetMagicSircleMoved() == true)
			{
				if (m_PlayerMoveFlgChanged == false)
				{
					gm->SetMoveEnabledFlg(true);
					m_PlayerMoveFlgChanged = true;
				}
			}
		}
		else
		{
			//auto delta = App::GetApp()->GetElapsedTime();
			//m_Timer += delta;
		}
	}

	void GameManagement::ClearCheck()
	{
		//auto gm = GameManager::GetInstance();
		//if (gm->GetClearFlg() == true && gm->GetClearFlgChanged() == false)
		//{
		//	ChangeCamera();
		//	gm->SetClearFlgChanged(true);
		//}
	}

	void GameManagement::ButtonControl()
	{
		m_InputHandler.PushHandle(GetThis<GameManagement>());
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		WORD wButtons = 0;
		if (cntlVec[0].bConnected) {
			wButtons = cntlVec[0].wPressedButtons;
		}
		auto gm = GameManager::GetInstance();
		switch (gm->GetSceneNum())
		{
		case SceneNum::StageSelect:
		//Dパッド左
			if (wButtons & XINPUT_GAMEPAD_DPAD_LEFT) {
				if (gm->GetSelectingButtonNum() > 0)
				{
					auto ptrXA = App::GetApp()->GetXAudio2Manager();
					ptrXA->Start(WstringKey::SE_Cursol, 0, 1.0f);

					gm->SetSelectingButtonMinus();
					testFlg = true;
				}
			}
			//Dパッド右
			if (wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) {
				if (gm->GetSelectingButtonNum() < gm->GetMaxButtonNum())
				{
					auto ptrXA = App::GetApp()->GetXAudio2Manager();
					ptrXA->Start(WstringKey::SE_Cursol, 0, 1.0f);

					gm->SetSelectingButtonPlus();
					testFlg = false;
				}
			}
			//Dパッド上
			if (wButtons & XINPUT_GAMEPAD_DPAD_UP) {
				if (4 < gm->GetSelectingButtonNum())
				{
					auto ptrXA = App::GetApp()->GetXAudio2Manager();
					ptrXA->Start(WstringKey::SE_Cursol, 0, 1.0f);

					gm->SetSelectingButtonMinus_5();
				}
			}
			//Dパッド下
			if (wButtons & XINPUT_GAMEPAD_DPAD_DOWN) {
				if (gm->GetSelectingButtonNum() < 5)
				{
					auto ptrXA = App::GetApp()->GetXAudio2Manager();
					ptrXA->Start(WstringKey::SE_Cursol, 0, 1.0f);

					gm->SetSelectingButtonPlus_5();
				}
			}
			break;
		case SceneNum::GameStage_1:
		case SceneNum::GameStage_2:
		case SceneNum::GameStage_3:
		case SceneNum::GameStage_4:
		case SceneNum::GameStage_5:
		case SceneNum::GameStage_6:
		case SceneNum::GameStage_7:
		case SceneNum::GameStage_8:
		case SceneNum::GameStage_9:
		case SceneNum::GameStage_10:
		case SceneNum::GameStage_Test:
			//Dパッド上
			if (wButtons & XINPUT_GAMEPAD_DPAD_UP) {
				if (gm->GetSelectingButtonNum() > 0)
				{
					auto ptrXA = App::GetApp()->GetXAudio2Manager();
					ptrXA->Start(WstringKey::SE_Cursol, 0, 1.0f);

					gm->SetSelectingButtonMinus();
					testFlg = true;
				}
			}
			//Dパッド下
			if (wButtons & XINPUT_GAMEPAD_DPAD_DOWN) {
				if (gm->GetSelectingButtonNum() < gm->GetMaxButtonNum())
				{
					auto ptrXA = App::GetApp()->GetXAudio2Manager();
					ptrXA->Start(WstringKey::SE_Cursol, 0, 1.0f);

					gm->SetSelectingButtonPlus();
					testFlg = false;
				}
			}
			break;
		default:
			break;
		}
	}

	void GameManagement::ChangeCamera()
	{
		auto gm = GameManager::GetInstance();
		int stageNum = gm->GetSceneNum();

		if (stageNum == SceneNum::GameStage_1)
		{
			auto ptrGameGtage = GetTypeStage<GameStage>();
			ptrGameGtage->ToPlayerCamera();
		}
		else if (stageNum == SceneNum::GameStage_2)
		{
			auto ptrGameGtage = GetTypeStage<GameStage2>();
			ptrGameGtage->ToPlayerCamera();
		}
		else if (stageNum == SceneNum::GameStage_3)
		{
			auto ptrGameGtage = GetTypeStage<GameStage3>();
			ptrGameGtage->ToPlayerCamera();
		}
		else if (stageNum == SceneNum::GameStage_4)
		{
			auto ptrGameGtage = GetTypeStage<GameStage4>();
			ptrGameGtage->ToPlayerCamera();
		}
		else if (stageNum == SceneNum::GameStage_5)
		{
			auto ptrGameGtage = GetTypeStage<GameStage5>();
			ptrGameGtage->ToPlayerCamera();
		}
		else if (stageNum == SceneNum::GameStage_6)
		{
			auto ptrGameGtage = GetTypeStage<GameStage6>();
			ptrGameGtage->ToPlayerCamera();
		}
		else if (stageNum == SceneNum::GameStage_7)
		{
			auto ptrGameGtage = GetTypeStage<GameStage7>();
			ptrGameGtage->ToPlayerCamera();
		}
		else if (stageNum == SceneNum::GameStage_8)
		{
			auto ptrGameGtage = GetTypeStage<GameStage8>();
			ptrGameGtage->ToPlayerCamera();
		}
		else if (stageNum == SceneNum::GameStage_9)
		{
			auto ptrGameGtage = GetTypeStage<GameStage9>();
			ptrGameGtage->ToPlayerCamera();
		}
		else if (stageNum == SceneNum::GameStage_10)
		{
			auto ptrGameGtage = GetTypeStage<GameStage10>();
			ptrGameGtage->ToPlayerCamera();
		}
		else if (stageNum == SceneNum::GameStage_Test)
		{
			auto ptrGameGtage = GetTypeStage<TestStage>();
			ptrGameGtage->ToPlayerCamera();
		}
	}

	void GameManagement::StageEffect()
	{
		auto multiFire = GetStage()->AddGameObject<MultiFire>();
		GetStage()->SetSharedGameObject(L"MultiFire", multiFire);
		auto multiFireBlue = GetStage()->AddGameObject<MultiFireBlue>();
		GetStage()->SetSharedGameObject(L"MultiFireBlue", multiFireBlue);
		auto redFire = GetStage()->AddGameObject<RedFire>();
		GetStage()->SetSharedGameObject(WstringKey::ShareObj_RedFire, redFire);
		auto orangeFire = GetStage()->AddGameObject<OrangeFire>();
		GetStage()->SetSharedGameObject(WstringKey::ShareObj_OrangeFire, orangeFire);
		auto yellowFire = GetStage()->AddGameObject<YellowFire>();
		GetStage()->SetSharedGameObject(WstringKey::ShareObj_YellowFire, yellowFire);
		auto greenFire = GetStage()->AddGameObject<GreenFire>();
		GetStage()->SetSharedGameObject(WstringKey::ShareObj_GreenFire, greenFire);
		auto blueFire = GetStage()->AddGameObject<BlueFire>();
		GetStage()->SetSharedGameObject(WstringKey::ShareObj_BlueFire, blueFire);
		auto blackFire = GetStage()->AddGameObject<BlackFire>();
		GetStage()->SetSharedGameObject(WstringKey::ShareObj_BlackFire, blackFire);
		auto breakWallEffect = GetStage()->AddGameObject<WallBreakEffect>();
		GetStage()->SetSharedGameObject(WstringKey::ShareObj_BreakWallEffect, breakWallEffect);
		auto reflectEffect = GetStage()->AddGameObject<ReflectBulletEffect>();
		GetStage()->SetSharedGameObject(WstringKey::ShareObj_ReflectBulletEffect, reflectEffect);
	}

	void GameManagement::CreateFadeIn(wstring textureKey, Col4 color)
	{
		auto fadeSprite = GetStage()->AddGameObject<FadeSprite>(true, Vec2(1280, 800), Vec2(0, 0), false, 0.0f, 1.0f, textureKey, 3, color);
		fadeSprite->SetFadeFlgChanged(false);
	}
	void GameManagement::CreateFadeOut(wstring textureKey, Col4 color)
	{
		auto fadeSprite = GetStage()->AddGameObject<FadeSprite>(true, Vec2(1280, 800), Vec2(0, 0), true, 1.0f, 0.0f, textureKey, 3, color);
		fadeSprite->SetFadeFlgChanged(false);
	}

	void GameManagement::TitleButton_A()
	{
		auto gm = GameManager::GetInstance();
		if (gm->GetFadeFlgChanged() == true)
		{
			auto ptrXA = App::GetApp()->GetXAudio2Manager();
			ptrXA->Start(WstringKey::SE_Enter, 0, 1.0f);

			gm->SetLoadSceneNum(SceneNum::StageSelect);
			gm->SetFadeFlgChanged(false);
			ExitScene();

		}
	}

	//ステージセレクト中のボタン
	void GameManagement::StageSelectButton_A()
	{
		auto gm = GameManager::GetInstance();
		if (gm->GetFadeFlgChanged() == true)
		{
			auto selectingButtonNum = gm->GetSelectingButtonNum();
			switch (selectingButtonNum)
			{
			case 0:
				gm->SetLoadSceneNum(SceneNum::GameStage_1);
				break;
			case 1:
				gm->SetLoadSceneNum(SceneNum::GameStage_2);
				break;
			case 2:
				gm->SetLoadSceneNum(SceneNum::GameStage_3);
				break;
			case 3:
				gm->SetLoadSceneNum(SceneNum::GameStage_4);
				break;
			case 4:
				gm->SetLoadSceneNum(SceneNum::GameStage_5);
				break;
			case 5:
				gm->SetLoadSceneNum(SceneNum::GameStage_6);
				break;
			case 6:
				gm->SetLoadSceneNum(SceneNum::GameStage_7);
				break;
			case 7:
				gm->SetLoadSceneNum(SceneNum::GameStage_8);
				break;
			case 8:
				gm->SetLoadSceneNum(SceneNum::GameStage_9);
				break;
			case 9:
				gm->SetLoadSceneNum(SceneNum::GameStage_10);
				break;
			default:
				break;
			}

			auto ptrXA = App::GetApp()->GetXAudio2Manager();
			ptrXA->Start(WstringKey::SE_Enter, 0, 1.0f);

			gm->SetFadeFlgChanged(false);
			ExitScene();
		}
	}
	void GameManagement::StageSelectButton_B()
	{
		auto gm = GameManager::GetInstance();
		//LoadScene(SceneNum::Title);
		if (gm->GetFadeFlgChanged() == true)
		{
			auto ptrXA = App::GetApp()->GetXAudio2Manager();
			ptrXA->Start(WstringKey::SE_Cancel, 0, 1.0f);

			gm->SetLoadSceneNum(SceneNum::Title);
			gm->SetFadeFlgChanged(false);
			ExitScene();

		}
	}

	//ゲームステージ内でのボタン
	void GameManagement::GameStageButton_A()
	{
		auto gm = GameManager::GetInstance();
		if (gm->GetPoseFlg() == true)
		{
			if (gm->GetFadeFlgChanged() == true)
			{
				switch (gm->GetSelectingButtonNum())
				{
				case 0: // リトライ
					//LoadScene(gm->GetSceneNum());
					gm->SetLoadSceneNum(gm->GetSceneNum());
					gm->SetFadeFlgChanged(false);
					ExitScene();
					break;
				case 1:	// ステージセレクト
					//LoadScene((int)SceneNum::StageSelect);
					gm->SetLoadSceneNum(SceneNum::StageSelect);
					gm->SetFadeFlgChanged(false);
					ExitScene();
					break;
				case 2: // ゲームに戻る
					gm->SetPoseFlg(false);
					gm->SetPoseFlgChanged(false);
					break;
				default:
					break;
				}

				auto ptrXA = App::GetApp()->GetXAudio2Manager();
				ptrXA->Start(WstringKey::SE_Enter, 0, 1.0f);
			}
		}
		//クリアした場合
		if (gm->GetClearFlgChanged() == true)
		{
			if (gm->GetFadeFlgChanged() == true)
			{
				switch (gm->GetSelectingButtonNum())
				{
				case 0: // 次のステージへ
					if (gm->GetNextSceneNum() == SceneNum::End)
					{
						//LoadScene(SceneNum::StageSelect);
						gm->SetLoadSceneNum(SceneNum::StageSelect);
					}
					else
					{
						//LoadScene(gm->GetNextSceneNum());
						gm->SetLoadSceneNum(gm->GetNextSceneNum());
					}
					break;
				case 1: // ステージセレクトへ
					//LoadScene((int)SceneNum::StageSelect);
					gm->SetLoadSceneNum(SceneNum::StageSelect);
					break;
				default:
					break;
				}

				auto ptrXA = App::GetApp()->GetXAudio2Manager();
				ptrXA->Start(WstringKey::SE_Enter, 0, 1.0f);

				gm->SetFadeFlgChanged(false);
				ExitScene();
			}
		}
		//ゲームオーバーになった場合
		if (gm->GetDeathFlgChanged() == true)
		{
			if (gm->GetFadeFlgChanged() == true)
			{
				switch (gm->GetSelectingButtonNum())
				{
				case 0: // リトライ
					//LoadScene(gm->GetSceneNum());
					gm->SetLoadSceneNum(gm->GetSceneNum());
					break;
				case 1: // ステージセレクトへ
					//LoadScene((int)SceneNum::StageSelect);
					gm->SetLoadSceneNum(SceneNum::StageSelect);
					break;
				default:
					break;
				}
				auto ptrXA = App::GetApp()->GetXAudio2Manager();
				ptrXA->Start(WstringKey::SE_Enter, 0, 1.0f);

				gm->SetFadeFlgChanged(false);
				ExitScene();
			}
		}
		//カメラの移動が終わってない場合
		if (gm->GetOpeningCameraMoveEnd() == false)
		{
			auto gm = GameManager::GetInstance();
			ChangeCamera();
			gm->SetOpeningCameraMoveEnd(true);
		}
	}

	void GameManagement::GameStageButton_Start()
	{
		auto gm = GameManager::GetInstance();
		if (gm->GetPoseFlgChanged() == true)
		{
			if (gm->GetPoseFlg() == true)
			{
				gm->SetPoseFlg(false);
				gm->SetPoseFlgChanged(false);
			}
			else
			{
				gm->SetPoseFlg(true);
				gm->SetPoseFlgChanged(false);
			}
		}
	}

	//	初期化
	void GameManagement::OnCreate()
	{
		// 大きさ、回転、位置
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale);
		ptrTrans->SetRotation(m_Rotation);
		ptrTrans->SetPosition(m_Position);

		StageEffect();
		EnterScene();

		// DrawString用
		//auto strComp = AddComponent<StringSprite>();
		//strComp->SetBackColor(Col4(0, 0, 0, 0.5f));
		//strComp->SetTextRect(Rect2D<float>(50, 150, 400, 600));
	}

	void GameManagement::OnUpdate()
	{
		auto gm = GameManager::GetInstance();

		ButtonControl();
		PlayerMoveEnabled();

		if (gm->GetFadeFlgChanged() == false)
		{
			if (1.0f < m_Timer)
			{
				LoadScene(gm->GetLoadSceneNum());
			}
			else
			{
				auto delta = App::GetApp()->GetElapsedTime();
				m_Timer += delta;
			}
		}
	}

	void GameManagement::OnUpdate2()
	{
		//DrawStrings();
	}

	void GameManagement::DrawStrings()
	{
		auto gm = GameManager::GetInstance();

		wstring selectingButton(L"選択しているボタンの番号 : ");
		selectingButton += Util::UintToWStr(gm->GetSelectingButtonNum()) + L"\n";

		wstring maxButtonNum(L"現在のボタンの最大番号 : ");
		maxButtonNum += Util::UintToWStr(gm->GetMaxButtonNum()) + L"\n";

		wstring sceneNum(L"現在のシーン : ");
		switch (gm->GetSceneNum())
		{
		case (int)SceneNum::Title:
			sceneNum += L"タイトル\n";
			break;
		case (int)SceneNum::StageSelect:
			sceneNum += L"ステージセレクト\n";
			break;
		case (int)SceneNum::GameStage_1:
			sceneNum += L"ゲームステージ１\n";
			break;
		case (int)SceneNum::GameStage_2:
			sceneNum += L"ゲームステージ２\n";
			break;
		case (int)SceneNum::GameStage_3:
			sceneNum += L"ゲームステージ３\n";
			break;
		case (int)SceneNum::GameStage_4:
			sceneNum += L"ゲームステージ４\n";
			break;
		case (int)SceneNum::GameStage_5:
			sceneNum += L"ゲームステージ５\n";
			break;
		case (int)SceneNum::GameStage_6:
			sceneNum += L"ゲームステージ６\n";
			break;
		case (int)SceneNum::GameStage_Test:
			sceneNum += L"テストステージ\n";
			break;
		default:
			break;
		}

		wstring timer(L"m_Timer : ");
		timer += Util::FloatToWStr(m_Timer) + L"\nGetPlayerMoveTime : " + Util::FloatToWStr(gm->GetPlayerMoveTime()) + L"\n";

		wstring pose(L"ポーズフラグ : ");
		if (gm->GetPoseFlg() == true)
		{
			pose += L"true\n";
		}
		else
		{
			pose += L"false\n";
		}

		wstring camName = L"現在のカメラの名前：";
		switch (gm->GetSceneNum())
		{
		case (int)SceneNum::GameStage_1:
		case (int)SceneNum::GameStage_2:
		case (int)SceneNum::GameStage_3:
		case (int)SceneNum::GameStage_4:
		case (int)SceneNum::GameStage_5:
		case (int)SceneNum::GameStage_6:
		case (int)SceneNum::GameStage_7:
		case (int)SceneNum::GameStage_8:
		case (int)SceneNum::GameStage_9:
		case (int)SceneNum::GameStage_10:
			camName += gm->GetCameraName();
			break;
		default:
			camName += L"なし\n";
			break;
		}

		wstring playerCamState = L"PlayerCamera_State：";
		switch (gm->GetSceneNum())
		{
		case (int)SceneNum::GameStage_1:
		case (int)SceneNum::GameStage_2:
		case (int)SceneNum::GameStage_3:
		case (int)SceneNum::GameStage_4:
		case (int)SceneNum::GameStage_5:
		case (int)SceneNum::GameStage_6:
		case (int)SceneNum::GameStage_7:
		case (int)SceneNum::GameStage_8:
		case (int)SceneNum::GameStage_9:
		case (int)SceneNum::GameStage_10:
			playerCamState += gm->GetPlayerCameraStateName();
			break;
		default:
			playerCamState += L"なし\n";
			break;
		}

		wstring testFLG(L"テストフラグ : ");
		if (gm->GetTestFlg() == true)
		{
			testFLG += L"true\n";
		}
		else
		{
			testFLG += L"false\n";
		}

		wstring testText(L"テストテキスト\n");
		testText += gm->GetTestText();


		wstring str = selectingButton + maxButtonNum + sceneNum + timer + pose + camName + playerCamState + L"\n" + testFLG + testText+ L"\n";
		auto ptrString = GetComponent<StringSprite>();
		ptrString->SetText(str);
	}

	void GameManagement::OnPushA()
	{
		auto gm = GameManager::GetInstance();
		switch (gm->GetSceneNum())
		{
		case (int)SceneNum::Title:
			TitleButton_A();
			break;
		case (int)SceneNum::StageSelect:
			StageSelectButton_A();
			break;
		case (int)SceneNum::GameStage_1:
		case (int)SceneNum::GameStage_2:
		case (int)SceneNum::GameStage_3:
		case (int)SceneNum::GameStage_4:
		case (int)SceneNum::GameStage_5:
		case (int)SceneNum::GameStage_6:
		case (int)SceneNum::GameStage_7:
		case (int)SceneNum::GameStage_8:
		case (int)SceneNum::GameStage_9:
		case (int)SceneNum::GameStage_10:
		case(int)SceneNum::GameStage_Test:
			GameStageButton_A();
			break;
		default:
			break;
		}
	}

	void GameManagement::OnPushB()
	{
		auto gm = GameManager::GetInstance();
		switch (gm->GetSceneNum())
		{
		case (int)SceneNum::Title:
			TitleButton_B();
			break;
		case (int)SceneNum::StageSelect:
			StageSelectButton_B();
			break;
		case (int)SceneNum::GameStage_1:
		case (int)SceneNum::GameStage_2:
		case (int)SceneNum::GameStage_3:
		case (int)SceneNum::GameStage_4:
		case (int)SceneNum::GameStage_5:
		case (int)SceneNum::GameStage_6:
		case (int)SceneNum::GameStage_7:
		case (int)SceneNum::GameStage_8:
		case (int)SceneNum::GameStage_9:
		case (int)SceneNum::GameStage_10:
			GameStageButton_B();
			break;
		default:
			break;
		}
	}

	void GameManagement::OnPushStart()
	{
		auto gm = GameManager::GetInstance();
		switch (gm->GetSceneNum())
		{
		case (int)SceneNum::Title:
			LoadScene((int)SceneNum::GameStage_Test);
			break;
		case (int)SceneNum::GameStage_1:
		case (int)SceneNum::GameStage_2:
		case (int)SceneNum::GameStage_3:
		case (int)SceneNum::GameStage_4:
		case (int)SceneNum::GameStage_5:
		case (int)SceneNum::GameStage_6:
		case (int)SceneNum::GameStage_7:
		case (int)SceneNum::GameStage_8:
		case (int)SceneNum::GameStage_9:
		case (int)SceneNum::GameStage_10:
			GameStageButton_Start();
			break;
		default:
			break;
		}
	}
}
//end basecross
