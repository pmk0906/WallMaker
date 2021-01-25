#include "stdafx.h"
#include "Project.h"
#include "EnemyShield.h"

////威力１の一般弾
namespace basecross {
	EnemyShield::EnemyShield(
		const shared_ptr<Stage>& StagePtr,
		const shared_ptr<GameObject>& Parent
	) :
		GameObject(StagePtr),
		m_Parent(Parent)
	{}
	//EnemyShield::~EnemyShield() {}

	void EnemyShield::OnCreate()
	{
		Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
		spanMat.affineTransformation(
			Vec3(1.0f, 1.0f, 2.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f)
		);

		auto drawComp = AddComponent<BcPNTnTStaticModelDraw>();
		drawComp->SetMeshResource(L"SHELD_MESH");

		// 衝突判定
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetAfterCollision(AfterCollision::None);
		//ptrColl->SetDrawActive(true);

		AddTag(L"EnemyShield");
		//タグをつける
		//AddTag(WstringKey::Tag_DrawActiveFalse);

		Initialize();

		auto myTrans = GetComponent<Transform>();
		myTrans->SetParent(m_Parent->GetThis<GameObject>());

		auto ptrMyTrans = AddComponent<Transform>();

		ptrMyTrans->SetScale(Vec3(3.0f, 1.0f, 1.0f));
		ptrMyTrans->SetRotation(Vec3(0.0f,XMConvertToRadians(180.0f),0.0f));
		ptrMyTrans->SetPosition(Vec3(0.0f, 0.0f, 2.5f));
	}

	void EnemyShield::OnUpdate()
	{
		Die();
		SetColor();
		//FireEffect();
	}

	void EnemyShield::Initialize()
	{
		m_Hp = 3.0f;
	}

	float EnemyShield::GetHP() const
	{
		return m_Hp;
	}

	Vec3 EnemyShield::GetPosition() const
	{
		return GetComponent<Transform>()->GetPosition();
	}

	void EnemyShield::Damage(float damage)
	{
		m_Hp -= damage;
	}

	void EnemyShield::Die()
	{
		if (m_Hp <= 0.0f)
		{
			//SetDrawActive(false);
			//SetUpdateActive(false);
			GetStage()->RemoveGameObject<EnemyShield>(GetThis<EnemyShield>());

			GenerataFire(30, Vec3(30.0f));
		}
	}

	void EnemyShield::DirectDie()
	{
		//SetDrawActive(false);
		//SetUpdateActive(false);
		GetStage()->RemoveGameObject<EnemyShield>(GetThis<EnemyShield>());

	}

	void EnemyShield::SetColor()
	{
		if (m_Hp == 1.0f)
		{
			Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
			spanMat.affineTransformation(
				Vec3(1.0f, 1.0f, 2.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f)
			);

			auto drawComp = AddComponent<BcPNTnTStaticModelDraw>();
			drawComp->SetMeshResource(L"RED_SHIELD");
		}
		else if (m_Hp == 2.0f)
		{
			Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
			spanMat.affineTransformation(
				Vec3(1.0f, 1.0f, 2.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f)
			);

			auto drawComp = AddComponent<BcPNTnTStaticModelDraw>();
			drawComp->SetMeshResource(L"ORANGE_SHIELD");
		}
		else if (m_Hp == 3.0f)
		{
			Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
			spanMat.affineTransformation(
				Vec3(1.0f, 1.0f, 2.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f)
			);

			auto drawComp = AddComponent<BcPNTnTStaticModelDraw>();
			drawComp->SetMeshResource(L"YELLOW_SHIELD");
		}
	}

	void EnemyShield::GenerataFire(int GenerateNum, Vec3 MoveSpeed)
	{
		auto myPos = GetComponent<Transform>()->GetWorldPosition();
		auto PtrFire = GetStage()->GetSharedGameObject<MultiFire>(L"MultiFire", false);
		if (PtrFire) {
			PtrFire->InsertFire(myPos , GenerateNum, MoveSpeed);
		}
	}

	PatrolShield::PatrolShield(
		const shared_ptr<Stage>& StagePtr,
		const shared_ptr<GameObject>& Parent
	) :
		GameObject(StagePtr),
		m_Parent(Parent)
	{}
	//EnemyShield::~EnemyShield() {}

