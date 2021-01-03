/*!
@file Character.cpp
@brief �L�����N�^�[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
	//--------------------------------------------------------------------------------------
	///	�����̉��N���X
	//--------------------------------------------------------------------------------------
	//�\�z�Ɣj��
	MultiFire::MultiFire(shared_ptr<Stage>& StagePtr) :
		MultiParticle(StagePtr)
	{}
	MultiFire::~MultiFire() {}

	//������
	void MultiFire::OnCreate() {
		//���Z�`�揈��������
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
			//�e�p�[�e�B�N���̈ړ����x���w��
			rParticleSprite.m_Velocity = Vec3(
				rParticleSprite.m_LocalPos.x * MoveSpeed.x,
				rParticleSprite.m_LocalPos.y * MoveSpeed.y,
				rParticleSprite.m_LocalPos.z * MoveSpeed.z
			);
			//�F�̎w��
			rParticleSprite.m_Color = Col4(1.0f, 1.0f, 1.0f, 1.0f);
		}
	}

	//--------------------------------------------------------------------------------------
	///	�����̉��N���X
	//--------------------------------------------------------------------------------------
	//�\�z�Ɣj��
	MultiFireBlue::MultiFireBlue(shared_ptr<Stage>& StagePtr) :
		MultiParticle(StagePtr)
	{}
	MultiFireBlue::~MultiFireBlue() {}

	//������
	void MultiFireBlue::OnCreate() {
		//���Z�`�揈��������
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
			//�e�p�[�e�B�N���̈ړ����x���w��
			rParticleSprite.m_Velocity = Vec3(
				rParticleSprite.m_LocalPos.x * MoveSpeed.x,
				rParticleSprite.m_LocalPos.y * MoveSpeed.y,
				rParticleSprite.m_LocalPos.z * MoveSpeed.z
			);
			//�F�̎w��
			rParticleSprite.m_Color = Col4(1.0f, 1.0f, 1.0f, 1.0f);
		}
	}

	//--------------------------------------------------------------------------------------
	///	�ǂ��󂵂����̃G�t�F�N�g
	//--------------------------------------------------------------------------------------
	//�\�z�Ɣj��
	WallBreakEffect::WallBreakEffect(shared_ptr<Stage>& StagePtr) :
		MultiParticle(StagePtr)
	{}
	WallBreakEffect::~WallBreakEffect() {}

	//������
	void WallBreakEffect::OnCreate() {
		
		auto ptrGrav = AddComponent<Gravity>();

		//���Z�`�揈��������
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
			//�e�p�[�e�B�N���̈ړ����x���w��
			rParticleSprite.m_Velocity = Vec3(
				rParticleSprite.m_LocalPos.x * MoveSpeed.x,
				rParticleSprite.m_LocalPos.y * MoveSpeed.y,
				rParticleSprite.m_LocalPos.z * MoveSpeed.z
			);
		}
	}

	//--------------------------------------------------------------------------------------
	///	���˂����Ƃ��̃G�t�F�N�g
	//--------------------------------------------------------------------------------------
	//�\�z�Ɣj��
	ReflectBulletEffect::ReflectBulletEffect(shared_ptr<Stage>& StagePtr) :
		MultiParticle(StagePtr)
	{}
	ReflectBulletEffect::~ReflectBulletEffect() {}

	//������
	void ReflectBulletEffect::OnCreate() {

		//auto ptrGrav = AddComponent<Gravity>();

		//���Z�`�揈��������
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
			//�e�p�[�e�B�N���̈ړ����x���w��
			rParticleSprite.m_Velocity = Vec3(
				rParticleSprite.m_LocalPos.x * MoveSpeed.x,
				rParticleSprite.m_LocalPos.y * MoveSpeed.y,
				rParticleSprite.m_LocalPos.z * MoveSpeed.z
			);
		}
	}

	//--------------------------------------------------------------------------------------
	///	�Q�[���J�n���Ƀv���C���[���o�����o
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

	//	������
	void WarpMagicSircle::OnCreate()
	{
		auto playerPos = GetStage()->GetSharedGameObject<Player>(WstringKey::ShareObj_Player)->GetPosition();
		auto ptrMyTrans = AddComponent<Transform>();
		ptrMyTrans->SetScale(Vec3(7.0f, 0.3f, 7.0f));
		ptrMyTrans->SetRotation(Vec3(0.0f, m_Rotation.y, 0.0f));
		ptrMyTrans->SetPosition(playerPos + m_FirstOffset);

		Mat4x4 spanMat; // ���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
		spanMat.affineTransformation(
			Vec3(0.55f, 0.5f, 5.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(XMConvertToRadians(90.0f), 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, -0.5f)
		);

		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetAfterCollision(AfterCollision::None);
		//ptrColl->SetDrawActive(true);

		//�`�揈��
		auto ptrDraw = AddComponent<BcPNTnTStaticModelDraw>();
		ptrDraw->SetMeshResource(L"MAGICWALL_MESH");
		ptrDraw->SetMeshToTransformMatrix(spanMat);
		ptrDraw->SetLightingEnabled(false);
		ptrDraw->SetModelDiffusePriority(false);
		ptrDraw->SetAlpha(m_Alpha);

		//�`�悷��e�N�X�`����ݒ�
		SetAlphaActive(true);

		//�X�e�[�g�}�V���̍\�z
		m_StateMachine.reset(new StateMachine<WarpMagicSircle>(GetThis<WarpMagicSircle>()));
		//�ŏ��̃X�e�[�g��SeekFarState�ɐݒ�
		m_StateMachine->ChangeState(FirstState::Instance());
	}

	void WarpMagicSircle::OnUpdate()
	{	
		auto gm = GameManager::GetInstance();
		if (gm->GetOpeningCameraMoveEnd() == true)
		{
			//�X�e�[�g�}�V����Update���s��
			//���̒��ŃX�e�[�g�̐؂�ւ����s����
			m_StateMachine->Update();
		}
	}

	//--------------------------------------------------------------------------------------
	//	������Ԃ���~���u�Ԃ܂�
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
	//	�~��Ă��珰�Ŏ~�܂�܂�
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
	//	�~�܂��Ă��������܂�
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
