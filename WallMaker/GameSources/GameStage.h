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
		const int STAGE_LENGTH = 10;
		//ステージの横幅
		const int STAGE_WIDTH = 10;

		//ビューの作成
		void CreateViewLight();
		// ステージの作成
		void CreateStage();
		//敵の作成
		void CreateEnemy();
		//プレイヤーの作成
		void CreatePlayer();
		//UIの作成
		void CreateUI();

	public:
		//構築と破棄
		GameStage() :Stage() {}
		virtual ~GameStage() {}
		//初期化
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};


}
//end basecross

