#include "stdafx.h"
#include "Project.h"

////à–óÕÇPÇÃàÍî íe
namespace basecross {
	void DangerBullet::OnCreate()
	{
		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_SPHERE");
		drawComp->SetDiffuse(Col4(1.0f, 0.0f, 0.0f, 1.0f));

		// è’ìÀîªíË
		auto ptrColl = AddComponent<CollisionSphere>();
		ptrColl->SetAfterCollision(AfterCollision::None);

		AddTag(L"EnemyBullet");

		Initialize();
		auto myTrans = GetComponent<Transform>();
	}

	void DangerBullet::OnUpdate()
	{
		auto &app = App::GetApp();
		auto delta = app->GetElapsedTime();

		m_DieTime += delta;

		BulletMove();
		Die();
		SetMaxSpeed();
	}

	void DangerBullet::Initialize()
	{
		m_ReflectCount = 2;

		m_BulletSpeed = 15.0f;
		m_Attack = 2.0f;
		m_DieTime = 0.0f;

		flg_reflect = false;
	}

	void DangerBullet::BulletMove()
	{
		auto &app = App::GetApp();
		auto delta = app->GetElapsedTime();

		auto transComp = GetComponent<Transform>();
		auto pos = transComp->GetPosition();

		pos += m_BulletSpeed * dir * delta;

		transComp->SetPosition(pos);
	}

	void DangerBullet::Die()
	{
		if (m_DieTime >= 5.0f)
		{
			SetDrawActive(false);
			SetUpdateActive(false);
		}
	}

	void DangerBullet::SetDir(const Vec3& v)
	{
		dir = v;
	}

	Vec3 DangerBullet::GetPosition() const
	{
		return GetComponent<Transform>()->GetPosition();
	}

	Vec3 DangerBullet::Reflect(Vec3 wall, Vec3 bullet)
	{
		/*Vec3 temp = bullet;
		temp.reflect(wall);
		return temp;*/

		Vec3 reverse_BulletVec, newDir, length, reflection;
		float projection;

		reverse_BulletVec = bullet * -1.0f; // ÉxÉNÉgÉãÇÃå¸Ç´ÇãtÇ…Ç∑ÇÈ

		projection = dot(reverse_BulletVec, wall); // ì‡êœÇégÇ¡ÇƒéÀâeÇÃí∑Ç≥ÇãÅÇﬂÇÈ

		length = projection * wall; // éÀâeÇÃí∑Ç≥

		reflection = length * 2.0f; // éÀâeÇÃí∑Ç≥ÇÇQî{Ç∑ÇÈ

		newDir = reflection + bullet; // Ç∑Ç◊ÇƒÇÃÉxÉNÉgÉãÇë´Ç∑

		return newDir.normalize();
	}

	void DangerBullet::SetMaxSpeed()
	{
		if (m_BulletSpeed >= MAX_SPEED)
		{
			m_BulletSpeed = MAX_SPEED;
		}
	}

	//ìñÇΩÇ¡ÇΩèuä‘
	void DangerBullet::OnCollisionEnter(shared_ptr<GameObject>& other)
	{
		// ìñÇΩÇ¡ÇΩÇÃÇ™ÉvÉåÉCÉÑÅ[Ç»ÇÁ
		if (auto player = dynamic_pointer_cast<Player>(other))
		{
			player->Damage(ATTACK);

			SetDrawActive(false);
			SetUpdateActive(false);
		}

		//Å@Ç†ÇΩÇ¡ÇΩÇÃÇ™ï«Ç»ÇÁ
		if (auto magicWall = dynamic_pointer_cast<MagicWall>(other))
		{
			auto wallTrans = magicWall->GetComponent<Transform>();
			auto myTrans = GetComponent<Transform>();

			flg_reflect = true;

			m_ReflectCount -= 1;

			if (m_ReflectCount <= 0)
			{
				SetDir(Reflect(wallTrans->GetForword(), dir));

				m_BulletSpeed += 5.0f;
				m_Attack += 1.0f;
			}

			magicWall->Damage(m_Attack);
		}

		//ìñÇΩÇ¡ÇΩÇÃÇ™ìGÇ»ÇÁ
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

		if (auto dangerEnemy = dynamic_pointer_cast<DangerEnemy>(other))
		{
			if (flg_reflect)
			{
				dangerEnemy->Damage(m_Attack);
			}

			if (m_DieTime >= 0.3f)
			{
				SetDrawActive(false);
				SetUpdateActive(false);
			}
		}
	}
}