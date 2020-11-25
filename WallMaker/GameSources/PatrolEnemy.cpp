#include "stdafx.h"
#include "Project.h"

////往復する敵（左右移動）
namespace basecross {
	PatrolEnemy::PatrolEnemy(
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
	PatrolEnemy::~PatrolEnemy() {}

	void PatrolEnemy::OnCreate()
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
		AddTag(L"PatrolEnemy");

		//描画処理
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		//ptrDraw->SetFogEnabled(true);
		ptrDraw->SetOwnShadowActive(true);

		Initialize();
	}

	void PatrolEnemy::OnUpdate()
	{
		if (m_FireTime >= 3.0f)
		{
			Fire();
		}

		Reload();
		Move();
		Die();
	}

	void PatrolEnemy::Initialize()
	{
		m_EnemyHP = 1.0f;
		m_FireTime = 3.0f;
		m_MoveSpeed = 3.0f;
		m_MoveDirect = 1.0f;
		m_TimeOfChangeDirect = 0.0f;
	}

	void PatrolEnemy::Fire()
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

	void PatrolEnemy::Reload()
	{
		auto& app = App::GetApp();

		float delta = app->GetElapsedTime();

		m_FireTime += delta;
	}

	void PatrolEnemy::Move()
	{
		auto& app = App::GetApp();

		float delta = app->GetElapsedTime();

		auto transComp = GetComponent<Transform>();
		auto pos = transComp->GetPosition();

		pos.x += m_MoveSpeed * delta * m_MoveDirect;

		m_TimeOfChangeDirect += delta;

		if (m_TimeOfChangeDirect >= 2.0f)
		{
			m_MoveDirect *= -1.0f;

			m_TimeOfChangeDirect = 0.0f;
		}

		transComp->SetPosition(pos);
	}

	void PatrolEnemy::Damage(float damage)
	{
		m_EnemyHP -= damage;
	}

	void PatrolEnemy::Die()
	{
		if (m_EnemyHP <= 0.0f)
		{
			SetDrawActive(false);
			SetUpdateActive(false);
		}
	}
}