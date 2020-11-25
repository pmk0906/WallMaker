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
	class GameStage : public Stage {
		//�X�e�[�W�̉��s
		const int STAGE_LENGTH = 10;
		//�X�e�[�W�̉���
		const int STAGE_WIDTH = 10;

		//�r���[�̍쐬
		void CreateViewLight();
		// �X�e�[�W�̍쐬
		void CreateStage();
		//�G�̍쐬
		void CreateEnemy();
		//�v���C���[�̍쐬
		void CreatePlayer();
		//UI�̍쐬
		void CreateUI();

	public:
		//�\�z�Ɣj��
		GameStage() :Stage() {}
		virtual ~GameStage() {}
		//������
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};


}
//end basecross

