/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
	//--------------------------------------------------
	/// ゲームタイトルシーン
	//--------------------------------------------------

	void GameStageSelect::CreateViewLight()
	{
		const Vec3 eye(0.0f, 5.0f, -10.0f);
		const Vec3 at(0.0f);
		auto PtrView = CreateView<SingleView>();
		//ビューのカメラの設定
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(Vec3(0.0f, 2.0f, -3.0f));
		PtrCamera->SetAt(Vec3(0.0f, 0.0f, 0.0f));
		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();
	}

	void GameStageSelect::CreateButtonSprite()
	{
		AddGameObject<TitleSprite>(L"GAMESELECT_BG_TX", false, Vec2(1280.0f, 800.0f), Vec2(0.0f, 0.0f));

		auto buttonSprite  = AddGameObject<ButtonSprite>(true, Vec2(100, 100), Vec2(-400, 50.0f), true, 1.0f, L"STAGE_1_TX", 0, 2, Col4(1, 1, 1, 0.5f));
		auto buttonSprite2 = AddGameObject<ButtonSprite>(true, Vec2(100, 100), Vec2(-200, 50.0f), true, 1.0f, L"STAGE_2_TX", 1, 2, Col4(1, 1, 1, 0.5f));
		auto buttonSprite3 = AddGameObject<ButtonSprite>(true, Vec2(100, 100), Vec2(0, 50.0f),    true, 1.0f, L"STAGE_3_TX", 2, 2, Col4(1, 1, 1, 0.5f));
		auto buttonSprite4 = AddGameObject<ButtonSprite>(true, Vec2(100, 100), Vec2(200, 50.0f),  true, 1.0f, L"STAGE_4_TX", 3, 2, Col4(1, 1, 1, 0.5f));
		auto buttonSprite5 = AddGameObject<ButtonSprite>(true, Vec2(100, 100), Vec2(400, 50.0f),  true, 1.0f, L"STAGE_5_TX", 4, 2, Col4(1, 1, 1, 0.5f));

	}

	//	初期化
	void GameStageSelect::OnCreate()
	{
		CreateViewLight();
		//スプライトの作成
		CreateButtonSprite();

		//BGM
		auto ptrXA = App::GetApp()->GetXAudio2Manager();
		m_BGM = ptrXA->Start(WstringKey::SE_GameSelect, 0, 1.0f);
	}

	void GameStageSelect::OnUpdate()
	{
		//コントローラチェックして入力があればコマンド呼び出し
		m_InputHandler.PushHandle(GetThis<GameStageSelect>());
	}

	void GameStageSelect::OnPushA() 
	{
		PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), WstringKey::ToGameStage);

		StopBGM();
	}

	void GameStageSelect::OnPushB()
	{
		PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), WstringKey::ToGameTitle);
		StopBGM();
	}

	void GameStageSelect::StopBGM()
	{
		auto ptrXA = App::GetApp()->GetXAudio2Manager();

		ptrXA->Stop(m_BGM);
	}
}
//end basecross
