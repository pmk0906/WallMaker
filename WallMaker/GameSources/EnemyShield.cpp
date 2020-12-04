#include "stdafx.h"
#include "Project.h"

////à–óÕÇPÇÃàÍî íe
namespace basecross {
	void EnemyShield::OnCreate()
	{
		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_CUBE");

		// è’ìÀîªíË
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
