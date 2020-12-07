#include "stdafx.h"
#include "Project.h"

////範囲内に入ったプレイヤーを狙い弾を撃つ敵
namespace basecross {
	Cannon::Cannon(
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
	Cannon::~Cannon() {}

	void Cannon::OnCreate()
	{
		Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
		spanMat.affineTransformation(
			Vec3(0.8f, 1.0f, 0.8f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, XMConvertToRadians(180.0f), 0.0f),
			Vec3(0.0f, 0.0f, 0.0f)
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
		AddTag(L"Cannon");

		//描画処理
		auto ptrDraw = AddComponent<PNTStaticModelDraw>();
		ptrDraw->SetMeshResource(L"STOPENEMY_MESH");
		ptrDraw->SetMeshToTransformMatrix(spanMat);
		//ptrDraw->SetFogEnabled(true);
		ptrDraw->SetOwnShadowActive(true);

		Initialize();
	}

	void Cannon::OnUpdate()
	{

		auto gm = GameManager::GetInstance();
		if (gm->GetClearFlgChanged() == false)
		{
			if (m_FireTime >= 3.0f)
			{
				Fire();
			}

			Reload();
		}
	}

	void Cannon::Initialize()
	{
		m_FireTime = 3.0f;
	}

	void Cannon::Fire()
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

	void Cannon::Reload()
	{
		auto& app = App::GetApp();

		float delta = app->GetElapsedTime();

		m_FireTime += delta;
	}

	Vec3 Cannon::GetPosition() const
	{
		return GetComponent<Transform>()->GetPosition();
	}
}