	void PatrolShield::OnCreate()
	{
		Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
		spanMat.affineTransformation(
			Vec3(1.0f, 1.0f, 1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f)
		);

		auto drawComp = AddComponent<BcPNTnTStaticModelDraw>();
		drawComp->SetMeshResource(L"SHELD_MESH");

		// 衝突判定
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetAfterCollision(AfterCollision::None);
		//ptrColl->SetDrawActive(true);

		AddTag(L"PatrolShield");
		//タグをつける
		//AddTag(WstringKey::Tag_DrawActiveFalse);

		Initialize();

		auto myTrans = GetComponent<Transform>();
		myTrans->SetParent(m_Parent->GetThis<GameObject>());

		auto ptrMyTrans = AddComponent<Transform>();

		ptrMyTrans->SetScale(Vec3(3.0f, 1.0f, 2.0f));
		ptrMyTrans->SetRotation(Vec3(0.0f, XMConvertToRadians(180.0f), 0.0f));
		ptrMyTrans->SetPosition(Vec3(0.0f, 0.0f, 2.5f));
	}

	void PatrolShield::OnUpdate()
	{
		Die();
		SetColor();
	}

	void PatrolShield::Initialize()
	{
		m_Hp = 3.0f;
	}

	float PatrolShield::GetHP() const
	{
		return m_Hp;
	}

	Vec3 PatrolShield::GetPosition() const
	{
		return GetComponent<Transform>()->GetPosition();
	}

	void PatrolShield::Damage(float damage)
	{
		m_Hp -= damage;
	}

	void PatrolShield::Die()
	{
		if (m_Hp <= 0.0f)
		{
			//SetDrawActive(false);
			//SetUpdateActive(false);
			GetStage()->RemoveGameObject<PatrolShield>(GetThis<PatrolShield>());

			GenerataFire(50, Vec3(30.0f));

		}
	}

	void PatrolShield::DirectDie()
	{
		//SetDrawActive(false);
		//SetUpdateActive(false);
		GetStage()->RemoveGameObject<PatrolShield>(GetThis<PatrolShield>());
	}

	void PatrolShield::SetColor()
	{
		if (m_Hp == 1.0f)
		{
			Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
			spanMat.affineTransformation(
				Vec3(1.0f, 1.0f, 2.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f)
			);

			auto drawComp = AddComponent<BcPNTnTStaticModelDraw>();
			drawComp->SetMeshResource(L"RED_SHIELD");
		}
		else if (m_Hp == 2.0f)
		{
			Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
			spanMat.affineTransformation(
				Vec3(1.0f, 1.0f, 2.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f)
			);

			auto drawComp = AddComponent<BcPNTnTStaticModelDraw>();
			drawComp->SetMeshResource(L"ORANGE_SHIELD");
		}
		else if (m_Hp == 3.0f)
		{
			Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
			spanMat.affineTransformation(
				Vec3(1.0f, 1.0f, 2.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f)
			);

			auto drawComp = AddComponent<BcPNTnTStaticModelDraw>();
			drawComp->SetMeshResource(L"YELLOW_SHIELD");
		}
	}

	void PatrolShield::GenerataFire(int GenerateNum, Vec3 MoveSpeed)
	{
		auto ptrTrans = GetComponent<Transform>();
		auto PtrFire = GetStage()->GetSharedGameObject<MultiFire>(L"MultiFire", false);
		if (PtrFire) {
			PtrFire->InsertFire(GetComponent<Transform>()->GetPosition(), GenerateNum, MoveSpeed);
		}
	}

	UPPatrolShield::UPPatrolShield(
		const shared_ptr<Stage>& StagePtr,
		const shared_ptr<GameObject>& Parent
	) :
		GameObject(StagePtr),
		m_Parent(Parent)
	{}
	//EnemyShield::~EnemyShield() {}

	void UPPatrolShield::OnCreate()
	{
		Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
		spanMat.affineTransformation(
			Vec3(1.0f, 1.0f, 1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f)
		);

		auto drawComp = AddComponent<BcPNTnTStaticModelDraw>();
		drawComp->SetMeshResource(L"SHELD_MESH");

		// 衝突判定
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetAfterCollision(AfterCollision::None);
		//ptrColl->SetDrawActive(true);

		AddTag(L"UPPatrolShield");
		//タグをつける
		//AddTag(WstringKey::Tag_DrawActiveFalse);

		Initialize();

		auto myTrans = GetComponent<Transform>();
		myTrans->SetParent(m_Parent->GetThis<GameObject>());

		auto ptrMyTrans = AddComponent<Transform>();

		ptrMyTrans->SetScale(Vec3(3.0f, 1.0f, 2.0f));
		ptrMyTrans->SetRotation(Vec3(0.0f, XMConvertToRadians(180.0f), 0.0f));
		ptrMyTrans->SetPosition(Vec3(0.0f, 0.0f, 2.5f));
	}

	void UPPatrolShield::OnUpdate()
	{
		Die();
		SetColor();
	}

