/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
	//--------------------------------------------------------------------------------------
	///	複数の炎クラス
	//--------------------------------------------------------------------------------------
	//構築と破棄
	MultiFire::MultiFire(shared_ptr<Stage>& StagePtr) :
		MultiParticle(StagePtr)
	{}
	MultiFire::~MultiFire() {}

	//初期化
	void MultiFire::OnCreate() {
		//加算描画処理をする
		SetAddType(true);
	}

	void MultiFire::InsertFire(const Vec3& Pos, int GenerateNum, Vec3 MoveSpeed) 
	{
		auto ptrParticle = InsertParticle(GenerateNum);
		ptrParticle->SetEmitterPos(Pos);
		ptrParticle->SetTextureResource(L"FIRE_TX");
		ptrParticle->SetMaxTime(1.0f);
		for (auto& rParticleSprite : ptrParticle->GetParticleSpriteVec()) {
			rParticleSprite.m_LocalPos.x = Util::RandZeroToOne() * 0.1f - 0.05f;
			rParticleSprite.m_LocalPos.y = Util::RandZeroToOne() * 0.1f;
			rParticleSprite.m_LocalPos.z = Util::RandZeroToOne() * 0.1f - 0.05f;
			//各パーティクルの移動速度を指定
			rParticleSprite.m_Velocity = Vec3(
				rParticleSprite.m_LocalPos.x * MoveSpeed.x,
				rParticleSprite.m_LocalPos.y * MoveSpeed.y,
				rParticleSprite.m_LocalPos.z * MoveSpeed.z
			);
			//色の指定
			rParticleSprite.m_Color = Col4(1.0f, 1.0f, 1.0f, 1.0f);
		}
	}

	//--------------------------------------------------------------------------------------
	///	複数の炎クラス
	//--------------------------------------------------------------------------------------
	//構築と破棄
	MultiFireBlue::MultiFireBlue(shared_ptr<Stage>& StagePtr) :
		MultiParticle(StagePtr)
	{}
	MultiFireBlue::~MultiFireBlue() {}

	//初期化
	void MultiFireBlue::OnCreate() {
		//加算描画処理をする
		SetAddType(true);
	}

	void MultiFireBlue::InsertFire(const Vec3& Pos, int GenerateNum, Vec3 MoveSpeed) {
		auto ptrParticle = InsertParticle(GenerateNum);
		ptrParticle->SetEmitterPos(Pos);
		ptrParticle->SetTextureResource(L"BLUEFIRE_TX");
		ptrParticle->SetMaxTime(1.0f);
		for (auto& rParticleSprite : ptrParticle->GetParticleSpriteVec()) {
			rParticleSprite.m_LocalPos.x = Util::RandZeroToOne() * 0.1f - 0.05f;
			rParticleSprite.m_LocalPos.y = Util::RandZeroToOne() * 0.1f;
			rParticleSprite.m_LocalPos.z = Util::RandZeroToOne() * 0.1f - 0.05f;
			//各パーティクルの移動速度を指定
			rParticleSprite.m_Velocity = Vec3(
				rParticleSprite.m_LocalPos.x * MoveSpeed.x,
				rParticleSprite.m_LocalPos.y * MoveSpeed.y,
				rParticleSprite.m_LocalPos.z * MoveSpeed.z
			);
			//色の指定
			rParticleSprite.m_Color = Col4(1.0f, 1.0f, 1.0f, 1.0f);
		}
	}

	//--------------------------------------------------------------------------------------
	///	壁を壊した時のエフェクト
	//--------------------------------------------------------------------------------------
	//構築と破棄
	WallBreakEffect::WallBreakEffect(shared_ptr<Stage>& StagePtr) :
		MultiParticle(StagePtr)
	{}
	WallBreakEffect::~WallBreakEffect() {}

	//初期化
	void WallBreakEffect::OnCreate() {
		
		auto ptrGrav = AddComponent<Gravity>();

		//加算描画処理をする
		SetAddType(true);
	}

	void WallBreakEffect::InsertEffect(const Vec3& Pos, int GenerateNum, Vec3 MoveSpeed) {
		auto ptrParticle = InsertParticle(GenerateNum);
		ptrParticle->SetEmitterPos(Pos);
		ptrParticle->SetTextureResource(L"BREAK_TX");
		ptrParticle->SetMaxTime(1.0f);
		for (auto& rParticleSprite : ptrParticle->GetParticleSpriteVec()) {
			rParticleSprite.m_LocalPos.x = Util::RandZeroToOne() * 0.1f - 0.05f;
			rParticleSprite.m_LocalPos.y = Util::RandZeroToOne() * 0.1f;
			rParticleSprite.m_LocalPos.z = Util::RandZeroToOne() * 0.1f - 0.05f;
			//各パーティクルの移動速度を指定
			rParticleSprite.m_Velocity = Vec3(
				rParticleSprite.m_LocalPos.x * MoveSpeed.x,
				rParticleSprite.m_LocalPos.y * MoveSpeed.y,
				rParticleSprite.m_LocalPos.z * MoveSpeed.z
			);
		}
	}

	//--------------------------------------------------------------------------------------
	///	反射したときのエフェクト
	//--------------------------------------------------------------------------------------
	//構築と破棄
	ReflectBulletEffect::ReflectBulletEffect(shared_ptr<Stage>& StagePtr) :
		MultiParticle(StagePtr)
	{}
	ReflectBulletEffect::~ReflectBulletEffect() {}

	//初期化
	void ReflectBulletEffect::OnCreate() {

		//auto ptrGrav = AddComponent<Gravity>();

		//加算描画処理をする
		SetAddType(true);
	}

	void ReflectBulletEffect::InsertEffect(const Vec3& Pos, int GenerateNum, Vec3 MoveSpeed) {
		auto ptrParticle = InsertParticle(GenerateNum);
		ptrParticle->SetEmitterPos(Pos);
		ptrParticle->SetTextureResource(L"REFLECT_TX");
		ptrParticle->SetMaxTime(1.0f);
		for (auto& rParticleSprite : ptrParticle->GetParticleSpriteVec()) {
			rParticleSprite.m_LocalPos.x = Util::RandZeroToOne() * 0.1f - 0.05f;
			rParticleSprite.m_LocalPos.y = Util::RandZeroToOne() * 0.1f;
			rParticleSprite.m_LocalPos.z = Util::RandZeroToOne() * 0.1f - 0.05f;
			//各パーティクルの移動速度を指定
			rParticleSprite.m_Velocity = Vec3(
				rParticleSprite.m_LocalPos.x * MoveSpeed.x,
				rParticleSprite.m_LocalPos.y * MoveSpeed.y,
				rParticleSprite.m_LocalPos.z * MoveSpeed.z
			);
		}
	}

	//--------------------------------------------------------------------------------------
	///	ゲーム開始時にプレイヤーを出す演出
	//--------------------------------------------------------------------------------------
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

	void WarpMagicSircle::UnClear()
	{
		if (1.0f <= m_Alpha)
		{
			GetStateMachine()->ChangeState(DownState::Instance());
		}
		else
		{
			float delta = App::GetApp()->GetElapsedTime();
			m_ClearTimer += delta;
			auto ptrDraw = GetComponent<BcPNTnTStaticModelDraw>();
			m_Alpha += 0.05;
			ptrDraw->SetAlpha(m_Alpha);
		}
	}

	void WarpMagicSircle::Falling()
	{
		auto player_share = GetStage()->GetSharedGameObject<Player>(WstringKey::ShareObj_Player);
		auto playerPos = player_share->GetPosition();
		auto ptrTrans = GetComponent<Transform>();
		auto myPos = ptrTrans->GetPosition();
		if (myPos.y <= playerPos.y - 0.75f)
		{
			GetStateMachine()->ChangeState(DeleteState::Instance());
		}
		else
		{
			ptrTrans->SetPosition(myPos.x, myPos.y - 0.1f, myPos.z);
		}
	}
	//
	void WarpMagicSircle::ClearAndDelete()
	{
		if (m_Alpha <= 0.0f)
		{
			auto gm = GameManager::GetInstance();
			gm->SetMagicSircleMoved(true);

			auto startSprite = GetStage()->AddGameObject<FadeSprite>(true, Vec2(800, 200), Vec2(0, 150), false, 0.0f, 3.0f, L"START_TX", 1, Col4(1, 1, 1, 1.0f));
			startSprite->SetFadeFlgChanged(false);

			SetDrawActive(false);
			SetUpdateActive(false);
		}
		else
		{
			float delta = App::GetApp()->GetElapsedTime();
			m_ClearTimer -= delta;
			auto ptrDraw = GetComponent<BcPNTnTStaticModelDraw>();
			m_Alpha -= 0.05;
			ptrDraw->SetAlpha(m_Alpha);
		}
	}

	//	初期化
	void WarpMagicSircle::OnCreate()
	{
		auto playerPos = GetStage()->GetSharedGameObject<Player>(WstringKey::ShareObj_Player)->GetPosition();
		auto ptrMyTrans = AddComponent<Transform>();
		ptrMyTrans->SetScale(Vec3(7.0f, 0.3f, 7.0f));
		ptrMyTrans->SetRotation(Vec3(0.0f, m_Rotation.y, 0.0f));
		ptrMyTrans->SetPosition(playerPos + m_FirstOffset);

		Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
		spanMat.affineTransformation(
			Vec3(0.55f, 0.5f, 5.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(XMConvertToRadians(90.0f), 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, -0.5f)
		);

		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetAfterCollision(AfterCollision::None);
		//ptrColl->SetDrawActive(true);

		//描画処理
		auto ptrDraw = AddComponent<BcPNTnTStaticModelDraw>();
		ptrDraw->SetMeshResource(L"MAGICWALL_MESH");
		ptrDraw->SetMeshToTransformMatrix(spanMat);
		ptrDraw->SetLightingEnabled(false);
		ptrDraw->SetModelDiffusePriority(false);
		ptrDraw->SetAlpha(m_Alpha);

		//描画するテクスチャを設定
		SetAlphaActive(true);

		//ステートマシンの構築
		m_StateMachine.reset(new StateMachine<WarpMagicSircle>(GetThis<WarpMagicSircle>()));
		//最初のステートをSeekFarStateに設定
		m_StateMachine->ChangeState(FirstState::Instance());
	}

	void WarpMagicSircle::OnUpdate()
	{	
		auto gm = GameManager::GetInstance();
		if (gm->GetOpeningCameraMoveEnd() == true)
		{
			//ステートマシンのUpdateを行う
			//この中でステートの切り替えが行われる
			m_StateMachine->Update();
		}
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
		Obj->UnClear();
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
		auto gm = GameManager::GetInstance();
		gm->SetMagicSircleEnabledLook(true);
	}
	void DownState::Execute(const shared_ptr<WarpMagicSircle>& Obj) {
		Obj->Falling();
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
		Obj->ClearAndDelete();
	}
	void DeleteState::Exit(const shared_ptr<WarpMagicSircle>& Obj) {
	}
}
//end basecross
