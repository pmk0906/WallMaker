#include "stdafx.h"
#include "Project.h"

////範囲内に入ったプレイヤーを狙い弾を撃つ敵
namespace basecross {

	RayObject::RayObject(
		const shared_ptr<Stage>& StagePtr,
		const shared_ptr<GameObject>& Parent)
		:
		GameObject(StagePtr),
		m_Parent(Parent)
	{}
	RayObject::~RayObject() {}

	void RayObject::OnCreate()
	{
		// 衝突判定
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);

		//タグをつける
		AddTag(L"EnemyFirst");

		Initialize();
	}

	void RayObject::OnUpdate()
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

			LookPlayer();

			if (enemyToPlayer.length() <= 20.0f)
			{
				Fire();	
			}

			//if (GetRayFlg() == true)
			//{
			//	auto parentObject = dynamic_pointer_cast<EnemyFirst>(m_Parent);
			//	parentObject->SetFlgRay(GetRayFlg());
			//}
			//else
			//{
			//	auto parentObject = dynamic_pointer_cast<EnemyFirst>(m_Parent);
			//	parentObject->SetFlgRay(GetRayFlg());
			//}
			//auto parentObject = dynamic_pointer_cast<EnemyFirst>(m_Parent);
			//parentObject->SetFlgRay(GetRayFlg());
			
			
		}
		if (gm->GetPoseFlg() == false)
		{
			/*auto ptrDraw = GetComponent<PNTBoneModelDraw>();
			float elapsedTime = App::GetApp()->GetElapsedTime();
			ptrDraw->UpdateAnimation(elapsedTime);*/
		}
	}

	void RayObject::Initialize()
	{
		m_RotY = 0.0f;
		m_FireTime = 1.0f;
	}

	void RayObject::Reload()
	{
		auto& app = App::GetApp();

		float delta = app->GetElapsedTime();

		m_FireTime += delta;
	}

	void RayObject::Fire()
	{
		auto transComp = GetComponent<Transform>();

		auto forward_player = transComp->GetForword();

		auto pos = transComp->GetPosition();

		auto raybullet = GetStage()->AddGameObject<RayBullet>(GetThis<RayObject>());

		flg_Ray = raybullet->GetRayFlg();

		auto bulletTrans = raybullet->GetComponent<Transform>();

		auto bulletPos = raybullet->GetPosition();

		auto scale_enemy = transComp->GetScale();

		bulletPos = pos + forward_player * scale_enemy.x;

		bulletTrans->SetPosition(bulletPos);
		raybullet->SetDir(forward_player);

		//auto ptrXA = App::GetApp()->GetXAudio2Manager();
		//ptrXA->Start(WstringKey::SE_Bullet, 0, 1.0f);

		m_FireTime = 0.0f;
	}

	void RayObject::LookPlayer()
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

		float rot = XMConvertToRadians(90.0f) * delta; // １フレ―ム当たりの旋回角度

		// 外積を用いてプレイヤーがいる方向に旋回する
		if (forward.cross(dir).y < 0.0f) {
			m_RotY += rot;
		}
		else {
			m_RotY -= rot;
		}

		transComp->SetRotation(0.0f, -m_RotY, 0.0f);
	}

	Vec3 RayObject::GetPosition() const
	{
		return GetComponent<Transform>()->GetPosition();
	}

	bool RayObject::GetRayFlg()
	{
		return flg_Ray;
	}
	void RayObject::SetRayFlg(bool rayFlg)
	{
		flg_Ray = rayFlg;
	}

	void RayObject::SetParentRayFlg(bool rayFlg)
	{
		//auto parentObject = dynamic_pointer_cast<EnemyFirst>(m_Parent);
		//parentObject->SetFlgRay(rayFlg);
	}
}