	void UPPatrolShield::Initialize()
	{
		m_Hp = 3.0f;
	}

	float UPPatrolShield::GetHP() const
	{
		return m_Hp;
	}

	Vec3 UPPatrolShield::GetPosition() const
	{
		return GetComponent<Transform>()->GetPosition();
	}

	void UPPatrolShield::Damage(float damage)
	{
		m_Hp -= damage;
	}

	void UPPatrolShield::Die()
	{
		if (m_Hp <= 0.0f)
		{
			//SetDrawActive(false);
			//SetUpdateActive(false);
			GetStage()->RemoveGameObject<UPPatrolShield>(GetThis<UPPatrolShield>());

			GenerataFire(50, Vec3(30.0f));

		}
	}

	void UPPatrolShield::DirectDie()
	{
		//SetDrawActive(false);
		//SetUpdateActive(false);
		GetStage()->RemoveGameObject<UPPatrolShield>(GetThis<UPPatrolShield>());
	}

	void UPPatrolShield::SetColor()
	{
		if (m_Hp == 1.0f)
		{
			Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
			spanMat.affineTransformation(
				Vec3(1.0f, 1.0f, 2.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f)
			);

			auto drawComp = AddComponent<BcPNTnTStaticModelDraw>();
			drawComp->SetMeshResource(L"RED_SHIELD");
		}
		else if (m_Hp == 2.0f)
		{
			Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
			spanMat.affineTransformation(
				Vec3(1.0f, 1.0f, 2.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f)
			);

			auto drawComp = AddComponent<BcPNTnTStaticModelDraw>();
			drawComp->SetMeshResource(L"ORANGE_SHIELD");
		}
		else if (m_Hp == 3.0f)
		{
			Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
			spanMat.affineTransformation(
				Vec3(1.0f, 1.0f, 2.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f)
			);

			auto drawComp = AddComponent<BcPNTnTStaticModelDraw>();
			drawComp->SetMeshResource(L"YELLOW_SHIELD");
		}
	}

	void UPPatrolShield::GenerataFire(int GenerateNum, Vec3 MoveSpeed)
	{
		auto myPos = GetComponent<Transform>()->GetWorldPosition();
		auto PtrFire = GetStage()->GetSharedGameObject<MultiFire>(L"MultiFire", false);
		if (PtrFire) {
			PtrFire->InsertFire(myPos, GenerateNum, MoveSpeed);
		}
	}

	RapidShield::RapidShield(
		const shared_ptr<Stage>& StagePtr,
		const shared_ptr<GameObject>& Parent
	) :
		GameObject(StagePtr),
		m_Parent(Parent)
	{}
	//EnemyShield::~EnemyShield() {}

	void RapidShield::OnCreate()
	{
		Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
		spanMat.affineTransformation(
			Vec3(1.0f, 1.0f, 1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f)
		);

		auto drawComp = AddComponent<BcPNTnTStaticModelDraw>();
		drawComp->SetMeshResource(L"SHELD_MESH");

		// 衝突判定
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetAfterCollision(AfterCollision::None);
		//ptrColl->SetDrawActive(true);

		AddTag(L"EnemyShield");
		//タグをつける
		//AddTag(WstringKey::Tag_DrawActiveFalse);

		Initialize();

		auto myTrans = GetComponent<Transform>();
		myTrans->SetParent(m_Parent->GetThis<GameObject>());

		auto ptrMyTrans = AddComponent<Transform>();

		ptrMyTrans->SetScale(Vec3(3.0f, 1.0f, 2.0f));
		ptrMyTrans->SetRotation(Vec3(0.0f, XMConvertToRadians(180.0f), 0.0f));
		ptrMyTrans->SetPosition(Vec3(0.0f, 0.0f, 2.5f));
	}

	void RapidShield::OnUpdate()
	{
		Die();
		SetColor();
	}

	void RapidShield::Initialize()
	{
		m_Hp = 3.0f;
	}

	float RapidShield::GetHP() const
	{
		return m_Hp;
	}

	Vec3 RapidShield::GetPosition() const
	{
		return GetComponent<Transform>()->GetPosition();
	}

	void RapidShield::Damage(float damage)
	{
		m_Hp -= damage;
	}

	void RapidShield::Die()
	{
		if (m_Hp <= 0.0f)
		{
			//SetDrawActive(false);
			//SetUpdateActive(false);
			GetStage()->RemoveGameObject<RapidShield>(GetThis<RapidShield>());

			GenerataFire(50, Vec3(30.0f));
		}
	}

