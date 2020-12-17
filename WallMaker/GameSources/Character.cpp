/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
	FixedBox::FixedBox(
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
	FixedBox::~FixedBox() {}

	//	初期化
	void FixedBox::OnCreate()
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
		AddTag(L"FixedBox");
		//影をつける（シャドウマップを描画する）
		//auto shadowPtr = AddComponent<Shadowmap>();
		////影の形（メッシュ）を設定
		//shadowPtr->SetMeshResource(L"DEFAULT_DODECAHEDRON");
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_DODECAHEDRON");
		//ptrDraw->SetTextureResource(WstringKey::Tx_Floor);
		//ptrDraw->SetFogEnabled(true);
		ptrDraw->SetOwnShadowActive(true);
		//描画するテクスチャを設定
		ptrDraw->SetTextureResource(L"FLOOR_TX");
		SetAlphaActive(false);

		SetDrawLayer(-2);
	}

	///--------------------------------------------------
	/// Floor
	///--------------------------------------------------
	Floor::Floor(
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
	Floor::~Floor() {}
	
	//	初期化
	void Floor::OnCreate()
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
		AddTag(WstringKey::Tag_Floor);
		AddTag(WstringKey::Tag_DrawActiveFalse);

		//影をつける（シャドウマップを描画する）
		//auto shadowPtr = AddComponent<Shadowmap>();
		////影の形（メッシュ）を設定
		//shadowPtr->SetMeshResource(L"DEFAULT_CUBE");
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		//ptrDraw->SetTextureResource(WstringKey::Tx_Floor);
		//ptrDraw->SetFogEnabled(true);
		ptrDraw->SetOwnShadowActive(true);
		//描画するテクスチャを設定
		ptrDraw->SetTextureResource(L"FLOOR_4x4_TX");
		SetAlphaActive(false);

		SetDrawLayer(-2);
	}

	///--------------------------------------------------
	/// StageWall
	///--------------------------------------------------
	StageWall::StageWall(
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
	StageWall::~StageWall () {}

	//	初期化
	void StageWall::OnCreate()
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
		AddTag(WstringKey::Tag_DrawActiveFalse);
		//影をつける（シャドウマップを描画する）
		//auto shadowPtr = AddComponent<Shadowmap>();
		////影の形（メッシュ）を設定
		//shadowPtr->SetMeshResource(L"DEFAULT_CUBE");
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		//ptrDraw->SetTextureResource(WstringKey::Tx_Floor);
		//ptrDraw->SetFogEnabled(true);
		ptrDraw->SetOwnShadowActive(true);
		ptrDraw->SetLightingEnabled(false);
		//描画するテクスチャを設定
		ptrDraw->SetTextureResource(L"WALL_TX");
		SetAlphaActive(false);

		SetDrawLayer(-2);
	}

	///--------------------------------------------------
	/// StageRefrectWall
	///--------------------------------------------------
	StageRefrectWall::StageRefrectWall(
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
	StageRefrectWall::~StageRefrectWall() {}

	//	初期化
	void StageRefrectWall::OnCreate()
	{
		// 大きさ、回転、位置
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale);
		ptrTrans->SetRotation(m_Rotation);
		ptrTrans->SetPosition(m_Position);

		// 衝突判定
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);
		//ptrColl->SetDrawActive(true);
		ptrColl->SetAfterCollision(AfterCollision::None);

		//タグをつける
		AddTag(WstringKey::Tag_DrawActiveFalse);
		//影をつける（シャドウマップを描画する）
		//auto shadowPtr = AddComponent<Shadowmap>();
		////影の形（メッシュ）を設定
		//shadowPtr->SetMeshResource(L"DEFAULT_CUBE");
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		ptrDraw->SetOwnShadowActive(true);
		ptrDraw->SetTextureResource(L"REFLECTWALL_TX");

		SetDrawLayer(-2);
	}

	BreakWall::BreakWall(
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
	BreakWall::~BreakWall() {}

	//	初期化
	void BreakWall::OnCreate()
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
		AddTag(WstringKey::Tag_DrawActiveFalse);
		//影をつける（シャドウマップを描画する）
		//auto shadowPtr = AddComponent<Shadowmap>();
		////影の形（メッシュ）を設定
		//shadowPtr->SetMeshResource(L"DEFAULT_CUBE");
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		//ptrDraw->SetTextureResource(WstringKey::Tx_Floor);
		//ptrDraw->SetFogEnabled(true);
		ptrDraw->SetOwnShadowActive(true);
		ptrDraw->SetLightingEnabled(false);
		//描画するテクスチャを設定
		ptrDraw->SetTextureResource(L"BREAKWALL_TX");
		SetAlphaActive(false);

		SetDrawLayer(-2);
	}

	void BreakWall::OnUpdate()
	{
		Die();
	}

	void BreakWall::Damage(float damage)
	{
		m_Hp -= damage;
	}

	void BreakWall::Die()
	{
		if (m_Hp <= 0.0f)
		{
			GetStage()->RemoveGameObject<BreakWall>(GetThis<BreakWall>());

			GenerateEffect(30, Vec3(30.0f));
		}
	}

	void BreakWall::GenerateEffect(int GenerateNum, Vec3 MoveSpeed)
	{
		auto myPos = GetComponent<Transform>()->GetPosition();
		auto PtrFire = GetStage()->GetSharedGameObject<WallBreakEffect>(WstringKey::ShareObj_BreakWallEffect, false);
		if (PtrFire) {
			PtrFire->InsertEffect(myPos, GenerateNum, MoveSpeed);
		}
	}


	///--------------------------------------------------
	/// MoveEnableReflectWall
	///--------------------------------------------------
	MoveEnableReflectBlock::MoveEnableReflectBlock(
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
	MoveEnableReflectBlock::~MoveEnableReflectBlock() {}

	//	初期化
	void MoveEnableReflectBlock::OnCreate()
	{
		// 大きさ、回転、位置
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale);
		ptrTrans->SetRotation(m_Rotation);
		ptrTrans->SetPosition(m_Position);

		// 衝突判定
		auto ptrColl = AddComponent<CollisionObb>();
		//ptrColl->SetFixed(true);

		//タグをつける
		AddTag(WstringKey::Tag_DrawActiveFalse);
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		ptrDraw->SetOwnShadowActive(true);
		ptrDraw->SetLightingEnabled(false);
		//描画するテクスチャを設定
		ptrDraw->SetTextureResource(L"WALL_TX");
		SetAlphaActive(false);

		m_Child1 = GetStage()->AddGameObject<MoveEnableReflectWall>(Vec3(3.0f, 3.0f, 0.5f), Vec3(0.0f), Vec3(0.0f, 1.5f, 1.4f), GetThis<MoveEnableReflectBlock>());
		//m_Child2 = GetStage()->AddGameObject<MoveEnableReflectWall>(Vec3(3.0f, 3.0f, 0.5f), Vec3(0.0f), Vec3(0.0f, -1.4f, 0.0f), GetThis<MoveEnableReflectBlock>());
		//m_Child3 = GetStage()->AddGameObject<MoveEnableReflectWall>(Vec3(3.0f, 3.0f, 0.5f), Vec3(0.0f, XMConvertToRadians(90.0f), 0.0f), Vec3(1.4f, 0.0f, 0.0f), GetThis<MoveEnableReflectBlock>());
		//m_Child4 = GetStage()->AddGameObject<MoveEnableReflectWall>(Vec3(3.0f, 3.0f, 0.5f), Vec3(0.0f, XMConvertToRadians(90.0f), 0.0f), Vec3(-1.4f, -1.4f, 0.0f), GetThis<MoveEnableReflectBlock>());

		SetDrawLayer(-2);
	}

	///--------------------------------------------------
	/// StageRefrectWall
	///--------------------------------------------------
	MoveEnableReflectWall::MoveEnableReflectWall(
		const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position,
		const shared_ptr<GameObject>& Parent
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position),
		m_Parent(Parent)
	{}
	MoveEnableReflectWall::~MoveEnableReflectWall() {}

	//	初期化
	void MoveEnableReflectWall::OnCreate()
	{
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetParent(m_Parent->GetThis<GameObject>());

		// 大きさ、回転、位置;
		ptrTrans->SetScale(m_Scale);
		ptrTrans->SetRotation(m_Rotation);
		ptrTrans->SetPosition(m_Position);

		// 衝突判定
		auto ptrColl = AddComponent<CollisionObb>();
		//ptrColl->SetFixed(true);
		//ptrColl->SetDrawActive(true);
		ptrColl->SetAfterCollision(AfterCollision::Auto);

		//タグをつける
		//AddTag(WstringKey::Tag_DrawActiveFalse);
		//影をつける（シャドウマップを描画する）
		//auto shadowPtr = AddComponent<Shadowmap>();
		////影の形（メッシュ）を設定
		//shadowPtr->SetMeshResource(L"DEFAULT_CUBE");
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		ptrDraw->SetOwnShadowActive(true);
		ptrDraw->SetTextureResource(L"REFLECTWALL_TX");

		SetDrawLayer(-2);
	}
}
//end basecross
