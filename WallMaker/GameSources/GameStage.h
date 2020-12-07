/*!
@file GameStage.h
@brief ゲームステージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス
	//--------------------------------------------------------------------------------------
	class GameStage : public Stage {
		//ステージの奥行
		const int STAGE_LENGTH = 16;
		//ステージの横幅
		const int STAGE_WIDTH = 32;

		InputHandler<GameStage> m_InputHandler;

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

	public:
		//構築と破棄
		GameStage() :Stage() {}
		virtual ~GameStage() {
			StopBGM();
		}

		void DrawStrings();

		//初期化
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		void StopBGM();
	};


}
//end basecross

