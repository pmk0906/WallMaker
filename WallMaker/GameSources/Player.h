/*!
@file Player.h
@brief プレイヤーなど
*/
	
#pragma once
#include "stdafx.h"

namespace basecross{
	//--------------------------------------------------
	// プレイヤー
	//--------------------------------------------------
	class Player : public GameObject
	{
		bool m_TestFlg = false;
		int m_ArrivedWall = 0;

		//スピード
		float m_Speed;
		//HP
		float m_PlayerHp = 3.0f;
		// Rトリガーが押されているか
		bool m_BeforePushRTFlg = false;
		bool m_PushRTFlg = false;

		//壁のストック
		const int m_MaxWallStock = 3;
		int m_WallStock = 3;
		bool m_wallDecreaseFlg = false;

		//壁の数を数える
		void SetCountWall();

		//RTriggerについて
		void RTriggerHandler();
		// プレイヤーが使用するコントローラの入力
		Vec2 GetInputState() const;
		Vec2 GetInputStateR() const;
		//方向の取得
		Vec3 GetMoveVector() const;
		Vec3 GetMoveVectorR() const;
		//プレイヤーの移動
		void MovePlayer();
		void MovePlayer2();
		Vec3 forward = Vec3(1, 0, 0);

		// 魔法壁の生成
		void CreateMagicWall();
		//入力ハンドラー
		InputHandler<Player> m_InputHandler;

		// 子オブジェクト
		shared_ptr<GameObject> m_MagicSkeltonWall = nullptr;

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
		virtual void OnUpdate2() override;
		virtual void OnCollisionEnter(shared_ptr<GameObject>& other)override;

		//デバッグ用
		void DrawStrings();

		//RTriggerが押されているかのフラグを取得
		bool GetRTriggerPushFlg();

		Vec3 GetRotation() const;
		Vec3 GetPosition() const;
		//HPの取得
		float GetLife();
		//壁のストックの取得
		int GetWallStock();

		//壁のストックを減らす
		void WallStockDecrease();
		void WallStockDecreaseFlg();

		//Damage関数
		void Damage(float damage);

		//死ぬ
		void Die();

		// ボタン
		void OnPushA();
		void OnPushB();
		// RT長押し
		void OnHoldRTrigger(); // 押している間
		void OnReleaseRTrigger(); // 離している間
	};

	//--------------------------------------------------
	// 魔法壁
	//--------------------------------------------------
	class MagicWall : public GameObject
	{
		float m_Hp = 1.0f;

		// 大きさ、回転、位置
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;

		void Delete();

	public:
		//構築と破棄
		MagicWall(
			const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
		);
		virtual ~MagicWall();
		// 初期化
		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		void SetHp(float hp);
		void Damage(float damage);
	};

	//--------------------------------------------------
	// 魔法壁(固定前)
	//--------------------------------------------------
	class MagicSkeltonWall : public GameObject
	{
		//壁を生成するときに何かと重なっているかのフラグ
		bool m_CollisionFlg = false;
		// 透明な魔法壁の可視、不可視の切り替え
		void SkeltonWallSwitch();

		// 親オブジェクト
		const shared_ptr<GameObject>& m_Parent;

		// 大きさ、回転、位置
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;

	public:
		//構築と破棄
		MagicSkeltonWall(
			const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position,
			const shared_ptr<GameObject>& Parent
		);
		virtual ~MagicSkeltonWall();
		// 初期化
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		virtual void OnUpdate2() override;
		virtual void OnCollisionEnter(shared_ptr<GameObject>& other)override;
		virtual void OnCollisionExcute(shared_ptr<GameObject>& other)override;
		virtual void OnCollisionExit(shared_ptr<GameObject>& other)override;

		void DrawStrings();

		void SetCollisionFlg(bool flg);
		bool GetCollisionFlg();
		Vec3 GetScale() const;
		Vec3 GetRotation() const;
		Vec3 GetPosition() const;

	};

}
//end basecross