	void RapidShield::DirectDie()
	{
		//SetDrawActive(false);
		//SetUpdateActive(false);
		GetStage()->RemoveGameObject<RapidShield>(GetThis<RapidShield>());
	}

	void RapidShield::SetColor()
	{
		if (m_Hp == 1.0f)
		{
			Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
			spanMat.affineTransformation(
				Vec3(1.0f, 1.0f, 2.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f)
			);

			auto drawComp = AddComponent<BcPNTnTStaticModelDraw>();
			drawComp->SetMeshResource(L"RED_SHIELD");
		}
		else if (m_Hp == 2.0f)
		{
			Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
			spanMat.affineTransformation(
				Vec3(1.0f, 1.0f, 2.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f)
			);

			auto drawComp = AddComponent<BcPNTnTStaticModelDraw>();
			drawComp->SetMeshResource(L"ORANGE_SHIELD");
		}
		else if (m_Hp == 3.0f)
		{
			Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
			spanMat.affineTransformation(
				Vec3(1.0f, 1.0f, 2.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f)
			);

			auto drawComp = AddComponent<BcPNTnTStaticModelDraw>();
			drawComp->SetMeshResource(L"YELLOW_SHIELD");
		}
	}

	void RapidShield::GenerataFire(int GenerateNum, Vec3 MoveSpeed)
	{
		auto myPos = GetComponent<Transform>()->GetWorldPosition();
		auto PtrFire = GetStage()->GetSharedGameObject<MultiFire>(L"MultiFire", false);
		if (PtrFire) {
			PtrFire->InsertFire(myPos, GenerateNum, MoveSpeed);
		}
	}

	DangerShield::DangerShield(
		const shared_ptr<Stage>& StagePtr,
		const shared_ptr<GameObject>& Parent
	) :
		GameObject(StagePtr),
		m_Parent(Parent)
	{}
	//EnemyShield::~EnemyShield() {}

	void DangerShield::OnCreate()
	{
		Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
		spanMat.affineTransformation(
			Vec3(1.0f, 1.0f, 1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f)
		);

		auto drawComp = AddComponent<BcPNTnTStaticModelDraw>();
		drawComp->SetMeshResource(L"SHELD_MESH");

		// 衝突判定
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetAfterCollision(AfterCollision::None);
		//ptrColl->SetDrawActive(true);

		AddTag(L"EnemyShield");

		Initialize();

		auto myTrans = GetComponent<Transform>();
		myTrans->SetParent(m_Parent->GetThis<GameObject>());

		auto ptrMyTrans = AddComponent<Transform>();

		ptrMyTrans->SetScale(Vec3(3.0f, 1.0f, 2.0f));
		ptrMyTrans->SetRotation(Vec3(0.0f, XMConvertToRadians(180.0f), 0.0f));
		ptrMyTrans->SetPosition(Vec3(0.0f, 0.0f, 3.0f));
	}

	void DangerShield::OnUpdate()
	{
		Die();
		SetColor();
	}

	void DangerShield::Initialize()
	{
		m_Hp = 5.0f;
	}

	float DangerShield::GetHP() const
	{
		return m_Hp;
	}

	Vec3 DangerShield::GetPosition() const
	{
		return GetComponent<Transform>()->GetPosition();
	}

	void DangerShield::Damage(float damage)
	{
		m_Hp -= damage;
	}

	void DangerShield::Die()
	{
		if (m_Hp <= 0.0f)
		{
			//SetDrawActive(false);
			//SetUpdateActive(false);
			GetStage()->RemoveGameObject<DangerShield>(GetThis<DangerShield>());
		}
	}

	void DangerShield::DirectDie()
	{
		//SetDrawActive(false);
		//SetUpdateActive(false);
		GetStage()->RemoveGameObject<DangerShield>(GetThis<DangerShield>());
	}

	void DangerShield::SetColor()
	{
		if (m_Hp == 1.0f)
		{
			Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
			spanMat.affineTransformation(
				Vec3(1.0f, 1.0f, 2.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f)
			);

			auto drawComp = AddComponent<BcPNTnTStaticModelDraw>();
			drawComp->SetMeshResource(L"RED_SHIELD");
		}
		else if (m_Hp == 2.0f)
		{
			Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
			spanMat.affineTransformation(
				Vec3(1.0f, 1.0f, 2.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f)
			);

			auto drawComp = AddComponent<BcPNTnTStaticModelDraw>();
			drawComp->SetMeshResource(L"ORANGE_SHIELD");
		}
		else if (m_Hp == 3.0f)
		{
			Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
			spanMat.affineTransformation(
				Vec3(1.0f, 1.0f, 2.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f)
			);

			auto drawComp = AddComponent<BcPNTnTStaticModelDraw>();
			drawComp->SetMeshResource(L"YELLOW_SHIELD");
		}
		else if (m_Hp == 4.0f)
		{
			Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
			spanMat.affineTransformation(
				Vec3(1.0f, 1.0f, 2.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f)
			);

			auto drawComp = AddComponent<BcPNTnTStaticModelDraw>();
			drawComp->SetMeshResource(L"GREEN_SHIELD");
		}
		else if (m_Hp == 5.0f)
		{
			Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
			spanMat.affineTransformation(
				Vec3(1.0f, 1.0f, 2.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f)
			);

			auto drawComp = AddComponent<BcPNTnTStaticModelDraw>();
			drawComp->SetMeshResource(L"BLUE_SHIELD");
		}
	}

