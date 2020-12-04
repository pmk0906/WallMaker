
/*!
@file Scene.cpp
@brief �V�[������
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
	//-----------------------------------------------------------------
	//�Q�[���}�l�[�W���[
	//�I������Ă���X�e�[�W��c�����Ă���
	//-----------------------------------------------------------------
	GameManager* GameManager::GM = nullptr;
	GameManager* GameManager::GetInstance() {
		if (GM == nullptr) {
			GM = new GameManager();
		}
		return GM;
	}

	//--------------------------------------------------------------------------------------
	///	�Q�[���V�[��
	//--------------------------------------------------------------------------------------
	
	void Scene::CreateResources() {
		// �f�[�^�f�B���N�g���̎擾
		wstring dataDir;
		App::GetApp()->GetDataDirectory(dataDir);
		// �e�N�X�`��
		wstring texturesDir = dataDir + L"Textures\\";
		// �A�j���[�V����
		wstring animDir = dataDir + L"Animations\\";
		// �I�[�f�B�I
		wstring audioDir = dataDir + L"Audios\\";
		// BGM
		wstring bgmDir = audioDir + L"BGM\\";
		// SE
		wstring seDir = audioDir + L"SE\\";

		struct Pairs
		{
			wstring Key;
			wstring FileName;
		};

		// �e�N�X�`��
		Pairs txPairs[] =
		{
			{L"TRACE_TX", L"trace.png"},
			{L"FLOOR_TX", L"Floor.png"},
			{L"MAGICWALL_TX", L"MagicWall.jpg"},
			{L"WALL_TX", L"BlockWall.tga"},
			{L"HEART_TX", L"Heart.png"},
			{L"WALLSTOCK_TX", L"UI_MagicWall.png"},
			{L"GAMETITLE_TX", L"Title.png"},
			{L"GAMESELECT_BG_TX", L"Select_BackGround.png"},
			{L"WHITE_TX", L"White.png"},
			{L"TO_NEXTSTAGE_TX", L"ToNextStage.png"},
			{L"TO_STAGESELECT_TX", L"ToStageSelect.png"},
			{L"TO_RETRY_TX", L"ToRetry.png"},
			{L"STAGE_1_TX", L"StageNum1.png"},
			{L"STAGE_2_TX", L"StageNum2.png"},
			{L"STAGE_3_TX", L"StageNum3.png"},
			{L"STAGE_4_TX", L"StageNum4.png"},
			{L"STAGE_5_TX", L"StageNum5.png"}
		};
		// �A�j���[�V����
		Pairs animPairs[] = 
		{
			//{WstringKey::Anim_Player, L"PL_Stand.bmf"},
			{WstringKey::Anim_Player, L"PL_Stand_Walk.bmf"}
		};
		//�X�^�e�B�b�N
		Pairs staticPairs[] =
		{
			{L"TREASURE_MESH", L"Treasure.bmf"},
			{L"SHELD_MESH", L"Shield.bmf"},
			{L"ENEMY_MESH", L"Enemy.bmf"},
			{L"STOPENEMY_MESH", L"StopEnemy.bmf"}

		};
		//�^���W�F���g�L��X�^�e�B�b�N
		Pairs staticTangentPairs[] =
		{
			{L"MAGICWALL_MESH", L"MagicWall.bmf"},
			{L"MAGICWALL_RED_MESH", L"MagicWall_R.bmf"}
		};

		Pairs bgmPairs[] =
		{
			{L"SE_CraeteMagicWall", L"magicwall.wav"}
		};

		Pairs sePairs[] =
		{
			{L"SE_CraeteMagicWall", L"magicwall.wav"},
			{L"SE_Bullet", L"Bullet.wav"},
			{L"SE_Reflection", L"Reflection.wav"},
			{L"SE_EnemyDamage", L"EnemyDamage.wav"},
			{L"SE_BreakWall", L"BreakWall.wav"},
			{L"SE_PlayerDamage", L"PlayerDamage.wav"},
			{L"SE_MainBGM", L"MainBGM.wav"},
			{L"SE_GameClear", L"GameClear.wav"},
			{L"SE_GameTitle", L"GameTitle.wav"},
			{L"SE_GameSelect", L"GameSelect.wav"}
		};

		// �e�N�X�`��
		for (auto pair : txPairs)
		{
			wstring strTexture = texturesDir + pair.FileName;
			App::GetApp()->RegisterTexture(pair.Key, strTexture);
		}

		// �A�j���[�V����
		for (auto pair : animPairs)
		{
			auto modelMesh = MeshResource::CreateBoneModelMesh(animDir, pair.FileName);
			App::GetApp()->RegisterResource(pair.Key, modelMesh);
		}
		//�X�^�e�B�b�N
		for (auto pair : staticPairs)
		{
			auto staticModelMesh = MeshResource::CreateStaticModelMesh(animDir, pair.FileName);
			App::GetApp()->RegisterResource(pair.Key, staticModelMesh);
		}
		//�^���W�F���g�L��X�^�e�B�b�N
		for (auto pair : staticTangentPairs)
		{
			auto staticModelMesh = MeshResource::CreateStaticModelMeshWithTangent(animDir, pair.FileName);
			App::GetApp()->RegisterResource(pair.Key, staticModelMesh);
		}

		//BGM
		for (auto pair : sePairs)
		{
			wstring strBGM = bgmDir + pair.FileName;
			App::GetApp()->RegisterWav(pair.Key, strBGM);
		}

		//SE
		for (auto pair : sePairs)
		{
			wstring strSE = seDir + pair.FileName;
			App::GetApp()->RegisterWav(pair.Key, strSE);
		}
	}

	void Scene::OnCreate(){
		try {
			// ���\�[�X�̍쐬
			CreateResources();

			//�N���A����F��ݒ�
			Col4 Col;
			Col.set(31.0f / 255.0f, 30.0f / 255.0f, 71.0f / 255.0f, 255.0f / 255.0f);
			SetClearColor(Col);
			//�������g�ɃC�x���g�𑗂�
			//����ɂ��e�X�e�[�W��I�u�W�F�N�g��Create���ɃV�[���ɃA�N�Z�X�ł���
			PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), WstringKey::ToGameTitle);
		}
		catch (...) {
			throw;
		}
	}

	Scene::~Scene() {
	}

	void Scene::OnEvent(const shared_ptr<Event>& event) {
		if (event->m_MsgStr == WstringKey::ToGameTitle) {
			//�ŏ��̃A�N�e�B�u�X�e�[�W�̐ݒ�
			ResetActiveStage<GameTitle>();
		}
		else if (event->m_MsgStr == WstringKey::ToGameStageSelect) {
			ResetActiveStage<GameStageSelect>();
		}
		else if (event->m_MsgStr == WstringKey::ToGameStage) {
			//�ŏ��̃A�N�e�B�u�X�e�[�W�̐ݒ�
			ResetActiveStage<GameStage>();
		}
	}
}
//end basecross
