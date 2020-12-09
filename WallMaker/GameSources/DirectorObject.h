/*!
@file Character.h
@brief キャラク??など
*/

#pragma once
#include "stdafx.h"

namespace basecross{
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
