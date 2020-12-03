/*!
@file Character.h
@brief キャラク??など
*/

#pragma once
#include "stdafx.h"

namespace basecross{

	// 仮床
	class GameStageSelect : public Stage
	{
		float delta = 0.0f;

		//ビューの作成
		void CreateViewLight();
		//UIの作成
		void CreateTitleSprite();

		// 入力ハンドラー
		InputHandler<GameStageSelect> m_InputHandler;

	public:
		// 構築と破棄
		GameStageSelect() :Stage() {}
		virtual ~GameStageSelect() {}

		// 初期化
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		void OnPushA();
		void OnPushB() {}
		void OnHoldRTrigger() {}
		void OnReleaseRTrigger() {}
	};
}
//end basecross
