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
		void CreateButtonSprite();

		shared_ptr<SoundItem> m_BGM;

	public:
		// 構築と破棄
		GameStageSelect() :Stage() {}
		virtual ~GameStageSelect() {
			StopBGM();
		}

		// 初期化
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		void OnPushDPad(int dPadNum) {};
		void OnHoldRTrigger() {}
		void OnReleaseRTrigger() {}
		void StopBGM();

		//wstring GetSceneName();
	};
}
//end basecross
