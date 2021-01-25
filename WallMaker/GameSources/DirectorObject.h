/*!
@file Character.h
@brief ƒLƒƒƒ‰ƒN??‚È‚Ç
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	//--------------------------------------------------------------------------------------
	///	•¡”‚Ì‰ŠƒNƒ‰ƒX
	//--------------------------------------------------------------------------------------
	class MultiFire : public MultiParticle {
	public:
		//\’z‚Æ”jŠü
		MultiFire(shared_ptr<Stage>& StagePtr);
		virtual ~MultiFire();
		//‰Šú‰»
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		void InsertFire(const Vec3& Pos, int GenerateNum, Vec3 MoveSpeed);
	};
	//--------------------------------------------------------------------------------------
	///	•¡”‚Ì”½ËŒã‚Ì‰ŠƒNƒ‰ƒX
	//--------------------------------------------------------------------------------------
	class MultiFireBlue : public MultiParticle {
	public:
		//\’z‚Æ”jŠü
		MultiFireBlue(shared_ptr<Stage>& StagePtr);
		virtual ~MultiFireBlue();
		//‰Šú‰»
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		void InsertFire(const Vec3& Pos, int GenerateNum, Vec3 MoveSpeed);
	};

	class RedFire : public MultiParticle {
	public:
		//\’z‚Æ”jŠü
		RedFire(shared_ptr<Stage>& StagePtr);
		virtual ~RedFire();
		//‰Šú‰»
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		void InsertFire(const Vec3& Pos, int GenerateNum, Vec3 MoveSpeed);
	};

	class OrangeFire : public MultiParticle {
	public:
		//\’z‚Æ”jŠü
		OrangeFire(shared_ptr<Stage>& StagePtr);
		virtual ~OrangeFire();
		//‰Šú‰»
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		void InsertFire(const Vec3& Pos, int GenerateNum, Vec3 MoveSpeed);
	};

	class YellowFire : public MultiParticle {
	public:
		//\’z‚Æ”jŠü
		YellowFire(shared_ptr<Stage>& StagePtr);
		virtual ~YellowFire();
		//‰Šú‰»
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		void InsertFire(const Vec3& Pos, int GenerateNum, Vec3 MoveSpeed);
	};

	class GreenFire : public MultiParticle {
	public:
		//\’z‚Æ”jŠü
		GreenFire(shared_ptr<Stage>& StagePtr);
		virtual ~GreenFire();
		//‰Šú‰»
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		void InsertFire(const Vec3& Pos, int GenerateNum, Vec3 MoveSpeed);
	};

	class BlueFire : public MultiParticle {
	public:
		//\’z‚Æ”jŠü
		BlueFire(shared_ptr<Stage>& StagePtr);
		virtual ~BlueFire();
		//‰Šú‰»
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		void InsertFire(const Vec3& Pos, int GenerateNum, Vec3 MoveSpeed);
	};

	class BlackFire : public MultiParticle {
	public:
		//\’z‚Æ”jŠü
		BlackFire(shared_ptr<Stage>& StagePtr);
		virtual ~BlackFire();
		//‰Šú‰»
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		void InsertFire(const Vec3& Pos, int GenerateNum, Vec3 MoveSpeed);
	};
	//--------------------------------------------------------------------------------------
	///	•Ç‚ğ‰ó‚µ‚½‚Æ‚«‚Ì‰Œ
	//--------------------------------------------------------------------------------------
	class WallBreakEffect : public MultiParticle {
	public:
		//\’z‚Æ”jŠü
		WallBreakEffect(shared_ptr<Stage>& StagePtr);
		virtual ~WallBreakEffect();
		//‰Šú‰»
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		void InsertEffect(const Vec3& Pos, int GenerateNum, Vec3 MoveSpeed);
	};

	//--------------------------------------------------------------------------------------
	///	’e‚ª”½Ë‚µ‚½‚Æ‚«‚ÌƒGƒtƒFƒNƒg
	//--------------------------------------------------------------------------------------
	class ReflectBulletEffect : public MultiParticle {
	public:
		//\’z‚Æ”jŠü
		ReflectBulletEffect(shared_ptr<Stage>& StagePtr);
		virtual ~ReflectBulletEffect();
		//‰Šú‰»
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		void InsertEffect(const Vec3& Pos, int GenerateNum, Vec3 MoveSpeed);
	};

	//--------------------------------------------------------------------------------------
	///	ƒQ[ƒ€ŠJn‚ÉƒvƒŒƒCƒ„[‚ğo‚·‰‰o
	//--------------------------------------------------------------------------------------
	// ‰¼°
	class WarpMagicSircle : public GameObject
	{
		// ‘å‚«‚³A‰ñ“]AˆÊ’u
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;

		//ƒXƒe[ƒgƒ}ƒV[ƒ“
		unique_ptr< StateMachine<WarpMagicSircle> >  m_StateMachine;
		Vec3 m_StartPos;
		float m_StateChangeSize;

		//Š®‘S‚É‰Â‹‰»‚·‚é‚Ü‚Å‚ÌŠÔ
		float m_ClearTimer = 0.0f;
		float m_ForDownTime = 1.0f;
		//Š®‘S‚É“§–¾‚É‚È‚é‚Ü‚Å‚ÌŠÔ
		float m_ForClearTime = 1.0f;
		//Œ»İ‚Ì“§–¾“x
		float m_Alpha = 0.0f;

		Vec3 m_FirstOffset = Vec3(0.0f, 2.0f, 0.0f);

	public:
		//\’z‚Æ”jŠü
		WarpMagicSircle(
			const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
		);
		virtual ~WarpMagicSircle();

		//ƒAƒNƒZƒT
		const unique_ptr<StateMachine<WarpMagicSircle>>& GetStateMachine() {
			return m_StateMachine;
		}
		float GetStateChangeSize() const {
			return m_StateChangeSize;
		}

		// ‰Šú‰»
		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		void UnClear();
		void Falling();
		void ClearAndDelete();
	};

	//--------------------------------------------------------------------------------------
	//	class FirstState : public ObjState<WarpMagicSircle>;
	//	—p“r: “§–¾ó‘Ô‚©‚ç~‚è‚éuŠÔ‚Ü‚Å
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
	//	—p“r: ~‚è‚Ä‚©‚ç°‚Å~‚Ü‚é‚Ü‚Å
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
	//	—p“r: ~‚Ü‚Á‚Ä‚©‚çÁ‚¦‚é‚Ü‚Å
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
