/*!
@file Character.cpp
@brief �L�����N�^�[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
	///-----------------------------------------------
	/// �v���C���[�̃��C�t
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

	//	������
	void PlayerLife::OnCreate()
	{
		float helfSize = 0.5f;
		//���_�z��(�c��5���\��)
		vector<VertexPositionColorTexture> vertices = {
			{ VertexPositionColorTexture(Vec3(-helfSize, helfSize, 0),Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize, helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(-helfSize, -helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(0.0f, 1.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize, -helfSize, 0), Col4(1.0f, 1.0f, 1.0, 1.0f), Vec2(1.0f, 1.0f)) },
		};
		//�C���f�b�N�X�z��
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		SetAlphaActive(m_Trace);
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_StartScale.x, m_StartScale.y, 1.0f);
		ptrTrans->SetRotation(0, 0, 0);
		ptrTrans->SetPosition(m_StartPos);
		//���_�ƃC���f�b�N�X���w�肵�ăX�v���C�g�쐬
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
			//�F���Â�����
			auto ptrDraw = GetComponent<PCTSpriteDraw>();
			auto col = ptrDraw->GetDiffuse();
			col.x = 0.3f;
			col.y = 0.3f;
			col.z = 0.3f;
			ptrDraw->SetDiffuse(col);
		}
		else
		{
			////�F��߂�
			auto ptrDraw = GetComponent<PCTSpriteDraw>();
			auto col = ptrDraw->GetDiffuse();
			col.x = 1.0f;
			col.y = 1.0f;
			col.z = 1.0f;
			ptrDraw->SetDiffuse(col);
		}
	}

	///-----------------------------------------------
	/// �g����ǂ̐�
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

	//	������
	void WallStock::OnCreate()
	{
		float helfSize = 0.5f;
		//���_�z��(�c��5���\��)
		vector<VertexPositionColorTexture> vertices = {
			{ VertexPositionColorTexture(Vec3(-helfSize, helfSize, 0),Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize, helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(-helfSize, -helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(0.0f, 1.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize, -helfSize, 0), Col4(1.0f, 1.0f, 1.0, 1.0f), Vec2(1.0f, 1.0f)) },
		};
		//�C���f�b�N�X�z��
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		SetAlphaActive(m_Trace);
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_StartScale.x, m_StartScale.y, 1.0f);
		ptrTrans->SetRotation(0, 0, 0);
		ptrTrans->SetPosition(m_StartPos);
		//���_�ƃC���f�b�N�X���w�肵�ăX�v���C�g�쐬
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
			////�F��߂�
			auto ptrDraw = GetComponent<PCTSpriteDraw>();
			auto col = ptrDraw->GetDiffuse();
			col.x = 1.0f;
			col.y = 1.0f;
			col.z = 1.0f;
			ptrDraw->SetDiffuse(col);
		}
		else
		{
			//�F���Â�����
			auto ptrDraw = GetComponent<PCTSpriteDraw>();
			auto col = ptrDraw->GetDiffuse();
			col.x = 0.3f;
			col.y = 0.3f;
			col.z = 0.3f;
			ptrDraw->SetDiffuse(col);
		}
	}

	///-----------------------------------------------
	/// �ėp�X�v���C�g
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

	//	������
	void Sprite::OnCreate()
	{
		float helfSize = 0.5f;
		//���_�z��(�c��5���\��)
		vector<VertexPositionColorTexture> vertices = {
			{ VertexPositionColorTexture(Vec3(-helfSize, helfSize, 0),Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize, helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(-helfSize, -helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(0.0f, 1.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize, -helfSize, 0), Col4(1.0f, 1.0f, 1.0, 1.0f), Vec2(1.0f, 1.0f)) },
		};
		//�C���f�b�N�X�z��
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		//�傫���A��]�A�ʒu
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_StartScale.x, m_StartScale.y, 1.0f);
		ptrTrans->SetRotation(0, 0, 0);
		ptrTrans->SetPosition(Vec3(m_StartPos.x, m_StartPos.y, 0.0f));
		//���_�ƃC���f�b�N�X���w�肵�ăX�v���C�g�쐬
		auto ptrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
		ptrDraw->SetTextureResource(m_TextureKey);
		ptrDraw->SetDiffuse(m_Color);
		//��������
		SetAlphaActive(m_Trace);
		// ���C���[
		SetDrawLayer(m_Layer);
	}

	void Sprite::OnUpdate()
	{

	}

	///-----------------------------------------------
	/// �X�v���C�g(�t�F�[�h�C��/�A�E�g�p)
	///-----------------------------------------------
	FadeSprite::FadeSprite(
		const shared_ptr<Stage>& StagePtr,
		bool Trace,
		const Vec2& StartScale,
		const Vec3& StartPos,
		bool FadeFlg,
		const wstring TextureKey
	) :
		GameObject(StagePtr),
		m_Trace(Trace),
		m_StartScale(StartScale),
		m_StartPos(StartPos),
		m_FadeFlg(FadeFlg),
		m_TextureKey(TextureKey)
	{}
	FadeSprite::~FadeSprite() {}

	void FadeSprite::SwitchFadeFlg()
	{
		m_FadeFlg = !m_FadeFlg;
		m_FadeFlgChanged = false;
	}

	//	������
	void FadeSprite::OnCreate()
	{
		float helfSize = 0.5f;
		//���_�z��(�c��5���\��)
		vector<VertexPositionColorTexture> vertices = {
			{ VertexPositionColorTexture(Vec3(-helfSize, helfSize, 0),Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize, helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(-helfSize, -helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(0.0f, 1.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize, -helfSize, 0), Col4(1.0f, 1.0f, 1.0, 1.0f), Vec2(1.0f, 1.0f)) },
		};
		//�C���f�b�N�X�z��
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		SetAlphaActive(m_Trace);
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_StartScale.x, m_StartScale.y, 1.0f);
		ptrTrans->SetRotation(0, 0, 0);
		ptrTrans->SetPosition(m_StartPos);
		//���_�ƃC���f�b�N�X���w�肵�ăX�v���C�g�쐬
		auto ptrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
		ptrDraw->SetSamplerState(SamplerState::LinearWrap);
		ptrDraw->SetTextureResource(L"WHITE_TX");
		auto col = ptrDraw->GetDiffuse();
		if (m_FadeFlg == true)
		{
			col.w = 0.0f;
		}
		else
		{
			col.w = 1.0f;
		}
		ptrDraw->SetDiffuse(col);
	}

	void FadeSprite::OnUpdate()
	{
		if (m_FadeFlgChanged == false)
		{
			if (m_FadeFlg == true)
			{
				if (m_AlphaValue < 1.0f)
				{
					auto drawComp = GetComponent<PCTSpriteDraw>();
					auto col = drawComp->GetDiffuse();
					auto delta = App::GetApp()->GetElapsedTime();
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
				if (m_AlphaValue > 0.0f)
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
}
//end basecross