	ReflectShield::ReflectShield(
		const shared_ptr<Stage>& StagePtr,
		const shared_ptr<GameObject>& Parent
	) :
		GameObject(StagePtr),
		m_Parent(Parent)
	{}
	//EnemyShield::~EnemyShield() {}

	void ReflectShield::OnCreate()
	{
		Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
		spanMat.affineTransformation(
			Vec3(1.0f, 1.0f, 2.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f)
		);

		auto drawComp = AddComponent<BcPNTnTStaticModelDraw>();
		drawComp->SetMeshResource(L"SHELD_MESH");

		// 衝突判定
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetAfterCollision(AfterCollision::None);
		//ptrColl->SetDrawActive(true);

		AddTag(L"EnemyShield");
		//タグをつける
		//AddTag(WstringKey::Tag_DrawActiveFalse);

		Initialize();

		auto myTrans = GetComponent<Transform>();
		myTrans->SetParent(m_Parent->GetThis<GameObject>());

		auto ptrMyTrans = AddComponent<Transform>();

		ptrMyTrans->SetScale(Vec3(3.0f, 1.0f, 1.0f));
		ptrMyTrans->SetRotation(Vec3(0.0f, XMConvertToRadians(180.0f), 0.0f));
		ptrMyTrans->SetPosition(Vec3(0.0f, 0.0f, 2.5f));
	}

	void ReflectShield::OnUpdate()
	{
		Die();
		SetColor();
		//FireEffect();
	}

	void ReflectShield::Initialize()
	{
		m_Hp = 3.0f;
	}

	float ReflectShield::GetHP() const
	{
		return m_Hp;
	}

	Vec3 ReflectShield::GetPosition() const
	{
		return GetComponent<Transform>()->GetPosition();
	}

	void ReflectShield::Damage(float damage)
	{
		m_Hp -= damage;
	}

	void ReflectShield::Die()
	{
		if (m_Hp <= 0.0f)
		{
			//SetDrawActive(false);
			//SetUpdateActive(false);
			GetStage()->RemoveGameObject<ReflectShield>(GetThis<ReflectShield>());

			GenerataFire(30, Vec3(30.0f));
		}
	}

	void ReflectShield::DirectDie()
	{
		//SetDrawActive(false);
		//SetUpdateActive(false);
		GetStage()->RemoveGameObject<ReflectShield>(GetThis<ReflectShield>());

	}

	void ReflectShield::SetColor()
	{
		if (m_Hp == 1.0f)
		{
			Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
			spanMat.affineTransformation(
				Vec3(1.0f, 1.0f, 2.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f)
			);

			auto drawComp = AddComponent<BcPNTnTStaticModelDraw>();
			drawComp->SetMeshResource(L"RED_SHIELD");
		}
		else if (m_Hp == 2.0f)
		{
			Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
			spanMat.affineTransformation(
				Vec3(1.0f, 1.0f, 2.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f)
			);

			auto drawComp = AddComponent<BcPNTnTStaticModelDraw>();
			drawComp->SetMeshResource(L"ORANGE_SHIELD");
		}
		else if (m_Hp == 3.0f)
		{
			Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
			spanMat.affineTransformation(
				Vec3(1.0f, 1.0f, 2.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f)
			);

			auto drawComp = AddComponent<BcPNTnTStaticModelDraw>();
			drawComp->SetMeshResource(L"YELLOW_SHIELD");
		}
	}

	void ReflectShield::GenerataFire(int GenerateNum, Vec3 MoveSpeed)
	{
		auto myPos = GetComponent<Transform>()->GetWorldPosition();
		auto PtrFire = GetStage()->GetSharedGameObject<MultiFire>(L"MultiFire", false);
		if (PtrFire) {
			PtrFire->InsertFire(myPos, GenerateNum, MoveSpeed);
		}
	}
}
