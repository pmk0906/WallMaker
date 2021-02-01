/*!
@file GameStage6.h
@brief �Q�[���X�e�[�W
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	enum class CameraSelect_Stage6 {
		playerCamera,
		openingCamera,
		myCamera,
		goalCamera,
	};

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class GameStage6 : public Stage {

		//PlayerCamera�p�̃r���[
		shared_ptr<SingleView> m_PlayerCameraView;
		//OpeningCamera�p�̃r���[
		shared_ptr<SingleView> m_OpeningCameraView;
		//MyCamera�p�̃r���[
		shared_ptr<SingleView> m_MyCameraView;
		//GoalCamera�p�̃r���[
		shared_ptr<SingleView> m_GoalCameraView;
		CameraSelect_Stage6 m_CameraSelect;

		//�X�e�[�W�̉��s
		const int STAGE_LENGTH = 20;
		//�X�e�[�W�̉���
		const int STAGE_WIDTH = 28;

		InputHandler<GameStage6> m_InputHandler;

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
		GameStage6() :Stage() {}
		virtual ~GameStage6() {
			StopBGM();
		}

		//������
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		virtual void OnUpdate2() override;
		void DrawStrings();

		void StopBGM();


		void ToMyCamera();
		void ToPlayerCamera();
		void ToGoalCamera();

		void ChangeBGM(wstring bgmKey);
		wstring m_BgmName = L"";
		void SetBgmName(wstring bgmName);
		wstring GetBgmName();

		wstring GetCameraSelectName();

	};


}
//end basecross
