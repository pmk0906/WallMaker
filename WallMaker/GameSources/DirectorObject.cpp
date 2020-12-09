/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
	WarpMagicSircle::WarpMagicSircle(
		const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position)
	{}
	WarpMagicSircle::~WarpMagicSircle() {}

	//	初期化
	void WarpMagicSircle::OnCreate()
	{
		auto player_share = GetStage()->GetSharedGameObject<Player>(WstringKey::ShareObj_Player);
		auto ptrMyTrans = AddComponent<Transform>();
		ptrMyTrans->SetScale(Vec3(5.0f, 0.3f, 5.0f));
		ptrMyTrans->SetRotation(Vec3(0.0f, m_Rotation.y, 0.0f));
		ptrMyTrans->SetPosition(Vec3(m_Position.x, m_Position.y, m_Position.z));

		Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
		spanMat.affineTransformation(
			Vec3(0.55f, 0.5f, 5.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(XMConvertToRadians(90.0f), 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, -0.5f)
		);

		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetAfterCollision(AfterCollision::None);
		ptrColl->SetDrawActive(true);

		//描画処理
		auto ptrDraw = AddComponent<BcPNTnTStaticModelDraw>();
		ptrDraw->SetMeshResource(L"MAGICWALL_MESH");
		ptrDraw->SetMeshToTransformMatrix(spanMat);
		ptrDraw->SetLightingEnabled(false);

		//描画するテクスチャを設定
		SetAlphaActive(true);

		//ステートマシンの構築
		m_StateMachine.reset(new StateMachine<WarpMagicSircle>(GetThis<WarpMagicSircle>()));
		//最初のステートをSeekFarStateに設定
		m_StateMachine->ChangeState(FirstState::Instance());
	}

	void WarpMagicSircle::OnUpdate()
	{
		auto player_share = GetStage()->GetSharedGameObject<Player>(WstringKey::ShareObj_Player);
		auto playerPos = player_share->GetPosition();

		//ステートマシンのUpdateを行う
		//この中でステートの切り替えが行われる
		m_StateMachine->Update();
	}

	//--------------------------------------------------------------------------------------
	//	透明状態から降りる瞬間まで
	//--------------------------------------------------------------------------------------
	shared_ptr<FirstState> FirstState::Instance() {
		static shared_ptr<FirstState> instance(new FirstState);
		return instance;
	}
	void FirstState::Enter(const shared_ptr<WarpMagicSircle>& Obj) {
	}
	void FirstState::Execute(const shared_ptr<WarpMagicSircle>& Obj) {
		auto ptrSeek = Obj->GetBehavior<SeekSteering>();
		auto ptrSep = Obj->GetBehavior<SeparationSteering>();
	}

	void FirstState::Exit(const shared_ptr<WarpMagicSircle>& Obj) {
	}

	//--------------------------------------------------------------------------------------
	//	降りてから床で止まるまで
	//--------------------------------------------------------------------------------------
	shared_ptr<DownState> DownState::Instance() {
		static shared_ptr<DownState> instance(new DownState);
		return instance;
	}
	void DownState::Enter(const shared_ptr<WarpMagicSircle>& Obj) {
	}
	void DownState::Execute(const shared_ptr<WarpMagicSircle>& Obj) {
		auto ptrArrive = Obj->GetBehavior<ArriveSteering>();
		auto ptrSep = Obj->GetBehavior<SeparationSteering>();
	}
	void DownState::Exit(const shared_ptr<WarpMagicSircle>& Obj) {
	}

	//--------------------------------------------------------------------------------------
	//	止まってから消えるまで
	//--------------------------------------------------------------------------------------
	shared_ptr<DeleteState> DeleteState::Instance() {
		static shared_ptr<DeleteState> instance(new DeleteState);
		return instance;
	}
	void DeleteState::Enter(const shared_ptr<WarpMagicSircle>& Obj) {
	}
	void DeleteState::Execute(const shared_ptr<WarpMagicSircle>& Obj) {
		auto ptrArrive = Obj->GetBehavior<ArriveSteering>();
		auto ptrSep = Obj->GetBehavior<SeparationSteering>();
	}
	void DeleteState::Exit(const shared_ptr<WarpMagicSircle>& Obj) {
	}
}
//end basecross
