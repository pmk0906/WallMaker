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
			Vec3(1.0f, 1.0f, 1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, -0.5f, 0.0f)
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
		ptrMyTrans->SetRotation(Vec3(0.0f,XMConvertToRadians(180.0f),0.0f));
		ptrMyTrans->SetPosition(Vec3(0.0f, 0.5f, 2.5f));
	}

	void EnemyShield::OnUpdate()
	{
		Die();
	}

	void EnemyShield::Initialize()
	{
		m_Hp = 3.0f;
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
			SetDrawActive(false);
			SetUpdateActive(false);
		}
	}

	void EnemyShield::DirectDie()
	{
		SetDrawActive(false);
		SetUpdateActive(false);
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
			Vec3(0.0f, -0.5f, 0.0f)
		);

		auto drawComp = AddComponent<BcPNTnTStaticModelDraw>();
		drawComp->SetMeshResource(L"SHELD_MESH");

		// 衝突判定
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetAfterCollision(AfterCollision::None);
		//ptrColl->SetDrawActive(true);

		AddTag(L"PatrolShield");

		Initialize();

		auto myTrans = GetComponent<Transform>();
		myTrans->SetParent(m_Parent->GetThis<GameObject>());

		auto ptrMyTrans = AddComponent<Transform>();

		ptrMyTrans->SetScale(Vec3(3.0f, 1.0f, 2.0f));
		ptrMyTrans->SetRotation(Vec3(0.0f, XMConvertToRadians(180.0f), 0.0f));
		ptrMyTrans->SetPosition(Vec3(0.0f, 0.5f, 2.5f));
	}

	void PatrolShield::OnUpdate()
	{
		Die();
	}

	void PatrolShield::Initialize()
	{
		m_Hp = 3.0f;
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
			SetDrawActive(false);
			SetUpdateActive(false);
		}
	}

	void PatrolShield::DirectDie()
	{
		SetDrawActive(false);
		SetUpdateActive(false);
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
			Vec3(0.0f, -0.5f, 0.0f)
		);

		auto drawComp = AddComponent<BcPNTnTStaticModelDraw>();
		drawComp->SetMeshResource(L"SHELD_MESH");

		// 衝突判定
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetAfterCollision(AfterCollision::None);
		//ptrColl->SetDrawActive(true);

		AddTag(L"UPPatrolShield");

		Initialize();

		auto myTrans = GetComponent<Transform>();
		myTrans->SetParent(m_Parent->GetThis<GameObject>());

		auto ptrMyTrans = AddComponent<Transform>();

		ptrMyTrans->SetScale(Vec3(3.0f, 1.0f, 2.0f));
		ptrMyTrans->SetRotation(Vec3(0.0f, XMConvertToRadians(180.0f), 0.0f));
		ptrMyTrans->SetPosition(Vec3(0.0f, 0.5f, 2.5f));
	}

	void UPPatrolShield::OnUpdate()
	{
		Die();
	}

	void UPPatrolShield::Initialize()
	{
		m_Hp = 3.0f;
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
			SetDrawActive(false);
			SetUpdateActive(false);
		}
	}

	void UPPatrolShield::DirectDie()
	{
		SetDrawActive(false);
		SetUpdateActive(false);
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
			Vec3(0.0f, -0.5f, 0.0f)
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
		ptrMyTrans->SetPosition(Vec3(0.0f, 0.5f, 2.5f));
	}

	void RapidShield::OnUpdate()
	{
		Die();
	}

	void RapidShield::Initialize()
	{
		m_Hp = 3.0f;
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
			SetDrawActive(false);
			SetUpdateActive(false);
		}
	}

	void RapidShield::DirectDie()
	{
		SetDrawActive(false);
		SetUpdateActive(false);
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
			Vec3(0.0f, -0.5f, 0.0f)
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
	}

	void DangerShield::Initialize()
	{
		m_Hp = 6.0f;
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
			SetDrawActive(false);
			SetUpdateActive(false);
		}
	}

	void DangerShield::DirectDie()
	{
		SetDrawActive(false);
		SetUpdateActive(false);
	}
}
