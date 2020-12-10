/*!
@file Character.h
@brief キャラク??など
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	//--------------------------------------------------------------------------------------
	///	複数の炎クラス
	//--------------------------------------------------------------------------------------
	class MultiFire : public MultiParticle {
	public:
		//構築と破棄
		MultiFire(shared_ptr<Stage>& StagePtr);
		virtual ~MultiFire();
		//初期化
		virtual void OnCreate() override;
		void InsertFire(const Vec3& Pos, int GenerateNum, Vec3 MoveSpeed);
	};
	//--------------------------------------------------------------------------------------
	///	複数の反射後の炎クラス
	//--------------------------------------------------------------------------------------
	class MultiFireBlue : public MultiParticle {
	public:
		//構築と破棄
		MultiFireBlue(shared_ptr<Stage>& StagePtr);
		virtual ~MultiFireBlue();
		//初期化
		virtual void OnCreate() override;
		void InsertFire(const Vec3& Pos, int GenerateNum, Vec3 MoveSpeed);
	};

	//--------------------------------------------------------------------------------------
	///	ゲーム開始時にプレイヤーを出す演出
	//--------------------------------------------------------------------------------------
	// 仮床
	class WarpMagicSircle : public GameObject
	{
		// 大きさ、回転、位置
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;

		//ステートマシーン
		unique_ptr< StateMachine<WarpMagicSircle> >  m_StateMachine;
		Vec3 m_StartPos;
		float m_StateChangeSize;

		//完全に可視化するまでの時間
		float m_ClearTimer = 0.0f;
		float m_ForDownTime = 1.0f;
		//完全に透明になるまでの時間
		float m_ForClearTime = 1.0f;
		//現在の透明度
		float m_Alpha = 0.0f;

		Vec3 m_FirstOffset = Vec3(0.0f, 2.0f, 0.0f);

	public:
		//構築と破棄
		WarpMagicSircle(
			const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
		);
		virtual ~WarpMagicSircle();

		//アクセサ
		const unique_ptr<StateMachine<WarpMagicSircle>>& GetStateMachine() {
			return m_StateMachine;
		}
		float GetStateChangeSize() const {
			return m_StateChangeSize;
		}

		// 初期化
		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		void UnClear();
		void Falling();
		void ClearAndDelete();
	};

	//--------------------------------------------------------------------------------------
	//	class FirstState : public ObjState<WarpMagicSircle>;
	//	用途: 透明状態から降りる瞬間まで
	//--------------------------------------------------------------------------------------
	class FirstState : public ObjState<WarpMagicSircle>
	{
		FirstState() {}
	public:
		static shared_ptr<FirstState> Instance();
		virtual void Enter(const shared_ptr<WarpMagicSircle>& Obj)override;
		virtual void Execute(const shared_ptr<WarpMagicSircle>& Obj)override;
		virtual void Exit(const shared_ptr<WarpMagicSircle>& Obj)override;
	};

	//--------------------------------------------------------------------------------------
	//	class DownState : public ObjState<WarpMagicSircle>;
	//	用途: 降りてから床で止まるまで
	//--------------------------------------------------------------------------------------
	class DownState : public ObjState<WarpMagicSircle>
	{
		DownState() {}
	public:
		static shared_ptr<DownState> Instance();
		virtual void Enter(const shared_ptr<WarpMagicSircle>& Obj)override;
		virtual void Execute(const shared_ptr<WarpMagicSircle>& Obj)override;
		virtual void Exit(const shared_ptr<WarpMagicSircle>& Obj)override;
	};
	//--------------------------------------------------------------------------------------
	//	class DeleteState : public ObjState<WarpMagicSircle>;
	//	用途: 止まってから消えるまで
	//--------------------------------------------------------------------------------------
	class DeleteState : public ObjState<WarpMagicSircle>
	{
		DeleteState() {}
	public:
		static shared_ptr<DeleteState> Instance();
		virtual void Enter(const shared_ptr<WarpMagicSircle>& Obj)override;
		virtual void Execute(const shared_ptr<WarpMagicSircle>& Obj)override;
		virtual void Exit(const shared_ptr<WarpMagicSircle>& Obj)override;
	};
}
//end basecross
