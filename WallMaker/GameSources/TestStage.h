/*!
@file GameStage.h
@brief ゲームステージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	enum class CameraSelect_TestStage {
		openingCamera,
		myCamera,
		objCamera,
	};
	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス
	//--------------------------------------------------------------------------------------
	class TestStage : public Stage {

		//OpeningCamera用のビュー
		shared_ptr<SingleView> m_OpeningCameraView;
		//MyCamera用のビュー
		shared_ptr<SingleView> m_MyCameraView;
		CameraSelect_TestStage m_CameraSelect;

		//ステージの奥行
		const int STAGE_LENGTH = 16;
		//ステージの横幅
		const int STAGE_WIDTH = 32;

		shared_ptr<SoundItem> m_BGM;

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

	public:
		//構築と破棄
		TestStage() :Stage() {}
		virtual ~TestStage() {
			StopBGM();
		}

		void DrawStrings();

		//初期化
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		void StopBGM();

		void ToMyCamera();
	};


}
//end basecross

