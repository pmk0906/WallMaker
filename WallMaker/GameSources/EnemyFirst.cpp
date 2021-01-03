#include "stdafx.h"
#include "Project.h"

////範囲内に入ったプレイヤーを狙い弾を撃つ敵
namespace basecross {
	EnemyFirst::EnemyFirst(
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
	EnemyFirst::~EnemyFirst() {}

	void EnemyFirst::OnCreate()
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
		//タグをつける
		AddTag(WstringKey::Tag_DrawActiveFalse);

		//描画処理
		auto ptrDraw = AddComponent<PNTBoneModelDraw>();
		ptrDraw->SetMeshResource(WstringKey::Anim_Enemy);
		ptrDraw->SetMeshToTransformMatrix(spanMat);
		//ptrDraw->SetFogEnabled(true);
		ptrDraw->SetOwnShadowActive(true);

		ptrDraw->AddAnimation(WstringKey::AM_EnemyGearSpin, 0, 31, true, 30.0f);
		ptrDraw->ChangeCurrentAnimation(WstringKey::AM_EnemyGearSpin);

		Initialize();
		CreateShield();
		//CreateRay();
	}

	void EnemyFirst::OnUpdate()
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
				//auto gameStage = dynamic_pointer_cast<GameStage>(obj);

				if (player) 
				{
					playerPos = player->GetPosition();
				}
			}

			//auto rayObject = dynamic_pointer_cast<RayObject>(m_RayObject);

			auto enemyToPlayer = playerPos - enemyPos;

			if (enemyToPlayer.length() <= 20.0f /*&& rayObject->GetRayFlg() == true*/)
			{
				LookPlayer();

				if (m_FireTime >= 3.0f)
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

	void EnemyFirst::Initialize()
	{
		m_EnemyHP = 1.0f;
		m_RotY = 0.0f;
		m_FireTime = 0.0f;

		flg_Ray = true;
	}

	void EnemyFirst::Fire()
	{
		auto transComp = GetComponent<Transform>();

		auto forward_player = transComp->GetForword();

		auto pos = transComp->GetPosition();

		auto enemybullet = GetStage()->AddGameObject<EnemyBullet>();
		auto bulletTrans = enemybullet->GetComponent<Transform>();

		auto bulletPos = enemybullet->GetPosition();

		auto scale_enemy = transComp->GetScale();

		bulletPos = pos + forward_player * scale_enemy.x;

		bulletTrans->SetPosition(bulletPos);
		enemybullet->SetDir(forward_player);

		m_FireTime = 0.0f;

		auto ptrXA = App::GetApp()->GetXAudio2Manager();
		ptrXA->Start(WstringKey::SE_Bullet, 0, 1.0f);
	}

	void EnemyFirst::Reload()
	{
		auto& app = App::GetApp();

		float delta = app->GetElapsedTime();

		m_FireTime += delta;
	}

	void EnemyFirst::LookPlayer()
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

	void EnemyFirst::Damage(float damage)
	{
		m_EnemyHP -= damage;
	}

	void EnemyFirst::Die()
	{
		auto ptrChild = dynamic_pointer_cast<EnemyShield>(m_Shield);

		if (m_EnemyHP <= 0.0f)
		{
			//SetDrawActive(false);
			//SetUpdateActive(false);
			GetStage()->RemoveGameObject<EnemyFirst>(GetThis<EnemyFirst>());

			ptrChild->DirectDie();

			GenerataFire(30, Vec3(50.0f));
		}
	}

	void EnemyFirst::CreateShield()
	{
		m_Shield = GetStage()->AddGameObject<EnemyShield>(GetThis<EnemyFirst>());
	}

	void EnemyFirst::CreateRay()
	{
		auto transComp = GetComponent<Transform>();
		auto pos = transComp->GetPosition();

		m_RayObject = GetStage()->AddGameObject<RayObject>(GetThis<EnemyFirst>());

		auto rayTrans = m_RayObject->GetComponent<Transform>();

		auto rayPos = rayTrans->GetPosition();

		rayPos = pos;

		rayTrans->SetPosition(rayPos);
	}

	void EnemyFirst::FireEffect()
	{
		if (m_FireTime >= 2.0f)
		{
			GenerataFire(2, Vec3(10.0f));
		}
	}

	void EnemyFirst::GenerataFire(int GenerateNum, Vec3 MoveSpeed)
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

	float EnemyFirst::GetHp()
	{
		return m_EnemyHP;
	}

	float EnemyFirst::GetFireTime()
	{
		return m_FireTime;
	}

	bool EnemyFirst::GetFlgRay()
	{
		return flg_Ray;
	}

	void EnemyFirst::SetFlgRay(bool rayFlg)
	{
		flg_Ray = rayFlg;
	}

	Vec3 EnemyFirst::GetPosition() const
	{
		return GetComponent<Transform>()->GetPosition();
	}
}
