#include "stdafx.h"
#include "Project.h"

////�З͂P�̈�ʒe
namespace basecross {
	void RayBullet::OnCreate()
	{
		Mat4x4 spanMat; // ���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
		spanMat.affineTransformation(
			Vec3(1.0f, 1.0f, 1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, -3.0f, 0.0f)
		);

		//�`��
		auto ptrDraw = AddComponent<PNTStaticModelDraw>();
		ptrDraw->SetMeshResource(L"BULLET_MESH");
		ptrDraw->SetMeshToTransformMatrix(spanMat);

		// �Փ˔���
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetAfterCollision(AfterCollision::None);

		AddTag(L"EnemyBullet");

		Initialize();

		auto myTrans = GetComponent<Transform>();

		auto my_Scale = myTrans->GetScale();

		myTrans->SetScale(0.1f, 0.1f, 0.1f);
	}

	void RayBullet::OnUpdate()
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
			}
		}
	}

	void RayBullet::Initialize()
	{
		m_BulletSpeed = 100.0f;
		m_DieTime = 0.0f;

		flg_Ray = true;
	}

	void RayBullet::BulletMove()
	{
		auto &app = App::GetApp();
		auto delta = app->GetElapsedTime();

		auto transComp = GetComponent<Transform>();
		auto pos = transComp->GetPosition();

		pos += m_BulletSpeed * dir * delta;

		transComp->SetPosition(pos);
	}

	void RayBullet::Die()
	{
		if (m_DieTime >= 2.0f)
		{
			SetDrawActive(false);
			SetUpdateActive(false);
		}
	}

	void RayBullet::SetDir(const Vec3& v)
	{
		dir = v;
	}

	Vec3 RayBullet::GetPosition() const
	{
		return GetComponent<Transform>()->GetPosition();
	}

	bool RayBullet::GetRayFlg()
	{
		return flg_Ray;
	}

	//���������u��
	void RayBullet::OnCollisionEnter(shared_ptr<GameObject>& other)
	{
		if (auto player = dynamic_pointer_cast<Player>(other))
		{
			flg_Ray = true;

			SetDrawActive(false);
			SetUpdateActive(false);
		}
		
		else if (auto reflectWall = dynamic_pointer_cast<StageRefrectWall>(other))
		{
			flg_Ray = false;

			SetDrawActive(false);
			SetUpdateActive(false);
		}
		else if (auto stageWall = dynamic_pointer_cast<StageWall>(other))
		{
			flg_Ray = false;

			SetDrawActive(false);
			SetUpdateActive(false);
		}
		else if (auto breakWall = dynamic_pointer_cast<BreakWall>(other))
		{
			flg_Ray = false;

			SetDrawActive(false);
			SetUpdateActive(false);
		}

	}
}
