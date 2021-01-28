/*!
@file Character.h
@brief キャラク??など
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	enum PlayerCamStateNum
	{
		ToTreasureState,
		ToStartPointState,
		MoveToPlayerState,
		ZoomState,
		EndState
	};
	enum GoalCamStateNum
	{
		MoveStartState,
		MovingState,
		MoveEndState
	};

	//--------------------------------------------------------------------------------------
	//　Myカメラ
	//--------------------------------------------------------------------------------------
	class MyCameraman : public GameObject
	{
		Vec3 offset = Vec3(0.0f, 40.0f, -7.0f);

	public:
		//構築と破棄
		MyCameraman(const shared_ptr<Stage>& StagePtr);
		virtual ~MyCameraman();
		//初期化
		virtual void OnCreate() override;
		//操作
		virtual void OnUpdate() override;
		void ChangeCamera();
	};

	//--------------------------------------------------------------------------------------
	//　Myカメラ(コンポーネントではない)
	//--------------------------------------------------------------------------------------
	class MyCamera : public Camera
	{
		weak_ptr<GameObject> m_TargetObject;	//目標となるオブジェクト
		float m_ToTargetLerp;	//目標を追いかける際の補間値
		bsm::Vec3 m_TargetToAt;	//目標から視点を調整する位置ベクトル

		//プレイヤーからの位置
		Vec3 offset = Vec3(0.0f, 40.0f, -7.0f);

	public:
		void OnUpdate() override;
		void ChangeCamera();
		void SetTargetObject(const shared_ptr<GameObject>& Obj);
	};

	//--------------------------------------------------------------------------------------
	//　プレイヤーカメラ
	//--------------------------------------------------------------------------------------
	class PlayerCameraman : public GameObject {
		Vec3 m_StartPos;
		Vec3 m_EndPos;
		Vec3 m_AtStartPos;
		Vec3 m_AtEndPos;
		Vec3 m_AtPos;
		float m_TotalTime;

		Vec3 offset = Vec3(0.0f, 40.0f, -7.0f);
		Vec3 m_MyCamOffset = Vec3(0.0f, 10.0f, -7.0f);
		Vec3 m_GoalCamOffset = Vec3(0.0f, 10.0f, -7.0f);


		//ステートマシーン
		unique_ptr< StateMachine<PlayerCameraman> >  m_StateMachine;
	public:
		//構築と破棄
		PlayerCameraman(const shared_ptr<Stage>& StagePtr);
		virtual ~PlayerCameraman();
		//初期化
		virtual void OnCreate() override;
		//操作
		virtual void OnUpdate() override;
		//アクセサ
		const unique_ptr<StateMachine<PlayerCameraman>>& GetStateMachine() {
			return m_StateMachine;
		}

		Vec3 GetAtPos() const {
			return m_AtPos;
		}
		Vec3 GetPos() const {
			return GetComponent<Transform>()->GetPosition();
		}

		void ToTreasureEnterBehavior();
		void ToStartPointEnterBehavior();
		void MoveToPlayerEnterBehavior();
		void MoveToPlayerExcuteBehavior();
		void MoveToPlayer();
		void ZoomEnterBehavior();
		bool ExcuteBehavior(float totaltime);
		void ZoomDrawSwitch();

		//描画切り替え
		float m_DrawActiveLength = 35.0f;
		float m_DrawActiveFloorLength = 40.0f;
		void DrawActiveSwitch();
	};

	//--------------------------------------------------------------------------------------
	//	class PlayerCameramanMoveToPlayerState : public ObjState<PlayerCameraman>;
	//--------------------------------------------------------------------------------------
	class PlayerCameramanMoveToPlayerState : public ObjState<PlayerCameraman>
	{
		PlayerCameramanMoveToPlayerState() {}
	public:
		static shared_ptr<PlayerCameramanMoveToPlayerState> Instance();
		virtual void Enter(const shared_ptr<PlayerCameraman>& Obj)override;
		virtual void Execute(const shared_ptr<PlayerCameraman>& Obj)override;
		virtual void Exit(const shared_ptr<PlayerCameraman>& Obj)override;
	};
	//--------------------------------------------------------------------------------------
	//	class PlayerCameramanClearState : public ObjState<PlayerCameraman>;
	//--------------------------------------------------------------------------------------
	class PlayerCameramanZoomState : public ObjState<PlayerCameraman>
	{
		PlayerCameramanZoomState() {}
	public:
		static shared_ptr<PlayerCameramanZoomState> Instance();
		virtual void Enter(const shared_ptr<PlayerCameraman>& Obj)override;
		virtual void Execute(const shared_ptr<PlayerCameraman>& Obj)override;
		virtual void Exit(const shared_ptr<PlayerCameraman>& Obj)override;
	};
	//--------------------------------------------------------------------------------------
	//	class PlayerCameramanEndState : public ObjState<PlayerCameraman>;
	//--------------------------------------------------------------------------------------
	class PlayerCameramanEndState : public ObjState<PlayerCameraman>
	{
		PlayerCameramanEndState() {}
	public:
		static shared_ptr<PlayerCameramanEndState> Instance();
		virtual void Enter(const shared_ptr<PlayerCameraman>& Obj)override;
		virtual void Execute(const shared_ptr<PlayerCameraman>& Obj)override;
		virtual void Exit(const shared_ptr<PlayerCameraman>& Obj)override;
	};

	//--------------------------------------------------------------------------------------
	//	プレイヤーカメラ（コンポーネントではない）
	//--------------------------------------------------------------------------------------
	class PlayerCamera : public Camera {
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンストラクタ
		*/
		//--------------------------------------------------------------------------------------
		PlayerCamera();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~PlayerCamera();
		//--------------------------------------------------------------------------------------
		/*!
		@brief 更新処理
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate()override;
		void ChangeCamera();
	};

	//--------------------------------------------------------------------------------------
	//　オープニングカメラ
	//--------------------------------------------------------------------------------------
	class OpeningCameraman : public GameObject {
		Vec3 m_StartPos;
		Vec3 m_EndPos;
		Vec3 m_AtStartPos;
		Vec3 m_AtEndPos;
		Vec3 m_AtPos;
		float m_TotalTime;

		Vec3 offset = Vec3(0.0f, 40.0f, -7.0f);

		//ステートマシーン
		unique_ptr< StateMachine<OpeningCameraman> >  m_StateMachine;
	public:
		//構築と破棄
		OpeningCameraman(const shared_ptr<Stage>& StagePtr);
		virtual ~OpeningCameraman();
		//初期化
		virtual void OnCreate() override;
		//操作
		virtual void OnUpdate() override;
		//アクセサ
		const unique_ptr<StateMachine<OpeningCameraman>>& GetStateMachine() {
			return m_StateMachine;
		}

		Vec3 GetAtPos() const {
			return m_AtPos;
		}
		void ToGoalEnterBehavior();
		void ToGoalExcuteBehavior();
		float GetTotalTime();
		void ToStartEnterBehavior();
		bool ExcuteBehavior(float totaltime);
		void EndStateEnterBehavior();

		//描画切り替え
		float m_DrawActiveLength = 35.0f;
		float m_DrawActiveFloorLength = 40.0f;
		void DrawActiveSwitch();
	};

	//--------------------------------------------------------------------------------------
	//	class OpeningCameramanToGoalState : public ObjState<OpeningCameraman>;
	//--------------------------------------------------------------------------------------
	class OpeningCameramanStartState : public ObjState<OpeningCameraman>
	{
		OpeningCameramanStartState() {}
	public:
		static shared_ptr<OpeningCameramanStartState> Instance();
		virtual void Enter(const shared_ptr<OpeningCameraman>& Obj)override;
		virtual void Execute(const shared_ptr<OpeningCameraman>& Obj)override;
		virtual void Exit(const shared_ptr<OpeningCameraman>& Obj)override;
	};

	//--------------------------------------------------------------------------------------
	//	class OpeningCameramanToStartState : public ObjState<OpeningCameraman>;
	//--------------------------------------------------------------------------------------
	class OpeningCameramanMoveState : public ObjState<OpeningCameraman>
	{
		OpeningCameramanMoveState() {}
	public:
		static shared_ptr<OpeningCameramanMoveState> Instance();
		virtual void Enter(const shared_ptr<OpeningCameraman>& Obj)override;
		virtual void Execute(const shared_ptr<OpeningCameraman>& Obj)override;
		virtual void Exit(const shared_ptr<OpeningCameraman>& Obj)override;
	};

	//--------------------------------------------------------------------------------------
	//	class OpeningCameramanEndState : public ObjState<OpeningCameraman>;
	//--------------------------------------------------------------------------------------
	class OpeningCameramanEndState : public ObjState<OpeningCameraman>
	{
		OpeningCameramanEndState() {}
	public:
		static shared_ptr<OpeningCameramanEndState> Instance();
		virtual void Enter(const shared_ptr<OpeningCameraman>& Obj)override;
		virtual void Execute(const shared_ptr<OpeningCameraman>& Obj)override;
		virtual void Exit(const shared_ptr<OpeningCameraman>& Obj)override;
	};

	//--------------------------------------------------------------------------------------
	//	オープニングカメラ（コンポーネントではない）
	//--------------------------------------------------------------------------------------
	class OpeningCamera : public Camera {
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンストラクタ
		*/
		//--------------------------------------------------------------------------------------
		OpeningCamera();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~OpeningCamera();
		//--------------------------------------------------------------------------------------
		/*!
		@brief 更新処理
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate()override;

	};

	//--------------------------------------------------------------------------------------
	//　ゴールカメラ
	//--------------------------------------------------------------------------------------
	class GoalCameraman : public GameObject {
		Vec3 m_StartPos;
		Vec3 m_EndPos;
		Vec3 m_AtStartPos;
		Vec3 m_AtEndPos;
		Vec3 m_AtPos;
		float m_TotalTime;

		Vec3 m_MyCamOffset = Vec3(0.0f, 40.0f, -7.0f);
		Vec3 m_GoalCamOffset = Vec3(0.0f, 10.0f, -7.0f);

		GoalCamStateNum m_GoalCamStateNum;

		//ステートマシーン
		unique_ptr< StateMachine<GoalCameraman> >  m_StateMachine;

		int m_StateNum = 0;
	public:
		//構築と破棄
		GoalCameraman(const shared_ptr<Stage>& StagePtr);
		virtual ~GoalCameraman();
		//初期化
		virtual void OnCreate() override;
		//操作
		virtual void OnUpdate() override;
		virtual void OnUpdate2() override;
		void DrawStrings();
		//アクセサ
		const unique_ptr<StateMachine<GoalCameraman>>& GetStateMachine() {
			return m_StateMachine;
		}

		Vec3 GetAtPos() const {
			return m_AtPos;
		}

		void SetStateNum(int stateNum)
		{
			m_StateNum = stateNum;
		}
		int GetStateNum()
		{
			return m_StateNum;
		}

		void SetGoalCameraStateNum(GoalCamStateNum goalNum)
		{
			m_GoalCamStateNum = goalNum;
		}
		GoalCamStateNum GetGoalCameraStateNum()
		{
			return m_GoalCamStateNum;
		}

		void MoveStartEnterBehavior();
		void MoveStartExcuteBehaviour();
		void MovingEnterBehavior();
		void MovingExcuteBehavior();
		void MoveEndEnterBehavior();
		bool ExcuteBehavior(float totaltime);
	};

	//--------------------------------------------------------------------------------------
	//	class OpeningCameramanToGoalState : public ObjState<GoalCameraman>;
	//--------------------------------------------------------------------------------------
	class GoalCameramanMoveStartState : public ObjState<GoalCameraman>
	{
		GoalCameramanMoveStartState() {}
	public:
		static shared_ptr<GoalCameramanMoveStartState> Instance();
		virtual void Enter(const shared_ptr<GoalCameraman>& Obj)override;
		virtual void Execute(const shared_ptr<GoalCameraman>& Obj)override;
		virtual void Exit(const shared_ptr<GoalCameraman>& Obj)override;
	};

	//--------------------------------------------------------------------------------------
	//	class OpeningCameramanToStartState : public ObjState<GoalCameraman>;
	//--------------------------------------------------------------------------------------
	class GoalCameramanMovingState : public ObjState<GoalCameraman>
	{
		GoalCameramanMovingState() {}
	public:
		static shared_ptr<GoalCameramanMovingState> Instance();
		virtual void Enter(const shared_ptr<GoalCameraman>& Obj)override;
		virtual void Execute(const shared_ptr<GoalCameraman>& Obj)override;
		virtual void Exit(const shared_ptr<GoalCameraman>& Obj)override;
	};

	//--------------------------------------------------------------------------------------
	//	class OpeningCameramanEndState : public ObjState<GoalCameraman>;
	//--------------------------------------------------------------------------------------
	class GoalCameramanMoveEndState : public ObjState<GoalCameraman>
	{
		GoalCameramanMoveEndState() {}
	public:
		static shared_ptr<GoalCameramanMoveEndState> Instance();
		virtual void Enter(const shared_ptr<GoalCameraman>& Obj)override;
		virtual void Execute(const shared_ptr<GoalCameraman>& Obj)override;
		virtual void Exit(const shared_ptr<GoalCameraman>& Obj)override;
	};

	//--------------------------------------------------------------------------------------
	//	ゴールカメラ（コンポーネントではない）
	//--------------------------------------------------------------------------------------
	class GoalCamera : public Camera {
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンストラクタ
		*/
		//--------------------------------------------------------------------------------------
		GoalCamera();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~GoalCamera();
		//--------------------------------------------------------------------------------------
		/*!
		@brief 更新処理
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate()override;

		void SetTargetPoint(const shared_ptr<GameObject>& Obj);
	};
}
//end basecross
