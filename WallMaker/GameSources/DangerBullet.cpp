#include "stdafx.h"
#include "Project.h"

////威力２の強力な弾
namespace basecross {
	void DangerBullet::OnCreate()
	{
		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_DODECAHEDRON");
		drawComp->SetDiffuse(Col4(1.0f, 0.0f, 0.0f, 1.0f));

		// 衝突判定
		auto ptrColl = AddComponent<CollisionSphere>();
		ptrColl->SetAfterCollision(AfterCollision::None);

		AddTag(L"EnemyBullet");

		Initialize();
		auto myTrans = GetComponent<Transform>();

		auto my_Scale = myTrans->GetScale();

		myTrans->SetScale(0.7f, 0.7f, 0.7f);
	}

	void DangerBullet::OnUpdate()
	{
		auto &app = App::GetApp();
		auto delta = app->GetElapsedTime();

		m_DieTime += delta;

		BulletMove();
		Die();
		SetMaxSpeed();
		SetColor();
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

		reverse_BulletVec = bullet * -1.0f; // ベクトルの向きを逆にする

		projection = dot(reverse_BulletVec, wall); // 内積を使って射影の長さを求める

		length = projection * wall; // 射影の長さ

		reflection = length * 2.0f; // 射影の長さを２倍する

		newDir = reflection + bullet; // すべてのベクトルを足す

		return newDir.normalize();
	}

	void DangerBullet::SetMaxSpeed()
	{
		if (m_BulletSpeed >= MAX_SPEED)
		{
			m_BulletSpeed = MAX_SPEED;
		}
	}

	void DangerBullet::SetColor()
	{
		if (m_ReflectCount <= 1)
		{
			auto drawComp = AddComponent<PNTStaticDraw>();

			drawComp->SetDiffuse(Col4(1.0f, 1.0f, 1.0, 1.0f));
		}
	}

	//当たった瞬間
	void DangerBullet::OnCollisionEnter(shared_ptr<GameObject>& other)
	{
		// 当たったのがプレイヤーなら
		if (auto player = dynamic_pointer_cast<Player>(other))
		{
			player->Damage(ATTACK);

			auto ptrXA = App::GetApp()->GetXAudio2Manager();
			ptrXA->Start(WstringKey::SE_PlayerDamage, 0, 1.0f);

			SetDrawActive(false);
			SetUpdateActive(false);
		}

		//　あたったのが壁なら
		if (auto magicWall = dynamic_pointer_cast<MagicWall>(other))
		{
			auto wallTrans = magicWall->GetComponent<Transform>();
			auto myTrans = GetComponent<Transform>();

			flg_reflect = true;

			m_ReflectCount -= 1;

			if (m_ReflectCount <= 0)
			{
				SetDir(Reflect(wallTrans->GetForword(), dir));

				auto ptrXA = App::GetApp()->GetXAudio2Manager();
				ptrXA->Start(WstringKey::SE_Reflection, 0, 1.0f);

				m_BulletSpeed += 5.0f;
				m_Attack += 1.0f;
			}

			else
			{
				auto ptrXA = App::GetApp()->GetXAudio2Manager();
				ptrXA->Start(WstringKey::SE_BreakWall, 0, 1.0f);
			}

			magicWall->Damage(m_Attack);
		}

		//　あたったのがシールドなら
		if (auto shield = dynamic_pointer_cast<EnemyShield>(other))
		{
			if (flg_reflect)
			{
				shield->Damage(m_Attack);

				SetDrawActive(false);
				SetUpdateActive(false);
			}
		}

		//　あたったのがシールドなら
		if (auto shield = dynamic_pointer_cast<PatrolShield>(other))
		{
			if (flg_reflect)
			{
				shield->Damage(m_Attack);

				SetDrawActive(false);
				SetUpdateActive(false);
			}
		}

		//　あたったのがシールドなら
		if (auto shield = dynamic_pointer_cast<UPPatrolShield>(other))
		{
			if (flg_reflect)
			{
				shield->Damage(m_Attack);

				SetDrawActive(false);
				SetUpdateActive(false);
			}
		}

		//　あたったのがシールドなら
		if (auto shield = dynamic_pointer_cast<RapidShield>(other))
		{
			if (flg_reflect)
			{
				shield->Damage(m_Attack);

				SetDrawActive(false);
				SetUpdateActive(false);
			}
		}

		//　あたったのがシールドなら
		if (auto shield = dynamic_pointer_cast<DangerShield>(other))
		{
			if (flg_reflect)
			{
				shield->Damage(m_Attack);

				SetDrawActive(false);
				SetUpdateActive(false);
			}
		}

		//当たったのが敵なら
		if (auto enemy = dynamic_pointer_cast<EnemyFirst>(other))
		{
			if (flg_reflect)
			{
				enemy->Damage(m_Attack);

				auto ptrXA = App::GetApp()->GetXAudio2Manager();
				ptrXA->Start(WstringKey::SE_EnemyDamage, 0, 1.0f);
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

				auto ptrXA = App::GetApp()->GetXAudio2Manager();
				ptrXA->Start(WstringKey::SE_EnemyDamage, 0, 1.0f);
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

				auto ptrXA = App::GetApp()->GetXAudio2Manager();
				ptrXA->Start(WstringKey::SE_EnemyDamage, 0, 1.0f);
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

				auto ptrXA = App::GetApp()->GetXAudio2Manager();
				ptrXA->Start(WstringKey::SE_EnemyDamage, 0, 1.0f);
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

				auto ptrXA = App::GetApp()->GetXAudio2Manager();
				ptrXA->Start(WstringKey::SE_EnemyDamage, 0, 1.0f);
			}

			if (m_DieTime >= 0.3f)
			{
				SetDrawActive(false);
				SetUpdateActive(false);
			}
		}

		if (auto stageWall = dynamic_pointer_cast<StageWall>(other))
		{
			//auto wallTrans = stageWall->GetComponent<Transform>();

			//SetDir(Reflect(wallTrans->GetForword(), dir));

			SetDrawActive(false);
			SetUpdateActive(false);
		}

	}
}