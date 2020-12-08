/*!
@file Character.cpp
@brief �L�����N�^�[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
	///--------------------------------------------------
	/// ��
	///--------------------------------------------------
	TreasureBox::TreasureBox(
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
	TreasureBox::~TreasureBox() {}

	//	������
	void TreasureBox::OnCreate()
	{
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(2.0f, 2.0f, 2.0f);
		ptrTrans->SetRotation(0.0f, 0.0f, 0.0f);
		ptrTrans->SetPosition(m_Position);

		Mat4x4 spanMat; // ���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
		spanMat.affineTransformation(
			Vec3(0.5f, 0.5f, 0.5f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, XMConvertToRadians(180.0f), 0.0f),
			Vec3(0.0f, -0.5f, -0.2f)
		);

		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetDrawActive(true);

		//�e������i�V���h�E�}�b�v��`�悷��j
		auto ptrShadow = AddComponent<Shadowmap>();
		//�e�̌`�i���b�V���j��ݒ�
		ptrShadow->SetMeshResource(L"TREASUREBOX_MESH");
		ptrShadow->SetMeshToTransformMatrix(spanMat);

		auto ptrDraw = AddComponent<PNTStaticModelDraw>();
		ptrDraw->SetMeshResource(L"TREASUREBOX_MESH");
		ptrDraw->SetMeshToTransformMatrix(spanMat);

		AddTag(WstringKey::Tag_Treasure);

		// DrawString�p
		//auto strComp = AddComponent<StringSprite>();
		//strComp->SetBackColor(Col4(0, 0, 0, 0.5f));
		//strComp->SetTextRect(Rect2D<float>(10, 600, 270, 210));
	}

	void TreasureBox::OnUpdate2()
	{
		//DrawStrings();
	}

	void TreasureBox::DrawStrings()
	{
		//������\��
		wstring treasureFlg(L"TreasureFlg.y: ");
		treasureFlg += Util::FloatToWStr(m_TreasureFlg) + L"\n";

		auto gm = GameManager::GetInstance();
		auto clearFlg = gm->GetClearFlg();
		wstring GMClearFlg(L"GameManagerClearFlg: ");
		GMClearFlg += Util::FloatToWStr(clearFlg) + L"\n";

		wstring str = treasureFlg + GMClearFlg + L"\n";
		auto ptrString = GetComponent<StringSprite>();
		ptrString->SetText(str);
	}

	void TreasureBox::OnCollisionEnter(shared_ptr<GameObject>& other) {
		if (auto player = dynamic_pointer_cast<Player>(other))
		{
			SetTreasureFlg(true);
		}
	}
	
	void TreasureBox::SetTreasureFlg(bool flg)
	{
		m_TreasureFlg = flg;
	}

	bool TreasureBox::GetTreasureFlg()
	{
		return m_TreasureFlg;
	}
}
//end basecross
