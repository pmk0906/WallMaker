#include "stdafx.h"
#include "Project.h"

////威力１の一般弾
namespace basecross {
	void EnemyBullet::OnCreate()
	{
		Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
		spanMat.affineTransformation(
			Vec3(1.0f, 1.0f, 1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f)
		);

		//描画
		auto ptrDraw = AddComponent<PNTStaticModelDraw>();
		ptrDraw->SetMeshResource(L"BULLET_MESH");
		ptrDraw->SetMeshToTransformMatrix(spanMat);

		// 衝突判定
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetAfterCollision(AfterCollision::None);

		AddTag(L"EnemyBullet");

		Initialize();

		auto myTrans = GetComponent<Transform>();

		auto my_Scale = myTrans->GetScale();

		myTrans->SetScale(0.7f, 0.7f, 0.7f);
	}

	void EnemyBullet::OnUpdate()
	{
		auto gm = GameManager::GetInstance();
		if (gm->GetClearFlgChanged() == false)
		{
			auto &app = App::GetApp();
			auto delta = app->GetElapsedTime();

			m_DieTime += delta;

			BulletMove();
			Die();
			SetMaxSpeed();
			SetColor();

			if (flg_reflect == false)
			{
				GenerateFire(2, Vec3(1.0f, 1.0f, 1.0f));
			}
			else
			{
				GenerateFireBlue(2, Vec3(1.0f, 1.0f, 1.0f));
			}
		}
	}

	void EnemyBullet::Initialize()
	{
		m_BulletSpeed = 15.0f;
		m_Attack = 1.0f;
		m_DieTime = 0.0f;
		m_ReflectTime = 0.0f;

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

	void EnemyBullet::SetColor()
	{
		Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
		spanMat.affineTransformation(
			Vec3(1.0f, 1.0f, 1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f)
		);

		if (flg_reflect)
		{
			auto ptrDraw = AddComponent<PNTStaticModelDraw>();

			ptrDraw->SetMeshResource(L"BLUE_BULLET_MESH");
			ptrDraw->SetMeshToTransformMatrix(spanMat);
		}
	}

	void EnemyBullet::GenerateFire(int GenerateNum, Vec3 MoveSpeed)
	{
		auto ptrTrans = GetComponent<Transform>();
		auto PtrFire = GetStage()->GetSharedGameObject<MultiFire>(L"MultiFire", false);
		if (PtrFire) {
			PtrFire->InsertFire(GetComponent<Transform>()->GetPosition(), GenerateNum, MoveSpeed);
		}
	}

	void EnemyBullet::GenerateFireBlue(int GenerateNum, Vec3 MoveSpeed)
	{
		auto ptrTrans = GetComponent<Transform>();
		auto PtrFire = GetStage()->GetSharedGameObject<MultiFireBlue>(L"MultiFireBlue", false);
		if (PtrFire) {
			PtrFire->InsertFire(GetComponent<Transform>()->GetPosition(), GenerateNum, MoveSpeed);
		}
	}

	//当たった瞬間
	void EnemyBullet::OnCollisionEnter(shared_ptr<GameObject>& other)
	{
		// 当たったのがプレイヤーなら
		if (auto player = dynamic_pointer_cast<Player>(other))
		{
			if (flg_reflect == false)
			{
				player->Damage(ATTACK);

				auto ptrXA = App::GetApp()->GetXAudio2Manager();
				ptrXA->Start(WstringKey::SE_PlayerDamage, 0, 1.0f);
			}

			SetDrawActive(false);
			SetUpdateActive(false);
		}

		//　あたったのが壁なら
		if (auto magicWall = dynamic_pointer_cast<MagicWall>(other))
		{
			auto wallTrans = magicWall->GetComponent<Transform>();
			auto myTrans = GetComponent<Transform>();

			SetDir(Reflect(wallTrans->GetForword(), dir));

			auto ptrXA = App::GetApp()->GetXAudio2Manager();
			ptrXA->Start(WstringKey::SE_Reflection, 0, 1.0f);

			if (flg_reflect)
			{
				m_BulletSpeed += 5.0f;
				m_Attack += 1.0f;
			}

			flg_reflect = true;

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
		
		if (auto reflectWall = dynamic_pointer_cast<StageRefrectWall>(other))
		{
			auto wallTrans = reflectWall->GetComponent<Transform>();
			auto myTrans = GetComponent<Transform>();

			auto pos = myTrans->GetPosition();

			if (flg_reflect)
			{
				pos -= 0.1f;

				SetDir(Reflect(wallTrans->GetForword(), dir));

				m_BulletSpeed += 5.0f;
				m_Attack += 1.0f;
			}

			myTrans->SetPosition(pos);
		}

		if (auto stageWall = dynamic_pointer_cast<StageWall>(other))
		{
			SetDrawActive(false);
			SetUpdateActive(false);
		}

		if (auto cannon = dynamic_pointer_cast<Cannon>(other))
		{
			SetDrawActive(false);
			SetUpdateActive(false);
		}

		if (auto breakWall = dynamic_pointer_cast<BreakWall>(other))
		{
			if (flg_reflect)
			{
				breakWall->Damage(m_Attack);

				auto ptrXA = App::GetApp()->GetXAudio2Manager();
				ptrXA->Start(WstringKey::SE_BreakStageWall, 0, 1.0f);
			}

			SetDrawActive(false);
			SetUpdateActive(false);
		}
	}
}
