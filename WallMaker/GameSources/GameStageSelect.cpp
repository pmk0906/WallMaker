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

	void GameStageSelect::CreateTitleSprite()
	{
		AddGameObject<TitleSprite>(L"MAGICWALL_TX", false,
			Vec2(1280.0f, 800.0f), Vec2(0.0f, 0.0f));
	}

	//	初期化
	void GameStageSelect::OnCreate()
	{
		CreateViewLight();
		//スプライトの作成
		CreateTitleSprite();
	}

	void GameStageSelect::OnUpdate()
	{
		//コントローラチェックして入力があればコマンド呼び出し
		m_InputHandler.PushHandle(GetThis<GameStageSelect>());

		//コントローラの取得
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].bConnected) {
			//Bボタン
			if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B) {
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), WstringKey::ToGameStage);
			}
		}

	}

	void GameStageSelect::OnPushA() 
	{
		PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), WstringKey::ToGameStage);
	}
}
//end basecross
