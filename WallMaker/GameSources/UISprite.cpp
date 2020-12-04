/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
	///-----------------------------------------------
	/// 汎用スプライト
	///-----------------------------------------------
	Sprite::Sprite(
		const shared_ptr<Stage>& StagePtr,
		bool Trace,
		const Vec2& StartScale,
		const Vec2& StartPos,
		const wstring TextureKey,
		const int& Layer,
		const Col4& Color
	) :
		GameObject(StagePtr),
		m_Trace(Trace),
		m_StartScale(StartScale),
		m_StartPos(StartPos),
		m_TextureKey(TextureKey),
		m_Layer(Layer),
		m_Color(Color)
	{}
	Sprite::~Sprite() {}

	//	初期化
	void Sprite::OnCreate()
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
		//大きさ、回転、位置
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_StartScale.x, m_StartScale.y, 1.0f);
		ptrTrans->SetRotation(0, 0, 0);
		ptrTrans->SetPosition(Vec3(m_StartPos.x, m_StartPos.y, 0.0f));
		//頂点とインデックスを指定してスプライト作成
		auto ptrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
		ptrDraw->SetTextureResource(m_TextureKey);
		ptrDraw->SetDiffuse(m_Color);
		//透明処理
		SetAlphaActive(m_Trace);
		// レイヤー
		SetDrawLayer(m_Layer);
	}

	void Sprite::OnUpdate()
	{

	}

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
		if (playerWallStock >= m_WallNum)
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

	///-----------------------------------------------
	/// スプライト(フェードイン/アウト用)
	///-----------------------------------------------
	FadeSprite::FadeSprite(
		const shared_ptr<Stage>& StagePtr,
		bool Trace,
		const Vec2& StartScale,
		const Vec2& StartPos,
		bool FadeFlg,
		const float AlphaLimit,
		const wstring TextureKey,
		const int& Layer,
		const Col4& Color
	) :
		GameObject(StagePtr),
		m_Trace(Trace),
		m_StartScale(StartScale),
		m_StartPos(StartPos),
		m_FadeFlg(FadeFlg),
		m_AlphaLimit(AlphaLimit),
		m_TextureKey(TextureKey),
		m_Layer(Layer),
		m_Color(Color)
	{}
	FadeSprite::~FadeSprite() {}

	void FadeSprite::SwitchFadeFlg()
	{
		m_FadeFlg = !m_FadeFlg;
		m_FadeFlgChanged = false;
	}

	//	初期化
	void FadeSprite::OnCreate()
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
		ptrTrans->SetPosition(Vec3(m_StartPos.x, m_StartPos.y, 0.0f));
		//頂点とインデックスを指定してスプライト作成
		auto ptrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
		ptrDraw->SetSamplerState(SamplerState::LinearWrap);
		ptrDraw->SetTextureResource(m_TextureKey);
		if (m_FadeFlg == true)
		{
			m_Color.w = 1.0f;
		}
		else
		{
			m_Color.w = 0.0f;
		}
		ptrDraw->SetDiffuse(m_Color);
		// レイヤー
		SetDrawLayer(m_Layer);
	}

	void FadeSprite::OnUpdate()
	{
		if (m_FadeFlgChanged == false)
		{
			if (m_FadeFlg == true)
			{
				if (m_AlphaValue < m_AlphaLimit)
				{
					auto delta = App::GetApp()->GetElapsedTime();
					auto drawComp = GetComponent<PCTSpriteDraw>();
					auto col = drawComp->GetDiffuse();
					m_AlphaValue += delta;
					col.w = m_AlphaValue;
					drawComp->SetDiffuse(col);
				}
				else
				{
					m_FadeFlgChanged = true;
				}
			}
			else
			{
				if (m_AlphaValue > m_AlphaLimit)
				{
					auto drawComp = GetComponent<PCTSpriteDraw>();
					auto col = drawComp->GetDiffuse();
					auto delta = App::GetApp()->GetElapsedTime();
					m_AlphaValue -= delta;
					col.w = m_AlphaValue;
					drawComp->SetDiffuse(col);
				}
				else
				{
					m_FadeFlgChanged = true;
				}
			}
		}
	}

	void FadeSprite::SetFadeFlgChanged(bool flg)
	{
		m_FadeFlgChanged = flg;
	}

	///-----------------------------------------------
	/// ボタンスプライト
	///-----------------------------------------------
	ButtonSprite::ButtonSprite(
		const shared_ptr<Stage>& StagePtr,
		bool Trace,
		const Vec2& StartScale,
		const Vec2& StartPos,
		bool FadeFlg,
		const float AlphaLimit,
		const wstring TextureKey,
		const int& SelectedButtonNum,
		const int& Layer,
		const Col4& Color
		
	) :
		GameObject(StagePtr),
		m_Trace(Trace),
		m_StartScale(StartScale),
		m_StartPos(StartPos),
		m_FadeFlg(FadeFlg),
		m_AlphaLimit(AlphaLimit),
		m_TextureKey(TextureKey),
		m_SelectButtonNum(SelectedButtonNum),
		m_Layer(Layer),
		m_Color(Color)
	{}
	ButtonSprite::~ButtonSprite() {}

	void ButtonSprite::SelectingThis()
	{
		auto gm = GameManager::GetInstance();
		if (m_SelectButtonNum == gm->GetSelectingButtonNum())
		{
			auto delta = App::GetApp()->GetElapsedTime();
			m_Timer += delta;
			float sin = sinf(m_Timer * 2);
			auto transComp = GetComponent<Transform>();
			transComp->SetScale(
				m_FirstScale.x + sin * m_FirstScale.x / 20 + m_FirstScale.x / 20, 
				m_FirstScale.y + sin * m_FirstScale.y / 20 + m_FirstScale.y / 20,
				1.0f
			);
			//transComp->SetScale(Vec3(m_FirstScale.x, m_FirstScale.y, 1.0f));
		}
		else
		{
			auto transComp = GetComponent<Transform>();
			transComp->SetScale(m_FirstScale);
			m_Timer = 0.0f;
		}
	}

	//	初期化
	void ButtonSprite::OnCreate()
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
		ptrTrans->SetPosition(Vec3(m_StartPos.x, m_StartPos.y, 0.0f));
		//頂点とインデックスを指定してスプライト作成
		auto ptrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
		ptrDraw->SetSamplerState(SamplerState::LinearWrap);
		ptrDraw->SetTextureResource(m_TextureKey);
		if (m_FadeFlg == true)
		{
			m_Color.w = 1.0f;
		}
		else
		{
			m_Color.w = 0.0f;
		}
		ptrDraw->SetDiffuse(m_Color);
		// レイヤー
		SetDrawLayer(m_Layer);

		m_FirstScale = GetComponent<Transform>()->GetScale();
	}

	void ButtonSprite::OnUpdate()
	{
		if (m_FadeFlgChanged == false)
		{
			if (m_FadeFlg == true)
			{
				if (m_AlphaValue < m_AlphaLimit)
				{
					auto delta = App::GetApp()->GetElapsedTime();
					auto drawComp = GetComponent<PCTSpriteDraw>();
					auto col = drawComp->GetDiffuse();
					m_AlphaValue += delta;
					col.w = m_AlphaValue;
					drawComp->SetDiffuse(col);
				}
				else
				{
					m_FadeFlgChanged = true;
				}
			}
			else
			{
				if (m_AlphaValue > m_AlphaLimit)
				{
					auto drawComp = GetComponent<PCTSpriteDraw>();
					auto col = drawComp->GetDiffuse();
					auto delta = App::GetApp()->GetElapsedTime();
					m_AlphaValue -= delta;
					col.w = m_AlphaValue;
					drawComp->SetDiffuse(col);
				}
				else
				{
					m_FadeFlgChanged = true;
				}
			}
		}
		auto gm = GameManager::GetInstance();
		SelectingThis();
	}
}
//end basecross
