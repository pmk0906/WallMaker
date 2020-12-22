/*!
@file GameStage.h
@brief �Q�[���X�e�[�W
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	enum class CameraSelect_TestStage {
		openingCamera,
		myCamera,
		objCamera,
	};
	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class TestStage : public Stage {

		//OpeningCamera�p�̃r���[
		shared_ptr<SingleView> m_OpeningCameraView;
		//MyCamera�p�̃r���[
		shared_ptr<SingleView> m_MyCameraView;
		CameraSelect_TestStage m_CameraSelect;

		//�X�e�[�W�̉��s
		const int STAGE_LENGTH = 16;
		//�X�e�[�W�̉���
		const int STAGE_WIDTH = 32;

		shared_ptr<SoundItem> m_BGM;

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

	public:
		//�\�z�Ɣj��
		TestStage() :Stage() {}
		virtual ~TestStage() {
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

