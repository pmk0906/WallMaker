#include "stdafx.h"
#include "Project.h"

////威力１の一般弾
namespace basecross {
	void ReflectBullet::OnCreate()
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
		ptrDraw->SetMeshResource(L"ENEMY_BULLET");
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

	void ReflectBullet::OnUpdate()
	{
		auto gm = GameManager::GetInstance();
		if (gm->GetMoveEnabledFlg() == true)
		{
			if (gm->GetClearFlgChanged() == false)
			{
				auto &app = App::GetApp();
				auto delta = app->GetElapsedTime();

				m_DieTime += delta;

				BulletMove();
				Die();
				SetMaxSpeed();
				SetMaxAttack();
				//SetColor();
				SetReflectflg();

				if (flg_reflect == false)
				{
					BulletEffectBlack(1, Vec3(0.0f, 0.0f, 0.0f));
				}
				else
				{
					SetColor();
				}
			}
		}
	}

	void ReflectBullet::Initialize()
	{
		m_BulletSpeed = 15.0f;
		m_Attack = 0.0f;
		m_DieTime = 0.0f;
		m_ReflectTime = 0.0f;
		m_ReflectAbilty = 1.0f;
		m_Hp = 0.0f;

		flg_reflect = false;
		flg_reflectWall = false;
	}

	void ReflectBullet::BulletMove()
	{
		auto &app = App::GetApp();
		auto delta = app->GetElapsedTime();

		auto transComp = GetComponent<Transform>();
		auto pos = transComp->GetPosition();

		pos += m_BulletSpeed * dir * delta;

		transComp->SetPosition(pos);
	}

	void ReflectBullet::Die()
	{
		if (m_DieTime >= 5.0f)
		{
			SetDrawActive(false);
			SetUpdateActive(false);
		}
	}

	void ReflectBullet::SetDir(const Vec3& v)
	{
		dir = v;
	}

	Vec3 ReflectBullet::GetPosition() const
	{
		return GetComponent<Transform>()->GetPosition();
	}

	Vec3 ReflectBullet::Reflect(Vec3 wall, Vec3 bullet)
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

	void ReflectBullet::SetMaxSpeed()
	{
		if (m_BulletSpeed >= MAX_SPEED)
		{
			m_BulletSpeed = MAX_SPEED;
		}
	}

	void ReflectBullet::SetMaxAttack()
	{
		if (m_Attack >= MAX_ATTACK)
		{
			m_Attack = MAX_ATTACK;
		}
	}

	void ReflectBullet::SetColor()
	{
		Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
		spanMat.affineTransformation(
			Vec3(1.0f, 1.0f, 1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, -3.0f, 0.0f)
		);

		if (flg_reflect)
		{
			if (m_Attack == 1.0f)
			{
				auto ptrDraw = AddComponent<PNTStaticModelDraw>();

				ptrDraw->SetMeshResource(L"RED_BULLET");
				ptrDraw->SetMeshToTransformMatrix(spanMat);
			}
			else if (m_Attack == 2.0f)
			{
				auto ptrDraw = AddComponent<PNTStaticModelDraw>();

				ptrDraw->SetMeshResource(L"ORANGE_BULLET");
				ptrDraw->SetMeshToTransformMatrix(spanMat);
			}
			else if (m_Attack == 3.0f)
			{
				auto ptrDraw = AddComponent<PNTStaticModelDraw>();

				ptrDraw->SetMeshResource(L"YELLOW_BULLET");
				ptrDraw->SetMeshToTransformMatrix(spanMat);
			}
			else if (m_Attack == 4.0f)
			{
				auto ptrDraw = AddComponent<PNTStaticModelDraw>();

				ptrDraw->SetMeshResource(L"GREEN_BULLET");
				ptrDraw->SetMeshToTransformMatrix(spanMat);
			}
			else if (m_Attack == 5.0f)
			{
				auto ptrDraw = AddComponent<PNTStaticModelDraw>();

				ptrDraw->SetMeshResource(L"BLUE_BULLET");
				ptrDraw->SetMeshToTransformMatrix(spanMat);
			}
		}
	}

	void ReflectBullet::GenerateFire(int GenerateNum, Vec3 MoveSpeed)
	{
		auto ptrTrans = GetComponent<Transform>();
		auto PtrFire = GetStage()->GetSharedGameObject<MultiFire>(L"MultiFire", false);
		if (PtrFire) {
			PtrFire->InsertFire(GetComponent<Transform>()->GetPosition(), GenerateNum, MoveSpeed);
		}
	}

	void ReflectBullet::GenerateFireBlue(int GenerateNum, Vec3 MoveSpeed)
	{
		auto ptrTrans = GetComponent<Transform>();
		auto PtrFire = GetStage()->GetSharedGameObject<MultiFireBlue>(L"MultiFireBlue", false);
		if (PtrFire) {
			PtrFire->InsertFire(GetComponent<Transform>()->GetPosition(), GenerateNum, MoveSpeed);
		}
	}

	void ReflectBullet::BulletEffectRed(int GenerateNum, Vec3 MoveSpeed)
	{
		auto ptrTrans = GetComponent<Transform>();
		auto PtrFire = GetStage()->GetSharedGameObject<RedFire>(WstringKey::ShareObj_RedFire, false);
		if (PtrFire) {
			PtrFire->InsertFire(GetComponent<Transform>()->GetPosition(), GenerateNum, MoveSpeed);
		}
	}

