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
		auto myTrans = GetComponent<Transform>();
	}

	void EnemyBullet::OnUpdate()
	{
		auto &app = App::GetApp();
		auto delta = app->GetElapsedTime();

		m_DieTime += delta;

		BulletMove();
		Die();
		SetMaxSpeed();
	}

	void EnemyBullet::Initialize()
	{
		m_BulletSpeed = 15.0f;
		m_Attack = 1.0f;
		m_DieTime = 0.0f;

		flg_reflect = false;
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
		if (m_DieTime >= 5.0f)
		{
			SetDrawActive(false);
			SetUpdateActive(false);
		}
	}

	void EnemyBullet::SetDir(const Vec3& v)
	{
		dir = v;
	}

	Vec3 EnemyBullet::GetPosition() const
	{
		return GetComponent<Transform>()->GetPosition();
	}

	Vec3 EnemyBullet::Reflect(Vec3 wall, Vec3 bullet)
	{
		/*Vec3 temp = bullet;
		temp.reflect(wall);
		return temp;*/

		Vec3 reverse_BulletVec, newDir, length, reflection;
		float projection;

		reverse_BulletVec = bullet * -1.0f; // ベクトルの向きを逆にする

		projection = dot(reverse_BulletVec, wall); // 内積を使って射影の長さを求める

		length = projection * wall; // 射影の長さ

		reflection = length * 2.0f; // 射影の長さを２倍する

		newDir = reflection + bullet; // すべてのベクトルを足す

		return newDir.normalize();
	}

	void EnemyBullet::SetMaxSpeed()
	{
		if (m_BulletSpeed >= MAX_SPEED)
		{
			m_BulletSpeed = MAX_SPEED;
		}
	}

	//当たった瞬間
	void EnemyBullet::OnCollisionEnter(shared_ptr<GameObject>& other)
	{
		// 当たったのがプレイヤーなら
		if (auto player = dynamic_pointer_cast<Player>(other))
		{
			player->Damage(ATTACK);

			SetDrawActive(false);
			SetUpdateActive(false);
		}

		//　あたったのが壁なら
		if (auto magicWall = dynamic_pointer_cast<MagicWall>(other))
		{
			auto wallTrans = magicWall->GetComponent<Transform>();
			auto myTrans = GetComponent<Transform>();

			SetDir(Reflect(wallTrans->GetForword(), dir));

			flg_reflect = true;

			m_BulletSpeed += 5.0f;
			m_Attack += 1.0f;
		}

		//当たったのが敵なら
		if (auto enemy = dynamic_pointer_cast<EnemyFirst>(other))
		{
			if (flg_reflect)
			{
				enemy->Damage(m_Attack);
			}

			if (m_DieTime >= 0.3f)
			{
				SetDrawActive(false);
				SetUpdateActive(false);
			}
		}

		if (auto patrolEnemy = dynamic_pointer_cast<PatrolEnemy>(other))
		{
			if (flg_reflect)
			{
				patrolEnemy->Damage(m_Attack);
			}

			if (m_DieTime >= 0.3f)
			{
				SetDrawActive(false);
				SetUpdateActive(false);
			}
		}

		if (auto upDownEnemy = dynamic_pointer_cast<PatrolEnemyUPDown>(other))
		{
			if (flg_reflect)
			{
				upDownEnemy->Damage(m_Attack);
			}

			if (m_DieTime >= 0.3f)
			{
				SetDrawActive(false);
				SetUpdateActive(false);
			}
		}

		if (auto raipidFireEnemy = dynamic_pointer_cast<RapidFireEnemy>(other))
		{
			if (flg_reflect)
			{
				raipidFireEnemy->Damage(m_Attack);
			}

			if (m_DieTime >= 0.3f)
			{
				SetDrawActive(false);
				SetUpdateActive(false);
			}
		}
	}
}
