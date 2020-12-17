/*!
@file GameStage4.h
@brief �Q�[���X�e�[�W
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	enum class CameraSelect_Stage4 {
		openingCamera,
		myCamera,
		objCamera,
	};

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class GameStage4 : public Stage {

		//OpeningCamera�p�̃r���[
		shared_ptr<SingleView> m_OpeningCameraView;
		//MyCamera�p�̃r���[
		shared_ptr<SingleView> m_MyCameraView;
		CameraSelect_Stage4 m_CameraSelect;

		//�X�e�[�W�̉��s
		const int STAGE_LENGTH = 16;
		//�X�e�[�W�̉���
		const int STAGE_WIDTH = 32;

		InputHandler<GameStage4> m_InputHandler;

		shared_ptr<SoundItem> m_BGM;

		shared_ptr<GameObject> WhiteSprite = nullptr;
		shared_ptr<GameObject> ResultSprite = nullptr;
		shared_ptr<GameObject> m_Button1 = nullptr;
		shared_ptr<GameObject> m_Button2 = nullptr;
		shared_ptr<GameObject> m_Button3 = nullptr;

		//�r���[�̍쐬
		void CreateViewLight();
		// �X�e�[�W�̍쐬
		void CreateStage();
		void CreateWall();
		//�G�̍쐬
		void CreateEnemy();
		//�v���C���[�̍쐬
		void CreatePlayer(Vec3 pos);
		//UI�̍쐬
		void CreateUI();
		//�J�����}���̍쐬
		void CreateCameraman();

		//�{�^���̍쐬�E�폜
		void CreateClearButton();
		void CreateGameOverButton();
		void CreateSpriteAndButton();
		void SwitchPoseButton(bool poseFlg);

	public:
		//�\�z�Ɣj��
		GameStage4() :Stage() {}
		virtual ~GameStage4() {
			StopBGM();
		}

		void DrawStrings();

		//������
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		void StopBGM();

		void ToMyCamera();
	};


}
//end basecross

