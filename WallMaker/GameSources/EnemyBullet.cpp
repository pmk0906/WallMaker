#include "stdafx.h"
#include "Project.h"

////威力１の一般弾
namespace basecross {
	void EnemyBullet::OnCreate()
	{
		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_SPHERE");

		// 衝突判定
		auto ptrColl = AddComponent<CollisionSphere>();
		ptrColl->SetAfterCollision(AfterCollision::None);

		AddTag(L"EnemyBullet");

		Initialize();
	}

	void EnemyBullet::OnUpdate()
	{
		auto &app = App::GetApp();
		auto delta = app->GetElapsedTime();

		m_DieTime += delta;

		BulletMove();
		Die();
	}

	void EnemyBullet::Initialize()
	{
		m_BulletSpeed = 15.0f;
		m_Attack = 1.0f;
		m_DieTime = 0.0f;
	}

	void EnemyBullet::BulletMove()
	{
		auto &app = App::GetApp();
		auto delta = app->GetElapsedTime();

		auto transComp = GetComponent<Transform>();
		auto pos = transComp->GetPosition();

		pos += m_BulletSpeed * dir * delta;

		transComp->SetPosition(pos);
	}

	void EnemyBullet::Die()
	{
		if (m_DieTime >= 3.0f)
		{
			SetDrawActive(false);
			SetUpdateActive(false);
		}
	}

	//当たった瞬間
	void EnemyBullet::OnCollisionEnter(shared_ptr<GameObject>& other)
	{
		// 当たったのがプレイヤーなら
		if (auto player = dynamic_pointer_cast<Player>(other))
		{
			SetDrawActive(false);
			SetUpdateActive(false);
		}
	}
}
