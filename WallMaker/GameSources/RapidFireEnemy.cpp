#include "stdafx.h"
#include "Project.h"

////範囲内に入ったプレイヤーをロックオンして３連射する敵
namespace basecross {
	RapidFireEnemy::RapidFireEnemy(
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
	RapidFireEnemy::~RapidFireEnemy() {}

	void RapidFireEnemy::OnCreate()
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
		AddTag(L"EnemyFirst");

		//描画処理
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		//ptrDraw->SetFogEnabled(true);
		ptrDraw->SetOwnShadowActive(true);

		Initialize();
	}

	void RapidFireEnemy::OnUpdate()
	{
		auto transComp = GetComponent<Transform>();

		auto enemyPos = transComp->GetPosition();

		auto objs = GetStage()->GetGameObjectVec();

		auto& app = App::GetApp();
		float delta = app->GetElapsedTime();

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

		if (enemyToPlayer.length() <= 20.0f)
		{
			m_LockOnTime += delta;

			LookPlayer();

			if (m_FireTime >= 1.0f && flg_LockOn)
			{
				Fire();
			}
		}

		else
		{
			m_LockOnTime = 0.0f;
		}

		Reload();
		LockOn();
		Die();
	}

	void RapidFireEnemy::Initialize()
	{
		m_EnemyHP = 1.0f;
		m_RotY = 0.0f;
		m_FireTime = 1.0f;
		m_LockOnTime = 0.0f;

		m_FireCount = 0;

		flg_LockOn = false;
	}

	void RapidFireEnemy::Fire()
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


		auto scale_player = transComp->GetScale();

		bulletTrans->SetPosition(pos + forward_player * scale_player.x);
		enemybullet->SetDir(forward_player);

		m_FireTime = 0.0f;

		m_FireCount++;

		auto ptrXA = App::GetApp()->GetXAudio2Manager();
		ptrXA->Start(WstringKey::SE_Bullet, 0, 1.0f);
	}

	void RapidFireEnemy::Reload()
	{
		auto& app = App::GetApp();

		float delta = app->GetElapsedTime();

		m_FireTime += delta;

		if (m_FireCount >= 3)
		{
			m_FireCount = 0;
			m_LockOnTime = 0.0f;
			flg_LockOn = false;
		}
	}

	void RapidFireEnemy::LookPlayer()
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

		auto forward = transComp->GetForword();

		auto dir = enemyToPlayer.normalize();

		float rot = XMConvertToRadians(45.0f) * delta; // １フレ―ム当たりの旋回角度

		// 外積を用いてプレイヤーがいる方向に旋回する
		if (forward.cross(dir).y < 0.0f) {
			m_RotY += rot;
		}
		else {
			m_RotY -= rot;
		}

		transComp->SetRotation(0.0f, -m_RotY, 0.0f);

	}

	void RapidFireEnemy::LockOn()
	{
		if (m_LockOnTime >= 3.0f)
		{
			flg_LockOn = true;
		}
	}

	void RapidFireEnemy::Damage(float damage)
	{
		m_EnemyHP -= damage;
	}

	void RapidFireEnemy::Die()
	{
		if (m_EnemyHP <= 0.0f)
		{
			SetDrawActive(false);
			SetUpdateActive(false);
		}
	}

	Vec3 RapidFireEnemy::GetPosition() const
	{
		return GetComponent<Transform>()->GetPosition();
	}
}