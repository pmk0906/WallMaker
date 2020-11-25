/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
	///-----------------------------------------------
	/// プレイヤーのライフ
	///-----------------------------------------------
	PlayerLife::PlayerLife(
		const shared_ptr<Stage>& StagePtr, 
		bool Trace,
		const Vec2& StartScale, 
		const Vec3& StartPos,
		const int LifeNum
	) :
		GameObject(StagePtr),
		m_Trace(Trace),
		m_StartScale(StartScale),
		m_StartPos(StartPos),
		m_LifeNum(LifeNum)
	{}
	PlayerLife::~PlayerLife() {}

	//	初期化
	void PlayerLife::OnCreate()
	{
		float helfSize = 0.5f;
		//頂点配列(縦横5個ずつ表示)
		vector<VertexPositionColorTexture> vertices = {
			{ VertexPositionColorTexture(Vec3(-helfSize, helfSize, 0),Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize, helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(-helfSize, -helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(0.0f, 1.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize, -helfSize, 0), Col4(1.0f, 1.0f, 1.0, 1.0f), Vec2(1.0f, 1.0f)) },
		};
		//インデックス配列
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		SetAlphaActive(m_Trace);
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_StartScale.x, m_StartScale.y, 1.0f);
		ptrTrans->SetRotation(0, 0, 0);
		ptrTrans->SetPosition(m_StartPos);
		//頂点とインデックスを指定してスプライト作成
		auto ptrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
		ptrDraw->SetSamplerState(SamplerState::LinearWrap);
		ptrDraw->SetTextureResource(L"HEART_TX");
	}

	void PlayerLife::OnUpdate()
	{
		auto player_share = GetStage()->GetSharedGameObject<Player>(WstringKey::ShareObj_Player);
		float playerHp = player_share->GetLife();
		if (playerHp < m_LifeNum)
		{
			//色を暗くする
			auto ptrDraw = GetComponent<PCTSpriteDraw>();
			auto col = ptrDraw->GetDiffuse();
			col.x = 0.3f;
			col.y = 0.3f;
			col.z = 0.3f;
			ptrDraw->SetDiffuse(col);
		}
		else
		{
			////色を戻す
			auto ptrDraw = GetComponent<PCTSpriteDraw>();
			auto col = ptrDraw->GetDiffuse();
			col.x = 1.0f;
			col.y = 1.0f;
			col.z = 1.0f;
			ptrDraw->SetDiffuse(col);
		}
	}

	///-----------------------------------------------
	/// 使える壁の数
	///-----------------------------------------------

	WallStock::WallStock(
		const shared_ptr<Stage>& StagePtr,
		bool Trace,
		const Vec2& StartScale,
		const Vec3& StartPos,
		const int WallNum
	) :
		GameObject(StagePtr),
		m_Trace(Trace),
		m_StartScale(StartScale),
		m_StartPos(StartPos),
		m_WallNum(WallNum)
	{}
	WallStock::~WallStock() {}

	//	初期化
	void WallStock::OnCreate()
	{
		float helfSize = 0.5f;
		//頂点配列(縦横5個ずつ表示)
		vector<VertexPositionColorTexture> vertices = {
			{ VertexPositionColorTexture(Vec3(-helfSize, helfSize, 0),Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize, helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(-helfSize, -helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(0.0f, 1.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize, -helfSize, 0), Col4(1.0f, 1.0f, 1.0, 1.0f), Vec2(1.0f, 1.0f)) },
		};
		//インデックス配列
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		SetAlphaActive(m_Trace);
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_StartScale.x, m_StartScale.y, 1.0f);
		ptrTrans->SetRotation(0, 0, 0);
		ptrTrans->SetPosition(m_StartPos);
		//頂点とインデックスを指定してスプライト作成
		auto ptrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
		ptrDraw->SetSamplerState(SamplerState::LinearWrap);
		ptrDraw->SetTextureResource(L"WALLSTOCK_TX");
	}

	void WallStock::OnUpdate()
	{
		auto player_share = GetStage()->GetSharedGameObject<Player>(WstringKey::ShareObj_Player);
		float playerWallStock = player_share->GetWallStock();
		if (playerWallStock < m_WallNum)
		{
			////色を戻す
			auto ptrDraw = GetComponent<PCTSpriteDraw>();
			auto col = ptrDraw->GetDiffuse();
			col.x = 1.0f;
			col.y = 1.0f;
			col.z = 1.0f;
			ptrDraw->SetDiffuse(col);
		}
		else
		{
			//色を暗くする
			auto ptrDraw = GetComponent<PCTSpriteDraw>();
			auto col = ptrDraw->GetDiffuse();
			col.x = 0.3f;
			col.y = 0.3f;
			col.z = 0.3f;
			ptrDraw->SetDiffuse(col);
		}
	}
}
//end basecross
