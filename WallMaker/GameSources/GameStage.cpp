/*!
@file GameStage.cpp
@brief �Q�[���X�e�[�W����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X����
	//--------------------------------------------------------------------------------------
	void GameStage::CreateViewLight() {
		const Vec3 eye(0.0f, 30.0f, -20.0f);
		const Vec3 at(0.0f);
		auto PtrView = CreateView<SingleView>();
		//�r���[�̃J�����̐ݒ�
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);
		PtrCamera->SetAt(at);
		//�}���`���C�g�̍쐬
		auto PtrMultiLight = CreateLight<MultiLight>();
		//�f�t�H���g�̃��C�e�B���O���w��
		PtrMultiLight->SetDefaultLighting();
	}



	void GameStage::OnCreate() 
	{
		try {
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();
		}
		catch (...) {
			throw;
		}

		CreateStage();
		CreateEnemy();
		CreatePlayer();
		CreateUI();
	}

	void GameStage::OnUpdate() 
	{

	}

	void GameStage::CreateStage()
	{
		// ��
		//AddGameObject<FixedBox>(Vec3(100.0f, 1.0f, 50.0f), Vec3(0.0f), Vec3(0.0f, -0.5f, 0.0f));
		int posX = 0;
		int posZ = 0;
		Vec3 stagePos = Vec3(posX, 0, posZ);
		for (int l = 0; l < STAGE_LENGTH; l++) {
			for (int w = 0; w < STAGE_WIDTH; w++) {
				AddGameObject<Floor>(Vec3(4.0f, 1.0f, 4.0f), Vec3(0.0f), Vec3(w * 4 - STAGE_LENGTH * 2 , 0, l * 4 - STAGE_WIDTH * 2));
			}
		}
	}

	void GameStage::CreateEnemy()
	{
		//�G�@
		AddGameObject<EnemyFirst>(Vec3(2.0f, 1.0f, 3.5f), Vec3(0.0f), Vec3(-5.0f, 1.5f, 0.0f));

		//�����G�i���j
		AddGameObject<PatrolEnemy>(Vec3(3.0f, 1.0f, 2.0f), Vec3(0.0f, XMConvertToRadians(180), 0.0f),
			Vec3(-3.0f, 1.5f, 5.0f));

		//�����G�i�c�j
		AddGameObject<PatrolEnemyUPDown>(Vec3(3.0f, 1.0f, 2.0f), Vec3(0.0f, XMConvertToRadians(270), 0.0f),
			Vec3(10.0f, 1.5f, -5.0f));

		//�A�˂���G
		AddGameObject<RapidFireEnemy>(Vec3(2.0f, 1.0f, 3.5f), Vec3(0.0f), Vec3(0.0f, 1.5f, -5.0f));

	}

	void GameStage::CreatePlayer()
	{
		auto player = AddGameObject<Player>(Vec3(1.0f), Vec3(0.0f), Vec3(0.0f, 2.0f, 0.0f));
		SetSharedGameObject(WstringKey::ShareObj_Player, player);

		SetSharedGameObject(L"Player", player);

	}

	void GameStage::CreateUI()
	{
		//�v���C���[�̃��C�t�\��
		AddGameObject<PlayerLife>(true, Vec2(100.0f), Vec3(-590.0f, 350.0f, 0.1f), 1.0f);
		AddGameObject<PlayerLife>(true, Vec2(100.0f), Vec3(-490.0f, 350.0f, 0.1f), 2.0f);
		AddGameObject<PlayerLife>(true, Vec2(100.0f), Vec3(-390.0f, 350.0f, 0.1f), 3.0f);
		//�ǂ̃X�g�b�N�\��
		AddGameObject<WallStock>(true, Vec2(100.0f), Vec3(-590.0f, 250.0f, 0.1f), 1.0f);
		AddGameObject<WallStock>(true, Vec2(100.0f), Vec3(-490.0f, 250.0f, 0.1f), 2.0f);
		AddGameObject<WallStock>(true, Vec2(100.0f), Vec3(-390.0f, 250.0f, 0.1f), 3.0f);
	}
}
//end basecross
