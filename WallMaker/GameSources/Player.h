/*!
@file Player.h
@brief プレイヤーなど
*/
	
#pragma once
#include "stdafx.h"

namespace basecross{
	// プレイヤー
	class Player : public GameObject
	{
		// プレイヤーが使用するコントローラの入力
		Vec2 GetInputState() const;
		Vec3 GetMoveVector() const;
		//プレイヤーの移動
		void MovePlayer();
		//入力ハンドラー
		InputHandler<Player> m_InputHandler;
		//スピード
		float m_Speed;

		// 大きさ、回転、位置
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;


	public :
		Player(
			const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
		);
		virtual ~Player();
		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		// Aボタン
		void OnPushA();
	};

}
//end basecross

