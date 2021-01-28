/*!
@file Character.h
@brief �L�����N??�Ȃ�
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
	//�@My�J����
	//--------------------------------------------------------------------------------------
	class MyCameraman : public GameObject
	{
		Vec3 offset = Vec3(0.0f, 40.0f, -7.0f);

	public:
		//�\�z�Ɣj��
		MyCameraman(const shared_ptr<Stage>& StagePtr);
		virtual ~MyCameraman();
		//������
		virtual void OnCreate() override;
		//����
		virtual void OnUpdate() override;
		void ChangeCamera();
	};

	//--------------------------------------------------------------------------------------
	//�@My�J����(�R���|�[�l���g�ł͂Ȃ�)
	//--------------------------------------------------------------------------------------
	class MyCamera : public Camera
	{
		weak_ptr<GameObject> m_TargetObject;	//�ڕW�ƂȂ�I�u�W�F�N�g
		float m_ToTargetLerp;	//�ڕW��ǂ�������ۂ̕�Ԓl
		bsm::Vec3 m_TargetToAt;	//�ڕW���王�_�𒲐�����ʒu�x�N�g��

		//�v���C���[����̈ʒu
		Vec3 offset = Vec3(0.0f, 40.0f, -7.0f);

	public:
		void OnUpdate() override;
		void ChangeCamera();
		void SetTargetObject(const shared_ptr<GameObject>& Obj);
	};

	//--------------------------------------------------------------------------------------
	//�@�v���C���[�J����
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


		//�X�e�[�g�}�V�[��
		unique_ptr< StateMachine<PlayerCameraman> >  m_StateMachine;
	public:
		//�\�z�Ɣj��
		PlayerCameraman(const shared_ptr<Stage>& StagePtr);
		virtual ~PlayerCameraman();
		//������
		virtual void OnCreate() override;
		//����
		virtual void OnUpdate() override;
		//�A�N�Z�T
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

		//�`��؂�ւ�
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
	//	�v���C���[�J�����i�R���|�[�l���g�ł͂Ȃ��j
	//--------------------------------------------------------------------------------------
	class PlayerCamera : public Camera {
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�R���X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		PlayerCamera();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~PlayerCamera();
		//--------------------------------------------------------------------------------------
		/*!
		@brief �X�V����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate()override;
		void ChangeCamera();
	};

	//--------------------------------------------------------------------------------------
	//�@�I�[�v�j���O�J����
	//--------------------------------------------------------------------------------------
	class OpeningCameraman : public GameObject {
		Vec3 m_StartPos;
		Vec3 m_EndPos;
		Vec3 m_AtStartPos;
		Vec3 m_AtEndPos;
		Vec3 m_AtPos;
		float m_TotalTime;

		Vec3 offset = Vec3(0.0f, 40.0f, -7.0f);

		//�X�e�[�g�}�V�[��
		unique_ptr< StateMachine<OpeningCameraman> >  m_StateMachine;
	public:
		//�\�z�Ɣj��
		OpeningCameraman(const shared_ptr<Stage>& StagePtr);
		virtual ~OpeningCameraman();
		//������
		virtual void OnCreate() override;
		//����
		virtual void OnUpdate() override;
		//�A�N�Z�T
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

		//�`��؂�ւ�
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
	//	�I�[�v�j���O�J�����i�R���|�[�l���g�ł͂Ȃ��j
	//--------------------------------------------------------------------------------------
	class OpeningCamera : public Camera {
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�R���X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		OpeningCamera();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~OpeningCamera();
		//--------------------------------------------------------------------------------------
		/*!
		@brief �X�V����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate()override;

	};

	//--------------------------------------------------------------------------------------
	//�@�S�[���J����
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

		//�X�e�[�g�}�V�[��
		unique_ptr< StateMachine<GoalCameraman> >  m_StateMachine;

		int m_StateNum = 0;
	public:
		//�\�z�Ɣj��
		GoalCameraman(const shared_ptr<Stage>& StagePtr);
		virtual ~GoalCameraman();
		//������
		virtual void OnCreate() override;
		//����
		virtual void OnUpdate() override;
		virtual void OnUpdate2() override;
		void DrawStrings();
		//�A�N�Z�T
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
	//	�S�[���J�����i�R���|�[�l���g�ł͂Ȃ��j
	//--------------------------------------------------------------------------------------
	class GoalCamera : public Camera {
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�R���X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		GoalCamera();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	�f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~GoalCamera();
		//--------------------------------------------------------------------------------------
		/*!
		@brief �X�V����
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate()override;

		void SetTargetPoint(const shared_ptr<GameObject>& Obj);
	};
}
//end basecross
