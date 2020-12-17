/*!
@file GameStage5.cpp
@brief �Q�[���X�e�[�W����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X����
	//--------------------------------------------------------------------------------------
	void GameStage5::CreateViewLight() 
	{
		const Vec3 eye(0.0f, 30.0f, -20.0f);
		const Vec3 at(0.0f);
		//OpeningCameraView�p�̃r���[
		m_OpeningCameraView = ObjectFactory::Create<SingleView>(GetThis<Stage>());
		auto ptrOpeningCamera = ObjectFactory::Create<OpeningCamera>();
		m_OpeningCameraView->SetCamera(ptrOpeningCamera);
		//MyCamera�p�̃r���[
		m_MyCameraView = ObjectFactory::Create<SingleView>(GetThis<Stage>());
		auto PtrCamera = ObjectFactory::Create<MyCamera>();
		PtrCamera->SetEye(eye);
		PtrCamera->SetAt(at);
		m_MyCameraView->SetCamera(PtrCamera);
		//������Ԃł�m_OpeningCameraView���g��
		SetView(m_OpeningCameraView);
		m_CameraSelect = CameraSelect_Stage5::openingCamera;
		//�}���`���C�g�̍쐬
		auto PtrMultiLight = CreateLight<MultiLight>();
		//�f�t�H���g�̃��C�e�B���O���w��
		PtrMultiLight->SetDefaultLighting();
	}

	void GameStage5::CreateWall()
	{
		int mapRows = 16;
		int mapCols = 32;
		
		auto map = new int[mapRows * mapCols];

		const int mapData[] = 
		{
			//1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ,1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			//1,47,48,48,48,48,48,48,48,48,48,48,48,48,49, 1, 1, 1,47,48,48,48,48,48,48,48,48,48,48,48,49, 1,
			//1,44, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,49, 1,47 ,3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3,46, 1,
			//1,44, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0,46, 1,44, 0, 0, 0,42,42,42,42, 0, 0, 0, 0, 0,46, 1,
			//1,41,42,42,42,42,42, 0, 0, 0, 0, 0, 0, 0, 0,46, 1,44, 0, 0,46, 1, 1, 1, 1,41, 0, 0, 0, 0,46, 1,
			//1, 1, 1, 1, 1, 1, 1,44, 0, 0, 0, 0, 0, 0, 0,46, 1,44, 0, 0, 0,48,48,48,49, 1,44, 0, 0, 0,46, 1,
			//1,47,48,48,48,48,48, 0, 0, 0, 0, 0, 0, 0, 0,46, 1,44, 0, 0, 0, 0, 0, 0,46, 1,41, 0, 0, 0,46, 1,
			//1,44, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,46, 1,44, 0, 0, 0, 0, 3, 0, 0,49, 1,44, 0, 0,46, 1,
			//1,44, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,46, 1,41, 0, 0, 0, 0, 0, 0, 0,46, 1,44, 0, 3,46, 1,
			//1,44, 0, 0, 0, 0, 0, 0, 0,42,42,42,42,42,42,43, 1, 1,41,42,42,42, 0, 0, 0,46, 1,44, 0, 0,46, 1,
			//1,44, 0, 0, 0, 0, 0, 0,46, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,44, 0, 0,46, 1,44, 0, 0,46, 1,
			//1,44, 0, 0, 0, 0, 0, 0, 0,48,48,48,48,48,48,48,48,48,48,48,48,48, 0, 0, 0,46, 1,44, 0, 0,46, 1,
			//1,44, 0, 5, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0,46, 1,44, 6, 0,46, 1,
			//1,44, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,46, 1,44, 0, 2,46, 1,
			//1,41,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,43, 1,41,42,42,43, 1,
			//1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1

			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ,1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1,47,48,48,48,49, 1,47,48,48,48,48,48,48,48,48, 1,47,48,48,48,48,48,48,48,49, 1,47,48,48,49, 1,
			1,44, 0, 3, 0,46, 1,44, 0, 0, 0, 0, 0, 0,74,46, 1,44 ,0, 0, 0, 0, 0, 0, 0,46, 1,44,72, 0,46, 1,
			1,44, 0, 0, 0,46, 1,44, 0, 0, 0, 0, 0, 0, 0,46, 1,44, 0, 0, 0, 0,42, 0, 0,46, 1,44, 0, 0,46, 1,
			1,44, 0, 0, 0, 0,48, 0, 0, 0, 0, 0, 0, 0, 0,46, 1,44, 0, 0, 0,46, 1, 8, 8, 8, 1,44, 0, 0,46, 1,
			1,44, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3,46, 1,44, 0, 6, 0,46, 1,44, 0, 0,48, 0, 0, 0,46, 1,
			1,44, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,46, 1,44, 0, 0, 0,46, 1,44, 0, 0, 0, 0, 3, 0,46, 1,
			1,44, 0, 0, 0, 0,42,42, 0, 0, 0, 0, 0, 0,42,43, 1,41,42,42,42,43, 1,41, 0, 0, 0, 0, 0, 0,46, 1,
			1,44, 0, 0, 0,46, 1, 1, 8, 8, 8, 8, 8, 8, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,44, 0, 0, 0, 0, 0,46, 1,
			1,44, 0, 0, 0,46, 1, 1, 8, 8, 8, 8, 8, 8, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,41,42,42, 0, 0, 0,46, 1,
			1,44, 0, 0, 0,46, 1,47, 0, 0, 0, 0, 0,46, 1,47,48,48,48,48,48,48,49, 1, 1, 1, 1,44, 0, 0,46, 1,
			1,44, 0, 0, 0,46, 1,44, 0, 0, 0, 0, 0,46, 1,44,42, 0, 0, 0, 0, 0,46, 1,47,48,48, 0, 0, 0,46, 1,
			1,44, 0, 2, 0,46, 1,44, 0, 0, 0, 0, 0, 0, 0,46, 1,44, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,46, 1,
			1,44, 0, 0, 0,46, 1,44, 3, 0, 0, 0, 0,46, 1,44,48, 0, 0, 0, 0,12,46, 1,44, 0, 0, 0, 0, 0,46, 1,
			1,41,42,42,42,43, 1,41,42,42,42,42,42,43, 1,41,42,42,42,42,42,42,43, 1,41,42,42,42,42,42,43, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
		};

		memcpy(map, mapData, sizeof(int) * mapRows * mapCols);

		// �u���b�N
		for (int r = 0; r < mapRows; r++) {
			for (int c = 0; c < mapCols; c++) {
				auto pos = Vec3((c * 3.0f) - mapCols, 1.0f, -(r * 3.0f) + mapRows);
				auto scale = Vec3(3.0f, 3.0f, 0.5f);
				switch (map[r * mapCols + c]) {
				case 0:
					break;
				case 1: // ���ʂ̕�
					AddGameObject<StageWall>(Vec3(3.0f), Vec3(0.0f), Vec3(pos));
					break;
				case 2: // �v���C���[����
					CreatePlayer(pos);
					AddGameObject<WarpMagicSircle>(Vec3(0.0f), Vec3(0.0f), Vec3(pos.x, 4.0f, pos.z));
					break;
				case 3: // �ʏ�̓G
					AddGameObject<EnemyFirst>(Vec3(2.0f, 1.0f, 3.5f), Vec3(0.0f), Vec3(pos));
					break;
				case 5: // �A�˓I
					AddGameObject<RapidFireEnemy>(Vec3(2.0f, 1.0f, 3.5f), Vec3(0.0f), Vec3(pos.x, 1.5f, pos.z));
					break;
				// ���˕�(�e���L�[�̔z�u�Q��)
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
					AddGameObject<Cannon>(Vec3(2.0f, 1.0f, 3.5f), Vec3(0.0f, XMConvertToRadians(180.0f), 0.0f), Vec3(pos.x, 1.5f, pos.z));
					break;
				case 74:
					AddGameObject<Cannon>(Vec3(2.0f, 1.0f, 3.5f), Vec3(0.0f, XMConvertToRadians(270.0f), 0.0f), Vec3(pos.x, 1.5f, pos.z));
					break;
				case 76:
					AddGameObject<Cannon>(Vec3(2.0f, 1.0f, 3.5f), Vec3(0.0f, XMConvertToRadians(90.0f), 0.0f), Vec3(pos.x, 1.5f, pos.z));
					break;
				case 78:
					AddGameObject<Cannon>(Vec3(2.0f, 1.0f, 3.5f), Vec3(0.0f), Vec3(pos.x, 1.5f, pos.z));
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
			//�r���[�ƃ��C�g�̍쐬
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

		AddGameObject<GameManagement>(Vec3(0.0f), Vec3(0.0f), Vec3(0.0f));

		auto gm = GameManager::GetInstance();
		gm->InitGameManager();
		gm->SetSceneNum(SceneNum::GameStage_5);

		auto multiFire = AddGameObject<MultiFire>();
		SetSharedGameObject(L"MultiFire", multiFire);
		auto multiFireBlue = AddGameObject<MultiFireBlue>();
		SetSharedGameObject(L"MultiFireBlue", multiFireBlue);
		auto breakWallEffect = AddGameObject<WallBreakEffect>();
		SetSharedGameObject(WstringKey::ShareObj_BreakWallEffect, breakWallEffect);

		//BGM
		auto ptrXA = App::GetApp()->GetXAudio2Manager();
		m_BGM = ptrXA->Start(WstringKey::SE_MainBGM, XAUDIO2_LOOP_INFINITE, 0.5f);

		CreateSpriteAndButton();
	}

	void GameStage5::OnUpdate() 
	{
		auto gm = GameManager::GetInstance();

		gm->ClearCheck(GetThis<Stage>());

		if (gm->GetClearFlg() == true && gm->GetClearFlgChanged() == false)
		{
			CreateClearButton();
		}
		else if (gm->GetDeathFlg() == true && gm->GetDeathFlgChanged() == false)
		{
			CreateGameOverButton();
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

	}

	void GameStage5::CreateStage()
	{
		// ��
		float posX = 0.0f;
		float posZ = 0.0f;
		Vec3 stagePos = Vec3(posX, 0, posZ);
		for (int l = 0; l < STAGE_LENGTH / 4; l++) {
			for (int w = 0; w < STAGE_WIDTH / 4; w++) {
				AddGameObject<Floor>(Vec3(12.0f, 1.0f, 12.0f), Vec3(0.0f), Vec3(w * 12 - STAGE_LENGTH - 12.0f, -0.5f, l * 12 - STAGE_WIDTH + 9));
			}
		}
		//���ꖇ�̂�
		//AddGameObject<Floor>(Vec3(32.0f * 3.0f, 1.0f, 16.0f * 3.0f), Vec3(0.0f), Vec3(32.0f * 1.5f - 32.0f - 1.5f, 0.0f, -16.0f * 1.5f + 16.0f + 1.5f));

		CreateWall();

	}

	void GameStage5::CreateEnemy()
	{
		////�G�@
		//AddGameObject<EnemyFirst>(Vec3(2.0f, 1.0f, 3.5f), Vec3(0.0f), Vec3(-5.0f, 1.5f, 0.0f));

		////�����G�i���j
		//AddGameObject<PatrolEnemy>(Vec3(3.0f, 1.0f, 2.0f), Vec3(0.0f, XMConvertToRadians(180), 0.0f),
		//	Vec3(-3.0f, 1.5f, 5.0f));

		////�����G�i�c�j
		//AddGameObject<PatrolEnemyUPDown>(Vec3(3.0f, 1.0f, 2.0f), Vec3(0.0f, XMConvertToRadians(270), 0.0f),
		//	Vec3(10.0f, 1.5f, -5.0f));

		////�A�˂���G
		//AddGameObject<RapidFireEnemy>(Vec3(2.0f, 1.0f, 3.5f), Vec3(0.0f), Vec3(0.0f, 1.5f, -5.0f));

		//�����������G
		//AddGameObject<DangerEnemy>(Vec3(2.0f, 1.0f, 3.5f), Vec3(0.0f), Vec3(-5.0f, 1.5f, -3.0f));

		//��C
		//AddGameObject<Cannon>(Vec3(2.0f, 1.0f, 3.5f), Vec3(0.0f), Vec3(-5.0f, 1.5f, -3.0f));
	}

	void GameStage5::CreatePlayer(Vec3 pos)
	{
		auto player = AddGameObject<Player>(Vec3(1.5f), Vec3(0.0f), Vec3(pos.x, 2.0f, pos.z));
		SetSharedGameObject(WstringKey::ShareObj_Player, player);

	}

	void GameStage5::CreateUI()
	{
		//�v���C���[�̃��C�t�\��
		AddGameObject<PlayerLife>(true, Vec2(100.0f), Vec3(-590.0f, 350.0f, 0.1f), 1.0f);
		AddGameObject<PlayerLife>(true, Vec2(100.0f), Vec3(-490.0f, 350.0f, 0.1f), 2.0f);
		AddGameObject<PlayerLife>(true, Vec2(100.0f), Vec3(-390.0f, 350.0f, 0.1f), 3.0f);
		//�ǂ̃X�g�b�N�\��
		AddGameObject<WallStock>(true, Vec2(100.0f), Vec3(+590.0f, 350.0f, 0.1f), 1.0f);
		AddGameObject<WallStock>(true, Vec2(100.0f), Vec3(+490.0f, 350.0f, 0.1f), 2.0f);
		AddGameObject<WallStock>(true, Vec2(100.0f), Vec3(+390.0f, 350.0f, 0.1f), 3.0f);
	}

	//�J�����}���̍쐬
	void GameStage5::CreateCameraman() 
	{
		auto ptrOpeningCameraman = AddGameObject<OpeningCameraman>();
		//�V�F�A�z���OpeningCameraman��ǉ�
		SetSharedGameObject(L"OpeningCameraman", ptrOpeningCameraman);

		auto ptrOpeningCamera = dynamic_pointer_cast<OpeningCamera>(m_OpeningCameraView->GetCamera());
		if (ptrOpeningCamera) {
			ptrOpeningCamera->SetCameraObject(ptrOpeningCameraman);
			SetView(m_OpeningCameraView);
			m_CameraSelect = CameraSelect_Stage5::openingCamera;
		}

	}

	void GameStage5::CreateClearButton()
	{
		auto gm = GameManager::GetInstance();

		auto whiteSprite = dynamic_pointer_cast<FadeSprite>(WhiteSprite);
		whiteSprite->SetColor(Col4(1.0f, 1.0f, 1.0f, 0.5f));
		whiteSprite->SetFadeFlgChanged(false);
		whiteSprite->SetDrawActive(true);

		gm->SetClearFlgChanged(true);

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

	void GameStage5::ToMyCamera() {
		auto ptrPlayer = GetSharedGameObject<Player>(WstringKey::ShareObj_Player);
		//MyCamera�ɕύX
		auto ptrMyCamera = dynamic_pointer_cast<MyCamera>(m_MyCameraView->GetCamera());
		if (ptrMyCamera) {
			ptrMyCamera->SetTargetObject(ptrPlayer);
			//m_MyCameraView���g��
			SetView(m_MyCameraView);
			m_CameraSelect = CameraSelect_Stage5::myCamera;
		}
	}
}
//end basecross
