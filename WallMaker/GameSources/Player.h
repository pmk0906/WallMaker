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
		float m_DefaultSpeed = 5.0f;
		float m_HoldSpeed = 3.0f;
		//HP
		float m_PlayerHp = 3.0f;
		//死んだかのフラグ
		bool m_PlayerDiedFlg = false;

		//プレイヤーの透明度
		float m_Alpha = 0.0f;

		// Rトリガーが押されているか
		bool m_BeforePushRTFlg = false;
		bool m_PushRTFlg = false;

		//自身が動いているか
		bool m_MotionChanged = false;
		wstring m_MotionName = L"";

		//壁のストック
		const int m_MaxWallStock = 3;
		int m_WallStock = 3;
		bool m_wallDecreaseFlg = false;
		
		//ゴール時のモーション用フラグ
		bool m_GoalStandFlg = false;
		// ゴール時に回転
		float m_GoalTimer = 0.0f;
		float m_GoalSpinTimer = 2.0f;
		// 死亡時に回転
		float m_DeathTimer = 0.0f;
		float m_DeathSpinTimer = 1.0f;
		//　死亡したあとに倒れる
		float m_FallDownTimer = 0.0f;
		float m_FallDownTimeLimit = 1.0f;
		// 回転時に使用する角度
		float m_RotY;

		//ダメージを受けた時用のタイマー
		float m_InvincibleTime = 0.0f;
		// ダメージ後の無敵時間
		float m_InvincibleTimeLimit = 0.5f;
		// ダメージを受けた時のフラグ
		bool m_DamageFlg = false;
		// ダメージ後の無敵時間
		void InvincibleBehaviour();

		//壁の数を数える
		void SetCountWall();
		//壁を全て消す
		void WallAllDelete();

		//描画切り替え
		float m_DrawActiveLength = 37.0f;
		float m_DrawActiveFloorLength = 45.0f;
		void DrawActiveSwitch();

		// 最初に上に魔法陣が出たら見えるようにする
		void VisiblePlayer();

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
		Vec3 forward = Vec3(1, 0, 0);

		// 魔法壁の生成
		void CreateMagicWall();
		// モーションを登録する
		void MotionSetting();
		//クリア時の動作
		void ClearBehaviour();
		//死亡時の動作
		void GameOverBehaviour();

		// ゴールモーション用フラグ
		bool GoalMotionEndFlg;
		float m_Timer = 0.0f;
		//モーションの更新
		void MotionChange(wstring motionKey);
		void AnimationUpdate();
		//ゴール時にカメラを向く
		void LookCamera();



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
		bool GetPlayerDiedFlg();
		void SetPlayerDiedFlg(bool diedFlg);

		//壁のストックの取得
		int GetWallStock();

		//壁のストックを減らす
		void WallStockDecrease();
		void WallStockDecreaseFlg();
		//全ての壁を消す
		void AllWallDelete();

		//モーションの名前を登録
		void SetMotionName(wstring motionName);
		wstring GetMotionName();

		//Damage関数
		void Damage(float damage);

		//死ぬ
		void Die();
		//BGMを止める
		void StopBGM();

		// ボタン
		void OnPushA();
		void OnPushB();
		void OnPushStart() {}
		// RT長押し
		void OnHoldRTrigger(); // 押している間
		void OnReleaseRTrigger(); // 離している間
		bool GetRTriggerFlg();
		void SetRTriggerFlg(bool triggerFlg);
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
		
		bool m_CollisionFlg = false;

		void Delete();

		void GenerateEffect(int GenerateNum, Vec3 MoveSpeed);

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
		virtual void OnCollisionEnter(shared_ptr<GameObject>& other)override;
		virtual void OnCollisionExcute(shared_ptr<GameObject>& other)override;
		virtual void OnCollisionExit(shared_ptr<GameObject>& other)override;

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
		void ChangeColor();

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

