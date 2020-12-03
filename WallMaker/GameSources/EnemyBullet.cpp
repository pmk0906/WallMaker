#include "stdafx.h"
#include "Project.h"

////à–óÕÇPÇÃàÍî íe
namespace basecross {
	void EnemyBullet::OnCreate()
	{
		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_DODECAHEDRON");

		// è’ìÀîªíË
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

		reverse_BulletVec = bullet * -1.0f; // ÉxÉNÉgÉãÇÃå¸Ç´ÇãtÇ…Ç∑ÇÈ

		projection = dot(reverse_BulletVec, wall); // ì‡êœÇégÇ¡ÇƒéÀâeÇÃí∑Ç≥ÇãÅÇﬂÇÈ

		length = projection * wall; // éÀâeÇÃí∑Ç≥

		reflection = length * 2.0f; // éÀâeÇÃí∑Ç≥ÇÇQî{Ç∑ÇÈ

		newDir = reflection + bullet; // Ç∑Ç◊ÇƒÇÃÉxÉNÉgÉãÇë´Ç∑

		return newDir.normalize();
	}

	void EnemyBullet::SetMaxSpeed()
	{
		if (m_BulletSpeed >= MAX_SPEED)
		{
			m_BulletSpeed = MAX_SPEED;
		}
	}

	//ìñÇΩÇ¡ÇΩèuä‘
	void EnemyBullet::OnCollisionEnter(shared_ptr<GameObject>& other)
	{
		// ìñÇΩÇ¡ÇΩÇÃÇ™ÉvÉåÉCÉÑÅ[Ç»ÇÁ
		if (auto player = dynamic_pointer_cast<Player>(other))
		{
			player->Damage(ATTACK);

			auto ptrXA = App::GetApp()->GetXAudio2Manager();
			ptrXA->Start(WstringKey::SE_PlayerDamage, 0, 1.0f);

			SetDrawActive(false);
			SetUpdateActive(false);
		}

		//Å@Ç†ÇΩÇ¡ÇΩÇÃÇ™ï«Ç»ÇÁ
		if (auto magicWall = dynamic_pointer_cast<MagicWall>(other))
		{
			auto wallTrans = magicWall->GetComponent<Transform>();
			auto myTrans = GetComponent<Transform>();

			SetDir(Reflect(wallTrans->GetForword(), dir));

			auto ptrXA = App::GetApp()->GetXAudio2Manager();
			ptrXA->Start(WstringKey::SE_Reflection, 0, 1.0f);

			flg_reflect = true;

			m_BulletSpeed += 5.0f;
			m_Attack += 1.0f;

			magicWall->Damage(m_Attack);
		}

		//ìñÇΩÇ¡ÇΩÇÃÇ™ìGÇ»ÇÁ
		if (auto enemy = dynamic_pointer_cast<EnemyFirst>(other))
		{
			if (flg_reflect)
			{
				enemy->Damage(m_Attack);

				auto ptrXA = App::GetApp()->GetXAudio2Manager();
				ptrXA->Start(WstringKey::SE_EnemyDamage, 0, 1.0f);
			}

			if (m_DieTime >= 0.1f)
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

				auto ptrXA = App::GetApp()->GetXAudio2Manager();
				ptrXA->Start(WstringKey::SE_EnemyDamage, 0, 1.0f);
			}

			if (m_DieTime >= 0.1f)
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

				auto ptrXA = App::GetApp()->GetXAudio2Manager();
				ptrXA->Start(WstringKey::SE_EnemyDamage, 0, 1.0f);
			}

			if (m_DieTime >= 0.1f)
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

				auto ptrXA = App::GetApp()->GetXAudio2Manager();
				ptrXA->Start(WstringKey::SE_EnemyDamage, 0, 1.0f);
			}

			if (m_DieTime >= 0.1f)
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

				auto ptrXA = App::GetApp()->GetXAudio2Manager();
				ptrXA->Start(WstringKey::SE_EnemyDamage, 0, 1.0f);
			}

			if (m_DieTime >= 0.1f)
			{
				SetDrawActive(false);
				SetUpdateActive(false);
			}
		}
		
		//if (auto stageWall = dynamic_pointer_cast<StageRefrectWall>(other))
		//{
		//	auto wallTrans = stageWall->GetComponent<Transform>();

		//	if (flg_reflect)
		//	{
		//		
		//	}
		//	SetDir(Reflect(wallTrans->GetForword(), dir));
		//	//SetDrawActive(false);
		//	//SetUpdateActive(false);

		//}
		if (auto stageWall = dynamic_pointer_cast<StageWall>(other))
		{
			SetDrawActive(false);
			SetUpdateActive(false);

		}
	}
}
