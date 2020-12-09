/*!
@file Character.h
@brief キャラク??など
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	// 仮床
	class GameManagement : public GameObject
	{
		// 大きさ、回転、位置
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;

		bool testFlg = false;
		float m_Timer = 0.0f;
		bool m_PlayerMoveFlgChanged = false;

		InputHandler<GameManagement> m_InputHandler;

		void LoadScene(int stageNum);
		void PlayerMoveEnabled();

		void ButtonControl();

		void TitleButton_A();
		void TitleButton_B() {}
		void StageSelectButton_A();
		void StageSelectButton_B();
		void GameStageButton_A();
		void GameStageButton_B() {}


	public:
		// 構築と破棄
		GameManagement(
			const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position);
		virtual ~GameManagement();

		// 初期化
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		virtual void OnUpdate2() override;

		void OnPushA();
		void OnPushB();
		// RT長押し
		void OnHoldRTrigger() {} // 押している間
		void OnReleaseRTrigger() {} // 離している間

		void DrawStrings();
	};
}
//end basecross
