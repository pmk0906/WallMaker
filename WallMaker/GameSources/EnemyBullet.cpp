#include "stdafx.h"
#include "Project.h"

////�З͂P�̈�ʒe
namespace basecross {
	void EnemyBullet::OnCreate()
	{
		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_SPHERE");

		// �Փ˔���
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

	//���������u��
	void EnemyBullet::OnCollisionEnter(shared_ptr<GameObject>& other)
	{
		// ���������̂��v���C���[�Ȃ�
		if (auto player = dynamic_pointer_cast<Player>(other))
		{
			player->Damage(m_Attack);

			SetDrawActive(false);
			SetUpdateActive(false);
		}
	}
}
