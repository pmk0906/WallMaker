/*!
@file Character.cpp
@brief �L�����N�^�[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
	//--------------------------------------------------
	/// �Q�[���^�C�g���V�[��
	//--------------------------------------------------

	void GameStageSelect::CreateViewLight()
	{
		const Vec3 eye(0.0f, 5.0f, -10.0f);
		const Vec3 at(0.0f);
		auto PtrView = CreateView<SingleView>();
		//�r���[�̃J�����̐ݒ�
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(Vec3(0.0f, 2.0f, -3.0f));
		PtrCamera->SetAt(Vec3(0.0f, 0.0f, 0.0f));
		//�}���`���C�g�̍쐬
		auto PtrMultiLight = CreateLight<MultiLight>();
		//�f�t�H���g�̃��C�e�B���O���w��
		PtrMultiLight->SetDefaultLighting();
	}

	void GameStageSelect::CreateTitleSprite()
	{
		AddGameObject<TitleSprite>(L"MAGICWALL_TX", false,
			Vec2(1280.0f, 800.0f), Vec2(0.0f, 0.0f));
	}

	//	������
	void GameStageSelect::OnCreate()
	{
		CreateViewLight();
		//�X�v���C�g�̍쐬
		CreateTitleSprite();
	}

	void GameStageSelect::OnUpdate()
	{
		//�R���g���[���`�F�b�N���ē��͂�����΃R�}���h�Ăяo��
		m_InputHandler.PushHandle(GetThis<GameStageSelect>());

		//�R���g���[���̎擾
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].bConnected) {
			//B�{�^��
			if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B) {
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), WstringKey::ToGameStage);
			}
		}

	}

	void GameStageSelect::OnPushA() 
	{
		PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), WstringKey::ToGameStage);
	}
}
//end basecross
