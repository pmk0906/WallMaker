/*!
@file GameStage10.h
@brief ゲームステージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	enum class CameraSelect_Stage10 {
		playerCamera,
		openingCamera,
		myCamera,
		goalCamera,
	};

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス
	//--------------------------------------------------------------------------------------
	class GameStage10 : public Stage {

		//PlayerCamera用のビュー
		shared_ptr<SingleView> m_PlayerCameraView;
		//OpeningCamera用のビュー
		shared_ptr<SingleView> m_OpeningCameraView;
		//MyCamera用のビュー
		shared_ptr<SingleView> m_MyCameraView;
		//GoalCamera用のビュー
		shared_ptr<SingleView> m_GoalCameraView;
		CameraSelect_Stage10 m_CameraSelect;

		//ステージの奥行
		const int STAGE_LENGTH = 28;
		//ステージの横幅
		const int STAGE_WIDTH = 20;

		InputHandler<GameStage10> m_InputHandler;

		shared_ptr<SoundItem> m_BGM;

		shared_ptr<GameObject> WhiteSprite = nullptr;
		shared_ptr<GameObject> ResultSprite = nullptr;
		shared_ptr<GameObject> m_Button1 = nullptr;
		shared_ptr<GameObject> m_Button2 = nullptr;
		shared_ptr<GameObject> m_Button3 = nullptr;

		//ビューの作成
		void CreateViewLight();
		// ステージの作成
		void CreateStage();
		void CreateWall();
		//敵の作成
		void CreateEnemy();
		//プレイヤーの作成
		void CreatePlayer(Vec3 pos);
		//UIの作成
		void CreateUI();
		//カメラマンの作成
		void CreateCameraman();

		//ボタンの作成・削除
		void CreateClearButton();
		void CreateGameOverButton();
		void CreateSpriteAndButton();
		void SwitchPoseButton(bool poseFlg);


	public:
		//構築と破棄
		GameStage10() :Stage() {}
		virtual ~GameStage10() {
			StopBGM();
		}

		//初期化
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		virtual void OnUpdate2() override;
		void DrawStrings();

		void StopBGM();


		void ToMyCamera();
		void ToPlayerCamera();
		void ToGoalCamera();

		void ChangeBGM(wstring bgmKey);
		wstring m_BgmName = L"";
		void SetBgmName(wstring bgmName);
		wstring GetBgmName();

		wstring GetCameraSelectName();

	};


}
//end basecross

