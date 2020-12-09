#include "stdafx.h"
#include "Project.h"

////�З͂Q�̋��͂Ȓe
namespace basecross {
	void DangerBullet::OnCreate()
	{
		Mat4x4 spanMat; // ���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
		spanMat.affineTransformation(
			Vec3(1.0f, 1.0f, 1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f)
		);

		//�`��
		auto ptrDraw = AddComponent<PNTStaticModelDraw>();
		ptrDraw->SetMeshResource(L"THORN_BULLET_MESH");
		ptrDraw->SetMeshToTransformMatrix(spanMat);

		// �Փ˔���
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
		Vec3 reverse_BulletVec, newDir, length, reflection;
		float projection;

		reverse_BulletVec = bullet * -1.0f; // �x�N�g���̌������t�ɂ���

		projection = dot(reverse_BulletVec, wall); // ���ς��g���Ďˉe�̒��������߂�

		length = projection * wall; // �ˉe�̒���

		reflection = length * 2.0f; // �ˉe�̒������Q�{����

		newDir = reflection + bullet; // ���ׂẴx�N�g���𑫂�

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
		Mat4x4 spanMat; // ���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
		spanMat.affineTransformation(
			Vec3(1.0f, 1.0f, 1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f)
		);

		if (m_ReflectCount == 1)
		{
			//�`��
			auto ptrDraw = AddComponent<PNTStaticModelDraw>();

			ptrDraw->SetMeshResource(L"BULLET_MESH");
			ptrDraw->SetMeshToTransformMatrix(spanMat);
		}

		if (flg_reflect && m_ReflectCount <= 0)
		{
			auto ptrDraw = AddComponent<PNTStaticModelDraw>();

			ptrDraw->SetMeshResource(L"PURPLE_BULLET_MESH");
			ptrDraw->SetMeshToTransformMatrix(spanMat);
		}
	}

	//���������u��
	void DangerBullet::OnCollisionEnter(shared_ptr<GameObject>& other)
	{
		// ���������̂��v���C���[�Ȃ�
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

		//�@���������̂��ǂȂ�
		if (auto magicWall = dynamic_pointer_cast<MagicWall>(other))
		{
			auto wallTrans = magicWall->GetComponent<Transform>();
			auto myTrans = GetComponent<Transform>();

			m_ReflectCount -= 1;

			if (flg_reflect)
			{
				m_BulletSpeed += 5.0f;
				m_Attack += 1.0f;
			}

			if (m_ReflectCount <= 0)
			{
				flg_reflect = true;

				SetDir(Reflect(wallTrans->GetForword(), dir));

				auto ptrXA = App::GetApp()->GetXAudio2Manager();
				ptrXA->Start(WstringKey::SE_Reflection, 0, 1.0f);
			}

			else
			{
				auto ptrXA = App::GetApp()->GetXAudio2Manager();
				ptrXA->Start(WstringKey::SE_BreakWall, 0, 1.0f);
			}

			magicWall->Damage(m_Attack);
		}

		//�@���������̂��V�[���h�Ȃ�
		if (auto shield = dynamic_pointer_cast<EnemyShield>(other))
		{
			if (flg_reflect)
			{
				shield->Damage(m_Attack);

				SetDrawActive(false);
				SetUpdateActive(false);
			}
		}

		//�@���������̂��V�[���h�Ȃ�
		if (auto shield = dynamic_pointer_cast<PatrolShield>(other))
		{
			if (flg_reflect)
			{
				shield->Damage(m_Attack);

				SetDrawActive(false);
				SetUpdateActive(false);
			}
		}

		//�@���������̂��V�[���h�Ȃ�
		if (auto shield = dynamic_pointer_cast<UPPatrolShield>(other))
		{
			if (flg_reflect)
			{
				shield->Damage(m_Attack);

				SetDrawActive(false);
				SetUpdateActive(false);
			}
		}

		//�@���������̂��V�[���h�Ȃ�
		if (auto shield = dynamic_pointer_cast<RapidShield>(other))
		{
			if (flg_reflect)
			{
				shield->Damage(m_Attack);

				SetDrawActive(false);
				SetUpdateActive(false);
			}
		}

		//�@���������̂��V�[���h�Ȃ�
		if (auto shield = dynamic_pointer_cast<DangerShield>(other))
		{
			if (flg_reflect)
			{
				shield->Damage(m_Attack);

				SetDrawActive(false);
				SetUpdateActive(false);
			}
		}

		//���������̂��G�Ȃ�
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

		if (auto reflectWall = dynamic_pointer_cast<StageRefrectWall>(other))
		{
			auto wallTrans = reflectWall->GetComponent<Transform>();
			auto myTrans = GetComponent<Transform>();

			auto pos = myTrans->GetPosition();

			if (flg_reflect)
			{
				pos -= 0.15f;

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