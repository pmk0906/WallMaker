#include "stdafx.h"
#include "Project.h"

////範囲内に入ったプレイヤーを狙い強力な弾を撃つ敵
namespace basecross {
	DangerEnemy::DangerEnemy(
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
	DangerEnemy::~DangerEnemy() {}

	void DangerEnemy::OnCreate()
	{
		Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
		spanMat.affineTransformation(
			Vec3(0.3f, 1.0f, 0.5f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, XMConvertToRadians(270.0f), 0.0f),
			Vec3(0.0f, -1.5f, 0.0f)
		);

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
		AddTag(WstringKey::Tag_DrawActiveFalse);

		//描画処理
		auto ptrDraw = AddComponent<PNTBoneModelDraw>();
		ptrDraw->SetMeshResource(WstringKey::Anim_EnemyBlue);
		ptrDraw->SetMeshToTransformMatrix(spanMat);
		//ptrDraw->SetFogEnabled(true);
		ptrDraw->SetOwnShadowActive(true);

		ptrDraw->AddAnimation(WstringKey::AM_EnemyGearSpin, 0, 31, true, 30.0f);
		ptrDraw->ChangeCurrentAnimation(WstringKey::AM_EnemyGearSpin);

		Initialize();
		CreateShield();
	}

	void DangerEnemy::OnUpdate()
	{
		auto gm = GameManager::GetInstance();

		if (gm->GetMoveEnabledFlg() == true)
		{
			auto transComp = GetComponent<Transform>();

			auto enemyPos = transComp->GetPosition();

			auto objs = GetStage()->GetGameObjectVec();

			Vec3 playerPos(0.0f, 0.0f, 0.0f);

			for (auto& obj : objs)
			{
				auto player = dynamic_pointer_cast<Player>(obj);
				//auto gameStage = dynamic_pointer_cast<GameStage>(GetStage());

				if (player) {
					playerPos = player->GetPosition();
				}
			}

			auto enemyToPlayer = playerPos - enemyPos;

			if (enemyToPlayer.length() <= 20.0f)
			{
				LookPlayer();

				if (m_FireTime >= 5.0f)
				{
					Fire();
				}
			}

			Reload();
			Die();
			FireEffect();

		}
		if (gm->GetPoseFlg() == false)
		{
			auto ptrDraw = GetComponent<PNTBoneModelDraw>();
			float elapsedTime = App::GetApp()->GetElapsedTime();
			ptrDraw->UpdateAnimation(elapsedTime);
		}
	}

	void DangerEnemy::Initialize()
	{
		m_EnemyHP = 2.0f;
		m_RotY = 0.0f;
		m_FireTime = 5.0f;
	}

	void DangerEnemy::Fire()
	{
		auto transComp = GetComponent<Transform>();

		auto forward_player = transComp->GetForword();

		auto pos = transComp->GetPosition();

		auto enemybullet = GetStage()->AddGameObject<DangerBullet>();
		auto bulletTrans = enemybullet->GetComponent<Transform>();

		auto scale_enemy = transComp->GetScale();

		bulletTrans->SetPosition(pos + forward_player * scale_enemy.x);
		enemybullet->SetDir(forward_player);

		m_FireTime = 0.0f;

		auto ptrXA = App::GetApp()->GetXAudio2Manager();
		ptrXA->Start(WstringKey::SE_Bullet, 0, 1.0f);
	}

	void DangerEnemy::Reload()
	{
		auto& app = App::GetApp();

		float delta = app->GetElapsedTime();

		m_FireTime += delta;
	}

	void DangerEnemy::LookPlayer()
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
			//auto gameStage = dynamic_pointer_cast<GameStage>(GetStage());

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

	void DangerEnemy::Damage(float damage)
	{
		m_EnemyHP -= damage;
	}

	void DangerEnemy::Die()
	{
		auto ptrChild = dynamic_pointer_cast<DangerShield>(m_Shield);

		if (m_EnemyHP <= 0.0f)
		{
			//SetDrawActive(false);
			//SetUpdateActive(false);
			GetStage()->RemoveGameObject<DangerEnemy>(GetThis<DangerEnemy>());

			ptrChild->DirectDie();

			GenerataFire(30, Vec3(50.0f));
		}
	}

	void DangerEnemy::CreateShield()
	{
		m_Shield = GetStage()->AddGameObject<DangerShield>(GetThis<DangerEnemy>());
	}

	void DangerEnemy::FireEffect()
	{
		if (m_FireTime >= 2.0f)
		{
			GenerataFire(2, Vec3(10.0f));
		}
	}

	void DangerEnemy::GenerataFire(int GenerateNum, Vec3 MoveSpeed)
	{
		auto ptrTrans = GetComponent<Transform>();
		auto forward_player = ptrTrans->GetForword();
		auto scale_enemy = ptrTrans->GetScale();
		auto PtrFire = GetStage()->GetSharedGameObject<MultiFire>(L"MultiFire", false);
		if (PtrFire) {
			PtrFire->InsertFire(ptrTrans->GetPosition() + forward_player * scale_enemy.x,
				GenerateNum, MoveSpeed);
		}
	}

	Vec3 DangerEnemy::GetPosition() const
	{
		return GetComponent<Transform>()->GetPosition();
	}
}
