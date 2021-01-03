#include "stdafx.h"
#include "Project.h"

////威力１の一般弾
namespace basecross {

	RayBullet::RayBullet(
		const shared_ptr<Stage>& StagePtr,
		const shared_ptr<GameObject>& Parent)
		:
		GameObject(StagePtr),
		m_Parent(Parent)
	{}
	RayBullet::~RayBullet() {}

	void RayBullet::OnCreate()
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
		ptrDraw->SetMeshResource(L"BULLET_MESH");
		ptrDraw->SetMeshToTransformMatrix(spanMat);

		// 衝突判定
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

	//当たった瞬間
	void RayBullet::OnCollisionEnter(shared_ptr<GameObject>& other)
	{
		if (auto player = dynamic_pointer_cast<Player>(other))
		{
			//auto rayObject = dynamic_pointer_cast<RayObject>(m_Parent);
			//rayObject->SetRayFlg(true);

			SetDrawActive(false);
			SetUpdateActive(false);
		}
		
		else if (auto reflectWall = dynamic_pointer_cast<StageRefrectWall>(other))
		{
			//auto rayObject = dynamic_pointer_cast<RayObject>(m_Parent);
			//rayObject->SetRayFlg(false);

			SetDrawActive(false);
			SetUpdateActive(false);
		}
		else if (auto stageWall = dynamic_pointer_cast<StageWall>(other))
		{
			//auto rayObject = dynamic_pointer_cast<RayObject>(m_Parent);
			//rayObject->SetRayFlg(false);

			SetDrawActive(false);
			SetUpdateActive(false);
		}
		else if (auto breakWall = dynamic_pointer_cast<BreakWall>(other))
		{
			//auto rayObject = dynamic_pointer_cast<RayObject>(m_Parent);
			//rayObject->SetRayFlg(false);
			//auto rayObject = static_pointer_cast<RayObject>(m_Parent);
			//rayObject->SetRayFlg(false);

			SetDrawActive(false);
			SetUpdateActive(false);
		}

	}
}
