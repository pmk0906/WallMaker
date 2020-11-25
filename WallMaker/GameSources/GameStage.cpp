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
	void GameStage::CreateViewLight() {
		const Vec3 eye(0.0f, 30.0f, -20.0f);
		const Vec3 at(0.0f);
		auto PtrView = CreateView<SingleView>();
		//ビューのカメラの設定
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);
		PtrCamera->SetAt(at);
		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();
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
		CreatePlayer();
		CreateUI();
	}

	void GameStage::OnUpdate() 
	{

	}

	void GameStage::CreateStage()
	{
		// 床
		//AddGameObject<FixedBox>(Vec3(100.0f, 1.0f, 50.0f), Vec3(0.0f), Vec3(0.0f, -0.5f, 0.0f));
		int posX = 0;
		int posZ = 0;
		Vec3 stagePos = Vec3(posX, 0, posZ);
		for (int l = 0; l < STAGE_LENGTH; l++) {
			for (int w = 0; w < STAGE_WIDTH; w++) {
				AddGameObject<Floor>(Vec3(4.0f, 1.0f, 4.0f), Vec3(0.0f), Vec3(w * 4 - STAGE_LENGTH * 2 , 0, l * 4 - STAGE_WIDTH * 2));
			}
		}
	}

	void GameStage::CreateEnemy()
	{
		//敵①
		AddGameObject<EnemyFirst>(Vec3(2.0f, 1.0f, 3.5f), Vec3(0.0f), Vec3(-5.0f, 1.5f, 0.0f));

		//往復敵（横）
		AddGameObject<PatrolEnemy>(Vec3(3.0f, 1.0f, 2.0f), Vec3(0.0f, XMConvertToRadians(180), 0.0f),
			Vec3(-3.0f, 1.5f, 5.0f));

		//往復敵（縦）
		AddGameObject<PatrolEnemyUPDown>(Vec3(3.0f, 1.0f, 2.0f), Vec3(0.0f, XMConvertToRadians(270), 0.0f),
			Vec3(10.0f, 1.5f, -5.0f));

		//連射する敵
		AddGameObject<RapidFireEnemy>(Vec3(2.0f, 1.0f, 3.5f), Vec3(0.0f), Vec3(0.0f, 1.5f, -5.0f));

	}

	void GameStage::CreatePlayer()
	{
		auto player = AddGameObject<Player>(Vec3(1.0f), Vec3(0.0f), Vec3(0.0f, 2.0f, 0.0f));
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
		AddGameObject<WallStock>(true, Vec2(100.0f), Vec3(-590.0f, 250.0f, 0.1f), 1.0f);
		AddGameObject<WallStock>(true, Vec2(100.0f), Vec3(-490.0f, 250.0f, 0.1f), 2.0f);
		AddGameObject<WallStock>(true, Vec2(100.0f), Vec3(-390.0f, 250.0f, 0.1f), 3.0f);
	}
}
//end basecross
