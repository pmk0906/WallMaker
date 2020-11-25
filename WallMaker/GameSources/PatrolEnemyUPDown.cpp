#include "stdafx.h"
#include "Project.h"

////往復する敵（上下移動）
namespace basecross {
	PatrolEnemyUPDown::PatrolEnemyUPDown(
		const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position)
	{}
	PatrolEnemyUPDown::~PatrolEnemyUPDown() {}

	void PatrolEnemyUPDown::OnCreate()
	{
		// 大きさ、回転、位置
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale);
		ptrTrans->SetRotation(m_Rotation);
		ptrTrans->SetPosition(m_Position);

		// 衝突判定
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);

		//タグをつける
		AddTag(L"PatrolEnemyUPDown");

		//描画処理
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		//ptrDraw->SetFogEnabled(true);
		ptrDraw->SetOwnShadowActive(true);

		Initialize();
	}

	void PatrolEnemyUPDown::OnUpdate()
	{
		if (m_FireTime >= 3.0f)
		{
			Fire();
		}

		Reload();
		Move();
		Die();
	}

	void PatrolEnemyUPDown::Initialize()
	{
		m_EnemyHP = 1.0f;
		m_FireTime = 3.0f;
		m_MoveSpeed = 3.0f;
		m_MoveDirect = 1.0f;
		m_TimeOfChangeDirect = 0.0f;
	}

	void PatrolEnemyUPDown::Fire()
	{
		auto& app = App::GetApp();

		auto transComp = GetComponent<Transform>();
		float delta = app->GetElapsedTime();
		auto objs = GetStage()->GetGameObjectVec();
		auto enemyPos = transComp->GetPosition();

		Vec3 playerPos(0.0f, 0.0f, 0.0f);

		for (auto& obj : objs)
		{
			auto player = dynamic_pointer_cast<Player>(obj);
			auto gameStage = dynamic_pointer_cast<GameStage>(GetStage());

			if (player) {
				playerPos = player->GetPosition();
			}
		}

		auto enemyToPlayer = playerPos - enemyPos;

		auto quaternion = transComp->GetQuaternion();
		auto rot_bullet = quaternion.toRotVec();

		auto forward_player = transComp->GetForword();

		auto pos = transComp->GetPosition();

		auto enemybullet = GetStage()->AddGameObject<EnemyBullet>();
		auto bulletTrans = enemybullet->GetComponent<Transform>();

		bulletTrans->SetPosition(pos);
		enemybullet->SetDir(forward_player);
		
		m_FireTime = 0.0f;
	}

	void PatrolEnemyUPDown::Reload()
	{
		auto& app = App::GetApp();

		float delta = app->GetElapsedTime();

		m_FireTime += delta;
	}

	void PatrolEnemyUPDown::Move()
	{
		auto& app = App::GetApp();

		float delta = app->GetElapsedTime();

		auto transComp = GetComponent<Transform>();
		auto pos = transComp->GetPosition();

		pos.z += m_MoveSpeed * delta * m_MoveDirect;

		m_TimeOfChangeDirect += delta;

		if (m_TimeOfChangeDirect >= 2.0f)
		{
			m_MoveDirect *= -1.0f;

			m_TimeOfChangeDirect = 0.0f;
		}

		transComp->SetPosition(pos);
	}

	void PatrolEnemyUPDown::Damage(float damage)
	{
		m_EnemyHP -= damage;
	}

	void PatrolEnemyUPDown::Die()
	{
		if (m_EnemyHP <= 0.0f)
		{
			SetDrawActive(false);
			SetUpdateActive(false);
		}
	}
}
