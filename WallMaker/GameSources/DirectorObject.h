/*!
@file Character.h
@brief �L�����N??�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	//--------------------------------------------------------------------------------------
	///	�����̉��N���X
	//--------------------------------------------------------------------------------------
	class MultiFire : public MultiParticle {
	public:
		//�\�z�Ɣj��
		MultiFire(shared_ptr<Stage>& StagePtr);
		virtual ~MultiFire();
		//������
		virtual void OnCreate() override;
		void InsertFire(const Vec3& Pos, int GenerateNum, Vec3 MoveSpeed);
	};
	//--------------------------------------------------------------------------------------
	///	�����̔��ˌ�̉��N���X
	//--------------------------------------------------------------------------------------
	class MultiFireBlue : public MultiParticle {
	public:
		//�\�z�Ɣj��
		MultiFireBlue(shared_ptr<Stage>& StagePtr);
		virtual ~MultiFireBlue();
		//������
		virtual void OnCreate() override;
		void InsertFire(const Vec3& Pos, int GenerateNum, Vec3 MoveSpeed);
	};

	//--------------------------------------------------------------------------------------
	///	�Q�[���J�n���Ƀv���C���[���o�����o
	//--------------------------------------------------------------------------------------
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

		//���S�ɉ�������܂ł̎���
		float m_ClearTimer = 0.0f;
		float m_ForDownTime = 1.0f;
		//���S�ɓ����ɂȂ�܂ł̎���
		float m_ForClearTime = 1.0f;
		//���݂̓����x
		float m_Alpha = 0.0f;

		Vec3 m_FirstOffset = Vec3(0.0f, 2.0f, 0.0f);

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

		void UnClear();
		void Falling();
		void ClearAndDelete();
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
