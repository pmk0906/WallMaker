/*!
@file Character.cpp
@brief �L�����N�^�[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
	///--------------------------------------------------
	/// GameManagement
	///--------------------------------------------------
	GameManagement::GameManagement(
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
	GameManagement::~GameManagement() {}

	//�V�[����ǂݍ���
	void GameManagement::LoadScene(int stageNum)
	{
		auto gm = GameManager::GetInstance();

		wstring sceneKey;
		switch (stageNum)
		{
		case (int)SceneNum::Title:
			sceneKey = WstringKey::ToGameTitle;
			gm->SetSceneNum(SceneNum::Title);
			break;
		case (int)SceneNum::StageSelect:
			sceneKey = WstringKey::ToGameStageSelect;
			gm->SetSceneNum(SceneNum::StageSelect);
			break;
		case (int)SceneNum::GameStage1:
			sceneKey = WstringKey::ToGameStage1;
			gm->SetSceneNum(SceneNum::GameStage1);
			break;
			//case StageNum::GameStage2:
			//	sceneKey = WstringKey::ToGameStage2;
			//	break;
			//case StageNum::GameStage3:
			//	sceneKey = WstringKey::ToGameStage3;
			//	break;
			//case StageNum::GameStage4:
			//	sceneKey = WstringKey::ToGameStage4;
			//	break;
			//case StageNum::GameStage5:
			//	sceneKey = WstringKey::ToGameStage5;
			//	break;
		}
		PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), sceneKey);
	}

	void GameManagement::PlayerMoveEnabled()
	{
		auto gm = GameManager::GetInstance();
		if (gm->GetOpeningCameraMoveEnd())
		{
			if(gm->GetMagicSircleMoved() == true)
			{
				if (m_PlayerMoveFlgChanged == false)
				{
					gm->SetMoveEnabledFlg(true);
					m_PlayerMoveFlgChanged = true;
				}
			}
		}
		else
		{
			auto delta = App::GetApp()->GetElapsedTime();
			m_Timer += delta;
		}
	}

	void GameManagement::ButtonControl()
	{
		m_InputHandler.PushHandle(GetThis<GameManagement>());
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		WORD wButtons = 0;
		if (cntlVec[0].bConnected) {
			wButtons = cntlVec[0].wPressedButtons;
		}
		auto gm = GameManager::GetInstance();
		switch (gm->GetSceneNum())
		{
		case SceneNum::StageSelect:
		//D�p�b�h��
			if (wButtons & XINPUT_GAMEPAD_DPAD_LEFT) {
				if (gm->GetSelectingButtonNum() > 0)
				{
					gm->SetSelectingButtonMinus();
					testFlg = true;
				}
			}
			//D�p�b�h�E
			if (wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) {
				if (gm->GetSelectingButtonNum() < gm->GetMaxButtonNum())
				{
					gm->SetSelectingButtonPlus();
					testFlg = false;
				}
			}
			break;
		case SceneNum::GameStage1:
		case SceneNum::GameStage2:
		case SceneNum::GameStage3:
		case SceneNum::GameStage4:
		case SceneNum::GameStage5:
			//D�p�b�h��
			if (wButtons & XINPUT_GAMEPAD_DPAD_UP) {
				if (gm->GetSelectingButtonNum() > 0)
				{
					gm->SetSelectingButtonMinus();
					testFlg = true;
				}
			}
			//D�p�b�h��
			if (wButtons & XINPUT_GAMEPAD_DPAD_DOWN) {
				if (gm->GetSelectingButtonNum() < gm->GetMaxButtonNum())
				{
					gm->SetSelectingButtonPlus();
					testFlg = false;
				}
			}
			break;
		}
	}

	void GameManagement::TitleButton_A()
	{
		LoadScene(SceneNum::StageSelect);
	}

	//�X�e�[�W�Z���N�g���̃{�^��
	void GameManagement::StageSelectButton_A()
	{
		auto gm = GameManager::GetInstance();

		switch (gm->GetSelectingButtonNum())
		{
		case 0:
			LoadScene((int)SceneNum::GameStage1);
			break;
		case 1:
			break;
		default:
			break;
		}
	}
	void GameManagement::StageSelectButton_B()
	{
		LoadScene(SceneNum::Title);
	}

	//�Q�[���X�e�[�W���ł̃{�^��
	void GameManagement::GameStageButton_A()
	{
		auto gm = GameManager::GetInstance();
		if (gm->GetClearFlgChanged() == true)
		{
			switch (gm->GetSelectingButtonNum())
			{
			case 0:
				break;
			case 1:
				LoadScene((int)SceneNum::StageSelect);
				break;
			default:
				break;
			}
		}
		if (gm->GetDeathFlgChanged() == true)
		{
			switch (gm->GetSelectingButtonNum())
			{
			case 0:
				LoadScene(gm->GetSceneNum());
				break;
			case 1:
				LoadScene((int)SceneNum::StageSelect);
				break;
			default:
				break;
			}

		}
	}

	//	������
	void GameManagement::OnCreate()
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

	void GameManagement::OnUpdate()
	{
		ButtonControl();
		PlayerMoveEnabled();
	}

	void GameManagement::OnUpdate2()
	{

		DrawStrings();
	}

	void GameManagement::DrawStrings()
	{
		auto gm = GameManager::GetInstance();

		wstring selectingButton(L"�I�����Ă���{�^���̔ԍ� : ");
		selectingButton += Util::UintToWStr(gm->GetSelectingButtonNum()) + L"\n";

		wstring maxButtonNum(L"���݂̃{�^���̍ő�ԍ� : ");
		maxButtonNum += Util::UintToWStr(gm->GetMaxButtonNum()) + L"\n";

		wstring sceneNum(L"���݂̃V�[�� : ");
		switch (gm->GetSceneNum())
		{
		case (int)SceneNum::Title:
			sceneNum += L"�^�C�g��\n";
			break;
		case (int)SceneNum::StageSelect:
			sceneNum += L"�X�e�[�W�Z���N�g\n";
			break;
		case (int)SceneNum::GameStage1:
			sceneNum += L"�Q�[���X�e�[�W�P\n";
			break;
		}

		wstring testFLG(L"�e�X�g�t���O : ");
		testFLG += Util::UintToWStr(testFlg) + L"\n";

		wstring timer(L"m_Timer : ");
		timer += Util::FloatToWStr(m_Timer) + L"\nGetPlayerMoveTime : " + Util::FloatToWStr(gm->GetPlayerMoveTime()) + L"\n";
		

		wstring str = selectingButton + maxButtonNum + sceneNum + testFLG + timer + L"\n";
		auto ptrString = GetComponent<StringSprite>();
		ptrString->SetText(str);
	}

	void GameManagement::OnPushA()
	{
		auto gm = GameManager::GetInstance();
		switch (gm->GetSceneNum())
		{
		case (int)SceneNum::Title:
			TitleButton_A();
			break;
		case (int)SceneNum::StageSelect:
			StageSelectButton_A();
			break;
		case (int)SceneNum::GameStage1:
			GameStageButton_A();
			break;
		}
	}

	void GameManagement::OnPushB()
	{
		auto gm = GameManager::GetInstance();
		switch (gm->GetSceneNum())
		{
		case (int)SceneNum::Title:
			TitleButton_B();
			break;
		case (int)SceneNum::StageSelect:
			StageSelectButton_B();
			break;
		case (int)SceneNum::GameStage1:
			GameStageButton_B();
			break;
		}
	}
}
//end basecross
