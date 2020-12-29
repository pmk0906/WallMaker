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
		AddTag(L"PatrolEnemy");

		//描画処理
		auto ptrDraw = AddComponent<PNTStaticModelDraw>();
		ptrDraw->SetMeshResource(L"ENEMY_MESH");
		ptrDraw->SetMeshToTransformMatrix(spanMat);
		//ptrDraw->SetFogEnabled(true);
		ptrDraw->SetOwnShadowActive(true);

		Initialize();
		CreateShield();
	}

	void PatrolEnemy::OnUpdate()
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
	}

	//変数の初期化
	void PatrolEnemy::Initialize()
	{
		m_EnemyHP = 1.0f;
		m_FireTime = 3.0f;
		m_MoveSpeed = 3.0f;
		m_MoveDirect = 1.0f;
		m_TimeOfChangeDirect = 0.0f;
	}

	//発射
	void PatrolEnemy::Fire()
	{
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

	//リロード
	void PatrolEnemy::Reload()
	{
		auto& app = App::GetApp();

		float delta = app->GetElapsedTime();

		m_FireTime += delta;
	}

	//往復（左右）
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

	//ダメージを受ける
	void PatrolEnemy::Damage(float damage)
	{
		m_EnemyHP -= damage;
	}


	//死ぬ
	void PatrolEnemy::Die()
	{
		auto ptrChild = dynamic_pointer_cast<PatrolShield>(m_Shield);

		if (m_EnemyHP <= 0.0f)
		{
			SetDrawActive(false);
			SetUpdateActive(false);

			ptrChild->DirectDie();

			GenerataFire(50, Vec3(50.0f));
		}
	}

	void PatrolEnemy::CreateShield()
	{
		m_Shield = GetStage()->AddGameObject<PatrolShield>(GetThis<PatrolEnemy>());
	}

	void PatrolEnemy::FireEffect()
	{
		if (m_FireTime >= 2.0f)
		{
			GenerataFire(2, Vec3(10.0f));
		}
	}

	void PatrolEnemy::GenerataFire(int GenerateNum, Vec3 MoveSpeed)
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

	//ポジションの取得
	Vec3 PatrolEnemy::GetPosition() const
	{
		return GetComponent<Transform>()->GetPosition();
	}
}