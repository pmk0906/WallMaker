/*!
@file Character.cpp
@brief �L�����N�^�[�Ȃǎ���
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

	//	������
	void FixedBox::OnCreate()
	{
		// �傫���A��]�A�ʒu
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale);
		ptrTrans->SetRotation(m_Rotation);
		ptrTrans->SetPosition(m_Position);

		// �Փ˔���
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);

		//�^�O������
		AddTag(L"FixedBox");
		//�e������i�V���h�E�}�b�v��`�悷��j
		auto shadowPtr = AddComponent<Shadowmap>();
		//�e�̌`�i���b�V���j��ݒ�
		shadowPtr->SetMeshResource(L"DEFAULT_DODECAHEDRON");
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_DODECAHEDRON");
		//ptrDraw->SetTextureResource(WstringKey::Tx_Floor);
		//ptrDraw->SetFogEnabled(true);
		ptrDraw->SetOwnShadowActive(true);
		//�`�悷��e�N�X�`����ݒ�
		ptrDraw->SetTextureResource(L"FLOOR_TX");
		SetAlphaActive(false);

		SetDrawLayer(-2);
	}

	///--------------------------------------------------
	/// Floor(�Ђъ��ꂽ�y)
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
	
	//	������
	void Floor::OnCreate()
	{
		// �傫���A��]�A�ʒu
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale);
		ptrTrans->SetRotation(m_Rotation);
		ptrTrans->SetPosition(m_Position);

		// �Փ˔���
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);

		//�^�O������
		AddTag(WstringKey::Tag_Floor);
		//�e������i�V���h�E�}�b�v��`�悷��j
		auto shadowPtr = AddComponent<Shadowmap>();
		//�e�̌`�i���b�V���j��ݒ�
		shadowPtr->SetMeshResource(L"DEFAULT_CUBE");
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		//ptrDraw->SetTextureResource(WstringKey::Tx_Floor);
		//ptrDraw->SetFogEnabled(true);
		ptrDraw->SetOwnShadowActive(true);
		//�`�悷��e�N�X�`����ݒ�
		ptrDraw->SetTextureResource(L"FLOOR_TX");
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

	//	������
	void StageWall::OnCreate()
	{
		// �傫���A��]�A�ʒu
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale);
		ptrTrans->SetRotation(m_Rotation);
		ptrTrans->SetPosition(m_Position);

		// �Փ˔���
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);

		//�^�O������
		AddTag(WstringKey::Tag_DrawActiveFalse);
		//�e������i�V���h�E�}�b�v��`�悷��j
		auto shadowPtr = AddComponent<Shadowmap>();
		//�e�̌`�i���b�V���j��ݒ�
		shadowPtr->SetMeshResource(L"DEFAULT_CUBE");
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		//ptrDraw->SetTextureResource(WstringKey::Tx_Floor);
		//ptrDraw->SetFogEnabled(true);
		ptrDraw->SetOwnShadowActive(true);
		ptrDraw->SetLightingEnabled(false);
		//�`�悷��e�N�X�`����ݒ�
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

	//	������
	void StageRefrectWall::OnCreate()
	{
		// �傫���A��]�A�ʒu
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale);
		ptrTrans->SetRotation(m_Rotation);
		ptrTrans->SetPosition(m_Position);

		// �Փ˔���
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);
		ptrColl->SetDrawActive(true);

		//�^�O������
		AddTag(WstringKey::Tag_DrawActiveFalse);
		//�e������i�V���h�E�}�b�v��`�悷��j
		auto shadowPtr = AddComponent<Shadowmap>();
		//�e�̌`�i���b�V���j��ݒ�
		shadowPtr->SetMeshResource(L"DEFAULT_CUBE");
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		ptrDraw->SetOwnShadowActive(true);

		SetDrawLayer(-2);
	}

	///--------------------------------------------------
	/// GameManagerDebug
	///--------------------------------------------------
	GameManagerDebug::GameManagerDebug(
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
	GameManagerDebug::~GameManagerDebug() {}

	//	������
	void GameManagerDebug::OnCreate()
	{
		// �傫���A��]�A�ʒu
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale);
		ptrTrans->SetRotation(m_Rotation);
		ptrTrans->SetPosition(m_Position);

		// DrawString�p
		auto strComp = AddComponent<StringSprite>();
		strComp->SetBackColor(Col4(0, 0, 0, 0.5f));
		strComp->SetTextRect(Rect2D<float>(1000, 510, 1270, 710));
	}

	void GameManagerDebug::OnUpdate()
	{
		m_InputHandler.PushHandle(GetThis<GameManagerDebug>());
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		WORD wButtons = 0;
		if (cntlVec[0].bConnected) {
			wButtons = cntlVec[0].wPressedButtons;
		}
		auto gm = GameManager::GetInstance();
		//D�p�b�h��
		if (wButtons & XINPUT_GAMEPAD_DPAD_UP) {
			if (gm->GetSelectingButtonNumVertical() > 0)
			{
				gm->SetSelectingButtonMinus();
				testFlg = true;
			}
		}
		//D�p�b�h��
		if (wButtons & XINPUT_GAMEPAD_DPAD_DOWN) {
			if (gm->GetSelectingButtonNumVertical() < gm->GetMaxButtonNum())
			{
				gm->SetSelectingButtonPlus();
				testFlg = false;
			}
		}

	}

	void GameManagerDebug::OnUpdate2()
	{

		DrawStrings();
	}

	void GameManagerDebug::DrawStrings()
	{
		auto gm = GameManager::GetInstance();

		wstring selectingButton(L"�I�����Ă���{�^���̔ԍ� : ");
		selectingButton += Util::UintToWStr(gm->GetSelectingButtonNumVertical()) + L"\n";

		wstring maxButtonNum(L"���݂̃{�^���̍ő�ԍ� : ");
		maxButtonNum += Util::UintToWStr(gm->GetMaxButtonNum()) + L"\n";

		wstring testFLG(L"�e�X�g�t���O : ");
		testFLG += Util::UintToWStr(testFlg) + L"\n";

		wstring str = selectingButton + maxButtonNum + testFLG + L"\n";
		auto ptrString = GetComponent<StringSprite>();
		ptrString->SetText(str);
	}

	void GameManagerDebug::OnPushA()
	{
		auto gm = GameManager::GetInstance();
		if (gm->GetClearFlgChanged())
		{
			switch (gm->GetSelectingButtonNumVertical())
			{
			case 0:
				break;
			case 1:
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), WstringKey::ToGameStageSelect);
				StopBGM();
				break;
			default:
				break;
			}
		}
		if (gm->GetDeathFlgChanged())
		{
			switch (gm->GetSelectingButtonNumVertical())
			{
			case 0:
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), WstringKey::ToGameStage);
				break;
			case 1:
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), WstringKey::ToGameStageSelect);
				StopBGM();
				break;
			default:
				break;
			}

		}
	}

	void GameManagerDebug::StopBGM()
	{
		auto gameStage = dynamic_pointer_cast<GameStage>(GetStage());

		gameStage->StopBGM();
	}

	//void GameManagerDebug::OnPushDPad(int dPadNum) {

	//	auto gm = GameManager::GetInstance();

	//	//testFlg = true;
	//	switch (dPadNum)
	//	{
	//	case DPadNum::UP:
	//		if (gm->GetSelectingButtonNum() < gm->GetMaxButtonNum())
	//		{
	//			gm->SetSelectingButtonPlus();
	//		}
	//		break;
	//	case DPadNum::DOWN:
	//		if (gm->GetSelectingButtonNum() > 0)
	//		{
	//			gm->SetSelectingButtonMinus();
	//			testFlg = false;
	//		}
	//		break;
	//	case DPadNum::RIGHT:
	//		break;
	//	case DPadNum::LEFT:
	//		break;
	//	}
	//};
}
//end basecross
