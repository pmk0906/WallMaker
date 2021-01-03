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
		AddTag(L"PatrolEnemyUPDown");
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
	}

	void PatrolEnemyUPDown::OnUpdate()
	{
		auto gm = GameManager::GetInstance();
		if (gm->GetMoveEnabledFlg() == true)
		{
			if (m_FireTime >= 3.0f)
			{
				Fire();
			}

			Reload();
			Move();
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
		/*auto& app = App::GetApp();

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

		bulletTrans->SetPosition(pos + forward_player * scale_player.z);
		enemybullet->SetDir(forward_player);
		
		m_FireTime = 0.0f;

		auto ptrXA = App::GetApp()->GetXAudio2Manager();
		ptrXA->Start(WstringKey::SE_Bullet, 0, 1.0f);*/

		auto transComp = GetComponent<Transform>();

		auto forward_player = transComp->GetForword();

		auto pos = transComp->GetPosition();

		auto enemybullet = GetStage()->AddGameObject<EnemyBullet>();
		auto bulletTrans = enemybullet->GetComponent<Transform>();

		auto scale_enemy = transComp->GetScale();

		bulletTrans->SetPosition(pos + forward_player * scale_enemy.x);
		enemybullet->SetDir(forward_player);

		m_FireTime = 0.0f;

		auto ptrXA = App::GetApp()->GetXAudio2Manager();
		ptrXA->Start(WstringKey::SE_Bullet, 0, 1.0f);
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
		auto ptrChild = dynamic_pointer_cast<UPPatrolShield>(m_Shield);

		if (m_EnemyHP <= 0.0f)
		{
			//SetDrawActive(false);
			//SetUpdateActive(false);
			GetStage()->RemoveGameObject<PatrolEnemyUPDown>(GetThis<PatrolEnemyUPDown>());

			ptrChild->DirectDie();

			GenerataFire(50, Vec3(50.0f));
		}
	}

	void PatrolEnemyUPDown::CreateShield()
	{
		m_Shield = GetStage()->AddGameObject<UPPatrolShield>(GetThis<PatrolEnemyUPDown>());
	}

	void PatrolEnemyUPDown::FireEffect()
	{
		if (m_FireTime >= 2.0f)
		{
			GenerataFire(2, Vec3(10.0f));
		}
	}

	void PatrolEnemyUPDown::GenerataFire(int GenerateNum, Vec3 MoveSpeed)
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

	Vec3 PatrolEnemyUPDown::GetPosition() const
	{
		return GetComponent<Transform>()->GetPosition();
	}
}