	void ReflectBullet::BulletEffectOrange(int GenerateNum, Vec3 MoveSpeed)
	{
		auto ptrTrans = GetComponent<Transform>();
		auto PtrFire = GetStage()->GetSharedGameObject<OrangeFire>(WstringKey::ShareObj_OrangeFire, false);
		if (PtrFire) {
			PtrFire->InsertFire(GetComponent<Transform>()->GetPosition(), GenerateNum, MoveSpeed);
		}
	}

	void ReflectBullet::BulletEffectYellow(int GenerateNum, Vec3 MoveSpeed)
	{
		auto ptrTrans = GetComponent<Transform>();
		auto PtrFire = GetStage()->GetSharedGameObject<YellowFire>(WstringKey::ShareObj_YellowFire, false);
		if (PtrFire) {
			PtrFire->InsertFire(GetComponent<Transform>()->GetPosition(), GenerateNum, MoveSpeed);
		}
	}

	void ReflectBullet::BulletEffectGreen(int GenerateNum, Vec3 MoveSpeed)
	{
		auto ptrTrans = GetComponent<Transform>();
		auto PtrFire = GetStage()->GetSharedGameObject<GreenFire>(WstringKey::ShareObj_GreenFire, false);
		if (PtrFire) {
			PtrFire->InsertFire(GetComponent<Transform>()->GetPosition(), GenerateNum, MoveSpeed);
		}
	}

	void ReflectBullet::BulletEffectBlue(int GenerateNum, Vec3 MoveSpeed)
	{
		auto ptrTrans = GetComponent<Transform>();
		auto PtrFire = GetStage()->GetSharedGameObject<BlueFire>(WstringKey::ShareObj_BlueFire, false);
		if (PtrFire) {
			PtrFire->InsertFire(GetComponent<Transform>()->GetPosition(), GenerateNum, MoveSpeed);
		}
	}

	void ReflectBullet::BulletEffectBlack(int GenerateNum, Vec3 MoveSpeed)
	{
		auto ptrTrans = GetComponent<Transform>();
		auto PtrFire = GetStage()->GetSharedGameObject<BlackFire>(WstringKey::ShareObj_BlackFire, false);
		if (PtrFire) {
			PtrFire->InsertFire(GetComponent<Transform>()->GetPosition(), GenerateNum, MoveSpeed);
		}
	}

	void ReflectBullet::GenerateReflectEffect(int GenerateNum, Vec3 MoveSpeed)
	{
		auto ptrTrans = GetComponent<Transform>();
		auto PtrFire = GetStage()->GetSharedGameObject<ReflectBulletEffect>(WstringKey::ShareObj_ReflectBulletEffect, false);
		if (PtrFire) {
			PtrFire->InsertEffect(GetComponent<Transform>()->GetPosition(), GenerateNum, MoveSpeed);
		}
	}

	void ReflectBullet::SetReflectflg()
	{
		if (m_ReflectTime >= 0.005f)
		{
			flg_reflectWall = false;

			m_ReflectTime = 0.0f;
		}
	}

	//当たった瞬間
	void ReflectBullet::OnCollisionEnter(shared_ptr<GameObject>& other)
	{
		// 当たったのがプレイヤーなら
		if (auto player = dynamic_pointer_cast<Player>(other))
		{
			if (flg_reflect == false)
			{
				player->Damage(DAMAGE);
			}

			SetDrawActive(false);
			SetUpdateActive(false);
		}

		//　あたったのが魔法壁なら
		if (auto magicWall = dynamic_pointer_cast<MagicWall>(other))
		{
			auto wallTrans = magicWall->GetComponent<Transform>();
			auto myTrans = GetComponent<Transform>();

			m_BulletSpeed += 5.0f;
			m_Attack += 1.0f;
			m_Hp += 1.0f;

			SetDir(Reflect(wallTrans->GetForword(), dir));
			m_ReflectAbilty -= 1.0f;

			auto ptrXA = App::GetApp()->GetXAudio2Manager();
			ptrXA->Start(WstringKey::SE_Reflection, 0, 1.0f);

			flg_reflect = true;

			GenerateReflectEffect(30, Vec3(30.0f));

			magicWall->Damage(m_Attack);

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

		if (auto reflectEnemy = dynamic_pointer_cast<ReflectEnemy>(other))
		{
			if (flg_reflect)
			{
				reflectEnemy->Damage(m_Attack);

				auto ptrXA = App::GetApp()->GetXAudio2Manager();
				ptrXA->Start(WstringKey::SE_EnemyDamage, 0, 1.0f);
			}

			if (m_DieTime >= 0.1f)
			{
				SetDrawActive(false);
				SetUpdateActive(false);
			}
		}

		// 当たったのが反射壁なら
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
			else if (m_ReflectAbilty >= 1.0f)
			{
				pos -= 0.1f;

				SetDir(Reflect(wallTrans->GetForword(), dir));

				flg_reflectWall = true;

				m_ReflectTime += delta;

				GenerateReflectEffect(30, Vec3(30.0f));

				auto ptrXA = App::GetApp()->GetXAudio2Manager();
				ptrXA->Start(WstringKey::SE_Reflection, 0, 1.0f);
			}

			myTrans->SetPosition(pos);

			m_ReflectAbilty -= 1.0f;
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
