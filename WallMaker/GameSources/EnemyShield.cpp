#include "stdafx.h"
#include "Project.h"

////�З͂P�̈�ʒe
namespace basecross {
	void EnemyShield::OnCreate()
	{
		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_CUBE");

		// �Փ˔���
		auto ptrColl = AddComponent<CollisionSphere>();
		ptrColl->SetAfterCollision(AfterCollision::None);

		AddTag(L"EnemyBullet");

		Initialize();

		auto myTrans = GetComponent<Transform>();
	}

	void EnemyShield::OnUpdate()
	{
		
	}

	void EnemyShield::Initialize()
	{

	}

	Vec3 EnemyShield::GetPosition() const
	{
		return GetComponent<Transform>()->GetPosition();
	}
