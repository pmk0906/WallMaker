/*!
@file Character.h
@brief キャラク??など
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	// 仮床
	class ManagerObject : public GameObject
	{
		// 大きさ、回転、位置
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;

		bool testFlg = false;

		float m_Timer = 0.0f;

		//プレイヤーが動けるフラグが変わったか
		bool m_PlayerMoveFlgChanged = false;

		InputHandler<ManagerObject> m_InputHandler;

		// シーンを読み込む
		void LoadScene(int stageNum);
		//シーンに入った時のフェードイン
		void EnterScene();
		//シーンから出る時にフェードアウト
		void ExitScene();
		//プレイヤーの行動の許可
		void PlayerMoveEnabled();

		// 十字ボタンの操作
		void ButtonControl();

		//エフェクトをステージに登録する
		void StageEffect();

		//壁を消すフラグ
		bool m_WallDeleteFlg = false;
		bool m_WallDeleteFlgChanged = false;

		//フェードイン・アウト
		void CreateFadeIn(wstring textureKey, Col4 color);
		void CreateFadeOut(wstring textureKey, Col4 color);
		shared_ptr<GameObject> m_FadeSprite;

		//シーン毎のボタンの処理
		void TitleButton_A();
		void TitleButton_B() {}
		void StageSelectButton_A();
		void StageSelectButton_B();
		void GameStageButton_A();
		void GameStageButton_B() {}
		void GameStageButton_Start();


	public:
		// 構築と破棄
		ManagerObject(
			const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position);
		virtual ~ManagerObject();

		// 初期化
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		virtual void OnUpdate2() override;

		void OnPushA();
		void OnPushB();
		void OnPushStart();
		// RT長押し
		void OnHoldRTrigger() {} // 押している間
		void OnReleaseRTrigger() {} // 離している間

		// カメラの変更
		void ChangeCamera();

		void DrawStrings();
	};
}
//end basecross
