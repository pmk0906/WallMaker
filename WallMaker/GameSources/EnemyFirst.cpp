#include "stdafx.h"
#include "Project.h"

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

		//影をつける（シャドウマップを描画する）
		auto shadowPtr = AddComponent<Shadowmap>();

		//影の形（メッシュ）を設定
		shadowPtr->SetMeshResource(L"DEFAULT_CUBE");
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");

		//ptrDraw->SetTextureResource(WstringKey::Tx_Floor);
		ptrDraw->SetFogEnabled(true);
		ptrDraw->SetOwnShadowActive(true);
	}

	void EnemyFirst::OnUpdate()
	{

	}

	void EnemyFirst::Initialize()
	{
		m_EnemyHP = 1.0f;
		m_rotY = 0.0f;
	}
}
