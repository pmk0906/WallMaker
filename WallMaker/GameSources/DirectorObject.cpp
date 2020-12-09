/*!
@file Character.cpp
@brief �L�����N�^�[�Ȃǎ���
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

	void WarpMagicSircle::ClearAndDelete()
	{
		if (m_Alpha <= 0.0f)
		{
			auto gm = GameManager::GetInstance();
			gm->SetMagicSircleMoved(true);
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
