/*!
@file GameStage.h
@brief �Q�[���X�e�[�W
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class TestStage : public Stage {
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
	};


}
//end basecross
