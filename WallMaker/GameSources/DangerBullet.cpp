#include "stdafx.h"
#include "Project.h"

////威力２の強力な弾
namespace basecross {
	void DangerBullet::OnCreate()
	{
		Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
		spanMat.affineTransformation(
			Vec3(1.0f, 1.0f, 1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, -3.0f, 0.0f)
		);

		//描画
		auto ptrDraw = AddComponent<PNTStaticModelDraw>();
		ptrDraw->SetMeshResource(L"ENEMY_BULLET_DANGER");
		ptrDraw->SetMeshToTransformMatrix(spanMat);

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
		auto gm = GameManager::GetInstance();


		if (gm->GetMoveEnabledFlg() == true)
		{
			auto &app = App::GetApp();
			auto delta = app->GetElapsedTime();

			m_DieTime += delta;

			BulletMove();
			Die();
			SetMaxSpeed();
			SetMaxAttack();
			SetColor();
			SetReflectflg();

			if (flg_reflect == false)
			{
				BulletEffectBlack(2, Vec3(1.0f, 1.0f, 1.0f));
			}
			else
			{
				SetColor();
			}
		}
	}

	void DangerBullet::Initialize()
	{
		m_ReflectCount = 2;

		m_BulletSpeed = 15.0f;
		m_Attack = 1.0f;
		m_DieTime = 0.0f;
		m_ReflectTime = 0.0f;
		m_Damage = 2.0f;
		m_Hp = 0.0f;

		flg_reflect = false;
		flg_reflectWall = false;
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

	void DangerBullet::SetMaxAttack()
	{
		if (m_Attack >= MAX_ATTACK)
		{
			m_Attack = MAX_ATTACK;
		}
	}

	void DangerBullet::SetColor()
	{
		Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
		spanMat.affineTransformation(
			Vec3(1.0f, 1.0f, 1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, -3.0f, 0.0f)
		);

		if (m_ReflectCount == 1)
		{
			//描画
			auto ptrDraw = AddComponent<PNTStaticModelDraw>();

			ptrDraw->SetMeshResource(L"ENEMY_BULLET");
			ptrDraw->SetMeshToTransformMatrix(spanMat);
		}

		if (flg_reflect && m_ReflectCount <= 0)
		{
			if (m_Attack == 1.0f)
			{
				auto ptrDraw = AddComponent<PNTStaticModelDraw>();

				ptrDraw->SetMeshResource(L"RED_BULLET");
				ptrDraw->SetMeshToTransformMatrix(spanMat);

				BulletEffectRed(3, Vec3(0.0f, 0.0f, 0.0f));
			}
			else if (m_Attack == 2.0f)
			{
				auto ptrDraw = AddComponent<PNTStaticModelDraw>();

				ptrDraw->SetMeshResource(L"ORANGE_BULLET");
				ptrDraw->SetMeshToTransformMatrix(spanMat);

				BulletEffectOrange(3, Vec3(0.0f, 0.0f, 0.0f));
			}
			else if (m_Attack == 3.0f)
			{
				auto ptrDraw = AddComponent<PNTStaticModelDraw>();

				ptrDraw->SetMeshResource(L"YELLOW_BULLET");
				ptrDraw->SetMeshToTransformMatrix(spanMat);

				BulletEffectYellow(3, Vec3(0.0f, 0.0f, 0.0f));
			}
			else if (m_Attack == 4.0f)
			{
				auto ptrDraw = AddComponent<PNTStaticModelDraw>();

				ptrDraw->SetMeshResource(L"GREEN_BULLET");
				ptrDraw->SetMeshToTransformMatrix(spanMat);

				BulletEffectGreen(3, Vec3(0.0f, 0.0f, 0.0f));
			}
			else if (m_Attack == 5.0f)
			{
				auto ptrDraw = AddComponent<PNTStaticModelDraw>();

				ptrDraw->SetMeshResource(L"BLUE_BULLET");
				ptrDraw->SetMeshToTransformMatrix(spanMat);

				BulletEffectBlue(3, Vec3(0.0f, 0.0f, 0.0f));
			}
		}
	}

	void DangerBullet::GenerateFire(int GenerateNum, Vec3 MoveSpeed)
	{
		auto ptrTrans = GetComponent<Transform>();
		auto PtrFire = GetStage()->GetSharedGameObject<MultiFire>(L"MultiFire", false);
		if (PtrFire) {
			PtrFire->InsertFire(GetComponent<Transform>()->GetPosition(), GenerateNum, MoveSpeed);
		}
	}

	void DangerBullet::GenerateFireBlue(int GenerateNum, Vec3 MoveSpeed)
	{
		auto ptrTrans = GetComponent<Transform>();
		auto PtrFire = GetStage()->GetSharedGameObject<MultiFireBlue>(L"MultiFireBlue", false);
		if (PtrFire) {
			PtrFire->InsertFire(GetComponent<Transform>()->GetPosition(), GenerateNum, MoveSpeed);
		}
	}

	void DangerBullet::BulletEffectRed(int GenerateNum, Vec3 MoveSpeed)
	{
		auto ptrTrans = GetComponent<Transform>();
		auto PtrFire = GetStage()->GetSharedGameObject<RedFire>(WstringKey::ShareObj_RedFire, false);
		if (PtrFire) {
			PtrFire->InsertFire(GetComponent<Transform>()->GetPosition(), GenerateNum, MoveSpeed);
		}
	}

	void DangerBullet::BulletEffectOrange(int GenerateNum, Vec3 MoveSpeed)
	{
		auto ptrTrans = GetComponent<Transform>();
		auto PtrFire = GetStage()->GetSharedGameObject<OrangeFire>(WstringKey::ShareObj_OrangeFire, false);
		if (PtrFire) {
			PtrFire->InsertFire(GetComponent<Transform>()->GetPosition(), GenerateNum, MoveSpeed);
		}
	}

	void DangerBullet::BulletEffectYellow(int GenerateNum, Vec3 MoveSpeed)
	{
		auto ptrTrans = GetComponent<Transform>();
		auto PtrFire = GetStage()->GetSharedGameObject<YellowFire>(WstringKey::ShareObj_YellowFire, false);
		if (PtrFire) {
			PtrFire->InsertFire(GetComponent<Transform>()->GetPosition(), GenerateNum, MoveSpeed);
		}
	}

	void DangerBullet::BulletEffectGreen(int GenerateNum, Vec3 MoveSpeed)
	{
		auto ptrTrans = GetComponent<Transform>();
		auto PtrFire = GetStage()->GetSharedGameObject<GreenFire>(WstringKey::ShareObj_GreenFire, false);
		if (PtrFire) {
			PtrFire->InsertFire(GetComponent<Transform>()->GetPosition(), GenerateNum, MoveSpeed);
		}
	}

	void DangerBullet::BulletEffectBlue(int GenerateNum, Vec3 MoveSpeed)
	{
		auto ptrTrans = GetComponent<Transform>();
		auto PtrFire = GetStage()->GetSharedGameObject<BlueFire>(WstringKey::ShareObj_BlueFire, false);
		if (PtrFire) {
			PtrFire->InsertFire(GetComponent<Transform>()->GetPosition(), GenerateNum, MoveSpeed);
		}
	}

	void DangerBullet::BulletEffectBlack(int GenerateNum, Vec3 MoveSpeed)
	{
		auto ptrTrans = GetComponent<Transform>();
		auto PtrFire = GetStage()->GetSharedGameObject<BlackFire>(WstringKey::ShareObj_BlackFire, false);
		if (PtrFire) {
			PtrFire->InsertFire(GetComponent<Transform>()->GetPosition(), GenerateNum, MoveSpeed);
		}
	}

	void DangerBullet::GenerateReflectEffect(int GenerateNum, Vec3 MoveSpeed)
	{
		auto ptrTrans = GetComponent<Transform>();
		auto PtrFire = GetStage()->GetSharedGameObject<ReflectBulletEffect>(WstringKey::ShareObj_ReflectBulletEffect, false);
		if (PtrFire) {
			PtrFire->InsertEffect(GetComponent<Transform>()->GetPosition(), GenerateNum, MoveSpeed);
		}
	}

	void DangerBullet::SetReflectflg()
	{
		if (m_ReflectTime >= 0.005f)
		{
			flg_reflectWall = false;

			m_ReflectTime = 0.0f;
		}
	}

	//当たった瞬間
	void DangerBullet::OnCollisionEnter(shared_ptr<GameObject>& other)
	{
		// 当たったのがプレイヤーなら
		if (auto player = dynamic_pointer_cast<Player>(other))
		{
			if (flg_reflect == false)
			{
				player->Damage(m_Damage);
			}

			SetDrawActive(false);
			SetUpdateActive(false);
		}

		//　あたったのが壁なら
		if (auto magicWall = dynamic_pointer_cast<MagicWall>(other))
		{
			auto wallTrans = magicWall->GetComponent<Transform>();
			auto myTrans = GetComponent<Transform>();

			m_ReflectCount -= 1;

			if (m_ReflectCount <= 0)
			{
				m_BulletSpeed += 5.0f;
				m_Attack += 1.0f;
				m_Hp += 1.0f;

				flg_reflect = true;

				SetDir(Reflect(wallTrans->GetForword(), dir));

				GenerateReflectEffect(30, Vec3(30.0f));

				auto ptrXA = App::GetApp()->GetXAudio2Manager();
				ptrXA->Start(WstringKey::SE_Reflection, 0, 1.0f);

				if (m_Attack == 1.0f)
				{
					auto ptrXA = App::GetApp()->GetXAudio2Manager();
					ptrXA->Start(WstringKey::SE_BULLET_RED, 0, 10.0f);
				}
				else if (m_Attack == 2.0f)
				{
					auto ptrXA = App::GetApp()->GetXAudio2Manager();
					ptrXA->Start(WstringKey::SE_BULLET_ORANGE, 0, 10.0f);
				}
				else if (m_Attack == 3.0f)
				{
					auto ptrXA = App::GetApp()->GetXAudio2Manager();
					ptrXA->Start(WstringKey::SE_BULLET_YELLOW, 0, 10.0f);
				}
				else if (m_Attack == 4.0f)
				{
					auto ptrXA = App::GetApp()->GetXAudio2Manager();
					ptrXA->Start(WstringKey::SE_BULLET_GREEN, 0, 10.0f);
				}
				else if (m_Attack >= 5.0f)
				{
					auto ptrXA = App::GetApp()->GetXAudio2Manager();
					ptrXA->Start(WstringKey::SE_BULLET_BLUE, 0, 10.0f);
				}
			}

			else
			{
				m_Attack -= 1.0f;
				m_Damage -= 1.0f;

				auto ptrXA = App::GetApp()->GetXAudio2Manager();
				ptrXA->Start(WstringKey::SE_BreakWall, 0, 1.0f);
			}

			magicWall->Damage(m_Damage);
		}

		//　あたったのがシールドなら
		if (auto shield = dynamic_pointer_cast<EnemyShield>(other))
		{
			if (flg_reflect)
			{
				if (m_Attack < shield->GetHP())
				{
					shield->Damage(m_Attack);

					auto ptrXA = App::GetApp()->GetXAudio2Manager();
					ptrXA->Start(WstringKey::SE_SheildUnbreak, 0, 2.0f);

					SetDrawActive(false);
					SetUpdateActive(false);
				}
				else if (m_Attack >= shield->GetHP())
				{
					shield->Damage(m_Attack);
				}
			}
		}

		//　あたったのがシールドなら
		if (auto shield = dynamic_pointer_cast<PatrolShield>(other))
		{
			if (flg_reflect)
			{
				if (m_Attack < shield->GetHP())
				{
					shield->Damage(m_Attack);

					auto ptrXA = App::GetApp()->GetXAudio2Manager();
					ptrXA->Start(WstringKey::SE_SheildUnbreak, 0, 2.0f);

					SetDrawActive(false);
					SetUpdateActive(false);
				}
				else if (m_Attack >= shield->GetHP())
				{
					shield->Damage(m_Attack);
				}
			}
		}

		//　あたったのがシールドなら
		if (auto shield = dynamic_pointer_cast<UPPatrolShield>(other))
		{
			if (flg_reflect)
			{
				if (m_Attack < shield->GetHP())
				{
					shield->Damage(m_Attack);

					auto ptrXA = App::GetApp()->GetXAudio2Manager();
					ptrXA->Start(WstringKey::SE_SheildUnbreak, 0, 2.0f);

					SetDrawActive(false);
					SetUpdateActive(false);
				}
				else if (m_Attack >= shield->GetHP())
				{
					shield->Damage(m_Attack);
				}
			}
		}

		//　あたったのがシールドなら
		if (auto shield = dynamic_pointer_cast<RapidShield>(other))
		{
			if (flg_reflect)
			{
				if (m_Attack < shield->GetHP())
				{
					shield->Damage(m_Attack);

					auto ptrXA = App::GetApp()->GetXAudio2Manager();
					ptrXA->Start(WstringKey::SE_SheildUnbreak, 0, 2.0f);

					SetDrawActive(false);
					SetUpdateActive(false);
				}
				else if (m_Attack >= shield->GetHP())
				{
					shield->Damage(m_Attack);
				}
			}
		}

		//　あたったのがシールドなら
		if (auto shield = dynamic_pointer_cast<DangerShield>(other))
		{
			if (flg_reflect)
			{
				if (m_Attack < shield->GetHP())
				{
					shield->Damage(m_Attack);

					auto ptrXA = App::GetApp()->GetXAudio2Manager();
					ptrXA->Start(WstringKey::SE_SheildUnbreak, 0, 2.0f);

					SetDrawActive(false);
					SetUpdateActive(false);
				}
				else if (m_Attack >= shield->GetHP())
				{
					shield->Damage(m_Attack);
				}
			}
		}

		//　あたったのがシールドなら
		if (auto shield = dynamic_pointer_cast<ReflectShield>(other))
		{
			if (flg_reflect)
			{
				if (m_Attack < shield->GetHP())
				{
					shield->Damage(m_Attack);

					auto ptrXA = App::GetApp()->GetXAudio2Manager();
					ptrXA->Start(WstringKey::SE_SheildUnbreak, 0, 2.0f);

					SetDrawActive(false);
					SetUpdateActive(false);
				}
				else if (m_Attack >= shield->GetHP())
				{
					shield->Damage(m_Attack);
				}
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

		if (auto reflectEnemy = dynamic_pointer_cast<ReflectEnemy>(other))
		{
			if (flg_reflect)
			{
				reflectEnemy->Damage(m_Attack);

				auto ptrXA = App::GetApp()->GetXAudio2Manager();
				ptrXA->Start(WstringKey::SE_EnemyDamage, 0, 1.0f);
			}

			if (m_DieTime >= 0.3f)
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

			auto &app = App::GetApp();
			auto delta = app->GetElapsedTime();

			if (flg_reflect && flg_reflectWall == false)
			{
				m_BulletSpeed += 10.0f;
				m_Attack += 1.0f;
				m_Hp += 1.0f;

				pos -= 0.1f;

				SetDir(Reflect(wallTrans->GetForword(), dir));

				flg_reflectWall = true;

				m_ReflectTime += delta;

				GenerateReflectEffect(30, Vec3(30.0f));

				if (m_Attack == 1.0f)
				{
					auto ptrXA = App::GetApp()->GetXAudio2Manager();
					ptrXA->Start(WstringKey::SE_BULLET_RED, 0, 10.0f);
				}
				else if (m_Attack == 2.0f)
				{
					auto ptrXA = App::GetApp()->GetXAudio2Manager();
					ptrXA->Start(WstringKey::SE_BULLET_ORANGE, 0, 10.0f);
				}
				else if (m_Attack == 3.0f)
				{
					auto ptrXA = App::GetApp()->GetXAudio2Manager();
					ptrXA->Start(WstringKey::SE_BULLET_YELLOW, 0, 10.0f);
				}
				else if (m_Attack == 4.0f)
				{
					auto ptrXA = App::GetApp()->GetXAudio2Manager();
					ptrXA->Start(WstringKey::SE_BULLET_GREEN, 0, 10.0f);
				}
				else if (m_Attack >= 5.0f)
				{
					auto ptrXA = App::GetApp()->GetXAudio2Manager();
					ptrXA->Start(WstringKey::SE_BULLET_BLUE, 0, 10.0f);
				}
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
				m_Hp -= 1.0f;

				auto ptrXA = App::GetApp()->GetXAudio2Manager();
				ptrXA->Start(WstringKey::SE_BreakStageWall, 0, 1.0f);
			}
			if (flg_reflect == false || m_Hp <= 0.0f)
			{
				SetDrawActive(false);
				SetUpdateActive(false);
			}
		}
	}
}