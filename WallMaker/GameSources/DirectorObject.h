/*!
@file Character.h
@brief �L�����N??�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	// ����
	class WarpMagicSircle : public GameObject
	{
		// �傫���A��]�A�ʒu
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;

		//�X�e�[�g�}�V�[��
		unique_ptr< StateMachine<WarpMagicSircle> >  m_StateMachine;
		Vec3 m_StartPos;
		float m_StateChangeSize;
	public:
		//�\�z�Ɣj��
		WarpMagicSircle(
			const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
		);
		virtual ~WarpMagicSircle();

		//�A�N�Z�T
		const unique_ptr<StateMachine<WarpMagicSircle>>& GetStateMachine() {
			return m_StateMachine;
		}
		float GetStateChangeSize() const {
			return m_StateChangeSize;
		}

		// ������
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};

	//--------------------------------------------------------------------------------------
	//	class FirstState : public ObjState<WarpMagicSircle>;
	//	�p�r: ������Ԃ���~���u�Ԃ܂�
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
	//	�p�r: �~��Ă��珰�Ŏ~�܂�܂�
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
	//	�p�r: �~�܂��Ă��������܂�
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
